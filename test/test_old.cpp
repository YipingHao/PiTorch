#include"extern.h"
#include<cmath>
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif




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






int test_entrance_old(const char* output_path)
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
        default:
            info = test_extern(para, item);
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

int static test14(const parameter& para);
int static test15(const parameter& para);
int static test16(const parameter& para);
int test_extern(const parameter& para, int item)
{
    int info;
    try
    {
        switch (item)
        {
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
            info = test16(para);
            break;
        }
    }
    catch (hyperlex::dictionary* error)
    {
        error->print(stdout);

    }
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

    if (option1)
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
            if (O[i] != con.out(i))
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
        if (!(C == M))
            std::cout << "C != M: " << (int)(C == M) << std::endl;
        if (clear) std::cout << "ba.backward(Mb, con, true);" << std::endl;
        ba.backward(Mb, con, true);
        if (clear) std::cout << "Nb.contraction(W, Mb, ba);" << std::endl;
        Nb.contraction(W, Mb, ba);
        if (Nb.GetOrder() != N.GetOrder() + extra)
            std::cout << "Nb.GetOrder() != N.GetOrder() + extra" << std::endl;
        for (i = 0; i < r; i++)
            if (Nb[i] != N[i]) std::cout << "Nb[i]!= N[i]: " << i << std::endl;
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
    catch (PikaError& E)
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
    catch (TestE& E)
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
    catch (TestE& E)
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
        if (Nb.GetOrder() != l + extra)
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
    Activation Af, d1, d2;
    PikaString out;
    std::cout << "Af.Example01(); " << std::endl;
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
        std::cout << "differetial(" << i + 1 << "): " << out.array() << std::endl;
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
    VISA1 F, f;
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
    std::cout << "Example(" << para.option2 << "): " << out.array() << std::endl;

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






////========================












static void testsymbolic(ActivFunc& Af, const double delta, bool print, double lower, double upper)
{
    vector<double> parameter;
    vector<double> output;
    vector<double*> input;
    double x, error, temp, temp2, y1, y2, X, f_out, b_out;
    double record1, record2;
    double recordb1, recordb2, error2;
    HyperAlgebra::SimpleRandom Sr;
    ActivFunc now;
    ActivFunc back;
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
int static test14(const parameter& para)
{
    ActivFunc Exp;
    ActivFunc Diff;
    hyperlex::BufferChar BC;
    try
    {
        Exp.Example(3);
        Exp.demo(stdout);
        Exp.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();

        Diff.copy(Exp);
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();

        Diff.differetial(0, 0, true);
        std::cout << "Diff.differetial(0, 0, true);" << std::endl;
        //Diff.demo(stdout);
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Diff.demo(stdout);
        std::cout << "Diff.Simplify();====================" << std::endl;
        Diff.Simplify();
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        //Diff.demo(BC, true, 0);

        Diff.demo(stdout);
        Diff.differetial(0, 0, true);
        std::cout << "Diff.differetial(0, 0, true);" << std::endl;
        //Diff.demo(stdout);
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Diff.Simplify();
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        //Diff.demo(BC, true, 0);
        //return 0;
        Diff.differetial(0, 0, true);
        std::cout << "Diff.differetial(0, 0, true);" << std::endl;
        //Diff.demo(stdout);
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Diff.Simplify();
        Diff.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();

        std::cout << "Exp.example(\"exp(-x * x)\");";
        std::cout << Exp.example("exp(-x * x)") << std::endl;
        Exp.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Exp.demo(stdout);

        size_t i, j;
        for (i = 0; i < 10; i++)
        {
            std::cout << "=========================Exp.Example(";
            std::cout << i;
            std::cout << ")=========================" << std::endl;
            Exp.Example(i + 1);
            Exp.demo(BC, true, 0);

            std::cout << BC.ptr() << std::endl; BC.clear();
            for (j = 0; j < 4; j++)
            {
                std::cout << "Differetial(";
                std::cout << j;
                std::cout << "):" << std::endl;
                Exp.Differetial();
                Exp.demo(BC, true, 0);
                std::cout << '\t' << BC.ptr() << std::endl; BC.clear();
                //if (i == 8) Exp.demo(stdout);
                Exp.Simplify();
                Exp.demo(BC, true, 0);
                std::cout << '\t' << BC.ptr() << std::endl; BC.clear();
            }
        }
        for (i = 0; i < 10; i++)
        {
            std::cout << "=========================Exp.Example(";
            std::cout << i;
            std::cout << ")=========================" << std::endl;
            Exp.Example(i + 1);
            Exp.demo(BC, true, 0);
            std::cout << BC.ptr() << std::endl; BC.clear();
            for (j = 0; j < 4; j++)
            {
                Exp.Differetial();
                Exp.Simplify();
                testsymbolic(Exp, 1.0E-7, false, 1.0, 2.0);
            }
        }



    }
    catch (hyperlex::dictionary* Error)
    {
        Error->print(stderr);
        delete Error;
    }
    std::cout << "hyperlex::dictionary dick;" << std::endl;
    hyperlex::dictionary dick;
    dick.append("haha", true);
    std::cout << "hyperlex::dictionary dick;" << std::endl;
    dick.append("ne2", (long int)-123);
    std::cout << "hyperlex::dictionary dick;" << std::endl;
    dick.append("ne3", -4.5);
    std::cout << "hyperlex::dictionary dick;" << std::endl;
    dick.append("bb32", "NoNo");
    std::cout << "hyperlex::dictionary dick;" << std::endl;
    dick.print(stdout);
    try
    {
        ActivFunc Ac;
        std::string ss;
        ss = "funct gauss (input x, para w[5])\n";
        ss += "{\n\tdef y;\n\tdef z;\n";
        ss += "\tw[4] = x;\n";
        ss += "\ty = (w[0] + x * w[1] + x * x * w[2]);\n";
        ss += "\ty = y + (x * x * x * w[3] + x * x * x * x * w[4]);\n";
        ss += "\tz = exp(x*x);\n";
        ss += "\treturn y * z;\n}\n";
        std::cout << ss << std::endl;
        std::cout << "error: " << Ac.construct(ss.c_str()) << std::endl;;
        Ac.demo(stdout);
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Ac.differetial(0, 0, true);
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Ac.Simplify();
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
    }
    catch (hyperlex::dictionary* Error)
    {
        Error->print(stderr);
        delete Error;
    }
    try
    {
        ActivFunc Ac;
        std::string ss;
        ss = "func gauss (input x, para w[5], output o)\n";
        ss += "{\n\tdef y;\n\tdef z;\n";
        ss += "\t//w[4] = x;\n";
        ss += "\ty = (w[0] + x * w[1] + x * x * w[2]);\n";
        ss += "\ty = y + (x * x * x * w[3] + x * x * x * x * w[4]);\n";
        ss += "\tz = exp(x*x);\n";
        ss += "\to = y * z;\n}\n";
        std::cout << ss << std::endl;//
        Ac.build(ss.c_str());
        Ac.demo(stdout);
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Ac.differetial(0, 0, true);
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
        Ac.Simplify();
        Ac.demo(BC, true, 0);
        std::cout << BC.ptr() << std::endl; BC.clear();
    }
    catch (hyperlex::dictionary* Error)
    {
        Error->print(stderr);
        delete Error;
    }
    return 0;
}

struct SwifLexer
{
    enum regular
    {
        _id_ = 1,
        _integer_ = 2,
        _switch_ = 3,
        _enum_ = 4,
        _case_ = 5,
        _break_ = 6,
        _spaces_ = 7,
        _enters_ = 8,
        _tab_ = 9,
        _semicolon_ = 10,
        _colon_ = 11,
        _dot_ = 12,
        _comma_ = 13,
        _braceL_ = 14,
        _braceR_ = 15,
        _left_ = 16,
        _right_ = 17,
        _squareL_ = 18,
        _squareR_ = 19,
        _angleL_ = 20,
        _angleR_ = 21,
        _anntationS_ = 22,
        _anntationM_ = 23,
        _value_ = 24
    };
    enum group
    {
        _id___ = 1,
        _number___ = 2,
        _reserved___ = 3,
        _format___ = 4,
        _division___ = 5,
        _braket___ = 6,
        _anntation___ = 7,
        _value___ = 8
    };
    static int next(int state, const char c);
    static int action(int state);
    static int GroupGet(int state);
};
struct SwifPraser
{
    enum type
    {
        accept = 0,
        error = 1,
        push = 2,
        reduce = 3
    };
    enum rules
    {
        all_all_ = 0,
        ENUM_ENUM_ = 1,
        ITEMS_single_ = 2,
        ITEMS_multi_ = 3,
        //[division]_semicolon_ = 4,
        //[division]_colon_ = 5,
        //[division]_dot_ = 6,
        //[division]_comma_ = 7,
        ITEM_single_ = 8,
        ITEM_multi_ = 9,
        DN_null_ = 10,
        DN_ddd_ = 11
    };
    enum nonterminal
    {
        _all_ = 0,
        _ENUM_ = 1,
        _ITEMS_ = 2,
        //_[division]_ = 3,
        _ITEM_ = 4,
        _DN_ = 5
    };
    static const size_t StateCount;
    static const size_t NonTerminalCount;
    static const size_t TerminalCount;
    static const size_t RulesCount;
    static const int GOTO[20][6];
    static const int ACTION[20][25];
    static const int RulesToSymbol[12];
    static const int RulesLength[12];
    static const char* const RulesName[12];
    static const int Implicit[12];
};


int static LPMorpheneBuild(const char* source, hyperlex::Morpheme& eme);
int static test15(const parameter& para)
{
    int error;
    hyperlex::Morpheme eme;
    hyperlex::GrammarTree Tree;
    CFile input;
    hyperlex::BufferChar BC;
    GTIter iterator;
    GLTree* GT;
    SwifPraser::rules RRR;
    size_t i;
    std::string  sss;
    const char* key;
    input.OpenRead("./data/key.txt");
    BC << input.fp;

    error = LPMorpheneBuild(BC.ptr(), eme);
    std::cout << "input" << BC.ptr() << std::endl;
    if (error != 0)
    {
        std::cout << "error" << error << std::endl;
        return error;
    }
    eme.Demo(stdout);
    error = Tree.build<SwifPraser>(eme);
    if (error != 0)
    {
        std::cout << "error" << error << std::endl;
        return error;
    }
    Tree.Demo(stdout, eme, SwifPraser::RulesName);
    std::cout << "Tree.Demo(stdout, eme, SwifPraser::RulesName);" << std::endl;

    iterator.initial(Tree.GT);
    while (iterator.still())
    {
        GT = iterator.target();
        RRR = (SwifPraser::rules)GT->root().site;
        if (iterator.state() == 0 && GT->root().rules)
        {

            //printf("site:%zu, accept %d\n");
            switch (RRR)
            {
            case SwifPraser::ENUM_ENUM_:
                sss = eme.GetWord(GT->child(1)->root().site);
                break;
            }
        }
        if (iterator.state() != 0 && GT->root().rules)
        {
            //printf("site:%zu, accept %d\n");
            switch (RRR)
            {
            case SwifPraser::ITEM_single_:
            case SwifPraser::ITEM_multi_:
                key = eme.GetWord(GT->child(0)->root().site);
                printf("\tstate[(size_t)%s::%s] = (int)_%s_::%s;\n", sss.c_str(), key, sss.c_str(), key);
                break;
            }
        }
        iterator.next();
    }
    return 0;
}
struct AA
{
    int aa;
    AA() { aa = 0; }
    inline void demo(FILE* fp = stdout) const
    {
        fprintf(fp, "here: %d\n", aa);
    }
    inline void value(int a)
    {
        aa = a;
    }
};
template <class T> class trial
{
    T a;
    T b;
public:
    inline void value(int cc)
    {
        a.value(cc);
        b.value(cc);
    }
    inline void demo(FILE* fp = stdout)
    {
        a.demo(fp);
        b.demo(fp);
    }
};
template <class T> class Recur
{
protected:
    T* ww;

};
struct recur : public Recur<recur>
{
    int aa;
    recur() { aa = 0; bb = 0; }
    inline void demo(FILE* fp = stdout) const
    {
        fprintf(fp, "here: %d\n", aa);
        fprintf(fp, "sizeof(recur): %d\n", (int)sizeof(recur));
    }
    inline void value(int a)
    {
        aa = a;
        ww = this;
    }
    int bb;
};
int static test16(const parameter& para)
{
    trial<AA> here;
    here.value(12);
    here.demo();
    recur done;
    done.value(12);
    done.demo();

    hyperlex::dictionary error;
    for (size_t i = 0; i < 16; i++)
    {
        error.append("here", i);
    }
    error.print(stdout);

    return 0;
}


int static LPMorpheneBuild(const char* source, hyperlex::Morpheme& eme)
{
    int error;
    size_t i;
    SwifLexer::regular T;
    SwifLexer::group G;
    error = eme.Build<SwifLexer>(source);
    if (error != 0)
    {
        //errorCode = ErrorinputLEXICAL;
        return error;
    }
    for (i = 0; i < eme.GetCount(); i++)
    {
        T = (SwifLexer::regular)(eme[i].accept);
        G = (SwifLexer::group)(eme[i].category);
        if (G == SwifLexer::_format___ || G == SwifLexer::_anntation___)
        {
            eme.valid(i) = false;
        }
    }
    return 0;
}

int SwifLexer::next(int state, const char c)
{
    switch (state)
    {
    case 0:
        if (c == (char)9) return 9;
        else if (c == (char)10) return 8;
        else if (c == ' ') return 7;
        else if (c == '(') return 16;
        else if (c == ')') return 17;
        else if (c == '+') return 25;
        else if (c == ',') return 13;
        else if (c == '-') return 25;
        else if (c == '.') return 12;
        else if (c == '/') return 42;
        else if ('0' <= c && c <= '9') return 2;
        else if (c == ':') return 11;
        else if (c == ';') return 10;
        else if (c == '<') return 20;
        else if (c == '=') return 24;
        else if (c == '>') return 21;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '[') return 18;
        else if (c == ']') return 19;
        else if (c == '_') return 1;
        else if (c == 'a') return 1;
        else if (c == 'b') return 33;
        else if (c == 'c') return 35;
        else if (c == 'd') return 1;
        else if (c == 'e') return 39;
        else if ('f' <= c && c <= 'r') return 1;
        else if (c == 's') return 40;
        else if ('t' <= c && c <= 'z') return 1;
        else if (c == '{') return 14;
        else if (c == '}') return 15;
        else return 0;
    case 1:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'z') return 1;
        else return 0;
    case 2:
        if ('0' <= c && c <= '9') return 2;
        else return 0;
    case 3:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'z') return 1;
        else return 0;
    case 4:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'z') return 1;
        else return 0;
    case 5:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'z') return 1;
        else return 0;
    case 6:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'z') return 1;
        else return 0;
    case 7:
        if (c == ' ') return 7;
        else return 0;
    case 8:
        if (c == (char)10) return 8;
        else return 0;
    case 9:
        return 0;
    case 10:
        return 0;
    case 11:
        return 0;
    case 12:
        return 0;
    case 13:
        return 0;
    case 14:
        return 0;
    case 15:
        return 0;
    case 16:
        return 0;
    case 17:
        return 0;
    case 18:
        return 0;
    case 19:
        return 0;
    case 20:
        return 0;
    case 21:
        return 0;
    case 22:
        return 0;
    case 23:
        if ((char)0 <= c && c <= ')') return 41;
        else if (c == '*') return 44;
        else if ('+' <= c && c <= (char)127) return 41;
        else return 0;
    case 24:
        return 0;
    case 25:
        if ('0' <= c && c <= '9') return 2;
        else return 0;
    case 26:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'd') return 1;
        else if (c == 'e') return 5;
        else if ('f' <= c && c <= 'z') return 1;
        else return 0;
    case 27:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'g') return 1;
        else if (c == 'h') return 3;
        else if ('i' <= c && c <= 'z') return 1;
        else return 0;
    case 28:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'b') return 1;
        else if (c == 'c') return 27;
        else if ('d' <= c && c <= 'z') return 1;
        else return 0;
    case 29:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'j') return 1;
        else if (c == 'k') return 6;
        else if ('l' <= c && c <= 'z') return 1;
        else return 0;
    case 30:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if (c == 'a') return 29;
        else if ('b' <= c && c <= 'z') return 1;
        else return 0;
    case 31:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'd') return 1;
        else if (c == 'e') return 30;
        else if ('f' <= c && c <= 'z') return 1;
        else return 0;
    case 32:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'l') return 1;
        else if (c == 'm') return 4;
        else if ('n' <= c && c <= 'z') return 1;
        else return 0;
    case 33:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'q') return 1;
        else if (c == 'r') return 31;
        else if ('s' <= c && c <= 'z') return 1;
        else return 0;
    case 34:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'r') return 1;
        else if (c == 's') return 26;
        else if ('t' <= c && c <= 'z') return 1;
        else return 0;
    case 35:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if (c == 'a') return 34;
        else if ('b' <= c && c <= 'z') return 1;
        else return 0;
    case 36:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 's') return 1;
        else if (c == 't') return 28;
        else if ('u' <= c && c <= 'z') return 1;
        else return 0;
    case 37:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'h') return 1;
        else if (c == 'i') return 36;
        else if ('j' <= c && c <= 'z') return 1;
        else return 0;
    case 38:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 't') return 1;
        else if (c == 'u') return 32;
        else if ('v' <= c && c <= 'z') return 1;
        else return 0;
    case 39:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'm') return 1;
        else if (c == 'n') return 38;
        else if ('o' <= c && c <= 'z') return 1;
        else return 0;
    case 40:
        if ('0' <= c && c <= '9') return 1;
        else if ('A' <= c && c <= 'Z') return 1;
        else if (c == '_') return 1;
        else if ('a' <= c && c <= 'v') return 1;
        else if (c == 'w') return 37;
        else if ('x' <= c && c <= 'z') return 1;
        else return 0;
    case 41:
        if ((char)0 <= c && c <= ')') return 41;
        else if (c == '*') return 44;
        else if ('+' <= c && c <= (char)127) return 41;
        else return 0;
    case 42:
        if (c == '*') return 41;
        else if (c == '/') return 43;
        else return 0;
    case 43:
        if ((char)0 <= c && c <= (char)9) return 43;
        else if (c == (char)10) return 22;
        else if ((char)11 <= c && c <= (char)127) return 43;
        else return 0;
    case 44:
        if ((char)0 <= c && c <= ')') return 41;
        else if (c == '*') return 44;
        else if ('+' <= c && c <= '.') return 41;
        else if (c == '/') return 23;
        else if ('0' <= c && c <= (char)127) return 41;
        else return 0;
    }
    return 0;
}
int SwifLexer::action(int state)
{
    switch (state)
    {
    case 1:
        return 1;//id: id
    case 2:
        return 2;//number: integer
    case 3:
        return 3;//reserved: switch
    case 4:
        return 4;//reserved: enum
    case 5:
        return 5;//reserved: case
    case 6:
        return 6;//reserved: break
    case 7:
        return 7;//format: spaces
    case 8:
        return 8;//format: enters
    case 9:
        return 9;//format: tab
    case 10:
        return 10;//division: semicolon
    case 11:
        return 11;//division: colon
    case 12:
        return 12;//division: dot
    case 13:
        return 13;//division: comma
    case 14:
        return 14;//braket: braceL
    case 15:
        return 15;//braket: braceR
    case 16:
        return 16;//braket: left
    case 17:
        return 17;//braket: right
    case 18:
        return 18;//braket: squareL
    case 19:
        return 19;//braket: squareR
    case 20:
        return 20;//braket: angleL
    case 21:
        return 21;//braket: angleR
    case 22:
        return 22;//anntation: anntationS
    case 23:
        return 23;//anntation: anntationM
    case 24:
        return 24;//value: value
    case 26:
        return 1;//id: id
    case 27:
        return 1;//id: id
    case 28:
        return 1;//id: id
    case 29:
        return 1;//id: id
    case 30:
        return 1;//id: id
    case 31:
        return 1;//id: id
    case 32:
        return 1;//id: id
    case 33:
        return 1;//id: id
    case 34:
        return 1;//id: id
    case 35:
        return 1;//id: id
    case 36:
        return 1;//id: id
    case 37:
        return 1;//id: id
    case 38:
        return 1;//id: id
    case 39:
        return 1;//id: id
    case 40:
        return 1;//id: id
    }
    return 0;
}
int SwifLexer::GroupGet(int accept)
{
    switch (accept)
    {
    case 1:
        return 1;//id: id
    case 2:
        return 2;//number: integer
    case 3:
        return 3;//reserved: switch
    case 4:
        return 3;//reserved: enum
    case 5:
        return 3;//reserved: case
    case 6:
        return 3;//reserved: break
    case 7:
        return 4;//format: spaces
    case 8:
        return 4;//format: enters
    case 9:
        return 4;//format: tab
    case 10:
        return 5;//division: semicolon
    case 11:
        return 5;//division: colon
    case 12:
        return 5;//division: dot
    case 13:
        return 5;//division: comma
    case 14:
        return 6;//braket: braceL
    case 15:
        return 6;//braket: braceR
    case 16:
        return 6;//braket: left
    case 17:
        return 6;//braket: right
    case 18:
        return 6;//braket: squareL
    case 19:
        return 6;//braket: squareR
    case 20:
        return 6;//braket: angleL
    case 21:
        return 6;//braket: angleR
    case 22:
        return 7;//anntation: anntationS
    case 23:
        return 7;//anntation: anntationM
    case 24:
        return 8;//value: value
    }
    return 0;
}
const size_t SwifPraser::StateCount = 20;
const size_t SwifPraser::NonTerminalCount = 6;
const size_t SwifPraser::TerminalCount = 24;
const size_t SwifPraser::RulesCount = 12;
const int SwifPraser::GOTO[20][6] = { \
{1, 6, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 22, 1, 26, 1}, \
{1, 1, 1, 42, 1, 46}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 78, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 70, 1, 74}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1} };
//==============================
const int SwifPraser::ACTION[20][25] = { \
{17, 17, 17, 17, 10, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17}, \
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{5, 14, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 18, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57}, \
{5, 30, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
{43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 1, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 35, 35, 35, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 34}, \
{9, 9, 38, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 39, 39, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{47, 30, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 66, 61, 61, 61, 61, 61, 61, 61, 61, 61}, \
{19, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{27, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{31, 31, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 31, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 50, 54, 58, 62, 1, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 15, 15, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//==============================
const int SwifPraser::RulesToSymbol[12] = { \
0,\
1,\
2,\
2,\
3,\
3,\
3,\
3,\
4,\
4,\
5,\
5 };
//==============================
const int SwifPraser::RulesLength[12] = { \
1,\
7,\
1,\
3,\
1,\
1,\
1,\
1,\
1,\
3,\
0,\
1 };
//==============================
const char* const SwifPraser::RulesName[12] = { \
"all->ENUM ",\
"ENUM->enum id braceL ITEMS DN braceR DN ",\
"ITEMS->ITEM ",\
"ITEMS->ITEMS [division] ITEM ",\
"[division]->semicolon ",\
"[division]->colon ",\
"[division]->dot ",\
"[division]->comma ",\
"ITEM->id ",\
"ITEM->id value integer ",\
"DN->epsilon ",\
"DN->[division] " };
//==============================
const int SwifPraser::Implicit[12] = { \
0, \
0, \
0, \
0, \
1, \
1, \
1, \
1, \
0, \
0, \
0, \
0 };

