#include"../header/Pikachu.h"
using namespace Pikachu;
#include<cmath>
#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif


expression::expression()
{
    //ParameterCount = 0;
    //InputGroupCount = 0;
    ParameterCount = 0;
}
expression::~expression()
{

}
expression::node::node(void)
{
    Code = 0;
    src1 = 0;
    src2 = 0;
    Output = false;
}
expression::node::node(long long int ele)
{
    Type = _LeafConst_;
    Fc.SetValue(ele);
    src1 = 0;
    src2 = 0;
    Output = false;
}
expression::node::node(operation opera_)
{
    Type = _Operation_;
    Code = (int)opera_;
    src1 = 0;
    src2 = 0;
    Output = false;
}
expression::node::node(function func_)
{
    Type = _Funct_;
    Code = (int)func_;
    src1 = 0;
    src2 = 0;
    Output = false;
}
expression::node::node(function2 func_)
{
    Type = _Funct2_;
    Code = (int)func_;
    src1 = 0;
    src2 = 0;
    Output = false;
}

expression::node::node(type T, size_t S1, size_t S2)
{
    Type = T;
    Code = 0;
    src1 = S1;
    src2 = S2;
    Output = false;
}
expression::node* expression::node::copy(void)
{
    node* New;
    New = new node();
    New->Type = Type;
    New->Code = Code;
    New->Output = Output;
    New->src1 = src1;
    New->src2 = src2;
    New->Fc.SetValue(Fc);
    return New;
}
void expression::node::Demo(size_t label, PikaString& output, bool single) const
{
    switch (Type)
    {
    case Pikachu::_LeafX_:
        if (single)
        {
            output += "x";
        }
        else
        {
            output += "x[";
            output += (long long int)(src1);
            output += ", ";
            output += (long long int)(src2);
            output += "]";
        }
        break;
    case Pikachu::_LeafConst_:
        Fc.print(output);
        break;
    case Pikachu::_LeafPara_:
        if (single)
        {
            output += "w_";
            output += (long long int)(src2);
        }
        else
        {
            output += "w[";
            output += (long long int)(src1);
            output += ", ";
            output += (long long int)(src2);
            output += "]";
        }

        break;
    case Pikachu::_Funct_:
        if (label == 1)
        {
            if (!Output) output += ")";
        }
        else
        {
            output += FunctionName((function)Code);
            if (!Output) output += "(";
        }
        break;
    case Pikachu::_Operation_:
        if (label == 0) { if (!Output) output += "("; }
        else if (label == 2) { if (!Output) output += ")"; }
        else  output += OperationName((operation)Code);
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
            output += Function2Name((function2)Code);
            output += "(";
        }
        break;
    }
}
void expression::node::Demo(FILE* fp) const
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
        output += FunctionName((function)Code);
        break;
    case Pikachu::_Operation_:
        output += OperationName((operation)Code);
        break;
    case Pikachu::_Funct2_:
        output += Function2Name((function2)Code);
        break;
    }
    fprintf(fp, "%s.\n", output.array());
}



void expression::copy(const expression& source)
{
    size_t i;
    formula.copy(source.formula);
    //std::cout << "Parameter.recount(source.Parameter.count()); " << std::endl;
    output.recount(source.output.count());
    for (i = 0; i < source.output.count(); i++)
        output[i] = source.output[i];
    InputDim.recount(source.InputDim.count());
    for (i = 0; i < source.InputDim.count(); i++)
        InputDim[i] = source.InputDim[i];
    //output = source.output;
    //InputGroupCount = source.InputGroupCount;
    ParameterCount = source.ParameterCount;
}

void expression::Example(size_t No)
{
    if (No == 1)example01();
    else if (No == 2)example02();
    else if (No == 3)example03();
    else if (No == 4)example04();
    else if (No == 5)example05();
    else if (No == 6)example06();
    else if (No == 7)example07();
    else if (No == 8)example08();
    else if (No == 9)example09();
    else example10();
}
void expression::example01(void)
{
    node* New;
    size_t site;
    size_t input_;

    formula.clear();
    output.clear();

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_exp_);
    output.append(formula.MoveAppend(New));
    formula.append(site, output[0]);
    formula[output[0]].content->Output = true;

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example02(void)
{
    node* New;
    size_t site, temp;
    size_t input_;

    formula.clear();
    output.clear();

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_minus_);
    temp = formula.MoveAppend(New);
    formula.append(site, temp);

    New = new node(_exp_);
    output.append(formula.MoveAppend(New));
    formula.append(temp, output[0]);
    formula[output[0]].content->Output = true;

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example03(void)
{
    node* New;
    size_t site, temp;
    size_t input_;
    size_t i;
    size_t X_[4], W_[5], _M_[5];

    formula.clear();
    output.clear();

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 5;


    New = new node();
    New->Type = _LeafX_;
    X_[1] = formula.MoveAppend(New);
    X_[0] = X_[1];
    for (i = 2; i < 4; i++)
    {
        New = new node(_mul_);
        X_[i] = formula.MoveAppend(New);
        formula.append(X_[i - 1], X_[i - 2], X_[i]);
    }

    for (i = 0; i < 5; i++)
    {
        New = new node();
        New->Type = _LeafPara_;
        New->src2 = i;
        W_[i] = formula.MoveAppend(New);
    }


    _M_[0] = W_[0];
    for (i = 1; i < 4; i++)
    {
        New = new node(_mul_);
        _M_[i] = formula.MoveAppend(New);
        formula.append(W_[i], X_[i], _M_[i]);
    }
    for (i = 1; i < 4; i++)
    {
        New = new node(_add_);
        temp = formula.MoveAppend(New);
        formula.append(_M_[i - 1], _M_[i], temp);
        _M_[i] = temp;
    }

    New = new node(_mul_);
    temp = formula.MoveAppend(New);
    formula.append(W_[5 - 1], W_[5 - 1], temp);
    W_[5 - 1] = temp;

    New = new node(_mul_);
    _M_[4] = formula.MoveAppend(New);
    formula.append(X_[2], W_[5 - 1], _M_[4]);

    New = new node(_minus_);
    temp = formula.MoveAppend(New);
    formula.append(_M_[4], temp);
    _M_[4] = temp;

    New = new node(_exp_);
    temp = formula.MoveAppend(New);
    formula.append(_M_[4], temp);
    _M_[4] = temp;


    New = new node(_mul_);
    output.append(formula.MoveAppend(New));
    formula.append(_M_[3], _M_[4], output[0]);
    formula[output[0]].content->Output = true;


}
void expression::example04(void)
{
    node* New;
    size_t temp;
    size_t input_, two_, exp___, one_;
    size_t up__, down__;

    formula.clear();
    output.clear();

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);

    New = new node(2);
    two_ = formula.MoveAppend(New);

    New = new node(_mul_);
    temp = formula.MoveAppend(New);
    formula.append(input_, two_, temp);

    New = new node(_exp_);
    exp___ = formula.MoveAppend(New);
    formula.append(temp, exp___);

    New = new node(1);
    one_ = formula.MoveAppend(New);

    New = new node(_sub_);
    up__ = formula.MoveAppend(New);
    formula.append(exp___, one_, up__);

    New = new node(_add_);
    down__ = formula.MoveAppend(New);
    formula.append(exp___, one_, down__);

    New = new node(_div_);
    temp = formula.MoveAppend(New);
    formula.append(up__, down__, temp);

    output.append(temp);
    formula[temp].content->Output = true;

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example05(void)
{
    node* New;
    size_t site;
    size_t input_;

    formula.clear();
    output.clear();

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_minus_);
    output.append(formula.MoveAppend(New));
    formula.append(site, output[0]);
    formula[output[0]].content->Output = true;

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example06(void)
{

    node* New;
    size_t temp;
    size_t input_, two_, exp___, one_;
    size_t up__, down__;

    formula.clear();
    output.clear();
    InputDim.recount(1);


    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);
    InputDim[0] = input_;

    New = new node(_mul_);
    temp = formula.MoveAppend(New);
    formula.append(input_, input_, temp);

    New = new node(1);
    one_ = formula.MoveAppend(New);

    New = new node(_add_);
    up__ = formula.MoveAppend(New);
    formula.append(temp, one_, up__);

    New = new node(_sqrt_);
    down__ = formula.MoveAppend(New);
    formula.append(up__, down__);

    New = new node(_div_);
    temp = formula.MoveAppend(New);
    formula.append(input_, down__, temp);

    output.append(temp);
    formula[temp].content->Output = true;

    
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example07(void)
{
    node* New;
    size_t site;
    size_t input_;
    size_t temp;

    formula.clear();
    output.clear();

    InputDim.recount(1);
    
    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);
    InputDim[0] = input_;

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_minus_);
    temp = formula.MoveAppend(New);
    formula.append(site, temp);

    New = new node(_sin_);
    site = formula.MoveAppend(New);
    formula.append(temp, site);

    output.append(site);
    formula[site].content->Output = true;

    
    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example08(void)
{
    node* New;
    size_t site;
    size_t input_;
    size_t temp;

    formula.clear();
    output.clear();

    InputDim.recount(1);

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);
    InputDim[0] = input_;

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_ln_);
    temp = formula.MoveAppend(New);
    formula.append(site, temp);

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(temp, input_, site);

    output.append(site);
    formula[site].content->Output = true;


    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example09(void)
{
    node* New;
    size_t site;
    size_t input_;
    size_t temp;

    formula.clear();
    output.clear();

    InputDim.recount(1);

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);
    InputDim[0] = input_;

    New = new node(8);
    site = formula.MoveAppend(New);
   
    New = new node(_pow_);
    temp = formula.MoveAppend(New);
    formula.append(input_, site, temp);

    output.append(temp);
    formula[temp].content->Output = true;


    //InputGroupCount = 1;
    ParameterCount = 0;
}
void expression::example10(void)
{
    node* New;
    size_t site;
    size_t input_;
    size_t temp;

    formula.clear();
    output.clear();

    InputDim.recount(1);

    New = new node();
    New->Type = _LeafX_;
    input_ = formula.MoveAppend(New);
    InputDim[0] = input_;

    New = new node(_mul_);
    site = formula.MoveAppend(New);
    formula.append(input_, input_, site);

    New = new node(_pow_);
    temp = formula.MoveAppend(New);
    formula.append(site, input_, temp);

    output.append(temp);
    formula[temp].content->Output = true;
}

size_t expression::OutputAmount(void)const
{
    return output.count();
}
size_t expression::ParameterAmount(void)const
{
    return ParameterCount;
}
size_t expression::InputGroup(void)const
{
    return InputDim.count();
}

void expression::Demo(PikaString& out, bool single, size_t No)const
{
    vector<size_t> label, stack;
    size_t now, count;
    node* Here;
#ifdef Debug03_05
    std::cout << " formula.TraverseInitial(label, stack);" << std::endl;
#endif // Debug03_05

    formula.TraverseInitial(label, stack);
#ifdef Debug03_05
    std::cout << " stack.append(output);" << std::endl;
#endif // Debug03_05
    stack.append(output[No]);
#ifdef Debug03_05
    std::cout << " stack.append(output);" << std::endl;
#endif // Debug03_05
    while (stack.top(now) != 0)
    {
        count = label[now];
        Here = formula[now].content;
#ifdef Debug03_05
        std::cout << "now: " << now << ", count: " << count << std::endl;
#endif
        Here->Demo(count, out, single);
#ifdef Debug03_05
        std::cout << "Here->Demo(count, out);" << Here->Type << std::endl;
#endif
        formula.TraverseNextBack(label, stack);
    }

}
void expression::Demo(FILE* fp)const
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

void expression::PrintForwardInitial(vector<size_t>& label, vector<size_t>& sequence, buffer<size_t>& queue, vector<size_t>& output_)const
{
    size_t i;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != _uintMax_) queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    formula.TopoSortDFT(sequence);
    formula.SortingShrink(label, sequence);

    label.value(0);
    formula.OutputGive(output_);
}
void expression::ForwardMiniOpCore(vector<size_t>& label, vector<size_t>& output_, VISA1& instru, vector<size_t>& FreeReg, size_t now, node* here)const
{
    size_t left_, right_;
    size_t src1, src2;
    switch (here->Type)
    {
    case _LeafX_:
        label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
        formula.OutputCut(output_, now);
        break;
    case _LeafPara_:
        label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
        formula.OutputCut(output_, now);
        break;
    case  _LeafConst_:
        label[now] = instru.append(FreeReg, here->Fc);
        formula.OutputCut(output_, now);
        break;
    case _Operation_:
        left_ = formula[now].In[0];
        right_ = formula[now].In[1];
        src1 = label[left_];
        src2 = label[right_];
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
        label[now] = instru.append(VISA1::_op_, here->Code, FreeReg, src1, src2);
        break;
    case _Funct_:
        left_ = formula[now].In[0];
        src1 = label[left_];
        src2 = 0;
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        label[now] = instru.append(VISA1::_func_, here->Code, FreeReg, src1, src2);
        break;
    case _Funct2_:
        left_ = formula[now].In[0];
        src1 = label[left_];
        right_ = formula[now].In[1];
        src2 = label[right_];
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
        label[now] = instru.append(VISA1::_func2_, here->Code, FreeReg, src1, src2);
        break;
    default:
        break;
    }
}

void expression::ClearOutput(void)
{
    size_t i;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != _uintMax_)
        {
            formula[output[i]].content->Output = false;
        }
    }
}

void expression::PrintForwardMiniOp(VISA1& instru, vector<size_t>& FreeReg) const
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    vector<size_t> output_;

    size_t i, now, j;
    node* here;
    //size_t left_, right_;
    //size_t src1, src2;

    PrintForwardInitial(label, sequence, queue, output_);
    /*
    for (i = 0; i < output.count(); i++)
    {
        queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    formula.TopoSortDFT(sequence);
    formula.SortingShrink(label, sequence);

    label.value(0);
    formula.OutputGive(output_);
    */
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
        ForwardMiniOpCore(label, output_, instru, FreeReg, now, here);
        /*switch (here->Type)
        {
        case _LeafX_:
            label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
            formula.OutputCut(output_, now);
            break;
        case _LeafPara_:
            label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
            formula.OutputCut(output_, now);
            break;
        case  _LeafConst_:
            label[now] = instru.append(FreeReg, here->Fc);
            formula.OutputCut(output_, now);
            break;
        case _Operation_:
            left_ = formula[now].In[0];
            right_ = formula[now].In[1];
            src1 = label[left_];
            src2 = label[right_];
            formula.OutputCut(output_, now);
            if (output_[left_] == 0)  FreeReg.append(label[left_]);
            if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_op_, here->Code, FreeReg, src1, src2);
            break;
        case _Funct_:
            left_ = formula[now].In[0];
            src1 = label[left_];
            if ((function)here->Code == _pow_)
            {
                right_ = formula[now].In[1];
                src2 = label[right_];
            }
            else src2 = 0;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0)  FreeReg.append(label[left_]);
            if ((function)here->Code == _pow_)
                if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_func_, here->Code, FreeReg, src1, src2);
            break;
        default:
            break;
        }*/
        if (here->Output)
        {
#ifdef Debug03_06
            std::cout << "PrintForwardMiniOp, now: " << now << std::endl;
#endif
            for (j = 0; j < output.count(); j++)
            {
#ifdef Debug03_06
                std::cout << "output[" << j << "] = " << output[j] << std::endl;
#endif
                if (output[j] == now)
                {
                    instru.append(VISA1::_st_, 0, j, label[now], 0);
                }
            }
            if (output_[now] == 0) FreeReg.append(label[now]);
        }

    }
#ifdef Debug03_04
    std::cout << "end1" << std::endl;
#endif
    //
#ifdef Debug03_04
    std::cout << "end" << std::endl;
#endif
}
void expression::PrintForwardMiniReg(VISA1& instru, vector<size_t>& FreeReg)const
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    vector<size_t> output_;
    //vector<size_t> FreeReg;
    size_t i, now, j;
    node* here;
    size_t left_, right_;
    node* L_, * R_;
    size_t src1, src2;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != _uintMax_) queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    formula.TopoSortDFT(sequence);
    formula.SortingShrink(label, sequence);

    label.value(0);
    formula.OutputGive(output_);

    for (i = 0; i < sequence.count(); i++)
    {
        now = sequence[i];
        here = formula[now].content;
        //label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
            //formula.OutputCut(output_, now);
           // break;
        //label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, 0);
            //formula.OutputCut(output_, now);
            //break;
        //label[now] = instru.append(FreeReg, here->Fc);
            //formula.OutputCut(output_, now);
        switch (here->Type)
        {
        case _LeafX_:
        case _LeafPara_:
        case _LeafConst_:
            break;
        case _Operation_:
        {

            left_ = formula[now].In[0];
            right_ = formula[now].In[1];
            L_ = formula[left_].content;
            R_ = formula[right_].content;
            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            if (left_ != right_)
                src2 = instru.append(R_->Type, FreeReg, R_->src1, R_->src2, R_->Fc, label[right_]);
            else src2 = src1;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(src1);
            if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1)  FreeReg.append(src2);
            label[now] = instru.append(VISA1::_op_, here->Code, FreeReg, src1, src2);
            break;
        }
        case _Funct_:
            left_ = formula[now].In[0];
            L_ = formula[left_].content;
            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            src2 = 0;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(label[left_]);
            //if ((function)here->Code == _pow_)
            //    if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1) FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_func_, here->Code, FreeReg, src1, src2);
            break;
        case _Funct2_:
            left_ = formula[now].In[0];
            L_ = formula[left_].content;
            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            right_ = formula[now].In[1];
            R_ = formula[right_].content;
            if (left_ != right_)
                src2 = instru.append(R_->Type, FreeReg, R_->src1, R_->src2, R_->Fc, label[right_]);
            else src2 = src1;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(label[left_]);
            if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1) FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_func2_, here->Code, FreeReg, src1, src2);
            break;
        default:
            break;
        }
        if (here->Output)
        {
            for (j = 0; j < output.count(); j++)
            {
                if (output[j] == now)
                {
                    instru.append(VISA1::_st_, 0, j, label[now], 0);
                }
            }
            if (output_[now] == 0) FreeReg.append(label[now]);
        }

    }
#ifdef Debug03_04
    std::cout << "end1" << std::endl;
#endif
    //instru.append(VISA1::_st_, 0, 0, label[output], 0);
#ifdef Debug03_04
    std::cout << "end" << std::endl;
#endif
}

void expression::ParameterBackward(size_t No)
{
    vector<size_t> label, sequence;
    size_t i, length, now, site;
    node* here, * New;
    backward(true, output.count(), No, label, sequence);
    length = sequence.count();
    ClearOutput();
    output.recount(ParameterCount);
    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
            break;
        case _LeafPara_:
            output[here->src2] = label[now];
            if(label[now] != _uintMax_ )formula[label[now]].content->Output = true;
            break;
        }
    }
}
void expression::differetial(size_t X1, size_t X2, bool Input)
{
    vector<size_t> label, sequence;
    buffer<size_t> queue;
    size_t i, length, now, site;
    node* here, * New;

    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != _uintMax_) queue.append(output[i]);
    }

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
    label.value(_uintMax_);
    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
            New = new node(here->src1 == X1 && here->src2 == X2 && Input);
            label[now] = formula.MoveAppend(New);
            break;
        case _LeafPara_:
            New = new node(here->src1 == X1 && here->src2 == X2 && !Input);
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
        case _Funct2_:
            label[now] = Function2ForwardDifferential(label, now, here);
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
    for (i = 0; i < output.count(); i++)
    {
        formula[output[i]].content->Output = false;
        output[i] = label[output[i]];
        formula[output[i]].content->Output = true;
    }
    //output = label[sequence[length - 1]];
}
void expression::backward(bool ExternOutput, size_t NewInputDim, size_t No, vector<size_t>& label, vector<size_t>& sequence)
{
    //vector<size_t> label, sequence;
    buffer<size_t> queue;
    size_t i, length, now, site;
    node* here, * New;

    queue.append(output[No]);
    formula.BFTbackward(label, queue);
    //formula.path(label, queue, input, output);
    formula.TopologicalSortingBack(sequence);

    

    length = sequence.count();
    label.value(_uintMax_);

    if (ExternOutput)
    {
        New = new node();
        New->Type = _LeafX_;
        New->src1 = InputDim.count();
        New->src2 = No;
    }
    else
    {
        New = new node(1);
    }
    if(NewInputDim != 0) InputDim.append(NewInputDim);
    label[output[No]] = formula.MoveAppend(New);

   
    //InputGroupCount += 1;

    for (i = 0; i < length; i++)
    {
        now = sequence[i];
        here = formula[now].content;

        switch (here->Type)
        {
        case _LeafX_:
        case _LeafPara_:
        case  _LeafConst_:
            break;
        case _Operation_:
            OperationBackwardDifferential(label, now, here);
            break;
        case _Funct_:
            FunctionBackwardDifferential(label, now, here);
            break;
        case _Funct2_:
            Function2BackwardDifferential(label, now, here);
            break;
        default:
            break;
        }
    }
   
    // output = label[sequence[length - 1]];
}

void expression::elementwise(const expression& source, operation OP)
{
    size_t i, now;
    vector<size_t> label;
    node * New;
    if (output.count() != source.output.count())
        throw PikaError("expression::elementwise", "output.count() != source.output.count()", output.count());
    if (InputDim.count() != source.InputDim.count())
        throw PikaError("expression::elementwise", "InputDim.count() != source.InputDim.count()", InputDim.count());
    for (i = 0; i < source.InputDim.count(); i++)
    {
        if (InputDim[i] != source.InputDim[i])
            throw PikaError("expression::elementwise", "InputDim[i] != source.InputDim[i]", i);
    }
    formula.append(source.formula, label);
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] == _uintMax_ || source.output[i] == _uintMax_) continue;
        New = new node(OP);
        now = formula.MoveAppend(New);
        formula.append(output[i], label[source.output[i]], now);
        output[i] = now;
    }
}
void expression::InputExpand(size_t NewDim)
{
    InputDim.append(NewDim);
}




size_t expression::OperationForwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site;
    size_t left_, right_;
    size_t div_, mid_;
    size_t LeftSrc_, RightSrc_;
    LeftSrc_ = formula[now].In[0];
    RightSrc_ = formula[now].In[1];
    switch ((operation)here->Code)
    {
    case _add_:
    case _sub_:
        New = new node((operation)here->Code);
        site = formula.MoveAppend(New);
        formula.append(label[LeftSrc_], label[RightSrc_], site);
        break;
    case _mul_:
        New = new node(_mul_);//f=xy
        left_ = formula.MoveAppend(New);//x
        formula.append(label[LeftSrc_], RightSrc_, left_);

        New = new node(_mul_);
        right_ = formula.MoveAppend(New);
        formula.append(LeftSrc_, label[RightSrc_], right_);

        New = new node(_add_);
        site = formula.MoveAppend(New);
        formula.append(left_, right_, site);
        break;
    case _div_:
        New = new node(_mul_);//f=xy
        left_ = formula.MoveAppend(New);//x^\prime * y
        formula.append(label[LeftSrc_], RightSrc_, left_);//x^\prime

        New = new node(_mul_);
        right_ = formula.MoveAppend(New);//x * y^\prime
        formula.append(LeftSrc_, label[RightSrc_], right_);

        New = new node(_sub_);
        mid_ = formula.MoveAppend(New);
        formula.append(left_, right_, mid_);

        New = new node(_mul_);
        div_ = formula.MoveAppend(New);
        formula.append(RightSrc_, RightSrc_, div_);

        New = new node(_div_);
        site = formula.MoveAppend(New);
        formula.append(mid_, div_, site);
        break;
    }
    return site;
}
size_t expression::FunctionForwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site;
    size_t origin_, xPrime, const_;
    size_t originR_, originL_;
    size_t Src_, RSrc_;
    size_t temp1, temp2;
    Src_ = formula[now].In[0];

    switch ((function)here->Code)
    {
    case _sin_:
        New = new node(_cos_);
        origin_ = formula.MoveAppend(New);
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], origin_, xPrime);

        site = xPrime;
        break;
    case _cos_:
        New = new node(_sin_);
        origin_ = formula.MoveAppend(New);
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], origin_, xPrime);

        New = new node(_minus_);
        site = formula.MoveAppend(New);
        formula.append(xPrime, site);
        break;
    case _exp_:
        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], now, xPrime);

        site = xPrime;
        break;
    /*case _pow_:// R^{prime}ln(L)L^R+L^{prime}R L^{R-1}
        RSrc_ = formula[now].In[1];//1
        New = new node(1);
        const_ = formula.MoveAppend(New);

        New = new node(_sub_);//R-1
        xPrime = formula.MoveAppend(New);//x
        formula.append(RSrc_, const_, xPrime);

        New = new node(_pow_);//L^{R-1}
        temp1 = formula.MoveAppend(New);//x
        formula.append(Src_, xPrime, temp1);

        New = new node(_mul_);//R L^{R-1}
        temp2 = formula.MoveAppend(New);//x
        formula.append(RSrc_, temp1, temp2);

        New = new node(_mul_);//L^{prime} R L^{R-1}
        originR_ = formula.MoveAppend(New);
        formula.append(label[Src_], temp2, originR_);
        //========================================
        New = new node(_ln_);//f=xy
        origin_ = formula.MoveAppend(New);//x
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[RSrc_], origin_, xPrime);

        New = new node(_mul_);
        originL_ = formula.MoveAppend(New);
        formula.append(xPrime, now, originL_);
        //========================================
        New = new node(_add_);//f=xy
        site = formula.MoveAppend(New);//x
        formula.append(originL_, originR_, site);
        break;*/
    case _ln_:
        New = new node(_div_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[Src_], Src_, xPrime);

        site = xPrime;
        break;
    case _sqrt_://origin_
        New = new node(2);//f=xy
        const_ = formula.MoveAppend(New);//x

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(const_, now, xPrime);

        New = new node(_div_);//f=xy
        site = formula.MoveAppend(New);//x
        formula.append(label[Src_], xPrime, site);

        break;
    case _minus_:
        New = new node(_minus_);
        site = formula.MoveAppend(New);
        formula.append(label[Src_], site);
        break;

    default:
        break;
    }

    return site;
}
size_t expression::Function2ForwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site;
    size_t origin_, xPrime, const_;
    size_t originR_, originL_;
    size_t Src_, RSrc_;
    size_t temp1, temp2;
    Src_ = formula[now].In[0];

    switch ((function2)here->Code)
    {
    case _pow_:// R^{prime}ln(L)L^R+L^{prime}R L^{R-1}
        RSrc_ = formula[now].In[1];//1
        New = new node(1);
        const_ = formula.MoveAppend(New);

        New = new node(_sub_);//R-1
        xPrime = formula.MoveAppend(New);//x
        formula.append(RSrc_, const_, xPrime);

        New = new node(_pow_);//L^{R-1}
        temp1 = formula.MoveAppend(New);//x
        formula.append(Src_, xPrime, temp1);

        New = new node(_mul_);//R L^{R-1}
        temp2 = formula.MoveAppend(New);//x
        formula.append(RSrc_, temp1, temp2);

        New = new node(_mul_);//L^{prime} R L^{R-1}
        originR_ = formula.MoveAppend(New);
        formula.append(label[Src_], temp2, originR_);
        //========================================
        New = new node(_ln_);//f=xy
        origin_ = formula.MoveAppend(New);//x
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(label[RSrc_], origin_, xPrime);

        New = new node(_mul_);
        originL_ = formula.MoveAppend(New);
        formula.append(xPrime, now, originL_);
        //========================================
        New = new node(_add_);//f=xy
        site = formula.MoveAppend(New);//x
        formula.append(originL_, originR_, site);
        break;
    }

    return site;
}

void expression::BackwardAccumulate(vector<size_t>& label, size_t target, size_t source)
{
    size_t temp;
    node* New;
    if (label[target] == _uintMax_) label[target] = source;
    else
    {
        New = new node(_add_);
        temp = formula.MoveAppend(New);
        formula.append(label[target], source, temp);
        label[target] = temp;
    }
}
void expression::OperationBackwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site, temp;
    size_t left_, right_;
    size_t div_, mid_;
    size_t LeftSrc_, RightSrc_;
    LeftSrc_ = formula[now].In[0];
    RightSrc_ = formula[now].In[1];
    switch ((operation)here->Code)
    {
    case _add_:
        BackwardAccumulate(label, LeftSrc_, label[now]);
        BackwardAccumulate(label, RightSrc_, label[now]);
        break;
    case _sub_:
        BackwardAccumulate(label, LeftSrc_, label[now]);
        New = new node(_minus_);
        site = formula.MoveAppend(New);
        formula.append(label[now], site);
        BackwardAccumulate(label, RightSrc_, site);
        break;
    case _mul_:
        New = new node(_mul_);//f=xy
        left_ = formula.MoveAppend(New);//x
        formula.append(label[now], RightSrc_, left_);
        BackwardAccumulate(label, LeftSrc_, left_);

        New = new node(_mul_);
        right_ = formula.MoveAppend(New);
        formula.append(LeftSrc_, label[now], right_);
        BackwardAccumulate(label, RightSrc_, right_);
        break;
    case _div_:
        New = new node(_div_);//f=xy
        left_ = formula.MoveAppend(New);//x
        formula.append(label[now], RightSrc_, left_);
        BackwardAccumulate(label, LeftSrc_, left_);

        New = new node(_mul_);
        right_ = formula.MoveAppend(New);
        formula.append(RightSrc_, RightSrc_, right_);

        New = new node(_minus_);
        div_ = formula.MoveAppend(New);
        formula.append(right_, div_);

        New = new node(_mul_);
        mid_ = formula.MoveAppend(New);//x * y^\prime
        formula.append(label[now], LeftSrc_, mid_);

        New = new node(_div_);
        site = formula.MoveAppend(New);
        formula.append(mid_, div_, site);
        BackwardAccumulate(label, RightSrc_, site);
        break;
    }
    return;
}
void expression::FunctionBackwardAccumulate(vector<size_t>& label, size_t now, size_t source, int Code)
{
    node* New;
    size_t xPrime, temp;
    size_t target;
    target = formula[now].In[0];

    New = new node((operation)Code);
    xPrime = formula.MoveAppend(New);
    formula.append(label[now], source, xPrime);


    if (label[target] == _uintMax_) label[target] = xPrime;
    else
    {
        New = new node(_add_);
        temp = formula.MoveAppend(New);
        formula.append(label[target], xPrime, temp);
        label[target] = temp;
    }

}
void expression::FunctionBackwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site;
    size_t origin_, xPrime, const_;
    size_t originR_, originL_;
    size_t Src_;// RSrc_;
    //size_t temp1, temp2;
    Src_ = formula[now].In[0];

    switch ((function)here->Code)
    {
    case _sin_:
        New = new node(_cos_);
        origin_ = formula.MoveAppend(New);
        formula.append(Src_, origin_);
        FunctionBackwardAccumulate(label, now, origin_, _mul_);
        break;
    case _cos_:
        New = new node(_sin_);
        site = formula.MoveAppend(New);
        formula.append(Src_, site);

        New = new node(_minus_);
        xPrime = formula.MoveAppend(New);
        formula.append(site, xPrime);//??????
        FunctionBackwardAccumulate(label, now, xPrime, _mul_);
        break;
    case _exp_:
        FunctionBackwardAccumulate(label, now, now, _mul_);
        break;
    /*case _pow_:// R^{prime}ln(L)L^R+L^{prime}L^{R-1}
        RSrc_ = formula[now].In[1];//1
        New = new node(1);
        const_ = formula.MoveAppend(New);

        New = new node(_sub_);//R-1
        xPrime = formula.MoveAppend(New);//x
        formula.append(RSrc_, const_, xPrime);

        New = new node(_pow_);//L^{R-1}
        temp1 = formula.MoveAppend(New);//x
        formula.append(Src_, xPrime, temp1);

        New = new node(_mul_);//R L^{R-1}
        temp2 = formula.MoveAppend(New);//x
        formula.append(RSrc_, temp1, temp2);

        FunctionBackwardAccumulate(label, now, temp2, _mul_);
        //========================================
        New = new node(_ln_);//f=xy
        origin_ = formula.MoveAppend(New);//x
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(now, origin_, xPrime);

        New = new node(_mul_);
        originL_ = formula.MoveAppend(New);
        formula.append(xPrime, label[now], originL_);
        //========================================
        BackwardAccumulate(label, RSrc_, originL_);
        break;*/
    case _ln_:// \frac{\partial O}{\partial f}  /x
        FunctionBackwardAccumulate(label, now, Src_, _div_);
        break;
    case _sqrt_://origin_
        New = new node(2);//f=xy
        const_ = formula.MoveAppend(New);//x

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(const_, now, xPrime);

        FunctionBackwardAccumulate(label, now, xPrime, _div_);
        break;
    case _minus_:
        New = new node(_minus_);
        site = formula.MoveAppend(New);
        formula.append(label[now], site);
        BackwardAccumulate(label, Src_, site);
        break;
    default:
        break;
    }
    return;
}
void expression::Function2BackwardDifferential(vector<size_t>& label, size_t now, node* here)
{
    node* New;
    size_t site;
    size_t origin_, xPrime, const_;
    size_t originR_, originL_;
    size_t Src_, RSrc_;
    size_t temp1, temp2;
    Src_ = formula[now].In[0];

    switch ((function)here->Code)
    {
    case _pow_:// R^{prime}ln(L)L^R+L^{prime}L^{R-1}
        RSrc_ = formula[now].In[1];//1
        New = new node(1);
        const_ = formula.MoveAppend(New);

        New = new node(_sub_);//R-1
        xPrime = formula.MoveAppend(New);//x
        formula.append(RSrc_, const_, xPrime);

        New = new node(_pow_);//L^{R-1}
        temp1 = formula.MoveAppend(New);//x
        formula.append(Src_, xPrime, temp1);

        New = new node(_mul_);//R L^{R-1}
        temp2 = formula.MoveAppend(New);//x
        formula.append(RSrc_, temp1, temp2);

        FunctionBackwardAccumulate(label, now, temp2, _mul_);
        //========================================
        New = new node(_ln_);//f=xy
        origin_ = formula.MoveAppend(New);//x
        formula.append(Src_, origin_);

        New = new node(_mul_);//f=xy
        xPrime = formula.MoveAppend(New);//x
        formula.append(now, origin_, xPrime);

        New = new node(_mul_);
        originL_ = formula.MoveAppend(New);
        formula.append(xPrime, label[now], originL_);
        //========================================
        BackwardAccumulate(label, RSrc_, originL_);
        break;
    default:
        break;
    }
    return;
}


/*
01 add by 0, multiple by 1, 0 and so on.
02 arithmetic of constant.
03 repetitive leaf
04 repetitive node
05 wasted vortex.
*/


bool expression::Simplify(void)
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

#ifdef Debug03_03
        std::cout << "round_" << round_ << std::endl;
#endif // Debug03_03

    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}

void expression::LiftLeft(size_t target)
{
    size_t down;
    size_t i;
    if (formula[target].InDegree < 1)
        throw PikaError("expression::LiftLeft", "vertice[target].InDegree < 1", formula[target].InDegree);
    down = formula[target].In[0];
    formula.lift(target, down);
    if (formula[target].content->Output)
    {
        formula[target].content->Output = false;
        for (i = 0; i < output.count(); i++)
            if (output[i] == target) output[i] = down;
        formula[down].content->Output = true;
    }
    formula.VertexDelete(target);
}
void expression::LiftRight(size_t target)
{
    size_t down;
    size_t i;
    if (formula[target].InDegree < 2)
        throw PikaError("expression::LiftRight", "vertice[target].InDegree < 2", formula[target].InDegree);
    down = formula[target].In[1];
    formula.lift(target, down);
    if (formula[target].content->Output)
    {
        formula[target].content->Output = false;
        for (i = 0; i < output.count(); i++)
            if (output[i] == target) output[i] = down;
        formula[down].content->Output = true;
    }
    formula.VertexDelete(target);
}
bool expression::Simplify01(void)
{
    size_t i;
    node* here;
    node* left_, * right_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        switch ((operation)here->Code)
        {
        case _add_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                LiftRight(i);
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(i);
            }
            break;
        case _sub_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                formula.ArcDelete(formula[i].In[0], i);
                here->Type = _Funct_;
                here->Code = _minus_;
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(i);
            }
            break;
        case _mul_:
            if (left_->Type == _LeafConst_)
            {
                if (left_->Fc.isZero())
                {
                    LiftLeft(i);
                    changed_ = true;
                }
                else if (left_->Fc.isOne())
                {
                    LiftRight(i);
                    changed_ = true;
                }
            }
            else if (right_->Type == _LeafConst_)
            {
                if (right_->Fc.isZero())
                {
                    LiftRight(i);
                    changed_ = true;
                }
                else if (right_->Fc.isOne())
                {
                    LiftLeft(i);
                    changed_ = true;
                }
            }
            break;
        case _div_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(i);
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isOne())
            {
                LiftLeft(i);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool expression::Simplify02(void)
{
    size_t i;
    node* here;
    node* left_, * right_;
    size_t Left_;
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
            switch ((operation)here->Code)
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
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Funct_) continue;
        left_ = formula.In(i, 0).content;
        Left_ = formula[i].In[0];
        if (left_->Type != _LeafConst_) continue;
        here->Type = _LeafConst_;
        here->Fc = left_->Fc;
        switch ((function)here->Code)
        {
        case Pikachu::_sin_:
            here->Fc.sin();
            break;
        case Pikachu::_cos_:
            here->Fc.cos();
            break;
        case Pikachu::_exp_:
            here->Fc.exp();
            break;
        case Pikachu::_ln_:
            here->Fc.ln();
            break;
        case Pikachu::_sqrt_:
            here->Fc.sqrt();
            break;
        case Pikachu::_minus_:
            here->Fc.opposite();
            break;
        }
        formula.ArcDelete(Left_, i);
        changed_ = true;

    }
    return changed_;
}
bool expression::Simplify03(void)
{
    size_t i, j, k;
    node* here, * now;
    bool judge;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        for (j = i + 1; j < formula.capacity(); j++)
        {
            if (!formula[j].IfValid()) continue;
            now = formula[j].content;
            if (here->Type != now->Type) continue;
            judge = false;
            if (here->Type == _LeafConst_)
                judge = (here->Fc == now->Fc);
            else if (here->Type == _LeafX_)
                judge = ((here->src1 == now->src1) && (here->src2 == now->src2));
            else if (here->Type == _LeafPara_)
                judge = ((here->src1 == now->src1) && (here->src2 == now->src2));
            changed_ = judge || changed_;
            if (judge)
            {
                formula.lift(j, i);
                if (now->Output)
                {
                    here->Output = true;
                    for (k = 0; k < output.count(); k++)
                    {
                        if (output[k] == j) output[k] = i;
                    }
                }
                formula.VertexDelete(j);
            }
        }
    }
    return changed_;
}
bool expression::Simplify04(void)
{
    size_t i, j, k;
    node* here, * now;
    bool judge;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        for (j = i + 1; j < formula.capacity(); j++)
        {
            if (!formula[j].IfValid()) continue;
            now = formula[j].content;
            if (here->Type != now->Type || here->Code != now->Code) continue;
            judge = false;
            if (here->Type == _Operation_)
            {
                judge = judge || (formula[i].In[0] == formula[j].In[0] && formula[i].In[1] == formula[j].In[1]);
                if ((operation)here->Code == _add_ || (operation)here->Code == _mul_)
                    judge = judge || (formula[i].In[0] == formula[j].In[1] && formula[i].In[1] == formula[j].In[0]);
            }
            else if (here->Type == _Funct_)
                judge = (formula[i].In[0] == formula[j].In[0]);
            changed_ = judge || changed_;
            if (judge)
            {
                formula.lift(j, i);
                if (now->Output)
                {
                    here->Output = true;
                    for (k = 0; k < output.count(); k++)
                    {
                        if (output[k] == j) output[k] = i;
                    }
                }
                formula.VertexDelete(j);
            }
        }
    }
    return changed_;
}
bool expression::Simplify05(void)
{
    vector<size_t> label;
    buffer<size_t> queue;
    size_t i, count;
    count = 0;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != _uintMax_) queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    for (i = 0; i < label.count(); i++)
    {
        if (!formula[i].IfValid()) continue;
        if (!label[i])
        {
            count += 1;
            formula.VertexDelete(i);
        }
    }
    return count != 0;
}
bool expression::Simplify06(void)
{
    size_t i;
    size_t Left_, Right_;
    node* here;
    node* left_, * right_;
    int minusDegree;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        Left_ = formula[i].In[0];
        Right_ = formula[i].In[1];
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        minusDegree = ((left_->Type == _Funct_ && (function)(left_->Code) == _minus_) ? 1 : 0);
        minusDegree += ((right_->Type == _Funct_ && (function)(right_->Code) == _minus_) ? 1 : 0);
        switch ((operation)here->Code)
        {
        case _add_:
            if (minusDegree == 2)
            {

            }
            else if (minusDegree == 1)
            {
                if ((right_->Type == _Operation_ && (function)(right_->Code) == _minus_))
                {
                    changed_ = true;
                    formula.lift(i, Right_, formula[Right_].In[0]);
                    here->Code = _sub_;
                }
            }
            break;
        case _sub_:
            if (minusDegree == 2)
            {

            }
            else if (minusDegree == 1)
            {
                if (right_->Type == _Operation_ && (function)(right_->Code) == _minus_)
                {
                    changed_ = true;
                    formula.lift(i, Right_, formula[Right_].In[0]);
                    here->Code = _add_;
                }
            }
            break;
        case _mul_:
        case _div_:
            if (minusDegree == 2)
            {
                changed_ = true;
                formula.lift(i, Left_, formula[Left_].In[0]);
                formula.lift(i, Right_, formula[Right_].In[0]);
            }
            else if (minusDegree == 1)
            {

            }
            break;
        }
    }
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Funct_) continue;
        Left_ = formula[i].In[0];
        left_ = formula.In(i, 0).content;
        switch ((function)here->Code)
        {
        case Pikachu::_sin_:
        case Pikachu::_cos_:
        case Pikachu::_exp_:
        case Pikachu::_ln_:
        case Pikachu::_sqrt_:
            break;
        case Pikachu::_minus_:
            if (left_->Type == _Operation_ && (function)(left_->Code) == _minus_)
            {
                formula.lift(i, formula[Left_].In[0]);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool expression::Simplify07(void)
{
    size_t i;
    size_t Left_, Right_, temp_, two_;
    node* here;
    node* left_, * right_;
    node* New;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        Left_ = formula[i].In[0];
        Right_ = formula[i].In[1];
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        switch ((operation)here->Code)
        {
        case _add_:
            if (Left_ == Right_)
            {
                New = new node(2);
                two_ = formula.MoveAppend(New);

                New = new node(_mul_);
                temp_ = formula.MoveAppend(New);
                formula.append(two_, Left_, temp_);

                SimplifyMove(i, temp_);
                changed_ = true;
            }
            break;
        case _sub_:
            if (Left_ == Right_)
            {
                New = new node(0);
                temp_ = formula.MoveAppend(New);
                SimplifyMove(i, temp_);
                changed_ = true;
            }
            break;
        case _mul_:
            break;
        case _div_:
            if (Left_ == Right_)
            {
                New = new node(1);
                temp_ = formula.MoveAppend(New);
                SimplifyMove(i, temp_);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool expression::Simplify08(void)
{
    size_t i;
    size_t Left_, Right_, temp_, temp1_, site_;
    node* here;
    node* left_, * right_;
    node* New;
    int inDegree;
    bool changed_, judge;
    size_t j, LL, RR;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        Left_ = formula[i].In[0];
        Right_ = formula[i].In[1];
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        if (left_->Type != _Operation_ || right_->Type != _Operation_) continue;
        if ((operation)left_->Code != _mul_) continue;
        if ((operation)right_->Code != _mul_) continue;
        //if (formula[Left_].InDegree != 1 || (operation)left_->Code != _mul_) continue;
        //if (formula[Right_].InDegree != 1 || (operation)right_->Code != _mul_) continue;
        switch ((operation)here->Code)
        {
        case _add_:
        case _sub_:
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                if (formula[Left_].In[LL] == formula[Right_].In[RR])
                {
                    New = new node((operation)here->Code);
                    temp_ = formula.MoveAppend(New);
                    formula.append(formula[Left_].In[(size_t)(!LL)], formula[Right_].In[(size_t)(!RR)], temp_);

                    New = new node(_mul_);
                    site_ = formula.MoveAppend(New);
                    formula.append(formula[Left_].In[LL], temp_, site_);

                    SimplifyMove(i, site_);

                    changed_ = true;
                    break;
                }
            }
            break;
        case _mul_:
        case _div_:
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                judge = formula[formula[Left_].In[LL]].content->Type == _LeafConst_;
                judge = judge && formula[formula[Right_].In[RR]].content->Type == _LeafConst_;
                if (judge)
                {
                    New = new node((operation)here->Code);
                    temp_ = formula.MoveAppend(New);
                    formula.append(formula[Left_].In[(size_t)(!LL)], formula[Right_].In[(size_t)(!RR)], temp_);

                    New = new node((operation)here->Code);
                    temp1_ = formula.MoveAppend(New);
                    formula.append(formula[Left_].In[LL], formula[Right_].In[RR], temp1_);

                    New = new node(_mul_);
                    site_ = formula.MoveAppend(New);
                    formula.append(temp1_, temp_, site_);

                    SimplifyMove(i, site_);
                    changed_ = true;
                    break;
                }
            }
            break;
        }
        if ((operation)here->Code == _div_)
        {
            //std::cout << "Here: " << i << std::endl;
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                if (formula[Left_].In[LL] == formula[Right_].In[RR])
                {
                    New = new node(_div_);
                    temp_ = formula.MoveAppend(New);
                    formula.append(formula[Left_].In[(size_t)(!LL)], formula[Right_].In[(size_t)(!RR)], temp_);
                    SimplifyMove(i, temp_);
                    changed_ = true;
                    break;
                }
            }
        }
    }

    
    return changed_;
}
void expression::SimplifyMove(size_t target, size_t NewOne)
{
    size_t k;
    node* here, * now;
    here = formula[NewOne].content;
    now = formula[target].content;
    formula.lift(target, NewOne);
    if (now->Output)
    {
        here->Output = true;
        for (k = 0; k < output.count(); k++)
        {
            if (output[k] == target) output[k] = NewOne;
        }
    }
    formula.VertexDelete(target);
}
bool expression::Simplify09(void)
{
    size_t i;
    size_t Left_, Right_, site_;
    node* here;
    node* left_, * right_;
    node* New;
    int inDegree;
    bool changed_, judge;
    bool plus[4], boolT1, boolT2;
    bool add_sub[3]; //true: add, false :sub [0]: left, [1], right, [2]: middle
    size_t offset[4];
    size_t j, LL, RR, OpLL, OpRR;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        Left_ = formula[i].In[0];
        Right_ = formula[i].In[1];
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        if ((operation)here->Code != _add_ && (operation)here->Code != _sub_) continue;
        if (left_->Type != _Operation_ || right_->Type != _Operation_) continue;
        if ((operation)left_->Code != _add_ && (operation)left_->Code != _sub_) continue;
        if ((operation)right_->Code != _add_ && (operation)right_->Code != _sub_) continue;
        //if (formula[Left_].InDegree != 1 || formula[Right_].InDegree != 1) continue;
        plus[0] = true;
        plus[1] = left_->Code == (int)_add_;
        plus[2] = here->Code == (int)_add_;
        plus[3] = here->Code == right_->Code;
        for (j = 0; j < 4; j++)
        {
            LL = j / 2;
            RR = j % 2;
            boolT2 = (formula[formula[Left_].In[LL]].content->Type == _LeafConst_);
            boolT2 = boolT2 && (formula[formula[Right_].In[RR]].content->Type == _LeafConst_);
            boolT2 = boolT2 || (formula[Left_].In[LL] == formula[Right_].In[RR]);
            if (boolT2)
            {
                boolT1 = plus[LL] || plus[RR + 2];//at least one of those is plus;
                //2 * (!boolT1)£º into [2]£¬[3] if all are minus, otherwise  into [0]£¬[1];
                //if plus[LL] is true, if must be put into left,([0], [2]) 
                offset[!(plus[LL]) + 2 * (!boolT1)] = formula[Left_].In[LL];
                offset[(plus[LL]) + 2 * (!boolT1)] = formula[Right_].In[RR];
                add_sub[!boolT1] = (plus[LL] == plus[RR + 2]);
                /* if LL and RR all are minus, !boolT1 is true, into [1] (the right part)
                plus[LL] \ plus[RR + 2]) |  0    1
                0                        | add  sub
                1                        | sub  add
                */
                offset[!(plus[!LL]) + 2 * boolT1] = formula[Left_].In[(size_t)(!LL)];
                offset[(plus[!LL]) + 2 * boolT1] = formula[Right_].In[(size_t)(!RR)];
                add_sub[boolT1] = (plus[!LL] == plus[!RR + 2]);
                /* if if LL and RR all are minus, !LL and !RR can't be minus. boolT1 is false, into [0] (the left part)
                plus[!LL] \ plus[!RR + 2]) |  0    1
                0                          | add  sub
                1                          | sub  add
                */
                add_sub[2] = boolT1 ? (plus[!LL] || plus[!RR + 2]) : (plus[LL] || plus[RR + 2]);
                //if at least one of LL and RR is plus; boolT1 is true, !LL and !RR are in the right,
                // if one of them are plus, the middle can't be sub

                New = new node(add_sub[0] ? _add_ : _sub_);
                OpLL = formula.MoveAppend(New);
                formula.append(offset[0], offset[1], OpLL);

                New = new node(add_sub[1] ? _add_ : _sub_);
                OpRR = formula.MoveAppend(New);
                formula.append(offset[2], offset[3], OpRR);

                New = new node(add_sub[2] ? _add_ : _sub_);
                site_ = formula.MoveAppend(New);
                formula.append(OpLL, OpRR, site_);

                SimplifyMove(i, site_);
                changed_ = true;
                break;
            }
        }

    }
    return changed_;
}
bool expression::Simplify10(void)
{
    size_t i;
    size_t Left_, Right_, const_, final_;
    node* here;
    node* left_, * right_, *ll, *rr;
    node* New;
    int inDegree;
    bool changed_, judge;
    size_t j, LL, RR, first_, second_, up_;
    changed_ = false;
    for (i = 0; i < formula.capacity(); i++)
    {
        if (!formula[i].IfValid()) continue;
        here = formula[i].content;
        if (here->Type != _Operation_) continue;
        Left_ = formula[i].In[0];
        Right_ = formula[i].In[1];
        left_ = formula.In(i, 0).content;
        right_ = formula.In(i, 1).content;
        if (left_->Type != _Operation_ && right_->Type != _Operation_) continue;
        if ((operation)here->Code != _mul_) continue;
        if ((operation)right_->Code == _div_ && formula[Right_].In[1] == Left_)
        {
            SimplifyMove(i, formula[Right_].In[0]);
            changed_ = true;
        }
        if ((operation)left_->Code == _div_ && formula[Left_].In[1] == Right_)
        {
            SimplifyMove(i, formula[Left_].In[0]);
            changed_ = true;
        }
        judge = false;
        if (left_->Type == _LeafConst_ && (operation)right_->Code == _mul_)
        {
            LL = formula[Right_].In[0];
            RR = formula[Right_].In[1];
            up_ = Left_;
            judge = true;
        }
        else if (right_->Type == _LeafConst_ && (operation)left_->Code == _mul_)
        {
            LL = formula[Left_].In[0];
            RR = formula[Left_].In[1];
            up_ = Right_;
            judge = true;
        }
        if (judge)
        {
            judge = false;
            ll = formula[LL].content;
            rr = formula[RR].content;
            if (formula[LL].content->Type == _LeafConst_)
            {
                first_ = LL;
                second_ = RR;
                judge = true;
            }
            else if (formula[RR].content->Type == _LeafConst_)
            {
                first_ = RR;
                second_ = LL;
                judge = true;
            }
            if (judge)
            {
                New = new node(_mul_);
                const_ = formula.MoveAppend(New);
                formula.append(up_, first_, const_);
                New = new node(_mul_);
                final_ = formula.MoveAppend(New);
                formula.append(const_, second_, final_);
                SimplifyMove(i, final_);
                changed_ = true;
            }

        }
    }
    return changed_;
}



Expres::Expres()
{
    //ParameterCount = 0;
    //InputGroupCount = 0;
    ParameterCount = 0;
}
Expres::~Expres()
{

}
bool Expres::node::operator == (operation Op) const
{
    return  Type == _Operation_ && Code == (int)Op;
}
bool Expres::node::operator == (function Op) const
{
    return  Type == _Funct_ && Code == (int)Op;
}
Expres::node::node(void)
{
    Code = 0;
    src1 = 0;
    src2 = 0;
    Output = false;
}
Expres::node::node(long int ele)
{
    Type = _LeafConst_;
    Fc.SetValue((long long int)ele);
    src1 = 0;
    src2 = 0;
    Output = false;
}
Expres::node::node(operation opera_)
{
    Type = _Operation_;
    Code = (int)opera_;
    src1 = 0;
    src2 = 0;
    Output = false;
}
Expres::node::node(function func_)
{
    Type = _Funct_;
    Code = (int)func_;
    src1 = 0;
    src2 = 0;
    Output = false;
}
Expres::node::node(function2 func_)
{
    Type = _Funct2_;
    Code = (int)func_;
    src1 = 0;
    src2 = 0;
    Output = false;
}
Expres::node::node(type T, size_t S1, size_t S2)
{
    Type = T;
    Code = 0;
    src1 = S1;
    src2 = S2;
    Output = false;
}

Expres::node* Expres::node::copy(void)const
{
    node* New;
    New = new node();
    New->Type = Type;
    New->Code = Code;
    New->Output = Output;
    New->src1 = src1;
    New->src2 = src2;
    New->Fc.SetValue(Fc);
    return New;
}
void Expres::node::copy(const node& source)
{
    Type = source.Type;
    Code = source.Code;
    Output = source.Output;
    src1 = source.src1;
    src2 = source.src2;
    Fc.SetValue(source.Fc);
    return ;
}
void Expres::node::Demo(int label, bufferC& output, bool single, bool braket) const
{
    switch (Type)
    {
    case Pikachu::_LeafX_:
        if (single)
        {
            output += "x";
        }
        else
        {
            output += "x[";
            output += (long int)(src1);
            output += ", ";
            output += (long int)(src2);
            output += "]";
        }
        break;
    case Pikachu::_LeafConst_:
        Fc.print(output);
        break;
    case Pikachu::_LeafPara_:
        if (single)
        {
            output += "w_";
            output += (long int)(src2);
        }
        else
        {
            output += "w[";
            output += (long int)(src1);
            output += ", ";
            output += (long int)(src2);
            output += "]";
        }

        break;
    case Pikachu::_Funct_:
        if ((function)Code != _minus_)
        {
            if (label == 1) output += ")";
            else 
            {
                output += FunctionName((function)Code);
                output += "(";
            }
        }
        else
        {
            if (label == 0) 
            { 
                if (braket) output += "(-";
                else output += "-";
            }
            else
            {
                if(braket) output += ")";
            }
        }
        break;
    case Pikachu::_Operation_:
        if (label == 0) { if (braket) output += "("; }
        else if (label == 2) { if (braket) output += ")"; }
        else  output += OperationName((operation)Code);
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
            output += Function2Name((function2)Code);
            output += "(";
        }
        break;
    }
}
void Expres::node::demo(FILE* fp) const
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
        output += FunctionName((function)Code);
        break;
    case Pikachu::_Operation_:
        output += OperationName((operation)Code);
        break;
    case Pikachu::_Funct2_:
        output += Function2Name((function2)Code);
        break;
    }
    fprintf(fp, "%s.\n", output.array());
}

void Expres::clear(void)
{
    formula.clear();
    output.clear();
    InputDim.clear();
    ParameterCount = 0;
}
void Expres::copy(const Expres& source)
{
    size_t i;
    formula.copy(source.formula);
    //std::cout << "Parameter.recount(source.Parameter.count()); " << std::endl;
    output.recount(source.output.count());
    for (i = 0; i < source.output.count(); i++)
    {
        output[i] = formula[source.output[i]->site()];
    }
    formula.compress();
    InputDim.recount(source.InputDim.count());
    for (i = 0; i < source.InputDim.count(); i++)
        InputDim[i] = source.InputDim[i];
    ParameterCount = source.ParameterCount;
}
bool Expres::Simplify(void)
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

#ifdef Debug03_03
        std::cout << "round_" << round_ << std::endl;
#endif // Debug03_03

    } while (changed_);
    changed_ = changed_ || Simplify05();
    if (round_ > 1)
    {

    }
    return round_ > 1;
}
void Expres::Example(size_t No) 
{
    int error = 0;
    clear();
    if (No == 1) example01();
    else if (No == 2)error = example("exp(-(x*x))");
    else if (No == 3)error = example("pow(2, x) + pow(x, 4)");
    else if (No == 4)error = example("(exp(2 * x) - 1)/(exp(2 * x) + 1)");
    else if (No == 5)error = example("-(x*x)");
    else if (No == 6)error = example("(x)/(sqrt(1+x*x))");
    else if (No == 7)error = example("sin(-(x*x))");
    else if (No == 8)error = example("xln(x*x)");
    else if (No == 9)error = example("pow(x,8)");
    else error = example("pow(x * x,x)");
}

void Expres::demo(bufferC& out, bool single, size_t No)const
{
    vector<size_t> label, stack;
    size_t now, count;
    vortex<node>* Here;
    iteratorS<vortex<node>> iter;
    iter.append(output[No]);
    output[No]->label_3 = false;
    while (iter.still())
    {
        Here = iter.target();
        if (Here->Type == _Funct_ )
        {
            Here->In(0)->label_3 = ((function)Here->Code == _minus_);
        }
        else if (Here->Type == _Funct2_)
        {
            Here->In(0)->label_3 = false;
            Here->In(1)->label_3 = false;
        }
        else if (Here->Type == _Operation_)
        {
            Here->In(0)->label_3 = true;
            Here->In(1)->label_3 = true;
            if (*Here == _add_ || *Here == _sub_)
            {
                Here->In(0)->label_3 = false;
                if (*(Here->In(1)) == _mul_ || *(Here->In(1)) == _div_)
                    Here->In(1)->label_3 = false;
            }
            else if(*(Here->In(0)) == _mul_ || *(Here->In(0)) == _div_)
                Here->In(0)->label_3 = false;
        }
        Here->Demo(iter.state(), out, single, Here->label_3);
        vortex<node>::BackNext(iter);
    }
}
void Expres::demo(FILE* fp)const
{
    size_t i;
    for (i = 0; i < formula.count(); i++)
    {
        if (formula[i] != NULL)
        {
            fprintf(fp, "formula[%zu]: valid.\n", i);
            formula[i]->demo(fp);
            //formula[i]->Demo(fp);
            fprintf(fp, "\n");
        }
        else
        {
            fprintf(fp, "formula[%zu]: invalid.\n", i);
        }
    }
}

void Expres::PrintForwardMiniOp(VISA1& instru, vector<size_t>& FreeReg)const
{
    vector<size_t> label;
    vector<Ele*> sequence;
    buffer<Ele*> queue;
    vector<size_t> output_;

    size_t i, now, j;
    Ele* here;

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
            for (j = 0; j < output.count(); j++)
            {
                if (output[j] == here)
                {
                    instru.append(VISA1::_st_, 0, j, label[now], 0);
                }
            }
            if (output_[now] == 0) FreeReg.append(label[now]);
        }

    }
}
void Expres::PrintForwardMiniReg(VISA1& instru, vector<size_t>& FreeReg)const
{
    vector<size_t> label;
    vector<Ele*> sequence;
    buffer<Ele*> queue;
    vector<size_t> output_;
    //vector<size_t> FreeReg;
    size_t i, now, j;
    Ele* here;
    size_t left_, right_;
    Ele* L_, * R_;
    size_t src1, src2;
    PrintForwardInitial(sequence, queue, output_);


    label.recount(formula.count());
    label.value(0);

    for (i = 0; i < sequence.count(); i++)
    {
        here = sequence[i];
        now = here->site();
        switch (here->Type)
        {
        case _LeafX_:
        case _LeafPara_:
        case _LeafConst_:
            break;
        case _Operation_:
        {
            L_ = here->In(0);
            R_ = here->In(1);
            left_ = L_->site();
            right_ = R_->site();
            
            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            if (left_ != right_)
                src2 = instru.append(R_->Type, FreeReg, R_->src1, R_->src2, R_->Fc, label[right_]);
            else src2 = src1;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(src1);
            if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1)  FreeReg.append(src2);
            label[now] = instru.append(VISA1::_op_, here->Code, FreeReg, src1, src2);
            break;
        }
        case _Funct_:
            L_ = here->In(0);
            left_ = L_->site();

            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            src2 = 0;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(label[left_]);
            //if ((function)here->Code == _pow_)
            //    if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1) FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_func_, here->Code, FreeReg, src1, src2);
            break;
        case _Funct2_:
            L_ = here->In(0);
            left_ = L_->site();
            src1 = instru.append(L_->Type, FreeReg, L_->src1, L_->src2, L_->Fc, label[left_]);
            R_ = here->In(1);
            right_ = R_->site();
            if (left_ != right_)
                src2 = instru.append(R_->Type, FreeReg, R_->src1, R_->src2, R_->Fc, label[right_]);
            else src2 = src1;
            formula.OutputCut(output_, now);
            if (output_[left_] == 0 || isLeaf(L_->Type))  FreeReg.append(label[left_]);
            if ((output_[right_] == 0 || isLeaf(R_->Type)) && src2 != src1) FreeReg.append(label[right_]);
            label[now] = instru.append(VISA1::_func2_, here->Code, FreeReg, src1, src2);
            break;
        default:
            break;
        }
        if (here->Output)
        {
            for (j = 0; j < output.count(); j++)
            {
                if (output[j] == here)
                {
                    instru.append(VISA1::_st_, 0, j, label[now], 0);
                }
            }
            if (output_[now] == 0) FreeReg.append(label[now]);
        }

    }
}


void Expres::PrintForwardInitial(vector<Ele*>& sequence, buffer<Ele*>& queue, vector<size_t>& output_)const
{
    size_t i;
    vector<bool> label;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != NULL) queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    formula.TopoSortDFS(sequence);
    formula.Shrink(label, sequence);

    formula.OutputGive(output_);
}
void Expres::ForwardMiniOpCore(vector<size_t>& label, vector<size_t>& output_, VISA1& instru, vector<size_t>& FreeReg, size_t now, Ele* here)const
{
    size_t left_, right_;
    size_t src1, src2;
    switch (here->Type)
    {
    case _LeafX_:
        label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
        formula.OutputCut(output_, now);
        break;
    case _LeafPara_:
        label[now] = instru.append(VISA1::_ld_, (int)here->Type, FreeReg, here->src1, here->src2);
        formula.OutputCut(output_, now);
        break;
    case  _LeafConst_:
        label[now] = instru.append(FreeReg, here->Fc);
        formula.OutputCut(output_, now);
        break;
    case _Operation_:
        left_ = here->In(0)->site();
        right_ = here->In(1)->site();
        src1 = label[left_];
        src2 = label[right_];
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
        label[now] = instru.append(VISA1::_op_, here->Code, FreeReg, src1, src2);
        break;
    case _Funct_:
        left_ = here->In(0)->site();
        src1 = label[left_];
        src2 = 0;
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        label[now] = instru.append(VISA1::_func_, here->Code, FreeReg, src1, src2);
        break;
    case _Funct2_:
        left_ = here->In(0)->site();
        src1 = label[left_];
        right_ = here->In(1)->site();
        src2 = label[right_];
        formula.OutputCut(output_, now);
        if (output_[left_] == 0)  FreeReg.append(label[left_]);
        if (output_[right_] == 0 && src2 != src1)  FreeReg.append(label[right_]);
        label[now] = instru.append(VISA1::_func2_, here->Code, FreeReg, src1, src2);
        break;
    default:
        break;
    }
}


//========================Expression simplification
void Expres::differetial(size_t X1, size_t X2, bool Input)
{
    vector<vortex<node>*> sequence, label;
    buffer<vortex<node>*> queue;
    vector<bool> valid;
    size_t i, length, site;
    vortex<node>* here, * New;

    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != NULL) queue.append(output[i]);
    }
    printf("?????\n");
    formula.BFTbackward(valid, queue);
    printf("BFTbackward\n");
    formula.TopoSortBFS(sequence);
    printf("TopoSortBFS\n");
    formula.Shrink(valid, sequence);
    printf("?????\n");


    length = sequence.count();
    label.recount(formula.count());
    label.value(NULL);
    printf("formula.count():%zu\n", formula.count());
    for (i = 0; i < length; i++)
    {
        here = sequence[i];
        printf("\t%zu\n", here->site());
    }
    for (i = 0; i < length; i++)
    {
        printf("\t%zu, \n", i);
        here = sequence[i];
        site = here->site();
        printf("\t\t:%zu\n", here->site());
        switch (here->Type)
        {
        case _LeafX_:
            New = new vortex<node>(here->src1 == X1 && here->src2 == X2 && Input);
            formula.append(New);
            label[site] = New;
            break;
        case _LeafPara_:
            New = new vortex<node>(here->src1 == X1 && here->src2 == X2 && !Input);
            formula.append(New);
            label[site] = New;
            break;
        case  _LeafConst_:
            New = new vortex<node>(0);
            formula.append(New);
            label[site] = New;
            break;
        case _Operation_:
            label[site] = OpForwardDiff(label, here);
            printf("label[%zu]\n", (size_t)site);
            break;
        case _Funct_:
            label[site] = FunctForwardDiff(label, here);
            break;
        case _Funct2_:
            label[site] = Funct2ForwardDiff(label, here);
            break;
        default:
            break;
        }
    }
    printf("?????\n");
    for (i = 0; i < output.count(); i++)
    {
        formula[output[i]->site()]->Output = false;
        output[i] = label[output[i]->site()];
        formula[output[i]->site()]->Output = true;
    }
    printf("?????\n");

}
void Expres::ParameterBackward(size_t No)
{
    vector<vortex<node>*> label, sequence;
    size_t i, length, now;
    vortex<node>* here;
    backward(true, output.count(), No, label, sequence);
    length = sequence.count();
    ClearOutput();
    output.recount(ParameterCount);
    for (i = 0; i < length; i++)
    {
        here = sequence[i];
        now = here->site();

        switch (here->Type)
        {
        case _LeafX_:
            break;
        case _LeafPara_:
            output[here->src2] = label[now];
            if (label[now] != NULL) formula[label[now]->site()]->Output = true;
            break;
        }
    }
}
void Expres::backward(bool ExternOutput, size_t NewInputDim, size_t No, vector<vortex<Expres::node>*>& label, vector<vortex<Expres::node>*>& sequence)
{
    //vector<size_t> label, sequence;
    buffer<vortex<node>*> queue;
    size_t i, length, now, site;
    vortex<node>* here, * New;
    vector<bool> valid;
    queue.append(output[No]);
    formula.BFTbackward(valid, queue);
    //formula.path(label, queue, input, output);
    formula.TopoSortBFSBack(sequence);



    length = sequence.count();
    label.recount(length);
    label.value(NULL);

    if (ExternOutput)
    {
        New = new vortex<node>();
        New->Type = _LeafX_;
        New->src1 = InputDim.count();
        New->src2 = No;
    }
    else
    {
        New = new vortex<node>(1);
    }
    if (NewInputDim != 0) InputDim.append(NewInputDim);
    formula.append(New);
    label[output[No]->site()] = New;


    //InputGroupCount += 1;

    for (i = 0; i < length; i++)
    {
        here = sequence[i];
        now = here->site();

        switch (here->Type)
        {
        case _LeafX_:
        case _LeafPara_:
        case  _LeafConst_:
            break;
        case _Operation_:
            OperationBackDiff(label, now, here);
            break;
        case _Funct_:
            FunctBackDiff(label, now, here);
            break;
        case _Funct2_:
            Funct2BackDiff(label, now, here);
            break;
        default:
            break;
        }
    }
}
//========================Expression simplification
vortex<Expres::node>* Expres::NewNode(long int ele)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(ele);
    formula.append(New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(double ele)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(ele);
    formula.append(New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(operation Op)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(Op);
    formula.append(New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(vortex<Expres::node>* L, vortex<Expres::node>* R, operation Op)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(Op);
    formula.append(New);
    formula.ArcAdd(L, R, New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(function func_)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(func_);
    formula.append(New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(vortex<Expres::node>* L, function func_)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(func_);
    formula.append(New);
    formula.ArcAdd(L, New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(function2 func_)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(func_);
    formula.append(New);
    return New;
}
vortex<Expres::node>* Expres::NewNode(vortex<Expres::node>* L, vortex<Expres::node>* R, function2 func_)
{
    vortex<Expres::node>* New;
    New = new vortex<Expres::node>(func_);
    formula.append(New);
    formula.ArcAdd(L, R, New);
    return New;
}
vortex<Expres::node>* Expres::OpForwardDiff(vector<vortex<Expres::node>*>& label, vortex<Expres::node>* here)
{
    vortex<Expres::node>* site;
    vortex<Expres::node>* left_, * right_;
    vortex<Expres::node>* div_, * mid_;
    size_t LeftSrc_, RightSrc_;
    LeftSrc_ = here->In(0)->site();
    RightSrc_ = here->In(1)->site();
    switch ((operation)here->Code)
    {
    case _add_:
    case _sub_:
        site = NewNode(label[LeftSrc_], label[RightSrc_], (operation)here->Code);
        break;
    case _mul_:
        printf("_mul_0\n");
        left_ = NewNode(label[LeftSrc_], here->In(1), _mul_);
        printf("_mul_1\n");
        right_ = NewNode(here->In(0), label[RightSrc_], _mul_);
        printf("_mul_2\n");
        site = NewNode(left_, right_, _add_);
        printf("_mul_3\n");
        break;
    case _div_:
        left_ = NewNode(label[LeftSrc_], here->In(1), _mul_);//x^\prime * y
        right_ = NewNode(here->In(0), label[RightSrc_], _mul_);//x * y^\prime
        mid_ = NewNode(left_, right_, _sub_);
        div_ = NewNode(here->In(1), here->In(1), _mul_);
        site = NewNode(mid_, div_, _div_);
        break;
    }
    printf("return site;%zu\n", (size_t)site);
    return site;
}
vortex<Expres::node>* Expres::FunctForwardDiff(vector<vortex<Expres::node>*>& label, vortex<Expres::node>* here)
{
    vortex<Expres::node>* site;
    vortex<Expres::node>* origin_, * xPrime, * const_;
    size_t Src_, RSrc_;
    Src_ = here->In(0)->site();
    switch ((function)here->Code)
    {
    case _sin_:
        origin_ = NewNode(here->In(0), _cos_);
        site = NewNode(label[Src_], origin_, _mul_);
        break;
    case _cos_:
        origin_ = NewNode(here->In(0), _sin_);
        xPrime = NewNode(label[Src_], origin_, _mul_);
        site = NewNode(xPrime, _minus_);
        break;
    case _exp_:
        site = NewNode(label[Src_], here, _mul_);
        break;
    case _ln_:
        printf("_ln_:here->In(0):%zu\n", (size_t)here->In(0));
        site = NewNode(label[Src_], here->In(0), _div_);//f=xy
        break;
    case _sqrt_://origin_
        const_ = new vortex<node>((long int)2);//f=xy
        formula.append(const_);//x
        xPrime = NewNode(const_, here, _mul_);
        site = NewNode(label[Src_], xPrime, _div_);
        break;
    case _minus_:
        site = NewNode(label[Src_], _minus_);
        break;
    default:
        break;
    }
    return site;
}
vortex<Expres::node>* Expres::Funct2ForwardDiff(vector<vortex<Expres::node>*>& label, vortex<Expres::node>* here)
{
    //vortex<node>* New;
    vortex<node>* site;
    vortex<node>* origin_, * xPrime, * const_, * yPrime;
    vortex<node>* originR_, *originL_;
    size_t Src_, RSrc_;
    vortex<node>* temp1, * temp2;
    Src_ = here->In(0)->site();
    RSrc_ = here->In(1)->site();
    switch ((function2)here->Code)
    {
    case _pow_:// R^{prime}ln(L)L^R+L^{prime}R L^{R-1}
        //1
        const_ = new vortex<node>((long int)1);
        printf("const_\n");
        //formula.append(New);
        xPrime = NewNode(here->In(1), const_, _sub_);//R-1
        temp1 = NewNode(here->In(0), xPrime, _pow_);//L^{R-1}
        temp2 = NewNode(here->In(1), temp1, _mul_);//R L^{R-1}
        originR_ = NewNode(label[Src_], temp2, _mul_);//L^{prime} R L^{R-1}
        //========================================
        origin_ = NewNode(here->In(0), _ln_);// ln(L);
        yPrime = NewNode(label[RSrc_], origin_, _mul_); // R^{prime}ln(L)
        originL_ = NewNode(yPrime, here, _mul_);// L^R R^{prime}ln(L)
        //========================================
        site = NewNode(originL_, originR_, _add_);


        //New = new vortex<node>(_mul_);//R L^{R-1}
        //temp2 = formula.append(New);//x
        //formula.ArcAdd(RSrc_, temp1, temp2);

        //New = new vortex<node>(_mul_);//L^{prime} R L^{R-1}
        //originR_ = formula.append(New);
        //formula.ArcAdd(label[Src_], temp2, originR_);
        //========================================
        //New = new vortex<node>(_ln_);//f=xy
        //origin_ = formula.append(New);//x
        //formula.ArcAdd(Src_, origin_);

        //New = new vortex<node>(_mul_);//f=xy
        //xPrime = formula.append(New);//x
        //formula.ArcAdd(label[RSrc_], origin_, xPrime);

        //New = new vortex<node>(_mul_);
        //originL_ = formula.append(New);
        //formula.ArcAdd(xPrime, now, originL_);
        //========================================
       // New = new vortex<node>(_add_);//f=xy
        //site = formula.append(New);//x
        //formula.ArcAdd(originL_, originR_, site);
        break;
    }

    return site;
}

void Expres::ClearOutput(void)
{
    size_t i;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != NULL)
        {
            formula[output[i]->site()]->Output = false;
        }
    }
    output.clear();
}

void Expres::BackAccumulate(vector<vortex<node>*>& label, size_t target, vortex<node>* source)
{
    vortex<node>* New;
    if (label[target] == NULL) label[target] = source;
    else
    {
        New = NewNode(label[target], source, _add_);
        label[target] = New;
    }
}
void Expres::OperationBackDiff(vector<vortex<node>*>& label, size_t now, vortex<Expres::node>* here)
{
    vortex<node>* New;
    vortex<node>* site;
    vortex<node>* left_, * right_;
    vortex<node>* div_, * mid_;
    size_t LeftSrc_, RightSrc_;
    LeftSrc_ = here->In(0)->site();
    RightSrc_ = here->In(1)->site();
    switch ((operation)here->Code)
    {
    case _add_:
        BackAccumulate(label, LeftSrc_, label[now]);
        BackAccumulate(label, RightSrc_, label[now]);
        break;
    case _sub_:
        BackAccumulate(label, LeftSrc_, label[now]);
        New = NewNode(label[now], _minus_);
        BackAccumulate(label, RightSrc_, New);
        break;
    case _mul_:
        left_ = NewNode(label[now], here->In(1), _mul_);//f=xy
        BackAccumulate(label, LeftSrc_, left_);
        right_ = NewNode(here->In(0), label[now], _mul_);
        BackAccumulate(label, RightSrc_, right_);
        break;
    case _div_:
        left_ = NewNode(label[now], here->In(1), _div_);//f=xy
        BackAccumulate(label, LeftSrc_, left_);

        right_ = NewNode(here->In(1), here->In(1), _mul_);// R ^ 2
        div_ = NewNode(right_, _minus_);// -R ^ 2
        mid_ = NewNode(label[now], here->In(0), _mul_);// \frac{\partial O}{\partial Y}L
        site = NewNode(mid_, div_, _div_);// \frac{\partial O}{\partial Y}L / ( -R ^ 2)
        BackAccumulate(label, RightSrc_, site);
        break;
    }
}
void Expres::FunctBackAccumulate(vector<vortex<node>*>& label, size_t now, vortex<Expres::node>* source, int Code)
{
    vortex<node>* xPrime, * temp;
    size_t target;
    target = formula[now]->In(0)->site();

    xPrime = NewNode(label[now], source, (operation)Code);

    if (label[target] == NULL) label[target] = xPrime;
    else
    {
        temp = NewNode(label[target], xPrime, _add_);
        label[target] = temp;
    }
}
void Expres::FunctBackDiff(vector<vortex<node>*>& label, size_t now, vortex<Expres::node>* here)
{
    vortex<node>* New;
    vortex<node>* site;
    vortex<node>* origin_;
    vortex<node>* xPrime;
    vortex<node>* const_;
    vortex<node>* originR_;
    vortex<node>* originL_;
    vortex<node>* Src_;// RSrc_;
    //size_t temp1, temp2;
    Src_ = here->In(0);

    switch ((function)here->Code)
    {
    case _sin_:
        origin_ = NewNode(Src_, _cos_);
        FunctBackAccumulate(label, now, origin_, _mul_);
        break;
    case _cos_:
        site = NewNode(Src_, _cos_);
        origin_ = NewNode(site, _minus_);
        FunctBackAccumulate(label, now, origin_, _mul_);
        break;
    case _exp_:
        FunctBackAccumulate(label, now, here, _mul_);
        break;
    case _ln_:// \frac{\partial O}{\partial f}  /x
        FunctBackAccumulate(label, now, Src_, _div_);
        break;
    case _sqrt_://origin_
        const_ = new vortex<node>((long int)2);//f=xy
        xPrime = NewNode(const_, here, _mul_);//x
        FunctBackAccumulate(label, now, xPrime, _div_);
        break;
    case _minus_:
        site = NewNode(label[now], _minus_);
        BackAccumulate(label, Src_->site(), site);
        break;
    default:
        break;
    }
    return;
}
void Expres::Funct2BackDiff(vector<vortex<node>*>& label, size_t now, vortex<Expres::node>* here)
{
    vortex<node>* origin_;
    vortex<node>* xPrime;
    vortex<node>* yPrime;
    vortex<node>* const_;
    vortex<node>* originL_;
    vortex<node>* Src_;
    vortex<node>* RSrc_;
    vortex<node>* temp1;
    vortex<node>* temp2;
    Src_ = here->In(0);
    RSrc_ = here->In(1);
    switch ((function)here->Code)
    {
    case _pow_:// R^{prime}ln(L)L^R+L^{prime}L^{R-1}
        //1
        const_ = new vortex<node>((long int)1);

        xPrime = NewNode(RSrc_, const_, _sub_);//R-1
        temp1 = NewNode(Src_, xPrime, _pow_);//L^{R-1}
        temp2 = NewNode(RSrc_, temp1, _mul_);//R L^{R-1}

        FunctBackAccumulate(label, now, temp2, _mul_);
        //========================================
        origin_ = NewNode(Src_, _ln_);//ln L
        yPrime = NewNode(here, origin_, _mul_);//L^{R} ln(L)
        originL_ = NewNode(yPrime, label[now], _mul_);//L^{R} ln(L)
        //========================================
        BackAccumulate(label, RSrc_->site(), originL_);
        break;
    default:
        break;
    }
    return;
}


//========================Expression simplification
void Expres::example01(void)
{
    vortex<node>* New;
    vortex<node>* temp;
    vortex<node>* X;
    size_t site;
    size_t input_;

    X = new vortex<node>(_LeafX_, 0, 0);
    formula.append(X);

    New = new vortex<node>(_mul_);
    formula.append(New);
    
    formula.ArcAdd(X, X, New);

    temp = new vortex<node>(_exp_);
    output.append(temp);
    formula.append(temp);
    temp->Output = true;

    formula.ArcAdd(New, temp);

    InputDim.recount(1);
    InputDim[0] = 1;
    //InputGroupCount = 1;
    ParameterCount = 0;
}
//========================Expression simplification
bool Expres::Simplify01(void)
{
    size_t i;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        switch ((operation)here->Code)
        {
        case _add_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                LiftRight(here);
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(here);
            }
            break;
        case _sub_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                formula.ArcDelete(left_, here);
                //formula.ArcDelete(formula[i].In[0], i);
                here->Type = _Funct_;
                here->Code = _minus_;
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(here);
            }
            break;
        case _mul_:
            if (left_->Type == _LeafConst_)
            {
                if (left_->Fc.isZero())
                {
                    LiftLeft(here);
                    changed_ = true;
                }
                else if (left_->Fc.isOne())
                {
                    LiftRight(here);
                    changed_ = true;
                }
            }
            else if (right_->Type == _LeafConst_)
            {
                if (right_->Fc.isZero())
                {
                    LiftRight(here);
                    changed_ = true;
                }
                else if (right_->Fc.isOne())
                {
                    LiftLeft(here);
                    changed_ = true;
                }
            }
            break;
        case _div_:
            if (left_->Type == _LeafConst_ && left_->Fc.isZero())
            {
                changed_ = true;
                LiftLeft(here);
            }
            else if (right_->Type == _LeafConst_ && right_->Fc.isOne())
            {
                LiftLeft(here);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
void Expres::OutputAppend(vortex<Expres::node>* src)
{
    output.append(src);
    src->Output = true;
}
void Expres::OutputShift(vortex<Expres::node>* src, vortex<Expres::node>* dst)
{
    size_t i;
    if (src->Output)
    {
        src->Output = false;
        for (i = 0; i < output.count(); i++)
            if (output[i] == src) output[i] = dst;
        dst->Output = true;
    }
}
void Expres::LiftLeft(vortex<Expres::node>* target)
{
    vortex<node>* down;
    if (target->InDegree() < 1)
        throw PikaError("Expres::LiftLeft", "target->InDegree() < 1)", target->InDegree());
    down = target->In(0);
    formula.lift(target, down);
    OutputShift(target, down);
    formula.ruin(target->site());
}
void Expres::LiftRight(vortex<Expres::node>* target)
{
    vortex<node>* down;
    if (target->InDegree() < 2)
        throw PikaError("Expres::LiftRight", "target->InDegree() < 2", target->InDegree());
    down = target->In(1);
    formula.lift(target, down);
    OutputShift(target, down);
    formula.ruin(target->site());
}
bool Expres::Simplify02(void)
{
    size_t i;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        if (left_->Type == _LeafConst_ && right_->Type == _LeafConst_)
        {
            here->Type = _LeafConst_;
            switch ((operation)here->Code)
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
            formula.ArcDelete(left_, here);
            formula.ArcDelete(right_, here);
            //formula.ArcDelete(formula[i].In[0], i);
            //formula.ArcDelete(formula[i].In[1], i);
            changed_ = true;
        }

    }
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Funct_) continue;
        left_ = here->In(0);
        if (left_->Type != _LeafConst_) continue;
        here->Type = _LeafConst_;
        here->Fc = left_->Fc;
        switch ((function)here->Code)
        {
        case Pikachu::_sin_:
            here->Fc.sin();
            break;
        case Pikachu::_cos_:
            here->Fc.cos();
            break;
        case Pikachu::_exp_:
            here->Fc.exp();
            break;
        case Pikachu::_ln_:
            here->Fc.ln();
            break;
        case Pikachu::_sqrt_:
            here->Fc.sqrt();
            break;
        case Pikachu::_minus_:
            here->Fc.opposite();
            break;
        }
        formula.ArcDelete(left_, here);
        changed_ = true;
    }
    return changed_;
}
bool Expres::Simplify03(void)
{
    size_t i, j, k;
    vortex<node>* here, * now;
    bool judge;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        for (j = i + 1; j < formula.count(); j++)
        {
            now = formula[j];
            if (now == NULL) continue;
            if (here->Type != now->Type) continue;
            judge = false;
            if (here->Type == _LeafConst_)
                judge = (here->Fc == now->Fc);
            else if (here->Type == _LeafX_)
                judge = ((here->src1 == now->src1) && (here->src2 == now->src2));
            else if (here->Type == _LeafPara_)
                judge = ((here->src1 == now->src1) && (here->src2 == now->src2));
            changed_ = judge || changed_;
            if (judge)
            {
                formula.lift(now, here);
                OutputShift(now, here);
                formula.ruin(j);
                //formula.VertexDelete(j);
            }
        }
    }
    return changed_;
}
bool Expres::Simplify04(void) 
{
    size_t i, j, k;
    vortex<node>* here, * now;
    bool judge;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        for (j = i + 1; j < formula.count(); j++)
        {
            now = formula[j];
            if (now == NULL) continue;
            if (here->Type != now->Type || here->Code != now->Code) continue;
            judge = false;
            if (here->Type == _Operation_)
            {
                judge = judge || (here->In(0) == now->In(0) && here->In(1) == now->In(1));
                if ((operation)here->Code == _add_ || (operation)here->Code == _mul_)
                    judge = judge || (here->In(0) == now->In(1) && here->In(1) == now->In(0));
            }
            else if (here->Type == _Funct_)
                judge = (here->In(0) == now->In(0));
            changed_ = judge || changed_;
            if (judge)
            {
                formula.lift(now, here);
                //formula.lift(j, i);//middle down
                OutputShift(now, here);
                formula.ruin(j);
            }
        }
    }
    return changed_;
}
bool Expres::Simplify05(void) 
{
    vector<bool> label;
    buffer<vortex<node>*> queue;
    size_t i, count;
    count = 0;
    for (i = 0; i < output.count(); i++)
    {
        if (output[i] != NULL) queue.append(output[i]);
    }
    formula.BFTbackward(label, queue);
    for (i = 0; i < label.count(); i++)
    {
        if (formula[i] == NULL) continue;
        if (!label[i])
        {
            count += 1;
            formula.ruin(i);
        }
    }
    return count != 0;
}
bool Expres::Simplify06(void) 
{
    size_t i;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    int minusDegree;
    bool changed_;
    bool RightMinus;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        minusDegree = ((*left_ ==  _minus_) ? 1 : 0);
        RightMinus = (*right_ == _minus_);
        minusDegree += RightMinus ? 1 : 0;
        switch ((operation)here->Code)
        {
        case _add_:
            if (minusDegree == 2)
            {

            }
            else if (minusDegree == 1)
            {
                if (RightMinus)
                {
                    changed_ = true;
                    formula.lift(here, right_, right_->In(0));
                    here->Code = _sub_;
                }
            }
            break;
        case _sub_:
            if (minusDegree == 2)
            {

            }
            else if (minusDegree == 1)
            {
                if (RightMinus)
                {
                    changed_ = true;
                    formula.lift(here, right_, right_->In(0));
                    here->Code = _add_;
                }
            }
            break;
        case _mul_:
        case _div_:
            if (minusDegree == 2)
            {
                changed_ = true;
                formula.lift(here, left_, left_->In(0));
                formula.lift(here, right_, right_->In(0));
            }
            else if (minusDegree == 1)
            {

            }
            break;
        }
    }
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Funct_) continue;
        left_ = here->In(0);
        switch ((function)here->Code)
        {
        case Pikachu::_sin_:
        case Pikachu::_cos_:
        case Pikachu::_exp_:
        case Pikachu::_ln_:
        case Pikachu::_sqrt_:
            break;
        case Pikachu::_minus_:
            if (*left_ == _minus_)
            {
                formula.lift(here, left_->In(0));
                OutputShift(here, left_->In(0));
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool Expres::Simplify07(void) 
{
    size_t i;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    vortex<node>* New, *two_;
    bool changed_;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        switch ((operation)here->Code)
        {
        case _add_:
            if (left_ == right_)
            {
                two_ = new vortex<node>(2);
                formula.append(two_);

                New = new vortex<node>(_mul_);
                formula.append(New);
                formula.ArcAdd(two_, left_, New);

                SimplifyMove(here, New);
                changed_ = true;
            }
            break;
        case _sub_:
            if (left_ == right_)
            {
                New = new vortex<node>(0);
                formula.append(New);
                SimplifyMove(here, New);
                changed_ = true;
            }
            break;
        case _mul_:
            break;
        case _div_:
            if (left_ == right_)
            {
                New = new vortex<node>(1);
                formula.append(New);
                SimplifyMove(here, New);
                changed_ = true;
            }
            break;
        }
    }
    return changed_;
}
bool Expres::Simplify08(void)
{
    size_t i;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    vortex<node>* temp1_, * temp_, * New;
    bool changed_, judge;
    size_t j, LL, RR;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        if (!(*left_ == _mul_)) continue;
        if (!(*right_ == _mul_)) continue;
        switch ((operation)here->Code)
        {
        case _add_:
        case _sub_:
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                if (left_->In(LL) == right_->In(RR))
                {
                    temp_ = new vortex<node>((operation)here->Code);
                    formula.append(temp_);
                    formula.ArcAdd(left_->In((size_t)(!LL)), right_->In((size_t)(!RR)), temp_);

                    New = new vortex<node>(_mul_);
                    formula.append(New);
                    formula.ArcAdd(left_->In(LL), temp_, New);

                    SimplifyMove(here, New);

                    changed_ = true;
                    break;
                }
            }
            break;
        case _mul_:
        case _div_:
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                judge = left_->In(LL)->Type == _LeafConst_;
                judge = right_->In(RR)->Type == _LeafConst_;
                if (judge)
                {
                    temp_ = new vortex<node>((operation)here->Code);
                    formula.append(temp_);
                    formula.ArcAdd(left_->In((size_t)(!LL)), right_->In((size_t)(!RR)), temp_);

                    temp1_ = new vortex<node>((operation)here->Code);
                    formula.append(temp1_);
                    formula.ArcAdd(left_->In(LL), right_->In(RR), temp1_);

                    New = new vortex<node>(_mul_);
                    formula.append(New);
                    formula.ArcAdd(temp1_, temp_, New);

                    SimplifyMove(here, New);
                    changed_ = true;
                    break;
                }
            }
            break;
        }
        if ((operation)here->Code == _div_)
        {
            //std::cout << "Here: " << i << std::endl;
            for (j = 0; j < 4; j++)
            {
                LL = j / 2;
                RR = j % 2;
                if (left_->In(LL) == right_->In(RR))
                {
                    New = new vortex<node>(_div_);
                    formula.ArcAdd(left_->In((size_t)(!LL)), right_->In((size_t)(!RR)), New);
                    SimplifyMove(here, New);
                    changed_ = true;
                    break;
                }
            }
        }
    }


    return changed_;
}
bool Expres::Simplify09(void)
{
    size_t i;
    size_t site_;
    vortex<node>* here;
    vortex<node>* left_, * right_;
    vortex<node>* New, *OpLL, *OpRR;
    int inDegree;
    bool changed_, judge;
    bool plus[4], boolT1, boolT2;
    bool add_sub[3]; //true: add, false :sub [0]: left, [1], right, [2]: middle
    vortex<node>* offset[4];
    size_t j, LL, RR;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (here->Type != _Operation_) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        if ((operation)here->Code != _add_ && (operation)here->Code != _sub_) continue;
        if (left_->Type != _Operation_ || right_->Type != _Operation_) continue;
        if ((operation)left_->Code != _add_ && (operation)left_->Code != _sub_) continue;
        if ((operation)right_->Code != _add_ && (operation)right_->Code != _sub_) continue;
        //if (formula[Left_].InDegree != 1 || formula[Right_].InDegree != 1) continue;
        plus[0] = true;
        plus[1] = left_->Code == (int)_add_;
        plus[2] = here->Code == (int)_add_;
        plus[3] = here->Code == right_->Code;
        for (j = 0; j < 4; j++)
        {
            LL = j / 2;
            RR = j % 2;
            boolT2 = (left_->In(LL)->Type == _LeafConst_);
            boolT2 = boolT2 && (right_->In(RR)->Type == _LeafConst_);
            boolT2 = boolT2 || (left_->In(LL) == right_->In(RR));
            if (boolT2)
            {
                boolT1 = plus[LL] || plus[RR + 2];//at least one of those is plus;
                //2 * (!boolT1)£º into [2]£¬[3] if all are minus, otherwise  into [0]£¬[1];
                //if plus[LL] is true, if must be put into left,([0], [2]) 
                offset[!(plus[LL]) + 2 * (!boolT1)] = left_->In(LL);
                offset[(plus[LL]) + 2 * (!boolT1)] = right_->In(RR);
                add_sub[!boolT1] = (plus[LL] == plus[RR + 2]);
                /* if LL and RR all are minus, !boolT1 is true, into [1] (the right part)
                plus[LL] \ plus[RR + 2]) |  0    1
                0                        | add  sub
                1                        | sub  add
                */
                offset[!(plus[!LL]) + 2 * boolT1] = left_->In((size_t)(!LL));
                offset[(plus[!LL]) + 2 * boolT1] = right_->In((size_t)(!RR));
                add_sub[boolT1] = (plus[!LL] == plus[!RR + 2]);
                /* if if LL and RR all are minus, !LL and !RR can't be minus. boolT1 is false, into [0] (the left part)
                plus[!LL] \ plus[!RR + 2]) |  0    1
                0                          | add  sub
                1                          | sub  add
                */
                add_sub[2] = boolT1 ? (plus[!LL] || plus[!RR + 2]) : (plus[LL] || plus[RR + 2]);
                //if at least one of LL and RR is plus; boolT1 is true, !LL and !RR are in the right,
                // if one of them are plus, the middle can't be sub

                OpLL = new vortex<node>(add_sub[0] ? _add_ : _sub_);
                formula.append(OpLL);
                formula.ArcAdd(offset[0], offset[1], OpLL);

                OpRR = new vortex<node>(add_sub[1] ? _add_ : _sub_);
                formula.append(OpRR);
                formula.ArcAdd(offset[2], offset[3], OpRR);

                New = new vortex<node>(add_sub[2] ? _add_ : _sub_);
                formula.append(New);
                formula.ArcAdd(OpLL, OpRR, New);

                SimplifyMove(here, New);
                changed_ = true;
                break;
            }
        }

    }
    return changed_;
}
void Expres::SimplifyMove(vortex<node>* target, vortex<node>* NewOne)
{
    formula.lift(target, NewOne);
    OutputShift(target, NewOne);
    formula.ruin(target->site());
}
bool Expres::Simplify10(void)
{
    size_t i;
    vortex<node>* const_,* final_;
    vortex<node>* here;
    vortex<node>* left_, * right_, * first_, * second_;
    vortex<node>* New, *up_, *LL, *RR;
    int inDegree;
    bool changed_, judge;
    size_t j;
    changed_ = false;
    for (i = 0; i < formula.count(); i++)
    {
        here = formula[i];
        if (here == NULL) continue;
        if (!(*here == _mul_)) continue;
        left_ = here->In(0);
        right_ = here->In(1);
        if (left_->Type != _Operation_ && right_->Type != _Operation_) continue;
        if ((operation)right_->Code == _div_ && right_->In(1) == left_)
        {
            SimplifyMove(here, right_->In(0));
            changed_ = true;
        }
        if ((operation)left_->Code == _div_ && left_->In(1) == right_)
        {
            SimplifyMove(here, left_->In(0));
            changed_ = true;
        }
        judge = false;
        if (left_->Type == _LeafConst_ && (operation)right_->Code == _mul_)
        {
            LL = right_->In(0);
            RR = right_->In(1);
            up_ = left_;
            judge = true;
        }
        else if (right_->Type == _LeafConst_ && (operation)left_->Code == _mul_)
        {
            LL = left_->In(0);
            RR = left_->In(1);
            up_ = right_;
            judge = true;
        }
        if (judge)
        {
            judge = false;
            if (LL->Type == _LeafConst_)
            {
                first_ = LL;
                second_ = RR;
                judge = true;
            }
            else if (RR->Type == _LeafConst_)
            {
                first_ = RR;
                second_ = LL;
                judge = true;
            }
            if (judge)
            {
                const_ = new vortex<node>(_mul_);
                formula.append(const_);
                formula.ArcAdd(up_, first_, const_);
                final_ = new vortex<node>(_mul_);
                formula.append(final_);
                formula.ArcAdd(const_, second_, final_);
                SimplifyMove(here, final_);
                changed_ = true;
            }

        }
    }
    return changed_;
}
//========================