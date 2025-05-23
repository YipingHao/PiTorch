#ifndef Pikachuhioqewfry89r34qty89gerq5y8ihuqgwerf8u9t3sd
#define Pikachuhioqewfry89r34qty89gerq5y8ihuqgwerf8u9t3sd
#include"PikaType.h"
#define UnderDebugMode 1
#ifdef UnderDebugMode
#include<stdio.h>
#include<iostream>
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
	class network;
	
	class GraphNode;
	class Linear;
	class Nonlinear;
	class Leaf;
	class Elementwise;
	class Transform;

	class GraphNode
	{
	public:
		friend class network;
		//friend class GraphNode;
		friend class Linear;
		friend class Nonlinear;
		friend class Leaf;
		friend class Elementwise;
		friend class Transform;
		enum Affiliation
		{
			unknown = 0,
			initial = 1,
			dYdX = 2,
			dLdW = 3,
			Hdv = 4, 
		};
		enum VortexT
		{
			_leaf_ = 0,
			_tansform_ = 1,
			_elementwise_ = 2,
			_nonlinear_ = 3,
			_linear_ = 4,
			_extra_ = 5,
		};
		enum LeafType
		{
			_leafIn_ = 0,
			_leafPara_ = 1,
			_leafConst_ = 2,
		};
		enum ElementwiseType
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
		GraphNode();
		GraphNode(VortexT type, int op);
		~GraphNode();
		virtual GraphNode* copy(void) const = 0;
		virtual void SetDesc(const tensor & SrcL, const tensor & SrcR) = 0;
		virtual void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace) = 0;
		virtual void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace) = 0;
	protected:
		Affiliation Affi;
		VortexT Type;
		int Op;
		bool IfOutput;
		bool DataExpand;
		tensor descriptor;
		void CopyCore(GraphNode& dst)const;
		//size_t loaction;
		// double* forward, double*backward;
		//double* weight_bias, double* constant,
		//size_t prefix;
	};
	class Leaf : public GraphNode
	{
	public:
		friend class network;
		Leaf();
		Leaf(GraphNode::LeafType t);
		~Leaf();
		GraphNode* copy(void) const;
		void SetDesc(const tensor& SrcL, const tensor& SrcR);
		void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void Initial(const tensor& desc);
	protected:
		vector<FuncConst> value;
		size_t Label;
		void ForwardIn1X(size_t No, vector<size_t>& label, network& workspace);
		void ForwardIn2C(size_t No, vector<size_t>& label, network& workspace);
	};
	class Linear : public GraphNode
	{
	public:
		friend class Nonlinear;
		friend class Leaf;
		friend class Elementwise;
		friend class Transform;
		Linear();
		Linear(GraphNode::LinearType t);
		~Linear();
		GraphNode* copy(void) const;
		void SetDesc(const tensor& SrcL, const tensor& SrcR);
		void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
	protected:
		contract Desc;
		void ContracBack1(bool left, size_t No, vector<size_t>& label, network& workspace) const;
		void ForwardInCon1(size_t No, vector<size_t>& label, network& workspace);
	};
	class Nonlinear : public GraphNode
	{
	public:
		Nonlinear();
		Nonlinear(GraphNode::NonlinearType t);
		~Nonlinear();
		GraphNode* copy(void) const;
		void SetDesc(size_t No, network& workspace);
		void SetDesc(const tensor& SrcL, const tensor& SrcR);
		void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		
	protected:
		cluster cl;
		manifolds man;
		activation ac;
		ActiParaBackward apb;
		ActiHvForward ahf;
		HvForwardFinal hff;
		size_t next;
		size_t SrcDim;
		void BackCore1A(size_t No, vector<size_t>& label, network& workspace);
		void BackCore1AdLdW(size_t No, vector<size_t>& label, network& workspace);
		void BackCore2C(size_t No, vector<size_t>& label, network& workspace);
		void ForwardCore1A(size_t No, vector<size_t>& label, network& workspace);
		
		void ForwardCore1AHdv(size_t No, vector<size_t>& label, network& workspace);
		void ForwardCore2C(size_t No, vector<size_t>& label, network& workspace);
		void ForwardCore3ABack(size_t No, vector<size_t>& label, network& workspace);
		void SetNext(size_t No, network& workspace);
	};	
	class Elementwise : public GraphNode
	{
	public:
		friend class Linear;
		friend class Nonlinear;
		friend class Leaf;
		friend class Transform;
		friend class network;
		Elementwise();
		Elementwise(GraphNode::ElementwiseType t);
		~Elementwise();
		GraphNode* copy(void) const;
		void SetDesc(const tensor& SrcL, const tensor& SrcR);
		void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		
	protected:
		elementwise descE;
		void BackCore1(bool left, double alpha, size_t No, vector<size_t>& label, network& workspace)const;
		void BackCore2(bool left, size_t No, vector<size_t>& label, network& workspace)const;

		void ForwardCore1(size_t No, vector<size_t>& label, network& workspace)const;
		void ForwardCore2(size_t No, vector<size_t>& label, network& workspace)const;
	};
	class Transform : public GraphNode
	{
	public:
		//friend class GraphNode;
		friend class Linear;
		friend class Nonlinear;
		friend class Leaf;
		friend class Elementwise;
		Transform();
		Transform(GraphNode::TransformType t);
		~Transform();
		GraphNode* copy(void) const;
		void SetDesc(const tensor& SrcL, const tensor& SrcR);
		void backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace);
		void SetAlpha(long long int);
	protected:
		double alpha;
		dispatch DisDesc1;
		condensation CondenDesc2;

	};
	
	

	class network
	{
	public:
		friend class GraphNode;
		friend class Linear;
		friend class Nonlinear;
		friend class Leaf;
		friend class Elementwise;
		friend class Transform;
		network();
		~network();
		void backward(void);
		void forward(void);
		void copy(network& source);
		void backward(size_t No);
		void forward(size_t No);

		bool Simplify(void);
		bool SimplifyFinal(void);
	private:
		graph2<GraphNode> net;
		vector<size_t> parameter;

		vector<size_t> output;
		vector<elaboration*> OutInfor;

		vector<size_t> dLossdO;
		vector<size_t> LossDifferential;

		vector<size_t> VectorIn;
		vector<size_t> HessianVector;

		bool Initialized;
		bool LossCompute;
		bool Hessian;
		bool FinalSimplified;

		void backwardCheck(size_t No);

		void SetUnknown(GraphNode::Affiliation value);
		void SetOutput(size_t old, size_t theNewOutput, size_t dX);

		size_t append(GraphNode::VortexT type, int op);
		GraphNode* NewNode(GraphNode::VortexT type, int op);
		void BackwardAppend(size_t target, size_t source, vector<size_t>& label);
		void DifferentialOutAppend(size_t target, size_t source, vector<size_t>& label);
		void SetDesc(size_t target);

		bool Simplify01RedundancyCut(void);
		bool Simplify02ClusterFusion(void);
	};

	
	
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
		~Node();
		enum Affiliation
		{
			unknown = 0,
			initial = 1,
			dYdX = 2,
			dLdW = 3,
			Hdv = 4,
		};
		enum VortexType
		{
			_leaf_ = 0,
			_tansform_ = 1,
			_elementwise_ = 2,
			_nonlinear_ = 3,
			_linear_ = 4,
			_extra_ = 5,
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
		virtual void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H) = 0;
		virtual void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H) = 0;
		virtual void compute(tensor& DescOut)const = 0;
		virtual void check(void)const = 0;
		virtual void clear(void) = 0;
	protected:
		Affiliation Affi;
		VortexType Type;
		int Op;
		bool IfOutput;
		bool DataExpand;
		tensor descriptor;
		NetWork* network;

		void CopyCoreN(Node& dst) const;
		void setDesc(const tensor& desc);
		void setDesc(const tensor& desc, const vector<size_t>& H);
		void clearCore(void);
	};
	class LeafNode : public Node
	{
	protected:
		vector<FuncConst> value;
		size_t Label;
	public:
		LeafNode();
		LeafNode(NetWork* context, Node::LeafType t);
		~LeafNode();
		Node* copy(void) const;
		void compute(tensor& DescOut)const;
		void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void Initial(const tensor& desc, vector<size_t>& H);
		void check(void)const;
		void clear(void);
	};
	class MonoLinear : public Node
	{
	public:
		MonoLinear();
		~MonoLinear();
		Node* copy(void) const;
		void compute(tensor& DescOut)const;
		void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void build(const vector<sint>& Src, const vector<sint>& Dst, double Alpha);
		void build(const vector<sint>& Src, const vector<sint>& Dst, const vector<size_t>& H, double Alpha);
		friend class DiLinear;
	protected:
		double alpha;
		vector<sint> indexDst;
		vector<sint> indexSrc;
		size_t DummyIndex;
		size_t NewIndex;
		size_t RepeatedIndex;

		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	};
	class DiLinear : public Node
	{
	public:
		friend class NetWork;
		friend class LeafNode;
		friend class DiLinear;
		friend class DiNonlinear;
		friend class MonoLinear;
		friend class MonoNonlinear;
		DiLinear();
		~DiLinear();
		Node* copy(void) const; 
		void compute(tensor& DescOut)const;
		void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
		void trivial(Node* SrcL, Node* SrcR);
		void value(const vector<sint>& SrcL, const vector<sint>& SrcR, const vector<sint>& Dst);
		void build(void);
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
	};
	class MonoNonlinear : public Node
	{
	public:
		MonoNonlinear();
		~MonoNonlinear();
		Node* copy(void) const;
		void compute(tensor& DescOut)const;
		void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
	protected:
		tensor funcTensor;
		bool ScalarInput;
		sint x;
		vector<sint> function;

		vector<sint> indexDst;
		vector<sint> indexSrc;


		void* formula;

		size_t next;
		size_t SrcDim;
		
		sint MaxIndex(void) const;
		MonoNonlinear* differential(void) const;
		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary * ErrorGive(void) const;
	};
	class DiNonlinear : public Node
	{
	public:
		DiNonlinear();
		~DiNonlinear();
		Node* copy(void) const;
		void compute(tensor& DescOut)const;
		void forward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void backward(bool dYdX, vector<Node*>& label, vector<size_t>& H);
		void check(void)const;
		void clear(void);
	protected:
		tensor funcTensor;

		bool ScalarInput;
		sint x;
		bool ScalarPara;
		sint omega;
		vector<sint> function;

		vector<sint> indexDst;
		vector<sint> indexSrc;
		vector<sint> indexPara;

		sint MaxIndex(void) const;
		DiNonlinear* differential(bool X) const;
		void inforPrint(hyperlex::dictionary& dict)const;
		hyperlex::dictionary* ErrorGive(void) const;
	};
	
	

	
	
	

	class NetWork
	{
	public:
		NetWork();
		~NetWork();
		void copy(NetWork& source);
		void forward(size_t No);
		void backward(size_t No);
		void NodeAppend(Node* rear);
		friend class NetWork;
		friend class LeafNode;
		friend class DiLinear;
		friend class DiNonlinear;
		friend class MonoLinear;
		friend class MonoNonlinear;
	protected:
		graph<Node> net;

		vector<Node*> input;
		vector<Node*> output;
		vector<tensor*> descriptor;


		vector<Node*> parameter;


		vector<Node*> hahahah;
		void BackAcc(size_t target, vector<Node*>& label, Node* source);
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