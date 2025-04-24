#include"../header/Pikachu.h"
using namespace Pikachu;
#include<cmath>


#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif


void FuncConst::nan(void)
{
    IfNan = true;
    RealConst = 0.0;
    IntConst = 0;
}
double FuncConst::Rvalue(void) const
{
    return IfInt ? (double)IntConst : RealConst;
}
void FuncConst::SetValue(long long int ele)
{
    IfNan = false;
    IfInt = true;
    RealConst = (double)ele;
    IntConst = ele;
}
void FuncConst::SetValue(double ele)
{
    double temp;
    long long int middle;
    temp = ele;
    middle = (long long int)temp;
    temp -= (double)middle;
    IfInt = (temp == 0.0);
    if (std::isnan(ele))
    {
        nan();
    }
    else
    {
        IfNan = false;
        RealConst = ele;
        IntConst = (long long int)ele;
    }
}
void FuncConst::SetValue(const FuncConst& ele)
{
    IfNan = ele.IfNan;
    IfInt = ele.IfInt;
    RealConst = ele.RealConst;
    IntConst = ele.IntConst;
}

bool FuncConst::operator==(long long int ele) const
{
    return (IfInt ? ele == IntConst : false) && !IfNan;
}
bool FuncConst::operator==(double ele) const
{
    return (IfNan ? std::isnan(ele) : (IfInt ? false : (ele == RealConst)));
}
bool FuncConst::operator==(const FuncConst& ele) const
{
    return IfNan ? ele.IfNan : (IfInt ? (IntConst == ele.IntConst) : (RealConst == ele.RealConst));
}

void FuncConst::operator=(long long int ele)
{
    SetValue(ele);
}
void FuncConst::operator=(double ele)
{
    SetValue(ele);
}
void FuncConst::operator=(const FuncConst& ele)
{
    SetValue(ele);
}
FuncConst FuncConst::operator+(const FuncConst& right)
{
    FuncConst result;
    if (IfNan || right.IfNan)
        result.nan();
    else if (right.IfInt && IfInt)
    {
        long long int ele;
        ele = IntConst + right.IntConst;
        result = ele;
    }
    else
    {
        double here;
        here = Rvalue() + right.Rvalue();
        result = here;
    }
    return result;
}
FuncConst FuncConst::operator-(const FuncConst& right)
{
    FuncConst result;
    if (IfNan || right.IfNan)
        result.nan();
    else if (right.IfInt && IfInt)
    {
        long long int ele;
        ele = IntConst - right.IntConst;
        result = ele;
    }
    else
    {
        double here;
        here = Rvalue() - right.Rvalue();
        result = here;
    }
    return result;
}
FuncConst FuncConst::operator*(const FuncConst& right)
{
    FuncConst result;
    if (IfNan || right.IfNan)
        result.nan();
    else if (right.IfInt && IfInt)
    {
        long long int ele;
        ele = IntConst * right.IntConst;
        result = ele;
    }
    else
    {
        double here;
        here = Rvalue() * right.Rvalue();
        result = here;
    }
    return result;
}
FuncConst FuncConst::operator/(const FuncConst& right)
{
    FuncConst result;
    if ((right.IfInt ? right.IntConst == 0 : right.RealConst == 0.0) || right.IfNan || IfNan)
    {
        result.nan();
    }
    else if (right.IfInt && IfInt && (IntConst % right.IntConst == 0))
    {
        long long int ele;
        ele = IntConst / right.IntConst;
        result = ele;
    }
    else
    {
        double here;
        here = Rvalue() / right.Rvalue();
        result = here;
    }
    return result;
}

bool FuncConst::isZero(void) const
{
    return IfInt ? (IntConst == (long long int)0) : (RealConst == 0.0);
}
bool FuncConst::isOne(void) const
{
    return IfInt ? (IntConst == (long long int)1) : (RealConst == 1.0);
}

void FuncConst::sin(void)
{
    if (IfInt && IntConst == 0)
    {
        IntConst = 0;
        RealConst = 0.0;
    }   
    else
    {
        RealConst = std::sin(IfInt ? (double)IntConst : RealConst);
        IntConst = (long long int)RealConst;
        IfInt = false;
    }
}
void FuncConst::cos(void)
{
    if (IfInt && IntConst == 0)
    {
        IntConst = 1;
        RealConst = 1.0;
    }
    else
    {
        RealConst = std::cos(IfInt ? (double)IntConst : RealConst);
        IntConst = (long long int)RealConst;
        IfInt = false;
    }
}
void FuncConst::opposite(void)
{
    IntConst = -IntConst;
    RealConst = -RealConst;
}
void FuncConst::ln(void)
{
    if (IntConst <= 0 || RealConst <= 0.0)
    {
        IfNan = true;
        hyperlex::dictionary* error;
        error = new hyperlex::dictionary;
        error->append("location", "void FuncConst::ln(void)");
        error->append("error", "IntConst <= 0 || RealConst <= 0.0");
        error->append("IntConst", (long int)IntConst);
        error->append("RealConst", RealConst);
        throw error;
    }
    //printf("??????%d, IntConst: %lld, RealConst:%lf\n", (int)IfInt, IntConst, RealConst);
    if (IfInt && (IntConst == (long long)1))
    {
        IntConst = 0;
        RealConst = 0.0;
    }
    else
    {
        RealConst = std::log(IfInt ? (double)IntConst : RealConst);
        IfInt = false;
        IntConst = (long long int)RealConst;
        //printf("??????%d, IntConst: %lld, RealConst:%lf\n", (int)IfInt, IntConst, RealConst);
    }
}
void FuncConst::exp(void)
{
    if (IfInt && IntConst == 0)
    {
        IntConst = 1;
        RealConst = 1.0;
    }
    else
    {
        RealConst = std::exp(IfInt ? (double)IntConst : RealConst);
        IntConst = (long long int)RealConst;
        IfInt = false;
    }
}
void FuncConst::sqrt(void)
{
    long long int i, value;
    if (IfInt)
    {
        value = IntConst;
        for (i = 0; i < value; i++)
            if (i * i == value)
            {
                SetValue(i);
                return;
            }
    }
    SetValue(std::sqrt(IfInt ? (double)IntConst : RealConst));
}
void FuncConst::pow(const FuncConst& exponential)
{
    if (IfNan || exponential.IfNan) nan();
    else if (exponential.IfInt)
    {
        long long int cycle, i, base;
        double temp;
        cycle = exponential.IntConst >= 0 ? exponential.IntConst : -exponential.IntConst;
        if (IfInt)
        {
            base = 1;
            for (i = 0; i < cycle; i++) base *= IntConst;
            if (exponential.IntConst >= 0) SetValue(base);
            else if (IntConst <= 0) nan();
            else SetValue((double)(1.0 / ((double)base) ) );
        }
        else 
        {
            temp = 1.0;
            for (i = 0; i < cycle; i++) temp *= RealConst;
            if (exponential.IntConst >= 0) SetValue(temp);
            else if (RealConst <= 0.0) nan();
            else SetValue(1.0 / temp);
        }
    }
    else
        SetValue(std::pow(RealConst, exponential.RealConst));
    return;
}
void FuncConst::null(void)
{
    return;
}

void FuncConst::print(PikaString& output)const
{
    if (IfNan) output += "nan";
    else if (IfInt) output += IntConst;
    else output += RealConst;
}
void FuncConst::print(hyperlex::BufferChar& output)const
{
    if (IfNan) output += "nan";
    else if (IfInt) output += (long int)IntConst;
    else output += RealConst;
}
FuncConst FuncConst::compute(FuncConst& left, FuncConst& right, operation Opera)
{
    FuncConst result;
    switch (Opera)
    {
    case _add_:
        result = left + right;
        break;
    case _sub_:
        result = left - right;
        break;
    case _mul_:
        result = left * right;
        break;
    case _div_:
        result = left / right;
        break;
    }
    return result;
}
void FuncConst::ComputeSet(FuncConst& left, FuncConst& right, operation Opera)
{
    FuncConst result; 
    result = compute(left, right, Opera);
    SetValue(result);
}
FuncConst FuncConst::compute(FuncConst& left, function Func)
{
    FuncConst result;
    result = left;
    switch (Func)
    {
    case _sin_:
        result.sin();
        break;
    case _cos_:
        result.cos();
        break;
    case _exp_:
        result.exp();
        break;
    case _ln_:
        result.ln();
        break;
    case _sqrt_:
        result.sqrt();
        break;
    //case linear:
    //    result.null();
    //    break;
    case _minus_:
        result.opposite();
        break;
    default:
        break;
    }
    return result;
}
void FuncConst::ComputeSet(FuncConst& left, function Func)
{
    FuncConst result;
    result = compute(left, Func);
    SetValue(result);
}
FuncConst FuncConst::compute(FuncConst& left, FuncConst& right, function2 Func2)
{
    FuncConst result;
    result = left;
    switch (Func2)
    {
    case _pow_:
        result.pow(right);
        break;
    default:
        break;
    }
    return result;
}
void FuncConst::ComputeSet(FuncConst& left, FuncConst& right, function2 Func2)
{
    FuncConst result;
    result = compute(left, right, Func2);
    SetValue(result);
}



const char* Pikachu::FunctionName(function Fu)
{
    switch (Fu)
    {
    case Pikachu::_sin_:
        return "sin";
    case Pikachu::_cos_:
        return "cos";
    case Pikachu::_exp_:
        return "exp";
    case Pikachu::_ln_:
        return "ln";
    case Pikachu::_sqrt_:
        return "sqrt";
    case Pikachu::_minus_:
        return "-";
    }
    return "???";
}
const char* Pikachu::Function2Name(function2 Fu2)
{
    switch (Fu2)
    {
    case Pikachu::_pow_:
        return "pow";
    }
    return "???";
}
const char* Pikachu::OperationName(operation Op)
{
    switch (Op)
    {
    case Pikachu::_add_:
        return " + ";
    case Pikachu::_sub_:
        return " - ";
    case Pikachu::_mul_:
        return " * ";
    case Pikachu::_div_:
        return " / ";
    }
    return "???";
}
const char* Pikachu::OperationWord(operation Op)
{
    switch (Op)
    {
    case Pikachu::_add_:
        return "add";
    case Pikachu::_sub_:
        return "sub";
    case Pikachu::_mul_:
        return "mul";
    case Pikachu::_div_:
        return "div";
    }
    return "???";
}
const char* Pikachu::FunctionWord(function Fu)
{
    switch (Fu)
    {
    case Pikachu::_sin_:
        return "sin";
    case Pikachu::_cos_:
        return "cos";
    case Pikachu::_exp_:
        return "exp";
    case Pikachu::_ln_:
        return "ln";
    case Pikachu::_sqrt_:
        return "sqrt";
    case Pikachu::_minus_:
        return "minus";
    }
    return "???";
}
const char* Pikachu::Function2Word(function2 Fu2)
{
    switch (Fu2)
    {
    case Pikachu::_pow_:
        return "pow";
    }
    return "???";
}
bool Pikachu::isLeaf(enum type T)
{
    return (T == _LeafPara_) || (T == _LeafConst_) || (T == _LeafX_);
}
double Pikachu::ComputeOperation(double src1, double src2, operation Op)
{
    switch (Op)
    {
    case Pikachu::_add_:
        return src1 + src2;
    case Pikachu::_sub_:
        return src1 - src2;
    case Pikachu::_mul_:
        return src1 * src2;
    case Pikachu::_div_:
        return src1 / src2;
    }
    return 0.0;
}
double Pikachu::ComputeFunction(double src1, function Fu)
{
    switch (Fu)
    {
    case Pikachu::_sin_:
        return std::sin(src1);
    case Pikachu::_cos_:
        return std::cos(src1);
    case Pikachu::_exp_:
        return std::exp(src1);
    case Pikachu::_ln_:
        return std::log(src1);
    case Pikachu::_sqrt_:
        return std::sqrt(src1);
    case Pikachu::_minus_:
        return -(src1);
    }
    return 0.0;
}
double Pikachu::ComputeFunction2(double src1, double src2, function2 Fu2)
{
    switch (Fu2)
    {
    case Pikachu::_pow_:
        return std::pow(src1, src2);
    }
    return 0.0;
}

Activation::Activation()
{
    //ParameterCount = 0;
}
Activation::~Activation()
{

}
Activation::ActivationVortex::ActivationVortex(long long int ele)
{
    Type = _LeafConst_;
    Fc.SetValue(ele);
}
Activation::ActivationVortex::ActivationVortex(operation opera_)
{
    Type = _Operation_;
    Op = opera_;
}
Activation::ActivationVortex::ActivationVortex(function func_)
{
    Type = _Funct_;
    Fu = func_;
}
Activation::ActivationVortex* Activation::ActivationVortex::copy(void)
{
    ActivationVortex* New;
    New = new ActivationVortex();
    New->Type = Type;
    New->Op = Op;
    New->Fu = Fu;
    New->Fu2 = Fu2;
    New->Fc.SetValue(Fc);
    return New;
}
void Activation::ActivationVortex::Demo(size_t label, PikaString& output) const
{
    switch (Type)
    {
    case Pikachu::_LeafX_:
        output += "x";
        break;
    case Pikachu::_LeafConst_:
        Fc.print(output);
        break;
    case Pikachu::_LeafPara_:
        output += "w_";
        Fc.print(output);
        break;
    case Pikachu::_Funct_:
        if (label == 1)  output += ")";
        else
        {
            output += FunctionName(Fu);
            output += "(";
        }
        break;
    case Pikachu::_Operation_:
        if (label == 0)  output += "(";
        else if (label == 2)  output += ")";
        else  output += OperationName(Op);
        break;
    case Pikachu::_Funct2_:
        if (label == 1)
        {
            output += ", ";
        }
        else if (label == 2)
        {
            output += ")";
        }
        else
        {
            output += Function2Name(Fu2);
            output += "(";
        }
        break;
    }
}
void Activation::ActivationVortex::Demo(FILE* fp) const
{
    PikaString output;
    switch (Type)
    {
    case Pikachu::_LeafX_:
        output += "x";
        break;
    case Pikachu::_LeafConst_:
        Fc.print(output);
        break;
    case Pikachu::_LeafPara_:
        output += "w_";
        Fc.print(output);
        break;
    case Pikachu::_Funct_:
        output += FunctionName(Fu);
        break;
    case Pikachu::_Operation_:
        output += OperationName(Op);
        break;
    case Pikachu::_Funct2_:
        output += Function2Name(Fu2);
        break;
    }
    fprintf(fp, "%s.\n", output.array());
}

void Activation::differetial(void)
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    size_t i, length, now, site;
    ActivationVortex* here, *New;

    queue.append(output);
    formula.BFTbackward(label, queue);
    //formula.path(label, queue, input, output);
    formula.TopologicalSorting(sequence);
#ifdef Debug03_01 
    for (i = 0; i < sequence.count(); i++)
    {
        std::cout << "sequence[" << i << "] = " << sequence[i] << std::endl;
    }
#endif
    formula.SortingShrink(label, sequence);
#ifdef Debug03_01 //
    for (i = 0; i < label.count(); i++)
    {
        std::cout << "label[" << i << "] = " << label[i] << std::endl;
    }
    for (i = 0; i < sequence.count(); i++)
    {
        std::cout << "sequence[" << i << "] = " << sequence[i] << std::endl;
    }
#endif //  Debug03 //


    length = sequence.count();
    label.value(0);
    for (i = 0; i < length; i++)
    {  
        now = sequence[i];
        here = formula[now].content;
        
        switch (here->Type)
        {
        case _LeafX_:
            New = new ActivationVortex(1);
            label[now] = formula.MoveAppend(New);
            break;
        case _LeafPara_:
        case  _LeafConst_:
            New = new ActivationVortex(0);
            label[now] = formula.MoveAppend(New);
            break;
        case _Operation_:
            label[now] = ForwardDifferential(label, now, here);
            break;
        case _Funct_:
            label[now] = FunctionDifferential(label, now, here);
            break;
        case _Funct2_:
            label[now] = Function2Differential(label, now, here);
            break;
        default:
            break;
        }
    }
#ifdef Debug03_02
    for (i = 0; i < label.count(); i++)
    {
        std::cout << "label[" << i << "] = " << label[i] << std::endl;
    }
#endif
    output = label[sequence[length - 1]];
}
void Activation::differetial(const Activation& source)
{
    copy(source);
    differetial();
}
void Activation::copy(const Activation& source)
{
    size_t i;
    //std::cout << "formula.copy(source.formula);: "  << std::endl;
    formula.copy(source.formula);
    //std::cout << "Parameter.recount(source.Parameter.count()); " << std::endl;
    Parameter.recount(source.Parameter.count());
    for (i = 0; i < source.Parameter.count(); i++)
        Parameter[i] = source.Parameter[i];
   // ParameterCount = source.ParameterCount;
    input = source.input;
    output = source.output;
}

size_t Activation::ForwardDifferential(vector<size_t>& label, size_t now, Activation::ActivationVortex* here)
{
    ActivationVortex* New;
    size_t site;
    size_t left_, right_;
    size_t div_, mid_;
    size_t LeftSrc_, RightSrc_;
    LeftSrc_ = formula[now].In[0];
    RightSrc_ = formula[now].In[1];
    switch (here->Op)
    {
    case _add_:
    case _sub_:
        New = new ActivationVortex(here->Op);
        site = formula.MoveAppend(New);
        formula.append(label[LeftSrc_], label[RightSrc_], site);
        break;
    case _mul_:
        New = new ActivationVortex(_mul_);//f=xy
        left_ = formula.MoveAppend(New);//x
        formula.append(label[LeftSrc_], RightSrc_, left_);

        New = new ActivationVortex(_mul_);
        right_ = formula.MoveAppend(New);
        formula.append(LeftSrc_, label[RightSrc_], right_);

        New = new ActivationVortex(_add_);
        site = formula.MoveAppend(New);
        formula.append(left_, right_, site);
        break;
    case _div_:
        New = new ActivationVortex(_mul_);//f=xy
        left_ = formula.MoveAppend(New);//x^\prime * y
        formula.append(label[LeftSrc_], RightSrc_, left_);//x^\prime

        New = new ActivationVortex(_mul_);
        right_ = formula.MoveAppend(New);//x * y^\prime
        formula.append(LeftSrc_, label[RightSrc_], right_);

        New = new ActivationVortex(_sub_);
        mid_ = formula.MoveAppend(New);
        formula.append(left_, right_, mid_);

        New = new ActivationVortex(_mul_);
        div_ = formula.MoveAppend(New);
        formula.append(RightSrc_, RightSrc_, div_);

        New = new ActivationVortex(_mul_);
        site = formula.MoveAppend(New);
        formula.append(mid_, div_, site);
        break;
    }
    return site;
}
size_t Activation::Function2Differential(vector<size_t>& label, size_t now, ActivationVortex* here)
{
    ActivationVortex* New;
    size_t site;
    size_t origin_, xPrime, const_;
    size_t originR_, originL_;
    size_t Src_, RSrc_;
    Src_ = formula[now].In[0];

    switch (here->Fu2)
    {
    case _pow_:// Rln(L)L^R+L^{prime}L^{R-1}
        RSrc_ = formula[now].In[1];
        New = new ActivationVortex(1);//f=xy
        const_ = formula.MoveAppend(New);//x

        New = new ActivationVortex(_sub_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(RSrc_, const_, xPrime);

        New = new ActivationVortex(_mul_);
        originR_ = formula.MoveAppend(New);
        formula.append(label[Src_], xPrime, originR_);
        //========================================
        New = new ActivationVortex(_ln_);//f=xy
        origin_ = formula.MoveAppend(New);//x
        formula.append(Src_, origin_);

        New = new ActivationVortex(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[RSrc_], origin_, xPrime);

        New = new ActivationVortex(_mul_);
        originL_ = formula.MoveAppend(New);
        formula.append(xPrime, now, originL_);
        //========================================
        New = new ActivationVortex(_add_);//f=xy
        site = formula.MoveAppend(New);//x
        formula.append(originL_, originR_, site);
        break;

    default:
        break;
    }

    return site;
}
size_t Activation::FunctionDifferential(vector<size_t>& label, size_t now, Activation::ActivationVortex* here)
{
    ActivationVortex* New;
    size_t site;
    size_t origin_, xPrime, const_;
    //size_t originR_, originL_;
    size_t Src_;// RSrc_;
    Src_ = formula[now].In[0];
   
    switch (here->Fu)
    {
    case _sin_:
        New = new ActivationVortex(_cos_);
        origin_ = formula.MoveAppend(New);
        formula.append(Src_, origin_);

        New = new ActivationVortex(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], origin_, xPrime);

        site = xPrime;
        break;
    case _cos_:
        New = new ActivationVortex(_sin_);
        origin_ = formula.MoveAppend(New);
        formula.append(Src_, origin_);

        New = new ActivationVortex(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], origin_, xPrime);

        New = new ActivationVortex(_minus_);
        site = formula.MoveAppend(New);
        formula.append(xPrime, site);
        break;
    case _exp_:
        New = new ActivationVortex(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], now, xPrime);

        site = xPrime;
        break;
    case _ln_:
        New = new ActivationVortex(_div_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], Src_, xPrime);

        site = xPrime;
        break;
    case _sqrt_://origin_
        New = new ActivationVortex(2);//f=xy
        const_ = formula.MoveAppend(New);//x

        New = new ActivationVortex(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(const_, now, xPrime);

        New = new ActivationVortex(_div_);//f=xy
        site = formula.MoveAppend(New);//x
        formula.append(label[Src_], xPrime, site);

        break;
    case _minus_:
        New = new ActivationVortex(_minus_);
        site = formula.MoveAppend(New);
        formula.append(label[Src_], site);
        break;
    
    default:
        break;
    }
        
    return site;
}


void Activation::Example01(void)
{
    ActivationVortex* New;
    size_t site;

    Parameter.recount(0);
    formula.clear();

    New = new ActivationVortex();
    New->Type = _LeafX_;
    input = formula.MoveAppend(New);

    New = new ActivationVortex(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input, input, site);

    New = new ActivationVortex(_exp_);
    output = formula.MoveAppend(New);
    formula.append(site, output);
}
void Activation::Demo(PikaString & out)const
{
    vector<size_t> label, stack;
    size_t now, count;
    ActivationVortex* Here;
    
    formula.TraverseInitial(label, stack);
    stack.append(output);
    while (stack.top(now) != 0)
    {
        count = label[now];
        //std::cout << "count: " << count << "now: " << now << std::endl;
        Here = formula[now].content;
        Here->Demo(count, out);
        formula.TraverseNextBack(label, stack);
    }

}
void Activation::Demo(FILE* fp)const
{
    size_t i;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (formula[i].IfValid())
        {
            fprintf(fp, "formula[%zu]: valid.\n", i);
            formula[i].Demo(fp);
            formula[i].content->Demo(fp);
            fprintf(fp, "\n");
        }
        else
        {
            fprintf(fp, "formula[%zu]: invalid.\n", i);
        }
    }
}


bool Activation::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
#ifdef Debug03_03
        std::cout << "round_" << round_ << std::endl;
#endif // Debug03_03

    } while (changed_);
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
bool Activation::Simplify01(void)
{
    size_t i;
    ActivationVortex* here;
    ActivationVortex* left_, *right_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        switch (here->Op)
        {
        case _add_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                formula.LiftRight(i);
                
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                formula.LiftLeft(i);
            }
            break;
        case _sub_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                formula.ArcDelete(formula[i].In[0], i);
                here->Type = _Funct_;
                here->Fu = _minus_;
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                formula.LiftLeft(i);
            }
            break;
        case _mul_:
            if (left_->Type == _LeafConst_)
            {
                if (left_->Fc.isZero())
                {
                    formula.LiftLeft(i);
                    changed_ = true;
                }
                else if (left_->Fc.isOne())
                { 
                    formula.LiftRight(i);
                    changed_ = true;
                }
            }
            else if (right_->Type == _LeafConst_)
            {
                if (right_->Fc.isZero())
                {
                    formula.LiftRight(i);
                    changed_ = true;
                }
                else if (right_->Fc.isOne())
                {
                    formula.LiftLeft(i);
                    changed_ = true;
                }
            }
            break;
        case _div_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                formula.LiftLeft(i);
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isOne())
            {
                formula.LiftLeft(i);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool Activation::Simplify02(void)
{
    size_t i;
    ActivationVortex* here;
    ActivationVortex* left_, * right_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        if (left_->Type == _LeafConst_ && right_->Type == _LeafConst_)
        {
            here->Type = _LeafConst_;
            switch (here->Op)
            {
            case _add_:
                here->Fc = left_->Fc + right_->Fc;
                break;
            case _sub_:
                here->Fc = left_->Fc - right_->Fc;
                break;
            case _mul_:
                here->Fc = left_->Fc * right_->Fc;
                break;
            case _div_:
                here->Fc = left_->Fc / right_->Fc;
                break;
            }
            formula.ArcDelete(formula[i].In[0], i);
            formula.ArcDelete(formula[i].In[1], i);
            changed_ = true;
        }
        
    }
    return changed_;
}
/*

static bool IfInt__(double temp);
static size_t* copymalloc(const size_t* old, size_t length);
static long long int* copymalloc(const long long int* old, size_t length);
static enum Function::type* copymalloc(const enum Function::type* old, size_t length);
static enum Function::operation* copymalloc(const enum Function::operation* old, size_t length);
static long long int pes_int_int(long long int base, long long int exponent);
Function::Function()
{
    initialize();
}
void Function::initialize(void)
{
    size_t i;

    //Unit = new UnitList();
//
    //FormulaCount = 1;
    //Formula = (formula**)malloc(sizeof(formula*) * FormulaCount);
    //Order = (unsigned int*)malloc(sizeof(unsigned int) * FormulaCount);
    ///for (i = 0; i < FormulaCount; i++)
     //   Formula[i] = new formula();
}
Function::~Function()
{
    size_t i;
    for (i = 0; i < FormulaCount; i++)
        delete Formula[i];
    free((void*)Formula);

    //delete Unit;
    //Unit = NULL;
    //free((void*)Alpha);
    //free((void*)Beta);
}


size_t Function::formula::Add(long long int ele)
{
    size_t Target;
    Add();
    Target = Size;
    Size += 1;
    LChild[Target] = -1;
    RChild[Target] = -1;
    //Site[Target] = Unit->SearchAdd(ele);
    Co[Target].Const = ele;
    Type[Target] = LeafConst;
    //Op[Target] = div;
    return Target;
}
size_t Function::formula::Add(double ele)
{
    size_t Target;
    Add();
    Target = Size;
    Size += 1;
    LChild[Target] = -1;
    RChild[Target] = -1;
    //Site[Target] = Unit->SearchAdd(ele);
    Co[Target].Const = ele;
    Type[Target] = LeafConst;
    //Op[Target] = div;
    return Target;
}
size_t Function::formula::Add(long long int LL, long long int RR, Function::operation Opera)
{
    size_t Target;
    Add();
    Target = Size;
    Size += 1;
    LChild[Target] = LL;
    RChild[Target] = RR;
    Co[Target].Op = Opera;
    Type[Target] = Operation;
    return Target;
}
size_t Function::formula::Add(long long int LL, long long int RR, Function::function Func)
{
    size_t Target;
    Add();
    Target = Size;
    Size += 1;
    LChild[Target] = LL;
    RChild[Target] = RR;
    Co[Target].Func = Func;
    Type[Target] = Funct;
    return Target;
}
void Function::formula::Add(void)
{
    if (ContainerSize <= Size)
    {
        ContainerSize = ContainerSize + ContainerSize / 4 + 8;
        Type = (type*)realloc(Type, sizeof(type) * ContainerSize);
        Co = (content*)realloc(Co, sizeof(content) * ContainerSize);
        //Op = (operation*)realloc(Site, sizeof(operation) * ContainerSize);
        //Site = (size_t*)realloc(Site, sizeof(size_t) * ContainerSize);
        LChild = (long long int*)realloc(LChild, sizeof(long long int) * ContainerSize);
        RChild = (long long int*)realloc(RChild, sizeof(long long int) * ContainerSize);
    }
}
static size_t* copymalloc(const size_t* old, size_t length)
{
    size_t* copy;
    size_t i;
    copy = (size_t*)malloc(sizeof(size_t) * length);
    for (i = 0; i < length; i++)
        copy[i] = old[i];
    return copy;
}
static long long int* copymalloc(const long long int* old, size_t length)
{
    long long int* copy;
    size_t i;
    copy = (long long int*)malloc(sizeof(long long int) * length);
    for (i = 0; i < length; i++)
        copy[i] = old[i];
    return copy;
}
static enum Function::type* copymalloc(const enum Function::type* old, size_t length)
{
    enum Function::type* copy;
    size_t i;
    copy = (enum Function::type*)malloc(sizeof(Function::type) * length);
    for (i = 0; i < length; i++)
        copy[i] = old[i];
    return copy;
}
static enum Function::operation* copymalloc(const enum Function::operation* old, size_t length)
{
    enum Function::operation* copy;
    size_t i;
    copy = (enum Function::operation*)malloc(sizeof(Function::operation) * length);
    for (i = 0; i < length; i++)
        copy[i] = old[i];
    return copy;
}
#include <cmath>

long long int pes_int_int(long long int base, long long int exponent)
{
    long long int i, num;
    num = 1;
    for (i = 0; i < exponent; i++) num *= base;
    return num;
}
static bool IfInt__(double temp)
{
    long long int middle;
    middle = (long long int)temp;
    temp -= (double)middle;
    return temp == 0.0;
}
*/


void Activation::PrintForward(VISA1& instru)
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    vector<size_t> output_;
    vector<size_t> FreeReg;
    size_t i, now;
    ActivationVortex* here;
    size_t left_, right_;
    queue.append(output);
    formula.BFTbackward(label, queue);
    formula.TopoSortDFT(sequence);
    formula.SortingShrink(label, sequence);

    label.value(0);
    formula.OutputGive(output_);

#ifdef Debug03_04 
    for (i = 0; i < sequence.count(); i++)
    {
        std::cout << "sequence[" << i << "] = " << sequence[i] << std::endl;
    }
    for (i = 0; i < output_.count(); i++)
    {
        std::cout << "output_[" << i << "] = " << output_[i] << std::endl;
    }
    Demo(stdout);
#endif

    for (i = 0; i < sequence.count(); i++)
    {
        now = sequence[i];
        here = formula[now].content;
        

        switch (here->Type)
        {
        case _LeafX_:
            label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, 0, 0);
            formula.OutputCut(output_, now);
            break;
        case _LeafPara_:
            label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->Fc.IntConst, 0);
            formula.OutputCut(output_, now);
            break;
        case  _LeafConst_:

            label[now] = instru.append(FreeReg, here->Fc);
            formula.OutputCut(output_, now);
            break;
        case _Operation_:
            left_ = formula[now].In[0];
            right_ = formula[now].In[1];
            label[now] = instru.append(VISA1::_op_, (int)here->Op, FreeReg, label[left_], label[right_]);
            formula.OutputCut(output_, now);
            if (output_[left_] == 0)  FreeReg.append(label[left_]);
            if (output_[right_] == 0)  FreeReg.append(label[right_]);
            break;
        case _Funct_:
            left_ = formula[now].In[0];
            label[now] = instru.append(VISA1::_func_, (int)here->Fu, FreeReg, label[left_], 0);
            formula.OutputCut(output_, now);
            if (output_[left_] == 0)  FreeReg.append(label[left_]);
            break;
        default:
            break;
        }
        
       
    }
#ifdef Debug03_04
    std::cout << "end1" << std::endl;
#endif
    instru.append(VISA1::_st_, 0, 0, label[output], 0);
#ifdef Debug03_04
    std::cout << "end" << std::endl;
#endif
}

/*
for output node ,src1=1; src=2 output label.
*/


activation::activation()
{
}
activation ::~activation()
{
}
void activation::PrintForward(VISA1& instru)const
{
    vector<size_t> FreeReg;
    PrintForwardMiniOp(instru, FreeReg);
}
void activation::PrintBackward(VISA1& instru)const
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    vector<size_t> output_;
    vector<size_t> FreeReg;

    size_t i, now, end;
    node* here;
    size_t left_, right_;
    size_t src1, src2;
    
    PrintForwardInitial(label, sequence, queue, output_);
    for (i = 0; i < sequence.count(); i++)
    {
        now = sequence[i];
        here = formula[now].content;
        ForwardMiniOpCore(label, output_, instru, FreeReg, now, here);

        if (here->Output)
        {
            src1 = label[now];
            src2 = instru.append(VISA1::_ld_, (int)_LeafX_, FreeReg, 1, 0);

            FreeReg.append(src2);
            end = instru.append(VISA1::_op_, (int)_mul_, FreeReg, src1, src2);

            instru.append(VISA1::_st_, 0, 0, end, 0);
        }

    }
}
void activation::Differetial(void)
{
    differetial(0, 0, true);
}
void activation::Copy(const activation& source)
{
    this->copy(source);
    input = source.input;
}
bool activation::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();

        changed_ = changed_ || Simplify06();
        changed_ = changed_ || Simplify07();
        changed_ = changed_ || Simplify08();
        changed_ = changed_ || Simplify09();
        changed_ = changed_ || Simplify10();

        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
void activation::Example(size_t No)
{
    size_t i;
    node* New;
    if (No == 1)example01();
    else if (No == 2) example02();
    else if (No == 3) example03();
    else if (No == 4) example04();
    else if (No == 5) example05();
    else if (No == 6) example06();
    else if (No == 7) example07();
    else if (No == 8) example08();
    else if (No == 9) example09();
    else example10();
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        New = formula[i].content;
        if ((New->Type == _LeafX_) && (New->src1 == 0) && (New->src2 == 0)) break;
    }
    input = i;
}
void activation::ParameterBackward(VISA1& instru)
{
    expression Ex;
    vector<size_t> FreeReg;
    Ex.copy(*this);
    Ex.ParameterBackward(0);
    Ex.PrintForwardMiniOp(instru, FreeReg);
}
void activation::Demo(PikaString& out)const
{
    expression::Demo(out, true, 0);
}
void activation::Demo(FILE* fp)const
{
    expression::Demo(fp);
}
void activation::TestBackward(void)
{
    vector<size_t> label, sequence;
    size_t i, length, now, site, Base, temp, In_;
    node* here, * New, * base, * in_;
    backward(false, 0, 0, label, sequence);
    base = new node(0);
    Base = formula.MoveAppend(base);
    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
            if (label[now] != _uintMax_)
            {
                New = new node(_add_);
                site = formula.MoveAppend(New);//x
                formula.append(label[now], Base, site);

                Base = site;
            }
            break;
        case _LeafPara_:
            //output[here->src2] = label[now];
            break;
        }
    }
    output[0] = Base;
    formula[Base].content->Output = true;
}


ActiParaBackward::ActiParaBackward()
{
}
ActiParaBackward::~ActiParaBackward()
{
}
bool ActiParaBackward::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
void ActiParaBackward::Set(const activation& source)
{
    Copy(source);
    ParameterBackward(0);
}
void ActiParaBackward::Copy(const activation& source)
{
    this->copy(source);
    input = source.input;
}
void ActiParaBackward::Copy(const ActiParaBackward& source)
{
    this->copy(source);
    input = source.input;
}
void ActiParaBackward::Demo(FILE* fp)const
{
    expression::Demo(fp);
}

ActiHvForward::ActiHvForward()
{
}
ActiHvForward::~ActiHvForward()
{
}
bool ActiHvForward::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
void ActiHvForward::Set(const activation& source)
{
    vector<size_t> label, sequence;
    size_t i, length, now, site, Base, temp, In_;
    node* here, * New, *base, *in_;
    Copy(source);
    backward(false, ParameterCount, 0, label, sequence);
    length = sequence.count();
    ClearOutput();
    output.recount(1);
    base = new node(0);
    Base = formula.MoveAppend(base);
    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
            break;
        case _LeafPara_:
            //output[here->src2] = label[now];
            if (label[now] != _uintMax_)
            {
                in_ = new node(_LeafX_, InputDim.count() - 1, here->src2);
                In_ = formula.MoveAppend(in_);//x

                New = new node(_mul_);//f=xy
                temp = formula.MoveAppend(New);//x
                formula.append(label[now], In_, temp);

                New = new node(_add_);
                site = formula.MoveAppend(New);//x
                formula.append(temp, Base, site);

                Base = site;

            }
            break;
        }
    }
    output[0] = Base;
    formula[Base].content->Output = true;
}
void ActiHvForward::Copy(const activation& source)
{
    this->copy(source);
    input = source.input;
}
void ActiHvForward::Copy(const ActiHvForward& source)
{
    this->copy(source);
    input = source.input;
}
void ActiHvForward::Demo(FILE* fp)const
{
    expression::Demo(fp);
}


HvForwardFinal::HvForwardFinal()
{
}
HvForwardFinal::~HvForwardFinal()
{
}
bool HvForwardFinal::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
void HvForwardFinal::Set(const ActiParaBackward& source)
{
    vector<size_t> label, sequence;
    size_t i, length, now, site, Base, temp, In_;
    node* here, * New, * base, * in_;
    buffer<size_t> queue;

    Copy(source);
    for (i = 0; i < output.count(); i++)
        if(output[i] != _uintMax_) queue.append(output[i]);
    formula.BFTbackward(label, queue);
    formula.TopologicalSorting(sequence);
    formula.SortingShrink(label, sequence);
    InputDim.append(1);
    InputDim.append(1);
    InputDim.append(ParameterCount);
    length = sequence.count();
    label.value(_uintMax_);
    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
            if (here->src1 == 0 && here->src2 == 0)
                New = new node(_LeafX_, 2, 0);
            else if (here->src1 == 1 && here->src2 == 0)
                New = new node(_LeafX_, 3, 0);
            else throw PikaError("HvForwardFinal::Set", "here->src1", here->src1);
            label[now] = formula.MoveAppend(New);
            break;
        case _LeafPara_:
            New = new node(_LeafX_, 4, here->src2);
            label[now] = formula.MoveAppend(New);
            break;
        case  _LeafConst_:
            New = new node(0);
            label[now] = formula.MoveAppend(New);
            break;
        case _Operation_:
            label[now] = OperationForwardDifferential(label, now, here);
            break;
        case _Funct_:
            label[now] = FunctionForwardDifferential(label, now, here);
            break;
        default:
            break;
        }
    }
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] == _uintMax_) continue;
        formula[output[i]].content->Output = false;
        output[i] = label[output[i]];
        if (output[i] == _uintMax_)
            throw PikaError("HvForwardFinal::Set", "output[i] == _uintMax_", i);
        formula[output[i]].content->Output = true;
    }
}
void HvForwardFinal::Copy(const HvForwardFinal& source)
{
    this->copy(source);
    //input = source.input;
    if(InputDim.count() != 2)
        throw PikaError("HvForwardFinal::Copy", "InputDim.count() != 2", InputDim.count());
    if (InputDim[0] != 1)
        throw PikaError("HvForwardFinal::Copy", "InputDim[0] != 1)", InputDim[0]);
    if (InputDim[1] != 1)
        throw PikaError("HvForwardFinal::Copy", "InputDim[1] != 1", InputDim[1]);
}
void HvForwardFinal::Copy(const ActiParaBackward& source)
{
    this->copy(source);
    //input = source.input;
}
void HvForwardFinal::Demo(FILE* fp)const
{
    expression::Demo(fp);
}






ActivFunc::ActivFunc()
{
    input = 0;
}
ActivFunc::~ActivFunc()
{
    input = 0;
}
void ActivFunc::PrintForward(VISA1& instru)const
{
    vector<size_t> FreeReg;
    PrintForwardMiniOp(instru, FreeReg);
}
void ActivFunc::PrintBackward(VISA1& instru)const
{
    vector<size_t> label;
    vector<Ele*> sequence;
    buffer<Ele*> queue;
    vector<size_t> output_;
    vector<size_t> FreeReg;

    size_t i, now, end;
    Ele* here;
    size_t src1, src2;

    PrintForwardInitial(sequence, queue, output_);
    label.recount(formula.count());
    label.value(0);
    for (i = 0; i < sequence.count(); i++)
    {
        here = sequence[i];
        now = here->site();
        ForwardMiniOpCore(label, output_, instru, FreeReg, now, here);

        if (here->Output)
        {
            src1 = label[now];
            src2 = instru.append(VISA1::_ld_, (int)_LeafX_, FreeReg, 1, 0);

            FreeReg.append(src2);
            end = instru.append(VISA1::_op_, (int)_mul_, FreeReg, src1, src2);

            instru.append(VISA1::_st_, 0, 0, end, 0);
        }

    }
}
void ActivFunc::Differetial(void)
{
    differetial(0, 0, true);
}
void ActivFunc::ParameterBackward(VISA1& instru)
{
    Expres Ex;
    vector<size_t> FreeReg;
    Ex.copy(*this);
    Ex.ParameterBackward(0);
    Ex.PrintForwardMiniOp(instru, FreeReg);
}
void ActivFunc::Copy(const ActivFunc& source)
{
    copy(source);
    input = source.input;
}
bool ActivFunc::Simplify(void)
{
    bool changed_;
    size_t round_;
    round_ = 0;
    hyperlex::BufferChar BC;
    //printf("Simplify(void)\n");
    do
    {
        round_ += 1;
        changed_ = false;
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
        demo(BC, true, 0);
        std::cout << "Simplify04: " << BC.ptr() << std::endl; BC.clear();
        changed_ = changed_ || Simplify06();
        //printf("\tsub 07\n");
        changed_ = changed_ || Simplify07();
        //printf("\tsub 07\n");
        changed_ = changed_ || Simplify08();
        //printf("\tsub 07\n");
        changed_ = changed_ || Simplify09();
        //printf("\tsub 07\n");
        changed_ = changed_ || Simplify10();
        demo(BC, true, 0);
        std::cout << "Simplify10: " << BC.ptr() << std::endl; BC.clear();
        changed_ = changed_ || Simplify02();
        changed_ = changed_ || Simplify01();
        changed_ = changed_ || Simplify03();
        changed_ = changed_ || Simplify04();
        demo(BC, true, 0);
        std::cout << "Simplify04 2: " << BC.ptr() << std::endl; BC.clear();
    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    //printf("End\n");
    formula.compress();
    //printf("End2\n");
    return round_ > 1;
}

int ActivFunc::construct(FILE* fp)
{
    hyperlex::BufferChar BC;
    BC << fp;
    return construct(BC.ptr());
}
void ActivFunc::Demo(hyperlex::BufferChar& out)const
{
    Expres::demo(out, true, 0);
}
void ActivFunc::Demo(FILE* fp)const
{
    Expres::demo(fp);
}
void ActivFunc::TestBackward(void)
{
    vector<Ele*> label, sequence;
    size_t i, length, now, Base, temp, In_;
    Ele* here, * New, * base, * in_, *site;
    backward(false, 0, 0, label, sequence);
    base = new Ele((long int)0);
    formula.append(base);
    length = formula.count();
    for (i = 0; i < length; i++)
    {
        here = sequence[i];
        now = here->site();

        switch (here->Type)
        {
        case _LeafX_:
            if (label[now] != NULL)
            {
                New = new Ele(_add_);
                site = NewNode(label[now], base, _add_);

                base = site;
            }
            break;
        case _LeafPara_:
            //output[here->src2] = label[now];
            break;
        }
    }
    output[0] = base;
    formula[base->site()]->Output = true;
}


