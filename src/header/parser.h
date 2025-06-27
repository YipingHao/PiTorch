#ifndef parser_H_hiadfghuiadfhioasdfhiasdfikhasdfhiasdfhklsdhnfakl
#define parser_H_hiadfghuiadfhioasdfhiasdfikhasdfhiasdfhklsdhnfakl
namespace Pikachu
{
	int matrixGet(FILE* fp, vector<double>& output, size_t& row, size_t& column);
	int vectorGet(FILE* fp, vector<double>& output);
}

namespace Pikachu
{
	class BuildInfor;

	typedef hyperlex::Morpheme lex;
	typedef hyperlex::GrammarTree AST;
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
		enum type
		{
			_sint_,
			_unit_,
			_bool_,
			_complex_,
			_real_,
		};
		ConstObj();
		ConstObj(size_t dim, bool Scalar, enum type TTT, const char* Name);
		ConstObj(sint Rvalue, type T);
		ConstObj(double Rvalue);
		ConstObj(ConstObj* left, const char* op, ConstObj* right);
		ConstObj(const char* op, ConstObj* right);

		~ConstObj();

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
		void assign(sint right);
		void assign(const ConstObj* srcR);
		void assign(const ConstObj* srcR, size_t No);
		void assign(size_t NO, sint right);
		void demo(FILE* fp = stdout) const;
		void copy(const ConstObj* src);
		void copy(const ConstObj* src, size_t No);

	protected:
		type T;
		bool scalar;
		vector<status> S;
		vector<value> V;
		void demo(FILE* fp, type TT, status SS, const value& VV) const;
	public:
		inline bool ValuedScalarSint(void) const
		{
			return T == _sint_ && scalar && S[0] == valued;
		}
		inline sint GetSint(void) const
		{
			return V[0].i;
		}
		inline status GetState(size_t No = 0)const
		{
			return S[No];
		}
		inline sint GetInt(size_t No = 0) const
		{
			return V[No].i;
		}
		inline type GetType(void) const
		{
			return T;
		}
		inline bool SorUint(void) const
		{
			return T == _sint_ || T == _unit_;
		}
		inline bool GetScalar(void)const { return scalar; }
		inline size_t GetDim(void) const { return S.count(); };
	};
	class var : public CompilerObj
	{
	public:

		var();
		~var();

		enum authority
		{
			literal,
			valued,
		};


		void ruin(void);
		void demo(FILE* fp = stdout) const;
	protected:
		char* attribute;
		void* infor;
		vector<void*> infors;
		void initial(void);
	public:
		void SetAttri(const char* NewName);
		inline const char* SetAttri(void)const
		{
			return attribute;
		}
		bool compareAttri(const char* srcR) const;
		inline Expres::node* Getnode(void) const
		{
			return (Expres::node*)infor;
		}
		inline Expres::node* Getnode(size_t No) const
		{
			return (Expres::node*)infors[No];
		}
		inline void SetInfor(Expres::node* srcR)
		{
			infor = (void*)srcR;
		}
		inline void SetInfor(Expres::node* srcR, size_t No)
		{
			infors[No] = srcR;
		}
		inline bool scalar(void) const
		{
			return infors.count() == 0;
		}
		inline size_t count(void)
		{
			return infors.count() != 0 ? infors.count() : 1;
		}
		//inline size_t dim(void)
		inline size_t SetCount(size_t dim) 
		{
			infors.recount(dim);
			for (size_t i = 0; i < dim; i++)
			{
				infors[i] = NULL;
			}
		}
	};
	class func : public CompilerObj
	{
	public:
		func();
		~func();
		friend class BuildInfor;
	protected:
		Expres* Exp;
		void ruin(void);
		size_t InputCount;
		size_t OutputCount;
		size_t ParaCount;
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
	class context;
	class BuildInfor
	{
	public:
		BuildInfor();
		~BuildInfor();
		enum errorType
		{
			NoError = 0,
			PretreatLEXICAL,
			PretreatGRAMMAR,
			PretreatRepeat,
			PretreatOpenfail,
			PretreatNone,
			ErrorinputLEXICAL,
			ErrorinputGrammar,

			ErrorUnsupportType,
			ErrorRepeatVarDef,
			ErrorMissingVarDef,
			ErrorIndexOutofRange,
			ErrorNeedAInt,
			ErrorNameNULL,
			WrongEntrance,

			ErrorInitialAorS,
			//array dim not equal, assignment between 
			//scalar and array
			ErrorAssignType,

			SymbolicAlreadyDef,
			VarAlreadDef,
			TooMuchPara,
			TooMuchInput,
			NoneOutput,
			UndefineOutput,

			ErrorNotAConst,
			ErrorUnsupportFunc,
			ErrorUnKnowEXP,
			buildUndone,
		};
		int build(const char* FileName, context* dst);
		void ErrorDemo(FILE* fp = stdout) const;
		void clear(void);
		friend class context;
	protected:
		hyperlex::Morpheme MorphemePre;
		hyperlex::Morpheme LexicalSource;

		AST* ASTree;

		errorType errorCode;
		size_t errorInfor1;
		size_t errorInfor2;

		char* errorInfor3;
		bool errorInfor4;

		GTNode* ErrorNode;

		void initial(void);

		int pretreatment(const char* input, lex& output);
		void NeglectNullToken(lex& eme) const;
		int buildGanalysis(const lex& eme, context* dst);
		int buildAll(const lex& eme, AST& Tree, context* dst);

		int buildConstObj(const lex& eme, GTNode* GTarget, context* dst);
		int buildExp(const lex& eme, GTNode* GTarget, context* dst);
		int buildSymbolic(const lex& eme, GTNode* GTarget, context* dst);
		int buildNet(const lex& eme, GTNode* GTarget, context* dst);
		int buildDiff(const lex& eme, GTNode* GTarget, context* dst);
		
		int GetIDdim(size_t& dim, const lex& eme, GTNode* GTarget, context* dst);
		int SetAConstObj(const lex& eme, GTNode* GTarget, ConstObj::type Type, context* dst);
		int GetAConst(ConstObj*& output, const lex& eme, GTNode* GTarget, context* dst);
		int GetAVar(var*& output, const lex& eme, GTNode* EXP_RIGHT, context* dst);

		int addVar(const lex& eme, GTNode* PARA, context* dst, func* Func, const char* attri);
		int buildSymbolicName(const lex& eme, GTNode* PARA, context* dst, func* Func);
		int buildSymbolicPara(const lex& eme, GTNode* PARA, context* dst, func* Func);
		int buildSymbolicBody(const lex& eme, GTNode* PARA, context* dst, func* Func);
		int buildSymbolicCheck(const lex& eme, GTNode* PARA, context* dst, func* Func);
		size_t getValueDim(GTNode* GTarget);
	};
	class context
	{
	public:
		friend class BuildInfor;
		context();
		~context();
		void ruin(void);
		var* search(const char* name)const;
		var* SearchLocal(const char* name)const;
		ConstObj* searchConst(const char* name)const;
		ConstObj* SearchConstLocal(const char* name)const;
		func* searchFuncs(const char* name) const;
		func* searchFuncsLocal(const char* name) const;
		void demo(FILE* fp = stdout) const;
		void append(context* child);

		int build(const char* FileName);
		void clear(void);

		enum state
		{
			NoError,
			Undone,
			Error,
		};
	private:

		state S;


		vector<ConstObj*> Cobj;
		vector<var*> global;
		vector<func*> funcs;
		vector<NetInContext*> nets;
		context* parent;
		vector<context*> childs;
		void initial(void);

	};
}


#endif // !parser_H_hiadfghuiadfhioasdfhiasdfikhasdfhiasdfhklsdhnfakl

