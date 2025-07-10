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

	
	class context;
	class IDinfor;
	class TensorID;
	class ValueList;

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
			_uint_,
			_bool_,
			_complex_,
			_real_,
		};
		ConstObj();
		ConstObj(sint Rvalue, type T);
		ConstObj(double Rvalue);
		ConstObj(ConstObj* left, const char* op, ConstObj* right);
		ConstObj(const char* op, ConstObj* right);
		ConstObj(size_t dim, bool Scalar, type TTT, const char* Name);
		ConstObj(function func, const ConstObj* srcR); 
		ConstObj(function2 func, const ConstObj* left, const ConstObj* srcR);
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
		void assign(size_t No, const ConstObj* srcR);
		void assign(size_t NO, sint right);
		void demo(FILE* fp = stdout) const;
		void copy(const ConstObj* src);
		void copy(const ConstObj* src, size_t No);

		bool inline typeCheck(const ConstObj* src) const
		{
			if (src->T == T) return true;
			if (src->T == _sint_ && T == _uint_) return true; // 整型可以赋值给无符号整型
			if (src->T == _uint_ && T == _sint_) return true; // 无符号整型可以赋值给整型
			//if (src->T == _bool_ && T == _sint_) return true; // 布尔可以赋值给整型
			//if (src->T == _bool_ && T == _uint_) return true; // 布尔可以赋值给无符号整型
			//if (src->T == _real_ && T == _sint_) return true; // 浮点可以赋值给整型
			//if (src->T == _real_ && T == _uint_) return true; // 浮点可以赋值给无符号整型
			//if (src->T == _complex_ && T == _sint_) return true; // 复数可以赋值给整型
			//if (src->T == _complex_ && T == _uint_) return true; // 复数可以赋值给无符号整型
			//if (src->T == _complex_ && T == _real_) return true; // 复数可以赋值给浮点
			return false; // 不支持的类型转换
		}	
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
			switch (T)
			{
			case Pikachu::ConstObj::_sint_:
				return V[No].i;
			case Pikachu::ConstObj::_uint_:
				return (sint)V[No].u;
			case Pikachu::ConstObj::_bool_:
				return (sint)V[No].b;
			case Pikachu::ConstObj::_complex_:
				return (sint)V[No].f;
			case Pikachu::ConstObj::_real_:
				return (sint)V[No].f;
			default:
				break;
			}
			return V[No].i;
		}
		inline double GetReal(size_t No = 0) const
		{
			switch (T)
			{
			case Pikachu::ConstObj::_sint_:
				return (double)V[No].i;
			case Pikachu::ConstObj::_uint_:
				return (double)V[No].u;
			case Pikachu::ConstObj::_bool_:
				return (double)V[No].b;
			case Pikachu::ConstObj::_complex_:
				return (double)V[No].f;
			case Pikachu::ConstObj::_real_:
				return (double)V[No].f;
			default:
				break;
			}
			return V[No].f;
		}
		inline type GetType(void) const
		{
			return T;
		}
		inline bool SorUint(void) const
		{
			return T == _sint_ || T == _uint_;
		}
		inline bool GetScalar(void)const { return scalar; }
		inline size_t GetDim(void) const { return S.count(); };
		inline bool isInt(void)	const
		{
			return T == _sint_ || T == _uint_;
		}
		inline bool isReal(void) const
		{
			return T == _real_;
		}
	};
	class var : public CompilerObj
	{
	public:
		var(Expres::node* srcR);
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
		bool Scalar;
		//void* infor;
		vector<void*> infors;
		void initial(void);
	public:
		void SetAttri(const char* NewName);
		inline const char* GetAttri(void)const
		{
			return attribute;
		}
		bool compareAttri(const char* srcR) const;
		inline Expres::node* Getnode(void) const
		{
			//return (Expres::node*)infor;
			return (Expres::node*)infors[0];
		}
		inline Expres::node* Getnode(size_t No) const
		{
			return (Expres::node*)infors[No];
		}
		inline Node* GetTensor(size_t No) const
		{
			return (Node*)infors[No];
		}
		inline void SetInfor(Expres::node* srcR)
		{
			//infor = (void*)srcR;
			infors[0] = srcR;
		}
		inline void SetInfor(Expres::node* srcR, size_t No)
		{
			infors[No] = srcR;
		}
		inline void SetInfor(void* srcR, size_t No)
		{
			infors[No] = srcR;
		}
		inline bool scalar(void) const
		{
			return Scalar;
			//return infors.count() == 0;
		}
		inline size_t count(void)
		{
			return infors.count();
		}
		//inline size_t dim(void)
		inline size_t SetCount(size_t dim) 
		{
			infors.recount(dim);
			for (size_t i = 0; i < dim; i++)
			{
				infors[i] = NULL;
			}
			Scalar = false;
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
		context* realm;
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
		friend class BuildInfor;
	private:
		context* realm;
		NetWork* net;
		void ruin(void);
	};
	
	
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

			ErrorUnExpectedType,
			ErrorUnsupportType,
			ErrorRepeatVarDef,
			ErrorMissingConstVarDef,
			ErrorMissingVarDef,
			ErrorMissingFuncDef,
			ErrorMinusIndex,
			ErrorIndexOutofRange,
			ErrorSAmissMatch,
			ErrorNeedAInt,
			ErrorNameNULL,
			WrongEntrance,

			ErrorInitialAorS,
			//array dim not equal, assignment between 
			//scalar and array
			ErrorAssignType,
			ErrorAssignDim,
			
			ErrorInvalidRvalue,

			SymbolicAlreadyDef,
			VarAlreadDef,
			TooMuchPara,
			TooMuchInput,
			NoneOutput,
			UndefineOutput,
			NeedAscalar,
			
			ErrorListTypeMismatch,
			AssignAparaOrinput,
			ShouldNotAssignGlobalConst,

			ErrorNotAConst,
			ErrorUnsupportFunc,
			ErrorUnKnowEXP,

			ErrorUndefined,
			buildUndone,
		};
		int build(const char* FileName, context* dst);
		void ErrorDemo(FILE* fp = stdout) const;
		void clear(void);
		friend class context;
		friend class IDinfor;
		friend class Indexs;
		friend class TensorID;
		friend class ValueList;
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
		
		int GetIDdim(size_t& dim, const lex& eme, GTNode* ID, context* dst);
		int GetIDindex(size_t& index, const lex& eme, GTNode* ID, context* dst);
		
		
		int GetAConst(ConstObj*& output, const lex& eme, GTNode* GTarget, context* dst);
		int GetAExpres(Expres::node*& output, const lex& eme, GTNode* EXP_RIGHT, context* dst, func* Func);

		enum routine
		{
			expression,
			network,
		};
		
		int buildRoutineName(routine Rou, const lex& eme, GTNode* PARA, context* dst);
		int buildRoutinePara(routine Rou, const lex& eme, GTNode* PARA, context* dst);
		
		int buildSymbolicBody(const lex& eme, GTNode* PARA, context* dst, func* Func);
		int buildSymbolicCheck(const lex& eme, GTNode* PARA, context* dst, func* Func);
		size_t getValueDim(GTNode* GTarget);

		int buildNETBODY(const lex& eme, GTNode* NETBODY, NetInContext* Net);
		int buildTENSOR(const lex& eme, GTNode* NET_STATEMENT, NetInContext* Net);
		Node::OpType ParseOpType(const lex& eme, GTNode* OPERATOR);
		int buildNETCheck(const lex& eme, GTNode* NETBODY, context* dst, NetInContext* Net);
	};
	class IDinfor : public CompilerObj
	{
	public:
		IDinfor();
		~IDinfor();
		int build(const lex& eme, GTNode* ID_, BuildInfor* infor, context* dst);
		int build(const char* id, GTNode* Backup, BuildInfor* infor, context* dst);
		void* GetLocalTensorR(int& error, BuildInfor* infor, context* dst);//local
		var* GetLocalVarR(int &error, BuildInfor* infor, context* dst);//local
		ConstObj* GetAllConstR(int& error, BuildInfor* infor, context* dst);//global and local
		var* SetVarL(int& error, BuildInfor* infor, context* dst, const char* attri);
		ConstObj* SetConstL(int& error, BuildInfor* infor, context* dst, ConstObj::type TTT);
		void AssignLocalVarL(int& error, BuildInfor* infor, context* dst, void* SrcR);
		var* GetLocalVarL(int& error, BuildInfor* infor, context* dst);
		var* GetLocalTensorL(int& error, BuildInfor* infor, context* dst);
		ConstObj* GetLocalConstL(int& error, BuildInfor* infor, context* dst);
		func* GetAllFuncR(int& error, BuildInfor* infor, context* dst);
	protected:
		bool scalar;
		size_t index;
		GTNode* backup;
	public:
		size_t GetDim(void)const
		{
			return (scalar ? 1 : index);
		}
		size_t GetIndex(void)const
		{
			return (scalar ? 0 : index);
		}
		bool GetScalar(void)const
		{
			return scalar;
		}
		bool CheckType(int& error, BuildInfor* infor)const;

	};
	class Indexs : public CompilerObj
	{
	public:
		Indexs();
		~Indexs();
		int buildSQ_INDEXUNITS(const lex& eme, GTNode* SQ_INDEXUNITS, BuildInfor* infor, context* dst);
		int buildINDEXLIST(const lex& eme, GTNode* INDEXLIST, BuildInfor* infor, context* dst);
		int buildINDEXUNITS(const lex& eme, GTNode* INDEXUNITS, BuildInfor* infor, context* dst);
		int buildSUMSYMBOL(const lex& eme, GTNode* SUMSYMBOL, BuildInfor* infor, context* dst);
	protected:
		vector<char*> Tindex;
		char* copy(const char* src) const;
		void append(const lex& eme, GTNode* ID2, BuildInfor* infor, context* dst);
	public:
		inline const char* operator[](size_t No) const
		{
			if (No >= Tindex.count()) return NULL;
			return Tindex[No];
		}
		inline size_t GetCount(void) const
		{
			return Tindex.count();
		}
		inline vector<char*> const& GetIndex(void) const
		{
			return Tindex;
		}
		inline vector<char*> const& GetSIndex(void) const
		{
			return Tindex;
		}
	};

	
	class TensorID : public IDinfor
	{
	public:
		TensorID();
		~TensorID();
		int build(const lex& eme, GTNode* TENSORID, BuildInfor* infor, context* dst);
		int BuildSingle(const lex& eme, GTNode* TENSORID, BuildInfor* infor, context* dst);
	protected:
		vector<char*> Tindex;
		char* copy(const char* src) const;
		void append(const char* src);
		void append(const lex& eme, GTNode* ID2, BuildInfor* infor, context* dst);
	public:
		inline const char* operator[](size_t No) const
		{
			if (No >= Tindex.count()) return NULL;
			return Tindex[No];
		}
		inline size_t GetCount(void) const
		{
			return Tindex.count();
		}
		inline vector<char*> const & GetSIndex(void) const
		{
			return Tindex;
		}
	};
	class ValueList
	{
	public:
		ValueList();
		~ValueList();
		
		void append(ConstObj* srcR);
		int checkInt(BuildInfor* infor) const;
		int checkIndex(BuildInfor* infor) const;
		int checkDim(BuildInfor* infor) const;
		int buildSA(const lex& eme, GTNode* VALUELIST, BuildInfor* infor, context* dst);
		int build(const lex& eme, GTNode* VALUELIST, BuildInfor* infor, context* dst);
		void demo(FILE* fp = stdout) const;
		
	protected:
		vector<ConstObj*> values;
		GTNode* backup;
		bool scalar; // 是否为标量
	public:
		inline bool IsScalar(void) const
		{
			return scalar;
		}
		inline size_t GetCount(void) const
		{
			return values.count();
		}
		inline ConstObj::type GetType(void) const
		{
			if (values.count() == 0) return ConstObj::type::_uint_;
			return values[0]->GetType();
		}
		inline ConstObj* GetValue(size_t No) const
		{
			if (No >= values.count()) return NULL;
			return values[No];
		}

		void GetDim(vector<size_t>& dst) const;
	};

	//context is the main class of parser, it contains all the information

	class context
	{
	public:
		friend class BuildInfor;
		friend class IDinfor;
		context();
		~context();
		void ruin(void);
		inline var* RearVar(void)const
		{
			return global[global.count() - 1];
		}
		var* search(const char* name)const;
		var* SearchLocal(const char* name)const;
		ConstObj* searchConst(const char* name)const;
		ConstObj* SearchConstLocal(const char* name)const;
		func* searchFuncs(const char* name) const;
		func* searchFuncsLocal(const char* name) const;
		NetInContext* SearchNet(const char* name)const;
		NetInContext* SearchNetLocal(const char* name)const;
		bool SearchRoutine(const char* name) const;
		bool SearchRoutineLocal(const char* name) const;

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

