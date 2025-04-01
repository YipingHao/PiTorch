#include"extern.h"
#include<iostream>
int static test_entrance(const char* output_path);

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

#include<cmath>
int main()
{
    int error;
    try
    {
        error = test_entrance("./");
    }
    catch (Pikachu::PikaError& E)
    {
        std::cout << "int main(): " << std::endl;
        E.show(stderr);
    }
    return error;
}

class CFile
{
public:
    CFile();
    ~CFile();
    void close(void);
    void Open(const char* name, const char* mode);
    void OpenRead(const char* s);//SH_read_from_file__(const char* s);
    void OpenWriteAtRear(const char* s);//fp_write_at_rear(const char* s);
    void OpenWritePlus(const char* s);//fp_write_plus
    std::string FusePathAndName(const std::string& path, const std::string& name);//path_add_file_name
    std::string FusePathAndName(const char* path, const std::string& name);//path_add_file_name
    std::string ChangeSuffix(const std::string& file, const char* new_one);//string suffix_change(const string& file, const char* new_one);
    
    FILE* fp;
private:

};



class parameter
{
public:
    parameter();
    ~parameter();
    void build(hyperlex::dictionary& pf);
    std::string FullInputName(void) const;
    std::string FullOutputName(void) const;
    std::string FullDataName(void) const;
    void Demo(FILE* fp)const;
    size_t thread;
    char* funcName;
    bool option1;
    int option2;
private:
    char* inputPath;
    char* outputPath;

    char* inputName;
    char* outputName;

    char* DataFilePath;
    char* DataFileName;

};



int static test01(const parameter& para);
int static test02(const parameter& para);
int static test03(const parameter& para);
int static test04(const parameter& para);
int static test05(const parameter& para);
int static test06(const parameter& para);
int static test07(const parameter& para);
int static test08(const parameter& para);
int static test09(const parameter& para);
int static test10(const parameter& para);
int static test11(const parameter& para);
int static test12(const parameter& para);
int static test13(const parameter& para);
int static test14(const parameter& para);
int static test15(const parameter& para);
int static test16(const parameter& para);

int test_entrance(const char* output_path)
{
    int item;
    int info;
    hyperlex::dictionary pf;
    size_t sitePF;
    parameter para;
    CFile FF;
    FF.OpenRead("./test/parameter.txt");
    pf.build(FF.fp);
    pf.print(stdout);
    item = (int)pf.search((long int)0, "item");
    std::cout << "item: " << item << std::endl;
    info = 0;
    para.build(pf);
    std::cout << "======================== parameter Demo ========================" << std::endl;
    para.Demo(stdout);
    try
    {
        switch (item)
        {
        case 1:
            info = test01(para);
            break;
        case 2:
            info = test02(para);
            break;
        case 3:
            info = test03(para);
            break;
        case 4:
            std::cout << "Test contraction; " << std::endl;
            info = test04(para);
            break;
        case 5:
            std::cout << "Test dispatch; " << std::endl;
            info = test05(para);
            break;
        case 6:
            std::cout << "test elementwise; " << std::endl;
            info = test06(para);
            break;
        case 7:
            std::cout << "Test symbolic 01; " << std::endl;
            info = test07(para);
            break;
        case 8:
            std::cout << "Test activation; " << std::endl;
            info = test08(para);
            break;
        case 9:
            std::cout << "test expression; " << std::endl;
            info = test09(para);
            break;
        case 10:
            std::cout << "Test activation 2; " << std::endl;
            info = test10(para);
            break;
        case 11:
            std::cout << "Test backward; " << std::endl;
            info = test11(para);
            break;
        case 12:
            std::cout << "test_forward_all " << std::endl;
            info = test12(para);
            break;
        case 13:
            std::cout << "Test grammer LR0 LR1 from input file; " << std::endl;
            info = test13(para);
            break;
        case 14:
            std::cout << "Test template; " << std::endl;
            info = test14(para);
            break;
        case 15:
            std::cout << "Test grammer LR0 from input file; " << std::endl;
            info = test15(para);
            break;
        case 16:
            std::cout << "Test grammer LR1 from input file; " << std::endl;
            info = test16(para);
            break;
        default:
            info = test01(para);
            break;
        }
    }
    catch (Pikachu::PikaError& E)
    {
        std::cout << "test_entrance: " << item << std::endl;
        E.show(stderr);
        throw Pikachu::PikaError("test_entrance", "???", item);
    }
    
    std::cout << "test end: " << info << std::endl;
    return info;
}




static char* CopyMalloc(const char* s);
std::string static path_add_file_name(const std::string& path, const std::string& name);
bool static true_false_judge(const char* c_t_f);
int static if_letter_judge(char c);


parameter::parameter()
{
    inputPath = NULL;
    outputPath = NULL;

    inputName = NULL;
    outputName = NULL;

    funcName = NULL;

    DataFilePath = NULL;
    DataFileName = NULL;
}
parameter::~parameter()
{
    free(inputPath);
    free(outputPath);

    free(inputName);
    free(outputName);

    free(funcName);

    free(DataFilePath);
    free(DataFileName);
}
std::string parameter::FullInputName(void) const
{
    std::string path;
    std::string file;
    std::string out;
    path = inputPath;
    file = inputName;
    out = path_add_file_name(path, file);
    return out;
}
std::string parameter::FullOutputName(void) const
{
    std::string path;
    std::string file;
    std::string out;
    path = outputPath;
    file = outputName;
    out = path_add_file_name(path, file);
    return out;
}
std::string parameter::FullDataName(void) const
{
    std::string path;
    std::string file;
    std::string out;
    path = DataFilePath;
    file = DataFileName;
    out = path_add_file_name(path, file);
    return out;
}
void parameter::build(hyperlex::dictionary& pf)
{
    size_t sitePF, i;
    std::string temp;
    thread = (size_t)pf.search((long int)1, "thread");

    option2 = (size_t)pf.search((long int)1, "option2");
    
    temp = pf.search("InputFileName", "C10H8.txt");
    inputName = CopyMalloc(temp.c_str());

    temp = pf.search("OutputFileName", "fi.c");
    outputName = CopyMalloc(temp.c_str());

    temp = pf.search("InputFilePath", "/share/fayelulu/FIanalyzer/data/");
    inputPath = CopyMalloc(temp.c_str());

    temp = pf.search("OutputFilePath", "/share/fayelulu/FIanalyzer/data/");
    outputPath = CopyMalloc(temp.c_str());

    temp = pf.search("funcName", "RtoFI");
    funcName = CopyMalloc(temp.c_str());

    temp = pf.search("DataFilePath", "/share/fayelulu/FIanalyzer/data/");
    DataFilePath = CopyMalloc(temp.c_str());

    temp = pf.search("DataFileName", "fort.100");
    DataFileName = CopyMalloc(temp.c_str());

    option1 = pf.search(true, "option1");

}
void parameter::Demo(FILE* fp)const
{
    fprintf(fp, "thread: %zu\n", thread);
    fprintf(fp, "inputPath: %s\n", inputPath);
    fprintf(fp, "outputPath: %s\n", outputPath);
    fprintf(fp, "inputName: %s\n", inputName);
    fprintf(fp, "outputName: %s\n", outputName);
    fprintf(fp, "funcName: %s\n", funcName);

    if(option1)
        fprintf(fp, "option1: Y\n");
    else
        fprintf(fp, "option1: N\n");
    fprintf(fp, "option2: %d\n", option2);
}


using namespace Pikachu;
void static testcontract(const size_t l, const size_t r, const size_t o, const size_t extra)
{
    size_t i, cnDim, label, site, LorR, middle;
    vector<size_t> O;
    vector<size_t> L;
    vector<size_t> R;
    array<bool> OL;
    array<bool> RL;
    array<bool> LL;

    bool temp, clear;
    HyperAlgebra::SimpleRandom Sr;

    ContractDesc con, ba;
    tensor W, N, M, C, Nb, Mb;
    ContractDesc ba2;
    tensor Nb2, Mb2;
    //C = WN
    {
        O.recount(o);
        L.recount(l);
        R.recount(r);

        OL.Realloc(o);
        LL.Realloc(l);
        RL.Realloc(r);

        OL.value(false);
        LL.value(false);
        RL.value(false);
        cnDim = (l + r - o) / 2;
        clear = false;
        if (clear)std::cout << "dim output: " << o;
        if (clear)std::cout << ", dim left: " << l;
        if (clear)std::cout << ", dim right: " << r;
        if (clear)std::cout << ", contraction Dim: " << cnDim << std::endl;

        if (o > (l + r))
        {
            if (clear)std::cout << "Not well triple: (o > (l + r))" << std::endl;
            return;
        }
        if ((l + r - o) % 2 != 0)
        {
            if (clear)std::cout << "Not well triple: (remain 1)" << std::endl;
            return;
        }
        if (cnDim > l || cnDim > r)
        {
            if (clear)std::cout << "Not well triple: (cnDim > l || cnDim > r)" << std::endl;
            return;
        }
        label = 0;
    }

    
    W.ChangeOrder(l);
    N.ChangeOrder(r);
    M.ChangeOrder(o);
    C.ChangeOrder(o);
    
    Mb.ChangeOrder(o + extra);


    for (i = 0; i < cnDim; i++)
    {
        //std::cout << "i" << i << std::endl;
        middle = Sr.rand(1, 16);
        do
        {
            site = Sr.rand(0, l);
        } while (LL[site]);
        L[site] = label;
        LL[site] = true;
        W.ChangeDim(site, middle);
        //std::cout << "i" << i << std::endl;
        do
        {
            site = Sr.rand(0, r);
        } while (RL[site]);
        R[site] = label;
        RL[site] = true;
        N.ChangeDim(site, middle);
        
        label += 1;//std::cout << "i" << i << std::endl;
    }
    
    for (i = 0; i < o; i++)
    {
        middle = Sr.rand(1, 16);
        do
        {
            LorR = Sr.rand(0, 2);
            if ((LorR != 0 && l != 0) || r == 0)
            {
                site = Sr.rand(0, l);
                temp = LL[site];
            }
            else
            {
                site = Sr.rand(0, r);
                temp = RL[site];
            }
        } while (temp);
        O[i] = label;
        M.ChangeDim(i, middle);
        Mb.ChangeDim(i, middle);
        if ((LorR != 0 && l != 0) || r == 0)
        {
            L[site] = label;
            LL[site] = true;
            W.ChangeDim(site, middle);
        }
        else
        {
            R[site] = label;
            RL[site] = true;
            N.ChangeDim(site, middle);
        }
        label += 1;
    }
    for (i = 0; i < extra; i++)
    {
        middle = Sr.rand(1, 16);
        Mb.ChangeDim(i + o, middle);
    }
    
    try
    {
        //std::cout << "checkAndBuild(O, L, R);"  << std::endl;
        con.CheckAndBuild(O, L, R);
        //con.Demo(stdout);
        //C.contraction(W, N, con);
        for (i = 0; i < O.count(); i++)
        {
            if(O[i]!= con.out(i)) 
                std::cout << "O error: " << i << std::endl;
        }
        for (i = 0; i < L.count(); i++)
        {
            if (L[i] != con.left(i))
                std::cout << "L error: " << i << std::endl;
        }
        for (i = 0; i < R.count(); i++)
        {
            if (R[i] != con.right(i))
                std::cout << "R error: " << i << std::endl;
        }
        C.contraction(W, N, con);
        if(!(C == M))
            std::cout << "C != M: " << (int)(C == M) << std::endl;
        if(clear) std::cout << "ba.backward(Mb, con, true);" << std::endl;
        ba.backward(Mb, con, true);
        if (clear) std::cout << "Nb.contraction(W, Mb, ba);" << std::endl;
        Nb.contraction(W, Mb, ba);
        if (Nb.GetOrder() != N.GetOrder() + extra)
            std::cout << "Nb.GetOrder() != N.GetOrder() + extra" << std::endl;
        for (i = 0; i < r; i++)
            if(Nb[i]!= N[i]) std::cout << "Nb[i]!= N[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Nb[i + r] != Mb[i + o]) std::cout << "Nb[i + r] != Mb[i + o]: " << i << std::endl;
        }

        if (clear) std::cout << "ba.backward(Mb, con, false);" << std::endl;
        ba2.backward(Mb, con, false);
        if (clear) std::cout << "Nb.contraction(W, Mb, ba2);" << std::endl;
        Nb2.contraction(Mb, N, ba2);
        if (Nb2.GetOrder() != W.GetOrder() + extra)
        std::cout << "Nb2.GetOrder() != W.GetOrder() + extra" << std::endl;
        for (i = 0; i < l; i++)
            if (Nb2[i] != W[i]) std::cout << "Nb2[i] != W[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Nb2[i + l] != Mb[i + o]) std::cout << "Nb2[i + l] != Mb[i + o]: " << i << std::endl;
        }
    }
    catch (PikaError& E)
    {
        std::cout << "dim output: " << o;
        std::cout << ", dim left: " << l;
        std::cout << ", dim right: " << r;
        std::cout << ", contraction Dim: " << cnDim << std::endl;
        E.show(stderr);
    }
}

int static test01(const parameter& para)
{
    tensor W, N, M, C;
    vector<size_t> O;
    vector<size_t> L;
    vector<size_t> R;

    ContractDesc con;
    W.ChangeOrder(2);
    W.ChangeDim(0, 32);
    W.ChangeDim(1, 64);

    N.ChangeOrder(3);
    N.ChangeDim(0, 15);
    N.ChangeDim(1, 32);
    N.ChangeDim(2, 19);

    M.ChangeOrder(3);
    M.ChangeDim(0, 64);
    M.ChangeDim(1, 19);
    M.ChangeDim(2, 15);

    W.Demo(stdout, "W");
    N.Demo(stdout, "N");
    M.Demo(stdout, "M");
    
    //con.SetDim(M.GetOrder(), W.GetOrder(), N.GetOrder());
    
    L.append(0);
    L.append(1);

    R.append(2);
    R.append(0);
    R.append(3);

    O.append(1);
    O.append(3);
    O.append(2);
    try
    {
        con.CheckAndBuild(O, L, R);
        con.Demo(stdout);
        C.contraction(W, N, con);

    }
    catch (PikaError &E)
    {
        E.show(stderr);
    }
    std::cout << "C == M: " << (int)(C == M) << std::endl;
    return 0;
}
int static test02(const parameter& para)
{
    tensor W, N, M;
    W.ChangeOrder(2);
    try
    {
        W.ChangeDim(5, 0);
    }
    catch (PikaError E)
    {
        
    }
    W.ChangeDim(5, 0);
    return 0;
}

class TestE
{
public:
    TestE(const char* s);
    ~TestE();

private:
    const char* label;
};

TestE::TestE(const char* s)
{
    label = s;
    std::cout << "TestE::TestE(): " << label << std::endl;
}

TestE::~TestE()
{
    std::cout << "TestE::~TestE(): " << label << std::endl;
}
void static throw1(void)
{
    throw TestE("fisrt");
}
void static throw2(void)
{
    try
    {
        throw1();
    }
    catch(TestE&E)
    {
        throw TestE("second");
    }
}


int static test03(const parameter& para)
{
    try
    {
        throw2();
    }
    catch (TestE&E)
    {
        std::cout << "here" << std::endl;
    }

    elementwise E1, E2;
    vector<size_t> L;
    vector<size_t> R;
    vector<size_t> O;
    L.recount(5);
    R.recount(5);
    L[0] = 1;
    L[1] = _uintMax_;
    L[2] = 0;
    L[3] = 2;
    L[4] = _uintMax_;

    R[0] = 0;
    R[1] = 1;
    R[2] = 2;
    R[3] = _uintMax_;
    R[4] = 3;

    try
    {
        std::cout << " E.build(L, R);" << std::endl;
        E1.build(L, R);
    }
    catch (PikaError& E)
    {
        E.show(stdout);
        std::cout << "PikaError& E" << std::endl;
    }


    R[1] = _uintMax_;
    try
    {
        std::cout << " E.build(L, R);" << std::endl;
        E2.build(L, R);
    }
    catch (PikaError& E)
    {
        E.show(stdout);
        std::cout << "PikaError& E" << std::endl;
    }

    L.recount(2);
    R.recount(3);
    O.recount(3);
    L[0] = 0;
    L[1] = 3;

    R[0] = 3;
    R[1] = 1;
    R[2] = 2;
    O[0] = 0;
    O[1] = 1;
    O[2] = 2;

    ContractDesc desc1;
    desc1.CheckAndBuild(O, L, R);
    desc1.Demo(stdout);

    return 0;
}
int static test04(const parameter& para)
{
    size_t l;
    size_t r;
    size_t o;
    size_t extra;
    bool error;
    error = para.option1;
    std::cout << "range: " << para.thread << std::endl;
    if (error)
    {
        std::cout << "testcontract(l, r, o, 0); " << std::endl;
        for (l = 0; l < para.thread; l++)
        {
            std::cout << "l: " << l << std::endl;
            for (r = 0; r < para.thread; r++)
            {
                for (o = 0; o <= l + r; o++)
                {
                    testcontract(l, r, o, 0);
                }
            }
        }
    }
    else
    {
        std::cout << "testcontract(l, r, o, extra); " << std::endl;
        for (l = 0; l < para.thread; l++)
        {
            std::cout << "l: " << l << std::endl;
            for (r = 0; r < para.thread; r++)
            {
                for (o = 0; o <= l + r; o++)
                {
                    for (extra = 0; extra < para.thread; extra++)
                    {
                        testcontract(l, r, o, extra);
                    }
                }
            }
        }
    }
    return 0;
}


void static testDispatch(const size_t from, const size_t to, const size_t extra)
{
    size_t i, cnDim, label, site, LorR, middle;
    vector<size_t> Ii;
    vector<size_t> L;
    vector<size_t> R;
    array<bool> IL;
    array<bool> RL;
    array<bool> LL;

    bool temp, clear;
    HyperAlgebra::SimpleRandom Sr;

    dispatch desc;
    condensation ba;
    condensation dual;
    
    dispatch ba2;
    tensor W, N, M, C, Nb, Mb;

    tensor Nb2, Mb2;

    if (to < from) return;


    
    try
    {
        Ii.recount(to);
        Ii.value(_uintMax_);
        IL.Realloc(to);
        IL.value(false);

        M.ChangeOrder(to);
        N.ChangeOrder(from);
        Mb.ChangeOrder(to + extra);
        for (i = 0; i < to; i++)
        {
            cnDim = Sr.rand(1, 32);
            M.ChangeDim(i, cnDim);
        }
        for (i = to; i < to + extra; i++)
        {
            cnDim = Sr.rand(1, 32);
            Mb.ChangeDim(i, cnDim);
        }
        for (i = 0; i < from; i++)
        {
            do
            {
                label = Sr.rand(0, to);
            } while (IL[label]);
            IL[label] = true;
            Ii[label] = i;
            cnDim = Sr.rand(1, 32);
            M.ChangeDim(label, cnDim);
            N.ChangeDim(i, cnDim);
        }
        for (i = 0; i < to; i++)
        {
            Mb.ChangeDim(i, M[i]);
        }
        W.Set(M);

        desc.build(Ii);
        W.Dispatch(N, desc);
        if (!(W == M))
            std::cout << "W != M: " << (int)(W == M) << std::endl;
        
        dual.backward(M, desc);
        C.Condensation(M, dual);
        if (!(C == N))
            std::cout << "C != N: " << (int)(C == N) << std::endl;
        ba.backward(Mb, desc);
        
        Nb.Condensation(Mb, ba);
        if (Nb.GetOrder() != (from + extra)) std::cout << "Nb.GetOrder() != (from + extra)" << std::endl;
        for (i = 0; i < to; i++)
            if (Mb[i] != M[i]) std::cout << "Mb[i] != M[i]: " << i << std::endl;
        for (i = 0; i < from; i++)
            if (Nb[i] != N[i]) std::cout << "Nb[i]!= N[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Nb[i + from] != Mb[i + to]) std::cout << "Nb[i + from] != Mb[i + to]: " << i << std::endl;
        }

        Nb2.ChangeOrder(from + extra);
        Mb2.ChangeOrder(to + extra);
        for (i = 0; i < from; i++)
        {
            Nb2.ChangeDim(i, N[i]);
        }
        for (i = from; i < from + extra; i++)
        {
            cnDim = Sr.rand(1, 32);
            Nb2.ChangeDim(i, cnDim);
        }

        ba2.backward(Nb2, dual);
        for (i = 0; i < to; i++)
            Mb2.ChangeDim(i, M[i]);
        Mb2.Dispatch(Nb2, ba2);
        for (i = 0; i < to; i++)
            if (Mb2[i] != M[i]) std::cout << "Mb2[i] != M[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Mb2[i + to] != Nb2[i + from]) std::cout << "Mb2[i + to] != Nb2[i + from]: " << i << std::endl;
        }


    }
    catch (PikaError& E)
    {
        //std::cout << "dim output: " << o;
        //std::cout << ", dim left: " << l;
        //std::cout << ", dim right: " << r;
        //std::cout << ", contraction Dim: " << cnDim << std::endl;
        E.show(stderr);
    }
}

int static test05(const parameter& para)
{
    size_t from;
    size_t to;
    size_t extra;
    std::cout << "range: " << para.thread << std::endl;
    for (from = 0; from < para.thread; from++)
    {
        for (to = 0; to < para.thread; to++)
        {
            for (extra = 0; extra < para.thread; extra++)
            {
                testDispatch(from, to + from, extra);
            }
        }
    }
    return 0;
}
void static testelementwise(const size_t l, const size_t r, const size_t o, const size_t extra, const bool clear)
{
    size_t i, cnDim, label, site, LorR, middle;
    vector<size_t> L;
    vector<size_t> R;
    array<bool> RL;
    array<bool> LL;

    bool temp;
    HyperAlgebra::SimpleRandom Sr;

    tensor W, N, M, C, Nb, Mb;
    elementwise desc, ba;
    condensation dual;
    //C = WN
    {

        L.recount(o);
        R.recount(o);

        LL.Realloc(o);
        RL.Realloc(o);

        LL.value(false);
        RL.value(false);

        L.value(_uintMax_);
        R.value(_uintMax_);



        if (clear)std::cout << "dim output: " << o;
        if (clear)std::cout << ", dim left: " << l;
        if (clear)std::cout << ", dim right: " << r;
        if (clear)std::cout << ", extra Dim: " << extra << std::endl;

        if (o > (l + r) || o < l || o < r)
        {
            std::cout << "o > (l + r) || o < l || o < r" << std::endl;
            std::cout << "dim output: " << o;
            std::cout << ", dim left: " << l;
            std::cout << ", dim right: " << r;
            std::cout << ", extra Dim: " << extra << std::endl;
            return;
        }

        label = 0;
    }

    try
    {
        W.ChangeOrder(l);
        N.ChangeOrder(r);
        M.ChangeOrder(o);
        C.ChangeOrder(o);

        Mb.ChangeOrder(o + extra);

        for (i = 0; i < l; i++)
        {
            middle = Sr.rand(1, 16);
            do
            {
                site = Sr.rand(0, o);
            } while (LL[site]);
            L[site] = i;
            LL[site] = true;
            W.ChangeDim(i, middle);
            C.ChangeDim(site, middle);
        }
        label = l;
        for (i = 0; i < r; i++)
        {
            do
            {
                site = Sr.rand(0, o);
            } while (((label < o) && LL[site]) || RL[site]);
            label += 1;
            R[site] = i;
            RL[site] = true;
            if (LL[site])
                middle = W[L[site]];
            else
                middle = Sr.rand(1, 16);
            N.ChangeDim(i, middle);
            C.ChangeDim(site, middle);
        }
        desc.build(L, R);
        M.Elementwise(W, N, desc);
        if (!(C == M))
            std::cout << "C != M: " << (int)(C == M) << std::endl;
        for (i = 0; i < o; i++)
        {
            Mb.ChangeDim(i, M[i]);
        }
        for (i = o; i < o + extra; i++)
        {
            middle = Sr.rand(1, 16);
            Mb.ChangeDim(i, middle);
        }

        dual.backward(Mb, desc, true);
        Nb.Condensation(Mb, dual);
        if(Nb.GetOrder() != l + extra)
            std::cout << "left: Nb.GetOrder() != l + extra" << Nb.GetOrder() << std::endl;
        for (i = 0; i < l; i++)
            if (Nb[i] != W[i]) std::cout << "left: Nb[i]!= W[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Nb[i + l] != Mb[i + o]) std::cout << "left: Nb[i + l] != Mb[i + o]: " << i << std::endl;
        }


        dual.backward(Mb, desc, false);
        Nb.Condensation(Mb, dual);
        if (Nb.GetOrder() != r + extra)
            std::cout << "right: Nb.GetOrder() != r + extra" << std::endl;
        for (i = 0; i < r; i++)
            if (Nb[i] != N[i]) std::cout << "right: Nb[i]!= N[i]: " << i << std::endl;
        for (i = 0; i < extra; i++)
        {
            if (Nb[i + r] != Mb[i + o]) std::cout << "right: Nb[i + r] != Mb[i + o]: " << i << std::endl;
        }

        ba.backward(Mb, desc, true);
        C.Elementwise(Mb, N, ba);
        if (!(C == Mb))
            std::cout << "left: C != Mb: " << (int)(C == Mb) << std::endl;

        ba.backward(Mb, desc, false);
        C.Elementwise(Mb, W, ba);
        if (!(C == Mb))
            std::cout << "right: C != Mb: " << (int)(C == Mb) << std::endl;
    }
    catch (PikaError& E)
    {
        std::cout << "dim output: " << o;
        std::cout << ", dim left: " << l;
        std::cout << ", dim right: " << r;
        std::cout << ", extra Dim: " << extra << std::endl;
        E.show(stdout);
    }
   
}
int static test06(const parameter& para)
{
    size_t l;
    size_t r;
    size_t o;
    size_t extra;
    std::cout << "range: " << para.thread << std::endl;

    for (l = 0; l < para.thread; l++)
    {
        std::cout << "l: " << l << std::endl;
        for (r = 0; r < para.thread; r++)
        {
            //std::cout << "r: " << r << std::endl;
            for (o = (l < r ? r : l); o <= l + r; o++)
            {
                for (extra = 0; extra < para.thread; extra++)
                {
                    testelementwise(l, r, o, extra, para.option1);
                }
            }
        }
    }
    return 0;
}
int static test07(const parameter& para)
{
    Activation Af, d1,d2;
    PikaString out;
    std::cout << "Af.Example01(); "<< std::endl;
    Af.Example01();
    std::cout << "Af.Demo(stdout);: " << std::endl;
    Af.Demo(out);
    std::cout << "output: " << out.array() << std::endl;
    out.clear();
    std::cout << "d1.copy(Af);; " << std::endl;
    d1.copy(Af);
    d1.Demo(out);
    std::cout << "d1: " << out.array() << std::endl;
    out.clear();

    std::cout << "d1.differetial(Af); " << std::endl;
    d1.differetial();
    std::cout << "d1.Demo(out); " << std::endl;
    d1.Demo(out);
    std::cout << "d1: " << out.array() << std::endl;
    return 0;
}
int static test08(const parameter& para)
{
    Activation Af;
    PikaString out;
    Activation* former, now;
    VISA1 program;
    size_t i;
    Af.Example01();
    Af.Demo(out);
    std::cout << "Example01(): " << out.array() << std::endl;
    out.clear();
    former = new Activation();
    former->copy(Af);
    for (i = 0; i < para.thread; i++)
    {
        now.differetial(*former);
        now.Demo(out);
        std::cout << "differetial(" << i + 1 <<"): " << out.array() << std::endl;
        //std::cout << "graph(" << i + 1 << "): " << std::endl;
        //now.Demo(stdout);
        out.clear();

        now.Simplify();
        now.Demo(out);
        std::cout << "Simplify(" << i + 1 << "): " << out.array() << std::endl;
        out.clear();
        
        now.PrintForward(program);
        program.Demo(stdout);
        program.clear();


        former->copy(now);
    }

    return 0;
}
int static test09(const parameter& para)
{
    expression Af;
    PikaString out;
    expression* former, now;
    VISA1 program;
    vector<size_t> FreeReg;
    size_t i;
    Af.Example(1);
    Af.Demo(out, true, 0);
    std::cout << "Example01(): " << out.array() << std::endl;
    out.clear();
    former = new expression();
    former->copy(Af);
    for (i = 0; i < para.thread; i++)
    {
        now.copy(*former);
        now.differetial(0, 0, true);
        now.Demo(out, true, 0);
        std::cout << "differetial(" << i + 1 << "): " << out.array() << std::endl;
        //std::cout << "graph(" << i + 1 << "): " << std::endl;
        //now.Demo(stdout);
        out.clear();
        now.Simplify();
        now.Demo(out, true, 0);
        std::cout << "Simplify(" << i + 1 << "): " << out.array() << std::endl;
        out.clear();

        std::cout << "now.PrintForwardMiniOp(program);==========================" << std::endl;
        now.PrintForwardMiniOp(program, FreeReg);
        FreeReg.clear();
        program.Demo(stdout);
        program.clear();
        std::cout << "now.PrintForwardMiniReg(program);==========================" << std::endl;
        now.PrintForwardMiniReg(program, FreeReg);
        FreeReg.clear();
        program.Demo(stdout);
        program.clear();

        former->copy(now);
    }

    return 0;
    return 0;
}
void static testsymbolic(activation& Af, const double delta, bool print)
{
    vector<double> parameter;
    vector<double> output;
    vector<double*> input;
    double x, error, temp, y1, y2, X;
    HyperAlgebra::SimpleRandom Sr;
    activation now;
    size_t i;
    VISA1 F,f;
    parameter.recount(Af.ParameterAmount());
    output.recount(Af.OutputAmount());
    input.recount(1);
    input[0] = &x;

    for (i = 0; i < parameter.count(); i++)
    {
        parameter[i] = Sr.rand(-1.0, 1.0);
    }
    error = 0;
    
    now.Copy(Af);

    now.Differetial();
    now.Simplify();
    Af.PrintForward(F);
    now.PrintForward(f);

    error = 0.0;

    for (i = 0; i < 1024; i++)
    {
        X = Sr.rand(-1.0, 1.0);
        x = X + delta;
        F.compute(input.array(), parameter.array(), output.array());
        y1 = output[0];

        x = X - delta;
        F.compute(input.array(), parameter.array(), output.array());
        y2 = output[0];
        
        x = X;
        f.compute(input.array(), parameter.array(), output.array());
        temp = std::fabs((y1 - y2) * 0.5 / delta - output[0]);

        error = error > temp ? error : temp;
        if (print)
        {
            std::cout << "X: " << X << ", y1: " << y1 << ", y2: " << y2 << ", Numer: ";
            std::cout << (y1 - y2) * 0.5 / delta << ", output[0]" << output[0] << std::endl;
        }
    }

    std::cout << "error: " << error << std::endl;
}
int static test10(const parameter& para)
{
    activation Af;
    PikaString out;
    activation* former, now;
    VISA1 program;
    vector<size_t> FreeReg;
    size_t i;
    
    Af.Example(para.option2);

    Af.Demo(out);
    std::cout << "Example("<< para.option2 <<"): " << out.array() << std::endl;
    
    out.clear();
    former = new activation();
    former->copy(Af);
    for (i = 0; i < para.thread; i++)
    {
        now.copy(*former);
        now.Differetial();
        now.Demo(out);
        std::cout << "differetial(" << i + 1 << "): " << out.array() << std::endl;

        
        testsymbolic(*former, 1.0E-6, para.option1);
        out.clear();
        now.Simplify();
        now.Demo(out);
        std::cout << "Simplify(" << i + 1 << "): " << out.array() << std::endl;
        out.clear();

        std::cout << "now.PrintForwardMiniOp(program);==========================" << std::endl;
        now.PrintForwardMiniOp(program, FreeReg);
        FreeReg.clear();
        program.Demo(stdout);
        program.clear();
        std::cout << "now.PrintBackwardiniReg(program);==========================" << std::endl;
        now.PrintBackward(program);
        program.Demo(stdout);
        program.clear();
        former->copy(now);
    }

    return 0;
}
void static testbackward(activation& Af, const double delta, bool print)
{
    if (Af.ParameterAmount() == 0)return;
    vector<double> parameter;
    vector<double> y1, y2;
    vector<double*> input;
    double x, error, temp, X;
    HyperAlgebra::SimpleRandom Sr;
    activation back, now;
    size_t i, j;
    VISA1 B;
    vector<VISA1*> F;
    PikaString out;
    expression Bt;
    parameter.recount(Af.ParameterAmount());
    y1.recount(Af.ParameterAmount());
    y2.recount(Af.ParameterAmount());
    input.recount(2);
    input[0] = &x;
    input[1] = &X;

    for (i = 0; i < parameter.count(); i++)
    {
        parameter[i] = Sr.rand(-1.0, 1.0);
    }
    error = 0;

    Bt.copy(Af);
    Bt.ParameterBackward(0);
    for (i = 0; i < parameter.count(); i++)
    {
        Bt.Demo(out, false, i);
        std::cout << "ParameterBackward(" << i << "): " << out.array() << std::endl;
        out.clear();
    }
    Bt.Simplify();
    for (i = 0; i < parameter.count(); i++)
    {
        Bt.Demo(out, false, i);
        std::cout << "Simplify(" << i << "): " << out.array() << std::endl;
        out.clear();
    }

    back.Copy(Af);
    back.ParameterBackward(B);
    std::cout << "B.Demo(stdout);" << std::endl;
    B.Demo(stdout);

    F.recount(parameter.count());
    for (i = 0; i < parameter.count(); i++)
    {
        now.Copy(Af);
        now.differetial(0, i, false);
        now.Demo(out);
        std::cout << "differetial(" << i << "): " << out.array() << std::endl;
        out.clear();

        now.Simplify();
        now.Demo(out);
        std::cout << "Simplify(" << i << "): " << out.array() << std::endl;
        out.clear();

        F[i] = new VISA1();
        now.PrintBackward(*(F[i]));
        F[i]->Demo(stdout);
    }

    error = 0.0;

    for (i = 0; i < 1024; i++)
    {
        X = Sr.rand(-1.0, 1.0);
        X = Sr.rand(-1.0, 1.0);
        B.compute(input.array(), parameter.array(), y1.array());
        for (j = 0; j < parameter.count(); j++)
            F[j]->compute(input.array(), parameter.array(), y2.array() + j);
        for (j = 0; j < parameter.count(); j++)
        {
            temp = std::fabs(y1[j] - y2[j]);
            error = error > temp ? error : temp;
        }

        
        if (print)
        {
            std::cout << "X: " << X << ", x: " << x << std::endl;
            for (j = 0; j < parameter.count(); j++)
            {
                std::cout << "y1: " << y1[j] << ", y2: " << y2[j] << std::endl;
            }
            
        }
    }
    std::cout << "===========================error: " << error << std::endl;
    for (i = 0; i < parameter.count(); i++) delete F[i];
}
int static test11(const parameter& para)
{
    activation Af;
    PikaString out;
    activation* former, now;
    VISA1 program;
    vector<size_t> FreeReg;
    size_t i;

    Af.Example(para.option2);

    Af.Demo(out);
    std::cout << "Example(" << para.option2 << "): " << out.array() << std::endl;

    out.clear();
    former = new activation();
    former->copy(Af);
    for (i = 0; i < para.thread; i++)
    {
        now.copy(*former);
        now.Differetial();
        now.Simplify();
        now.Demo(out);
        std::cout << "differetial(" << i + 1 << "): " << out.array() << std::endl;
        out.clear();

        testbackward(*former, 1.0E-6, para.option1);
        former->copy(now);
    }

    return 0;
}
void static testsymbolic(activation& Af, const double delta, bool print, double lower, double upper)
{
    vector<double> parameter;
    vector<double> output;
    vector<double*> input;
    double x, error, temp, temp2, y1, y2, X, f_out, b_out;
    double record1, record2;
    double recordb1, recordb2, error2;
    HyperAlgebra::SimpleRandom Sr;
    activation now;
    activation back;
    size_t i;
    VISA1 F, f;
    VISA1 B;
    parameter.recount(Af.ParameterAmount());
    output.recount(Af.OutputAmount());
    input.recount(1);
    input[0] = &x;

    for (i = 0; i < parameter.count(); i++)
    {
        parameter[i] = Sr.rand(lower, upper);
    }
    error = 0;

    now.Copy(Af);
    now.Differetial();
    now.Simplify();
    back.Copy(Af);
    back.Differetial();
    back.Simplify();

    Af.PrintForward(F);
    now.PrintForward(f);
    back.PrintForward(B);

    error = 0.0;
    record1 = 0.0;
    record2 = 0.0;

    error2 = 0.0;
    recordb1 = 0.0;
    recordb2 = 0.0;
    for (i = 0; i < 1024; i++)
    {
        X = Sr.rand(lower, upper);
        x = X + delta;
        F.compute(input.array(), parameter.array(), output.array());
        y1 = output[0];

        x = X - delta;
        F.compute(input.array(), parameter.array(), output.array());
        y2 = output[0];

        x = X;
        f.compute(input.array(), parameter.array(), output.array());
        f_out = output[0];
        temp = std::fabs((y1 - y2) * 0.5 / delta - f_out);

        B.compute(input.array(), parameter.array(), output.array());
        b_out = output[0];
        temp2 = std::fabs(b_out - f_out);


        record1 = error > temp ? y1 : record1;
        record2 = error > temp ? y2 : record2;
        error = error > temp ? error : temp;

        recordb1 = error2 > temp2 ? y1 : recordb1;
        recordb2 = error2 > temp2 ? y2 : recordb2;
        error2 = error2 > temp2 ? error2 : temp2;

        if (print)
        {
            std::cout << "X: " << X << ", y1: " << y1 << ", y2: " << y2 << ", Numer: ";
            std::cout << (y1 - y2) * 0.5 / delta << ", output[0]" << output[0] << std::endl;
        }
    }
    std::cout << "\terror 1: " << error;
    std::cout << ", record1: " << record1;
    std::cout << ", record2: " << record2 << std::endl;

    std::cout << "\terror 2: " << error2;
    std::cout << ", recordb1: " << recordb1;
    std::cout << ", recordb2: " << recordb2 << std::endl;
}
void test_forward_all(size_t No, const parameter& para)
{
    activation Af;
    PikaString out;
    activation* former, now;
    VISA1 program;
    vector<size_t> FreeReg;
    size_t i;
    Af.Example(No);

    Af.Demo(out);
    std::cout << "Example(" << No << "): " << out.array() << std::endl;

    out.clear();
    former = new activation();
    former->copy(Af);
    for (i = 0; i < para.thread; i++)
    {
        now.copy(*former);
        now.Differetial();

        testsymbolic(*former, 1.0E-6, para.option1, 1.0, 2.0);
        out.clear();
        now.Simplify();

        // std::cout << "now.PrintForwardMiniOp(program);==========================" << std::endl;
        now.PrintForwardMiniOp(program, FreeReg);
        FreeReg.clear();
        //program.Demo(stdout);
        program.clear();
        //std::cout << "now.PrintBackwardiniReg(program);==========================" << std::endl;
        now.PrintBackward(program);
        // program.Demo(stdout);
        program.clear();
        former->copy(now);
    }

}
int static test12(const parameter& para)
{
    activation Af;
    PikaString out;
    activation* former, now;
    VISA1 program;
    vector<size_t> FreeReg;
    size_t i, kk;
    for (kk = 0; kk < para.option2; kk++)
    {
        test_forward_all(kk, para);
    }
    
    return 0;
}
int static test13(const parameter& para)
{
    CFile output, input;
    hyperlex::BufferChar bc;
    size_t i, j;
    size_t row, col;
    vector<double> temp;
    output.OpenWritePlus("./data/mat_3_3");
    fprintf(output.fp, "\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf(output.fp, " %+25.16E ", (double)(i * 3 + j) * 0.25);
        }
        fprintf(output.fp, "\n");
    }
    output.close();
    input.OpenRead("./data/mat_3_3");
    matrixGet(input.fp, temp, row, col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf(" %+25.16E ", temp[i * 3 + j]);
        }
        printf("\n");
    }
    return 0;
}
int static test14(const parameter& para)
{
    try
    {
        Expres Exp;
        hyperlex::BufferChar BC;
        Exp.Example(0);
        Exp.demo(stdout);
        Exp.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl;
    }
    catch (Pikachu::PikaError& E)
    {
        std::cout << "test14: " << std::endl;
        E.show(stderr);
        throw PikaError("test14", "???", 0);
        
    }
    
    return 0;
}
int static test15(const parameter& para)
{
    return 0;
}
int static test16(const parameter& para)
{
    return 0;
}




#include <string.h>
static char* CopyMalloc(const char* s)
{
    char* v;
    size_t size;
    size = strlen(s);
    v = (char*)malloc(sizeof(char) * (size + 4));
    strcpy(v, s);
    return v;
}
std::string static path_add_file_name(const std::string& path, const std::string& name)
{
    std::string fusion;
    if (path[path.length() - 1] == '/')
        fusion = path + name;
    else
        fusion = path + '/' + name;
    return fusion;
}
















int static if_letter_judge(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool static true_false_judge(const char* c_t_f)
{
    int i;
    for (i = 0; c_t_f[i] != '\0'; i++)
        if (if_letter_judge(c_t_f[i]))
            return c_t_f[i] == 'y' || c_t_f[i] == 'Y' || c_t_f[i] == 't' || c_t_f[i] == 'T';
    return false;
}

CFile::CFile()
{
    fp = NULL;
}
CFile::~CFile()
{
    close();
}
void CFile::close(void)
{
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
}
void CFile::Open(const char* name, const char* mode)
{
    int error;
#ifdef  _WIN64
    errno = 0;
    error = fopen_s(&fp, name, mode);
    if (error != 0)
    {
        fprintf(stderr, "WARNING: FAILURE OPEN:%s, errno_t:%d\n", name, error);
        fp = NULL;
    }
#else
    fp = fopen(name, mode);
    if (fp == NULL)
        fprintf(stderr, "WARNING: FAILURE OPEN:%s\n", name);
    //fprintf(stderr, "WARNING: FAILURE OPEN:%s, Error no.%d: %s\n", name, errno, strerror(errno));
#endif
    //ExitWarning((fp == NULL), stderr);
    return;
}
void CFile::OpenRead(const char* name)
{
    Open(name, "r");
}
void CFile::OpenWriteAtRear(const char* name)
{
    Open(name, "a+");
}
void CFile::OpenWritePlus(const char* name)
{
    Open(name, "w+");
}
std::string CFile::FusePathAndName(const std::string& path, const std::string& name)
{
    std::string fusion;
    if (path[path.length() - 1] == '/')
        fusion = path + name;
    else
        fusion = path + '/' + name;
    return fusion;
}
std::string CFile::FusePathAndName(const char* path, const std::string& name)
{
    std::string PPP;
    PPP = path;
    return FusePathAndName(PPP, name);
}
std::string CFile::ChangeSuffix(const std::string& file, const char* new_one)
{
    size_t i, j;
    std::string name;
    name = "";
    for (i = file.length(); i != 0; i--)
        if (file[i - 1] == '.') break;
    if (i == 0)
    {
        name = file;
        name += '.';
    }
    else
    {
        for (j = 0; j < i; j++)
            name += file[j];
    }
    if (new_one[0] == '.') name += (new_one + 1);
    else name += new_one;
    return name;
}
