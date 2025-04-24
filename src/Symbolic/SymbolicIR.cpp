#include"../header/Pikachu.h"
using namespace Pikachu;
#include<cmath>


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
    if (FreeReg.pop(reg_) != 0)  return reg_;
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



