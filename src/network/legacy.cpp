#include"../header/Pikachu.h"
#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

namespace Pikachu
{
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
		virtual void SetDesc(const tensor& SrcL, const tensor& SrcR) = 0;
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
}
using namespace Pikachu;



GraphNode::GraphNode()
{
	IfOutput = false;
	DataExpand = true;
	Affi = unknown;
}
GraphNode::GraphNode(VortexT type, int op)
{
	IfOutput = false;
	Type = type;
	Op = op;
}
GraphNode::~GraphNode()
{

}
void GraphNode::CopyCore(GraphNode& dst)const
{
	dst.Type = Type;
	dst.Op = Op;
	dst.IfOutput = IfOutput;
	dst.descriptor.Set(descriptor);
	return;
}

Leaf::Leaf()
{
	Type = _leaf_;
}
Leaf::Leaf(GraphNode::LeafType t)
{
	Type = _leaf_;
	Op = (int)t;
}
Leaf::~Leaf()
{
}
GraphNode* Leaf::copy(void) const
{
	Leaf* node;
	node = new Leaf();
	CopyCore(*node);
	//node->Desc.Set(Desc);
	return node;
}
void Leaf::SetDesc(const tensor& SrcL, const tensor& SrcR)
{
	descriptor.Set(SrcL);
}
void Leaf::backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	return;
}
void Leaf::Initial(const tensor& desc)
{
	size_t i, L;
	FuncConst one_;
	//zero_.SetValue((long long)0);
	one_.SetValue((long long)1);
	Op = (int)_leafConst_;
	DataExpand = false;
	if (desc.GetOrder() == 0)
	{
		descriptor.ChangeOrder(1);
		descriptor.ChangeDim(0, 1);
		value.append(one_);
	}
	else if (desc.GetOrder() == 1 && desc[0] == 1)
	{
		descriptor.Set(desc);
		value.append(one_);
	}
	else
	{
		descriptor.Clear();
		for (i = 0; i < desc.GetOrder(); i++) descriptor.AppendDim(desc[i]);
		for (i = 0; i < desc.GetOrder(); i++) descriptor.AppendDim(desc[i]);
		L = desc.GetCount();
		value.recount(descriptor.GetCount());
		for (i = 0; i < value.count(); i++)
			value[i].SetValue((long long)0);
		for (i = 0; i < L; i++)
			value[i * L + i].SetValue((long long)1);
	}
	return;
}
void Leaf::forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	LeafType LT;
	LT = (LeafType)Op;
	switch (LT)
	{
	case Pikachu::GraphNode::_leafIn_:
		ForwardIn1X(No, label, workspace);
		break;
	case Pikachu::GraphNode::_leafPara_:
	case Pikachu::GraphNode::_leafConst_:
		ForwardIn2C(No, label, workspace);
		break;
	default:
		throw PikaError("Leaf::forward", "switch (LT)", Op);
		break;
	}
}
void Leaf::ForwardIn1X(size_t No, vector<size_t>& label, network& workspace)
{

}
void Leaf::ForwardIn2C(size_t No, vector<size_t>& label, network& workspace)
{

}

Linear::Linear()
{
	Type = _linear_;
}
Linear::Linear(GraphNode::LinearType t)
{
	Type = _linear_;
	Op = (int)t;
}
Linear::~Linear()
{
}
GraphNode* Linear::copy(void) const
{
	Linear* node;
	node = new Linear();
	CopyCore(*node);
	node->Desc.Set(Desc);
	return node;
}
void Linear::SetDesc(const tensor& SrcL, const tensor& SrcR)
{
	LinearType LT;
	LT = (LinearType)Op;
	switch (LT)
	{
	case Pikachu::GraphNode::_contraction_:
		descriptor.contraction(SrcL, SrcR, Desc);
		break;
	default:
		throw PikaError("Linear::SetDesc", "switch (LT)", Op);
		break;
	}
	return;
}
void Linear::backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	LinearType LT;
	LT = (LinearType)Op;
	switch (LT)
	{
	case Pikachu::GraphNode::_contraction_:
		ContracBack1(true, No, label, workspace);
		ContracBack1(false, No, label, workspace);
		break;
	default:
		throw PikaError("Linear::BackwardAppend", "switch (LT)", Op);
		break;
	}
	return;
}
void Linear::ContracBack1(bool left, size_t No, vector<size_t>& label, network& workspace) const
{
	Linear* New;
	GraphNode* Src;
	size_t site;
	size_t original;
	size_t dst, peer;

	dst = workspace.net[No].In[(left ? 0 : 1)];
	peer = workspace.net[No].In[(left ? 1 : 0)];
	original = label[No];
	Src = workspace.net[original].content;

	site = workspace.append(_linear_, _contraction_);
	New = (Linear*)(workspace.net[site].content);

	New->Desc.backward(Src->descriptor, Desc, !left);
	if (left) workspace.net.append(original, peer, site);
	else workspace.net.append(peer, original, site);

	workspace.SetDesc(site);
	workspace.BackwardAppend(dst, site, label);
}
void Linear::forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	LinearType LT;
	LT = (LinearType)Op;
	switch (LT)
	{
	case Pikachu::GraphNode::_contraction_:
		ForwardInCon1(No, label, workspace);
		break;
	default:
		throw PikaError("Linear::BackwardAppend", "switch (LT)", Op);
		break;
	}
	return;
}
void Linear::ForwardInCon1(size_t No, vector<size_t>& label, network& workspace)
{
	size_t left, right, site;
	Linear* New;
	GraphNode* Left, * Right;
	left = workspace.net[No].In[0];
	right = workspace.net[No].In[1];
	if (label[left] != _uintMax_)
	{
		Left = workspace.net[label[left]].content;
		site = workspace.append(_linear_, Pikachu::GraphNode::_contraction_);
		New = (Linear*)(workspace.net[site].content);
		New->Desc.forward(Left->descriptor, Desc, true);
		workspace.net.append(label[left], right, site);
		workspace.SetDesc(site);
		workspace.DifferentialOutAppend(No, site, label);
	}
	//else if (label[right] == _uintMax_)
		//throw PikaError("Elementwise::ForwardCore2", "label[left] == _uintMax_ && label[right] == _uintMax_", Op);
	if (label[right] != _uintMax_)
	{
		Right = workspace.net[label[right]].content;
		site = workspace.append(_linear_, Pikachu::GraphNode::_contraction_);
		New = (Linear*)(workspace.net[site].content);
		New->Desc.forward(Right->descriptor, Desc, false);
		workspace.net.append(left, label[right], site);
		workspace.SetDesc(site);
		workspace.DifferentialOutAppend(No, site, label);
	}
}

Nonlinear::Nonlinear()
{
	Type = _nonlinear_;
	next = _uintMax_;
	SrcDim = 0;
}
Nonlinear::Nonlinear(GraphNode::NonlinearType t)
{
	Type = _nonlinear_;
	Op = (int)t;
	next = _uintMax_;
}
Nonlinear::~Nonlinear()
{
}
GraphNode* Nonlinear::copy(void) const
{
	Nonlinear* node;
	node = new Nonlinear();
	CopyCore(*node);
	node->cl.copy(cl);
	node->ac.Copy(ac);
	node->man.copy(man);
	return node;
}
void Nonlinear::SetDesc(const tensor& SrcL, const tensor& SrcR)
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
	size_t i;
	switch (NT)
	{
	case Pikachu::GraphNode::_activation_:
		//descriptor.Set(SrcL);
		//break;
	case Pikachu::GraphNode::_manifold_:
		//throw PikaError("Nonlinear::SetDesc", "case Pikachu::GraphNode::_manifold_", Op);
		//break;
	case Pikachu::GraphNode::_cluster_:
		//BackCore2(No, label, workspace);
		//descriptor.Clear();
		//for (i = 0; i < SrcDim; i++)
		//	descriptor.AppendDim(SrcL[i]);
		//for (i = 0; i < cl.GetOrder(); i++)
		//	descriptor.AppendDim(cl.GetDim(i));
		//for (i = SrcDim + 1; i < SrcL.GetOrder(); i++)
		//	descriptor.AppendDim(SrcL[i]);
		//break;
	case Pikachu::GraphNode::_activationBack_:
		///descriptor.Set(SrcL);
		//break;
	case Pikachu::GraphNode::_activationHv_:
		//descriptor.Set(SrcL);
		//break;
	default:
		throw PikaError("Nonlinear::SetDesc", "switch (LT)", Op);
		break;
	}
	return;
}
void Nonlinear::SetDesc(size_t target, network& workspace)
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
	size_t i;
	GraphNode* New;
	size_t left, right, degree;
	GraphNode* Left, * Right;
	Nonlinear* temp;
	New = workspace.net[target].content;
	degree = workspace.net[target].InDegree;
	if (degree == 0) throw PikaError("Nonlinear::SetDesc", "degree == 0", degree);
	left = workspace.net[target].In[0];
	Left = workspace.net[left].content;

	switch (NT)
	{
	case Pikachu::GraphNode::_activation_:
		descriptor.Set(Left->descriptor);
		break;
	case Pikachu::GraphNode::_manifold_:
		throw PikaError("Nonlinear::SetDesc", "case Pikachu::GraphNode::_manifold_", Op);
		break;
	case Pikachu::GraphNode::_cluster_:
		//BackCore2(No, label, workspace);
		descriptor.Clear();
		for (i = 0; i < SrcDim; i++)
			descriptor.AppendDim(Left->descriptor[i]);
		for (i = 0; i < cl.GetOrder(); i++)
			descriptor.AppendDim(cl.GetDim(i));
		for (i = SrcDim + 1; i < Left->descriptor.GetOrder(); i++)
			descriptor.AppendDim(Left->descriptor[i]);
		break;
	case Pikachu::GraphNode::_activationBack_:
		if (degree != 3) throw PikaError("Nonlinear::SetDesc", "degree != 3", degree);
		right = workspace.net[target].In[2];
		Right = workspace.net[right].content;
		//if(Left->descriptor == Right->descriptor)
		descriptor.Set(Right->descriptor);
		//else
		//	throw PikaError("Nonlinear::SetDesc", "_activationBack_::Left->descriptor == Right->descriptor", degree);
		break;
	case Pikachu::GraphNode::_activationHv_:
		descriptor.Set(Left->descriptor);
		break;
	case Pikachu::GraphNode::_HvFinal_:
		right = workspace.net[target].In[5];
		Right = workspace.net[right].content;
		descriptor.Set(Right->descriptor);
		break;
	default:
		throw PikaError("Nonlinear::SetDesc", "switch (LT)", Op);
		break;
	}
}
void Nonlinear::backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
	if (next == _uintMax_) SetNext(No, workspace);
	switch (NT)
	{
	case Pikachu::GraphNode::_activation_:
		BackCore1A(No, label, workspace);
		if (!dYdX) BackCore1AdLdW(No, label, workspace);
		break;
	case Pikachu::GraphNode::_manifold_:
		throw PikaError("Nonlinear::backward", "case Pikachu::GraphNode::_manifold_", Op);
		break;
	case Pikachu::GraphNode::_cluster_:
		BackCore2C(No, label, workspace);
		break;
		//case Pikachu::GraphNode::_activationBack_:
		//	throw PikaError("Nonlinear::backward", "case Pikachu::GraphNode::_manifold_", Op);
		//	break;
		//case Pikachu::GraphNode::_activationHv_:
		//	throw PikaError("Nonlinear::backward", "case Pikachu::GraphNode::_manifold_", Op);
		//	break;
	default:
		throw PikaError("Nonlinear::backward", "switch (LT)", Op);
		break;
	}
	return;
}
void Nonlinear::BackCore1A(size_t No, vector<size_t>& label, network& workspace)
{
	GraphNode* Src;
	Elementwise* Mul;
	size_t site;
	size_t original;
	size_t source, mul, inDeg;
	size_t i;

	inDeg = workspace.net[No].InDegree;
	source = workspace.net[No].In[0];
	original = label[No];
	Src = workspace.net[original].content;

	mul = workspace.append(_elementwise_, _mul_);
	Mul = (Elementwise*)(workspace.net[mul].content);
	Mul->descE.build(descriptor.GetOrder(), Src->descriptor.GetOrder());
	//Mul->descE.backward(Src->descriptor, descE, left);
	workspace.net.append(next, original, mul);
	workspace.SetDesc(mul);

	workspace.BackwardAppend(source, mul, label);
}
void Nonlinear::BackCore2C(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	GraphNode* Src, * Ori;
	Linear* Mul;
	size_t site;
	size_t original;
	size_t source, mul;

	source = workspace.net[No].In[0];
	Src = workspace.net[source].content;

	original = label[No];
	Ori = workspace.net[original].content;

	mul = workspace.append(_linear_, _contraction_);
	Mul = (Linear*)(workspace.net[mul].content);
	Mul->Desc.Build(Src->descriptor, SrcDim, Ori->descriptor, cl.GetOrder());
	workspace.net.append(next, original, mul);
	workspace.SetDesc(mul);


	workspace.BackwardAppend(source, mul, label);
}
void Nonlinear::BackCore1AdLdW(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	size_t site;
	size_t original;
	size_t sourceL, sourceR, inDeg;

	inDeg = workspace.net[No].InDegree;
	if (inDeg == 1) return;
	sourceL = workspace.net[No].In[0];
	sourceR = workspace.net[No].In[1];
	original = label[No];

	site = workspace.append(_nonlinear_, _activationBack_);
	New = (Nonlinear*)(workspace.net[site].content);
	New->apb.Set(ac);
	New->apb.Simplify();

	workspace.net.append(sourceL, original, sourceR, site);
	workspace.SetDesc(site);

	workspace.BackwardAppend(sourceR, site, label);
}
void Nonlinear::SetNext(size_t No, network& workspace)
{
	NonlinearType NT;
	Nonlinear* New;
	GraphNode* Src;
	size_t site;
	size_t source, inDeg;

	NT = (NonlinearType)Op;

	inDeg = workspace.net[No].InDegree;
	source = workspace.net[No].In[0];
	Src = workspace.net[source].content;

	switch (NT)
	{
	case Pikachu::GraphNode::_activation_:
		site = workspace.append(_nonlinear_, _activation_);
		New = (Nonlinear*)(workspace.net[site].content);
		New->ac.Copy(ac);
		New->ac.Differetial();
		if (inDeg == 1)
			workspace.net.append(source, site);
		else
			workspace.net.append(source, workspace.net[No].In[1], site);
		workspace.SetDesc(site);
		next = site;
		break;
	case Pikachu::GraphNode::_manifold_:
		throw PikaError("Nonlinear::SetNext", "case Pikachu::GraphNode::_manifold_", Op);
		break;
	case Pikachu::GraphNode::_cluster_:
		site = workspace.append(_nonlinear_, _cluster_);
		New = (Nonlinear*)(workspace.net[site].content);
		New->cl.copy(cl);
		New->cl.differential();
		New->SrcDim = SrcDim;
		workspace.net.append(source, site);
		workspace.SetDesc(site);
		next = site;
		break;
	default:
		throw PikaError("Nonlinear::SetNext", "switch (LT)", Op);
		break;
	}
	return;
}
void Nonlinear::forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
	size_t source;
	source = workspace.net[No].In[0];
	if (label[source] == _uintMax_) return;
	//throw PikaError("Nonlinear::forward", "label[No] == _uintMax_", Op);
	if (next == _uintMax_) SetNext(No, workspace);

	switch (NT)
	{
	case Pikachu::GraphNode::_activation_:
		ForwardCore1A(No, label, workspace);
		if (!dYdX)  ForwardCore1AHdv(No, label, workspace);
		break;
	case Pikachu::GraphNode::_manifold_:
		throw PikaError("Nonlinear::forward", "case Pikachu::GraphNode::_manifold_", Op);
		break;
	case Pikachu::GraphNode::_cluster_:
		ForwardCore2C(No, label, workspace);
		break;
	case Pikachu::GraphNode::_activationBack_:
		if (dYdX) throw PikaError("Nonlinear::forward", "dYdX switch (LT)", Op);
		else  ForwardCore3ABack(No, label, workspace);
		break;
	default:
		throw PikaError("Nonlinear::forward", "switch (LT)", Op);
		break;
	}
	return;
}
void Nonlinear::ForwardCore1A(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	GraphNode* Src;
	Elementwise* Mul;
	size_t site;
	size_t original, source;
	size_t mul;

	source = workspace.net[No].In[0];
	original = label[source];
	Src = workspace.net[original].content;

	mul = workspace.append(_elementwise_, _mul_);
	Mul = (Elementwise*)(workspace.net[mul].content);
	Mul->descE.build(descriptor.GetOrder(), Src->descriptor.GetOrder());
	workspace.net.append(next, original, mul);
	workspace.SetDesc(mul);
	workspace.BackwardAppend(No, mul, label);
}
void Nonlinear::ForwardCore2C(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	GraphNode* Src, * Ori;
	Linear* Mul;
	size_t site;
	size_t original;
	size_t source, mul;

	source = workspace.net[No].In[0];
	Src = workspace.net[source].content;

	original = label[source];
	Ori = workspace.net[original].content;

	mul = workspace.append(_linear_, _contraction_);
	Mul = (Linear*)(workspace.net[mul].content);
	Mul->Desc.ForwardBuild(Src->descriptor, SrcDim, Ori->descriptor, cl.GetOrder());
	workspace.net.append(next, original, mul);
	workspace.SetDesc(mul);

	workspace.BackwardAppend(No, mul, label);
}
void Nonlinear::ForwardCore1AHdv(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	size_t site;
	size_t source, inDeg;
	size_t weights;
	inDeg = workspace.net[No].InDegree;
	if (inDeg == 1) return;
	source = workspace.net[No].In[0];
	weights = workspace.net[No].In[1];

	site = workspace.append(_nonlinear_, GraphNode::_activationHv_);
	New = (Nonlinear*)(workspace.net[site].content);
	New->ahf.Set(ac);
	New->ahf.Simplify();

	workspace.net.append(source, label[weights], weights, site);
	workspace.SetDesc(site);
}
void Nonlinear::ForwardCore3ABack(size_t No, vector<size_t>& label, network& workspace)
{
	Nonlinear* New;
	size_t site;
	size_t source, inDeg;
	size_t weights, outputBack;
	inDeg = workspace.net[No].InDegree;
	if (inDeg != 3) throw PikaError("Nonlinear::ForwardCore3ABack", "inDeg != 3", inDeg);
	source = workspace.net[No].In[0];
	outputBack = workspace.net[No].In[1];
	weights = workspace.net[No].In[2];

	site = workspace.append(_nonlinear_, GraphNode::_HvFinal_);
	New = (Nonlinear*)(workspace.net[site].content);
	New->hff.Set(apb);
	New->hff.Simplify();

	workspace.net.append(source, outputBack, label[source], site);
	workspace.net.append(label[outputBack], label[weights], weights, site);
	workspace.SetDesc(site);
}


Elementwise::Elementwise()
{
	Type = _elementwise_;
}
Elementwise::Elementwise(GraphNode::ElementwiseType t)
{
	Type = _elementwise_;
	Op = (int)t;
}
Elementwise::~Elementwise()
{
}
GraphNode* Elementwise::copy(void) const
{
	Elementwise* node;
	node = new Elementwise();
	CopyCore(*node);
	node->descE.Set(descE);
	return node;
}
void Elementwise::SetDesc(const tensor& SrcL, const tensor& SrcR)
{
	descriptor.Elementwise(SrcL, SrcR, descE);
}
void Elementwise::backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	ElementwiseType ET;
	ET = (ElementwiseType)Op;
	double alpha;
	alpha = (ET == _sub_ ? -1.0 : 1.0);
	switch (ET)
	{
	case Pikachu::GraphNode::_add_:
	case Pikachu::GraphNode::_sub_:
		BackCore1(true, 1.0, No, label, workspace);
		BackCore1(false, alpha, No, label, workspace);
		break;
	case Pikachu::GraphNode::_mul_:
		BackCore2(true, No, label, workspace);
		BackCore2(false, No, label, workspace);
		break;
	default:
		throw PikaError("Elementwise::BackwardAppend", "switch (ET)", Op);
		break;
	}
}
void Elementwise::BackCore1(bool left, double alpha, size_t No, vector<size_t>& label, network& workspace)const
{
	Transform* New;
	GraphNode* Src;
	size_t site;
	size_t original;
	size_t dst;

	dst = workspace.net[No].In[(left ? 0 : 1)];

	original = label[No];
	Src = workspace.net[original].content;

	site = workspace.append(_tansform_, _condense_);
	New = (Transform*)(workspace.net[site].content);
	New->CondenDesc2.backward(Src->descriptor, descE, left);
	workspace.net.append(original, site);
	workspace.SetDesc(site);
	//New->descriptor.Condensation(Src->descriptor, New->CondenDesc2);
	New->alpha = alpha;
	workspace.BackwardAppend(dst, site, label);
}
void Elementwise::BackCore2(bool left, size_t No, vector<size_t>& label, network& workspace)const
{
	Elementwise* First;
	Transform* New;
	size_t site, first;
	GraphNode* Src, * SrcLR;
	size_t original, dst;

	dst = workspace.net[No].In[(left ? 1 : 0)];
	SrcLR = workspace.net[dst].content;
	original = label[No];
	Src = workspace.net[original].content;

	first = workspace.append(_elementwise_, _mul_);
	First = (Elementwise*)(workspace.net[first].content);
	First->descE.backward(Src->descriptor, descE, left);
	workspace.net.append(original, dst, first);
	workspace.SetDesc(first);
	//First->descriptor.Elementwise(Src->descriptor, SrcLR->descriptor, First->descE);

	site = workspace.append(_tansform_, _condense_);
	New = (Transform*)(workspace.net[site].content);
	New->CondenDesc2.backward(First->descriptor, descE, left);
	workspace.net.append(first, site);
	workspace.SetDesc(site);
	//New->descriptor.Condensation(First->descriptor, New->CondenDesc2);


	workspace.BackwardAppend(dst, site, label);
}
void Elementwise::forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	ElementwiseType ET;
	ET = (ElementwiseType)Op;
	double alpha;
	alpha = (ET == _sub_ ? -1.0 : 1.0);
	switch (ET)
	{
	case Pikachu::GraphNode::_add_:
	case Pikachu::GraphNode::_sub_:
		ForwardCore1(No, label, workspace);
		break;
	case Pikachu::GraphNode::_mul_:
		ForwardCore2(No, label, workspace);
		break;
	default:
		throw PikaError("Elementwise::BackwardAppend", "switch (ET)", Op);
		break;
	}
}
void Elementwise::ForwardCore1(size_t No, vector<size_t>& label, network& workspace)const
{
	size_t left, right, site;
	Elementwise* New;
	Transform* Single;
	GraphNode* Left, * Right;
	left = workspace.net[No].In[0];
	right = workspace.net[No].In[1];
	if (label[left] != _uintMax_) Left = workspace.net[label[left]].content;
	if (label[right] != _uintMax_) Right = workspace.net[label[right]].content;

	if (label[left] == _uintMax_)
	{
		if (label[right] != _uintMax_)
		{
			site = workspace.append(_tansform_, _dispatch_);
			Single = (Transform*)(workspace.net[site].content);
			Single->DisDesc1.forward(Right->descriptor, descE, false);
			if ((ElementwiseType)Op == _sub_) Single->SetAlpha(-1);
			workspace.net.append(label[right], site);
		}
		//else
			//throw PikaError("Elementwise::ForwardCore1", "label[left] == 0 && label[right] == 0", Op);
	}
	else
	{
		if (label[right] == _uintMax_)
		{
			site = workspace.append(_tansform_, _dispatch_);
			Single = (Transform*)(workspace.net[site].content);
			Single->DisDesc1.forward(Left->descriptor, descE, true);
			workspace.net.append(label[left], site);
		}
		else
		{
			site = workspace.append(_elementwise_, (ElementwiseType)Op);
			New = (Elementwise*)(workspace.net[site].content);
			New->descE.forward(Left->descriptor, Right->descriptor, descE);
			workspace.net.append(label[left], label[right], site);
		}
	}
	workspace.SetDesc(site);
	workspace.DifferentialOutAppend(No, site, label);
}
void Elementwise::ForwardCore2(size_t No, vector<size_t>& label, network& workspace)const
{
	size_t left, right, site;
	Elementwise* New;
	GraphNode* Left, * Right;
	left = workspace.net[No].In[0];
	right = workspace.net[No].In[1];
	if (label[left] != _uintMax_) Left = workspace.net[label[left]].content;
	if (label[right] != _uintMax_) Right = workspace.net[label[right]].content;
	if (label[left] != _uintMax_)
	{
		site = workspace.append(_elementwise_, Pikachu::GraphNode::_mul_);
		New = (Elementwise*)(workspace.net[site].content);
		New->descE.forward(Left->descriptor, true, descE);
		workspace.net.append(label[left], right, site);
		workspace.SetDesc(site);
		workspace.DifferentialOutAppend(No, site, label);
	}
	//else if(label[right] == _uintMax_)
	//	throw PikaError("Elementwise::ForwardCore2", "label[left] == 0 && label[right] == 0", Op);
	if (label[right] != _uintMax_)
	{
		site = workspace.append(_elementwise_, Pikachu::GraphNode::_mul_);
		New = (Elementwise*)(workspace.net[site].content);
		New->descE.forward(Right->descriptor, false, descE);
		workspace.net.append(left, label[right], site);
		workspace.SetDesc(site);
		workspace.DifferentialOutAppend(No, site, label);
	}
}

Transform::Transform()
{
	Type = _tansform_;
	alpha = 1.0;
}
Transform::Transform(GraphNode::TransformType t)
{
	Type = _tansform_;
	Op = (int)t;
}
Transform::~Transform()
{
}
GraphNode* Transform::copy(void) const
{
	Transform* node;
	node = new Transform();
	CopyCore(*node);
	node->DisDesc1.Set(DisDesc1);
	node->CondenDesc2.Set(CondenDesc2);
	node->alpha = alpha;
	return node;
}
void Transform::SetDesc(const tensor& SrcL, const tensor& SrcR)
{
	TransformType TT;
	TT = (TransformType)Op;
	switch (TT)
	{
	case Pikachu::GraphNode::_identity_:
		descriptor.Set(SrcL);
		break;
	case Pikachu::GraphNode::_condense_:
		descriptor.Condensation(SrcL, CondenDesc2);
		break;
	case Pikachu::GraphNode::_dispatch_:
		descriptor.Dispatch(SrcL, DisDesc1);
		break;
		break;
	default:
		throw PikaError("Transform::SetDesc", "error Op", TT);
		break;
	}
}
void Transform::backward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	TransformType TT;
	size_t dst, site;
	size_t original;
	Transform* New;
	GraphNode* Src;
	TT = (TransformType)Op;
	dst = workspace.net[No].In[0];
	original = label[No];
	Src = workspace.net[original].content;
	switch (TT)
	{
	case Pikachu::GraphNode::_identity_:
		workspace.BackwardAppend(dst, original, label);
		break;
	case Pikachu::GraphNode::_condense_:
		site = workspace.append(_tansform_, _dispatch_);
		New = (Transform*)(workspace.net[site].content);
		New->DisDesc1.backward(Src->descriptor, CondenDesc2);
		workspace.net.append(original, site);
		workspace.SetDesc(site);
		workspace.BackwardAppend(dst, site, label);
		break;
	case Pikachu::GraphNode::_dispatch_:
		site = workspace.append(_tansform_, _condense_);
		New = (Transform*)(workspace.net[site].content);
		New->CondenDesc2.backward(Src->descriptor, DisDesc1);
		workspace.net.append(original, site);
		workspace.SetDesc(site);
		workspace.BackwardAppend(dst, site, label);
		break;
	default:
		throw PikaError("Transform::backward", "error Op", TT);
		break;
	}
}
void Transform::forward(bool dYdX, size_t No, vector<size_t>& label, network& workspace)
{
	TransformType TT;
	size_t source, site;
	size_t original;
	GraphNode* Ori;
	Transform* New;
	TT = (TransformType)Op;
	source = workspace.net[No].In[0];
	original = label[source];
	if (original == _uintMax_) return;
	Ori = workspace.net[original].content;
	switch (TT)
	{
	case Pikachu::GraphNode::_identity_:
		//ForwardCore1I(No, label, workspace);
		site = original;
		break;
	case Pikachu::GraphNode::_condense_:
		site = workspace.append(_tansform_, _condense_);
		New = (Transform*)(workspace.net[site].content);
		New->CondenDesc2.forward(Ori->descriptor, CondenDesc2);
		workspace.net.append(original, site);
		workspace.SetDesc(site);
		break;
	case Pikachu::GraphNode::_dispatch_:
		site = workspace.append(_tansform_, _dispatch_);
		New = (Transform*)(workspace.net[site].content);
		New->DisDesc1.forward(Ori->descriptor, DisDesc1);
		workspace.net.append(original, site);
		workspace.SetDesc(site);
		break;
	default:
		throw PikaError("Transform::backward", "error Op", TT);
		break;
	}
	workspace.DifferentialOutAppend(No, original, label);
}
void Transform::SetAlpha(long long int ele)
{
	alpha = ele;
}



network::network()
{
	Initialized = false;
	LossCompute = false;
	Hessian = false;
	FinalSimplified = false;
}
network::~network()
{
	size_t i;
	for (i = 0; i < OutInfor.count(); i++)
		delete OutInfor[i];
}
void network::backward(void)
{
	vector<size_t> label, sequence;
	buffer<size_t> queue;
	size_t i, length, now, site;
	GraphNode* here;
	Leaf* TempLeaf;
	if (!Initialized)
		throw PikaError("network::backward(void)", "!Initialized", 0);
	if (LossCompute)
		throw PikaError("network::backward(void)", "LossCompute", 0);
	for (i = 0; i < output.count(); i++)
	{
		queue.append(output[i]);
	}
	net.BFTbackward(label, queue);
	net.TopologicalSortingBack(sequence);
	net.SortingShrink(label, sequence);
	length = sequence.count();
	label.value(_uintMax_);

	for (i = 0; i < output.count(); i++)
	{
		now = output[i];
		here = net[now].content;
		TempLeaf = new Leaf(GraphNode::_leafIn_);
		TempLeaf->SetDesc(here->descriptor, here->descriptor);
		TempLeaf->Label = i;
		label[now] = net.MoveAppend(TempLeaf);
		dLossdO.append(label[now]);
	}

	for (i = 0; i < length; i++)
	{
		now = sequence[i];
		here = net[now].content;
		here->backward(false, now, label, *this);
	}
	for (i = 0; i < parameter.count(); i++)
	{
		now = parameter[i];
		here = net[now].content;
		if (!(here->Type == GraphNode::_leaf_ && here->Op == (int)GraphNode::_leafPara_))
			throw PikaError("network::backward(void)", "parameter is not parameter", i);
		if (label[now] == _uintMax_)
			throw PikaError("network::backward(void)", "label[now] == _uintMax_", now);

		TempLeaf = (Leaf*)net[label[now]].content;
		TempLeaf->IfOutput = true;
		TempLeaf->Label = i;
		LossDifferential.append(label[now]);
	}
	SetUnknown(GraphNode::dLdW);
	LossCompute = true;
}
void network::forward(void)
{
	vector<size_t> label, sequence;
	buffer<size_t> queue;
	size_t i, length, now, site;
	GraphNode* here;
	Leaf* TempLeaf;
	if (!LossCompute)
		throw PikaError("network::forward(void)", "!LossCompute", 0);
	if (Hessian)
		throw PikaError("network::forward(void)", "Hessian", 0);

	for (i = 0; i < LossDifferential.count(); i++)
		queue.append(LossDifferential[i]);

	net.BFTbackward(label, queue);
	net.TopologicalSorting(sequence);
	net.SortingShrink(label, sequence);

	length = sequence.count();
	label.value(_uintMax_);

	for (i = 0; i < parameter.count(); i++)
	{
		now = parameter[i];
		here = net[now].content;
		TempLeaf = new Leaf(GraphNode::_leafIn_);
		TempLeaf->SetDesc(here->descriptor, here->descriptor);
		TempLeaf->Label = i;
		label[now] = net.MoveAppend(TempLeaf);
		VectorIn.append(label[now]);
	}

	for (i = 0; i < length; i++)
	{
		now = sequence[i];
		here = net[now].content;
		here->forward(false, now, label, *this);
		//if (here->IfOutput == true) SetOutput(now, label[now], No);
	}
	for (i = 0; i < LossDifferential.count(); i++)
	{
		now = LossDifferential[i];
		here = net[now].content;
		if (!(here->Type == GraphNode::_leaf_ && here->Op == (int)GraphNode::_leafPara_))
			throw PikaError("network::forward(void)", "parameter is not parameter", i);
		if (label[now] == _uintMax_)
			throw PikaError("network::forward(void)", "label[now] == _uintMax_", now);

		TempLeaf = (Leaf*)net[label[now]].content;
		TempLeaf->IfOutput = true;
		TempLeaf->Label = i;
		HessianVector.append(label[now]);
	}
	SetUnknown(GraphNode::Hdv);
	Hessian = true;
}
void network::copy(network& source)
{

}
void network::backward(size_t No)
{
	buffer<size_t> queue;
	size_t i, length, now, site;
	GraphNode* here;
	Leaf* TempLeaf;
	vector<size_t> label;
	vector<size_t> sequence;

	backwardCheck(No);

	queue.append(output[No]);
	net.BFTbackward(label, queue);
	net.TopologicalSortingBack(sequence);
	net.SortingShrink(label, sequence);
	length = sequence.count();
	label.value(_uintMax_);

	TempLeaf = new Leaf();
	TempLeaf->Initial(net[output[No]].content->descriptor);
	label[output[No]] = net.MoveAppend(TempLeaf);

	for (i = 0; i < length; i++)
	{
		now = sequence[i];
		here = net[now].content;
		here->backward(true, now, label, *this);
		if (here->Type == GraphNode::_leaf_ && here->Op == (int)GraphNode::_leafIn_)
		{
			TempLeaf = (Leaf*)here;
			SetOutput(No, label[now], TempLeaf->Label);
		}
	}
	SetUnknown(GraphNode::dYdX);
	return;
}
void network::forward(size_t No)
{
	vector<size_t> label, sequence;
	buffer<size_t> queue;
	size_t i, length, now, site;
	GraphNode* here;
	Leaf* TempLeaf;
	if (!Initialized)
		throw PikaError("network::forward(size_t)", "!Initialized", 0);
	for (i = 0; i < output.count(); i++)
	{
		queue.append(output[i]);
	}

	net.BFTbackward(label, queue);
	net.TopologicalSorting(sequence);
	net.SortingShrink(label, sequence);

	length = sequence.count();
	label.value(_uintMax_);

	for (i = 0; i < net.capacity(); i++)
	{
		if (!(net[i].IfValid())) continue;
		here = net[i].content;
		if (here->Type == GraphNode::_leaf_ && here->Op == (int)GraphNode::_leafIn_)
		{
			TempLeaf = (Leaf*)here;
			if (TempLeaf->Label == No)
			{
				TempLeaf = new Leaf();
				TempLeaf->Initial(net[i].content->descriptor);
				label[i] = net.MoveAppend(TempLeaf);
				break;
			}
		}

	}
	if (i == net.capacity())
		throw PikaError("network::forward(size_t)", "i == net.capacity()", i);

	for (i = 0; i < length; i++)
	{
		now = sequence[i];
		here = net[now].content;
		here->forward(true, now, label, *this);
		if (here->IfOutput == true) SetOutput(now, label[now], No);
	}
	SetUnknown(GraphNode::dYdX);
}

void network::backwardCheck(size_t No)
{
	if (No >= output.count())
		throw PikaError("network::backward", "No >= output.count()", No);
	if (output[No] >= net.capacity())
		throw PikaError("network::backward", "output[No] >= net.capacity()", output[No]);
	if (!net[output[No]].IfValid())
		throw PikaError("network::backward", "!net[output[No]].IfValid()", net.capacity());
	if (!Initialized)
		throw PikaError("network::backward", "!Initialized", 0);
}
void network::SetUnknown(GraphNode::Affiliation value)
{
	size_t i;
	GraphNode* here;
	for (i = 0; i < net.capacity(); i++)
	{
		if (!(net[i].IfValid())) continue;
		here = net[i].content;
		if (here->Affi == GraphNode::unknown)
			here->Affi = value;
	}
	return;
}
void network::SetOutput(size_t old, size_t theNewOutput, size_t dX)
{
	elaboration* oldDesc, * newDesc;
	output.append(theNewOutput);
	if (theNewOutput != _uintMax_)
		net[theNewOutput].content->IfOutput = true;

	oldDesc = OutInfor[old];
	newDesc = new elaboration;
	newDesc->attach(*oldDesc, dX);

	OutInfor.append(newDesc);
}
GraphNode* network::NewNode(GraphNode::VortexT type, int op)
{
	GraphNode* New;
	switch (type)
	{
	case Pikachu::GraphNode::_leaf_:
		New = new Leaf((GraphNode::LeafType)op);
		break;
	case Pikachu::GraphNode::_tansform_:
		New = new Transform((GraphNode::TransformType)op);
		break;
	case Pikachu::GraphNode::_elementwise_:
		New = new Elementwise((GraphNode::ElementwiseType)op);
		break;
	case Pikachu::GraphNode::_nonlinear_:
		New = new Nonlinear((GraphNode::NonlinearType)op);
		break;
	case Pikachu::GraphNode::_linear_:
		New = new Linear((GraphNode::LinearType)op);
		break;
	case Pikachu::GraphNode::_extra_:
		New = new Leaf((GraphNode::LeafType)op);
		break;
	default:
		throw PikaError("network::append", "Error type", op);
		break;
	}
	return New;
}
size_t network::append(GraphNode::VortexT type, int op)
{
	GraphNode* New;
	size_t site;
	New = NewNode(type, op);
	site = net.MoveAppend(New);
	return site;
}
void network::BackwardAppend(size_t target, size_t source, vector<size_t>& label)
{
	/*Elementwise* New;
	size_t site, original;
	GraphNode* Left, * Right;
	original = label[target];
	if (original == 0) label[target] = source;
	else
	{
		New = new Elementwise(GraphNode::_add_);
		site = net.MoveAppend(New);
		Left = net[original].content;
		Right = net[source].content;
		if (!(Left->descriptor == Right->descriptor))
			throw PikaError("network::BackwardAppend", "left != right", site);
		New->descE.build(Left->descriptor.GetOrder());
		New->descriptor.Elementwise(Left->descriptor, Right->descriptor, New->descE);
		net.append(original, source, site);
		label[target] = site;
	}*/
	DifferentialOutAppend(target, source, label);
}
void network::DifferentialOutAppend(size_t target, size_t source, vector<size_t>& label)
{
	Elementwise* New;
	size_t site, original;
	GraphNode* Left, * Right;
	original = label[target];
	if (original == _uintMax_) label[target] = source;
	else
	{
		New = new Elementwise(GraphNode::_add_);
		site = net.MoveAppend(New);
		Left = net[original].content;
		Right = net[source].content;
		if (!(Left->descriptor == Right->descriptor))
			throw PikaError("network::BackwardAppend", "left != right", site);
		New->descE.build(Left->descriptor.GetOrder());
		New->descriptor.Elementwise(Left->descriptor, Right->descriptor, New->descE);
		net.append(original, source, site);
		label[target] = site;
	}
}
void network::SetDesc(size_t target)
{
	GraphNode* New;
	size_t left, right, degree;
	GraphNode* Left, * Right;
	Nonlinear* temp;
	New = net[target].content;
	degree = net[target].InDegree;
	if (degree == 0) return;
	left = net[target].In[0];
	Left = net[left].content;
	right = (degree == 1) ? left : net[target].In[1];
	Right = net[right].content;

	if (New->Type != GraphNode::_nonlinear_) New->SetDesc(Left->descriptor, Right->descriptor);
	else
	{
		temp = (Nonlinear*)New;
		temp->SetDesc(target, *this);
	}
}

bool network::Simplify(void)
{
	bool changed_;
	size_t round_;
	round_ = 0;
	do
	{
		round_ += 1;
		changed_ = false;
		changed_ = changed_ || Simplify01RedundancyCut();
		//changed_ = changed_ || Simplify01();
		//changed_ = changed_ || Simplify03();


	} while (changed_);
	//changed_ = changed_ || Simplify05();
	if (round_ > 1)
	{

	}
	return round_ > 1;
}
bool network::SimplifyFinal(void)
{
	bool changed_;
	size_t round_;
	round_ = 0;
	do
	{
		round_ += 1;
		changed_ = false;
		changed_ = changed_ || Simplify01RedundancyCut();
		changed_ = changed_ || Simplify02ClusterFusion();
		//changed_ = changed_ || Simplify03();


	} while (changed_);
	//changed_ = changed_ || Simplify05();
	if (round_ > 1)
	{

	}
	FinalSimplified = true;
	return round_ > 1;
}
bool network::Simplify01RedundancyCut(void)
{
	bool changed_;
	buffer<size_t> queue;
	size_t i;
	GraphNode* here;
	vector<size_t> label;
	Leaf* LL;
	changed_ = false;
	queue.clear();
	for (i = 0; i < output.count(); i++)
		queue.append(output[i]);
	net.BFTbackward(label, queue);
	for (i = 0; i < net.capacity(); i++)
	{
		if (!(net[i].IfValid())) continue;
		here = net[i].content;
		if (label[i])continue;
		if (here->Type != GraphNode::_leaf_)
		{
			net.VertexDelete(i);
			changed_ = true;
		}
		else if ((GraphNode::LeafType)here->Op == GraphNode::_leafConst_)
		{
			net.VertexDelete(i);
			changed_ = true;
		}
	}
	return changed_;
}
bool network::Simplify02ClusterFusion(void)
{
	bool changed_;
	changed_ = false;
	return changed_;
}

