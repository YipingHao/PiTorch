#include"../header/Pikachu.h"
#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif


using namespace Pikachu;

Node::Node()
{
	IfOutput = false;
	DataExpand = true;
	Affi = unknown;
	network = NULL;
}
Node::~Node()
{

}
void Node::CopyCoreN(Node& dst) const
{
	dst.Type = Type;
	dst.Op = Op;
	dst.IfOutput = IfOutput;
	dst.descriptor.Set(descriptor);
	CopyToCore(dst);
	return;
}
void Node::setDesc(const Tensor& desc)
{
	descriptor.Set(desc);
}
void Node::setDesc(const Tensor& desc, const vector<size_t>& H)
{
	Tensor descTemp;
	size_t i;
	descTemp.Set(desc);
	for (i = 0; i < H.count(); i++)
		descTemp.append(H[i]);
	descriptor.Set(descTemp);
}

void Node::clearCore(void)
{
	ArcClear();
}


LeafNode::LeafNode()
{
	Type = _leaf_;
}
LeafNode::LeafNode(NetWork* context, Node::LeafType t)
{
	Type = _leaf_;
	Op = (int)t;
	network = context;
}
LeafNode::~LeafNode()
{

}
DiLinear::DiLinear()
{
	Type = _DiLinear_;
}
DiLinear::DiLinear(Node::OpType OT)
{
	Type = _DiLinear_;
	Op = (int)OT;
}
DiLinear::~DiLinear()
{
}
DiNonlinear::DiNonlinear()
{
	Type = _DiNonlinear_;
}
DiNonlinear::~DiNonlinear()
{
}
MonoLinear::MonoLinear()
{
	Type = _MonoLinear_;
}
MonoLinear::~MonoLinear()
{
}
MonoNonlinear::MonoNonlinear()
{
	formula = NULL;
	Type = _MonoNonlinear_;
	next = _uintMax_;
	SrcDim = 0;

	gradient = NULL;
}
MonoNonlinear::~MonoNonlinear()
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
	switch (NT)
	{
	case Pikachu::Node::_activation_:
	{
		cluster*cl;
		cl = (cluster*)formula;
		delete cl;
		break;
	}
	case Pikachu::Node::_manifold_:
	{
		manifolds*man;
		man = (manifolds*)formula;
		delete man;
		break;
	}
	case Pikachu::Node::_cluster_:
	{
		activation* ac;
		ac = (activation*)formula;
		delete ac;
		break;
	}
	case Pikachu::Node::_activationBack_:
	{
		ActiParaBackward* apb;
		apb = (ActiParaBackward*)formula;
		delete apb;
		break;
	}
	case Pikachu::Node::_activationHv_:
	{
		ActiHvForward*ahf;
		ahf = (ActiHvForward*)formula;
		delete ahf;
		break;
	}
	case Pikachu::Node::_HvFinal_:
	{
		HvForwardFinal*hff;
		hff = (HvForwardFinal*)formula;
		delete hff;
		break;
	}
	default:
		break;
	}
	formula = NULL;
}

Node* LeafNode::copy(void) const
{
	Node* node;
	node = new LeafNode;
	//node->CopyCore(*this);
	CopyCoreN(*node);
	//node->Desc.Set(Desc);
	return node;
}
Node* DiLinear::copy(void) const
{
	DiLinear* node;
	node = new DiLinear();
	CopyCoreN(*node);
	//node->descE.Set(descE);
	return node;
}
Node* DiNonlinear::copy(void) const
{
	DiNonlinear* node;
	node = new DiNonlinear();
	CopyCoreN(*node);
	//node->DisDesc1.Set(DisDesc1);
	//node->CondenDesc2.Set(CondenDesc2);
	//node->alpha = alpha;
	return node;
}
Node* MonoLinear::copy(void) const
{
	MonoLinear* node;
	node = new MonoLinear();
	CopyCoreN(*node);
	//node->Desc.Set(Desc);
	return node;
}
Node* MonoNonlinear::copy(void) const
{
	MonoNonlinear* node;
	node = new MonoNonlinear();
	CopyCoreN(*node);
	NonlinearType NT;
	NT = (NonlinearType)Op;
	switch (NT)
	{
	case Pikachu::Node::_activation_:
	{
		cluster* cl;
		cl = new cluster;
		cl->copy(*((cluster*)formula));
		node->formula = (void*)cl;
		break;
	}
	case Pikachu::Node::_manifold_:
	{
		manifolds* man;
		man = new manifolds;
		man->copy(*((manifolds*)formula));
		node->formula = (void*)man;
		break;
	}
	case Pikachu::Node::_cluster_:
	{
		activation* ac;
		ac = new activation;
		ac->copy(*((activation*)formula));
		node->formula = (void*)ac;
		break;
	}
	case Pikachu::Node::_activationBack_:
	{
		ActiParaBackward* apb;
		apb = new ActiParaBackward;
		apb->copy(*((ActiParaBackward*)formula));
		node->formula = (void*)apb;
		break;
	}
	case Pikachu::Node::_activationHv_:
	{
		ActiHvForward* ahf;
		ahf = new ActiHvForward;
		ahf->copy(*((ActiHvForward*)formula));
		node->formula = (void*)ahf;
		break;
	}
	case Pikachu::Node::_HvFinal_:
	{
		HvForwardFinal* hff;
		hff = new HvForwardFinal;
		hff->copy(*((HvForwardFinal*)formula));
		node->formula = (void*)hff;
		break;
	}
	default:
		break;
	}
	return node;
}

void LeafNode::check(void) const
{

}
void DiLinear::check(void) const
{

}
void DiNonlinear::check(void) const
{

}
void MonoLinear::check(void) const
{

}
void MonoNonlinear::check(void) const
{

}

void LeafNode::clear(void)
{

}
void MonoLinear::clear(void)
{
	clearCore();
}
void DiLinear::clear(void)
{
	clearCore();
}
void MonoNonlinear::clear(void)
{
	clearCore();
}
void DiNonlinear::clear(void)
{
	clearCore();
}

void LeafNode::compute(Tensor& DescOut)const
{
	DescOut.Set(descriptor);
}
void MonoLinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		size_t site = indexSrc.search(indexDst[i]);
		if (site == _uintMax_)
		{
			DescOut.ChangeDim(i, descriptor[i]);
		}
		else DescOut.ChangeDim(i, in[0]->descriptor[site]);
	}
}
void DiLinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		size_t siteL = indexSrcL.search(indexDst[i]);
		size_t siteR = indexSrcR.search(indexDst[i]);
		if (siteL == _uintMax_)
		{
			if (siteR == _uintMax_)
			{
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "DiLinear::compute");
				error->append("error", "missing index");
				throw error;
			}
			else
				DescOut.ChangeDim(i, in[1]->descriptor[siteR]);
		}
		else
		{
			DescOut.ChangeDim(i, in[0]->descriptor[siteL]);
			if (siteR != _uintMax_)
			{
				if (in[0]->descriptor[siteL] != in[1]->descriptor[siteR])
				{
					hyperlex::dictionary* error = ErrorGive();
					error->append("location", "DiLinear::compute");
					error->append("error", "repeat index");
					error->append("siteL", "siteL");
					error->append("siteR", "siteR");
					throw error;
				}
			}
		}
	}
}
void MonoNonlinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		size_t siteS = indexSrc.search(indexDst[i]);
		size_t siteF = function.search(indexDst[i]);
		if (siteS == _uintMax_)
		{
			if (siteF == _uintMax_)
			{
				hyperlex::dictionary * error = ErrorGive();
				error->append("location", "MonoNonlinear::compute");
				error->append("error", "missing index");
				throw error;
			}
			else
				DescOut.ChangeDim(i, funcTensor[siteF]);
		}
		else
		{
			DescOut.ChangeDim(i, in[0]->descriptor[siteS]);
			if (siteF != _uintMax_)
			{
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "MonoNonlinear::compute");
				error->append("error", "repeated index");
				throw error;
			}
		}
	}
}
void DiNonlinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		size_t siteS = indexSrc.search(indexDst[i]);
		size_t siteF = function.search(indexDst[i]);
		size_t siteP = indexPara.search(indexDst[i]);
		size_t index = _uintMax_;
		int count = 0;
		if (siteS != _uintMax_)
		{
			count += 1;
			DescOut.ChangeDim(i, in[0]->descriptor[siteS]);
		}
		if (siteF != _uintMax_)
		{
			count += 1;
			DescOut.ChangeDim(i, funcTensor[siteF]);
		}
		if (siteP != _uintMax_)
		{
			count += 1;
			DescOut.ChangeDim(i, in[1]->descriptor[siteP]);
		}
		if (count != 0)
		{
			hyperlex::dictionary* error = ErrorGive();
			error->append("location", "DiNonlinear::compute");
			error->append("error", "error index");
			throw error;
		}
	}
}


void Node::PrintScreenCore(FILE* fp)const
{
	demo(fp);
	switch (Type)
	{
	case Pikachu::Node::_leaf_:
		fprintf(fp, "\ttype: leaf.\n");
		break;
	case Pikachu::Node::_MonoLinear_:
		fprintf(fp, "\ttype: MonoLinear.\n");
		break;
	case Pikachu::Node::_DiLinear_:
		fprintf(fp, "\ttype: DiLinear.\n");
		break;
	case Pikachu::Node::_MonoNonlinear_:
		fprintf(fp, "\ttype: MonoNonlinear.\n");
		break;
	case Pikachu::Node::_DiNonlinear_:
		fprintf(fp, "\ttype: DiNonlinear.\n");
		break;
	default:
		break;
	}
	descriptor.demo(fp, "descriptor");
}
void static printVecSint(FILE* fp, const char* name, const vector<sint>& source)
{
	fprintf(fp, "\t%s(%zu): [", name, source.count());
	if (source.count() != 0)
		fprintf(fp, "%zu", source[0]);
	for (size_t i = 1; i < source.count(); i++)
		fprintf(fp, ", %zu", source[i]);
	fprintf(fp, "]\n");
}

void LeafNode::PrintScreen(FILE* fp)const
{
	PrintScreenCore(fp);
	LeafType LT;
	LT = (Node::LeafType)Op;
	switch (LT)
	{
	case Pikachu::Node::_leafIn_:
		fprintf(fp, "\tleaf type: input.\n");
		break;
	case Pikachu::Node::_leafPara_:
		fprintf(fp, "\tleaf type: parameter.\n");
		break;
	case Pikachu::Node::_leafConst_:
		fprintf(fp, "\tleaf type: constant.\n");
		break;
	default:
		break;
	}
}
void MonoLinear::PrintScreen(FILE* fp)const
{
	PrintScreenCore(fp);
	fprintf(fp, "\talpha: %.16lf\n", alpha);
	printVecSint(fp, "indexDst", indexDst);
	printVecSint(fp, "indexSrc", indexSrc);
	fprintf(fp, "\tDummyIndex: %zu\n", DummyIndex);
	fprintf(fp, "\tNewIndex: %zu\n", NewIndex);
	fprintf(fp, "\tRepeatedIndex: %zu\n", RepeatedIndex);
}
void DiLinear::PrintScreen(FILE* fp)const
{
	PrintScreenCore(fp);
	printVecSint(fp, "indexDst", indexDst);
	printVecSint(fp, "indexSrcL", indexSrcL);
	printVecSint(fp, "indexSrcR", indexSrcR);
	fprintf(fp, "\tDummyIndex: %zu\n", DummyIndex);
	fprintf(fp, "\tRepeatedIndex: %zu\n", RepeatedIndex);
}
void MonoNonlinear::PrintScreen(FILE* fp)const
{
	PrintScreenCore(fp);
	funcTensor.demo(fp, "funcTensor");
	printVecSint(fp, "function", function);

	printVecSint(fp, "indexDst", indexDst);
	printVecSint(fp, "indexSrc", indexSrc);

	fprintf(fp, ScalarInput ? "\tScalarInput: true\n" : "\tScalarInput: false\n");
	fprintf(fp, "\tx: %lld\n", (long long)x);
}
void DiNonlinear::PrintScreen(FILE* fp)const
{
	PrintScreenCore(fp);
	funcTensor.demo(fp, "funcTensor");

	fprintf(fp, ScalarInput ? "\tScalarInput: true\n" : "\tScalarInput: false\n");
	fprintf(fp, "\tx: %lld\n", (long long)x);
	fprintf(fp, ScalarPara ? "\tScalarPara: true\n" : "\tScalarPara: false\n");
	fprintf(fp, "\tomega: %lld\n", (long long)omega);

	printVecSint(fp, "function", function);

	printVecSint(fp, "indexDst", indexDst);
	printVecSint(fp, "indexSrc", indexSrc);
	printVecSint(fp, "indexPara", indexPara);
	


}

bool LeafNode::IsConst(const FuncConst& Rvalue) const
{
	LeafType LT;
	LT = (Node::LeafType)Op;
	if (LT != _leafConst_) return false;
	for (size_t i = 0; i < value.count(); i++)
	{
		if (!(value[i] == Rvalue)) return false;
	}
	return true;
}
bool MonoLinear::IsConst(const FuncConst& Rvalue) const
{
	return false;
}
bool DiLinear::IsConst(const FuncConst& Rvalue) const
{
	return false;
}
bool MonoNonlinear::IsConst(const FuncConst& Rvalue) const
{
	return false;
}
bool DiNonlinear::IsConst(const FuncConst& Rvalue) const
{
	return false;
}
void DiLinear::trivial(Node* SrcL, Node* SrcR)
{
	size_t i;
	hyperlex::dictionary* error = NULL;
	clear();
	if (SrcL->descriptor != SrcR->descriptor)
	{
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::trivial");
		error->append("error", "SrcL->descriptor != SrcR->descriptor");
		error->append("SrcL", SrcL->descriptor.GetOrder());
		error->append("SrcR", SrcR->descriptor.GetOrder());
		throw error;
	}
	if (SrcL->network == NULL || SrcL->network != SrcR->network)
	{
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::trivial");
		error->append("error", "SrcL->network == NULL || SrcL->network != SrcR->network");
		throw error;
	}
	Op = OpType::_add_;
	DummyIndex = 0;
	RepeatedIndex = SrcL->descriptor.GetOrder();
	indexDst.recount(RepeatedIndex);
	indexSrcL.recount(RepeatedIndex);
	indexSrcR.recount(RepeatedIndex);
	for (i = 0; i < RepeatedIndex; i++)
	{
		indexDst[i] = (sint)(i + 1);
		indexSrcL[i] = (sint)(i + 1);
		indexSrcR[i] = (sint)(i + 1);
	}
	SrcL->network->NodeAppend(this);
	network->net.ArcAdd(SrcL, SrcR, this);

}

void LeafNode::backward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{

	return;
}
void DiLinear::backward(bool dYdX, vector<Node*>& label, vector<size_t>& H) 
{
	Node::OpType OT;
	OT = (Node::OpType)Op;
	
	switch (OT)
	{
	case Pikachu::Node::_add_:
	case Pikachu::Node::_sub_:
	{
		MonoLinear* diff;
		Node* SrcBack_, * source;
		size_t siteThis, siteSource;
		double Ralpha;
		Ralpha = (OT == _sub_ ? -1.0 : 1.0);
		siteThis = site();
		siteSource = source->site();
		SrcBack_ = label[siteThis];


		diff = new MonoLinear();
		diff->build(indexDst, indexSrcL, H, 1.0);
		diff->setDesc(in[0]->descriptor, H);
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, diff);
		network->BackAcc(in[0]->site(), label, diff);

		diff = new MonoLinear();
		diff->build(indexDst, indexSrcR, H, Ralpha);
		diff->setDesc(in[1]->descriptor, H);
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, diff);
		network->BackAcc(in[1]->site(), label, diff);
		break;
	}
	case Pikachu::Node::_mul_:
	{
		DiLinear* diff;
		Node* SrcBack_;
		size_t siteThis;
		siteThis = site();
		SrcBack_ = label[siteThis];


		diff = new DiLinear(Node::_mul_);
		//diff->build(indexDst, indexSrcL, H, 1.0);
		diff->setDesc(in[0]->descriptor, H);
		diff->value(indexDst, indexSrcR, indexSrcL);
		diff->Happend(true, false, true, H.count());
		diff->build();
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, in[1], diff);
		network->BackAcc(in[0]->site(), label, diff);

		diff = new DiLinear(Node::_mul_);
		//diff->build(indexDst, indexSrcR, H, Ralpha);
		diff->setDesc(in[1]->descriptor, H);
		diff->value(indexDst, indexSrcL, indexSrcR);
		diff->Happend(false, true, true, H.count());
		diff->build();
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, in[0], diff);
		network->BackAcc(in[1]->site(), label, diff);
		break;
	}
	default:
	{
		hyperlex::dictionary* error;
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::backward");
		error->append("error", "switch (OT) unknown type");
		error->append("Op", Op);
		throw error;
		break;
	}
		
	}
}
void DiNonlinear::backward(bool dYdX, vector<Node*>& label, vector<size_t>& H) 
{
	DiNonlinear* func;
	DiLinear* diff;
	Node* SrcBack_;
	size_t siteThis;
	siteThis = site();
	SrcBack_ = label[siteThis];

	func = differential(true);
	diff = new DiLinear();
	diff->setDesc(in[0]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexSrc);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(in[0]->site(), label, diff);

	func = differential(false);
	diff = new DiLinear();
	diff->setDesc(in[1]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexPara);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(in[1]->site(), label, diff);

}
void MonoLinear::backward(bool dYdX, vector<Node*>& label, vector<size_t>& H) 
{
	MonoLinear* diff;
	Node* SrcBack_, *source;
	size_t siteThis, siteSource;
	siteThis = site();
	source = in[0];
	siteSource = source->site();
	SrcBack_ = label[siteThis];


	diff = new MonoLinear();
	diff->build(indexDst, indexSrc, H, alpha);
	diff->setDesc(source->descriptor, H);


	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, diff);
	network->BackAcc(siteSource, label, diff);

	return;
}
void MonoNonlinear::backward(bool dYdX, vector<Node*>& label, vector<size_t>& H) 
{
	MonoNonlinear* func;
	func = differential();

	DiLinear* diff;
	Node* SrcBack_;
	size_t siteThis;
	siteThis = site();
	SrcBack_ = label[siteThis];


	diff = new DiLinear(Node::_mul_);
	//diff->build(indexDst, indexSrcL, H, 1.0);
	diff->setDesc(in[0]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexSrc);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(in[0]->site(), label, diff);
	return;
}


void LeafNode::forward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{

}
void MonoLinear::forward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{
	MonoLinear* diff;
	Node* SrcForward_, * source;
	size_t siteThis, siteSource;
	siteThis = site();
	source = in[0];
	siteSource = source->site();
	SrcForward_ = label[siteSource];


	diff = new MonoLinear();
	diff->build(indexSrc, indexDst, H, alpha);
	diff->setDesc(descriptor, H);


	network->NodeAppend(diff);
	network->net.ArcAdd(SrcForward_, diff);
	label[siteThis] = diff;

	return;
}
void DiLinear::forward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{
	Node::OpType OT;
	OT = (Node::OpType)Op;

	switch (OT)
	{
	case Pikachu::Node::_add_:
	case Pikachu::Node::_sub_:
	{
		DiLinear* diff;
		size_t siteL, siteR;
		size_t siteThis;
		siteL = in[0]->site();
		siteR = in[1]->site();
		siteThis = site();


		diff = new DiLinear(Node::_mul_);
		//diff->build(indexDst, indexSrcL, H, 1.0);
		diff->setDesc(descriptor, H);
		diff->value(indexDst, indexSrcR, indexSrcL);
		diff->Happend(true, true, true, H.count());
		diff->build();
		network->NodeAppend(diff);
		network->net.ArcAdd(label[siteL], label[siteR], diff);
		label[siteThis] = diff;
		break;
	}
	case Pikachu::Node::_mul_:
	{
		DiLinear* diffL, * diffR, *sum;
		size_t siteL, siteR;
		size_t siteThis;
		siteL = in[0]->site();
		siteR = in[1]->site();
		siteThis = site();


		diffL = new DiLinear(Node::_mul_);
		diffL->setDesc(descriptor, H);
		diffL->value(indexSrcL, indexSrcR, indexDst);
		diffL->Happend(true, false, true, H.count());
		diffL->build();
		network->NodeAppend(diffL);
		network->net.ArcAdd(label[siteL], in[1], diffL);

		diffR = new DiLinear(Node::_mul_);
		diffR->setDesc(descriptor, H);
		diffR->value(indexSrcL, indexSrcR, indexDst);
		diffR->Happend(false, true, true, H.count());
		diffR->build();
		network->NodeAppend(diffR);
		network->net.ArcAdd(in[0], label[siteR], diffR);

		sum = new DiLinear();
		sum->trivial(diffL, diffR);
		label[siteThis] = sum;
		break;
	}
	default:
	{
		hyperlex::dictionary* error;
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::backward");
		error->append("error", "switch (OT) unknown type");
		error->append("Op", Op);
		throw error;
		break;
	}

	}
}
void MonoNonlinear::forward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{
	MonoNonlinear* func;
	func = differential();

	DiLinear* diff;
	Node* sourceF;
	size_t siteThis;
	siteThis = site();
	sourceF = label[siteThis];


	diff = new DiLinear(Node::_mul_);
	diff->setDesc(descriptor, H);
	diff->value(indexSrc, func->indexDst, indexDst);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(sourceF, func, diff);
	label[siteThis] = diff;
}
void DiNonlinear::forward(bool dYdX, vector<Node*>& label, vector<size_t>& H)
{
	DiLinear* diffL, * diffR, * sum;
	DiNonlinear* funcX, *funcP;
	size_t siteL, siteR;
	size_t siteThis;
	siteL = in[0]->site();
	siteR = in[1]->site();
	siteThis = site();

	funcX = differential(true);
	funcP = differential(false);
	//左右反了
	diffL = new DiLinear(Node::_mul_);
	diffL->setDesc(descriptor, H);
	diffL->value(funcX->indexDst, indexSrc, indexDst);
	diffL->Happend(false, true, true, H.count());
	diffL->build();
	network->NodeAppend(diffL);
	network->net.ArcAdd(funcX, label[siteL], diffL);

	diffR = new DiLinear(Node::_mul_);
	diffR->setDesc(descriptor, H);
	diffR->value(funcP->indexDst, indexPara, indexDst);
	diffR->Happend(false, true, true, H.count());
	diffR->build();
	network->NodeAppend(diffR);
	network->net.ArcAdd(funcP, label[siteR], diffR);

	sum = new DiLinear();
	sum->trivial(diffL, diffR);
	label[siteThis] = sum;
}



void LeafNode::Initial(const Tensor& desc, vector<size_t>& H)
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
		H.recount(0);
	}
	else if (desc.GetOrder() == 1 && desc[0] == 1)
	{
		descriptor.Set(desc);
		value.append(one_);
		H.recount(0);
	}
	else
	{
		descriptor.clear();
		H.recount(desc.GetOrder());
		for (i = 0; i < desc.GetOrder(); i++)
		{
			H[i] = desc[i];
			descriptor.append(desc[i]);
		}
		for (i = 0; i < desc.GetOrder(); i++) descriptor.append(desc[i]);
		L = desc.GetCount();
		value.recount(descriptor.GetCount());
		for (i = 0; i < value.count(); i++)
			value[i].SetValue((long long)0);
		for (i = 0; i < L; i++)
			value[i * L + i].SetValue((long long)1);
	}
	return;
}



void MonoLinear::inforPrint(hyperlex::dictionary& dict)const
{
	dict.append("alpha", alpha);
	dict.append("DummyIndex", DummyIndex);
	dict.append("NewIndex", NewIndex);
	dict.append("RepeatedIndex", RepeatedIndex);
	for (size_t i = 0; i < indexDst.count(); i++)
		dict.append("indexDst", (long int)indexDst[i]);
	for (size_t i = 0; i < indexSrc.count(); i++)
		dict.append("indexSrcL", (long int)indexSrc[i]);
}
hyperlex::dictionary* MonoLinear::ErrorGive(void) const
{
	hyperlex::dictionary* error;
	error = new  hyperlex::dictionary;
	inforPrint(*error);
	return error;
}
void MonoLinear::build(const vector<sint>& Src, const vector<sint>& Dst, double Alpha)
{
	sint max;
	size_t i;
	clear();
	max = Src[0];
	indexDst.recount(Dst.count());
	indexSrc.recount(Src.count());
	for (i = 0; i < Src.count(); i++)
	{
		max = max > Src[i] ? max : Src[i];
		indexSrc[i] = Src[i];
	}
	for (i = 0; i < Dst.count(); i++)
	{
		max = max > Dst[i] ? max : Dst[i];
		indexDst[i] = Dst[i];
	}
	DummyIndex = 0;
	NewIndex = 0;
	RepeatedIndex = 0;
	for (i = 0; i < indexSrc.count(); i++)
	{
		sint temp = indexSrc[i];
		size_t site = indexDst.search(temp);
		if (site == _uintMax_) NewIndex += 1;
		else RepeatedIndex += 1;
	}
	for (i = 0; i < indexDst.count(); i++)
	{
		sint temp = indexDst[i];
		size_t site = indexSrc.search(temp);
		if (site == _uintMax_) DummyIndex += 1;
	}
}
void MonoLinear::build(const vector<sint>& Src, const vector<sint>& Dst, const vector<size_t>& H, double Alpha)
{
	sint max;
	size_t i;
	clear();
	max = Src[0]; 
	indexDst.recount(Dst.count() + H.count());
	indexSrc.recount(Src.count() + H.count());
	for (i = 0; i < Src.count(); i++)
	{
		max = max > Src[i] ? max : Src[i];
		indexSrc[i] = Src[i];
	}
	for (i = 0; i < Dst.count(); i++)
	{
		max = max > Dst[i] ? max : Dst[i];
		indexDst[i] = Dst[i];
	}

	for (i = 0; i < H.count(); i++)
	{
		indexSrc[i + Src.count()] = (sint)(max + i + 1);
		indexDst[i + Dst.count()] = (sint)(max + i + 1);
	}
	DummyIndex = 0;
	NewIndex = 0;
	RepeatedIndex = 0;
	for (i = 0; i < indexSrc.count(); i++)
	{
		sint temp = indexSrc[i];
		size_t site = indexDst.search(temp);
		if (site == _uintMax_) NewIndex += 1;
		else RepeatedIndex += 1;
	}
	for (i = 0; i < indexDst.count(); i++)
	{
		sint temp = indexDst[i];
		size_t site = indexSrc.search(temp);
		if (site == _uintMax_) DummyIndex += 1;
	}
}



void DiLinear::value(const vector<sint>& SrcL, const vector<sint>& SrcR, const vector<sint>& Dst)
{
	indexSrcL.copy(SrcL);
	indexSrcR.copy(SrcR);
	indexDst.copy(Dst);
	return;
}
void DiLinear::build(void)
{
	DummyIndex = 0;
	RepeatedIndex = 0;
	size_t countL, countR, count;
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		countL = indexSrcL.Tcount(indexDst[i]);
		countR = indexSrcR.Tcount(indexDst[i]);
		count = countL + countR;
		if (countL > 1L || countR > 1L)
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "DiLinear::build");
			error->append("error", "countL > 1L || countR > 1L");
			error->append("countL", countL);
			error->append("countR", countR);
			error->append("i", i);
			throw error;
		}
		if (count == 2) RepeatedIndex += 1;
	}
	count = 0;
	for (size_t i = 0; i < indexSrcL.count(); i++)
	{
		countL = indexDst.Tcount(indexSrcL[i]);
		if (countL > 1L)
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "DiLinear::build");
			error->append("error", "countL > 1L");
			error->append("countL", countL);
			throw error;
		}
		if (countL == 1) count += 1;
	}

	DummyIndex = RepeatedIndex - count;
}
sint DiLinear::MaxIndex(void) const
{
	size_t i;
	sint temp;
	temp = indexSrcL[0];
	for (i = 0; i < indexSrcL.count(); i++)
	{
		temp = (temp > indexSrcL[i] ? temp : indexSrcL[i]);
	}
	for (i = 0; i < indexSrcR.count(); i++)
	{
		temp = (temp > indexSrcR[i] ? temp : indexSrcR[i]);
	}
	for (i = 0; i < indexDst.count(); i++)
	{
		temp = (temp > indexDst[i] ? temp : indexDst[i]);
	}

	return temp;
}
void DiLinear::Happend(bool L, bool R, bool D, size_t H)
{
	sint temp, delta;
	temp = MaxIndex();
	delta = temp + 1;
	for (size_t i = 0; i < H; i++)
	{
		if (L) indexSrcL.append(delta);
		if (R) indexSrcR.append(delta);
		if (D) indexDst.append(delta);
		delta += 1;
	}
	return;
}
void DiLinear::inforPrint(hyperlex::dictionary& dict)const
{
	dict.append("DummyIndex", DummyIndex);
	dict.append("RepeatedIndex", RepeatedIndex);
	for (size_t i = 0; i < indexDst.count(); i++)
		dict.append("indexDst", (long int)indexDst[i]);
	for (size_t i = 0; i < indexSrcL.count(); i++)
		dict.append("indexSrcL", (long int)indexSrcL[i]);
	for (size_t i = 0; i < indexSrcR.count(); i++)
		dict.append("indexSrcR", (long int)indexSrcR[i]);
}
hyperlex::dictionary* DiLinear::ErrorGive(void) const
{
	hyperlex::dictionary* error;
	error = new  hyperlex::dictionary;
	inforPrint(*error);
	return error;
}



void MonoNonlinear::inforPrint(hyperlex::dictionary& dict)const
{
	dict.append("ScalarInput", ScalarInput);
	dict.append("x", x);
	
}
hyperlex::dictionary* MonoNonlinear::ErrorGive(void) const
{
	hyperlex::dictionary* error;
	error = new  hyperlex::dictionary;
	inforPrint(*error);
	return error;
}
sint MonoNonlinear::MaxIndex(void) const
{
	size_t i;
	sint temp;
	temp = 0;
	for (i = 0; i < indexSrc.count(); i++)
	{
		temp = (temp > indexSrc[i] ? temp : indexSrc[i]);
	}
	for (i = 0; i < function.count(); i++)
	{
		temp = (temp > function[i] ? temp : function[i]);
	}
	for (i = 0; i < indexDst.count(); i++)
	{
		temp = (temp > indexDst[i] ? temp : indexDst[i]);
	}
	if (ScalarInput)
	{
		temp = (temp > x ? temp : x);
	}
	return temp;
}
MonoNonlinear* MonoNonlinear::differential(void)
{
	MonoNonlinear* diff;

	if (gradient != NULL) return gradient;
	diff = new MonoNonlinear;
	diff->x = x;
	diff->ScalarInput = ScalarInput;

	diff->function.copy(function);
	diff->indexSrc.copy(indexSrc);
	diff->indexDst.copy(indexDst);

	diff->descriptor.Set(descriptor);
	diff->funcTensor.Set(funcTensor);
	if (!ScalarInput)
	{
		size_t site = diff->indexSrc.search(x);
		if (site == _uintMax_)
		{
			hyperlex::dictionary* error = ErrorGive();
			error->append("location", "differential");
			throw error;
		}
		sint index = 1 + MaxIndex();
		size_t dimX;
		dimX = in[0]->descriptor[site];
		diff->function.append(x);
		diff->indexDst.append(x);

		diff->x = index;
		diff->indexSrc[site] = index;
		
		diff->descriptor.append(dimX);
		diff->funcTensor.append(dimX);
	}
	network->NodeAppend(diff);
	network->net.ArcAdd(in[0], diff);
	gradient = diff;
	return diff;
}

sint DiNonlinear::MaxIndex(void) const
{
	size_t i;
	sint temp;
	temp = 0;
	for (i = 0; i < indexSrc.count(); i++)
	{
		temp = (temp > indexSrc[i] ? temp : indexSrc[i]);
	}
	for (i = 0; i < function.count(); i++)
	{
		temp = (temp > function[i] ? temp : function[i]);
	}
	for (i = 0; i < indexDst.count(); i++)
	{
		temp = (temp > indexDst[i] ? temp : indexDst[i]);
	}
	if (ScalarInput)
	{
		temp = (temp > x ? temp : x);
	}
	if (ScalarPara)
	{
		temp = (temp > omega ? temp : omega);
	}
	return temp;
}
DiNonlinear* DiNonlinear::differential(bool X) const
{
	DiNonlinear* diff;
	diff = new DiNonlinear;
	diff->ScalarInput = ScalarInput;
	diff->x = x;
	diff->ScalarPara = ScalarPara;
	diff->omega = omega;

	diff->function.copy(function);
	
	diff->indexDst.copy(indexDst);
	diff->indexSrc.copy(indexSrc);
	diff->indexPara.copy(indexPara);

	diff->descriptor.Set(descriptor);
	diff->funcTensor.Set(funcTensor);
	if (X)
	{
		if (!ScalarInput)
		{
			size_t site = diff->indexSrc.search(x);
			if (site == _uintMax_)
			{
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "differential");
				throw error;
			}
			sint index = 1 + MaxIndex();
			size_t dimX;
			dimX = in[0]->descriptor[site];
			diff->function.append(x);
			diff->indexDst.append(x);
			diff->x = index;
			diff->indexSrc[site] = index;
			diff->descriptor.append(dimX);
			diff->funcTensor.append(dimX);
		}
	}
	else
	{
		if (!ScalarPara)
		{
			size_t site = diff->indexPara.search(omega);
			if (site == _uintMax_)
			{
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "differential");
				throw error;
			}
			sint index = 1 + MaxIndex();
			size_t dimX;
			dimX = in[1]->descriptor[site];
			diff->function.append(omega);
			diff->indexDst.append(omega);
			diff->omega = index;
			diff->indexSrc[site] = index;
			diff->descriptor.append(dimX);
			diff->funcTensor.append(dimX);
		}
	}
	
	network->NodeAppend(diff);
	network->net.ArcAdd(in[0], in[1], diff);
}
void DiNonlinear::inforPrint(hyperlex::dictionary& dict)const
{
	dict.append("ScalarInput", ScalarInput);
	dict.append("x", x);
	dict.append("ScalarPara", ScalarPara);
	dict.append("omega", omega);
	for (size_t i = 0; i < function.count(); i++)
		dict.append("function", (long int)function[i]);
	for (size_t i = 0; i < funcTensor.GetOrder(); i++)
		dict.append("funcTensor", (long int)funcTensor[i]);

	for (size_t i = 0; i < indexDst.count(); i++)
		dict.append("indexDst", (long int)indexDst[i]);
	
	for (size_t i = 0; i < indexPara.count(); i++)
		dict.append("indexPara", (long int)indexPara[i]);
}
hyperlex::dictionary* DiNonlinear::ErrorGive(void) const
{
	hyperlex::dictionary* error;
	error = new  hyperlex::dictionary;
	inforPrint(*error);
	return error;
}



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
	if(left) workspace.net.append(original, peer, site);
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
	GraphNode* Src, *Ori;
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







/*
class NeuralNetwork;
class functionNode;//1
class manifoldNode;//1
class computeNode;//3
class distributeNode;
class vainNode;
class fusionNode;//6
class contractionNode;//7
class Vortex
{
public:
	friend class NeuralNetwork;
	friend class contractionNode;
	friend class manifoldNode;
	friend class functionNode;
	friend class distributeNode;
	friend class vainNode;
	friend class computeNode;
	friend class fusionNode;
	Vortex();
	~Vortex();

	enum SourceType
	{
		function = 0,
		conctraction = 1,
		compute = 2,
		fusion = 3,
		distribute = 4,
		vain = 5,
		manifold = 6,

	};
	enum InnerType
	{
		hidden = 0,
		input = 1,
		output = 2,
	};
	virtual void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const = 0;
	void linkage(Vortex* BackSrc);
	size_t GetDim(void) const;
	void SetDim(const tensor& source);
	void SetDim(const Vortex* source);
	bool dimEqual(const Vortex* Src) const;
	bool tensorEqual(const Vortex* Src) const;
	bool tensorEqual(const Vortex* Src, size_t from, size_t upper) const;
protected:
	vector<Vortex*> in;
	vector<Vortex*> out;
	SourceType source;
	InnerType inner;
	tensor descriptor;
	size_t site;
};

class functionNode : public Vortex
{
public:
	functionNode();
	~functionNode();
	enum FuncType
	{
		OneToOne = 0,
		NToOne = 1,
		//MatContraction = 2,
		//TensorContraction = 3,
	};
	enum parameter
	{
		none = 0,
		constant = 1,
		dynamic = 2,
		mixed = 3,
	};
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
private:
	FuncType F;
	parameter P;
	const tensorPara* descC;
	const tensorPara* descD;
	size_t index;
};
class computeNode : public Vortex
{
public:
	friend class functionNode;
	computeNode();
	~computeNode();
	enum CompuType
	{
		_add_ = 0,
		_sub_ = 1,
		_mul_ = 2,
		//division = 3,
	};
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
private:
	CompuType C;
	elementwise desc;
};
class manifoldNode : public Vortex
{
public:
	manifoldNode();
	~manifoldNode();
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
	enum parameter
	{
		none = 0,
		constant = 1,
		dynamic = 2,
		mixed = 3,
	};
private:
	parameter P;
	const tensorPara* descC;
	const tensorPara* descD;
};
class contractionNode : public Vortex
{
public:
	contractionNode();
	~contractionNode();
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
	//
	/*
	 \frac{\partial O^{abc}}{\partial x^{iml}}\frac{\partial x^{iml}}{\partial y^{j}}
	 代表不同数据点的张量维度放在最后，随后是代表输出层维度的各个指标。
	* /
size_t contractDimGet(void) const;
private:
	bool Ifconst;
	const tensorPara* parameter;
	ContractDesc contract;
	//tensor* contractL;
	//tensor* contractR;
	bool ifMat(void)const;
};
class distributeNode : public Vortex
{
public:
	friend class computeNode;
	enum transformType
	{
		_identity_ = 0,
		_condense_ = 1,
		_dispatch_ = 2,
		//cut = 1,
		//DimFusion = 2,
		//transposition = 3,
	};
	distributeNode();
	distributeNode(const transformType TT, double factor);
	~distributeNode();


	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
private:
	transformType transformT;
	double alpha;
	dispatch* DisDesc1;
	condensation* CondenDesc2;
};
class fusionNode : public Vortex
{
public:
	fusionNode();
	~fusionNode();
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;

private:
	size_t FusedDim;
};
class vainNode : public Vortex
{
public:
	vainNode();
	~vainNode();
	void backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const;
	enum VainType
	{
		ConstantT = 0,//a constant tensor
		ConstantC = 1,//a constant tensor with all the elements have the same value
		//viewed as scalar.
		hanging = 2,//input
	};
private:
	VainType VainT;
	double scalar;
	tensor* descC;
};
class NeuralNetwork
{


private:
	size_t StaticParameterCount;
	vector<tensor*> StaticParameter;
	vector<size_t> StaticParameterOffset;
	size_t DynamicParameterCount;
	vector<tensor*> DynamicParameter;
	vector<size_t> DynamicParameterOffset;



	vector<Vortex*> vortex;
	vector<size_t> VortexOffset;
	size_t VortexDim;

	vector<Vortex*> output;
	vector<size_t> OutputOffset;
	vector<tensor*> OutputInfro;
	size_t OutputDim;


	vector<Vortex*> input;
	vector<size_t> InputOffset;
	size_t InputDim;//offset = 0;



	void ParameterOffsetBuild(void);
	void VortexOffsetBuild(void);

	int CheckPartialInput(const tensor& infor)const;
	int GetFunctionAndX(const tensor& infor, size_t& Xoffset, size_t& FuncOffset)const;
	int CriticalPath(vector<size_t>& Critical, size_t Xoffset, size_t FuncOffset) const;
	int SequenceGet(const vector<size_t>& Critical, vector<size_t>& Sequence, vector<size_t>& OutCount, vector<size_t>& FoldPrefix, size_t& TotalNewVortex) const;
	size_t OutputCount(const size_t site, const vector<size_t>& Critical) const;



public:
	NeuralNetwork();
	~NeuralNetwork();

	int InputAccomplished(void);
	//0: NoError
	const char* getInputAccomplishedError(int error);

	int GraphUnfold(const tensor& differential);
	//0: NoError
	const char* getUnfoldError(int error);

	void BFTforward(vector<size_t>& label, buffer<size_t>& queue) const;
	void BFTbackward(vector<size_t>& label, buffer<size_t>& queue) const;
	void TopologicalSorting(vector<size_t>& sequence)const;
	void TopologicalSortingBack(vector<size_t>& sequence)const;

};
Vortex::Vortex()
{
	site = uintMax;
}
Vortex::~Vortex()
{
}
size_t Vortex::GetDim(void) const
{
	return descriptor.GetCount();
}
void Vortex::SetDim(const tensor& source)
{
	descriptor.Set(source);
}
void Vortex::SetDim(const Vortex* source)
{
	SetDim(source->descriptor);
}
bool Vortex::dimEqual(const Vortex* Src)const
{
	return GetDim() == Src->GetDim();
}
bool Vortex::tensorEqual(const Vortex* Src) const
{
	return descriptor == Src->descriptor;
}
bool Vortex::tensorEqual(const Vortex* Src, size_t from, size_t upper) const
{
	return descriptor.Equal(Src->descriptor, from, upper);
}
void Vortex::linkage(Vortex* BackSrc)
{
	in.append(BackSrc);
	BackSrc->out.append(this);
}

functionNode::functionNode()
{
	descC = NULL;
	descD = NULL;
	source = function;
	//in.recount(1);
	//in[0] = NULL;
}
functionNode::~functionNode()
{
	delete descC;
	delete descD;
}
void functionNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{
	computeNode* tempNodes;
	functionNode* Function_;
	if (No != 0) throw PikaError("functionNode::backward", "(No != 0)", 1);
	if (!tensorEqual(BackSrc, 0, descriptor.GetOrder()))
		throw PikaError("contractionNode::backward", "(No != 0)", 1);




	switch (F)
	{
	case Pikachu::functionNode::OneToOne:
	{
		Function_ = new functionNode();
		Function_->F = F;
		Function_->SetDim(descriptor);

		//NewNodes.Realloc(2);
		tempNodes = new computeNode();
		tempNodes->C = computeNode::_mul_;
		tempNodes->SetDim(descriptor);
		tempNodes->linkage(Function_);
		tempNodes->linkage(BackSrc);

		Function_->linkage(in[0]);

		NewNodes[0] = tempNodes;
		NewNodes[1] = Function_;
		break;
	}
	case Pikachu::functionNode::NToOne:
	{
		Function_ = new functionNode();
		Function_->F = F;
		Function_->SetDim(descriptor);

		//NewNodes.Realloc(1);
		NewNodes[0] = Function_;
		Function_->linkage(BackSrc);
		break;
	}
	}

	return;
}

contractionNode::contractionNode()
{
	source = conctraction;
	parameter = NULL;
	//contractL = NULL;
	//contractR = NULL;
}
contractionNode::~contractionNode()
{
	//delete contractL;
	//delete contractR;
}
void contractionNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{
	contractionNode* Function_;
	size_t contractionDim, remaindeDim;
	if (No != 0) throw PikaError("contractionNode::backward", "(No != 0)", 1);
	if (!tensorEqual(BackSrc, 0, descriptor.GetOrder()))
		throw PikaError("contractionNode::backward", "(No != 0)", 1);
	try
	{
		Function_ = new contractionNode();
		Function_->contract.backward(BackSrc->descriptor, contract);
		Function_->descriptor.contraction(*parameter, BackSrc->descriptor, Function_->contract);
		Function_->Ifconst = Ifconst;
		Function_->parameter = parameter;
		Function_->linkage(BackSrc);
	}
	catch (const PikaError& E)
	{
		throw PikaError(E, "contractionNode::backward");
	}
	NewNodes.append(Function_);
}
size_t contractionNode::contractDimGet(void) const
{
	return contract.DummyCount();
}
bool contractionNode::ifMat(void) const
{
	size_t label;
	return ((parameter->GetOrder() == 2) && (contract.DummyCount() == 1));
}


computeNode::computeNode()
{
	source = compute;
	//in.recount(2);
	//in[0] = NULL;
	//in[1] = NULL;
}
computeNode::~computeNode()
{
}
void computeNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{
	distributeNode* _distri_;
	computeNode* _compute_;
	size_t _LR_;
	if (No > 1) throw PikaError("computeNode::backward", "(No > 1)", 1);
	if (!tensorEqual(BackSrc, 0, descriptor.GetOrder()))
		throw PikaError("computeNode::backward", "(No != 0)", 1);
	try
	{
		switch (C)
		{
		case Pikachu::computeNode::_add_:
			_distri_ = new distributeNode(distributeNode::_condense_, 1.0);
			_distri_->CondenDesc2->backward(BackSrc->descriptor, desc, No == 0);
			_distri_->descriptor.Condensation(BackSrc->descriptor, *_distri_->CondenDesc2);
			_distri_->linkage(BackSrc);
			NewNodes.append(_distri_);
			break;
		case Pikachu::computeNode::_sub_:
			_distri_ = new distributeNode(distributeNode::_condense_, (No == 0 ? 1.0 : -1.0));
			_distri_->CondenDesc2->backward(BackSrc->descriptor, desc, No == 0);
			_distri_->descriptor.Condensation(BackSrc->descriptor, *_distri_->CondenDesc2);
			_distri_->linkage(BackSrc);
			NewNodes.append(_distri_);
			break;
		case Pikachu::computeNode::_mul_:
			_compute_ = new computeNode();
			_compute_->C = _mul_;
			_compute_->desc.backward(BackSrc->descriptor, desc, No == 0);
			_LR_ = (No == 0 ? 1 : 0);
			_compute_->descriptor.Elementwise(BackSrc->descriptor, in[_LR_]->descriptor, _compute_->desc);
			_compute_->linkage(BackSrc);
			_compute_->linkage(in[_LR_]);



			_distri_ = new distributeNode(distributeNode::_condense_, 1.0);
			_distri_->CondenDesc2->backward(_compute_->descriptor, desc, No == 0);
			_distri_->descriptor.Condensation(_compute_->descriptor, *_distri_->CondenDesc2);
			_distri_->linkage(_compute_);
			NewNodes.append(_distri_);



			NewNodes.append(_compute_);
			break;
		default:
			throw PikaError("computeNode::backward", "default:", 1);
			break;
		}
	}
	catch (const PikaError& E)
	{
		throw PikaError(E, "computeNode::backward");
	}

}


manifoldNode::manifoldNode()
{
	source = manifold;
	descC = NULL;
	descD = NULL;
}
manifoldNode::~manifoldNode()
{
}
void manifoldNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{

}

distributeNode::distributeNode()
{
	source = distribute;

	DisDesc1 = NULL;
	CondenDesc2 = NULL;

	//in.recount(1);
	//in[0] = NULL;
}
distributeNode::distributeNode(const distributeNode::transformType TT, double factor)
{
	source = distribute;
	DisDesc1 = NULL;
	CondenDesc2 = NULL;

	transformT = TT;
	alpha = factor;

	switch (transformT)
	{
	case Pikachu::distributeNode::_condense_:
		CondenDesc2 = new condensation();
		break;
	case Pikachu::distributeNode::_dispatch_:
		DisDesc1 = new dispatch();
		break;
	}

}
distributeNode::~distributeNode()
{
	delete DisDesc1;
	delete CondenDesc2;
}
void distributeNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{
	distributeNode* _distri_;
	if (No != 0) throw PikaError("distributeNode::backward", "(No != 0)", 1);
	if (!tensorEqual(BackSrc, 0, descriptor.GetOrder()))
		throw PikaError("distributeNode::backward", "(No != 0)", 1);
	try
	{
		switch (transformT)
		{
		case Pikachu::distributeNode::_identity_:
			break;
		case Pikachu::distributeNode::_condense_:
			_distri_ = new distributeNode(_dispatch_, alpha);
			_distri_->DisDesc1->backward(BackSrc->descriptor, *CondenDesc2);
			_distri_->descriptor.Dispatch(BackSrc->descriptor, *_distri_->DisDesc1, in[0]->descriptor);
			_distri_->linkage(BackSrc);
			NewNodes.append(_distri_);
			break;
		case Pikachu::distributeNode::_dispatch_:
			_distri_ = new distributeNode(_condense_, alpha);
			_distri_->CondenDesc2->backward(BackSrc->descriptor, *DisDesc1);
			_distri_->descriptor.Condensation(BackSrc->descriptor, *_distri_->CondenDesc2);
			_distri_->linkage(BackSrc);
			NewNodes.append(_distri_);
			break;
		default:
			throw PikaError("distributeNode::backward", "default:", 1 + transformT);

		}
	}
	catch (const PikaError& E)
	{
		throw PikaError(E, "distributeNode::backward");
	}

}

fusionNode::fusionNode()
{
	source = fusion;
}
fusionNode::~fusionNode()
{

}
void fusionNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{

}


vainNode::vainNode()
{
	source = vain;
	descC = NULL;
}
vainNode::~vainNode()
{

}
void vainNode::backward(size_t No, Vortex* BackSrc, vector<Vortex*>& NewNodes) const
{
	return;
}

*/



