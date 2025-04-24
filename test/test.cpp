#include"extern.h"
#include<cmath>
using namespace Pikachu;
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
    catch (hyperlex::dictionary*error)
    {
        error->print(stdout);

    }
    return info;
}

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
        Exp.Example(8);
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
                //Exp.demo(stdout);
                std::cout << '\t' << BC.ptr() << std::endl; BC.clear();
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
            for (j = 0; j < 2; j++)
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

