#include"../src/header/Pikachu.h"
#include"../extern/header/all.h"

using namespace Pikachu;
static bool compare(const char* str1, const char* str2);
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;

class CompilerObj
{
public:
    typedef long long int sint;
    CompilerObj();
    ~CompilerObj();
    bool eqaul(const char* opR) const;
    void SetName(const char* NewName);
    inline const char* GetName(void) const { return name; }
protected:
    char* name;
    void ruinCO(void);
};
class ConstObj : public CompilerObj
{
public:

    ConstObj();
    ~ConstObj();
    enum type
    {
        _sint_,
        _unit_,
        _bool_,
        _complex_,
        _real_,
    };
    union value
    {
        sint i;
        size_t u;
        void* t;//tensor
        bool b;
        double f;
    };
    enum status
    {
        valued,
        liberal,
    };
    void demo(FILE* fp = stdout) const;
    inline sint GetInt(size_t No = 0) const {
        return V[No].i;
    }
private:
    type T;
    bool scalar;
    vector<status> S;
    vector<value> V;
    void demo(FILE* fp, type TT, status SS, const value & VV) const;
};
class var : public CompilerObj
{
public:
    
    var();
    ~var();
    
    enum authority
    {
        literal,
        read,
        write,
        owned,
    };
    
    
    void ruin(void);

    void demo(FILE* fp = stdout) const;
private:

    
};
class func : public CompilerObj
{
public:
    func();
    ~func();

private:
    Expres* Exp;
    void ruin(void);
};
class NetInContext : public CompilerObj
{
public:
    NetInContext();
    ~NetInContext();

private:
    NetWork* net;
    void ruin(void);
};
class context
{
public:
    context();
    ~context();
    void ruin(void);
    var* search(const char* name)const;
    var* SearchLocal(const char* name)const;
    void demo(FILE* fp = stdout) const;
private:
    vector<var*> global;
    vector<func*> func;
    vector<NetInContext*> nets;
    context* parent;
    vector<context*> childs;

};



CompilerObj::CompilerObj()
{
    name = NULL;
}
CompilerObj::~CompilerObj()
{
    ruinCO();
}
void CompilerObj::ruinCO(void)
{
    free(name);
    name = NULL;
}
bool CompilerObj::eqaul(const char* opR) const
{
    return compare(opR, name);
}
void CompilerObj::SetName(const char* NewName)
{
    size_t i;
    free(name);
    name = NULL;
    if (!NewName) return;

    size_t len = 0;
    while (NewName[len] != '\0') ++len;

    name = (char*)(malloc((len + 1) * sizeof(char)));
    for (i = 0; i <= len; ++i)
    {
        name[i] = NewName[i];
    }
}

ConstObj::ConstObj()
{
    T = _sint_;
    scalar = true;
}
ConstObj::~ConstObj()
{

}
void ConstObj::demo(FILE* fp = stdout) const
{
    const char* type_ = "null";
    switch (T)
    {
    case ConstObj::_sint_:
        type_ = "sint";
        break;
    case ConstObj::_unit_:
        type_ = "unit";
        break;
    case ConstObj::_bool_:
        type_ = "bool";
        break;
    case ConstObj::_complex_:
        type_ = "complex";
        break;
    case ConstObj::_real_:
        type_ = "real";
        break;
    default:
        break;
    }
    if (scalar)
    {
        fprintf(fp, "%s %s = ", type_, name);
        demo(fp, T, S[0], V[0]);
    }
    else
    {
        fprintf(fp, "%s[%zu] %s = [", type_, V.count(), name);
        if (V.count()) demo(fp, T, S[0], V[0]);
        for (size_t i = 1; i < V.count(); i++)
        {
            fprintf(fp, ", ");
            demo(fp, T, S[i], V[i]);
        }
        fprintf(fp, "]");
    }

}
void ConstObj::demo(FILE* fp, type TT, status SS, const value& VV) const
{
    if (SS == status::liberal)
        fprintf(fp, "???");
    else
    {
        switch (TT)
        {
        case ConstObj::_sint_:
            fprintf(fp, "%lld", (long long)VV.i);
            break;
        case ConstObj::_unit_:
            fprintf(fp, "%zu", VV.u);
            break;
        case ConstObj::_bool_:
            if (VV.b)
                fprintf(fp, "true");
            else
                fprintf(fp, "false");
            break;
        case ConstObj::_complex_:
            fprintf(fp, "%lf", VV.f);
            break;
        case ConstObj::_real_:
            fprintf(fp, "%lf", VV.f);
            break;
        default:
            break;
        }
    }


}


var::var()
{
    SetName("implicit");
}
var::~var()
{
    ruin();
}
void var::ruin(void)
{
    ruinCO();
}
void var::demo(FILE* fp = stdout) const
{
    
}


func::func()
{
    Exp = NULL;
}
func::~func()
{
    ruin();
}
void func::ruin(void)
{
    delete Exp;
}


NetInContext::NetInContext()
{
    net = NULL;
}
NetInContext::~NetInContext()
{
    ruin();
}
void NetInContext::ruin(void)
{
    delete net;
}



context::context()
{
}
context::~context()
{
    ruin();
}
void context::ruin(void)
{
    for (size_t i = 0; i < global.count(); i++)
    {
        delete global[i];
    }
    global.clear();
    childs.clear();
}
void context::demo(FILE* fp = stdout) const
{

}

var* context::search(const char* name)const
{
    var* value = SearchLocal(name);
    if (value != NULL) return value;
    context* now = parent;
    while (now != NULL)
    {
        var* temp = now->SearchLocal(name);
        if (temp != NULL) return temp;
        now = parent->parent;
    }
    return NULL;
}
var* context::SearchLocal(const char* name)const
{
    for (size_t i = 0; i < global.count(); i++)
    {
        if (global[i]->eqaul(name)) return global[i];
    }
    return NULL;
}



static bool compare(const char* str1, const char* str2)
{
    size_t i;
    for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
    return str1[i] == str2[i];
}






