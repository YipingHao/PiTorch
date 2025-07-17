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

	all = this;
}
Node::~Node()
{
	infor = (void*)this;
}

void Node::setDesc(const Tensor& desc)
{
	descriptor.Set(desc);
}
void Node::setDesc(const vector<size_t>& desc)
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


// Node类及子类中新增的demo函数实现（使用indiceIS进行索引转换）

// Node类实现
void Node::Demo(FILE* fp) const 
{
	
	fprintf(fp, "Node: %p\n", this);
	fprintf(fp, "\tAffiliation: ");
	switch (Affi) {
	case unknown: fprintf(fp, "unknown\n"); break;
	case initial: fprintf(fp, "initial\n"); break;
	case dYdX: fprintf(fp, "dYdX\n"); break;
	case dLdW: fprintf(fp, "dLdW\n"); break;
	case Jacobi_: fprintf(fp, "Jacobi_\n"); break;
	case Hdv: fprintf(fp, "Hdv\n"); break;
	default: fprintf(fp, "invalid\n"); break;
	}
	fprintf(fp, "\tType: ");
	switch (Type) {
	case _leaf_: fprintf(fp, "leaf\n"); break;
	case _MonoLinear_: fprintf(fp, "MonoLinear\n"); break;
	case _DiLinear_: fprintf(fp, "DiLinear\n"); break;
	case _MonoNonlinear_: fprintf(fp, "MonoNonlinear\n"); break;
	case _DiNonlinear_: fprintf(fp, "DiNonlinear\n"); break;
	default: fprintf(fp, "invalid\n"); break;
	}
	fprintf(fp, "\tOp: %d\n", Op);
	fprintf(fp, "\tIfOutput: %s\n", IfOutput ? "true" : "false");
	fprintf(fp, "\tDataExpand: %s\n", DataExpand ? "true" : "false");
	fprintf(fp, "\tDescriptor: "); descriptor.demo(fp);
	fprintf(fp, "\tNetwork: %p\n", network);
	vortex<Node>::demo(fp);
}

// 辅助函数：将整数索引向量转换为字符表示
static void printIndices(FILE* fp, const vector<sint>& indices) {
	indiceIS converter;
	vector<sint> indicesCopy = indices;
	converter.appendI(indicesCopy);
	converter.ItoS();

	fprintf(fp, "[");
	for (size_t i = 0; i < converter.Scount(); i++) {
		const vector<char*>& strIndices = converter.S(i);
		for (size_t j = 0; j < strIndices.count(); j++) {
			fprintf(fp, "%s%s", strIndices[j], j < strIndices.count() - 1 ? ", " : "");
		}
	}
	fprintf(fp, "]\n");

}

void LeafNode::demo(FILE* fp) const 
{
	Node::Demo(fp);
	fprintf(fp, "\tLeafType: ");
	switch ((LeafType)Op) {
	case _leafIn_: fprintf(fp, "input\n"); break;
	case _leafPara_: fprintf(fp, "parameter\n"); break;
	case _leafConst_: fprintf(fp, "constant\n"); break;
	default: fprintf(fp, "invalid\n"); break;
	}
	fprintf(fp, "\tValue count: %zu\n", value.count());
	//if (value.count() > 0) {
	//	fprintf(fp, "\tFirst value: "); value[0].demo(fp);
	//}
	fprintf(fp, "\tLabel: %zu\n", Label);
}
void MonoLinear::demo(FILE* fp) const 
{
	Node::Demo(fp);
	fprintf(fp, "\tAlpha: %.16lf\n", alpha);
	fprintf(fp, "\tIndexDst (char): "); printIndices(fp, indexDst);
	fprintf(fp, "\tIndexSrc (char): "); printIndices(fp, indexSrc);
	fprintf(fp, "\tDummyIndex: %zu\n", DummyIndex);
	fprintf(fp, "\tNewIndex: %zu\n", NewIndex);
	fprintf(fp, "\tRepeatedIndex: %zu\n", RepeatedIndex);
}
void DiLinear::demo(FILE* fp) const {
	Node::Demo(fp);
	fprintf(fp, "\tOpType: ");
	switch ((OpType)Op) {
	case _add_: fprintf(fp, "add\n"); break;
	case _sub_: fprintf(fp, "sub\n"); break;
	case _mul_: fprintf(fp, "mul\n"); break;
	default: fprintf(fp, "invalid\n"); break;
	}
	fprintf(fp, "\tIndexDst (char): "); printIndices(fp, indexDst);
	fprintf(fp, "\tIndexSrcL (char): "); printIndices(fp, indexSrcL);
	fprintf(fp, "\tIndexSrcR (char): "); printIndices(fp, indexSrcR);
	fprintf(fp, "\tDummyIndex: %zu\n", DummyIndex);
	fprintf(fp, "\tRepeatedIndex: %zu\n", RepeatedIndex);
}
void MonoNonlinear::demo(FILE* fp) const {
	Node::Demo(fp);
	fprintf(fp, "\tScalarInput: %s\n", ScalarInput ? "true" : "false");
	fprintf(fp, "\tx: %lld\n", (long long)x);
	fprintf(fp, "\tFunction (char): "); printIndices(fp, function);
	fprintf(fp, "\tIndexDst (char): "); printIndices(fp, indexDst);
	fprintf(fp, "\tIndexSrc (char): "); printIndices(fp, indexSrc);
	fprintf(fp, "\tFuncTensor: "); funcTensor.demo(fp);
	//fprintf(fp, "\tFormula: "); formula.demo(fp);
}
void DiNonlinear::demo(FILE* fp) const {
	Node::Demo(fp);
	fprintf(fp, "\tScalarInput: %s\n", ScalarInput ? "true" : "false");
	fprintf(fp, "\tx: %lld\n", (long long)x);
	fprintf(fp, "\tScalarPara: %s\n", ScalarPara ? "true" : "false");
	fprintf(fp, "\tomega: %lld\n", (long long)omega);
	fprintf(fp, "\tFunction (char): "); printIndices(fp, function);
	fprintf(fp, "\tIndexDst (char): "); printIndices(fp, indexDst);
	fprintf(fp, "\tIndexSrc (char): "); printIndices(fp, indexSrc);
	fprintf(fp, "\tIndexPara (char): "); printIndices(fp, indexPara);
	fprintf(fp, "\tFuncTensor: "); funcTensor.demo(fp);
	//fprintf(fp, "\tFormula: "); formula.demo(fp);
}


LeafNode::LeafNode()
{
	Type = _leaf_;
}
LeafNode::LeafNode(NetWork* context, Node::LeafType t, Affiliation AA)
{
	Type = _leaf_;
	Op = (int)t;
	network = context;
	Affi = AA;
}
LeafNode::~LeafNode()
{

}
DiLinear::DiLinear()
{
	Type = _DiLinear_;
}
DiLinear::DiLinear(Node::OpType OT, Affiliation AA)
{
	Type = _DiLinear_;
	Op = (int)OT;
	Affi = AA;
}
DiLinear::~DiLinear()
{
}
DiNonlinear::DiNonlinear()
{
	Type = _DiNonlinear_;

	gradientX = NULL;
	gradientP = NULL;
}
DiNonlinear::DiNonlinear(Affiliation AA)
{
	Type = _DiNonlinear_;

	gradientX = NULL;
	gradientP = NULL;
	Affi = AA;
}
DiNonlinear::~DiNonlinear()
{
}
MonoLinear::MonoLinear()
{
	Type = _MonoLinear_;

}
MonoLinear::MonoLinear(Affiliation AA)
{
	Type = _MonoLinear_;
	Affi = AA;
}
MonoLinear::~MonoLinear()
{
}
MonoNonlinear::MonoNonlinear()
{
	Type = _MonoNonlinear_;

	ScalarInput = true;
	x = -1;
	gradient = NULL;
}
MonoNonlinear::MonoNonlinear(Affiliation AA)
{
	Type = _MonoNonlinear_;

	ScalarInput = true;
	x = -1;

	gradient = NULL;
	Affi = AA;
}
MonoNonlinear::~MonoNonlinear()
{
	NonlinearType NT;
	NT = (NonlinearType)Op;
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
Node* LeafNode::copy(void) const
{
	LeafNode* node;
	node = new LeafNode;
	//node->CopyCore(*this);
	CopyCoreN(*node);
	node->value.copy(value);
	//node->Desc.Set(Desc);
	return node;
}
Node* MonoLinear::copy(void) const
{
	MonoLinear* node;
	node = new MonoLinear();
	CopyCoreN(*node);
	node->alpha = alpha;
	node->indexDst.copy(indexDst);
	node->indexSrc.copy(indexSrc);
	node->DummyIndex = DummyIndex;
	node->NewIndex = NewIndex;
	node->RepeatedIndex = RepeatedIndex;
	return node;
}
Node* DiLinear::copy(void) const
{
	DiLinear* node;
	node = new DiLinear();
	CopyCoreN(*node);
	node->indexDst.copy(indexDst);
	node->indexSrcL.copy(indexSrcL);
	node->indexSrcR.copy(indexSrcR);
	node->DummyIndex = DummyIndex;
	node->RepeatedIndex = RepeatedIndex;
	return node;
}
Node* MonoNonlinear::copy(void) const
{
	MonoNonlinear* node;
	node = new MonoNonlinear();
	CopyCoreN(*node);
	node->funcTensor.copy(funcTensor);
	node->ScalarInput = ScalarInput;
	node->x = x;
	node->function.copy(function);

	node->indexDst.copy(indexDst);
	node->indexSrc.copy(indexSrc);

	node->formula.copy(formula);
	return node;
}
Node* DiNonlinear::copy(void) const
{
	DiNonlinear* node;
	node = new DiNonlinear();
	CopyCoreN(*node);

	node->funcTensor.copy(funcTensor);

	node->ScalarInput = ScalarInput;
	node->x = x;

	node->ScalarPara = ScalarPara;
	node->omega = omega;

	node->function.copy(function);

	node->indexDst.copy(indexDst);
	node->indexSrc.copy(indexSrc);
	node->indexPara.copy(indexPara);

	node->formula.copy(formula);

	


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

/*
compute:
	LeafNode: 直接输出descriptor
	MonoLinear: 根据indexDst和indexSrc计算descriptor
	DiLinear: 根据indexDst, indexSrcL, indexSrcR计算descriptor
	MonoNonlinear: 根据indexDst, indexSrc和function计算descriptor
	DiNonlinear: 根据indexDst, indexSrc, indexPara和function计算descriptor
*/
void LeafNode::compute(Tensor& DescOut)const
{
	DescOut.Set(descriptor);
}
// MonoLinear 节点：根据 indexDst 和 indexSrc 计算输出张量结构
// MonoLinear node: Compute output tensor descriptor according to indexDst and indexSrc
void MonoLinear::compute(Tensor& DescOut)const
{
	// 设置输出张量的阶（维数）为 indexDst 的长度
	// Set the order (rank) of output tensor to the length of indexDst
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		// 查找 indexDst[i] 是否在 indexSrc 中
		// Search if indexDst[i] exists in indexSrc
		size_t site = indexSrc.search(indexDst[i]);
		if (site == _uintMax_)
		{
			// 如果不在 indexSrc，则用自身 descriptor 的第 i 维
			// If not in indexSrc, use the i-th dimension of own descriptor
			DescOut.ChangeDim(i, descriptor[i]);
		}
		else
		{
			// 如果在 indexSrc，则用输入节点 in[0] 的对应维度
			// If in indexSrc, use the corresponding dimension from input node in[0]
			DescOut.ChangeDim(i, in[0]->descriptor[site]);
		}
	}
}
// DiLinear 节点：根据 indexDst, indexSrcL, indexSrcR 计算输出张量结构
// DiLinear node: Compute output tensor descriptor according to indexDst, indexSrcL, indexSrcR
void DiLinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		// 查找 indexDst[i] 是否在左、右输入的指标中
		// Search if indexDst[i] exists in indexSrcL and indexSrcR
		size_t siteL = indexSrcL.search(indexDst[i]);
		size_t siteR = indexSrcR.search(indexDst[i]);
		if (siteL == _uintMax_)
		{
			if (siteR == _uintMax_)
			{
				// 左右都没有，报错
				// Not found in both, throw error
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "DiLinear::compute");
				error->append("error", "missing index");
				throw error;
			}
			else
				DescOut.ChangeDim(i, in[1]->descriptor[siteR]);
			// 只在右输入，取右输入的维度
				// Only in right input, use right input's dimension
		}
		else
		{
			// 在左输入，取左输入的维度
			// In left input, use left input's dimension
			DescOut.ChangeDim(i, in[0]->descriptor[siteL]);
			if (siteR != _uintMax_)
			{
				// 如果左右都出现，必须维度一致，否则报错
				// If appears in both, dimensions must be equal, else throw error
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
// MonoNonlinear 节点：根据 indexDst, indexSrc, function 计算输出张量结构
// MonoNonlinear node: Compute output tensor descriptor according to indexDst, indexSrc, function
void MonoNonlinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		// 查找 indexDst[i] 是否在 indexSrc 和 function 中
		// Search if indexDst[i] exists in indexSrc and function
		size_t siteS = indexSrc.search(indexDst[i]);
		size_t siteF = function.search(indexDst[i]);
		if (siteS == _uintMax_)
		{
			if (siteF == _uintMax_)
			{
				// 两者都没有，报错
				// Not found in both, throw error
				hyperlex::dictionary * error = ErrorGive();
				error->append("location", "MonoNonlinear::compute");
				error->append("error", "missing index");
				throw error;
			}
			else
				DescOut.ChangeDim(i, funcTensor[siteF]);
			// 只在 function，取 funcTensor 的维度
			   // Only in function, use funcTensor's dimension

		}
		else
		{
			// 在 indexSrc，取输入节点的维度
			// In indexSrc, use input node's dimension
			DescOut.ChangeDim(i, in[0]->descriptor[siteS]);
			if (siteF != _uintMax_)
			{
				// 如果 function 也有，报错（重复）
				// If also in function, throw error (repeated index)
				hyperlex::dictionary* error = ErrorGive();
				error->append("location", "MonoNonlinear::compute");
				error->append("error", "repeated index");
				throw error;
			}
		}
	}
}
// DiNonlinear 节点：根据 indexDst, indexSrc, function, indexPara 计算输出张量结构
// DiNonlinear node: Compute output tensor descriptor according to indexDst, indexSrc, function, indexPara
void DiNonlinear::compute(Tensor& DescOut)const
{
	DescOut.ChangeOrder(indexDst.count());
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		// 查找 indexDst[i] 是否在 indexSrc、function、indexPara 中
		// Search if indexDst[i] exists in indexSrc, function, indexPara
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
			// 必须且只能在三者之一出现，否则报错
			// Must appear in exactly one of the three, else throw error
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
void DiLinear::trivial(Node* SrcL, Node* SrcR, Affiliation AA)
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
	Affi = AA;
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

bool LeafNode::IsZero(void) const
{
	LeafType LT;
	LT = (Node::LeafType)Op;
	FuncConst Rvalue;
	Rvalue.SetValue(0LL);
	if (LT != _leafConst_) return false;
	for (size_t i = 0; i < value.count(); i++)
	{
		if (!(value[i] == Rvalue)) return false;
	}
	return true;
}
bool MonoLinear::IsZero(void)  const
{
	return false;
}
bool DiLinear::IsZero(void) const
{
	return false;
}
bool MonoNonlinear::IsZero(void) const
{
	return false;
}
bool DiNonlinear::IsZero(void) const
{
	return false;
}

void LeafNode::backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
{

	return;
}
void DiLinear::backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) 
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


		diff = new MonoLinear(AA);
		diff->build(indexDst, indexSrcL, H, 1.0);
		diff->setDesc(in[0]->descriptor, H);
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, diff);
		network->BackAcc(AA, in[0]->site(), label, diff);

		diff = new MonoLinear(AA);
		diff->build(indexDst, indexSrcR, H, Ralpha);
		diff->setDesc(in[1]->descriptor, H);
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, diff);
		network->BackAcc(AA, in[1]->site(), label, diff);
		break;
	}
	case Pikachu::Node::_mul_:
	{
		DiLinear* diff;
		Node* SrcBack_;
		size_t siteThis;
		siteThis = site();
		SrcBack_ = label[siteThis];


		diff = new DiLinear(Node::_mul_, AA);
		//diff->build(indexDst, indexSrcL, H, 1.0);
		diff->setDesc(in[0]->descriptor, H);
		diff->value(indexDst, indexSrcR, indexSrcL);
		diff->Happend(true, false, true, H.count());
		diff->build();
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, in[1], diff);
		network->BackAcc(AA, in[0]->site(), label, diff);

		diff = new DiLinear(Node::_mul_, AA);
		//diff->build(indexDst, indexSrcR, H, Ralpha);
		diff->setDesc(in[1]->descriptor, H);
		diff->value(indexDst, indexSrcL, indexSrcR);
		diff->Happend(false, true, true, H.count());
		diff->build();
		network->NodeAppend(diff);
		network->net.ArcAdd(SrcBack_, in[0], diff);
		network->BackAcc(AA, in[1]->site(), label, diff);
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
void DiNonlinear::backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) 
{
	DiNonlinear* func;
	DiLinear* diff;
	Node* SrcBack_;
	size_t siteThis;
	siteThis = site();
	SrcBack_ = label[siteThis];

	func = differential(true, AA);
	diff = new DiLinear(Node::_mul_, AA);
	diff->setDesc(in[0]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexSrc);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(AA, in[0]->site(), label, diff);

	func = differential(false, AA);
	diff = new DiLinear(Node::_mul_, AA);
	diff->setDesc(in[1]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexPara);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(AA, in[1]->site(), label, diff);

}
void MonoLinear::backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) 
{
	MonoLinear* diff;
	Node* SrcBack_, *source;
	size_t siteThis, siteSource;
	siteThis = site();
	source = in[0];
	siteSource = source->site();
	SrcBack_ = label[siteThis];


	diff = new MonoLinear(AA);
	diff->build(indexDst, indexSrc, H, alpha);
	diff->setDesc(source->descriptor, H);


	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, diff);
	network->BackAcc(AA, siteSource, label, diff);

	return;
}
void MonoNonlinear::backward(Affiliation AA, vector<Node*>& label, vector<size_t>& H) 
{
	MonoNonlinear* func;
	func = differential(AA);

	DiLinear* diff;
	Node* SrcBack_;
	size_t siteThis;
	siteThis = site();
	SrcBack_ = label[siteThis];


	diff = new DiLinear(Node::_mul_, AA);
	//diff->build(indexDst, indexSrcL, H, 1.0);
	diff->setDesc(in[0]->descriptor, H);
	diff->value(indexDst, func->indexDst, indexSrc);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(SrcBack_, func, diff);
	network->BackAcc(AA, in[0]->site(), label, diff);
	return;
}

void LeafNode::forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
{
	LeafType LT;
	LT = (Node::LeafType)Op;
	LeafNode* diff;
	size_t siteThis;
	siteThis = site();
	if (label[siteThis] != NULL) return;
	diff = new LeafNode(network, Node::_leafConst_, AA);
	diff->setDesc(descriptor, H);
	diff->zero();
	label[siteThis] = diff;
}
void MonoLinear::forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
{
	MonoLinear* diff;
	Node* SrcForward_, * source;
	size_t siteThis, siteSource;
	siteThis = site();
	source = in[0];
	siteSource = source->site();
	SrcForward_ = label[siteSource];


	diff = new MonoLinear(AA);
	diff->build(indexSrc, indexDst, H, alpha);
	diff->setDesc(descriptor, H);


	network->NodeAppend(diff);
	network->net.ArcAdd(SrcForward_, diff);
	label[siteThis] = diff;

	return;
}
void DiLinear::forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
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


		diff = new DiLinear(Node::_mul_, AA);
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


		diffL = new DiLinear(Node::_mul_, AA);
		diffL->setDesc(descriptor, H);
		diffL->value(indexSrcL, indexSrcR, indexDst);
		diffL->Happend(true, false, true, H.count());
		diffL->build();
		network->NodeAppend(diffL);
		network->net.ArcAdd(label[siteL], in[1], diffL);

		diffR = new DiLinear(Node::_mul_, AA);
		diffR->setDesc(descriptor, H);
		diffR->value(indexSrcL, indexSrcR, indexDst);
		diffR->Happend(false, true, true, H.count());
		diffR->build();
		network->NodeAppend(diffR);
		network->net.ArcAdd(in[0], label[siteR], diffR);

		sum = new DiLinear();
		sum->trivial(diffL, diffR, AA);
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
void MonoNonlinear::forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
{
	MonoNonlinear* func;
	func = differential(AA);

	DiLinear* diff;
	Node* sourceF;
	size_t siteThis;
	siteThis = site();
	sourceF = label[siteThis];


	diff = new DiLinear(Node::_mul_, AA);
	diff->setDesc(descriptor, H);
	diff->value(indexSrc, func->indexDst, indexDst);
	diff->Happend(true, false, true, H.count());
	diff->build();
	network->NodeAppend(diff);
	network->net.ArcAdd(sourceF, func, diff);
	label[siteThis] = diff;
}
void DiNonlinear::forward(Affiliation AA, vector<Node*>& label, vector<size_t>& H)
{
	DiLinear* diffL, * diffR, * sum;
	DiNonlinear* funcX, *funcP;
	size_t siteL, siteR;
	size_t siteThis;
	siteL = in[0]->site();
	siteR = in[1]->site();
	siteThis = site();

	funcX = differential(true, AA);
	funcP = differential(false, AA);
	//左右反了
	diffL = new DiLinear(Node::_mul_, AA);
	diffL->setDesc(descriptor, H);
	diffL->value(funcX->indexDst, indexSrc, indexDst);
	diffL->Happend(false, true, true, H.count());
	diffL->build();
	network->NodeAppend(diffL);
	network->net.ArcAdd(funcX, label[siteL], diffL);

	diffR = new DiLinear(Node::_mul_, AA);
	diffR->setDesc(descriptor, H);
	diffR->value(funcP->indexDst, indexPara, indexDst);
	diffR->Happend(false, true, true, H.count());
	diffR->build();
	network->NodeAppend(diffR);
	network->net.ArcAdd(funcP, label[siteR], diffR);

	sum = new DiLinear();
	sum->trivial(diffL, diffR, AA);
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
void LeafNode::zero(void)
{
	size_t L;
	FuncConst zero_;
	//zero_.SetValue((long long)0);
	zero_.SetValue((long long)0);
	Op = (int)_leafConst_;
	L = descriptor.GetCount();
	for (size_t i = 0; i < L; i++)
	{
		value.append(zero_);
	}
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
	alpha = Alpha;
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
	alpha = Alpha;
}
int MonoLinear::build(Node* src, const vector<sint>& Src, const vector<sint>& dummy, const vector<sint>& Dst, double Alpha)
{
	size_t i, j;
	// 1. 检查 src 是否为 NULL
	if (!src) return -1;

	// 2. 检查 Src、dummy、Dst 内部是否有重复
	for (i = 0; i < Src.count(); ++i)
		for (j = i + 1; j < Src.count(); ++j)
			if (Src[i] == Src[j]) return -1;
	for (i = 0; i < dummy.count(); ++i)
		for (j = i + 1; j < dummy.count(); ++j)
			if (dummy[i] == dummy[j]) return -1;
	for (i = 0; i < Dst.count(); ++i)
		for (j = i + 1; j < Dst.count(); ++j)
			if (Dst[i] == Dst[j]) return -1;

	// 3. 检查 src 的阶是否等于 Src.count()
	if (src->descriptor.GetOrder() != Src.count()) return -1;

	// 4. 检查 Src 中的每个指标，要么在 dummy 中，要么在 Dst 中
	for (i = 0; i < Src.count(); ++i)
	{
		bool found = false;
		for (j = 0; j < dummy.count(); ++j)
			if (Src[i] == dummy[j]) { found = true; break; }
		if (!found)
		{
			for (j = 0; j < Dst.count(); ++j)
				if (Src[i] == Dst[j]) { found = true; break; }
		}
		if (!found) return -1;
	}

	// 5. 检查 Dst 中的每个指标不能与 dummy 重复
	for (i = 0; i < Dst.count(); ++i)
		for (j = 0; j < dummy.count(); ++j)
			if (Dst[i] == dummy[j]) return -1;

	// 6. 检查 dummy 中的每个指标必须在 Src 中出现
	for (i = 0; i < dummy.count(); ++i)
	{
		bool found = false;
		for (j = 0; j < Src.count(); ++j)
			if (dummy[i] == Src[j]) { found = true; break; }
		if (!found) return -1;
	}

	// 7. 赋值
	build(Src, Dst, Alpha);

	return 0;
}



void DiLinear::value(const vector<sint>& SrcL, const vector<sint>& SrcR, const vector<sint>& Dst)
{
	indexSrcL.copy(SrcL);
	indexSrcR.copy(SrcR);
	indexDst.copy(Dst);
	return;
}
/**
 * @brief 检查并统计二元线性节点的指标重复与哑指标数量
 *        Check and count repeated and dummy indices for DiLinear node
 *
 * 该函数用于分析 indexDst、indexSrcL、indexSrcR 三组指标的关系，统计
 * - RepeatedIndex: 在左、右输入中都出现且在输出中也出现的“重复指标”数量
 * - DummyIndex: 只在输入中出现、在输出中未出现的“哑指标”数量
 * 并对指标的唯一性做检查，若发现同一指标在同一组中出现多次则抛出异常。
 */
void DiLinear::build(void)
{
	DummyIndex = 0;
	// 虚指标计数器，dummy index counter
	RepeatedIndex = 0;
	// 重复指标计数器，repeated index counter

	// 1. 检查每个指标集内部是否有重复
	// Check for duplicates within each index set
	int errorCode = 0;
	for (size_t i = 0; i < indexDst.count(); ++i)
		for (size_t j = i + 1; j < indexDst.count(); ++j)
			if (indexDst[i] == indexDst[j])
				errorCode |= 1;
	for (size_t i = 0; i < indexSrcL.count(); ++i)
		for (size_t j = i + 1; j < indexSrcL.count(); ++j)
			if (indexSrcL[i] == indexSrcL[j])
				errorCode |= 2;
	for (size_t i = 0; i < indexSrcR.count(); ++i)
		for (size_t j = i + 1; j < indexSrcR.count(); ++j)
			if (indexSrcR[i] == indexSrcR[j])
				errorCode |= 4;
	if (errorCode != 0)
	{
		hyperlex::dictionary* error;
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::build");
		error->append("error", "repeat index");
		error->append("errorCode", errorCode);
		throw error;
	}


	size_t  countL, countR, count;
	// 遍历输出指标 indexDst，检查每个指标在左、右输入中出现的次数
	// For each output index, check its occurrence in left and right input indices
	for (size_t i = 0; i < indexDst.count(); i++)
	{
		countL = indexSrcL.Tcount(indexDst[i]);
		countR = indexSrcR.Tcount(indexDst[i]);
		count = countL + countR;
		// 如果该指标在左、右输入各出现一次，则为“重复指标”
		// If the index appears once in both left and right, it's a repeated index
		if (count == 2) RepeatedIndex += 1;
		// 如果输出指标在输入中都没有，抛出异常
		// If output index not found in any input, throw error
		if (count == 0)
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "DiLinear::build");
			error->append("error", "count == 0");
			throw error;
		}
	}
	count = 0;

	// 3. 统计 DummyIndex
	// 只在输入（indexSrcL 或 indexSrcR）中出现、在输出（indexDst）中未出现的指标
	for (size_t i = 0; i < indexSrcL.count(); ++i)
	{
		countR = indexSrcR.Tcount(indexSrcL[i]);
		if (countR != 0) DummyIndex += 1;
		else
		{
			count = indexDst.Tcount(indexSrcL[i]);
			if (count == 0) {
				// 左输入中有但输出和右输入都没有，非法
				hyperlex::dictionary* error;
				error = new hyperlex::dictionary;
				error->append("location", "DiLinear::build");
				error->append("error", "count == 0");
				throw error;
			}
		}
	}
	DummyIndex -= RepeatedIndex;
	// 4. 左右输入的张量如果不是哑标必须出现在输出中。
	size_t DstShould = indexSrcR.count() + indexSrcL.count();
	DstShould = DstShould - RepeatedIndex - DummyIndex * 2;
	if (DstShould != indexDst.count())
	{
		hyperlex::dictionary* error;
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::build");
		error->append("error", "extra input");
		throw error;
	}
}
void DiLinear::build(const indice_t & dummy)
{
	try
	{
		build();
	}
	catch (hyperlex::dictionary* error)
	{
		throw error;
	}
	// 1. 检查每个dummy集内部是否有重复
	// Check for duplicates within each index set
	int errorCode = 0;
	for (size_t i = 0; i < dummy.count(); ++i)
		for (size_t j = i + 1; j < dummy.count(); ++j)
			if (dummy[i] == dummy[j])
				errorCode |= 1;
	// 2. 检查 dummy 中的每个指标是否在 indexDst 中出现
	for (size_t i = 0; i < dummy.count(); ++i)
	{
		size_t site = indexDst.search(dummy[i]);
		if (site != _uintMax_) errorCode |= 2;
	}
	// 3. 检查 dummy 中的每个指标是否在 indexSrcL 或 indexSrcR 中出现
	for (size_t i = 0; i < dummy.count(); ++i)
	{
		size_t siteL = indexSrcL.search(dummy[i]);
		size_t siteR = indexSrcR.search(dummy[i]);
		if (siteL == _uintMax_ || siteR == _uintMax_) errorCode |= 4;
	}
	if (errorCode != 0)
	{
		hyperlex::dictionary* error;
		error = new hyperlex::dictionary;
		error->append("location", "DiLinear::build(const indice_t & dummy)");
		error->append("error", "repeat index");
		error->append("errorCode", errorCode);
		throw error;
	}
	return;
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
MonoNonlinear* MonoNonlinear::differential(Affiliation AA)
{
	MonoNonlinear* diff;

	if (gradient != NULL) return gradient;
	diff = new MonoNonlinear;
	diff->Affi = AA;
	diff->x = x;
	diff->ScalarInput = ScalarInput;

	diff->function.copy(function);
	diff->indexSrc.copy(indexSrc);
	diff->indexDst.copy(indexDst);

	diff->descriptor.Set(descriptor);
	diff->funcTensor.Set(funcTensor);
	diff->formula.copy(formula);
	diff->formula.differential();
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
		dimX = formula.GetInputDim();
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
int MonoNonlinear::build(const dims_t& dims, Node* srcL, Expres* func, indiceIS& indice)
{
	if (srcL == NULL || func == NULL) return -1;
	//TENSOR TENSORID assign TENSORVALUE semicolon;
	//TENSORID(TensorID funR) SQ_INDEXUNITS(listFunc) left TENSORID(idSrcL) right;
	vector<sint> const& dstI = indice.I(0);//IS.appendS(id.GetSIndex());
	vector<sint> const& funcI = indice.I(1);//IS.appendS(funR.GetSIndex());
	vector<sint> const& listI = indice.I(2);//IS.appendS(listFunc.GetSIndex());
	vector<sint> const& srcLI = indice.I(3);//IS.appendS(idSrcL.GetSIndex());

	formula.build(func);
	ScalarInput = formula.ScalarInput();
	if (1 != listI.count())
	{
		return 2343223; // 错误代码，函数索引维度不匹配
	}
	funcTensor.Set(formula.GetDims());
	if (!ScalarInput) x = listI[0];
	function.copy(funcI);

	indexDst.copy(dstI);
	indexSrc.copy(srcLI);

	return (int)CheckIndice();
}
MonoNonlinear::ErrorInfor MonoNonlinear::CheckIndice(void) const
{
	// 1. 检查 indexSrc、indexDst、function 内部是否有重复
	for (size_t i = 0; i < indexSrc.count(); ++i)
		for (size_t j = i + 1; j < indexSrc.count(); ++j)
			if (indexSrc[i] == indexSrc[j]) return IndexRedundancy;
	for (size_t i = 0; i < indexDst.count(); ++i)
		for (size_t j = i + 1; j < indexDst.count(); ++j)
			if (indexDst[i] == indexDst[j]) return IndexDstRedundancy;
	for (size_t i = 0; i < function.count(); ++i)
		for (size_t j = i + 1; j < function.count(); ++j)
			if (function[i] == function[j]) return FunctionRedundancy;
	// 2. 检查 x 是否在 indexSrc 中不在则报错。是否在indexDst中，在则报错
	if (!ScalarInput)
	{
		size_t site = indexSrc.search(x);
		if (site == _uintMax_) return XNotInIndexSrc; // x 不在 indexSrc 中，报错
		size_t siteDst = indexDst.search(x);
		if (siteDst != _uintMax_) return XInIndexDst; // x 在 indexDst 中，报错
	}
	// 3. 检查 indexDst 中的每个指标是否在 indexSrc 或 function 中
	for (size_t i = 0; i < indexDst.count(); ++i)
	{
		sint temp = indexDst[i];
		size_t siteSrc = indexSrc.search(temp);
		size_t siteFunc = function.search(temp);
		if (siteSrc == _uintMax_ && siteFunc == _uintMax_) return IndexDstNotInIndexSrcOrFunction;
	}
	//4.检查 indexSrc或function中的指标，如果不是x，那么必须在indexDst中
	for (size_t i = 0; i < indexSrc.count(); ++i)
	{
		sint temp = indexSrc[i];
		if (temp == x) continue; // 如果是 x，跳过检查
		size_t siteDst = indexDst.search(temp);
		if (siteDst == _uintMax_) return IndexSrcOrFunctionNotInIndexDst;
	}
	for (size_t i = 0; i < function.count(); ++i)
	{
		sint temp = function[i];
		if (temp == x) continue; // 如果是 x，跳过检查
		size_t siteDst = indexDst.search(temp);
		if (siteDst == _uintMax_) return IndexSrcOrFunctionNotInIndexDst;
	}
	return NoError;
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
DiNonlinear* DiNonlinear::differential(bool X, Affiliation AA)
{
	if (X)
	{
		if (gradientX != NULL) return gradientX;
	}
	else
	{
		if (gradientP != NULL) return gradientP;
	}
	DiNonlinear* diff;
	diff = new DiNonlinear;
	diff->Affi = AA;
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
	diff->formula.copy(formula);
	diff->formula.differential(X);
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
		gradientX = diff;
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
		gradientP = diff;
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
int DiNonlinear::build(const dims_t& dims, Node* srcL, Node* srcR, Expres* func, indiceIS& indice)
{
	if (srcL == NULL || srcR == NULL || func == NULL) return -1;
	//TENSOR TENSORID assign TENSORVALUE semicolon;
	//TENSORID(TensorID funR) SQ_INDEXUNITS(listFunc) left TENSORID(idSrcL) right;
	vector<sint> const& dstI = indice.I(0);//IS.appendS(id.GetSIndex());
	vector<sint> const& funcI = indice.I(1);//IS.appendS(funR.GetSIndex());
	vector<sint> const& listI = indice.I(2);//IS.appendS(listFunc.GetSIndex());
	vector<sint> const& srcLI = indice.I(3);//IS.appendS(idSrcL.GetSIndex());
	vector<sint> const& srcRI = indice.I(4);//IS.appendS(idSrcR.GetSIndex());
	formula.build(func);
	ScalarInput = formula.ScalarInput();
	ScalarPara = formula.ScalarPara();
	if (2 != listI.count())
	{
		return 2343223; // 错误代码，函数索引维度不匹配
	}
	funcTensor.Set(formula.GetDims());
	if (!ScalarInput) x = listI[0];
	if (!ScalarPara) omega = listI[1];
	function.copy(funcI);
	indexDst.copy(dstI);
	indexSrc.copy(srcLI);
	indexPara.copy(srcRI);
	return (int)CheckIndice();
}
DiNonlinear::ErrorInfor DiNonlinear::CheckIndice(void) const
{
	// 1. 检查 indexSrc、indexDst、function, indexPara 内部是否有重复
	for (size_t i = 0; i < indexSrc.count(); ++i)
		for (size_t j = i + 1; j < indexSrc.count(); ++j)
			if (indexSrc[i] == indexSrc[j]) return IndexRedundancy;
	for (size_t i = 0; i < indexDst.count(); ++i)
		for (size_t j = i + 1; j < indexDst.count(); ++j)
			if (indexDst[i] == indexDst[j]) return IndexDstRedundancy;
	for (size_t i = 0; i < function.count(); ++i)
		for (size_t j = i + 1; j < function.count(); ++j)
			if (function[i] == function[j]) return FunctionRedundancy;
	for (size_t i = 0; i < indexPara.count(); ++i)
		for (size_t j = i + 1; j < indexPara.count(); ++j)
			if (indexPara[i] == indexPara[j]) return IndexParaRedundancy;
	// 2. 检查 x 是否在 indexSrc 中不在则报错。是否在indexDst中，在则报错
	if (!ScalarInput)
	{
		size_t site = indexSrc.search(x);
		if (site == _uintMax_) return XNotInIndexSrc; // x 不在 indexSrc 中，报错
		size_t siteDst = indexDst.search(x);
		if (siteDst != _uintMax_) return XInIndexDst; // x 在 indexDst 中，报错
	}
	// 3. 检查 omega 是否在 indexPara 中不在则报错。是否在indexDst中，在则报错
	if (!ScalarPara)
	{
		size_t site = indexPara.search(omega);
		if (site == _uintMax_) return OmegaNotInIndexPara; // omega 不在 indexPara 中，报错
		size_t siteDst = indexDst.search(omega);
		if (siteDst != _uintMax_) return OmegaInIndexDst; // omega 在 indexDst 中，报错
	}
	// 4. 检查 indexDst 中的每个指标是否在 indexSrc 或 function 中
	for (size_t i = 0; i < indexDst.count(); ++i)
	{
		sint temp = indexDst[i];
		size_t siteSrc = indexSrc.search(temp);
		size_t siteFunc = function.search(temp);
		if (siteSrc == _uintMax_ && siteFunc == _uintMax_) return IndexDstNotInIndexSrcOrFunction;
	}
	//5.检查 indexSrc或function中的指标，如果不是x，那么必须在indexDst中
	for (size_t i = 0; i < indexSrc.count(); ++i)
	{
		sint temp = indexSrc[i];
		if (temp == x || temp == omega) continue; // 如果是 x，跳过检查
		size_t siteDst = indexDst.search(temp);
		if (siteDst == _uintMax_) return IndexSrcOrFunctionNotInIndexDst;
	}
	for (size_t i = 0; i < function.count(); ++i)
	{
		sint temp = function[i];
		if (temp == x || temp == omega) continue; // 如果是 x，跳过检查
		size_t siteDst = indexDst.search(temp);
		if (siteDst == _uintMax_) return IndexSrcOrFunctionNotInIndexDst;
	}
	//6.检查x是否等于omega
	if (!ScalarInput && !ScalarPara && x == omega) return XEqualOmega; // x 等于 omega，报错
	
	return NoError;
}


#include<string.h>
Node::LeafType Node::ParseLeafType(const char* input)
{
	if (strcmp(input, "para") == 0) return _leafPara_;
	if (strcmp(input, "input") == 0) return _leafIn_;
	if (strcmp(input, "output") == 0) return _leafConst_;
	if (strcmp(input, "const") == 0) return _leafConst_;
	return _leafConst_;
}
Node::OpType Node::ParseOpType(const char* input)
{
	if (strcmp(input, "+") == 0) return _add_;
	if (strcmp(input, "-") == 0) return _sub_;
	if (strcmp(input, "*") == 0) return _mul_;
	hyperlex::dictionary* error = new hyperlex::dictionary();
	error->append("error", "Unknown operation type");
	error->append("input", input);
	error->append("valid", "+, -, *");
	error->append("location", "Node::ParseOpType");
	throw error;
	return _add_; // 默认返回加法
}


indiceIS::indiceIS()
{
}
indiceIS::~indiceIS()
{
	clearS();
	clearI();
}
/**
 * 清理所有字符串数据
 * 遍历并释放每个字符串占用的内存，然后释放向量本身
 *
 * Clear all string data
 * Iterate through and free memory occupied by each string, then free the vector itself
 */
void indiceIS::clearS(void)
{
	for (size_t i = 0; i < indiceS.count(); ++i)
	{
		vector<char*>* temp = indiceS[i];
		for (size_t j = 0; j < temp->count(); ++j)
		{
			free((*temp)[j]);
		}
		delete temp;
	}
	indiceS.clear();
}
/**
 * 清理所有整数索引数据
 * 遍历并释放每个整数向量占用的内存，然后释放向量本身
 *
 * Clear all integer index data
 * Iterate through and free memory occupied by each integer vector, then free the vector itself
 */
void indiceIS::clearI(void)
{
	for (size_t i = 0; i < indicsI.count(); ++i)
	{
		vector<sint>* temp = indicsI[i];
		delete temp;
	}
	indicsI.clear();
}
/**
 * 将存储的字符串转换为整数索引
 * 使用StringPool将字符串映射到唯一索引（+1以避免零索引）
 *
 * Convert stored strings to integer indices
 * Use StringPool to map strings to unique indices (+1 to avoid zero index)
 */
void indiceIS::StoI(void)
{
	clearI();
	hyperlex::StringPool SP;
	for (size_t i = 0; i < indiceS.count(); ++i)
	{
		vector<char*>* temp = indiceS[i];
		vector<sint>* newI = new vector<sint>();
		newI->recount(temp->count());
		for (size_t j = 0; j < temp->count(); ++j)
		{
			const char* str = (*temp)[j];
			if (str == NULL)
			{
				(*newI)[j] = -1; // 使用 -1 作为特殊标记
			}
			else
			{
				sint index = SP.append(str);
				(*newI)[j] = index + 1; // +1 to avoid zero index
			}
			
		}
		indicsI.append(newI);
	}
}
/**
 * 将存储的索引转换为字符串
 * 使用IndexToString方法将索引转换为字符串表示
 * 注意：此方法不能还原原始字符串，只能生成新的编码
 *
 * Convert stored indices to strings
 * Use IndexToString method to convert indices to string representations
 * Note: This method cannot restore original strings, only generate new encodings
 */
void indiceIS::ItoS(void)
{
	clearS();
	for (size_t i = 0; i < indicsI.count(); ++i)
	{
		vector<sint>* temp = indicsI[i];
		vector<char*>* newS = new vector<char*>();
		newS->recount(temp->count());
		for (size_t j = 0; j < temp->count(); ++j)
		{
			sint index = (*temp)[j] - 1; // -1 to adjust for zero index
			(*newS)[j] = IndexToString(index);
		}
		indiceS.append(newS);
	}
}
/**
 * 演示当前的索引状态
 * 将每个整数索引和字符串索引打印到指定的文件指针
 *
 * Demonstrate the current index state
 * Print each integer index and string index to the specified file pointer
 */
void indiceIS::demo(FILE* fp) const
{
	for (size_t i = 0; i < indicsI.count(); ++i)
	{
		const vector<sint>* temp = indicsI[i];
		fprintf(fp, "Indice I %zu: [", i);
		if (temp->count() > 0)
		{
			fprintf(fp, "%lld", (long long int)(*temp)[0]);
		}
		for (size_t j = 1; j < temp->count(); ++j)
		{
			fprintf(fp, ", %lld", (long long int)(*temp)[j]);
		}
		fprintf(fp, "]\n");
	}
	for (size_t i = 0; i < indiceS.count(); i++)
	{
		vector<char*>* temp = indiceS[i];
		fprintf(fp, "Indice S %zu: [", i);
		if (temp->count() > 0)
		{
			fprintf(fp, "%s", (*temp)[0]);
		}
		for (size_t j = 1; j < temp->count(); ++j)
		{
			fprintf(fp, ", %s", (*temp)[j]);
		}
		fprintf(fp, "]\n");
	}
}
/**
 * 添加字符串组
 * 复制输入的字符串向量到内部存储，为每个字符串分配新内存
 *
 * Add a group of strings
 * Copy the input string vector to internal storage, allocating new memory for each string
 */
void indiceIS::appendS(const vector<char*>& S)
{
	vector<char*>* newS = new vector<char*>();
	newS->recount(S.count());
	for (size_t i = 0; i < S.count(); ++i)
	{
		const char* str = S[i];
		if (str == NULL) {
			(*newS)[i] = NULL; // 处理空字符串
			continue;
		}
		size_t len = strlen(str);
		char* newStr = (char*)malloc((len + 1) * sizeof(char));
		strcpy(newStr, str);
		(*newS)[i] = newStr;
	}
	indiceS.append(newS);
}
/**
 * 添加索引组
 * 复制输入的索引向量到内部存储
 *
 * Add a group of indices
 * Copy the input index vector to internal storage
 */
void indiceIS::appendI(const vector<sint>& I)
{
	vector<sint>* newI = new vector<sint>();
	newI->recount(I.count());
	for (size_t i = 0; i < I.count(); ++i)
	{
		(*newI)[i] = I[i];
	}
	indicsI.append(newI);
}
/**
 * 将数字索引转换为字符串表示
 *
 * 该方法实现了一种特殊的索引到字符串的映射机制：
 * - 小索引（0-25）映射为单个小写字母
 * - 大索引（≥26）映射为"字母+数字"的组合形式
 *
 * 字母表使用自定义顺序（从'i'开始），这可能与特定应用场景或历史编码习惯有关。
 * 注意：此方法不还原原始字符串，仅生成索引的编码表示。
 * 返回的字符串需调用者手动释放内存（通过free()）。
 *
 * @param index 待转换的数字索引（非负整数）
 * @return 指向动态分配的字符串的指针，需手动释放
 *
 * Example:
 *   Index 0 → "i"
 *   Index 1 → "j"
 *   ...
 *   Index 25 → "h"
 *   Index 26 → "i0"
 *   Index 27 → "j0"
 *   Index 52 → "i1"
 *   Index 78 → "i2"
 *
 * Convert numerical index to string representation
 *
 * This method implements a special index-to-string mapping mechanism:
 * - Small indices (0-25) are mapped to single lowercase letters
 * - Large indices (≥26) are mapped to "letter+number" combinations
 *
 * The alphabet uses a custom order (starting from 'i'), which may relate to
 * specific application requirements or historical encoding conventions.
 * Note: This method does not restore the original string, but generates
 * an encoded representation of the index.
 * The returned string must be manually freed by the caller (via free()).
 *
 * @param index The numerical index to convert (non-negative integer)
 * @return Pointer to a dynamically allocated string, must be freed manually
 *
 * Example:
 *   Index 0 → "i"
 *   Index 1 → "j"
 *   ...
 *   Index 25 → "h"
 *   Index 26 → "i0"
 *   Index 27 → "j0"
 *   Index 52 → "i1"
 *   Index 78 → "i2"
 */
char* indiceIS::IndexToString(size_t index)
{
	// 预定义的字母表（26个字母）
	static const char letters[27] = "ijklmnopqrstuvwxyzabcdefgh";

	// 处理小索引（0-25）：单个字母
	if (index < 26) {
		char* str = (char*)(malloc(2 * sizeof(char)));
		str[0] = letters[index];
		str[1] = '\0';
		return str;
	}

	// 处理大索引（≥26）：字母+数字组合
	size_t n = index - 26;
	char letter = letters[n % 26];  // 字母部分
	size_t num_part = n / 26;        // 数字部分

	// 手工计算数字部分的字符串长度
	size_t num_len = 1;
	if (num_part > 0) {
		size_t temp = num_part;
		while (temp != 0) {
			num_len++;
			temp /= 10;
		}
		num_len--;  // 修正循环多计的一次
	}

	// 分配内存：1(字母) + num_len(数字) + 1(结束符)
	char* str = (char*)malloc((num_len + 2) * sizeof(char));
	str[0] = letter;  // 设置首字母

	// 手工转换数字部分（不使用库函数）
	if (num_part == 0) {
		str[1] = '0';
		str[2] = '\0';
	}
	else
	{
		// 从最低位开始填充数字字符
		size_t pos = num_len;
		size_t temp = num_part;
		while (temp != 0) {
			str[pos] = '0' + (temp % 10);  // 取最后一位转为字符
			temp /= 10;
			pos--;
		}
		str[num_len + 1] = '\0';  // 设置结束符
	}

	return str;
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



