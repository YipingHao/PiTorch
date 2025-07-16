#include"../header/Pikachu.h"
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

NetWork::NetWork()
{

}
NetWork::~NetWork()
{
	for (size_t i = 0; i < OutDesc.count(); i++)
	{
		delete OutDesc[i];
	}
}
void NetWork::copy(NetWork& source)
{
	net.copy(source.net);

	vector<Node*> input;
	vector<Node*> parameter;
	vector<Node*> output;

	vector<Node*> gradient;
	vector<Node*> Hv;
}
void NetWork::forward(size_t No)
{
	buffer<Node*> queue;
	size_t length;
	Node* here;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H;
	Node::Affiliation AA = Node::dYdX;
	
	for (size_t i = 0; i < output.count(); i++)
		queue.append(output[i]);
	net.BFTbackward(valid, queue);
	net.TopoSortBFSBack(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		if (here == input[No])
		{
			TempLeaf = new LeafNode(this, Node::_leafConst_, AA);
			TempLeaf->Initial(here->descriptor, H);
			label[input[No]->site()] = TempLeaf;
		}
	}

	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		here->forward(Node::dYdX, label, H);
		if (here->IfOutput)
		{
			Node* Out;
			Tensor* diff;
			size_t hereSite = here->site();
			Out = label[hereSite];
			Out->IfOutput = true;
			output.append(label);
			diff = new Tensor;
			diff->copy(*OutDesc[hereSite]);
			diff->append(No);
			OutDesc.append(diff);
		}
	}

	//simplify();
}
void NetWork::backward(size_t No)
{
	buffer<Node*> queue;
	size_t i, length;
	Node* here, * Out;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H; 
	Node::Affiliation AA = Node::dYdX;


	Out = output[No];
	queue.append(Out);
	net.BFTbackward(valid, queue);
	net.TopoSortBFSBack(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	TempLeaf = new LeafNode(this, Node::_leafConst_, AA);
	TempLeaf->Initial(Out->descriptor, H);
	label[output[No]->site()] = TempLeaf;

	for (i = 0; i < length; i++)
	{
		here = sequence[i];
		here->backward(Node::dYdX, label, H);
		if (here->Type == Node::_leaf_ && here->Op == (int)Node::_leafIn_)
		{
			Node* OutB;
			Tensor* diff;
			size_t hereSite = here->site();
			OutB = label[hereSite];
			if (OutB == NULL)
			{
				hyperlex::dictionary* error;
				error = new hyperlex::dictionary;
				error->append("location", "NetWork::backward");
				error->append("error", "OutB == NULL");
				throw error;
			}
			OutB->IfOutput = true;
			output.append(label);
			diff = new Tensor;
			diff->copy(*OutDesc[hereSite]);
			diff->append(No);
			OutDesc.append(diff);
		}
	}

	//simplify();
}


void NetWork::gradient(void)
{
	buffer<Node*> queue;
	size_t length;
	Node* here, * Out;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H;
	Node::Affiliation AA = Node::dLdW;
	for (size_t i = 0; i < output.count(); i++)
	{
		Out = output[i];
		queue.append(Out);
	}
	
	net.BFTbackward(valid, queue);
	net.TopoSortBFSBack(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	for (size_t i = 0; i < output.count(); i++)
	{
		Out = output[i];
		TempLeaf = new LeafNode(this, Node::_leafIn_, AA);
		TempLeaf->setDesc(Out->descriptor);
		label[output[i]->site()] = TempLeaf;
		BackSrc.append(TempLeaf);
	}
	
	BackOut.recount(parameter.count());
	BackOut.value(NULL);
	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		here->backward(Node::dLdW, label, H);
		if (here->Type == Node::_leaf_ && here->Op == (int)Node::_leafPara_)
		{
			size_t j;
			for (j = 0; j < parameter.count(); j++)
			{
				if(parameter[j] == here)
				{
					BackOut[j] = label[here->site()];
					BackOut[j]->IfOutput = true;
					break;
				}
			}
			if (j == parameter.count())
			{
				hyperlex::dictionary* error;
				error = new hyperlex::dictionary;
				error->append("location", "NetWork::gradient");
				error->append("error", "j == parameter.count()");
				throw error;
			}
			
		}
	}
}
void NetWork::jacobi(void)
{
	buffer<Node*> queue;
	size_t length;
	Node* here, * Out;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H;
	Node::Affiliation AA = Node::Jacobi_;
	for (size_t i = 0; i < output.count(); i++)
	{
		Out = output[i];
		queue.append(Out);
	}

	net.BFTbackward(valid, queue);
	net.TopoSortBFSBack(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	for (size_t i = 0; i < output.count(); i++)
	{
		Out = output[i];
		TempLeaf = new LeafNode(this, Node::_leafIn_, AA);
		TempLeaf->setDesc(Out->descriptor);
		label[output[i]->site()] = TempLeaf;
		JacobiSrc.append(TempLeaf);
	}

	JacobiOut.recount(parameter.count());
	JacobiOut.value(NULL);
	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		here->backward(Node::Jacobi_, label, H);
		if (here->Type == Node::_leaf_ && here->Op == (int)Node::_leafPara_)
		{
			size_t j;
			for (j = 0; j < parameter.count(); j++)
			{
				if (parameter[j] == here)
				{
					JacobiOut[j] = label[here->site()];
					JacobiOut[j]->IfOutput = true;
					break;
				}
			}
			if (j == parameter.count())
			{
				hyperlex::dictionary* error;
				error = new hyperlex::dictionary;
				error->append("location", "NetWork::jacobi");
				error->append("error", "j == parameter.count()");
				throw error;
			}

		}
	}
}
void NetWork::Hv(void)
{
	gradient();
	buffer<Node*> queue;
	size_t length, now, site;
	Node* here;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H;

	for (size_t i = 0; i < BackOut.count(); i++)
		queue.append(BackOut[i]);
	net.BFTbackward(valid, queue);
	net.TopoSortBFSBack(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	HvSrc.recount(parameter.count());
	HvOut.recount(parameter.count());
	HvSrc.value(NULL);
	HvOut.value(NULL);
	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		if (here->Type == Node::_leaf_ && here->Op == (int)Node::_leafPara_)
		{
			size_t j;
			for (j = 0; j < parameter.count(); j++)
			{
				if (parameter[j] == here)
				{
					TempLeaf = new LeafNode(this, Node::_leafIn_, Node::Hdv);
					TempLeaf->setDesc(here->descriptor);
					label[here->site()] = TempLeaf;
					HvSrc[j] = TempLeaf;
					break;
				}
			}
			if (j == parameter.count())
			{
				hyperlex::dictionary* error;
				error = new hyperlex::dictionary;
				error->append("location", "NetWork::Hv");
				error->append("error", "j == parameter.count()");
				throw error;
			}
		}
	}

	for (size_t i = 0; i < length; i++)
	{
		here = sequence[i];
		here->forward(Node::Hdv, label, H);
		if (!here->IfOutput) continue;
		for (size_t j = 0; j < length; j++)
		{
			if (BackOut[j] == here)
			{
				Node* Out;
				size_t hereSite = here->site();
				Out = label[hereSite];
				Out->IfOutput = true;
				HvOut[j] = Out;
				break;
			}

		}
	}

	for (size_t i = 0; i < HvOut.count(); i++)
	{
		if (HvOut[i] == NULL || HvSrc[i] == NULL) 
		{
			hyperlex::dictionary* error;
			error = new hyperlex::dictionary;
			error->append("location", "NetWork::Hv");
			error->append("ParaCount", "HvOut.count()");
			error->append("i", i);
			error->append("error", "HvOut[i] == NULL || HvSrc[i] == NULL");
			throw error;
		}
	}
}


void NetWork::NodeAppend(Node* rear)
{
	rear->network = this;
	net.append(rear);
}

Node* NetWork::NewNodeLeaf(const dims_t& dims, Node::LeafType T)
{
	LeafNode* New = new LeafNode(this, T, Node::initial);
	New->setDesc(dims);
	NodeAppend(New);
	return New;
}
Node* NetWork::NewNodeMonoLinear(const dims_t&dims, Node* src, double factor_, indiceIS& indice)
{
	if (indice.Icount() != 3) return NULL;
	MonoLinear* dst = new MonoLinear(Node::initial);
	int error = dst->build(src, indice.I(0), indice.I(1), indice.I(2), factor_);
	if (error != 0)
	{
		delete dst;
		return NULL;
	}
	net.ArcAdd(src, dst);
	Tensor Desc;
	Desc.Set(dims);
	dst->compute(Desc);
	dst->setDesc(Desc);
	if (Desc != dims)
	{
		delete dst;
		return NULL;
	}
	NodeAppend(dst);
	return dst;
}
Node* NetWork::NewNodeDiLinear(const dims_t& dims, Node* srcL, Node* srcR, Node::OpType OT, indiceIS& indice)
{
	// 检查indice组数
	if (indice.Icount() != 4) return NULL;

	// 创建DiLinear节点，设置操作类型和归属
	DiLinear* dst = new DiLinear(OT, Node::initial);

	// 设置指标
	//IS.appendS(id.GetIndex());
	//IS.appendS(list.GetIndex());
	//IS.appendS(idL.GetIndex());
	//IS.appendS(idR.GetIndex());
	dst->indexSrcL.copy(indice.I(0));
	dst->indexSrcR.copy(indice.I(2));
	dst->indexDst.copy(indice.I(3));
	// 检查指标合法性
	try {
		dst->build();
	}
	catch (hyperlex::dictionary*Err) {
		delete dst;
		throw Err;
		return NULL;
	}

	// 建立网络连接
	net.ArcAdd(srcL, srcR, dst);

	// 计算输出张量结构
	Tensor Desc;
	Desc.Set(dims);
	dst->compute(Desc);
	dst->setDesc(Desc);

	// 校验输出结构
	if (Desc != dims) {
		delete dst;
		return NULL;
	}

	// 添加到网络
	NodeAppend(dst);
	return dst;
}
Node* NetWork::NewNodeMonoNonlinear(const dims_t& dims, Node* srcL, Expres* func, indiceIS& indice)
{
	if (indice.Icount() != 4) return NULL;
	MonoNonlinear* dst = new MonoNonlinear(Node::initial);
	int error = dst->build(dims, srcL, func, indice);
	if (error != 0)
	{
		delete dst;
		return NULL;
	}
	net.ArcAdd(srcL, dst);
	Tensor Desc;
	Desc.Set(dims);
	dst->compute(Desc);
	dst->setDesc(Desc);
	if (Desc != dims)
	{
		delete dst;
		return NULL;
	}
	NodeAppend(dst);
	return dst;
}
Node* NetWork::NewNodeDiNonlinear(const dims_t& dims, Node* srcL, Node* srcR, Expres* func, indiceIS& indice)
{
	if (indice.Icount() != 5) return NULL;
	DiNonlinear* dst = new DiNonlinear(Node::initial);
	int error = dst->build(dims, srcL, srcR, func, indice);
	if (error != 0)
	{
		delete dst;
		return NULL;
	}
	net.ArcAdd(srcL, srcR, dst);
	Tensor Desc;
	Desc.Set(dims);
	dst->compute(Desc);
	dst->setDesc(Desc);
	if (Desc != dims)
	{
		delete dst;
		return NULL;
	}
	NodeAppend(dst);
	return dst;
}

void NetWork::BackAcc(Node::Affiliation AA, size_t target, vector<Node*>& label, Node* source)
{
	Node *SrcL;
	DiLinear* New;
	if (source->network == NULL) NodeAppend(source);
	if (label[target] == NULL)
	{
		label[target] = source;
		return;
	}
	SrcL = label[target];
	New = new DiLinear();
	New->trivial(SrcL, source, AA);
	label[target] = New;
}

bool NetWork::simplify(void)
{
	bool changed_;
	size_t round_;
	round_ = 0;
	do
	{
		round_ += 1;
		changed_ = false;
		changed_ = changed_ || simplify01RedundancyCut();
		changed_ = changed_ || simplify02Zerotensor();
		//changed_ = changed_ || Simplify03();


	} while (changed_);
	//changed_ = changed_ || Simplify05();
	if (round_ > 1)
	{

	}
	return round_ > 1;
}
bool NetWork::simplify01RedundancyCut(void)
{
	bool changed_;
	buffer<Node*> queue;
	Node* here;
	vector<bool> valid;
	changed_ = false;
	queue.clear();
	for (size_t i = 0; i < output.count(); i++)
		queue.append(output[i]);
	for (size_t i = 0; i < BackOut.count(); i++)
		queue.append(BackOut[i]);
	for (size_t i = 0; i < HvOut.count(); i++)
		queue.append(HvOut[i]);
	for (size_t i = 0; i < JacobiOut.count(); i++)
		queue.append(JacobiOut[i]);

	net.BFTbackward(valid, queue);

	for (size_t i = 0; i < net.count(); i++)
	{
		if (net[i] == NULL) continue;
		here = net[i]; 
		if (valid[i])continue;
		if (here->Type != Node::_leaf_)
		{
			net.ruin(i);
			changed_ = true;
		}
		else if ((Node::LeafType)here->Op == Node::_leafConst_)
		{
			net.ruin(i);
			changed_ = true;
		}
	}
	return changed_;
}
bool NetWork::simplify02Zerotensor(void)
{
	bool changed_;
	Node* here;
	changed_ = false;
	for (size_t i = 0; i < net.count(); i++)
	{
		if (net[i] == NULL) continue;
		here = net[i];
		if (here->Type == Node::_leaf_) continue;
		if (here->Type == Node::_MonoLinear_ && here->in[0]->IsZero())
		{
			LeafNode* Zero;
			Zero = new LeafNode(here->network, Node::_leafConst_, here->Affi);
			Zero->setDesc(here->descriptor);
			replace(here, Zero);
		}
		if (here->Type == Node::_DiLinear_)
		{
			bool leftZero = here->in[0]->IsZero();
			bool rightZero = here->in[1]->IsZero();
			if (leftZero || rightZero)
			{
				Node::OpType Op = (Node::OpType)here->Op;
				switch (Op)
				{
				case Pikachu::Node::_add_:
				case Pikachu::Node::_sub_:
				{
					Node* Src = leftZero ? here->in[1] : here->in[0];
					double alpha = leftZero && (Op == Node::_sub_) ? 1.0 : -1.0;
					MonoLinear* NewOne;
					DiLinear* Now = (DiLinear*)here;
					NewOne = new MonoLinear(here->Affi);
					if(leftZero)
						NewOne->build(Now->indexSrcR, Now->indexDst, alpha);
					else 
						NewOne->build(Now->indexSrcL, Now->indexDst, alpha);
					replace(here, NewOne);
					break;
				}
					
				case Pikachu::Node::_mul_:
				{
					LeafNode* Zero;
					Zero = new LeafNode(here->network, Node::_leafConst_, here->Affi);
					Zero->setDesc(here->descriptor);
					replace(here, Zero);
					break;
				}
				default:
					break;
				}
			}
		}
	}
	return changed_;
}

void NetWork::replace(Node* target, Node* source)
{
	net.lift(target, source);
	OutputShift(target, source);
	net.ruin(target->site());
}
void NetWork::OutputShift(Node* target, Node* source)
{
	if (target->IfOutput)
	{
		for (size_t i = 0; i < output.count(); i++)
			if (output[i] == target) output[i] = source;
		for (size_t i = 0; i < BackOut.count(); i++)
			if (BackOut[i] == target) BackOut[i] = source;
		for (size_t i = 0; i < HvOut.count(); i++)
			if (HvOut[i] == target) HvOut[i] = source;
		for (size_t i = 0; i < JacobiOut.count(); i++)
			if (JacobiOut[i] == target) JacobiOut[i] = source;
		target->IfOutput = false;
		source->IfOutput = true;
	}
}

/*
NeuralNetwork::NeuralNetwork()
{
	//input = NULL;
	//input;
}
NeuralNetwork::~NeuralNetwork()
{
	size_t i;
	for (i = 0; i < StaticParameter.count(); i++)
		delete StaticParameter[i];
	for (i = 0; i < DynamicParameter.count(); i++)
		delete DynamicParameter[i];
	for (i = 0; i < vortex.count(); i++)
		delete vortex[i];
}
void NeuralNetwork::ParameterOffsetBuild(void)
{
	size_t offset;
	size_t i;
	offset = 0;
	DynamicParameterOffset.recount(DynamicParameter.count());
	for (i = 0; i < DynamicParameter.count(); i++)
	{
		DynamicParameterOffset[i] = offset;
		offset += DynamicParameter[i]->GetCount();
	}
	DynamicParameterCount = offset;

	if (StaticParameter.count() == 0)return;
	offset = 0;
	StaticParameterOffset.recount(StaticParameter.count());
	for (i = 0; i < StaticParameter.count(); i++)
	{
		StaticParameterOffset[i] = offset;
		offset += StaticParameter[i]->GetCount();
	}
	StaticParameterCount = offset;
}
void NeuralNetwork::VortexOffsetBuild(void)
{
	size_t offset;
	size_t i, j;
	offset = 0;

	VortexOffset.recount(vortex.count());
	for (i = 0; i < vortex.count(); i++)
	{
		for (j = 0; j < output.count(); j++)
			if (output[j] == vortex[i]) break;
		if (j == output.count())
		{
			VortexOffset[i] = offset;
			offset += vortex[i]->GetDim();
		}

	}
	VortexDim = offset;
}


int NeuralNetwork::InputAccomplished(void)
{
	ParameterOffsetBuild();
}
const char* NeuralNetwork::getInputAccomplishedError(int error)
{
	switch (error)
	{
	case 0:
		return "No Error";
	default:
		return "Unknown Type";
	}
}


int NeuralNetwork::GraphUnfold(const tensor& differential)
{
	int errorType;
	
	vector<size_t> Critical;
	vector<size_t> Sequence;
	vector<size_t> FoldPrefix;
	vector<size_t> OutCount;
	size_t Xoffset;
	size_t FuncOffset;
	size_t TotalNewVortex;
	size_t i, outCount__, Site, Prefix;
	int inner(void);



	errorType = CheckPartialInput(differential);
	if (errorType != 0) return errorType;
	errorType = GetFunctionAndX(differential, Xoffset, FuncOffset);
	if (errorType != 0) return errorType;
	errorType = CriticalPath(Critical, Xoffset, FuncOffset);
	if (errorType != 0) return errorType;
	errorType = SequenceGet(Critical, Sequence, OutCount, FoldPrefix, TotalNewVortex);
	if (errorType != 0) return errorType;

	for (i = 0; i < Sequence.count(); i++)
	{
		outCount__ = OutCount[i];
		Site = FoldPrefix[i];
		Prefix = FoldPrefix[i];

	}


	return errorType;
}
int NeuralNetwork::CheckPartialInput(const tensor& infor) const
{
	size_t temp, i;
	tensor former;
	if (infor.GetOrder() <= 1) return 1;
	for (i = 1; i < infor.GetOrder(); i++)
	{
		temp = infor[i];
		if (temp >= input.count()) return 2;
	}
	former.CutLast(infor);
	for (i = 0; i < OutputInfro.count(); i++)
	{
		if (infor == OutputInfro[i][0]) return 3;
	}
	for (i = 0; i < OutputInfro.count(); i++)
	{
		if (former == OutputInfro[i][0]) break;
	}
	if (i == OutputInfro.count()) return 4;
	


	return 0;
}
int NeuralNetwork::GetFunctionAndX(const tensor& infor, size_t& Xoffset, size_t& FuncOffset) const
{
	size_t temp, i;
	tensor former;
	Xoffset = infor[infor.GetOrder() - 1];
	former.CutLast(infor);
	for (i = 0; i < OutputInfro.count(); i++)
	{
		if (former == OutputInfro[i][0]) FuncOffset = i;
	}
	return 0;
}
int NeuralNetwork::CriticalPath(vector<size_t>& Critical, size_t Xoffset, size_t FuncOffset) const
{
	vector<size_t> label1;
	vector<size_t> label2;
	size_t i;
	buffer<size_t> queue;

	queue.append(Xoffset);
	BFTforward(label1, queue);
	if (label1.count() != 0) return 5;
	queue.append(FuncOffset);
	BFTbackward(label2, queue);
	if (label1.count() != 0) return 5;


	Critical.recount(label1.count());
	for (i = 0; i < label1.count(); i++)
	{
		Critical[i] = label1[i] && label2[i];
	}
	return 0;
}
int NeuralNetwork::SequenceGet(const vector<size_t>& Critical, vector<size_t>& Sequence, vector<size_t>& OutCount, vector<size_t>& FoldPrefix, size_t & TotalNewVortex) const
{
	vector<size_t> back;
	size_t i, Site, Count, Prefix;
	TopologicalSortingBack(back);
	Sequence.clear();
	Prefix = 0;
	for (i = 0; i < back.count(); i++)
	{
		Site = back[i];
		if (Critical[Site] != 0)
		{
			Sequence.append(Site);
			Count = OutputCount(Site, Critical);
			OutCount.append(Count);
			FoldPrefix.append(Prefix);
			Prefix += (Count == 0 ? 0 : 2 * Count - 1);
		}
	}
	TotalNewVortex = Prefix;
	return 0;
}
size_t NeuralNetwork::OutputCount(const size_t Site, const vector<size_t>& Critical) const
{
	size_t i, Count, length, temp;
	Vortex* Target;
	Count = 0;
	Target = vortex[Site];
	length = Target->out.count();
	for (i = 0; i < length; i++)
	{
		temp = Target->out[i]->site;
		Count += (Critical[temp] != 0 ? 1 : 0);
	}
	return Count;
}





const char* NeuralNetwork::getUnfoldError(int error)
{
	switch (error)
	{
	case 0:
		return "No Error";
	case 1:
		return "illegal differential Input: It must be a differential formula";
	case 2:
		return "illegal differential Input:independent variable out of range";
	case 3:
		return "The differential already exist!";
	case 4:
		return "There is no precursor differential!";
	case 5:
		return "Critical path error!";
	default:
		return "Unknown Type";
	}
}


void NeuralNetwork::BFTforward(vector<size_t>& label, buffer<size_t> &queue) const
{
	size_t head, i, next;
	Vortex* now;
	label.recount(vortex.count());
	label.value(0);

	while (queue.dequeue(head))
	{
		if (label[head] == 0)
		{
			label[head] = 1;
			now = vortex[head];
			for (i = 0; i < now->out.count(); i++)
			{
				next = now->out[i]->site;
				if(label[next] == 0) queue.append(next);
			}
		}
	}

}
void NeuralNetwork::BFTbackward(vector<size_t>& label, buffer<size_t>& queue) const
{
	size_t head, i, next;
	Vortex* now;
	label.recount(vortex.count());
	label.value(0);
	while (queue.dequeue(head))
	{
		if (label[head] == 0)
		{
			label[head] = 1;
			now = vortex[head];
			for (i = 0; i < now->in.count(); i++)
			{
				next = now->in[i]->site;
				if (label[next] == 0) queue.append(next);
			}
		}
	}
}
void NeuralNetwork::TopologicalSorting(vector<size_t>& sequence)const
{
	vector<size_t> label;
	buffer<size_t> queue;
	size_t head, i, next;
	Vortex* now;
	label.recount(vortex.count());
	sequence.clear();
	for (i = 0; i < vortex.count(); i++)
	{
		label[i] = vortex[i]->in.count();
		if (label[i] == 0) queue.append(i);
	}
	while (queue.dequeue(head))
	{
		sequence.append(head);
		now = vortex[head];
		for (i = 0; i < now->out.count(); i++)
		{
			next = now->out[i]->site;
			if (label[next] == 0)
			{
				
			}
			label[next] -= 1;
			if (label[next] == 0)
			{
				queue.append(next);
			}
		}
	}
}
void NeuralNetwork::TopologicalSortingBack(vector<size_t>& sequence)const
{
	vector<size_t> label;
	buffer<size_t> queue;
	size_t head, i, next;
	Vortex* now;
	label.recount(vortex.count());
	sequence.clear();
	for (i = 0; i < vortex.count(); i++)
	{
		label[i] = vortex[i]->out.count();
		if (label[i] == 0) queue.append(i);
	}
	while (queue.dequeue(head))
	{
		sequence.append(head);
		now = vortex[head];
		for (i = 0; i < now->in.count(); i++)
		{
			next = now->in[i]->site;
#ifdef Debug01
			if (label[next] == 0)
			{
				fprintf(stderr, "Debug01:void NeuralNetwork::TopologicalSortingBack(vector<size_t>& sequence)const\n");
			}
#endif // Debug01

			
			label[next] -= 1;
			if (label[next] == 0)
			{
				queue.append(next);
			}
		}
	}
}
*/





















