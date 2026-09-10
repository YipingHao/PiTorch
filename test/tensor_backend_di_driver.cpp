#include "../src/header/Pikachu.h"

#include <cstdio>

using namespace Pikachu;

class BackendTestNetwork : public NetWork
{
public:
    void AddInput(Node* node) { input.append(node); }
    void AddParameter(Node* node) { parameter.append(node); }
    void AddOutput(Node* node) { AppendOutput(node); }
};

class GaussianWithParameters : public Expres
{
public:
    GaussianWithParameters()
    {
        InputDim.append(1);
        Ele* x = NewNode(_LeafX_, 0, 0);
        Ele* w0 = NewNode(_LeafPara_, 0, 0);
        Ele* w1 = NewNode(_LeafPara_, 0, 1);
        Ele* w2 = NewNode(_LeafPara_, 0, 2);
        Ele* w3 = NewNode(_LeafPara_, 0, 3);
        Ele* w4 = NewNode(_LeafPara_, 0, 4);
        Ele* w5 = NewNode(_LeafPara_, 0, 5);
        Ele* x2 = NewNode(x, x, _mul_);
        Ele* x3 = NewNode(x2, x, _mul_);
        Ele* polynomial = NewNode(w0, NewNode(w1, x, _mul_), _add_);
        polynomial = NewNode(polynomial, NewNode(w2, x2, _mul_), _add_);
        polynomial = NewNode(polynomial, NewNode(w3, x3, _mul_), _add_);
        Ele* z = NewNode(NewNode(x, w4, _mul_), w5, _add_);
        Ele* decay = NewNode(NewNode(NewNode(z, z, _mul_), _minus_), _exp_);
        OutputAppend(NewNode(polynomial, decay, _mul_));
        SetParameterCount(6);
    }
};

static vector<size_t> Dims(size_t first)
{
    vector<size_t> result;
    result.append(first);
    return result;
}

static vector<sint> Indices(sint first)
{
    vector<sint> result;
    result.append(first);
    return result;
}

int main(int argc, char** argv)
{
    const char* outputPath = argc > 1 ? argv[1] : "./output/tensor_backend_di.cpp";
    BackendTestNetwork network;
    Node* input = network.NewNodeLeaf(Dims(2), Node::_leafIn_);
    Node* parameter = network.NewNodeLeaf(Dims(6), Node::_leafPara_);
    network.AddInput(input);
    network.AddParameter(parameter);

    indiceIS indices;
    indices.appendI(Indices(0));
    indices.appendI(Indices(indiceIS::InvalidLabal()));
    vector<sint> functionArguments;
    functionArguments.append(indiceIS::InvalidLabal());
    functionArguments.append(1);
    indices.appendI(functionArguments);
    indices.appendI(Indices(0));
    indices.appendI(Indices(1));

    GaussianWithParameters function;
    Node* output = network.NewNodeDiNonlinear(Dims(2), input, parameter, &function, indices);
    if (output == NULL) return 10;
    network.AddOutput(output);

    TensorCppBackend backend;
    const int status = backend.build(network, outputPath, "pikachu_compute");
    if (status != TensorCppBackend::Success)
        std::fprintf(stderr, "TensorCppBackend failed with status %d\n", status);
    return status;
}
