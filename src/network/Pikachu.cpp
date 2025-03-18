#include"../header/Pikachu.h"
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

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
	Leaf *TempLeaf;
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
	if(i == net.capacity())
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
	if(theNewOutput != _uintMax_)
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

	if(New->Type != GraphNode::_nonlinear_) New->SetDesc(Left->descriptor, Right->descriptor);
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
		if(label[i])continue;
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





















