#ifndef SymbolicH8u34herh834tyu845trjdfsh834th8345dfgjk2489
#define SymbolicH8u34herh834tyu845trjdfsh834th8345dfgjk2489

namespace Pikachu
{
	typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GLTree;
	typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTIter;
	enum type
	{
		_LeafX_ = 0,
		_LeafConst_ = 1,
		_LeafPara_ = 2,
		_Funct_ = 3,
		_Operation_ = 4,
		_Funct2_ = 5,
		//_Output_ = 5
	};
	enum operation
	{
		_add_ = 0,
		_sub_ = 1,
		_mul_ = 2,
		_div_ = 3,
	};
	enum function
	{
		_sin_, // alpha * sin(beta * x)
		_cos_, // alpha * cos(beta * x)
		_exp_, // alpha * exp(beta * x)	
		_ln_,  // alpha * ln(beta * x)
		_sqrt_, // alpha * sqrt(beta * x)
		//linear, // alpha + (beta * x)
		_minus_
	};
	enum function2
	{
		_pow_, // alpha * pow(beta * x)
	};
	struct FuncConst
	{
		bool IfNan;
		bool IfInt;
		double RealConst;
		long long int IntConst;

		double Rvalue(void) const;
		void nan(void);
		void SetValue(double ele);
		void SetValue(long long int ele);
		void SetValue(const FuncConst& ele);

		bool operator==(long long int ele) const;
		bool operator==(double ele) const;
		bool operator==(const FuncConst& ele) const;
		void operator=(long long int ele);
		void operator=(double ele);
		void operator=(const FuncConst& ele);
		FuncConst operator+(const FuncConst& right);
		FuncConst operator-(const FuncConst& right);
		FuncConst operator*(const FuncConst& right);
		FuncConst operator/(const FuncConst& right);
		bool isZero(void) const;
		bool isOne(void) const;

		void sin(void);
		void cos(void);
		void opposite(void);
		void ln(void);
		void exp(void);
		void sqrt(void);
		void null(void);
		void pow(const FuncConst& exponential);

		void print(PikaString& output)const;
		void print(hyperlex::BufferChar& output)const;
		FuncConst compute(FuncConst& left, FuncConst& right, operation Opera);
		void ComputeSet(FuncConst& left, FuncConst& right, operation Opera);
		FuncConst compute(FuncConst& left, function Func);
		void ComputeSet(FuncConst& left, function Func);
		FuncConst compute(FuncConst& left, FuncConst& right, function2 Func2);
		void ComputeSet(FuncConst& left, FuncConst& right, function2 Func2);
	};
	const char* FunctionName(function Fu);
	const char* Function2Name(function2 Fu2);
	const char* OperationName(operation Op);
	const char* OperationWord(operation Op);
	const char* FunctionWord(function Fu);
	const char* Function2Word(function2 Fu2);
	operation parseOp(const char* opStr);
	function parseFunction(const char* funcStr);
	function2 parseFunction2(const char* funcStr);

	bool isLeaf(enum type T);
	double ComputeOperation(double src1, double src2, operation Op);
	double ComputeFunction(double src1, function Fu);
	double ComputeFunction2(double src1, double src2, function2 Fu2);

	class VISA1
	{
	public:
		// virtual instruction architecture 
		VISA1();
		~VISA1();
		enum ISAT
		{
			_op_ = 0,
			_func_ = 1,
			_st_ = 2,
			_ld_ = 3,
			_func2_ = 4,
		};
		struct instruct
		{
			ISAT Type;
			int Op;
			size_t dst;
			size_t src1;
			size_t src2;
		};
		size_t RegAllocate(vector<size_t>& FreeReg);
		void append(ISAT Type, int Op, size_t dst, size_t src1, size_t src2);
		size_t append(ISAT Type, int Op, vector<size_t>& FreeReg, size_t src1, size_t src2);
		size_t append(vector<size_t>& FreeReg, const FuncConst& Fc);
		size_t append(type Type, vector<size_t>& FreeReg, size_t src1, size_t src2, const FuncConst& Fc, size_t label);
		void Demo(FILE* fp) const;
		void clear(void);
		void compute(double* const* X, const double* para, double* output) const;
	private:
		vector<instruct> program;
		vector<FuncConst> constant;
		//Reg0 is meanless
		size_t RegCount;
	};

	class Activation
	{
	public:
		Activation();
		~Activation();
		void differetial(void);
		void differetial(const Activation& source);
		void copy(const Activation& source);
		bool Simplify(void);
		void Example01(void);
		void Demo(PikaString& out)const;
		void Demo(FILE* fp)const;
		struct ActivationVortex
		{
			type Type;
			operation Op;
			function Fu;
			function2 Fu2;
			FuncConst Fc;
			ActivationVortex* copy(void);
			ActivationVortex() {}
			ActivationVortex(long long int ele);
			ActivationVortex(operation Op);
			ActivationVortex(function func_);
			void Demo(size_t label, PikaString& output) const;
			void Demo(FILE* fp) const;
		};
		void PrintForward(VISA1& instru);
	private:
		graph2<ActivationVortex> formula;
		vector<size_t> Parameter;
		//size_t ParameterCount;
		size_t input;
		size_t output;
		size_t ForwardDifferential(vector<size_t>& label, size_t now, ActivationVortex* here);
		size_t FunctionDifferential(vector<size_t>& label, size_t now, ActivationVortex* here);
		size_t Function2Differential(vector<size_t>& label, size_t now, ActivationVortex* here);
		bool Simplify01(void);
		bool Simplify02(void);
	};

	class expression
	{
	public:
		expression();
		~expression();
		struct node
		{
			type Type;
			int Code;
			bool Output;
			FuncConst Fc;
			size_t src1;
			size_t src2;
			node* copy(void);
			node();
			node(long long int ele);
			node(operation Op);
			node(function func_);
			node(function2 func_);
			node(type T, size_t S1, size_t S2);
			void Demo(size_t label, PikaString& output, bool single) const;
			void Demo(FILE* fp) const;
		};
		void differetial(size_t X1, size_t X2, bool Input);
		void ParameterBackward(size_t No);
		void backward(bool ExternOutput, size_t NewInputDim, size_t No, vector<size_t>& label, vector<size_t>& sequence);
		
		void elementwise(const expression& source, operation OP);
		void InputExpand(size_t NewDim);
		

		void copy(const expression& source);
		bool Simplify(void);
		void Example(size_t No);
		
		void Demo(PikaString& out, bool single, size_t No)const;
		void Demo(FILE* fp)const;
		void PrintForwardMiniOp(VISA1& instru, vector<size_t>& FreeReg)const;
		void PrintForwardMiniReg(VISA1& instru, vector<size_t>& FreeReg)const;

		size_t OutputAmount(void)const;
		size_t ParameterAmount(void)const;
		size_t InputGroup(void)const;
	protected:
		graph2<node> formula;
		vector<size_t> output;
		vector<size_t> InputDim;
		//size_t output;
		//size_t InputGroupCount;
		size_t ParameterCount;
		//vector<FuncConst> constant;
		size_t OperationForwardDifferential(vector<size_t>& label, size_t now, node* here);
		size_t FunctionForwardDifferential(vector<size_t>& label, size_t now, node* here);
		size_t Function2ForwardDifferential(vector<size_t>& label, size_t now, node* here);
		void BackwardAccumulate(vector<size_t>& label, size_t target, size_t source);
		void OperationBackwardDifferential(vector<size_t>& label, size_t now, node* here);
		void FunctionBackwardAccumulate(vector<size_t>& label, size_t target, size_t source, int Code);
		void FunctionBackwardDifferential(vector<size_t>& label, size_t now, node* here);
		void Function2BackwardDifferential(vector<size_t>& label, size_t now, node* here);
		//
		void example01(void);
		void example02(void);
		void example03(void);
		void example04(void);
		void example05(void);
		void example06(void);
		void example07(void);
		void example08(void);
		void example09(void);
		void example10(void);
		//========================Expression simplification
		bool Simplify01(void);
		void LiftLeft(size_t target);
		void LiftRight(size_t target);
		bool Simplify02(void);
		bool Simplify03(void);
		bool Simplify04(void);
		bool Simplify05(void);
		bool Simplify06(void);
		bool Simplify07(void);
		bool Simplify08(void);
		bool Simplify09(void);
		void SimplifyMove(size_t target, size_t NewOne);
		bool Simplify10(void);
		//========================
		//IR print
		void PrintForwardInitial(vector<size_t>& label, vector<size_t>& sequence, buffer<size_t>& queue, vector<size_t>& output_) const;
		void ForwardMiniOpCore(vector<size_t>& label, vector<size_t>& output_, VISA1& instru, vector<size_t>& FreeReg, size_t now, node* here)const;
		//======================== tools
		void ClearOutput(void);
	};

	//class BuildInfor;
	class BuildInfor;
	class Expres
	{
	public:
		typedef hyperlex::BufferChar bufferC;
		struct node : public vortex<node>
		{//CRTP ��Curiously Recurring Template Pattern��
			type Type;
			int Code;
			bool Output;
			FuncConst Fc;
			size_t src1;
			size_t src2;
			node* copy(void) const;
			void copy(const node &source);
			bool operator == (operation Op) const;
			bool operator == (function Op) const;
			bool operator == (long int num) const;
			node();
			node(long int ele);
			node(const FuncConst& ele);
			node(operation Op);
			node(function func_);
			node(function2 func_);
			node(type T, size_t S1, size_t S2);
			~node();
			void Demo(int label, bufferC& output, bool single, bool braket) const;
			void demo(FILE* fp) const;
		};
		typedef node Ele;
		Expres();
		~Expres();
		void clear(void);
		void copy(const Expres& source);
		void copy(const Expres& source, size_t OutNo);
		bool Simplify(void);
		void Example(size_t No);
		int example(const char* source);

		void demo(bufferC& out, bool single, size_t No)const;
		void demo(FILE* fp)const;

		void differetial(size_t X1, size_t X2, bool Input);
		void ParameterBackward(size_t No);
		void backward(bool ExternOutput, size_t NewInputDim, size_t No, vector<Ele*>& label, vector<Ele*>& sequence);
	
		void PrintForwardMiniOp(VISA1& instru, vector<size_t>& FreeReg)const;
		void PrintForwardMiniReg(VISA1& instru, vector<size_t>& FreeReg)const;

		friend class BuildInfor;
	protected:
		graph<node> formula;
		vector<Ele*> output;
		vector<size_t> InputDim;
		size_t ParameterCount;

		//====================================================
		void PrintForwardInitial(vector<Ele*>& sequence, buffer<Ele*>& queue, vector<size_t>& output_)const;
		void ForwardMiniOpCore(vector<size_t>& label, vector<size_t>& output_, VISA1& instru, vector<size_t>& FreeReg, size_t now, Ele* here)const;
		//====================================================
		Ele* NewNode(type T, size_t S1, size_t S2);
		Ele* NewNode(long int ele);
		Ele* NewNode(double ele);
		Ele* NewNode(const FuncConst& ele);
		Ele* NewNode(operation Op);
		Ele* NewNode(Ele* L, Ele* R, operation Op);
		Ele* NewNode(Ele* L, const char* Op, Ele* R);
		Ele* NewNode(function func_);
		Ele* NewNode(Ele* L, function func_);
		Ele* NewNode(const char* fun, Ele* L);
		Ele* NewNode(function2 func_);
		Ele* NewNode(Ele* L, Ele* R, function2 func_);
		Ele* NewNode(const char* fun2, Ele* L, Ele* R);
		Ele* OpForwardDiff(vector<Ele*>& label, Ele* here);
		Ele* FunctForwardDiff(vector<Ele*>& label, Ele* here);
		Ele* Funct2ForwardDiff(vector<Ele*>& label, Ele* here);
		void ClearOutput(void);
		void BackAccumulate(vector<Ele*>& label, size_t target, Ele* source);
		void OperationBackDiff(vector<Ele*>& label, size_t now, Ele* here);
		void FunctBackAccumulate(vector<Ele*>& label, size_t now, Ele* source, int Code);
		void FunctBackDiff(vector<Ele*>& label, size_t now, Ele* here);
		void Funct2BackDiff(vector<Ele*>& label, size_t now, Ele* here);
		//====================================================
		void OutputAppend(Ele* src);
		void OutputShift(Ele* src, Ele* dst);
		void example01(void);
		//========================Expression simplification
		bool Simplify01(void);
		void LiftLeft(Ele* target);
		void LiftRight(Ele* target);
		bool Simplify02(void);
		bool Simplify03(void);
		bool Simplify04(void);
		bool Simplify05(void);
		bool Simplify06(void);
		bool Simplify07(void);
		bool Simplify08(void);
		bool Simplify09(void);
		void SimplifyMove(Ele* target, Ele* NewOne);
		bool Simplify10(void);
		//========================
		int ManifoldBuild(const char * source);
		void ManifoldBuild(GLTree* Tree, hyperlex::Morpheme& eme, int* state);
	public:
		inline size_t OutputAmount(void)const { return output.count(); }
		inline size_t ParameterAmount(void)const { return ParameterCount; }
		inline size_t InputGroup(void)const { return InputDim.count(); }
		inline size_t InputCount(void)const
		{
			size_t count = 0;
			for (size_t i = 0; i < InputDim.count(); ++i)
			{
				count += InputDim[i];
			}
			return count;
		}
		size_t NodeCount(void)const;
		inline void SetParameterCount(size_t Rvalue)
		{
			ParameterCount = Rvalue;
		}
		void ShrinkOutput(size_t victim);
		// remove all the output node expression except the victim
		// without Simplification
	protected:

	};

	class activation : public expression
	{
	public:
		friend class ActiParaBackward;
		friend class ActiHvForward;
		activation();
		~activation();
		void PrintForward(VISA1& instru)const;
		void PrintBackward(VISA1& instru)const;
		void Differetial(void);
		void ParameterBackward(VISA1& instru);
		void Copy(const activation& source);
		bool Simplify(void);
		void Example(size_t No);
		void Demo(PikaString& out)const;
		void Demo(FILE* fp)const;
		void TestBackward(void);
	protected:
		size_t input;
	};
	class ActiParaBackward : public expression
	{
	public:
		ActiParaBackward();
		~ActiParaBackward();
		void Set(const activation& source);
		bool Simplify(void);
		void Demo(FILE* fp)const;
		void Copy(const ActiParaBackward& source);
	protected:
		void Copy(const activation& source);
		size_t input;
	};
	class ActiHvForward : public expression
	{
	public:
		ActiHvForward();
		~ActiHvForward();
		void Set(const activation& source);
		bool Simplify(void);
		void Demo(FILE* fp)const;
		void Copy(const ActiHvForward& source);
	protected:
		void Copy(const activation& source);
		size_t input;
	};
	class HvForwardFinal : public expression
	{
	public:
		HvForwardFinal();
		~HvForwardFinal();	
		void Set(const ActiParaBackward& source);
		bool Simplify(void);
		void Demo(FILE* fp)const;
		void Copy(const HvForwardFinal& source);
	protected:
		void Copy(const ActiParaBackward& source);
		//size_t input;
	};

	class ActivFunc : public Expres
	{	
	public:
		ActivFunc();
		~ActivFunc();
		void PrintForward(VISA1& instru)const;
		void PrintBackward(VISA1& instru)const;
		void Differetial(void);
		void ParameterBackward(VISA1& instru);
		void Copy(const ActivFunc& source);
		bool Simplify(void);
		int construct(const char * text);
		int construct(FILE* fp);
		int build(const char* text);
		void Demo(hyperlex::BufferChar& out)const;
		void Demo(FILE* fp)const;
		void TestBackward(void);
	protected:
		size_t input;

		int build(GLTree*Tree, hyperlex::Morpheme&eme, int*state);
	};




	class manifold : public expression
	{
	public:
		manifold();
		~manifold();
		void OutputAppned(size_t X1, size_t X2, operation OP);
		void Backdiff(size_t dx, size_t y, const manifold* in);
		manifold* MonoForward(size_t y, vector<size_t>& OutputDim) const;
		manifold* DiForward(size_t y, vector<size_t>& OutputDim) const;
		bool Simplify(void);
	protected:

	};
	class manifolds
	{
	public:
		manifolds();
		~manifolds();
		void backward(void);
		void copy(const manifolds& source);
		void forward(size_t Xin);
		void forward(void);
	private:
		vector<size_t> OutputDim;
		size_t InitialOutDim;
		size_t InitialInDim;
		size_t XDim;
		bool mono;
		vector <size_t> InputDim;
		vector<manifold*> storage;
		void ResetStorage(const vector<manifold*>& source, bool copy);
		void ForwardMono(void);
		void ForwardBi(void);
		void StackNext(vector<size_t>& stack, long long int& top, const long long int label, bool& delta)const;
	};
	class cluster
	{
	public:
		cluster();
		~cluster();
		void differential(void);
		void copy(const cluster& source);
		size_t GetOrder(void) const;
		size_t GetDim(size_t No) const;
	private:
		vector<size_t> OutputDim;
		size_t InitialOutDim;
		size_t InitialInDim;
		vector<manifold*> storage;
		void ResetStorage(const vector<manifold*>& source, bool copy);
		void StackNext(vector<size_t>& stack, long long int& top, const long long int label, bool& delta)const;
		bool StackNext(vector<size_t>& stack, const long long int label)const;
	};

	class MonoFunc
	{
	protected:
		bool OutputFusion;
		size_t OutputDim;
		size_t InputDim;
		vector<size_t> dims;
		vector<Expres*> cluster;
		size_t order;
	public:
		MonoFunc();
		~MonoFunc();
		void build(Expres* source);
		void differential(void);
		void clear(void);
		void copy(const MonoFunc& source);
		void demo(FILE* fp = stdout) const;
		inline size_t GetOutputOrder(void) const
		{
			return OutputDim;
		}
		inline size_t GetInputDim(void) const
		{
			return InputDim;
		}
		inline size_t GetFuncDim(size_t No) const
		{
			return dims[No];
		}
		inline Expres* & operator[](size_t No)
		{
			return cluster[No];
		}
		inline Expres* const &  operator[](size_t No) const
		{
			return cluster[No];
		}
		inline bool ScalarInput(void) const
		{
			return (InputDim == 1);
		}
		inline vector<size_t> const& GetDims(void) const
		{
			return dims;
		}
	};
	class DiFunc
	{
	protected:
		bool OutputFusion;
		size_t OutputDim;
		size_t InputDim;
		size_t ParameterDim;
		size_t order;
		vector<size_t> dims;
		vector<Expres*> original;
		vector<bool> diffInfor;
		vector<Expres*> cluster;
	public:
		DiFunc();
		~DiFunc();
		void diffX(void);
		void differential(bool X);
		void copy(const DiFunc& source);
		void clear(void);
		void demo(FILE* fp = stdout) const;
		void build(Expres* source);
		inline size_t GetOutputOrder(void) const
		{
			return OutputDim;
		}
		inline size_t GetInputDim(void) const
		{
			return InputDim;
		}
		inline size_t GetFuncDim(size_t No) const
		{
			return dims[No];
		}
		inline Expres*& operator[](size_t No)
		{
			return cluster[No];
		}
		inline Expres* const& operator[](size_t No) const
		{
			return cluster[No];
		}
	
		inline bool ScalarInput(void) const
		{
			return (InputDim == 1);
		}
		inline bool ScalarPara(void) const
		{
			return (ParameterDim == 1);
		}
		inline vector<size_t> const& GetDims(void) const
		{
			return dims;
		}
	};


	


	


}


#endif
