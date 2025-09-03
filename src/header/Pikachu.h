#ifndef Pikachuhioqewfry89r34qty89gerq5y8ihuqgwerf8u9t3sd
#define Pikachuhioqewfry89r34qty89gerq5y8ihuqgwerf8u9t3sd
#include"PikaType.h"
#define UnderDebugMode 1
#ifdef UnderDebugMode
#include<stdio.h>
#include<iostream>
#include <map>
#include <vector>
#include <string>
//#define Debug01 /
#define Debug02 //
//#define Debug03 //
#ifdef Debug03
//20241011
//#define Debug03_01
//#define Debug03_02
//#define Debug03_03//20241016
//#define Debug03_04 //20241017
//#define Debug03_05 //20241021
#define Debug03_06 //20241028
#endif
#endif // UnderDebugMode
#include"Symbolic.h"
namespace Pikachu
{
	typedef vector<size_t> dims_t;
	typedef vector<sint> indice_t;
	/**
 * @brief 索引字符串与整数转换类
 *
 * 该类用于处理字符串与整数张量索引之间的双向转换，支持批量操作和演示功能。
 * 字符串存储在动态分配的内存中，索引使用sint类型（长整型）表示。
 *
 * 普通的字符串索引转为正数整数索引，NULL指针转换成-1
 * @class indiceIS
 * @brief Index String-Integer Conversion Class
 *
 * This class handles bidirectional conversion between strings and integer indices,
 * supporting batch operations and demonstration functionality.
 * Strings are stored in dynamically allocated memory, and indices are represented using
 * the sint type (long integer).
 */
	class indiceIS
	{
	public:
		indiceIS();// 构造函数：初始化对象 | Constructor: Initialize the object
		~indiceIS();// 析构函数：清理资源 | Destructor: Clean up resources
		void StoI(void);          // 将字符串转换为索引 | Convert strings to indices
		void ItoS(void);          // 将索引转换为字符串 | Convert indices to strings
		void demo(FILE* fp = stdout) const;  // 演示当前存储的索引和字符串 | Demonstrate stored indices and strings
		//typedef long long int sint;
	protected:
		vector<vector<char*>*> indiceS;  // 存储字符串的二维向量 | 2D vector storing strings
		vector<vector<sint>*> indicsI;   // 存储索引的二维向量 | 2D vector storing indices

		void clearS(void);  // 清理字符串数据 | Clear string data
		void clearI(void);  // 清理索引数据 | Clear index data
	public:
		/** 获取存储的字符串组数量 | Get the number of stored string groups */
		inline size_t Scount(void) const { return indiceS.count(); }
		/** 获取存储的索引组数量 | Get the number of stored index groups */
		inline size_t Icount(void) const { return indicsI.count(); }
		/** 获取指定索引处的字符串组引用 | Get reference to the string group at specified index */
		inline vector<char*> const& S(size_t index)const { return *indiceS[index]; }
		/** 获取指定索引处的索引组引用 | Get reference to the index group at specified index */
		inline vector<sint> const& I(size_t index)const { return *indicsI[index]; }
		// 添加字符串组 | Add a group of strings
		void appendS(const vector<char*>& S);
		// 添加索引组 | Add a group of indices */
		void appendI(const vector<sint>& I);
		/** 将数字索引转换为字符串表示 | Convert numerical index to string representation */
		static char* IndexToString(size_t index);

		inline static sint InvalidLabal(void)
		{
			return -1;
		}
	};

	class network;
	

	
	



	
	
	class NetWork;
	class LeafNode;
	class DiLinear;
	class DiNonlinear;
	class MonoLinear;
	class MonoNonlinear;
	class Node : public vortex<Node>
	{
	public:
		friend class NetWork;
		friend class LeafNode;
		friend class DiLinear;
		friend class DiNonlinear;
		friend class MonoLinear;
		friend class MonoNonlinear;
		

		Node();
		virtual ~Node();
		enum Affiliation
		{
			unknown = 0,
			initial = 1,
			dYdX = 2,
			dLdW = 3,
			Jacobi_ = 4,
			Hdv = 5,
		};
		enum VortexType
		{
			_leaf_ = 0,
			_MonoLinear_ = 1,
			_DiLinear_ = 2,
			_MonoNonlinear_ = 3,
			_DiNonlinear_ = 4,
		};
		enum LeafType
		{
			_leafIn_ = 0,
			_leafPara_ = 1,
			_leafConst_ = 2,
		};
		enum OpType
		{
			_add_ = 0,
			_sub_ = 1,
			_mul_ = 2,
		};
		enum TransformType
		{
			_identity_ = 0,
			_condense_ = 1,
			_dispatch_ = 2,
		};
		enum LinearType
		{
			_contraction_ = 0,

		};
		enum NonlinearType
		{
			_activation_ = 0,
			_manifold_ = 1,
			_cluster_ = 2,
			_activationBack_ = 3,
			_activationHv_ = 4,
			_HvFinal_ = 5,
		};
		virtual Node* copy(void)const  = 0;
		//virtual void copy(Node& source) = 0;
		virtual void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) = 0;
		virtual void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) = 0;
		virtual void compute(Tensor& DescOut)const = 0;
		virtual void check(void)const = 0;
		virtual void clear(void) = 0;
		virtual void PrintScreen(FILE* fp = stdout)const = 0;
		virtual bool IsConst(const FuncConst & value) const = 0;
		void demo(FILE* fp = stdout) const;
		virtual void demo(size_t tabs, FILE* fp) const = 0;
		virtual bool IsZero(void) const = 0;
		void setDesc(const Tensor& desc);
		void setDesc(const vector<size_t>& desc);
		static LeafType ParseLeafType(const char* input);
		static OpType ParseOpType(const char* input);
		void PrintConcise(FILE* fp = stdout) const;
	protected:
		Affiliation Affi;
		VortexType Type;
		int Op;
		bool IfOutput;
		bool DataExpand;
		Tensor descriptor;
		NetWork* network;
		
		char* name;
		size_t NameLabel;

		void CopyCoreN(Node& dst) const;
		
		void setDesc(const Tensor& desc, const vector<size_t>& H);
		void clearCore(void);
		void PrintScreenCore(FILE* fp)const;
		void Demo(size_t tabs, FILE* fp) const;
	public:
		bool eqaul(const char* opR) const;
		bool equal(const Node* opR) const;
		bool equal(const Node& opR) const;
		void SetName(const char* NewName);
		void SetLabel(size_t NewLabel);
		bool CompareName(const char* NewName) const;
		inline const char* GetName(void) const { return name; }
		inline size_t GetLabel(void) const { return NameLabel; }
		inline size_t GetOrder(void) const { return descriptor.GetOrder(); }
		inline size_t GetDim(size_t No) const { return descriptor[No]; }
		inline const Tensor& GetDesc(void) const { return descriptor; }
		inline size_t GetElementCount(void) const { return descriptor.GetCount(); }
	};
	class LeafNode : public Node
	{
	protected:
		vector<FuncConst> value;
		size_t Label;
	public:
		LeafNode();
		LeafNode(NetWork* context, Node::LeafType t, Affiliation AA);
		~LeafNode();
		Node* copy(void) const;
		void compute(Tensor& DescOut)const;
		void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void Initial(const Tensor& desc, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void PrintScreen(FILE* fp = stdout)const;
		bool IsConst(const FuncConst& value) const;
		void demo(size_t tabs, FILE* fp = stdout) const;
		bool IsZero(void) const;
		void zero(void);
	};
	class MonoLinear : public Node
	{
	public:
		MonoLinear();
		MonoLinear(Affiliation AA);
		~MonoLinear();
		Node* copy(void) const;
		void compute(Tensor& DescOut)const;
		void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		int build(Node* src, const vector<sint>& Src, const vector<sint>& dummy, const vector<sint>& Dst, double Alpha);
		void build(const vector<sint>& Src, const vector<sint>& Dst, double Alpha);
		void build(const vector<sint>& Src, const vector<sint>& Dst, const vector<size_t>& H, double Alpha);
		friend class DiLinear;
		void PrintScreen(FILE* fp = stdout)const;
		bool IsConst(const FuncConst& value) const;
		bool IsZero(void) const;
		void demo(size_t tabs, FILE* fp = stdout) const;
	protected:
		double alpha;
		vector<sint> indexDst;
		vector<sint> indexSrc;
		size_t DummyIndex;
		size_t NewIndex;
		size_t RepeatedIndex;

		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	public:
		friend class NetWork;
	};
	class DiLinear : public Node
	{
	public:
		friend class NetWork;
		friend class LeafNode;
		friend class DiNonlinear;
		friend class MonoLinear;
		friend class MonoNonlinear;
		DiLinear();
		DiLinear(Node::OpType OT, Affiliation AA);
		~DiLinear();
		Node* copy(void) const; 
		void compute(Tensor& DescOut)const;
		void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void trivial(Node* SrcL, Node* SrcR, Affiliation AA);
		void value(const vector<sint>& SrcL, const vector<sint>& SrcR, const vector<sint>& Dst);
		void PrintScreen(FILE* fp = stdout)const;
		bool IsConst(const FuncConst& value) const;
		bool IsZero(void) const;
		void demo(size_t tabs, FILE* fp = stdout) const;
	protected:
		//elementwise descE;
		vector<sint> indexDst;
		vector<sint> indexSrcL;
		vector<sint> indexSrcR;
		size_t DummyIndex;
		size_t RepeatedIndex;
		sint MaxIndex(void) const;
		void Happend(bool L, bool R, bool D, size_t H);
		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	public:
		void build(const indice_t& dummy);
		void build(void);
	};
	class MonoNonlinear : public Node
	{
	protected:
		Tensor funcTensor;
		bool ScalarInput;
		sint x;
		vector<sint> function;

		vector<sint> indexDst;
		vector<sint> indexSrc;

		MonoFunc formula;



		MonoNonlinear* gradient;

		sint MaxIndex(void) const;
		MonoNonlinear* differential(Affiliation AA);
		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	public:
		enum ErrorInfor
		{
			NoError = 0,
			//indexSrc内部的重复
			IndexRedundancy,
			//indexDst内部的重复
			IndexDstRedundancy,
			//function内部的重复
			FunctionRedundancy,
			//X的值不在indexSrc中
			XNotInIndexSrc,
			//X的值在indexDst中
			XInIndexDst,
			//indexDst中的指标不在indexSrc 或 function 中
			IndexDstNotInIndexSrcOrFunction,
			// 检查 indexSrc中的指标，如果不是x，那么必须在indexDst中
			IndexSrcOrFunctionNotInIndexDst,
			//检查 function中的指标，不能是x，必须在indexDst中
			FunctionContainsX
		};
		MonoNonlinear();
		MonoNonlinear(Affiliation AA);
		~MonoNonlinear();
		Node* copy(void) const;
		void compute(Tensor& DescOut)const;
		void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void PrintScreen(FILE* fp = stdout)const;
		bool IsConst(const FuncConst& value) const;
		bool IsZero(void) const;
		void demo(size_t tabs, FILE* fp = stdout) const;

		int build(const dims_t& dims, Node* srcL, Expres* func, indiceIS& indice);
		ErrorInfor CheckIndice(void) const;
	
	};
	class DiNonlinear : public Node
	{
	public:
		DiNonlinear();
		DiNonlinear(Affiliation AA);
		~DiNonlinear();
		Node* copy(void) const;
		void compute(Tensor& DescOut)const;
		void forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void PrintScreen(FILE* fp = stdout)const;
		bool IsConst(const FuncConst& value) const;
		bool IsZero(void) const;
		void demo(size_t tabs, FILE* fp = stdout) const;
	protected:
		Tensor funcTensor;

		bool ScalarInput;
		sint x;
		bool ScalarPara;
		sint omega;
		vector<sint> function;

		vector<sint> indexDst;
		vector<sint> indexSrc;
		vector<sint> indexPara;

		DiFunc formula;

		DiNonlinear* gradientX;
		DiNonlinear* gradientP;

		sint MaxIndex(void) const;
		DiNonlinear* differential(bool X, Affiliation AA);
		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	public:
		enum ErrorInfor
		{
			NoError = 0,
			
			IndexRedundancy,//indexSrc内部的重复
			IndexDstRedundancy,//indexDst内部的重复
			FunctionRedundancy,//function内部的重复
			IndexParaRedundancy,//indexPara内部的重复
			XNotInIndexSrc,//X的值不在indexSrc中
			XInIndexDst,//X的值在indexDst中
			OmegaNotInIndexPara,//
			OmegaInIndexDst,//
			//indexDst中的指标不在indexSrc 或 function 中
			IndexDstNotInIndexSrcOrFunction,
			// 检查 indexSrc或function中的指标，如果不是x，那么必须在indexDst中
			IndexSrcOrFunctionNotInIndexDst,
			XEqualOmega,//
			FunctionContainsXOrOmega,// 
		};
		int build(const dims_t& dims, Node* srcL, Node* srcR, Expres* func, indiceIS& indice);
		ErrorInfor CheckIndice(void) const;
	};
	
	

	
	
	
	
	class BackEnd;
	class NetWork
	{
	public:
		
		NetWork();
		~NetWork();
		void copy(NetWork& source);
		void forward(size_t No, const vector<size_t> & UpNo, const char*OutputName);
		void backward(size_t No, const vector<size_t>& DownNo, const char* OutputName);
		void demo(FILE* fp = stdout);
		void demo(size_t tabs, FILE* fp, const vector<Node*> & listT, const char * Tinfor);
		void demo(size_t tabs, FILE* fp);

		void gradient(void);
		void jacobi(void);
		void Hv(void);
		
		void NodeAppend(Node* rear);
		friend class LeafNode;
		friend class DiLinear;
		friend class DiNonlinear;
		friend class MonoLinear;
		friend class MonoNonlinear;

		friend class BackEnd;
		Node* NewNodeLeaf(const dims_t& dims, Node::LeafType T);
		Node* NewNodeMonoLinear(const dims_t&dims, Node* src, double factor_, indiceIS & indice);
		Node* NewNodeDiLinear(const dims_t& dims, Node* srcL, Node* srcR, Node::OpType OT, indiceIS& indice);
		Node* NewNodeMonoNonlinear(const dims_t& dims, Node* srcL, Expres * func, indiceIS& indice);
		Node* NewNodeDiNonlinear(const dims_t& dims, Node* srcL, Node* srcR, Expres* func, indiceIS& indice);


		inline size_t InputNodeCount(void) const { return input.count(); }
		inline size_t ParameterNodeCount(void) const { return parameter.count(); }
		inline size_t OutputNodeCount(void) const { return output.count(); }
		size_t InputCount(void) const;
		size_t ParameterCount(void) const;
		size_t OutputCount(void) const;
	protected:
		friend class BuildInfor;
		graph<Node> net;

		vector<Node*> input;
		vector<Node*> parameter;
		vector<Node*> output;
		vector<Tensor*> OutDesc;
		//gradient
		vector<Node*> BackSrc;
		vector<Node*> BackOut;
		//Hv
		vector<Node*> HvSrc;
		vector<Node*> HvOut;
		//jacobi
		vector<Node*> JacobiSrc;
		vector<Node*> JacobiOut;

		void AppendOutput(Node* out);

		void replace(Node* target, Node* source);
		void OutputShift(Node* target, Node* source);
		bool simplify(void);
		bool simplify01RedundancyCut(void);
		bool simplify02Zerotensor(void);

		void copyInfor(vector<Node*>& Dst, const vector<Node*>& Src);

		void BackAcc(Node::Affiliation AA, size_t target, vector<Node*>& label, Node* source);


		bool checkName(const char* name);//检查所有的输出与叶子节点名称是否与给定名称相同
		Node* CheckNameOutput(const char* name, size_t Label);
		//检查所有的输出节点名称与标签是否与给定名称与标签相同，如果相同返回对应节点
		//否则返回NULL
		Node* CheckNameInput(const char* name, size_t Label);
		//检查所有的叶子Input类型节点名称与标签是否与给定名称与标签相同，如果相同返回对应节点
		//否则返回NULL

		void OutputNameSearch(const vector<const char*>& name, const vector<size_t>& index, vector<size_t> & No) const;
		void InputNameSearch(const vector<const char*>& name, const vector<size_t>& index, vector<size_t>& No) const;
	};

	
	

	class BackEnd
	{
	public:
		BackEnd();
		~BackEnd();
		int build(const char* machine, NetWork* net, const char* output);
	private:
		int CPUbackEnd(NetWork* net, FILE*fp);
		int CUDAbackEnd(NetWork* net, FILE* fp);
	};

	
}


#include"parser.h"



#endif




/*

class Function
	{
	public:
		Function();
		~Function();
		enum operation
		{
			add,
			sub,
			mul,
			div
		};
		enum function
		{
			sin, // alpha * sin(beta * x)
			cos, // alpha * cos(beta * x)
			pow, // alpha * pow(beta * x)
			exp, // alpha * exp(beta * x)
			ln,  // alpha * ln(beta * x)
			sqrt, // alpha * sqrt(beta * x)
			//linear, // alpha + (beta * x)
			minus
		};
		enum type
		{
			LeafX,
			LeafConst,
			LeafPara,
			Funct,
			Operation,
			Output
		};
		enum ErrorCode
		{
			NoError,
			DivideZero,
			LogInputError,
			SqrtInputError
		};

		union content
		{
			operation Op;
			size_t No;
			FuncConst Const;
			function Func;
		};
		struct DiffStack
		{
			long long int* stack;
			bool* label;
			size_t* infro;
			size_t top;
			DiffStack(size_t length)
			{
				size_t i;
				top = 0;
				stack = (long long int*)malloc(sizeof(long long int) * length);
				label = (bool*)malloc(sizeof(bool) * length);
				infro = (size_t*)malloc(sizeof(size_t) * length);
				for (i = 0; i < length; i++) label[i] = false;
			}
			~DiffStack(void)
			{
				free((void*)stack);
				free((void*)label);
				free((void*)infro);
			}
			void Add(long long int site)
			{
				stack[top] = site;
				top += 1;
			}
			long long int Pop()
			{
				long long int out;
				out = stack[top];
				top -= 1;
				return out;
			}
		};

		struct formula
		{
		public:
			size_t ContainerSize;
			size_t Size;
			long long int output;

			content* Co;
			type* Type;
			ErrorCode Error;
			//operation* Op;
			//size_t* Site;
			long long int* LChild;
			long long int* RChild;

			//UnitList* Unit;

			formula();
			formula(const formula* F);
			~formula();
			void initial(void);
			void refresh(void);
			void ruin(void);

			void shrink_formula(void);
			void simplify_formula(void);
			formula* differential(size_t i);
			void zero(void);
		private:

			size_t Add(long long int ele);
			size_t Add(double ele);
			size_t Add(long long int LL, long long int RR, operation Opera);
			size_t Add(long long int LL, long long int RR, function Func);
			void Add(void);

			bool AddZeroCheck(long long int* stack);
			bool MultipleOneCheck(long long int* stack);
			bool MultipleZeroCheck(long long int* stack);
			bool ConstComputeCheck(long long int* stack);


			bool CheckOperation(long long int Target, operation should);
			// 0 Left child is zero / one
			// 1 Left child is zero / one
			// 2 Right child is zero / one
			// 3 All child is zero / one
			int IfAChildZero(long long int Target);
			int IfAChildOne(long long int Target);
			bool IfASiteZero(long long int Target);
			bool IfASiteOne(long long int Target);

			bool IfAllChildConst(long long int Target);
			bool IfAllInputConst(long long int Target);
			void ChangeToConst(long long int Target, FuncConst& ConstSite);

			bool checkDependence(void);
			void differential(size_t i, formula* output, DiffStack* stack, long long int Target);
			size_t DiffOp(formula* output, DiffStack* stack, long long int Target);
			size_t DiffFunc(formula* output, DiffStack* stack, long long int Target);

		};

	private:
		size_t InputCount;
		size_t FormulaCount;
		//formula** Formula;
		unsigned int* Order;

		//UnitList* Unit;

		void initialize(void);

	};

*/