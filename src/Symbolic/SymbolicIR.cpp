#include"../header/Pikachu.h"
using namespace Pikachu;
#include<cmath>
#include<cstdio>
#include<cstring>


VISA1::VISA1()
{
    RegCount = 0;
}
VISA1::~VISA1()
{

}

size_t VISA1::RegAllocate(vector<size_t>& FreeReg)
{
    size_t reg_;
    while (FreeReg.pop(reg_) != 0)
        if (reg_ != 0) return reg_;
    RegCount += 1;
    return RegCount;
}
void VISA1::append(ISAT Type, int Op, size_t dst, size_t src1, size_t src2)
{
    instruct New_;
    New_.Type = Type;
    New_.Op = Op;
    New_.dst = dst;
    New_.src1 = src1;
    New_.src2 = src2;
    program.append(New_);
}
size_t VISA1::append(ISAT Type, int Op, vector<size_t>& FreeReg, size_t src1, size_t src2)
{
    instruct New_;
    New_.Type = Type;
    New_.Op = Op;
    New_.dst = RegAllocate(FreeReg);
    New_.src1 = src1;
    New_.src2 = src2;
    program.append(New_);
    return  New_.dst;
}
size_t VISA1::append(vector<size_t>& FreeReg, const FuncConst& Fc)
{
    instruct New_;
    size_t i;
    New_.Type = _ld_;
    New_.Op = _LeafConst_;
    New_.dst = RegAllocate(FreeReg);
    New_.src2 = 0;
    for (i = 0; i < constant.count(); i++)
        if (constant[i] == Fc) break;
    if (i == constant.count())
        constant.append(Fc);
    New_.src1 = i;
    program.append(New_);
    return  New_.dst;
}
size_t VISA1::append(type Type, vector<size_t>& FreeReg, size_t src1, size_t src2, const FuncConst& Fc, size_t label)
{
    switch (Type)
    {
    case _LeafX_:
        return append(VISA1::_ld_, (int)Type, FreeReg, src1, src2);
    case _LeafPara_:
        return append(VISA1::_ld_, (int)Type, FreeReg, src1, src2);
    case _LeafConst_:
        return append(FreeReg, Fc);
    default:
        return label;
    }
}
void VISA1::clear(void)
{
    RegCount = 0;
    program.clear();
    constant.clear();
}
void VISA1::compute(double* const* X, const double* para, double* output) const
{
    vector<double> reg;
    size_t i;
    size_t dst, src1, src2;
    int code;
    reg.recount(RegCount + 1);
    for (i = 0; i < program.count(); i++)
    {
        dst = program[i].dst;
        src1 = program[i].src1;
        src2 = program[i].src2;
        code = program[i].Op;
        switch (program[i].Type)
        {
        case _op_:
            reg[dst] = ComputeOperation(reg[src1], reg[src2], (operation)code);
            break;
        case _func_:
            reg[dst] = ComputeFunction(reg[src1], (function)code);
            break;
        case _st_:
            output[dst] = reg[src1];
            break;
        case _ld_:
            if (program[i].Op == (int)_LeafX_)
                reg[dst] = X[src1][src2];
            else if (program[i].Op == (int)_LeafPara_)
                reg[dst] = para[src2];
            else if (program[i].Op == (int)_LeafConst_)
                reg[dst] = constant[src1].Rvalue();
            break;
        case _func2_:
            reg[dst] = ComputeFunction2(reg[src1], reg[src2], (function2)code);
            break;
        }
    }
}

void VISA1::Demo(FILE* fp) const
{
    size_t i;
    PikaString output;
    fprintf(fp, "Register Count: %zu, Program length: %zu, constant count: %zu\n", RegCount, program.count(), constant.count());
    for (i = 0; i < program.count(); i++)
    {
        fprintf(fp, "\tinst[%zu] ", i);//
        switch (program[i].Type)
        {
        case _op_:
            fprintf(fp, "%s reg[%zu], reg[%zu], reg[%zu];\n", OperationWord((operation)program[i].Op), program[i].dst, program[i].src1, program[i].src2);
            break;
        case _func_:
            fprintf(fp, "%s reg[%zu], reg[%zu];\n", FunctionWord((function)program[i].Op), program[i].dst, program[i].src1);
            break;
        case _st_:
            fprintf(fp, "st output[%zu], reg[%zu];\n", program[i].dst, program[i].src1);
            break;
        case _ld_:
            if (program[i].Op == (int)_LeafX_)
                fprintf(fp, "ld reg[%zu], input[%zu, %zu];\n", program[i].dst, program[i].src1, program[i].src2);
            else if (program[i].Op == (int)_LeafPara_)
                fprintf(fp, "ld reg[%zu], parameter[%zu];\n", program[i].dst, program[i].src2);
            else if (program[i].Op == (int)_LeafConst_)
            {
                constant[program[i].src1].print(output);
                fprintf(fp, "ld reg[%zu], %s;//const[%zu]\n", program[i].dst, output.array(), program[i].src1);
                output.clear();
            }
            break;
        case _func2_:
            fprintf(fp, "%s reg[%zu], reg[%zu], reg[%zu];\n", Function2Word((function2)program[i].Op), program[i].dst, program[i].src1, program[i].src2);
            break;
        }
    }

}

namespace
{
bool IsCppIdentifier(const char* name)
{
    if (name == NULL || name[0] == '\0') return false;
    const char first = name[0];
    if (!((first >= 'a' && first <= 'z') ||
        (first >= 'A' && first <= 'Z') || first == '_')) return false;
    for (size_t i = 1; name[i] != '\0'; ++i)
    {
        const char here = name[i];
        if (!((here >= 'a' && here <= 'z') ||
            (here >= 'A' && here <= 'Z') ||
            (here >= '0' && here <= '9') || here == '_')) return false;
    }
    static const char* keywords[] = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand",
        "bitor", "bool", "break", "case", "catch", "char", "char16_t",
        "char32_t", "class", "compl", "const", "constexpr", "const_cast",
        "continue", "decltype", "default", "delete", "do", "double",
        "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int",
        "long", "main", "mutable", "namespace", "new", "noexcept", "not",
        "not_eq", "nullptr", "operator", "or", "or_eq", "private",
        "protected", "public", "register", "reinterpret_cast", "return",
        "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this",
        "thread_local", "throw", "true", "try", "typedef", "typeid",
        "typename", "union", "unsigned", "using", "virtual", "void",
        "volatile", "wchar_t", "while", "xor", "xor_eq"
    };
    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i)
        if (strcmp(name, keywords[i]) == 0) return false;
    return true;
}

void PrintCppConstant(FILE* output, const FuncConst& constant)
{
    if (constant.IfNan)
    {
        fprintf(output, "std::numeric_limits<double>::quiet_NaN()");
    }
    else if (std::isinf(constant.Rvalue()))
    {
        if (constant.Rvalue() < 0.0) fprintf(output, "-");
        fprintf(output, "std::numeric_limits<double>::infinity()");
    }
    else
    {
        fprintf(output, "%.17g", constant.Rvalue());
    }
}
}

int SymbolicCppBackend::build(const Expres& expression, const char* outputPath,
    const char* functionName, Lowering lowering) const
{
    if (outputPath == NULL || outputPath[0] == '\0' || functionName == NULL)
        return InvalidArgument;
    if (!IsCppIdentifier(functionName)) return InvalidFunctionName;
    if (lowering != MiniOperations && lowering != MiniRegisters) return InvalidArgument;

    VISA1 visa;
    vector<size_t> freeRegisters;
    if (lowering == MiniOperations)
        expression.PrintForwardMiniOp(visa, freeRegisters);
    else
        expression.PrintForwardMiniReg(visa, freeRegisters);
    return build(visa, outputPath, functionName);
}

int SymbolicCppBackend::build(const VISA1& visa, const char* outputPath,
    const char* functionName) const
{
    if (outputPath == NULL || outputPath[0] == '\0' || functionName == NULL)
        return InvalidArgument;
    if (!IsCppIdentifier(functionName)) return InvalidFunctionName;

    FILE* output = fopen(outputPath, "w");
    if (output == NULL) return OpenFailure;
    const int status = print(visa, output, functionName);
    const int closeStatus = fclose(output);
    if (status != Success) return status;
    return closeStatus == 0 ? Success : WriteFailure;
}

int SymbolicCppBackend::print(const VISA1& visa, FILE* output,
    const char* functionName) const
{
    if (output == NULL || functionName == NULL) return InvalidArgument;
    if (!IsCppIdentifier(functionName)) return InvalidFunctionName;

    for (size_t i = 0; i < visa.program.count(); ++i)
    {
        const VISA1::instruct& here = visa.program[i];
        switch (here.Type)
        {
        case VISA1::_op_:
            if (here.Op < (int)_add_ || here.Op > (int)_div_ ||
                here.dst == 0 || here.dst > visa.RegCount ||
                here.src1 == 0 || here.src1 > visa.RegCount ||
                here.src2 == 0 || here.src2 > visa.RegCount)
                return InvalidProgram;
            break;
        case VISA1::_func_:
            if (here.Op < (int)_sin_ || here.Op > (int)_minus_ ||
                here.dst == 0 || here.dst > visa.RegCount ||
                here.src1 == 0 || here.src1 > visa.RegCount)
                return InvalidProgram;
            break;
        case VISA1::_func2_:
            if (here.Op != (int)_pow_ ||
                here.dst == 0 || here.dst > visa.RegCount ||
                here.src1 == 0 || here.src1 > visa.RegCount ||
                here.src2 == 0 || here.src2 > visa.RegCount)
                return InvalidProgram;
            break;
        case VISA1::_st_:
            if (here.src1 == 0 || here.src1 > visa.RegCount)
                return InvalidProgram;
            break;
        case VISA1::_ld_:
            if (here.dst == 0 || here.dst > visa.RegCount)
                return InvalidProgram;
            if (here.Op == (int)_LeafConst_)
            {
                if (here.src1 >= visa.constant.count()) return InvalidProgram;
            }
            else if (here.Op != (int)_LeafX_ && here.Op != (int)_LeafPara_)
            {
                return InvalidProgram;
            }
            break;
        default:
            return InvalidProgram;
        }
    }

    fprintf(output, "// Generated by Pikachu::SymbolicCppBackend.\n");
    fprintf(output, "// VISA1 instructions: %zu, registers: %zu, constants: %zu.\n",
        visa.program.count(), visa.RegCount, visa.constant.count());
    fprintf(output, "#include <cmath>\n");
    fprintf(output, "#include <limits>\n\n");
    fprintf(output, "extern \"C\" void %s(const double* const* input, ", functionName);
    fprintf(output, "const double* parameter, double* output)\n{\n");
    fprintf(output, "    double reg[%zu] = {};\n", visa.RegCount + 1);

    for (size_t i = 0; i < visa.program.count(); ++i)
    {
        const VISA1::instruct& here = visa.program[i];
        switch (here.Type)
        {
        case VISA1::_op_:
        {
            const char* op = "+";
            if ((operation)here.Op == _sub_) op = "-";
            else if ((operation)here.Op == _mul_) op = "*";
            else if ((operation)here.Op == _div_) op = "/";
            fprintf(output, "    reg[%zu] = reg[%zu] %s reg[%zu];\n",
                here.dst, here.src1, op, here.src2);
            break;
        }
        case VISA1::_func_:
            if ((function)here.Op == _minus_)
            {
                fprintf(output, "    reg[%zu] = -reg[%zu];\n", here.dst, here.src1);
            }
            else
            {
                const char* functionNameCpp = "sin";
                if ((function)here.Op == _cos_) functionNameCpp = "cos";
                else if ((function)here.Op == _exp_) functionNameCpp = "exp";
                else if ((function)here.Op == _ln_) functionNameCpp = "log";
                else if ((function)here.Op == _sqrt_) functionNameCpp = "sqrt";
                fprintf(output, "    reg[%zu] = std::%s(reg[%zu]);\n",
                    here.dst, functionNameCpp, here.src1);
            }
            break;
        case VISA1::_func2_:
            fprintf(output, "    reg[%zu] = std::pow(reg[%zu], reg[%zu]);\n",
                here.dst, here.src1, here.src2);
            break;
        case VISA1::_st_:
            fprintf(output, "    output[%zu] = reg[%zu];\n", here.dst, here.src1);
            break;
        case VISA1::_ld_:
            if (here.Op == (int)_LeafX_)
            {
                fprintf(output, "    reg[%zu] = input[%zu][%zu];\n",
                    here.dst, here.src1, here.src2);
            }
            else if (here.Op == (int)_LeafPara_)
            {
                fprintf(output, "    reg[%zu] = parameter[%zu];\n", here.dst, here.src2);
            }
            else
            {
                fprintf(output, "    reg[%zu] = ", here.dst);
                PrintCppConstant(output, visa.constant[here.src1]);
                fprintf(output, ";\n");
            }
            break;
        default:
            return InvalidProgram;
        }
    }
    fprintf(output, "}\n");
    return ferror(output) == 0 ? Success : WriteFailure;
}
