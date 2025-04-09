#include"../header/Pikachu.h"
#include"../../extern/lexical/dictionary.h"
#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif
namespace LP
{
    struct FuncLexer
    {
        enum regular
        {
            _id_ = 1,
            _integer_ = 2,
            _realC_ = 3,
            _funct_ = 4,
            _manifold_ = 5,
            _function_ = 6,
            _manif_ = 7,
            _def_ = 8,
            _input_ = 9,
            _output_ = 10,
            _para_ = 11,
            _real_ = 12,
            _sint_ = 13,
            _uint_ = 14,
            _return_ = 15,
            _for_ = 16,
            _if_ = 17,
            _else_ = 18,
            _sin_ = 19,
            _cos_ = 20,
            _exp_ = 21,
            _ln_ = 22,
            _log_ = 23,
            _sqrt_ = 24,
            _pow_ = 25,
            _spaces_ = 26,
            _enters_ = 27,
            _tab_ = 28,
            _semicolon_ = 29,
            _colon_ = 30,
            _dot_ = 31,
            _comma_ = 32,
            _braceL_ = 33,
            _braceR_ = 34,
            _left_ = 35,
            _right_ = 36,
            _squareL_ = 37,
            _squareR_ = 38,
            _angleL_ = 39,
            _angleR_ = 40,
            _anntationS_ = 41,
            _anntationM_ = 42,
            _multi_ = 43,
            _div_ = 44,
            _sub_ = 45,
            _add_ = 46,
            _value_ = 47
        };
        enum group
        {
            _id___ = 1,
            _number___ = 2,
            _reserved___ = 3,
            _function1___ = 4,
            _function2___ = 5,
            _format___ = 6,
            _division___ = 7,
            _braket___ = 8,
            _anntation___ = 9,
            _operatmd___ = 10,
            _operatas___ = 11,
            _value___ = 12
        };
        static int next(int state, const char c);
        static int action(int state);
        static int GroupGet(int state);
        static Pikachu::function functionGet(int state);
        static Pikachu::operation operationGet(int state);
    };

    struct FuncPraser
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
            FUNCTION_FUNCTION_ = 1,
            PARA_PARA_ = 2,
            //<MANIFPARAS>_single_ = 3,
            //<MANIFPARAS>_multi_ = 4,
            MANIFPARA_input_ = 5,
            MANIFPARA_para_ = 6,
            MANIFPARA_paras_ = 7,
            //<FUNCTWORD>_function_ = 8,
            //<FUNCTWORD>_funct_ = 9,
            MANIFBODY_MANIFBODY_ = 10,
            DELARATIONS_DELARATIONS_ = 11,
            //<DELARATION*>_first_ = 12,
            //<DELARATION*>_multi_ = 13,
            DELARATION_single_ = 14,
            DELARATION_multi_ = 15,
            RETURN_RETURN_ = 16,
            EXPRESSIONS_EXPRESSIONS_ = 17,
            //<EXPRESSION*>_first_ = 18,
            //<EXPRESSION*>_multi_ = 19,
            EXPRESSION_EXPRESSION_ = 20,
            //EXP_RIGHT_<implicit>_ = 21,
            EXP_RIGHT_add_ = 22,
            //[operatas]_sub_ = 23,
            //[operatas]_add_ = 24,
            //EXP_MUL_<implicit>_ = 25,
            EXP_MUL_multi_ = 26,
            //[operatmd]_multi_ = 27,
            //[operatmd]_div_ = 28,
            //EXP_MINUS_<implicit>_ = 29,
            EXP_MINUS_plus_ = 30,
            UNIT_id_ = 31,
            UNIT_call_ = 32,
            UNIT_const_ = 33,
            UNIT_complex_ = 34,
            //[number]_integer_ = 35,
            //[number]_realC_ = 36,
            ID_array_ = 37,
            ID_single_ = 38,
            CALL_call_1_ = 39,
            CALL_call_2_ = 40,
            //[function1]_sin_ = 41,
            //[function1]_cos_ = 42,
            //[function1]_exp_ = 43,
            //[function1]_ln_ = 44,
            //[function1]_log_ = 45,
            //[function1]_sqrt_ = 46,
            //[function2]_pow_ = 47
        };
        enum nonterminal
        {
            _all_ = 0,
            _FUNCTION_ = 1,
            _PARA_ = 2,
            //_<MANIFPARAS>_ = 3,
            _MANIFPARA_ = 4,
            //_<FUNCTWORD>_ = 5,
            _MANIFBODY_ = 6,
            _DELARATIONS_ = 7,
            //_<DELARATION*>_ = 8,
            _DELARATION_ = 9,
            _RETURN_ = 10,
            _EXPRESSIONS_ = 11,
            //_<EXPRESSION*>_ = 12,
            _EXPRESSION_ = 13,
            _EXP_RIGHT_ = 14,
            //_[operatas]_ = 15,
            _EXP_MUL_ = 16,
            //_[operatmd]_ = 17,
            _EXP_MINUS_ = 18,
            _UNIT_ = 19,
            //_[number]_ = 20,
            _ID_ = 21,
            _CALL_ = 22,
            //_[function1]_ = 23,
            //_[function2]_ = 24
        };
        static const size_t StateCount;
        static const size_t NonTerminalCount;
        static const size_t TerminalCount;
        static const size_t RulesCount;
        static const int GOTO[85][25];
        static const int ACTION[85][48];
        static const int RulesToSymbol[48];
        static const int RulesLength[48];
        static const char* const RulesName[48];
        static const int Implicit[48];
    };
    int static  LPMorpheneBuild(const char* source, hyperlex::Morpheme& eme);

}
namespace Rtensor
{
    struct lexer
    {
        enum regular
        {
            _id_ = 1,
            _integer_ = 2,
            _real_ = 3,
            _enters_ = 4,
            _spaces_ = 5,
            _tab_ = 6,
            _semicolon_ = 7,
            _colon_ = 8,
            _dot_ = 9
        };
        enum group
        {
            _id___ = 1,
            _number___ = 2,
            _enters___ = 3,
            _format___ = 4,
            _division___ = 5
        };
        static int next(int state, const char c);
        static int action(int state);
        static int GroupGet(int state);
    };
}
namespace Exp
{
    struct ExpLexer
    {
        enum regular
        {
            _id_ = 1,
            _integer_ = 2,
            _realC_ = 3,
            _return_ = 4,
            _for_ = 5,
            _if_ = 6,
            _else_ = 7,
            _sin_ = 8,
            _cos_ = 9,
            _exp_ = 10,
            _ln_ = 11,
            _log_ = 12,
            _sqrt_ = 13,
            _pow_ = 14,
            _spaces_ = 15,
            _enters_ = 16,
            _tab_ = 17,
            _semicolon_ = 18,
            _colon_ = 19,
            _dot_ = 20,
            _comma_ = 21,
            _braceL_ = 22,
            _braceR_ = 23,
            _left_ = 24,
            _right_ = 25,
            _squareL_ = 26,
            _squareR_ = 27,
            _angleL_ = 28,
            _angleR_ = 29,
            _anntationS_ = 30,
            _anntationM_ = 31,
            _multi_ = 32,
            _div_ = 33,
            _sub_ = 34,
            _add_ = 35,
            _value_ = 36
        };
        enum group
        {
            _id___ = 1,
            _number___ = 2,
            _reserved___ = 3,
            _function1___ = 4,
            _function2___ = 5,
            _format___ = 6,
            _division___ = 7,
            _braket___ = 8,
            _anntation___ = 9,
            _operatmd___ = 10,
            _operatas___ = 11,
            _value___ = 12
        };
        static int next(int state, const char c);
        static int action(int state);
        static int GroupGet(int state);
        static Pikachu::function functionGet(int state);
        static Pikachu::operation operationGet(int state);
    };
    struct ExpPraser
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
            Expression_left_right_ = 1,
            Expression_right_ = 2,
            //EXP_RIGHT_<implicit>_ = 3,
            EXP_RIGHT_add_ = 4,
            //[operatas]_sub_ = 5,
            //[operatas]_add_ = 6,
            //EXP_MUL_<implicit>_ = 7,
            EXP_MUL_multi_ = 8,
            //[operatmd]_multi_ = 9,
            //[operatmd]_div_ = 10,
            //EXP_MINUS_<implicit>_ = 11,
            EXP_MINUS_plus_ = 12,
            UNIT_id_ = 13,
            UNIT_call_ = 14,
            UNIT_const_ = 15,
            UNIT_complex_ = 16,
            //[number]_integer_ = 17,
            //[number]_realC_ = 18,
            CALL_call_1_ = 19,
            CALL_call_2_ = 20,
            //[function1]_sin_ = 21,
            //[function1]_cos_ = 22,
            //[function1]_exp_ = 23,
            //[function1]_ln_ = 24,
            //[function1]_log_ = 25,
            //[function1]_sqrt_ = 26,
            //[function2]_pow_ = 27
        };
        enum nonterminal
        {
            _all_ = 0,
            _Expression_ = 1,
            _EXP_RIGHT_ = 2,
            //_[operatas]_ = 3,
            _EXP_MUL_ = 4,
            //_[operatmd]_ = 5,
            _EXP_MINUS_ = 6,
            _UNIT_ = 7,
            //_[number]_ = 8,
            _CALL_ = 9,
            //_[function1]_ = 10,
            //_[function2]_ = 11
        };
        static const size_t StateCount;
        static const size_t NonTerminalCount;
        static const size_t TerminalCount;
        static const size_t RulesCount;
        static const int GOTO[45][12];
        static const int ACTION[45][37];
        static const int RulesToSymbol[28];
        static const int RulesLength[28];
        static const char* const RulesName[28];
        static const int Implicit[28];
    };
}




int Pikachu::matrixGet(FILE* fp, vector<double>& output, size_t& row, size_t& column)
{
    int error, state;
    size_t i;
    double temp;
    hyperlex::Morpheme eme;
    size_t record;
    state = 0;
    record = 0;
    error = eme.Build<Rtensor::lexer>(fp);
    row = 0;
    if (error != 0) return error;
    for (i = 0; i < eme.GetCount(); i++)
    {
        if (eme[i].accept == Rtensor::lexer::regular::_real_)
        {
            temp = eme.GetReal(i);
            output.append(temp);
            if (state == 0) state = 1;
            record += 1;
        }
        else if (eme[i].accept == Rtensor::lexer::regular::_enters_)
        {
            if (state == 1)
            {
                column = record;
                record = 0;
                state = 2;
                row += 1;
            }
            else if (state == 2)
            {
                if (column != record) error = (int)eme[i].line;
                record = 0;
                row += 1;
            }
        }
    }
    return error;
}
int Pikachu::vectorGet(FILE* fp, vector<double>& output)
{
    int error;
    size_t i;
    double temp;
    hyperlex::Morpheme eme;
    error = eme.Build<Rtensor::lexer>(fp);
    if (error != 0) return error;
    for (i = 0; i < eme.GetCount(); i++)
    {
        if (eme[i].accept == Rtensor::lexer::regular::_real_)
        {
            temp = eme.GetReal(i);
            output.append(temp);
        }
    }
    return error;
}

class LexSheet
{
public:
    struct item
    {
        hyperlex::BufferChar name;
        hyperlex::BufferChar attri;
        size_t length;
        Pikachu::vector<void*> infor;
        long int label;
        item() { label = 0;
        length = 0;
        }
        ~item() {}
        inline bool nameIs(const char* source)
        {
            hyperlex::BufferChar temp;
            temp = source;
            return name == temp;
        }
        inline bool attriIs(const char* source)
        {
            hyperlex::BufferChar temp;
            temp = source;
            return attri == temp;
        }
        inline void*& operator [](size_t site) 
        {
            return infor[site]; 
        }
        inline size_t count(void) const { return infor.count(); }
    };
    struct SiteInfor
    {
        size_t site1;
        size_t site2;
    };
private:
    hyperlex::vector<item*> items;
public:
    LexSheet() {}
    ~LexSheet()
    {
        size_t i;
        for (i = 0; i < items.count(); i++)
        {
            delete items[i];
        }
    }
    inline item*& operator [](size_t site) { return items[site]; }
    inline item*& operator [](int site) { return items[(size_t)site]; }
    inline item* operator [](const char* source)
    {
        size_t i;
        for (i = 0; i < items.count(); i++)
        {
            if (items[i] != NULL)
                if (items[i]->nameIs(source)) return items[i];
        }
        return NULL;
    }
    inline void* operator [](const SiteInfor* source)
    {
        item* temp;
        temp = items[source->site1];
        return temp->infor[source->site2];
    }
    void append(size_t length, const char* Name, const char* Attri)
    {
        item* New;
        long int temp;
        size_t i;
        New = new item;
        New->name = Name;
        New->attri = Attri;
        New->length = length;
        New->infor.recount(length);
        New->infor.value(NULL);
        temp = 0;
        for (i = 0; i < items.count(); i++)
        {
            if (items[i] != NULL)
                if (items[i]->attriIs(Attri)) temp += 1;
        }
        New->label = temp;
        items.append(New);
    }
    void demo(FILE* fp)
    {
        size_t i;
        for (i = 0; i < items.count(); i++)
        {
            if (items[i] != NULL)
            {
                fprintf(fp, "items[%zu]: length: %zu\n", i, items[i]->length);
                fprintf(fp, "\tname: %s\n", items[i]->name.ptr());
                fprintf(fp, "\tattribute: %s\n", items[i]->attri.ptr());
            }
        }
    }
    inline size_t count(void) { return items.count(); }
    inline SiteInfor* siteGet(const char* Name, size_t No)
    {
        size_t i;
        SiteInfor* New;
        New = NULL;
        for (i = 0; i < items.count(); i++)
        {
            if (items[i] != NULL)
                if (items[i]->nameIs(Name))
                {
                    if (No < items[i]->count())
                    {
                        New = (SiteInfor*)malloc(sizeof(SiteInfor));
                        New->site1 = i;
                        New->site2 = No;
                    }
                }
        }
        return New;
    }
};

static int ExpMorpheneBuild(const char* source, hyperlex::Morpheme& eme)
{
    using namespace Exp;
    int error;
    size_t i;
    ExpLexer::regular T;
    ExpLexer::group G;
    error = eme.Build<ExpLexer>(source);
    if (error != 0)
    {
        //errorCode = ErrorinputLEXICAL;
        return error;
    }
    for (i = 0; i < eme.GetCount(); i++)
    {
        T = (ExpLexer::regular)(eme[i].accept);
        G = (ExpLexer::group)(eme[i].category);
        if (G == ExpLexer::_format___ || G == ExpLexer::_anntation___)
        {
            eme.valid(i) = false;
        }
    }
    return error;
}
int Pikachu::Expres::example(const char* source)
{
    size_t i, site;
    int error;
    hyperlex::Morpheme eme;
    GTIter iterator;
    hyperlex::GrammarTree Tree;
    GLTree* GT;
    Ele* left_;
    Ele* right_;
    Ele* here;
    Exp::ExpPraser::rules RRR;
    Pikachu::function func__;
    Pikachu::operation op__;
    LexSheet Ls;
    const char* name__;
    clear();
    error = ExpMorpheneBuild(source, eme);
    if (error != 0)return error;
    //eme.Demo(stdout);
   
    error = Tree.build<Exp::ExpPraser>(eme);
    if (error != 0)
    {
        return error;
    }
    //Tree.Demo(stdout, eme, Exp::ExpPraser::RulesName);
    iterator.initial(Tree.GT);
    while (iterator.still())
    {
        GT = iterator.target();
        if (iterator.state() != 0 && GT->root().rules)
        {
            RRR = (Exp::ExpPraser::rules)GT->root().site;
            //printf("RRR:%zu\n", GT->root().site);
            switch (RRR)
            {
            case Exp::ExpPraser::Expression_left_right_:
                here = (Ele*)GT->child(2)->root().infor;
                OutputAppend(here);
                break;
            case Exp::ExpPraser::Expression_right_:
                here = (Ele*)GT->child(0)->root().infor;
                OutputAppend(here);
                break;
            case Exp::ExpPraser::EXP_RIGHT_add_:
            case Exp::ExpPraser::EXP_MUL_multi_:
                left_ = (Ele*)GT->child(0)->root().infor;
                right_ = (Ele*)GT->child(2)->root().infor;
                op__ = Exp::ExpLexer::operationGet(eme[GT->child(1)].accept);
                here = NewNode(left_, right_, op__);
                break;
            case Exp::ExpPraser::EXP_MINUS_plus_:
                left_ = (Ele*)GT->child(1)->root().infor;
                op__ = Exp::ExpLexer::operationGet(eme[GT->child(0)].accept);
                //printf("EXP_MINUS_plus_:%d\n", (int)op__);
                if (op__ == Pikachu::_sub_) here = NewNode(left_, _minus_);
                else here = left_;
                break;
            case Exp::ExpPraser::UNIT_id_:
                name__ = eme.GetWord(GT->child(0)->root().site);
                if (Ls.count() == 0)
                {
                    here = new Ele();
                    here->Type = Pikachu::_LeafX_;
                    formula.append(here);
                    Ls.append(1, name__, "input");
                    (*Ls[0])[0] = (void*)here;
                }
                else if (Ls[name__] != NULL)
                {
                    here = (Ele*)(*Ls[0])[0];
                }
                else return -12234;
                break;
            case Exp::ExpPraser::UNIT_call_:
                here = (Ele*)GT->child(0)->root().infor;
                break;
            case Exp::ExpPraser::UNIT_const_:
                site = GT->child(0)->root().site;
                if (eme[site].accept == (int)Exp::ExpLexer::regular::_integer_)
                    here = NewNode(eme.GetInt(site));
                else
                    here = NewNode(eme.GetReal(site));
                break;
            case Exp::ExpPraser::UNIT_complex_:
                here = (Ele*)GT->child(1)->root().infor;
                break;
            case Exp::ExpPraser::CALL_call_1_:
                left_ = (Ele*)GT->child(2)->root().infor;
                func__ = Exp::ExpLexer::functionGet(eme[GT->child(0)].accept);
                here = NewNode(left_, func__);
                break;
            case Exp::ExpPraser::CALL_call_2_:
                left_ = (Ele*)GT->child(2)->root().infor;
                right_ = (Ele*)GT->child(4)->root().infor;
                here = NewNode(left_, right_, _pow_);
                break;
            default:
                break;
            }
            GT->root().infor = (void*)here;
        }
        iterator.next();
    }
    InputDim.recount(1);
    InputDim[0] = 1;
    ParameterCount = 0;
    return 0;
}

int Pikachu::ActivFunc::construct(const char* source)
{
    using namespace LP;
    size_t i;
    int error;
    hyperlex::Morpheme eme;
    hyperlex::GrammarTree Tree;
    hyperlex::vector<int> state;
    clear();

    error = LPMorpheneBuild(source, eme);
    if (error != 0) 
    {
        for (i = 0; i < eme.GetCount(); i++)
        {
            printf("%s\n", eme.GetWord(i));
        }
        
        return error;
    }
    eme.Demo(stdout);

    error = Tree.build<FuncPraser>(eme);
    if (error != 0)
    {
        return error;
    }
    Tree.Demo(stdout, eme, Exp::ExpPraser::RulesName);
    
    state.recount(FuncPraser::RulesCount);
    for (i = 0; i < state.count(); i++) state[i] = (int)i;
    error = build(Tree.GT, eme, state.ptr());

    InputDim.recount(1);
    InputDim[0] = 1;
    return 0;
}
int Pikachu::ActivFunc::build(GLTree* Tree, hyperlex::Morpheme& eme, int* state)
{
    using namespace LP;
    GTIter iterator;
    GLTree* GT;
    FuncPraser::rules RRR;

    Ele* left_;
    Ele* right_;
    Ele* here;
    Pikachu::function func__;
    Pikachu::operation op__;
    LexSheet Ls;
    LexSheet::SiteInfor* SiteTemp_;
    const char* name__;

    size_t i, site, temp_;
    iterator.initial(Tree);

    while (iterator.still())
    {
        GT = iterator.target();
        if (iterator.state() != 0 && GT->root().rules)
        {
            RRR = (FuncPraser::rules)state[GT->root().site];
            here = NULL;
            SiteTemp_ = NULL;
            switch (RRR)
            {
            case LP::FuncPraser::MANIFPARA_input_:
                name__ = eme.GetWord(GT->child(1)->root().site);
                here = new Ele();
                here->Type = Pikachu::_LeafX_;
                formula.append(here);
                Ls.append(1, name__, "input");
                (*Ls[name__])[0] = (void*)here;
                break;
            case LP::FuncPraser::MANIFPARA_para_:
                name__ = eme.GetWord(GT->child(1)->root().site);
                Ls.append(1, name__, "para");
                site = Ls.count() - 1;
                (*Ls[site])[0] = NewNode(Pikachu::_LeafPara_, Ls[site]->label, 0);
                ParameterCount += 1;
                break;
            case LP::FuncPraser::MANIFPARA_paras_:
                name__ = eme.GetWord(GT->child(1)->root().site);
                site = GT->child(3)->root().site;
                temp_ = eme.GetInt(site);
                Ls.append(temp_, name__, "para");
                ParameterCount += temp_;
                site = Ls.count() - 1;
                for (i = 0; i < temp_; i++)
                {
                    (*Ls[site])[i] = NewNode(Pikachu::_LeafPara_, Ls[site]->label, i);
                }
                break;
            case LP::FuncPraser::DELARATION_single_:
                name__ = eme.GetWord(GT->child(1)->root().site);
                Ls.append(1, name__, "var");
                break;
            case LP::FuncPraser::DELARATION_multi_:
                name__ = eme.GetWord(GT->child(1)->root().site);
                site = GT->child(3)->root().site;
                temp_ = eme.GetInt(site);
                Ls.append(temp_, name__, "var");
                break;
            case LP::FuncPraser::RETURN_RETURN_:
                here = (Ele*)GT->child(1)->root().infor;
                OutputAppend(here);
                here = NULL;
                break;
            case LP::FuncPraser::EXPRESSION_EXPRESSION_:
                right_ = (Ele*)GT->child(2)->root().infor;
                SiteTemp_ = (LexSheet::SiteInfor*)GT->child(0)->root().infor;
                if (SiteTemp_ == NULL) return -5448;
                Ls[SiteTemp_->site1]->infor[SiteTemp_->site2] = right_;
                here = right_;
                free((void*)SiteTemp_);
                break;
            case LP::FuncPraser::EXP_RIGHT_add_:
            case LP::FuncPraser::EXP_MUL_multi_:
                left_ = (Ele*)GT->child(0)->root().infor;
                right_ = (Ele*)GT->child(2)->root().infor;
                op__ = FuncLexer::operationGet(eme[GT->child(1)].accept);
                here = NewNode(left_, right_, op__);
                break;
            case LP::FuncPraser::EXP_MINUS_plus_:
                left_ = (Ele*)GT->child(1)->root().infor;
                op__ = FuncLexer::operationGet(eme[GT->child(0)].accept);
                if (op__ == Pikachu::_sub_) here = NewNode(left_, _minus_);
                else here = left_;
                break;
            case LP::FuncPraser::UNIT_id_:
                SiteTemp_ = (LexSheet::SiteInfor*)GT->child(0)->root().infor;
                if (SiteTemp_ == NULL) return -548348;
                here = (Ele*)Ls[SiteTemp_];
                if (here == NULL) return -4784537;
                free((void*)SiteTemp_);
                break;
            case LP::FuncPraser::UNIT_call_:
                here = (Ele*)GT->child(0)->root().infor;
                break;
            case LP::FuncPraser::UNIT_const_:
                site = GT->child(0)->root().site;
                if (eme[site].accept == (int)FuncLexer::regular::_integer_)
                    here = NewNode(eme.GetInt(site));
                else
                    here = NewNode(eme.GetReal(site));
                break;
            case LP::FuncPraser::UNIT_complex_:
                here = (Ele*)GT->child(1)->root().infor;
                break;
            case LP::FuncPraser::ID_array_:
                name__ = eme.GetWord(GT->child(0)->root().site);
                site = GT->child(2)->root().site;
                temp_ = eme.GetInt(site);
                SiteTemp_ = Ls.siteGet(name__, temp_);
                if (SiteTemp_ == NULL) return -34843;
                break;
            case LP::FuncPraser::ID_single_:
                name__ = eme.GetWord(GT->child(0)->root().site);
                SiteTemp_ = Ls.siteGet(name__, 0);
                if (SiteTemp_ == NULL) return -34844;
                break;
            case LP::FuncPraser::CALL_call_1_:
                left_ = (Ele*)GT->child(2)->root().infor;
                func__ = FuncLexer::functionGet(eme[GT->child(0)].accept);
                here = NewNode(left_, func__);
                break;
            case LP::FuncPraser::CALL_call_2_:
                left_ = (Ele*)GT->child(2)->root().infor;
                right_ = (Ele*)GT->child(4)->root().infor;
                here = NewNode(left_, right_, _pow_);
                break;
            default:
                break;
            }
            GT->root().infor = (here == NULL ? (void*)SiteTemp_ : (void*)here);
        }
        iterator.next();
    }
    return 0;
}

namespace Rtensor
{
    int lexer::next(int state, const char c)
    {
        switch (state)
        {
        case 0:
            if (c == (char)9) return 6;
            else if (c == (char)10) return 4;
            else if (c == ' ') return 5;
            else if (c == '+') return 10;
            else if (c == '-') return 10;
            else if (c == '.') return 9;
            else if ('0' <= c && c <= '9') return 2;
            else if (c == ':') return 8;
            else if (c == ';') return 7;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 1:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 2:
            if (c == '.') return 13;
            else if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 3:
            if ('0' <= c && c <= '9') return 3;
            else if (c == 'E') return 12;
            else if (c == 'e') return 12;
            else return 0;
        case 4:
            if (c == (char)10) return 4;
            else return 0;
        case 5:
            if (c == ' ') return 5;
            else return 0;
        case 6:
            return 0;
        case 7:
            return 0;
        case 8:
            return 0;
        case 9:
            return 0;
        case 10:
            if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 11:
            if ('0' <= c && c <= '9') return 11;
            else return 0;
        case 12:
            if (c == '+') return 14;
            else if (c == '-') return 14;
            else if ('0' <= c && c <= '9') return 11;
            else return 0;
        case 13:
            if ('0' <= c && c <= '9') return 3;
            else return 0;
        case 14:
            if ('0' <= c && c <= '9') return 11;
            else return 0;
        }
        return 0;
    }
    int lexer::action(int state)
    {
        switch (state)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 3;//number: real
        case 4:
            return 4;//enters: enters
        case 5:
            return 5;//format: spaces
        case 6:
            return 6;//format: tab
        case 7:
            return 7;//division: semicolon
        case 8:
            return 8;//division: colon
        case 9:
            return 9;//division: dot
        case 11:
            return 3;//number: real
        }
        return 0;
    }
    int lexer::GroupGet(int accept)
    {
        switch (accept)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 2;//number: real
        case 4:
            return 3;//enters: enters
        case 5:
            return 4;//format: spaces
        case 6:
            return 4;//format: tab
        case 7:
            return 5;//division: semicolon
        case 8:
            return 5;//division: colon
        case 9:
            return 5;//division: dot
        }
        return 0;
    }

    
}
namespace LP
{ 

    int LPMorpheneBuild(const char* source, hyperlex::Morpheme& eme)
    {
        int error;
        size_t i;
        FuncLexer::regular T;
        FuncLexer::group G;
        error = eme.Build<FuncLexer>(source);
        if (error != 0)
        {
            //errorCode = ErrorinputLEXICAL;
            return error;
        }
        for (i = 0; i < eme.GetCount(); i++)
        {
            T = (FuncLexer::regular)(eme[i].accept);
            G = (FuncLexer::group)(eme[i].category);
            if (G == FuncLexer::_format___ || G == FuncLexer::_anntation___)
            {
                eme.valid(i) = false;
            }
        }
    }

    const size_t FuncPraser::StateCount = 85;
    const size_t FuncPraser::NonTerminalCount = 25;
    const size_t FuncPraser::TerminalCount = 47;
    const size_t FuncPraser::RulesCount = 48;
    const int FuncPraser::GOTO[85][25] = { \
    {1, 6, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 26, 30, 34, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 82, 86, 90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 126, 130, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 94, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 322, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 134, 1, 1, 1, 1, 1, 1, 1, 138, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 314, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 266, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 262, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 266, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 166, 1, 1, 278, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 286, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 294, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 306, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 330, 166, 170, 1, 174, 178, 182, 186, 190, 194, 198}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 254, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
    //==============================
    const int FuncPraser::ACTION[85][48] = { \
    {1, 1, 1, 1, 14, 1, 18, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 22, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 39, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 35, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 38, 1, 42, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 74, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 66, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 1, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {5, 62, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
    {5, 46, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 1, 1, 1, 27, 50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {9, 9, 54, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
    {153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 58, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 31, 1, 1, 1, 31, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 23, 1, 1, 1, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 38, 1, 42, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 19, 1, 1, 1, 19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 78, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133}, \
    {1, 51, 1, 1, 1, 1, 1, 1, 51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 338, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
    {1, 75, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 75, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 47, 1, 1, 1, 1, 1, 1, 98, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 55, 1, 1, 1, 1, 1, 1, 55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {5, 102, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 110, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 59, 1, 1, 1, 1, 1, 1, 59, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {9, 9, 114, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
    {153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 118, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
    {117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 122, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117}, \
    {1, 63, 1, 1, 1, 1, 1, 1, 63, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 326, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61}, \
    {1, 142, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 71, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 79, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 79, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 158}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 155, 1, 1, 155, 1, 1, 1, 155, 146, 1, 1, 1, 1, 1, 155, 155, 155, 155, 155}, \
    {9, 9, 150, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, \
    {153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 154, 153, 153, 153, 153, 153, 153, 153, 153, 153}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 151, 1, 1, 151, 1, 1, 1, 151, 1, 1, 1, 1, 1, 1, 151, 151, 151, 151, 151}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 318, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 87, 1, 1, 87, 1, 1, 1, 87, 1, 1, 1, 1, 1, 1, 270, 274, 87, 87, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 103, 1, 1, 103, 1, 1, 1, 103, 1, 1, 1, 1, 1, 1, 103, 103, 103, 103, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 119, 1, 1, 119, 1, 1, 1, 119, 1, 1, 1, 1, 1, 1, 119, 119, 119, 119, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 135, 1, 1, 135, 1, 1, 1, 135, 1, 1, 1, 1, 1, 1, 135, 135, 135, 135, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 127, 1, 1, 127, 1, 1, 1, 127, 1, 1, 1, 1, 1, 1, 127, 127, 127, 127, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 131, 1, 1, 131, 1, 1, 1, 131, 1, 1, 1, 1, 1, 1, 131, 131, 131, 131, 1}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 302, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 282, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 143, 1, 1, 143, 1, 1, 1, 143, 1, 1, 1, 1, 1, 1, 143, 143, 143, 143, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 147, 1, 1, 147, 1, 1, 1, 147, 1, 1, 1, 1, 1, 1, 147, 147, 147, 147, 1}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 167, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 171, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 175, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 179, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 183, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 187, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 191, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 95, 95, 95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 95, 95, 95, 95, 95, 95, 95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 95, 1, 1, 1, 1, 1, 1, 1, 1, 1, 95, 95, 1}, \
    {1, 99, 99, 99, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 99, 99, 99, 99, 99, 99, 99, 1, 1, 1, 1, 1, 1, 1, 1, 1, 99, 1, 1, 1, 1, 1, 1, 1, 1, 1, 99, 99, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 258, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 139, 1, 1, 139, 1, 1, 1, 139, 1, 1, 1, 1, 1, 1, 139, 139, 139, 139, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 91, 1, 1, 91, 1, 1, 1, 91, 1, 1, 1, 1, 1, 1, 270, 274, 91, 91, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 111, 111, 111, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 111, 111, 111, 111, 111, 111, 111, 1, 1, 1, 1, 1, 1, 1, 1, 1, 111, 1, 1, 1, 1, 1, 1, 1, 1, 1, 111, 111, 1}, \
    {1, 115, 115, 115, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 115, 115, 115, 115, 115, 115, 115, 1, 1, 1, 1, 1, 1, 1, 1, 1, 115, 1, 1, 1, 1, 1, 1, 1, 1, 1, 115, 115, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 107, 1, 1, 107, 1, 1, 1, 107, 1, 1, 1, 1, 1, 1, 107, 107, 107, 107, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 290, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 298, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 163, 1, 1, 163, 1, 1, 1, 163, 1, 1, 1, 1, 1, 1, 163, 163, 163, 163, 1}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 310, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 159, 1, 1, 159, 1, 1, 1, 159, 1, 1, 1, 1, 1, 1, 159, 159, 159, 159, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 123, 1, 1, 123, 1, 1, 1, 123, 1, 1, 1, 1, 1, 1, 123, 123, 123, 123, 1}, \
    {1, 83, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 83, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 43, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
    {1, 142, 202, 206, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 210, 214, 218, 222, 226, 230, 234, 1, 1, 1, 1, 1, 1, 1, 1, 1, 238, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 334, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 242, 246, 1}, \
    {137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 67, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137}, \
    {7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
    //==============================
    const int FuncPraser::RulesToSymbol[48] = { \
    0,\
    1,\
    2,\
    3,\
    3,\
    4,\
    4,\
    4,\
    5,\
    5,\
    6,\
    7,\
    8,\
    8,\
    9,\
    9,\
    10,\
    11,\
    12,\
    12,\
    13,\
    14,\
    14,\
    15,\
    15,\
    16,\
    16,\
    17,\
    17,\
    18,\
    18,\
    19,\
    19,\
    19,\
    19,\
    20,\
    20,\
    21,\
    21,\
    22,\
    22,\
    23,\
    23,\
    23,\
    23,\
    23,\
    23,\
    24 };
    //==============================
    const int FuncPraser::RulesLength[48] = { \
    1,\
    7,\
    1,\
    1,\
    3,\
    2,\
    2,\
    5,\
    1,\
    1,\
    3,\
    1,\
    0,\
    2,\
    3,\
    6,\
    3,\
    1,\
    0,\
    2,\
    4,\
    1,\
    3,\
    1,\
    1,\
    1,\
    3,\
    1,\
    1,\
    1,\
    2,\
    1,\
    1,\
    1,\
    3,\
    1,\
    1,\
    4,\
    1,\
    4,\
    6,\
    1,\
    1,\
    1,\
    1,\
    1,\
    1,\
    1 };
    //==============================
    const char* const FuncPraser::RulesName[48] = { \
    "all->FUNCTION ",\
    "FUNCTION-><FUNCTWORD> left PARA right braceL MANIFBODY braceR ",\
    "PARA-><MANIFPARAS> ",\
    "<MANIFPARAS>->MANIFPARA ",\
    "<MANIFPARAS>-><MANIFPARAS> comma MANIFPARA ",\
    "MANIFPARA->input id ",\
    "MANIFPARA->para id ",\
    "MANIFPARA->para id squareL integer squareR ",\
    "<FUNCTWORD>->function ",\
    "<FUNCTWORD>->funct ",\
    "MANIFBODY->DELARATIONS EXPRESSIONS RETURN ",\
    "DELARATIONS-><DELARATION*> ",\
    "<DELARATION*>->epsilon ",\
    "<DELARATION*>-><DELARATION*> DELARATION ",\
    "DELARATION->def id semicolon ",\
    "DELARATION->def id squareL integer squareR semicolon ",\
    "RETURN->return EXP_RIGHT semicolon ",\
    "EXPRESSIONS-><EXPRESSION*> ",\
    "<EXPRESSION*>->epsilon ",\
    "<EXPRESSION*>-><EXPRESSION*> EXPRESSION ",\
    "EXPRESSION->ID value EXP_RIGHT semicolon ",\
    "EXP_RIGHT->EXP_MUL ",\
    "EXP_RIGHT->EXP_RIGHT [operatas] EXP_MUL ",\
    "[operatas]->sub ",\
    "[operatas]->add ",\
    "EXP_MUL->EXP_MINUS ",\
    "EXP_MUL->EXP_MUL [operatmd] EXP_MINUS ",\
    "[operatmd]->multi ",\
    "[operatmd]->div ",\
    "EXP_MINUS->UNIT ",\
    "EXP_MINUS->[operatas] UNIT ",\
    "UNIT->ID ",\
    "UNIT->CALL ",\
    "UNIT->[number] ",\
    "UNIT->left EXP_RIGHT right ",\
    "[number]->integer ",\
    "[number]->realC ",\
    "ID->id squareL integer squareR ",\
    "ID->id ",\
    "CALL->[function1] left EXP_RIGHT right ",\
    "CALL->[function2] left EXP_RIGHT comma EXP_RIGHT right ",\
    "[function1]->sin ",\
    "[function1]->cos ",\
    "[function1]->exp ",\
    "[function1]->ln ",\
    "[function1]->log ",\
    "[function1]->sqrt ",\
    "[function2]->pow " };
    //==============================
    const int FuncPraser::Implicit[48] = { \
    0, \
    0, \
    0, \
    1, \
    1, \
    0, \
    0, \
    0, \
    1, \
    1, \
    0, \
    0, \
    1, \
    1, \
    0, \
    0, \
    0, \
    0, \
    1, \
    1, \
    0, \
    1, \
    0, \
    1, \
    1, \
    1, \
    0, \
    1, \
    1, \
    1, \
    0, \
    0, \
    0, \
    0, \
    0, \
    1, \
    1, \
    0, \
    0, \
    0, \
    0, \
    1, \
    1, \
    1, \
    1, \
    1, \
    1, \
    1 };


    int FuncLexer::next(int state, const char c)
    {
        switch (state)
        {
        case 0:
            if (c == (char)9) return 28;
            else if (c == (char)10) return 27;
            else if (c == ' ') return 26;
            else if (c == '(') return 35;
            else if (c == ')') return 36;
            else if (c == '*') return 43;
            else if (c == '+') return 46;
            else if (c == ',') return 32;
            else if (c == '-') return 45;
            else if (c == '.') return 31;
            else if (c == '/') return 44;
            else if ('0' <= c && c <= '9') return 2;
            else if (c == ':') return 30;
            else if (c == ';') return 29;
            else if (c == '<') return 39;
            else if (c == '=') return 47;
            else if (c == '>') return 40;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '[') return 37;
            else if (c == ']') return 38;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'b') return 1;
            else if (c == 'c') return 69;
            else if (c == 'd') return 53;
            else if (c == 'e') return 68;
            else if (c == 'f') return 66;
            else if ('g' <= c && c <= 'h') return 1;
            else if (c == 'i') return 52;
            else if ('j' <= c && c <= 'k') return 1;
            else if (c == 'l') return 59;
            else if (c == 'm') return 60;
            else if (c == 'n') return 1;
            else if (c == 'o') return 78;
            else if (c == 'p') return 65;
            else if (c == 'q') return 1;
            else if (c == 'r') return 58;
            else if (c == 's') return 61;
            else if (c == 't') return 1;
            else if (c == 'u') return 73;
            else if ('v' <= c && c <= 'z') return 1;
            else if (c == '{') return 33;
            else if (c == '}') return 34;
            else return 0;
        case 1:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 2:
            if (c == '.') return 48;
            else if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 3:
            if ('0' <= c && c <= '9') return 3;
            else if (c == 'E') return 82;
            else if (c == 'e') return 82;
            else return 0;
        case 4:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'h') return 1;
            else if (c == 'i') return 62;
            else if ('j' <= c && c <= 'z') return 1;
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
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 85;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 8:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 9:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 10:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 11:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 12:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 13:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 14:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 15:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 16:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 17:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 18:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 19:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 13;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 20:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 21:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 22:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 23:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 24:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 25:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 26:
            if (c == ' ') return 26;
            else return 0;
        case 27:
            if (c == (char)10) return 27;
            else return 0;
        case 28:
            return 0;
        case 29:
            return 0;
        case 30:
            return 0;
        case 31:
            return 0;
        case 32:
            return 0;
        case 33:
            return 0;
        case 34:
            return 0;
        case 35:
            return 0;
        case 36:
            return 0;
        case 37:
            return 0;
        case 38:
            return 0;
        case 39:
            return 0;
        case 40:
            return 0;
        case 41:
            return 0;
        case 42:
            if ((char)0 <= c && c <= ')') return 81;
            else if (c == '*') return 93;
            else if ('+' <= c && c <= (char)127) return 81;
            else return 0;
        case 43:
            return 0;
        case 44:
            if (c == '*') return 81;
            else if (c == '/') return 92;
            else return 0;
        case 45:
            if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 46:
            if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 47:
            return 0;
        case 48:
            if ('0' <= c && c <= '9') return 3;
            else return 0;
        case 49:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if (c == 'a') return 11;
            else if ('b' <= c && c <= 'z') return 1;
            else return 0;
        case 50:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'c') return 1;
            else if (c == 'd') return 5;
            else if ('e' <= c && c <= 'z') return 1;
            else return 0;
        case 51:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'd') return 1;
            else if (c == 'e') return 18;
            else if ('f' <= c && c <= 'z') return 1;
            else return 0;
        case 52:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'e') return 1;
            else if (c == 'f') return 17;
            else if ('g' <= c && c <= 'm') return 1;
            else if (c == 'n') return 101;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 53:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'd') return 1;
            else if (c == 'e') return 94;
            else if ('f' <= c && c <= 'z') return 1;
            else return 0;
        case 54:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'f') return 1;
            else if (c == 'g') return 23;
            else if ('h' <= c && c <= 'z') return 1;
            else return 0;
        case 55:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'h') return 1;
            else if (c == 'i') return 84;
            else if ('j' <= c && c <= 'z') return 1;
            else return 0;
        case 56:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'k') return 1;
            else if (c == 'l') return 12;
            else if ('m' <= c && c <= 'z') return 1;
            else return 0;
        case 57:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if (c == 'a') return 56;
            else if ('b' <= c && c <= 's') return 1;
            else if (c == 't') return 75;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 58:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'd') return 1;
            else if (c == 'e') return 57;
            else if ('f' <= c && c <= 'z') return 1;
            else return 0;
        case 59:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 22;
            else if (c == 'o') return 54;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 60:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if (c == 'a') return 98;
            else if ('b' <= c && c <= 'z') return 1;
            else return 0;
        case 61:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'h') return 1;
            else if (c == 'i') return 86;
            else if ('j' <= c && c <= 'p') return 1;
            else if (c == 'q') return 74;
            else if ('r' <= c && c <= 'z') return 1;
            else return 0;
        case 62:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 102;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 63:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'o') return 1;
            else if (c == 'p') return 21;
            else if ('q' <= c && c <= 'z') return 1;
            else return 0;
        case 64:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 95;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 65:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if (c == 'a') return 87;
            else if ('b' <= c && c <= 'n') return 1;
            else if (c == 'o') return 79;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 66:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 96;
            else if ('p' <= c && c <= 't') return 1;
            else if (c == 'u') return 90;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 67:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'r') return 1;
            else if (c == 's') return 51;
            else if ('t' <= c && c <= 'z') return 1;
            else return 0;
        case 68:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'k') return 1;
            else if (c == 'l') return 67;
            else if ('m' <= c && c <= 'w') return 1;
            else if (c == 'x') return 63;
            else if ('y' <= c && c <= 'z') return 1;
            else return 0;
        case 69:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 88;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 70:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 14;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 71:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'b') return 1;
            else if (c == 'c') return 103;
            else if ('d' <= c && c <= 'z') return 1;
            else return 0;
        case 72:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 70;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 73:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'h') return 1;
            else if (c == 'i') return 72;
            else if ('j' <= c && c <= 'z') return 1;
            else return 0;
        case 74:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 89;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 75:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 't') return 1;
            else if (c == 'u') return 64;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 76:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'o') return 1;
            else if (c == 'p') return 91;
            else if ('q' <= c && c <= 'z') return 1;
            else return 0;
        case 77:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 76;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 78:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 't') return 1;
            else if (c == 'u') return 77;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 79:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'v') return 1;
            else if (c == 'w') return 25;
            else if ('x' <= c && c <= 'z') return 1;
            else return 0;
        case 80:
            if ('0' <= c && c <= '9') return 80;
            else return 0;
        case 81:
            if ((char)0 <= c && c <= ')') return 81;
            else if (c == '*') return 93;
            else if ('+' <= c && c <= (char)127) return 81;
            else return 0;
        case 82:
            if (c == '+') return 83;
            else if (c == '-') return 83;
            else if ('0' <= c && c <= '9') return 80;
            else return 0;
        case 83:
            if ('0' <= c && c <= '9') return 80;
            else return 0;
        case 84:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'e') return 1;
            else if (c == 'f') return 7;
            else if ('g' <= c && c <= 'z') return 1;
            else return 0;
        case 85:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'k') return 1;
            else if (c == 'l') return 50;
            else if ('m' <= c && c <= 'z') return 1;
            else return 0;
        case 86:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 19;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 87:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 49;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 88:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'r') return 1;
            else if (c == 's') return 20;
            else if ('t' <= c && c <= 'z') return 1;
            else return 0;
        case 89:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 24;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 90:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 71;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 91:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 't') return 1;
            else if (c == 'u') return 97;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 92:
            if ((char)0 <= c && c <= (char)9) return 92;
            else if (c == (char)10) return 41;
            else if ((char)11 <= c && c <= (char)127) return 92;
            else return 0;
        case 93:
            if ((char)0 <= c && c <= ')') return 81;
            else if (c == '*') return 93;
            else if ('+' <= c && c <= '.') return 81;
            else if (c == '/') return 42;
            else if ('0' <= c && c <= (char)127) return 81;
            else return 0;
        case 94:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'e') return 1;
            else if (c == 'f') return 8;
            else if ('g' <= c && c <= 'z') return 1;
            else return 0;
        case 95:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 15;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 96:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 16;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 97:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 10;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 98:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 55;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 99:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 9;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 100:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 't') return 1;
            else if (c == 'u') return 99;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 101:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'o') return 1;
            else if (c == 'p') return 100;
            else if ('q' <= c && c <= 'z') return 1;
            else return 0;
        case 102:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 6;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 103:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 4;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        }
        return 0;
    }
    int FuncLexer::action(int state)
    {
        switch (state)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 3;//number: realC
        case 4:
            return 4;//reserved: funct
        case 5:
            return 5;//reserved: manifold
        case 6:
            return 6;//reserved: function
        case 7:
            return 7;//reserved: manif
        case 8:
            return 8;//reserved: def
        case 9:
            return 9;//reserved: input
        case 10:
            return 10;//reserved: output
        case 11:
            return 11;//reserved: para
        case 12:
            return 12;//reserved: real
        case 13:
            return 13;//reserved: sint
        case 14:
            return 14;//reserved: uint
        case 15:
            return 15;//reserved: return
        case 16:
            return 16;//reserved: for
        case 17:
            return 17;//reserved: if
        case 18:
            return 18;//reserved: else
        case 19:
            return 19;//function1: sin
        case 20:
            return 20;//function1: cos
        case 21:
            return 21;//function1: exp
        case 22:
            return 22;//function1: ln
        case 23:
            return 23;//function1: log
        case 24:
            return 24;//function1: sqrt
        case 25:
            return 25;//function2: pow
        case 26:
            return 26;//format: spaces
        case 27:
            return 27;//format: enters
        case 28:
            return 28;//format: tab
        case 29:
            return 29;//division: semicolon
        case 30:
            return 30;//division: colon
        case 31:
            return 31;//division: dot
        case 32:
            return 32;//division: comma
        case 33:
            return 33;//braket: braceL
        case 34:
            return 34;//braket: braceR
        case 35:
            return 35;//braket: left
        case 36:
            return 36;//braket: right
        case 37:
            return 37;//braket: squareL
        case 38:
            return 38;//braket: squareR
        case 39:
            return 39;//braket: angleL
        case 40:
            return 40;//braket: angleR
        case 41:
            return 41;//anntation: anntationS
        case 42:
            return 42;//anntation: anntationM
        case 43:
            return 43;//operatmd: multi
        case 44:
            return 44;//operatmd: div
        case 45:
            return 45;//operatas: sub
        case 46:
            return 46;//operatas: add
        case 47:
            return 47;//value: value
        case 49:
            return 1;//id: id
        case 50:
            return 1;//id: id
        case 51:
            return 1;//id: id
        case 52:
            return 1;//id: id
        case 53:
            return 1;//id: id
        case 54:
            return 1;//id: id
        case 55:
            return 1;//id: id
        case 56:
            return 1;//id: id
        case 57:
            return 1;//id: id
        case 58:
            return 1;//id: id
        case 59:
            return 1;//id: id
        case 60:
            return 1;//id: id
        case 61:
            return 1;//id: id
        case 62:
            return 1;//id: id
        case 63:
            return 1;//id: id
        case 64:
            return 1;//id: id
        case 65:
            return 1;//id: id
        case 66:
            return 1;//id: id
        case 67:
            return 1;//id: id
        case 68:
            return 1;//id: id
        case 69:
            return 1;//id: id
        case 70:
            return 1;//id: id
        case 71:
            return 1;//id: id
        case 72:
            return 1;//id: id
        case 73:
            return 1;//id: id
        case 74:
            return 1;//id: id
        case 75:
            return 1;//id: id
        case 76:
            return 1;//id: id
        case 77:
            return 1;//id: id
        case 78:
            return 1;//id: id
        case 79:
            return 1;//id: id
        case 80:
            return 3;//number: realC
        case 84:
            return 1;//id: id
        case 85:
            return 1;//id: id
        case 86:
            return 1;//id: id
        case 87:
            return 1;//id: id
        case 88:
            return 1;//id: id
        case 89:
            return 1;//id: id
        case 90:
            return 1;//id: id
        case 91:
            return 1;//id: id
        case 94:
            return 1;//id: id
        case 95:
            return 1;//id: id
        case 96:
            return 1;//id: id
        case 97:
            return 1;//id: id
        case 98:
            return 1;//id: id
        case 99:
            return 1;//id: id
        case 100:
            return 1;//id: id
        case 101:
            return 1;//id: id
        case 102:
            return 1;//id: id
        case 103:
            return 1;//id: id
        }
        return 0;
    }
    int FuncLexer::GroupGet(int accept)
    {
        switch (accept)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 2;//number: realC
        case 4:
            return 3;//reserved: funct
        case 5:
            return 3;//reserved: manifold
        case 6:
            return 3;//reserved: function
        case 7:
            return 3;//reserved: manif
        case 8:
            return 3;//reserved: def
        case 9:
            return 3;//reserved: input
        case 10:
            return 3;//reserved: output
        case 11:
            return 3;//reserved: para
        case 12:
            return 3;//reserved: real
        case 13:
            return 3;//reserved: sint
        case 14:
            return 3;//reserved: uint
        case 15:
            return 3;//reserved: return
        case 16:
            return 3;//reserved: for
        case 17:
            return 3;//reserved: if
        case 18:
            return 3;//reserved: else
        case 19:
            return 4;//function1: sin
        case 20:
            return 4;//function1: cos
        case 21:
            return 4;//function1: exp
        case 22:
            return 4;//function1: ln
        case 23:
            return 4;//function1: log
        case 24:
            return 4;//function1: sqrt
        case 25:
            return 5;//function2: pow
        case 26:
            return 6;//format: spaces
        case 27:
            return 6;//format: enters
        case 28:
            return 6;//format: tab
        case 29:
            return 7;//division: semicolon
        case 30:
            return 7;//division: colon
        case 31:
            return 7;//division: dot
        case 32:
            return 7;//division: comma
        case 33:
            return 8;//braket: braceL
        case 34:
            return 8;//braket: braceR
        case 35:
            return 8;//braket: left
        case 36:
            return 8;//braket: right
        case 37:
            return 8;//braket: squareL
        case 38:
            return 8;//braket: squareR
        case 39:
            return 8;//braket: angleL
        case 40:
            return 8;//braket: angleR
        case 41:
            return 9;//anntation: anntationS
        case 42:
            return 9;//anntation: anntationM
        case 43:
            return 10;//operatmd: multi
        case 44:
            return 10;//operatmd: div
        case 45:
            return 11;//operatas: sub
        case 46:
            return 11;//operatas: add
        case 47:
            return 12;//value: value
        }
        return 0;
    }

    Pikachu::function FuncLexer::functionGet(int state)
    {
        regular RR;
        RR = (regular)state;
        switch (RR)
        {
        case FuncLexer::_sin_:
            return Pikachu::function::_sin_;

        case FuncLexer::_cos_:
            return Pikachu::function::_cos_;

        case FuncLexer::_exp_:
            return Pikachu::function::_exp_;

        case FuncLexer::_ln_:
            return Pikachu::function::_ln_;
        case FuncLexer::_log_:
            return Pikachu::function::_ln_;

        case FuncLexer::_sqrt_:
            return Pikachu::function::_sqrt_;

        default:
            break;
        }
        return Pikachu::function::_sin_;
    }
    Pikachu::operation FuncLexer::operationGet(int state)
    {
        regular RR;
        RR = (regular)state;
        switch (RR)
        {
        case FuncLexer::_multi_:
            return Pikachu::operation::_mul_;

        case FuncLexer::_div_:
            return Pikachu::operation::_div_;

        case FuncLexer::_sub_:
            return Pikachu::operation::_sub_;

        case FuncLexer::_add_:
            return Pikachu::operation::_add_;
        }
        return Pikachu::operation::_mul_;
    }
}
namespace Exp
{
    int ExpLexer::next(int state, const char c)
    {
        switch (state)
        {
        case 0:
            if (c == (char)9) return 17;
            else if (c == (char)10) return 16;
            else if (c == ' ') return 15;
            else if (c == '(') return 24;
            else if (c == ')') return 25;
            else if (c == '*') return 32;
            else if (c == '+') return 35;
            else if (c == ',') return 21;
            else if (c == '-') return 34;
            else if (c == '.') return 20;
            else if (c == '/') return 33;
            else if ('0' <= c && c <= '9') return 2;
            else if (c == ':') return 19;
            else if (c == ';') return 18;
            else if (c == '<') return 28;
            else if (c == '=') return 36;
            else if (c == '>') return 29;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '[') return 26;
            else if (c == ']') return 27;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'b') return 1;
            else if (c == 'c') return 48;
            else if (c == 'd') return 1;
            else if (c == 'e') return 47;
            else if (c == 'f') return 45;
            else if ('g' <= c && c <= 'h') return 1;
            else if (c == 'i') return 39;
            else if ('j' <= c && c <= 'k') return 1;
            else if (c == 'l') return 41;
            else if ('m' <= c && c <= 'o') return 1;
            else if (c == 'p') return 55;
            else if (c == 'q') return 1;
            else if (c == 'r') return 53;
            else if (c == 's') return 42;
            else if ('t' <= c && c <= 'z') return 1;
            else if (c == '{') return 22;
            else if (c == '}') return 23;
            else return 0;
        case 1:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 2:
            if (c == '.') return 37;
            else if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 3:
            if ('0' <= c && c <= '9') return 3;
            else if (c == 'E') return 58;
            else if (c == 'e') return 58;
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
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 8:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 9:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 10:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 11:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 12:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 13:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 14:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'z') return 1;
            else return 0;
        case 15:
            if (c == ' ') return 15;
            else return 0;
        case 16:
            if (c == (char)10) return 16;
            else return 0;
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
            return 0;
        case 24:
            return 0;
        case 25:
            return 0;
        case 26:
            return 0;
        case 27:
            return 0;
        case 28:
            return 0;
        case 29:
            return 0;
        case 30:
            return 0;
        case 31:
            if ((char)0 <= c && c <= ')') return 57;
            else if (c == '*') return 64;
            else if ('+' <= c && c <= (char)127) return 57;
            else return 0;
        case 32:
            return 0;
        case 33:
            if (c == '*') return 57;
            else if (c == '/') return 63;
            else return 0;
        case 34:
            if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 35:
            if ('0' <= c && c <= '9') return 2;
            else return 0;
        case 36:
            return 0;
        case 37:
            if ('0' <= c && c <= '9') return 3;
            else return 0;
        case 38:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'd') return 1;
            else if (c == 'e') return 7;
            else if ('f' <= c && c <= 'z') return 1;
            else return 0;
        case 39:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'e') return 1;
            else if (c == 'f') return 6;
            else if ('g' <= c && c <= 'z') return 1;
            else return 0;
        case 40:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'f') return 1;
            else if (c == 'g') return 12;
            else if ('h' <= c && c <= 'z') return 1;
            else return 0;
        case 41:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 11;
            else if (c == 'o') return 40;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 42:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'h') return 1;
            else if (c == 'i') return 60;
            else if ('j' <= c && c <= 'p') return 1;
            else if (c == 'q') return 50;
            else if ('r' <= c && c <= 'z') return 1;
            else return 0;
        case 43:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'o') return 1;
            else if (c == 'p') return 10;
            else if ('q' <= c && c <= 'z') return 1;
            else return 0;
        case 44:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 65;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 45:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 61;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 46:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'r') return 1;
            else if (c == 's') return 38;
            else if ('t' <= c && c <= 'z') return 1;
            else return 0;
        case 47:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'k') return 1;
            else if (c == 'l') return 46;
            else if ('m' <= c && c <= 'w') return 1;
            else if (c == 'x') return 43;
            else if ('y' <= c && c <= 'z') return 1;
            else return 0;
        case 48:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 62;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 49:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 13;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 50:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 49;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 51:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 't') return 1;
            else if (c == 'u') return 44;
            else if ('v' <= c && c <= 'z') return 1;
            else return 0;
        case 52:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 's') return 1;
            else if (c == 't') return 51;
            else if ('u' <= c && c <= 'z') return 1;
            else return 0;
        case 53:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'd') return 1;
            else if (c == 'e') return 52;
            else if ('f' <= c && c <= 'z') return 1;
            else return 0;
        case 54:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'v') return 1;
            else if (c == 'w') return 14;
            else if ('x' <= c && c <= 'z') return 1;
            else return 0;
        case 55:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'n') return 1;
            else if (c == 'o') return 54;
            else if ('p' <= c && c <= 'z') return 1;
            else return 0;
        case 56:
            if ('0' <= c && c <= '9') return 56;
            else return 0;
        case 57:
            if ((char)0 <= c && c <= ')') return 57;
            else if (c == '*') return 64;
            else if ('+' <= c && c <= (char)127) return 57;
            else return 0;
        case 58:
            if (c == '+') return 59;
            else if (c == '-') return 59;
            else if ('0' <= c && c <= '9') return 56;
            else return 0;
        case 59:
            if ('0' <= c && c <= '9') return 56;
            else return 0;
        case 60:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 8;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        case 61:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'q') return 1;
            else if (c == 'r') return 5;
            else if ('s' <= c && c <= 'z') return 1;
            else return 0;
        case 62:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'r') return 1;
            else if (c == 's') return 9;
            else if ('t' <= c && c <= 'z') return 1;
            else return 0;
        case 63:
            if ((char)0 <= c && c <= (char)9) return 63;
            else if (c == (char)10) return 30;
            else if ((char)11 <= c && c <= (char)127) return 63;
            else return 0;
        case 64:
            if ((char)0 <= c && c <= ')') return 57;
            else if (c == '*') return 64;
            else if ('+' <= c && c <= '.') return 57;
            else if (c == '/') return 31;
            else if ('0' <= c && c <= (char)127) return 57;
            else return 0;
        case 65:
            if ('0' <= c && c <= '9') return 1;
            else if ('A' <= c && c <= 'Z') return 1;
            else if (c == '_') return 1;
            else if ('a' <= c && c <= 'm') return 1;
            else if (c == 'n') return 4;
            else if ('o' <= c && c <= 'z') return 1;
            else return 0;
        }
        return 0;
    }
    int ExpLexer::action(int state)
    {
        switch (state)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 3;//number: realC
        case 4:
            return 4;//reserved: return
        case 5:
            return 5;//reserved: for
        case 6:
            return 6;//reserved: if
        case 7:
            return 7;//reserved: else
        case 8:
            return 8;//function1: sin
        case 9:
            return 9;//function1: cos
        case 10:
            return 10;//function1: exp
        case 11:
            return 11;//function1: ln
        case 12:
            return 12;//function1: log
        case 13:
            return 13;//function1: sqrt
        case 14:
            return 14;//function2: pow
        case 15:
            return 15;//format: spaces
        case 16:
            return 16;//format: enters
        case 17:
            return 17;//format: tab
        case 18:
            return 18;//division: semicolon
        case 19:
            return 19;//division: colon
        case 20:
            return 20;//division: dot
        case 21:
            return 21;//division: comma
        case 22:
            return 22;//braket: braceL
        case 23:
            return 23;//braket: braceR
        case 24:
            return 24;//braket: left
        case 25:
            return 25;//braket: right
        case 26:
            return 26;//braket: squareL
        case 27:
            return 27;//braket: squareR
        case 28:
            return 28;//braket: angleL
        case 29:
            return 29;//braket: angleR
        case 30:
            return 30;//anntation: anntationS
        case 31:
            return 31;//anntation: anntationM
        case 32:
            return 32;//operatmd: multi
        case 33:
            return 33;//operatmd: div
        case 34:
            return 34;//operatas: sub
        case 35:
            return 35;//operatas: add
        case 36:
            return 36;//value: value
        case 38:
            return 1;//id: id
        case 39:
            return 1;//id: id
        case 40:
            return 1;//id: id
        case 41:
            return 1;//id: id
        case 42:
            return 1;//id: id
        case 43:
            return 1;//id: id
        case 44:
            return 1;//id: id
        case 45:
            return 1;//id: id
        case 46:
            return 1;//id: id
        case 47:
            return 1;//id: id
        case 48:
            return 1;//id: id
        case 49:
            return 1;//id: id
        case 50:
            return 1;//id: id
        case 51:
            return 1;//id: id
        case 52:
            return 1;//id: id
        case 53:
            return 1;//id: id
        case 54:
            return 1;//id: id
        case 55:
            return 1;//id: id
        case 56:
            return 3;//number: realC
        case 60:
            return 1;//id: id
        case 61:
            return 1;//id: id
        case 62:
            return 1;//id: id
        case 65:
            return 1;//id: id
        }
        return 0;
    }
    int ExpLexer::GroupGet(int accept)
    {
        switch (accept)
        {
        case 1:
            return 1;//id: id
        case 2:
            return 2;//number: integer
        case 3:
            return 2;//number: realC
        case 4:
            return 3;//reserved: return
        case 5:
            return 3;//reserved: for
        case 6:
            return 3;//reserved: if
        case 7:
            return 3;//reserved: else
        case 8:
            return 4;//function1: sin
        case 9:
            return 4;//function1: cos
        case 10:
            return 4;//function1: exp
        case 11:
            return 4;//function1: ln
        case 12:
            return 4;//function1: log
        case 13:
            return 4;//function1: sqrt
        case 14:
            return 5;//function2: pow
        case 15:
            return 6;//format: spaces
        case 16:
            return 6;//format: enters
        case 17:
            return 6;//format: tab
        case 18:
            return 7;//division: semicolon
        case 19:
            return 7;//division: colon
        case 20:
            return 7;//division: dot
        case 21:
            return 7;//division: comma
        case 22:
            return 8;//braket: braceL
        case 23:
            return 8;//braket: braceR
        case 24:
            return 8;//braket: left
        case 25:
            return 8;//braket: right
        case 26:
            return 8;//braket: squareL
        case 27:
            return 8;//braket: squareR
        case 28:
            return 8;//braket: angleL
        case 29:
            return 8;//braket: angleR
        case 30:
            return 9;//anntation: anntationS
        case 31:
            return 9;//anntation: anntationM
        case 32:
            return 10;//operatmd: multi
        case 33:
            return 10;//operatmd: div
        case 34:
            return 11;//operatas: sub
        case 35:
            return 11;//operatas: add
        case 36:
            return 12;//value: value
        }
        return 0;
    }
    Pikachu::function ExpLexer::functionGet(int state)
    {
        regular RR;
        RR = (regular)state;
        switch (RR)
        {
        case ExpLexer::_sin_:
            return Pikachu::function::_sin_;

        case ExpLexer::_cos_:
            return Pikachu::function::_cos_;

        case ExpLexer::_exp_:
            return Pikachu::function::_exp_;

        case ExpLexer::_ln_:
            return Pikachu::function::_ln_;
        case ExpLexer::_log_:
            return Pikachu::function::_ln_;

        case ExpLexer::_sqrt_:
            return Pikachu::function::_sqrt_;
        
        default:
            break;
        }
        return Pikachu::function::_sin_;
    }
    Pikachu::operation ExpLexer::operationGet(int state)
    {
        regular RR;
        RR = (regular)state;
        switch (RR)
        {
        case ExpLexer::_multi_:
            return Pikachu::operation::_mul_;

        case ExpLexer::_div_:
            return Pikachu::operation::_div_;

        case ExpLexer::_sub_:
            return Pikachu::operation::_sub_;

        case ExpLexer::_add_:
            return Pikachu::operation::_add_;
        }
        return Pikachu::operation::_mul_;
    }
    const size_t ExpPraser::StateCount = 45;
    const size_t ExpPraser::NonTerminalCount = 12;
    const size_t ExpPraser::TerminalCount = 36;
    const size_t ExpPraser::RulesCount = 28;
    const int ExpPraser::GOTO[45][12] = { \
    {1, 6, 10, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 178, 30, 34, 38, 42}, \
    {1, 1, 1, 1, 1, 118, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 98, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 14, 114, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 118, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 14, 1, 1, 130, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 138, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 150, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 158, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 170, 14, 18, 1, 22, 26, 30, 34, 38, 42}, \
    {1, 1, 1, 106, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
    //==============================
    const int ExpPraser::ACTION[45][37] = { \
    {1, 46, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 15, 1, 1, 1, 15, 1, 1, 1, 1, 1, 1, 122, 126, 15, 15, 1}, \
    {31, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 31, 1, 1, 31, 1, 1, 1, 31, 1, 1, 1, 1, 1, 1, 31, 31, 31, 31, 1}, \
    {47, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 47, 1, 1, 47, 1, 1, 1, 47, 1, 1, 1, 1, 1, 1, 47, 47, 47, 47, 1}, \
    {63, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 63, 1, 1, 63, 1, 1, 1, 63, 1, 1, 1, 1, 1, 1, 63, 63, 63, 63, 1}, \
    {59, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 59, 1, 1, 59, 1, 1, 1, 59, 1, 1, 1, 1, 1, 1, 59, 59, 59, 59, 1}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 166, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 146, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 1, 1, 55, 1, 1, 1, 55, 1, 1, 1, 1, 1, 1, 55, 55, 55, 55, 134}, \
    {71, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 71, 1, 1, 71, 1, 1, 1, 71, 1, 1, 1, 1, 1, 1, 71, 71, 71, 71, 1}, \
    {75, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 75, 1, 1, 75, 1, 1, 1, 75, 1, 1, 1, 1, 1, 1, 75, 75, 75, 75, 1}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 87, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 91, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 95, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 99, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 103, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 107, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 111, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 23, 23, 23, 1, 1, 1, 1, 23, 23, 23, 23, 23, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 23, 23, 1}, \
    {1, 27, 27, 27, 1, 1, 1, 1, 27, 27, 27, 27, 27, 27, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 27, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 110, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {55, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 55, 1, 1, 55, 1, 1, 1, 55, 1, 1, 1, 1, 1, 1, 55, 55, 55, 55, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {67, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 67, 1, 1, 67, 1, 1, 1, 67, 1, 1, 1, 1, 1, 1, 67, 67, 67, 67, 1}, \
    {19, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 19, 1, 1, 19, 1, 1, 1, 19, 1, 1, 1, 1, 1, 1, 122, 126, 19, 19, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 39, 39, 39, 1, 1, 1, 1, 39, 39, 39, 39, 39, 39, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 1, 1, 1, 1, 1, 1, 1, 1, 1, 39, 39, 1}, \
    {1, 43, 43, 43, 1, 1, 1, 1, 43, 43, 43, 43, 43, 43, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 1, 1, 1, 1, 1, 1, 1, 1, 1, 43, 43, 1}, \
    {35, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 1, 1, 35, 1, 1, 1, 35, 1, 1, 1, 1, 1, 1, 35, 35, 35, 35, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 142, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 154, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 162, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {83, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 83, 1, 1, 83, 1, 1, 1, 83, 1, 1, 1, 1, 1, 1, 83, 83, 83, 83, 1}, \
    {1, 102, 50, 54, 1, 1, 1, 1, 58, 62, 66, 70, 74, 78, 82, 1, 1, 1, 1, 1, 1, 1, 1, 1, 86, 1, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 174, 1, 1, 1, 1, 1, 1, 1, 1, 90, 94, 1}, \
    {79, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 79, 1, 1, 79, 1, 1, 1, 79, 1, 1, 1, 1, 1, 1, 79, 79, 79, 79, 1}, \
    {51, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 51, 1, 1, 51, 1, 1, 1, 51, 1, 1, 1, 1, 1, 1, 51, 51, 51, 51, 1} };
    //==============================
    const int ExpPraser::RulesToSymbol[28] = { \
    0,\
    1,\
    1,\
    2,\
    2,\
    3,\
    3,\
    4,\
    4,\
    5,\
    5,\
    6,\
    6,\
    7,\
    7,\
    7,\
    7,\
    8,\
    8,\
    9,\
    9,\
    10,\
    10,\
    10,\
    10,\
    10,\
    10,\
    11 };
    //==============================
    const int ExpPraser::RulesLength[28] = { \
    1,\
    4,\
    1,\
    1,\
    3,\
    1,\
    1,\
    1,\
    3,\
    1,\
    1,\
    1,\
    2,\
    1,\
    1,\
    1,\
    3,\
    1,\
    1,\
    4,\
    6,\
    1,\
    1,\
    1,\
    1,\
    1,\
    1,\
    1 };
    //==============================
    const char* const ExpPraser::RulesName[28] = { \
    "all->Expression ",\
    "Expression->id value EXP_RIGHT semicolon ",\
    "Expression->EXP_RIGHT ",\
    "EXP_RIGHT->EXP_MUL ",\
    "EXP_RIGHT->EXP_RIGHT [operatas] EXP_MUL ",\
    "[operatas]->sub ",\
    "[operatas]->add ",\
    "EXP_MUL->EXP_MINUS ",\
    "EXP_MUL->EXP_MUL [operatmd] EXP_MINUS ",\
    "[operatmd]->multi ",\
    "[operatmd]->div ",\
    "EXP_MINUS->UNIT ",\
    "EXP_MINUS->[operatas] UNIT ",\
    "UNIT->id ",\
    "UNIT->CALL ",\
    "UNIT->[number] ",\
    "UNIT->left EXP_RIGHT right ",\
    "[number]->integer ",\
    "[number]->realC ",\
    "CALL->[function1] left EXP_RIGHT right ",\
    "CALL->[function2] left EXP_RIGHT comma EXP_RIGHT right ",\
    "[function1]->sin ",\
    "[function1]->cos ",\
    "[function1]->exp ",\
    "[function1]->ln ",\
    "[function1]->log ",\
    "[function1]->sqrt ",\
    "[function2]->pow " };
    //==============================
    const int ExpPraser::Implicit[28] = { \
    0, \
    0, \
    0, \
    1, \
    0, \
    1, \
    1, \
    1, \
    0, \
    1, \
    1, \
    1, \
    0, \
    0, \
    0, \
    0, \
    0, \
    1, \
    1, \
    0, \
    0, \
    1, \
    1, \
    1, \
    1, \
    1, \
    1, \
    1 };

}

