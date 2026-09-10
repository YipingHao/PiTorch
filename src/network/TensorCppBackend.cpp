#include "../header/Pikachu.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>
#include <limits>

namespace Pikachu
{
namespace
{
struct Storage
{
    enum Kind { Input, Parameter, Workspace } kind;
    size_t offset;
};

struct KernelGroup
{
    std::vector<std::string> names;
    size_t outputsPerKernel;
};

bool IsIdentifier(const char* name)
{
    if (name == NULL || name[0] == '\0') return false;
    const unsigned char first = static_cast<unsigned char>(name[0]);
    if (!(first == '_' || (first >= 'A' && first <= 'Z') ||
        (first >= 'a' && first <= 'z'))) return false;
    for (size_t i = 1; name[i] != '\0'; ++i)
    {
        const unsigned char here = static_cast<unsigned char>(name[i]);
        if (!(here == '_' || (here >= 'A' && here <= 'Z') ||
            (here >= 'a' && here <= 'z') || (here >= '0' && here <= '9')))
            return false;
    }
    return true;
}

std::string Number(double value)
{
    if (std::isnan(value)) return "std::numeric_limits<double>::quiet_NaN()";
    if (std::isinf(value))
        return value < 0.0 ? "-std::numeric_limits<double>::infinity()" :
            "std::numeric_limits<double>::infinity()";
    std::ostringstream output;
    output << std::setprecision(17) << value;
    return output.str();
}

std::vector<size_t> Shape(const Node* node)
{
    std::vector<size_t> shape;
    for (size_t i = 0; i < node->GetOrder(); ++i) shape.push_back(node->GetDim(i));
    return shape;
}

std::vector<size_t> Shape(const Tensor* tensor)
{
    std::vector<size_t> shape;
    for (size_t i = 0; i < tensor->GetOrder(); ++i) shape.push_back((*tensor)[i]);
    return shape;
}

template<class T>
std::vector<T> CopyVector(const Pikachu::vector<T>& source)
{
    std::vector<T> result;
    for (size_t i = 0; i < source.count(); ++i) result.push_back(source[i]);
    return result;
}

size_t FlatOffset(const std::vector<size_t>& shape,
    const std::vector<size_t>& coordinate)
{
    size_t result = 0;
    for (size_t i = 0; i < shape.size(); ++i) result = result * shape[i] + coordinate[i];
    return result;
}

void Enumerate(const std::vector<size_t>& shape,
    const std::function<void(const std::vector<size_t>&)>& action)
{
    std::vector<size_t> coordinate(shape.size(), 0);
    std::function<void(size_t)> visit = [&](size_t axis)
    {
        if (axis == shape.size())
        {
            action(coordinate);
            return;
        }
        for (size_t i = 0; i < shape[axis]; ++i)
        {
            coordinate[axis] = i;
            visit(axis + 1);
        }
    };
    visit(0);
}

bool AddDimensions(std::map<sint, size_t>& dimensions,
    const std::vector<sint>& indices, const std::vector<size_t>& shape)
{
    if (indices.size() != shape.size()) return false;
    for (size_t i = 0; i < indices.size(); ++i)
    {
        std::map<sint, size_t>::const_iterator found = dimensions.find(indices[i]);
        if (found != dimensions.end() && found->second != shape[i]) return false;
        dimensions[indices[i]] = shape[i];
    }
    return true;
}

bool CoordinateFor(const std::vector<sint>& indices,
    const std::map<sint, size_t>& coordinate, std::vector<size_t>& result)
{
    result.resize(indices.size());
    for (size_t i = 0; i < indices.size(); ++i)
    {
        std::map<sint, size_t>::const_iterator found = coordinate.find(indices[i]);
        if (found == coordinate.end()) return false;
        result[i] = found->second;
    }
    return true;
}

std::string Reference(const std::map<const Node*, Storage>& storage,
    const Node* node, size_t element)
{
    const Storage& place = storage.find(node)->second;
    const char* name = place.kind == Storage::Input ? "input" :
        (place.kind == Storage::Parameter ? "parameter" : "workspace.data()");
    std::ostringstream result;
    result << name << "[" << place.offset + element << "]";
    return result.str();
}

bool BuildOutputCoordinate(const std::vector<sint>& indices,
    const std::vector<size_t>& values, std::map<sint, size_t>& coordinate)
{
    if (indices.size() != values.size()) return false;
    coordinate.clear();
    for (size_t i = 0; i < indices.size(); ++i)
    {
        if (coordinate.find(indices[i]) != coordinate.end()) return false;
        coordinate[indices[i]] = values[i];
    }
    return true;
}

std::string FlatExpression(const std::vector<size_t>& shape,
    const std::vector<std::string>& coordinate)
{
    if (shape.size() != coordinate.size()) return std::string();
    if (shape.empty()) return "0";
    std::string result = coordinate[0];
    for (size_t i = 1; i < shape.size(); ++i)
        result = "(" + result + " * " + std::to_string(shape[i]) + " + " + coordinate[i] + ")";
    return result;
}

std::string DynamicReference(const std::map<const Node*, Storage>& storage,
    const Node* node, const std::string& element)
{
    const Storage& place = storage.find(node)->second;
    const char* name = place.kind == Storage::Input ? "input" :
        (place.kind == Storage::Parameter ? "parameter" : "workspace.data()");
    std::ostringstream result;
    result << name << "[" << place.offset << " + " << element << "]";
    return result.str();
}

void OpenLoops(FILE* output, const std::vector<size_t>& shape,
    const std::string& prefix, size_t serial, std::vector<std::string>& variables,
    size_t indentation)
{
    variables.clear();
    for (size_t i = 0; i < shape.size(); ++i)
    {
        std::ostringstream variable;
        variable << prefix << "_" << serial << "_" << i;
        variables.push_back(variable.str());
        fprintf(output, "%*sfor (std::size_t %s = 0; %s < %zu; ++%s)\n%*s{\n",
            static_cast<int>(indentation), "", variable.str().c_str(), variable.str().c_str(),
            shape[i], variable.str().c_str(), static_cast<int>(indentation), "");
        indentation += 4;
    }
}

void CloseLoops(FILE* output, size_t count, size_t indentation)
{
    for (size_t i = 0; i < count; ++i)
    {
        indentation -= 4;
        fprintf(output, "%*s}\n", static_cast<int>(indentation), "");
    }
}

int EmitMonoLinear(const Node& node, const Node* source, double alpha,
    const std::vector<sint>& dstIndices, const std::vector<sint>& srcIndices,
    size_t serial, FILE* output, const std::map<const Node*, Storage>& storage)
{
    const std::vector<size_t> dstShape = Shape(&node);
    const std::vector<size_t> srcShape = Shape(source);
    std::map<sint, size_t> dimensions;
    if (!AddDimensions(dimensions, dstIndices, dstShape) ||
        !AddDimensions(dimensions, srcIndices, srcShape)) return TensorCppBackend::InvalidGraph;

    std::vector<sint> reductionIndices;
    std::vector<size_t> reductionShape;
    for (size_t i = 0; i < srcIndices.size(); ++i)
        if (std::find(dstIndices.begin(), dstIndices.end(), srcIndices[i]) == dstIndices.end())
        {
            reductionIndices.push_back(srcIndices[i]);
            reductionShape.push_back(srcShape[i]);
        }

    fprintf(output, "    {\n");
    std::vector<std::string> dstVariables, reductionVariables;
    OpenLoops(output, dstShape, "i", serial, dstVariables, 8);
    std::map<sint, std::string> coordinate;
    for (size_t i = 0; i < dstIndices.size(); ++i) coordinate[dstIndices[i]] = dstVariables[i];
    const std::string dstReference = DynamicReference(storage, &node,
        FlatExpression(dstShape, dstVariables));
    fprintf(output, "%*s%s = 0.0;\n", static_cast<int>(8 + dstShape.size() * 4), "",
        dstReference.c_str());
    OpenLoops(output, reductionShape, "r", serial, reductionVariables,
        8 + dstShape.size() * 4);
    for (size_t i = 0; i < reductionIndices.size(); ++i)
        coordinate[reductionIndices[i]] = reductionVariables[i];
    std::vector<std::string> srcCoordinate;
    for (size_t i = 0; i < srcIndices.size(); ++i)
    {
        if (coordinate.find(srcIndices[i]) == coordinate.end()) return TensorCppBackend::InvalidGraph;
        srcCoordinate.push_back(coordinate[srcIndices[i]]);
    }
    fprintf(output, "%*s%s += %s * %s;\n",
        static_cast<int>(8 + (dstShape.size() + reductionShape.size()) * 4), "",
        dstReference.c_str(), Number(alpha).c_str(),
        DynamicReference(storage, source, FlatExpression(srcShape, srcCoordinate)).c_str());
    CloseLoops(output, reductionShape.size(), 8 + (dstShape.size() + reductionShape.size()) * 4);
    CloseLoops(output, dstShape.size(), 8 + dstShape.size() * 4);
    fprintf(output, "    }\n");
    return TensorCppBackend::Success;
}

int EmitDiLinear(const Node& node, const Node* left, const Node* right, int op,
    const std::vector<sint>& dstIndices, const std::vector<sint>& leftIndices,
    const std::vector<sint>& rightIndices, size_t serial, FILE* output,
    const std::map<const Node*, Storage>& storage)
{
    const std::vector<size_t> dstShape = Shape(&node);
    const std::vector<size_t> leftShape = Shape(left);
    const std::vector<size_t> rightShape = Shape(right);
    std::map<sint, size_t> dimensions;
    if (!AddDimensions(dimensions, dstIndices, dstShape) ||
        !AddDimensions(dimensions, leftIndices, leftShape) ||
        !AddDimensions(dimensions, rightIndices, rightShape)) return TensorCppBackend::InvalidGraph;

    std::vector<sint> reductionIndices;
    std::vector<size_t> reductionShape;
    for (size_t i = 0; i < leftIndices.size(); ++i)
    {
        const sint index = leftIndices[i];
        if (std::find(dstIndices.begin(), dstIndices.end(), index) == dstIndices.end())
        {
            if (std::find(rightIndices.begin(), rightIndices.end(), index) == rightIndices.end())
                return TensorCppBackend::InvalidGraph;
            reductionIndices.push_back(index);
            reductionShape.push_back(dimensions[index]);
        }
    }
    for (size_t i = 0; i < rightIndices.size(); ++i)
        if (std::find(dstIndices.begin(), dstIndices.end(), rightIndices[i]) == dstIndices.end() &&
            std::find(reductionIndices.begin(), reductionIndices.end(), rightIndices[i]) == reductionIndices.end())
            return TensorCppBackend::InvalidGraph;
    const char* operation = op == Node::_add_ ? "+" :
        (op == Node::_sub_ ? "-" : (op == Node::_mul_ ? "*" : NULL));
    if (operation == NULL) return TensorCppBackend::UnsupportedNode;

    fprintf(output, "    {\n");
    std::vector<std::string> dstVariables, reductionVariables;
    OpenLoops(output, dstShape, "i", serial, dstVariables, 8);
    std::map<sint, std::string> coordinate;
    for (size_t i = 0; i < dstIndices.size(); ++i) coordinate[dstIndices[i]] = dstVariables[i];
    const std::string dstReference = DynamicReference(storage, &node,
        FlatExpression(dstShape, dstVariables));
    fprintf(output, "%*s%s = 0.0;\n", static_cast<int>(8 + dstShape.size() * 4), "",
        dstReference.c_str());
    OpenLoops(output, reductionShape, "r", serial, reductionVariables,
        8 + dstShape.size() * 4);
    for (size_t i = 0; i < reductionIndices.size(); ++i)
        coordinate[reductionIndices[i]] = reductionVariables[i];
    std::vector<std::string> leftCoordinate, rightCoordinate;
    for (size_t i = 0; i < leftIndices.size(); ++i)
    {
        if (coordinate.find(leftIndices[i]) == coordinate.end()) return TensorCppBackend::InvalidGraph;
        leftCoordinate.push_back(coordinate[leftIndices[i]]);
    }
    for (size_t i = 0; i < rightIndices.size(); ++i)
    {
        if (coordinate.find(rightIndices[i]) == coordinate.end()) return TensorCppBackend::InvalidGraph;
        rightCoordinate.push_back(coordinate[rightIndices[i]]);
    }
    fprintf(output, "%*s%s += %s %s %s;\n",
        static_cast<int>(8 + (dstShape.size() + reductionShape.size()) * 4), "",
        dstReference.c_str(),
        DynamicReference(storage, left, FlatExpression(leftShape, leftCoordinate)).c_str(), operation,
        DynamicReference(storage, right, FlatExpression(rightShape, rightCoordinate)).c_str());
    CloseLoops(output, reductionShape.size(), 8 + (dstShape.size() + reductionShape.size()) * 4);
    CloseLoops(output, dstShape.size(), 8 + dstShape.size() * 4);
    fprintf(output, "    }\n");
    return TensorCppBackend::Success;
}

size_t FunctionFlat(const std::vector<size_t>& coordinate,
    const std::vector<size_t>& shape, size_t begin)
{
    size_t result = 0;
    for (size_t i = begin; i < shape.size(); ++i) result = result * shape[i] + coordinate[i];
    return result;
}

template<class Nonlinear, class Formula>
int EmitNonlinearCore(const Nonlinear& node, const Formula& formula,
    const Node* source, const Node* parameterSource, const std::vector<sint>& srcIndices,
    const std::vector<sint>& paraIndices, bool scalarInput, sint inputIndex,
    bool scalarParameter, sint parameterIndex, const std::vector<sint>& dstIndices,
    const std::vector<sint>& functionIndices, const std::vector<size_t>& functionShape,
    const KernelGroup& kernels, FILE* output,
    const std::map<const Node*, Storage>& storage)
{
    const std::vector<size_t> dstShape = Shape(&node);
    const std::vector<size_t> srcShape = Shape(source);
    const std::vector<size_t> paraShape = parameterSource ? Shape(parameterSource) : std::vector<size_t>();
    std::vector<size_t> activeFunctionShape;
    std::vector<size_t> activeFunctionAxes;
    if (functionIndices.size() == functionShape.size())
    {
        activeFunctionShape = functionShape;
        for (size_t i = 0; i < functionShape.size(); ++i) activeFunctionAxes.push_back(i);
    }
    else
    {
        for (size_t i = 0; i < functionShape.size(); ++i)
            if (functionShape[i] != 1)
            {
                activeFunctionShape.push_back(functionShape[i]);
                activeFunctionAxes.push_back(i);
            }
        if (functionIndices.size() != activeFunctionShape.size())
            return TensorCppBackend::InvalidGraph;
    }

    std::map<sint, size_t> dimensions;
    if (!AddDimensions(dimensions, dstIndices, dstShape) ||
        !AddDimensions(dimensions, srcIndices, srcShape) ||
        !AddDimensions(dimensions, functionIndices, activeFunctionShape) ||
        (parameterSource && !AddDimensions(dimensions, paraIndices, paraShape)))
        return TensorCppBackend::InvalidGraph;

    const size_t inputCount = formula.GetInputDim();
    if (inputCount == 0 || (scalarInput && inputCount != 1)) return TensorCppBackend::InvalidGraph;
    size_t parameterCount = 0;
    if (!kernels.names.empty()) parameterCount = formula[0]->ParameterAmount();
    if (!parameterSource && parameterCount != 0) return TensorCppBackend::UnsupportedNode;
    if (parameterSource && parameterCount == 0) return TensorCppBackend::InvalidGraph;

    int status = TensorCppBackend::Success;
    Enumerate(dstShape, [&](const std::vector<size_t>& dstCoordinate)
    {
        if (status != TensorCppBackend::Success) return;
        std::map<sint, size_t> coordinate;
        if (!BuildOutputCoordinate(dstIndices, dstCoordinate, coordinate))
        {
            status = TensorCppBackend::InvalidGraph;
            return;
        }
        std::vector<size_t> activeFunctionCoordinate;
        if (!CoordinateFor(functionIndices, coordinate, activeFunctionCoordinate))
        {
            status = TensorCppBackend::InvalidGraph;
            return;
        }
        std::vector<size_t> functionCoordinate(functionShape.size(), 0);
        for (size_t i = 0; i < activeFunctionAxes.size(); ++i)
            functionCoordinate[activeFunctionAxes[i]] = activeFunctionCoordinate[i];

        size_t kernelIndex = 0;
        size_t kernelOutput = 0;
        if (kernels.outputsPerKernel == 1)
            kernelIndex = FunctionFlat(functionCoordinate, functionShape, 0);
        else
        {
            if (functionCoordinate.empty() || kernels.outputsPerKernel != functionShape[0])
            {
                status = TensorCppBackend::InvalidGraph;
                return;
            }
            kernelOutput = functionCoordinate[0];
            kernelIndex = FunctionFlat(functionCoordinate, functionShape, 1);
        }
        if (kernelIndex >= kernels.names.size())
        {
            status = TensorCppBackend::InvalidGraph;
            return;
        }

        fprintf(output, "    {\n");
        fprintf(output, "        double kernel_input_values[%zu];\n", inputCount);
        for (size_t i = 0; i < inputCount; ++i)
        {
            std::map<sint, size_t> sourceMap = coordinate;
            if (!scalarInput) sourceMap[inputIndex] = i;
            std::vector<size_t> sourceCoordinate;
            if (!CoordinateFor(srcIndices, sourceMap, sourceCoordinate))
            {
                status = TensorCppBackend::InvalidGraph;
                return;
            }
            fprintf(output, "        kernel_input_values[%zu] = %s;\n", i,
                Reference(storage, source, FlatOffset(srcShape, sourceCoordinate)).c_str());
        }
        fprintf(output, "        const double* kernel_inputs[1] = { kernel_input_values };\n");
        if (parameterSource)
        {
            fprintf(output, "        double kernel_parameters[%zu];\n", parameterCount);
            for (size_t i = 0; i < parameterCount; ++i)
            {
                std::map<sint, size_t> parameterMap = coordinate;
                if (!scalarParameter) parameterMap[parameterIndex] = i;
                std::vector<size_t> parameterCoordinate;
                if (!CoordinateFor(paraIndices, parameterMap, parameterCoordinate))
                {
                    status = TensorCppBackend::InvalidGraph;
                    return;
                }
                fprintf(output, "        kernel_parameters[%zu] = %s;\n", i,
                    Reference(storage, parameterSource,
                        FlatOffset(paraShape, parameterCoordinate)).c_str());
            }
        }
        fprintf(output, "        double kernel_output[%zu] = {};\n", kernels.outputsPerKernel);
        fprintf(output, "        %s(kernel_inputs, %s, kernel_output);\n",
            kernels.names[kernelIndex].c_str(), parameterSource ? "kernel_parameters" : "0");
        fprintf(output, "        %s = kernel_output[%zu];\n",
            Reference(storage, &node, FlatOffset(dstShape, dstCoordinate)).c_str(), kernelOutput);
        fprintf(output, "    }\n");
    });
    return status;
}
}

int TensorCppBackend::build(const NetWork& net, const char* outputPath,
    const char* functionName) const
{
    if (outputPath == NULL || outputPath[0] == '\0') return InvalidArgument;
    FILE* output = fopen(outputPath, "w");
    if (output == NULL) return OpenFailure;
    const int status = print(net, output, functionName);
    const int closeStatus = fclose(output);
    if (status != Success) return status;
    return closeStatus == 0 ? Success : WriteFailure;
}

int TensorCppBackend::print(const NetWork& net, FILE* output,
    const char* functionName) const
{
    if (output == NULL || functionName == NULL) return InvalidArgument;
    if (!IsIdentifier(functionName)) return InvalidFunctionName;

    // Follow incoming operands from the declared outputs.  Derivative graphs can
    // legitimately retain seed/identity nodes outside graph.content, and the
    // legacy graph also coalesces duplicate outgoing neighbours for x*x.
    // Dependency DFS handles both cases and drops unreachable graph nodes.
    Pikachu::vector<Node*> sequence;
    std::set<Node*> visiting, visited;
    bool dependencyError = false;
    std::function<void(Node*)> visit = [&](Node* node)
    {
        if (node == NULL || dependencyError || visited.find(node) != visited.end()) return;
        if (visiting.find(node) != visiting.end())
        {
            dependencyError = true;
            return;
        }
        visiting.insert(node);
        for (size_t i = 0; i < node->InDegree(); ++i) visit(node->In(i));
        visiting.erase(node);
        visited.insert(node);
        sequence.append(node);
    };
    for (size_t i = 0; i < net.output.count(); ++i) visit(net.output[i]);
    if (dependencyError)
    {
        fprintf(stderr, "TensorCppBackend: dependency graph contains a cycle.\n");
        return InvalidGraph;
    }
    std::map<const Node*, Storage> storage;
    size_t inputOffset = 0, parameterOffset = 0, workspaceOffset = 0;
    for (size_t i = 0; i < net.input.count(); ++i)
    {
        if (net.input[i] == NULL)
        {
            fprintf(stderr, "TensorCppBackend: null input node %zu.\n", i);
            return InvalidGraph;
        }
        storage[net.input[i]] = Storage{ Storage::Input, inputOffset };
        inputOffset += net.input[i]->GetElementCount();
    }
    for (size_t i = 0; i < net.parameter.count(); ++i)
    {
        if (net.parameter[i] == NULL || storage.find(net.parameter[i]) != storage.end())
        {
            fprintf(stderr, "TensorCppBackend: invalid parameter node %zu.\n", i);
            return InvalidGraph;
        }
        storage[net.parameter[i]] = Storage{ Storage::Parameter, parameterOffset };
        parameterOffset += net.parameter[i]->GetElementCount();
    }
    for (size_t i = 0; i < sequence.count(); ++i)
    {
        Node* node = sequence[i];
        if (node == NULL)
        {
            fprintf(stderr, "TensorCppBackend: null node in topological order at %zu.\n", i);
            return InvalidGraph;
        }
        if (storage.find(node) == storage.end())
        {
            storage[node] = Storage{ Storage::Workspace, workspaceOffset };
            workspaceOffset += node->GetElementCount();
        }
    }
    for (size_t i = 0; i < net.output.count(); ++i)
        if (net.output[i] == NULL || storage.find(net.output[i]) == storage.end())
        {
            fprintf(stderr, "TensorCppBackend: output node %zu is absent from the graph.\n", i);
            return InvalidGraph;
        }

    fprintf(output, "// Generated by Pikachu::TensorCppBackend.\n");
    fprintf(output, "// Static row-major CPU graph; input/parameter/output are flattened.\n");
    fprintf(output, "#include <cmath>\n#include <cstddef>\n#include <limits>\n#include <vector>\n\n");

    std::map<const Node*, KernelGroup> kernelGroups;
    SymbolicCppBackend symbolic;
    size_t kernelSerial = 0;
    for (size_t i = 0; i < sequence.count(); ++i)
    {
        Node* node = sequence[i];
        size_t clusterCount = 0;
        const MonoNonlinear* mono = NULL;
        const DiNonlinear* dual = NULL;
        if (node->Type == Node::_MonoNonlinear_) mono = static_cast<const MonoNonlinear*>(node);
        else if (node->Type == Node::_DiNonlinear_) dual = static_cast<const DiNonlinear*>(node);
        else continue;

        const Expres* first = mono ? mono->formula[0] : dual->formula[0];
        if (first == NULL || first->InputGroup() != 1 || first->OutputAmount() == 0)
            return UnsupportedNode;
        const size_t outputsPerKernel = first->OutputAmount();
        const size_t functionElements = mono ? mono->funcTensor.GetCount() : dual->funcTensor.GetCount();
        if (functionElements == 0 || functionElements % outputsPerKernel != 0) return InvalidGraph;
        clusterCount = functionElements / outputsPerKernel;

        KernelGroup group;
        group.outputsPerKernel = outputsPerKernel;
        for (size_t k = 0; k < clusterCount; ++k)
        {
            const Expres* expression = mono ? mono->formula[k] : dual->formula[k];
            if (expression == NULL || expression->InputGroup() != 1 ||
                expression->OutputAmount() != outputsPerKernel)
                return InvalidGraph;
            std::ostringstream name;
            name << functionName << "_kernel_" << kernelSerial++;
            VISA1 visa;
            Pikachu::vector<size_t> freeRegisters;
            expression->PrintForwardMiniReg(visa, freeRegisters);
            const int symbolicStatus = symbolic.print(visa, output, name.str().c_str());
            if (symbolicStatus != SymbolicCppBackend::Success) return SymbolicFailure;
            fprintf(output, "\n");
            group.names.push_back(name.str());
        }
        kernelGroups[node] = group;
    }

    fprintf(output, "extern \"C\" std::size_t %s_input_count() { return %zu; }\n",
        functionName, inputOffset);
    fprintf(output, "extern \"C\" std::size_t %s_parameter_count() { return %zu; }\n",
        functionName, parameterOffset);
    size_t outputCount = 0;
    for (size_t i = 0; i < net.output.count(); ++i) outputCount += net.output[i]->GetElementCount();
    fprintf(output, "extern \"C\" std::size_t %s_output_count() { return %zu; }\n\n",
        functionName, outputCount);
    fprintf(output, "extern \"C\" void %s(const double* input, const double* parameter, double* output)\n{\n",
        functionName);
    fprintf(output, "    std::vector<double> workspace(%zu, 0.0);\n", workspaceOffset);

    for (size_t i = 0; i < sequence.count(); ++i)
    {
        Node* node = sequence[i];
        int status = Success;
        if (node->Type == Node::_leaf_)
        {
            const LeafNode* leaf = static_cast<const LeafNode*>(node);
            if (storage[node].kind != Storage::Workspace) continue;
            if (node->Op != Node::_leafConst_) return InvalidGraph;
            for (size_t j = 0; j < node->GetElementCount(); ++j)
            {
                const double value = j < leaf->value.count() ? leaf->value[j].Rvalue() : 0.0;
                fprintf(output, "    %s = %s;\n", Reference(storage, node, j).c_str(),
                    Number(value).c_str());
            }
        }
        else if (node->Type == Node::_MonoLinear_)
        {
            const MonoLinear& linear = *static_cast<const MonoLinear*>(node);
            if (linear.InDegree() != 1) return InvalidGraph;
            status = EmitMonoLinear(linear, node->In(0), linear.alpha,
                CopyVector(linear.indexDst), CopyVector(linear.indexSrc), i, output, storage);
        }
        else if (node->Type == Node::_DiLinear_)
        {
            const DiLinear& linear = *static_cast<const DiLinear*>(node);
            if (linear.InDegree() != 2) return InvalidGraph;
            status = EmitDiLinear(linear, node->In(0), node->In(1), linear.Op,
                CopyVector(linear.indexDst), CopyVector(linear.indexSrcL),
                CopyVector(linear.indexSrcR), i, output, storage);
        }
        else if (node->Type == Node::_MonoNonlinear_)
        {
            const MonoNonlinear& nonlinear = *static_cast<const MonoNonlinear*>(node);
            if (nonlinear.InDegree() != 1) return InvalidGraph;
            status = EmitNonlinearCore(nonlinear, nonlinear.formula, node->In(0), NULL,
                CopyVector(nonlinear.indexSrc), std::vector<sint>(), nonlinear.ScalarInput,
                nonlinear.x, true, -1, CopyVector(nonlinear.indexDst),
                CopyVector(nonlinear.function), Shape(&nonlinear.funcTensor),
                kernelGroups[node], output, storage);
        }
        else if (node->Type == Node::_DiNonlinear_)
        {
            const DiNonlinear& nonlinear = *static_cast<const DiNonlinear*>(node);
            if (nonlinear.InDegree() != 2) return InvalidGraph;
            status = EmitNonlinearCore(nonlinear, nonlinear.formula,
                node->In(0), node->In(1), CopyVector(nonlinear.indexSrc),
                CopyVector(nonlinear.indexPara), nonlinear.ScalarInput, nonlinear.x,
                nonlinear.ScalarPara, nonlinear.omega, CopyVector(nonlinear.indexDst),
                CopyVector(nonlinear.function), Shape(&nonlinear.funcTensor),
                kernelGroups[node], output, storage);
        }
        else return UnsupportedNode;
        if (status != Success) return status;
    }

    size_t flatOutput = 0;
    for (size_t i = 0; i < net.output.count(); ++i)
        for (size_t j = 0; j < net.output[i]->GetElementCount(); ++j)
            fprintf(output, "    output[%zu] = %s;\n", flatOutput++,
                Reference(storage, net.output[i], j).c_str());
    fprintf(output, "}\n");
    return ferror(output) == 0 ? Success : WriteFailure;
}
}
