#include"../header/Pikachu.h"
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

static void ErrorAdd(const vector<size_t>& infor, const char* name, hyperlex::dictionary* error)
{
	char key[256];
	sprintf(key, "%s_dims", name);
	error->append(key, (long int)infor.count());
	sprintf(key, "%s_infor", name);
	for (size_t i = 0; i < infor.count(); i++)
	{
		error->append(key, (long int)infor[i]);
	}
}

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
void NetWork::copyInfor(vector<Node*>& Dst, const vector<Node*>& Src)
{
	Dst.recount(Src.count());
	for (size_t i = 0; i < Src.count(); i++)
	{
		Node* src = Src[i];
		if (src == NULL)
		{
			Dst[i] = NULL;
			continue;
		}
		size_t site = src->site();
		Node* newNode = net[site];
		if (newNode == NULL)
		{
			hyperlex::dictionary* error = new hyperlex::dictionary;
			error->append("location", "NetWork::copyInfor");
			error->append("error", "newNode == NULL");
			throw error;
		}
		Dst[i] = newNode;
	}
}
void NetWork::copy(NetWork& source)
{
	net.copy(source.net);
	for (size_t i = 0; i < net.count(); i++)
	{
		Node* now = net[i];
		if (now != NULL)
		{
			now->network = this;
		}
	}

	OutDesc.recount(source.OutDesc.count());
	for (size_t i = 0; i < OutDesc.count(); i++)
	{
		Tensor* now = new Tensor;
		now->Set(*source.OutDesc[i]);
		OutDesc[i] = now;
	}

	copyInfor(input, source.input);
	copyInfor(parameter, source.parameter);
	copyInfor(output, source.output);

	
	copyInfor(BackSrc, source.BackSrc);
	copyInfor(BackOut, source.BackOut);
	
	copyInfor(HvSrc, source.HvSrc);
	copyInfor(HvOut, source.HvOut);

	copyInfor(JacobiSrc, source.JacobiSrc);
	copyInfor(JacobiOut, source.JacobiOut);

	//copyInfor(OutDesc, source.OutDesc);
}
void NetWork::forward(size_t No, const vector<size_t>& UpNo, const char* OutputName)
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
	
	for (size_t j = 0; j < UpNo.count(); j++)
	{
		for (size_t i = 0; i < output.count(); i++)
		{
			if (output[i]->site() == UpNo[j])
			{
				queue.append(output[i]);
				break;
			}
		}
	}
	net.BFTbackward(valid, queue);
	net.TopoSortBFS(sequence);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	for (size_t i = 0; i < sequence.count(); i++)
	{
		here = sequence[i];
		if (here->site() == No)
		{
			TempLeaf = new LeafNode(this, Node::_leafConst_, AA);
			TempLeaf->Initial(here->descriptor, H);
			label[No] = TempLeaf;
		}
	}
	size_t InputSite = 0;
	for (size_t i = 0; i < input.count(); i++)
	{
		if (input[i]->site() == No) {
			InputSite = i;
			break;
		}
	}
	for (size_t i = 0; i < sequence.count(); i++)
	{
		here = sequence[i];
		here->forward(Node::dYdX, label, H);
		if (here->IfOutput)
		{
			Node* Out;
			
			size_t hereSite = here->site();
			Out = label[hereSite];
			
			size_t LabelSite = here->site();
			for (size_t j = 0; j < UpNo.count(); j++)
			{
				if (LabelSite == UpNo[j])
				{
					if (OutputName != NULL)
					{
						Tensor* diff;
						Out->SetName(OutputName);
						Out->SetLabel(j);

						Out->IfOutput = true;
						output.append(Out);
						diff = new Tensor;
						diff->copy(*OutDesc[hereSite]);
						diff->append(InputSite);
						OutDesc.append(diff);
					}
					//else
					//{
					//	char name[64];
					//	sprintf(name, "output_%zu", No);
					//	Out->SetName(name);
					//}
					break;
				}
			}
		}
	}
	//新输出的命名规则:传入的OutputName如果不为NULL，则使用它作为输出名称，
	// 标号则为传入的旧的节点的UpNo[j]对应的j。 
	//simplify();
}
void NetWork::backward(size_t No, const vector<size_t>& DownNo, const char* OutputName)
{
	buffer<Node*> queue;
	size_t length;
	Node* here, * Out;
	LeafNode* TempLeaf;
	vector<bool> valid;
	vector<Node*> label;
	vector<Node*> sequence;
	vector<size_t> H; 
	Node::Affiliation AA = Node::dYdX;

	net.TopoSortBFSBack(sequence);

	Out = net[No];
	queue.append(Out);
	net.BFTbackward(valid, queue);
	net.Shrink(valid, sequence);


	queue.clear();
	for (size_t i = 0; i < DownNo.count(); i++)
	{
		for (size_t j = 0; j < input.count(); j++)
		{
			if (input[j]->site() == DownNo[i])
			{
				queue.append(input[j]);
				break;
			}
		}
	}
	net.BFTforward(valid, queue);
	net.Shrink(valid, sequence);

	length = net.count();

	label.recount(length);
	label.value(NULL);

	TempLeaf = new LeafNode(this, Node::_leafConst_, AA);
	TempLeaf->Initial(Out->descriptor, H);
	label[No] = TempLeaf;
	NodeAppend(TempLeaf);

	for (size_t i = 0; i < sequence.count(); i++)
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
			
			size_t LabelSite = here->site();
			for (size_t j = 0; j < DownNo.count(); j++)
			{
				if (LabelSite == DownNo[j])
				{
					if (OutputName != NULL)
					{
						Out->SetName(OutputName);
						Out->SetLabel(j);
						OutB->IfOutput = true;
						output.append(OutB);

						diff = new Tensor;
						diff->copy(*OutDesc[hereSite]);
						diff->append(No);
						OutDesc.append(diff);
					}
					break;
				}
			}

			
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
		NodeAppend(TempLeaf);
		BackSrc.append(TempLeaf);
	}
	
	BackOut.recount(parameter.count());
	BackOut.value(NULL);
	for (size_t i = 0; i < sequence.count(); i++)
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
		NodeAppend(TempLeaf);
		JacobiSrc.append(TempLeaf);
	}

	JacobiOut.recount(parameter.count());
	JacobiOut.value(NULL);
	for (size_t i = 0; i < sequence.count(); i++)
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
	net.TopoSortBFS(sequence);
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
	/*switch (T)
	{
	case Pikachu::Node::_leafIn_:
		input.append(New);
		break;
	case Pikachu::Node::_leafPara_:
		parameter.append(New);
		break;
	case Pikachu::Node::_leafConst_:
		break;
	default:
		break;
	}*/
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
	//IS.appendS(id.GetIndex());[0]
	//IS.appendS(list.GetIndex());[1]
	//IS.appendS(idL.GetIndex());[2]
	//IS.appendS(idR.GetIndex());[3]
	indice_t dummy;
	dst->indexDst.copy(indice.I(0));
	dummy.copy(indice.I(1));
	dst->indexSrcL.copy(indice.I(2));
	dst->indexSrcR.copy(indice.I(3));
	
	// 检查指标合法性
	try {
		dst->build(dummy);
	}
	catch (hyperlex::dictionary*Err) {
		delete dst;
		throw Err;
		return NULL;
	}

	// 建立网络连接
	NodeAppend(dst);
	net.ArcAdd(srcL, srcR, dst);

	// 计算输出张量结构
	Tensor Desc;
	Desc.Set(dims);
	dst->compute(Desc);
	dst->setDesc(Desc);

	// 校验输出结构
	if (Desc != dims) {
		net.ruin(dst->site());
		hyperlex::dictionary* error = new hyperlex::dictionary;
		error->append("location", "NewNodeDiNonlinear");
		error->append("error", "Desc != dims");
		ErrorAdd(dims, "dims", error);
		ErrorAdd(Desc, "Desc", error);
		throw error;
		return NULL;
	}

	// 添加到网络
	
	return dst;
}
Node* NetWork::NewNodeMonoNonlinear(const dims_t& dims, Node* srcL, Expres* func, indiceIS& indice)
{
	if (indice.Icount() != 4) return NULL;
	vector<sint> const& funcI = indice.I(1);//IS.appendS(funR.GetSIndex());
	vector<sint> const& listI = indice.I(2);//IS.appendS(listFunc.GetSIndex());
	if (funcI.count() > 1 && listI.count() > 1)
	{
		hyperlex::dictionary* error = new hyperlex::dictionary;
		error->append("location", "NewNodeMonoNonlinear");
		error->append("funcICount", funcI.count());
		error->append("listICount", listI.count());
		error->append("error", "(funcI.count() > 1 && listI.count() > 1)");
		throw error;
	}
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
		hyperlex::dictionary* error = new hyperlex::dictionary;
		error->append("location", "NewNodeMonoNonlinear");
		error->append("error", "Desc != dims");
		ErrorAdd(dims, "dims", error);
		ErrorAdd(Desc, "Desc", error);
		throw error;
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
		hyperlex::dictionary* error = new hyperlex::dictionary;
		error->append("location", "NewNodeDiNonlinear");
		error->append("error", "Desc != dims");
		ErrorAdd(dims, "dims", error);
		ErrorAdd(Desc, "Desc", error);
		throw error;
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

void NetWork::AppendOutput(Node* out)
{
	output.append(out);
	out->IfOutput = true;
}


/*
		bool checkName(const char* name);//检查所有的输出与叶子节点名称是否与给定名称相同
		Node* CheckNameOutput(const char* name, size_t Label);
		//检查所有的输出节点名称与标签是否与给定名称与标签相同，如果相同返回对应节点
		//否则返回NULL
		Node* CheckNameInput(const char* name, size_t Label);
		//检查所有的叶子Input类型节点名称与标签是否与给定名称与标签相同，如果相同返回对应节点
		//否则返回NULL
*/

bool NetWork::checkName(const char* name)
{
	for (size_t i = 0; i < output.count(); i++)
	{
		if (output[i]->CompareName(name)) true;
	}
	for (size_t i = 0; i < input.count(); i++)
	{
		if (input[i]->CompareName(name)) return true;
	}
	for (size_t i = 0; i < parameter.count(); i++)
	{
		if (parameter[i]->CompareName(name)) return true;
	}
	return false;
}
Node* NetWork::CheckNameOutput(const char* name, size_t Label)
{
	for (size_t i = 0; i < output.count(); i++)
	{
		if (output[i]->CompareName(name) && output[i]->NameLabel == Label) return output[i];
	}
	return NULL;
}
Node* NetWork::CheckNameInput(const char* name, size_t Label)
{
	for (size_t i = 0; i < input.count(); i++)
	{
		if (input[i]->CompareName(name) && input[i]->NameLabel == Label) return input[i];
	}
	return NULL;
}	


void NetWork::OutputNameSearch(const vector<const char*>& name, const vector<size_t>& index, vector<size_t>& No) const
{
	for (size_t i = 0; i < name.count(); i++)
	{
		Node* target = NULL;
		for (size_t j = 0; j < output.count(); j++)
		{
			if (output[j]->CompareName(name[i]) && output[j]->NameLabel == index[i])
			{
				target = output[j];
				break;
			}
		}
		if (target != NULL)
		{
			No.append(target->site());
		}
		else
		{
			hyperlex::dictionary* error = new hyperlex::dictionary;
			error->append("location", "NetWork::OutputNameSearch");
			error->append("error", "target == NULL");
			error->append("name", name[i]);
			error->append("index", index[i]);
			throw error;
		}
	}
}
void NetWork::InputNameSearch(const vector<const char*>& name, const vector<size_t>& index, vector<size_t>& No) const
{
	for (size_t i = 0; i < name.count(); i++)
	{
		Node* target = NULL;
		for (size_t j = 0; j < input.count(); j++)
		{
			if (input[j]->CompareName(name[i]) && input[j]->NameLabel == index[i])
			{
				target = input[j];
				break;
			}
		}
		if (target != NULL)
		{
			No.append(target->site());
		}
		else
		{
			hyperlex::dictionary* error = new hyperlex::dictionary;
			error->append("location", "NetWork::InputNameSearch");
			error->append("error", "target == NULL");
			error->append("name", name[i]);
			error->append("index", index[i]);
			throw error;
		}
	}
}









// NetWork类的demo方法实现
// Implementation of NetWork::demo with indentation and English output

void Pikachu::NetWork::demo(FILE* fp)
{
	demo(0, fp);
}
void NetWork::demo(size_t tabs, FILE* fp, const vector<Node*>& listT, const char* Tinfor)
{
	for (size_t i = 0; i < tabs + 1; ++i) fprintf(fp, "\t");
	fprintf(fp, "%s[%zu]:\n", Tinfor, listT.count());
	for (size_t i = 0; i < listT.count(); ++i)
	{
		for (size_t j = 0; j < tabs + 2; ++j) fprintf(fp, "\t");
		if (listT[i])
			listT[i]->PrintConcise(fp);
		else
			fprintf(fp, "NULL\n");
	}
}
void Pikachu::NetWork::demo(size_t tabs, FILE* fp)
{

	// 打印输入节点
	demo(tabs, fp, input, "Inputs");

	// 打印参数节点
	demo(tabs, fp, parameter, "Parameters");

	// 打印输出节点
	demo(tabs, fp, output, "Outputs");

	// 输出张量描述
	for (size_t i = 0; i < tabs + 1; ++i) fprintf(fp, "\t");
	fprintf(fp, "Output Descriptors[%zu]:\n", OutDesc.count());
	for (size_t i = 0; i < OutDesc.count(); ++i) {
		for (size_t j = 0; j < tabs + 2; ++j) fprintf(fp, "\t");
		if (OutDesc[i])
			OutDesc[i]->demo(fp);
		else
			fprintf(fp, "NULL");
		fprintf(fp, "\n");
	}

	// 梯度相关
	demo(tabs, fp, BackSrc, "Gradient Source Nodes (BackSrc)");
	demo(tabs, fp, BackOut, "Gradient Output Nodes (BackOut)");

	// Hessian相关
	demo(tabs, fp, HvSrc, "Hessian Source Nodes (HvSrc)");
	demo(tabs, fp, HvOut, "Hessian Output Nodes (HvOut)");

	// Jacobi相关
	demo(tabs, fp, JacobiSrc, "Jacobi Source Nodes (JacobiSrc)");
	demo(tabs, fp, JacobiOut, "Jacobi Output Nodes (JacobiOut)");

	// Print all nodes in graph
	for (size_t i = 0; i < tabs + 1; ++i) fprintf(fp, "\t");
	fprintf(fp, "All Nodes[%zu]:\n", net.count());
	for (size_t i = 0; i < net.count(); ++i)
	{
		if (net[i])
		{
			size_t Tabs = tabs + 2;
			for (size_t j = 0; j < Tabs; ++j) fprintf(fp, "\t");
			fprintf(fp, "Nodes[%zu]:\n", i);
			for (size_t j = 0; j < Tabs; ++j) fprintf(fp, "\t");
			fprintf(fp, "{\n", i);
			net[i]->demo(Tabs + 1, fp);
			for (size_t j = 0; j < Tabs; ++j) fprintf(fp, "\t");
			fprintf(fp, "}\n");
		}
			
		else
		{
			for (size_t j = 0; j < tabs + 2; ++j) fprintf(fp, "\t");
			fprintf(fp, "NULL");
		}
			
		fprintf(fp, "\n");
	}
}
