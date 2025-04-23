#include"../header/Pikachu.h"
using namespace Pikachu;

#ifdef UnderDebugMode
#include<iostream>
#endif // UnderDebugMode


#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif
tensor::tensor()
{
	order = 1;
	dim = (size_t*)malloc(sizeof(size_t) * 1);
	dim[0] = 1;
	count = 1;
}
tensor::~tensor()
{
	free(dim);
}
bool tensor::operator==(const tensor& Right) const
{
	size_t i;
	if (order != Right.order) return false;
	for (i = 0; i < order; i++)
		if (dim[i] != Right.dim[i]) return false;
	return true;
}
bool tensor::CountCompare(const tensor& Right) const
{
	return count == Right.count;
}
bool tensor::Equal(const tensor& Right, size_t begin, size_t upper) const
{
	size_t i;
	if(upper > order) throw PikaError("tensor::Equal", "(upper > order)", 1);
	if (upper > Right.order) throw PikaError("tensor::Equal", "(upper > Right.order)", 1);
	for (i = begin; i < upper; i++)
		if (dim[i] != Right.dim[i]) return false;
	return true;
}
void tensor::ChangeOrder(size_t NewOrder)
{
	size_t i;
	if (NewOrder == order) return;
	if (NewOrder == 0)
	{
		free(dim);
		order = 0;
		dim = NULL;
		count = 1;
		return;
	}
	dim = (size_t*)realloc(dim, sizeof(size_t) * NewOrder);
	if (NewOrder < order)
	{
		for (i = NewOrder; i < order; i++) dim[NewOrder - 1] *= dim[i];
	}
	else
	{
		for (i = order; i < NewOrder; i++) dim[i] = 1;
	}
	order = NewOrder;
	return;
}
void tensor::ChangeDim(size_t No, size_t NewDim)
{
	size_t i;
	if(No > order) throw PikaError("tensor::ChangeDim", "Out of range", 1);
	if (NewDim == 0) throw PikaError("tensor::ChangeDim", "Dim is 0", 1);
	dim[No] = NewDim;
	count = dim[0];
	for (i = 1; i < order; i++)
		count *= dim[i];
	return;
}
void tensor::AppendDim(size_t NewDim)
{
	if (NewDim == 0) throw PikaError("tensor::AppendDim", "Dim is 0", 1);
	dim = (size_t*)realloc(dim, sizeof(size_t) * (order + 1));
	count *= NewDim;
	dim[order] = NewDim;
	order = order + 1;
}
void tensor::Clear(void)
{
	order = 0;
	free(dim);
	dim = NULL;
	count = 1;
}
void tensor::CutLast(const tensor& source)
{
	size_t i;
	if (source.GetOrder() == 0)return;
	ChangeOrder(source.GetOrder() - 1);
	for (i = 0; i < source.GetOrder() - 1; i++)
	{
		ChangeDim(i, source[i]);
	}
}
void tensor::Set(const tensor& source)
{
	size_t i;
	order = source.order;
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	for (i = 0; i < order; i++) dim[i] = source[i];
	count = source.count;
}
void tensor::Demo(FILE* fp)const
{
	size_t i;
	fprintf(fp, "order: %zu, ", order);
	if (order != 0)
	{
		fprintf(fp, "[");
		for (i = 0; i < order - 1; i++)
		{
			fprintf(fp, "%zu, ", dim[i]);
		}
		fprintf(fp, "%zu], ", dim[order - 1]);
	}
	fprintf(fp, "count: %zu.\n", count);
}
void tensor::Demo(FILE* fp, const char* name)const
{
	size_t i;
	fprintf(fp, "%s, order: %zu, ", name, order);
	if (order != 0)
	{
		fprintf(fp, "[");
		for (i = 0; i < order - 1; i++)
		{
			fprintf(fp, "%zu, ", dim[i]);
		}
		fprintf(fp, "%zu], ", dim[order - 1]);
	}
	fprintf(fp, "count: %zu.\n", count);
}
void tensor::OrderGrowth(void)
{
	OrderGrowth(1);
}
void tensor::OrderGrowth(size_t delta)
{
	ChangeOrder(order + delta);
}
void tensor::OrderGrowthOne(size_t NewDim)
{
	OrderGrowth();
	ChangeDim(order - 1, NewDim);
}
size_t tensor::GetCount(void)const
{
	return count;
}
size_t tensor::GetOrder(void)const
{
	return order;
}
const size_t& tensor::operator[](size_t target) const
{
	if (target >= order) throw PikaError("tensor::operator[]", "Out of range", 1);
	return dim[target];
}

void tensor::contraction(const tensor& sourceL, const tensor& sourceR)
{
	size_t i;
	order = sourceL.order + sourceR.order;
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	for (i = 0; i < sourceL.order; i++) dim[i] = sourceL[i];
	for (i = 0; i < sourceR.order; i++) dim[i + sourceL.order] = sourceR[i];
	count = sourceL.count * sourceR.count;
}
void tensor::contraction(const tensor& sourceL, const tensor& sourceR, const ContractDesc& contract)
{
	size_t i, j;
	if (sourceL.GetOrder() != contract.Left.count()) 
		throw PikaError("tensor::contraction", "order unmatch", 1);
	if (sourceR.GetOrder() != contract.Right.count())
		throw PikaError("tensor::contraction", "order unmatch", 2);
	order = contract.Out.count();
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	count = 1;
	for (i = 0; i < order; i++)
	{
		j = contract.Out[i].peer;
		dim[i] = contract.Out[i].infor.left ? sourceL[j] : sourceR[j];
		count *= dim[i];
	}
	for (i = 0; i < contract.Left.count(); i++)
	{
		if (contract.Left[i].infor.dummy == true)
		{
			if(sourceL[i] != sourceR[contract.Left[i].peer])
				throw PikaError("tensor::contraction", "tensor dim unmatch", 2);
		}
	}
	return;
}
void tensor::contraction(const tensor& sourceL, const tensor& sourceR, const contract& contract)
{
	size_t i, j;
	if (sourceL.GetOrder() != contract.Left.count())
		throw PikaError("tensor::contraction", "order unmatch", 1);
	if (sourceR.GetOrder() != contract.Right.count())
		throw PikaError("tensor::contraction", "order unmatch", 2);
	order = contract.Out.count();
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	count = 1;
	for (i = 0; i < order; i++)
	{
		if (contract.Out[i].src1 != _uintMax_) dim[i] = sourceL[j];
		else dim[i] = sourceR[j];
		count *= dim[i];
	}
	for (i = 0; i < contract.Left.count(); i++)
	{
		if (contract.Left[i].src2 != _uintMax_)
		{
			if (sourceL[i] != sourceR[contract.Left[i].src2])
				throw PikaError("tensor::contraction", "tensor dim unmatch", 2);
		}
	}
	return;
}

void tensor::Dispatch(const tensor& source, const dispatch& desc)
{
	size_t i;
	if (source.GetOrder() != desc.sourceOrder)
		throw PikaError("tensor::Dispatch", "source.GetOrder() != desc.sourceOrder", 1);
	if (source.GetOrder() == desc.Desc.count())
	{
		order = source.GetOrder();
		dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	}
	else
	{
		if (order != desc.Desc.count())
			throw PikaError("tensor::Dispatch", "order != desc.Desc.count()", 1);
	}
	count = 1;
	for (i = 0; i < order; i++)
	{
		if (desc.Desc[i] != _uintMax_)
			dim[i] = source[desc.Desc[i]];
		count *= dim[i];
	}
	return;
}
void tensor::Dispatch(const tensor& source, const dispatch& desc, const tensor& former)
{
	size_t i;
	if (former.GetOrder() < source.GetOrder())
		throw PikaError("tensor::Dispatch", "former.GetOrder() < source.GetOrder()", 1);
	if (source.GetOrder() != desc.sourceOrder)
		throw PikaError("tensor::Dispatch", "source.GetOrder() != desc.sourceOrder", 1);
	order = source.GetOrder();
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	count = 1;
	for (i = 0; i < order; i++)
	{
		if (desc.Desc[i] != _uintMax_)
			dim[i] = source[desc.Desc[i]];
		else
		{
			if (i < former.GetOrder())
				dim[i] = former[i];
			else
				throw PikaError("tensor::Dispatch", "i >= former.GetOrder()", i + 1);
		}
		count *= dim[i];
	}
	return;
}
void tensor::Condensation(const tensor & source, const condensation & desc)
{
	size_t i;
	if (source.GetOrder() != desc.Desc.count())
		throw PikaError("tensor::Condensation", "source.GetOrder() != desc.sourceOrder", 1);
	order = desc.OutSource.count();
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	count = 1;
	for (i = 0; i < order; i++)
	{
		dim[i] = source[desc.OutSource[i]];
		count *= dim[i];
	}
	return;
}
void tensor::Elementwise(const tensor& sourceL, const tensor& sourceR, const elementwise& desc)
{
	size_t i;
	if (sourceL.GetOrder() != desc.LeftDim)
		throw PikaError("tensor::Elementwise", "sourceL.GetOrder() != desc.LeftDim", 1);
	if (sourceR.GetOrder() != desc.RightDim)
		throw PikaError("tensor::Elementwise", "sourceR.GetOrder() != desc.RightDim", 2);

	order = desc.Desc.count();
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	count = 1;
	for (i = 0; i < order; i++)
	{
		if (desc.Desc[i].left != _uintMax_)
		{
			dim[i] = sourceL[desc.Desc[i].left];
			if (desc.Desc[i].right != _uintMax_)
				if(sourceR[desc.Desc[i].right] != sourceL[desc.Desc[i].left])
					throw PikaError("tensor::Elementwise", "sourceR[desc.Desc[i].right] != sourceL[desc.Desc[i].left]", i + 1);
		}
		else
		{
			if (desc.Desc[i].right != _uintMax_)
				dim[i] = sourceR[desc.Desc[i].right];
			else
				throw PikaError("tensor::Elementwise", "vain index", i + 1);
		}
		count *= dim[i];
	}

}

elaboration::elaboration()
{
}
elaboration::~elaboration()
{
}
void elaboration::attach(const elaboration& old, const size_t NewData)
{
	size_t i;
	recount(old.Count + 1);
	for (i = 0; i < Count; i++)
		content[i] = old[i];
	content[Count - 1] = NewData;
}
bool elaboration::operator==(const elaboration& Right) const
{
	size_t i;
	if (Count != Right.Count) return false;
	for (i = 0; i < Count; i++)
		if (content[i] != Right[i]) return false;
	return true;
}


tensorPara::tensorPara()
{

}
tensorPara::~tensorPara()
{

}
size_t tensorPara::site(void)const
{
	return No;
}
size_t tensorPara::prefix(void)const
{
	return Prefix;
}


tensorList::tensorList()
{
	Count = 0;
	Capacity = 0;
	content = NULL;
}
tensorList::~tensorList()
{
	size_t i;
	Count = 0;
	Capacity = 0;
	for (i = 0; i < Count; i++)
	{
		delete content[i];
	}
	free(content);
	content = NULL;
}
void tensorList::clear(void)
{
	size_t i;
	for (i = 0; i < Count; i++)
	{
		delete content[i];
	}
	Count = 0;
}
size_t tensorList::capacity(void) const
{
	return Capacity;
}
size_t tensorList::count(void) const
{
	return Count;
}
tensorPara*& tensorList::operator[](size_t target)
{
	return content[target];
}
size_t tensorList::append(void)
{
	size_t should, new_size;
	if (Count >= Capacity)
	{
		new_size = (Capacity + Capacity / 4 + 8);
		content = (tensorPara**)realloc(content, new_size * sizeof(tensorPara*));
		Capacity = new_size;
	}
	should = Count;
	Count += 1;
	return should;
}
void tensorList::append(tensor* element)
{
	size_t should;
	tensorPara* newOne;
	should = append();
	newOne = new tensorPara();

	newOne->Set(*element);
	newOne->No = should;
	if (should != 0)
	{
		newOne->Prefix = content[should - 1]->Prefix + content[should - 1]->GetCount();
	}
	else
	{
		newOne->Prefix = 0;
	}


	content[should] = newOne;
}

size_t tensorList::Offset(size_t No, size_t ld) const
{
	return content[No]->prefix() * ld;
}
size_t tensorList::Offset(size_t No) const
{
	return content[No]->prefix();
}



//_uintMax_


ContractDesc::ContractDesc()
{
	completed = false;
}
ContractDesc::~ContractDesc()
{
}
void ContractDesc::SetDim(size_t dimO, size_t dimL, size_t dimR)
{
	size_t i;
	Out.recount(dimO);
	Left.recount(dimL);
	Right.recount(dimR);
	for (i = 0; i < Out.count(); i++)
		Out[i].peer = _uintMax_;
	for (i = 0; i < Left.count(); i++)
		Left[i].peer = _uintMax_;
	for (i = 0; i < Right.count(); i++)
		Right[i].peer = _uintMax_;
	completed = false;
}
size_t& ContractDesc::out(size_t No)
{
	return Out[No].label;
}
size_t& ContractDesc::left(size_t No)
{
	return Left[No].label;
}
size_t& ContractDesc::right(size_t No)
{
	return Right[No].label;
}

//
void ContractDesc::CheckAndBuild(const vector<size_t>& O, const vector<size_t>& L, const vector<size_t>& R)
{
	size_t i;
	SetDim(O.count(), L.count(), R.count());
	for (i = 0; i < O.count(); i++)
		Out[i].label = O[i];
	for (i = 0; i < L.count(); i++)
		Left[i].label = L[i];
	for (i = 0; i < R.count(); i++)
		Right[i].label = R[i];
	try
	{
		//std::cout << "checkAndBuild(O, L, R);" << std::endl;
		CheckAndBuild();
	}
	catch (PikaError &E)
	{
		throw PikaError(E, "ContractDesc::CheckAndBuild->");
	}
}
void ContractDesc::CheckAndBuild(const tensor& TeensorSrc, size_t SrcDim, const tensor& BackSrc, size_t OutCount)
{

}
void ContractDesc::CheckAndBuild(size_t Front, size_t Output, size_t Last, size_t Extra)
{
	vector<size_t> O;
	vector<size_t> L; 
	vector<size_t> R;
	size_t i, label;
	SetDim(Front + Output + 1 + Last, Front + Output + Last + Extra, Front + 1 + Last + Extra);
	label = 0;
	for (i = 0; i < Front; i++)
	{
		Out[i].label = label;
		Left[i].label = label;
		Right[i].label = label;
		label += 1;
	}
	for (i = 0; i < Output; i++)
	{

	}
}
void ContractDesc::CheckAndBuild(void)
{
	size_t i, j, temp;
	//std::cout << "checkAndBuild(O, L, R) 1;" << std::endl;
	for (i = 0; i < Out.count(); i++)
	{
		for (j = 0; j < Left.count(); j++)
			if (Left[j].label == Out[i].label)
			{
				Left[j].peer = i;
				Out[i].peer = j;
				Left[j].infor.dummy = false;
				Out[i].infor.left = true;
				break;
			}
		if (j < Left.count()) continue;
		for (j = 0; j < Right.count(); j++)
			if (Right[j].label == Out[i].label)
			{
				Right[j].peer = i;
				Out[i].peer = j;
				Right[j].infor.dummy = false;
				Out[i].infor.left = false;
				break;
			}
	}
	//std::cout << "checkAndBuild(O, L, R) 2;" << std::endl;
	for (i = 0; i < Left.count(); i++)
	{
		if (Left[i].peer != _uintMax_) continue;
		for (j = 0; j < Right.count(); j++)
			if (Right[j].label == Left[i].label)
			{
				Right[j].peer = i;
				Left[i].peer = j;
				Right[j].infor.dummy = true;
				Left[i].infor.dummy = true;
				break;
			}
	}
	//std::cout << "checkAndBuild(O, L, R) 3;" << std::endl;
	for (i = 0; i < Left.count(); i++)
	{
		temp = Left[i].peer;
		if (temp == _uintMax_) throw PikaError("ContractDesc::CheckAndBuild", "Left[i].peer == _uintMax_", 1);
		if (Left[i].infor.dummy)
		{
			if (Right[temp].peer != i || Right[temp].infor.dummy != true) 
				throw PikaError("ContractDesc::CheckAndBuild", "Left[i].infor.dummy", 2);
		}
		else
		{
			if (Out[temp].peer != i || Out[temp].infor.left != true) 
				throw PikaError("ContractDesc::CheckAndBuild", "Left[i].infor.dummy", 3); 
		}
	}
	//std::cout << "checkAndBuild(O, L, R) 4;" << std::endl;
	for (i = 0; i < Right.count(); i++)
	{
		temp = Right[i].peer;
		if (temp == _uintMax_) throw PikaError("ContractDesc::CheckAndBuild", "Right[i].peer", 1);
		if (Right[i].infor.dummy)
		{
			if (Left[temp].peer != i || Left[temp].infor.dummy != true) 
				throw PikaError("ContractDesc::CheckAndBuild", "Right[i].infor.dummy", 4);
		}
		else
		{
			if (Out[temp].peer != i || Out[temp].infor.left != false) 
				throw PikaError("ContractDesc::CheckAndBuild", "Right[i].infor.dummy", 5);
		}
	}
	//std::cout << "checkAndBuild(O, L, R) 5;" << std::endl;
	for (i = 0; i < Out.count(); i++)
	{
		temp = Out[i].peer;
		if (temp == _uintMax_) throw PikaError("ContractDesc::CheckAndBuild", "Out[i].peer == _uintMax_", 1);
		if (Out[i].infor.left)
		{
			if (Left[temp].peer != i || Left[temp].infor.dummy == true) 
				throw PikaError("ContractDesc::CheckAndBuild", "Out[i].infor.left", 6);
		}
		else
		{
			if (Right[temp].peer != i || Right[temp].infor.dummy == true) 
				throw PikaError("ContractDesc::CheckAndBuild", "Out[i].infor.left", 7); 
		}
	}
	completed = true;
	//sstd::cout << "checkAndBuild(O, L, R);" << std::endl;
	return;
}
size_t ContractDesc::DummyCount(void)const
{
	return (Left.count() + Right.count() - Out.count()) / 2;
}
size_t ContractDesc::Max(void) const
{
	size_t i, largest;
	largest = 0;
	for (i = 0; i < Out.count(); i++)
		if (largest < Out[i].label) largest = Out[i].label;
	for (i = 0; i < Left.count(); i++)
		if (largest < Left[i].label) largest = Left[i].label;
	for (i = 0; i < Right.count(); i++)
		if (largest < Right[i].label) largest = Right[i].label;
	return largest;
}

void ContractDesc::backward(const tensor& BackSrc, const ContractDesc& forward)
{
	size_t i, j, k, index, temp;
	if (BackSrc.GetOrder() < forward.Out.count())
		throw PikaError("ContractDesc::backward", "BackSrc.GetOrder() < forward.Out.count()", 10); 
#ifdef Debug01
	std::cout << "backward 1;" << std::endl;
#endif // Debug01

	SetDim(forward, forward.Left.count(), BackSrc.GetOrder());
	index = 0;
#ifdef Debug01
	std::cout << "backward 2;" << std::endl;
#endif // Debug01
	for (i = 0; i < forward.Left.count(); i++)
	{
		Left[i].label = index;
		if (forward.Left[i].infor.dummy == false) // not dummy in forward, dummy here
		{
			Right[forward.Left[i].peer].label = index;
		}
		else // dummy in forward, not dummy here
		{
			Out[forward.Left[i].peer].label = index;
		}
		index += 1;
	}
#ifdef Debug01
	std::cout << "backward 3;" << std::endl;
#endif // Debug01
	for (i = 0; i < forward.Right.count(); i++)
	{
		if (forward.Right[i].infor.dummy == false) // not dummy in forward, dummy here
		{
			Right[forward.Right[i].peer].label = index;
			Out[i].label = index;
		}
		index++;
		// else  dummy in forward, not dummy here, computed before;
	}
#ifdef Debug01
	std::cout << "backward 4;" << std::endl;
#endif // Debug01
	temp = BackSrc.GetOrder() - forward.Out.count();
	for (i = 0; i < temp; i++)
	{
		Right[i + forward.Out.count()].label = index;
		Out[i + forward.Right.count()].label = index;
		index++;
	}
#ifdef Debug01
	std::cout << "backward 5;" << std::endl;
#endif // Debug01
	try
	{
		CheckAndBuild();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "ContractDesc::backward->");
	}
#ifdef Debug01
	std::cout << "backward 6;" << std::endl;
#endif // Debug01
}
void ContractDesc::backward(const tensor& BackSrc, const ContractDesc& forward, bool right)
{
	size_t i, j, k, index, temp;
	size_t extra;
	if (BackSrc.GetOrder() < forward.Out.count())
		throw PikaError("ContractDesc::backward", "BackSrc.GetOrder() < forward.Out.count()", 10);
	
	extra = BackSrc.GetOrder() - forward.Out.count();
	
	index = 0;
	if (right)
	{
		SetDim(forward.Right.count() + extra, forward.Left.count(), BackSrc.GetOrder());
		for (i = 0; i < forward.Left.count(); i++)
		{
			Left[i].label = index;
			temp = forward.Left[i].peer;
			if (forward.Left[i].infor.dummy == false) // not dummy in forward, dummy here
			{
				Right[temp].label = index;
			}
			else // dummy in forward, not dummy here
			{
				Out[temp].label = index;
			}
			index += 1;
		}

		for (i = 0; i < forward.Right.count(); i++)
		{
			if (forward.Right[i].infor.dummy == false) // not dummy in forward, dummy here
			{
				Right[forward.Right[i].peer].label = index;
				Out[i].label = index;
			}
			index++;
			// else  dummy in forward, not dummy here, computed before;
		}
		for (i = 0; i < extra; i++)
		{
			Right[i + forward.Out.count()].label = index;
			Out[i + forward.Right.count()].label = index;
			index++;
		}
	}		
	else
	{
		SetDim(forward.Left.count() + extra, BackSrc.GetOrder(), forward.Right.count());
		for (i = 0; i < forward.Right.count(); i++)
		{
			Right[i].label = index;
			temp = forward.Right[i].peer;
			if (forward.Right[i].infor.dummy == false) // not dummy in forward, dummy here
			{
				Left[temp].label = index;
			}
			else // dummy in forward, not dummy here
			{
				Out[temp].label = index;
			}
			index += 1;
		}
		for (i = 0; i < forward.Left.count(); i++)
		{
			if (forward.Left[i].infor.dummy == false) // not dummy in forward, dummy here
			{
				Left[forward.Left[i].peer].label = index;
				Out[i].label = index;
			}
			index++;
			// else  dummy in forward, not dummy here, computed before;
		}
		for (i = 0; i < extra; i++)
		{
			Left[i + forward.Out.count()].label = index;
			Out[i + forward.Left.count()].label = index;
			index++;
		}
		
	}

	try
	{
		CheckAndBuild();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "ContractDesc::backward->");
	}
}
void ContractDesc::SetDim(const ContractDesc& forward, size_t dimL, size_t dimR)
{
	size_t Oldorder, OrderNow;
	OrderNow = forward.Left.count() - forward.DummyCount();
	SetDim(dimL + dimR - 2 * OrderNow, dimL, dimR);
	return;
}
void ContractDesc::Demo(FILE* fp)
{
	size_t i;
	if (!completed)
	{
		fprintf(fp, "not completed\n");
		return;
	}
	fprintf(fp, "Out: [");
	for (i = 0; i < Out.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %d)", Out[i].label, Out[i].peer, (int)Out[i].infor.left);
	}
	fprintf(fp, "]\n");
	fprintf(fp, "Left: [");
	for (i = 0; i < Left.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %d)", Left[i].label, Left[i].peer, (int)Left[i].infor.dummy);
	}
	fprintf(fp, "]\n");
	fprintf(fp, "Right: [");
	for (i = 0; i < Right.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %d)", Right[i].label, Right[i].peer, (int)Right[i].infor.left);
	}
	fprintf(fp, "]\n");


}
void ContractDesc::Set(const ContractDesc& source)
{
	size_t i;
	Out.copy(source.Out);
	//for (i = 0; i < source.Out.count(); i++)
	//{
	//	Out[i].infor = source.Out[i].infor;
	//	Out[i].label = source.Out[i].label;
	//	Out[i].peer = source.Out[i].peer;
	//}
	Left.copy(source.Left);
	Right.copy(source.Right);
	completed = source.completed;
}


contract::contract()
{
	completed = false;
}
contract::~contract()
{
}
void contract::index::initial(void)
{
	src1 = _uintMax_;
	src2 = _uintMax_;
}
bool contract::index::vain(void)
{
	return src1 == _uintMax_ && src2 == _uintMax_;
}
void contract::SetDim(size_t dimO, size_t dimL, size_t dimR)
{
	Out.recount(dimO);
	Left.recount(dimL);
	Right.recount(dimR);
	Initial();
}
void contract::Initial(void)
{
	size_t i;
	for (i = 0; i < Out.count(); i++)
		Out[i].initial();
	for (i = 0; i < Left.count(); i++)
		Left[i].initial();
	for (i = 0; i < Right.count(); i++)
		Right[i].initial();
}
void contract::Build(void)
{
	size_t i, j;
	
	//std::cout << "checkAndBuild(O, L, R) 1;" << std::endl;
	for (i = 0; i < Out.count(); i++)
	{
		for (j = i + 1; j < Out.count(); j++)
			if (Out[j].label == Out[i].label)
				throw PikaError("contract::Build", "Out[j].label == Out[i].label", i);
		for (j = 0; j < Left.count(); j++)
			if (Left[j].label == Out[i].label)
			{
				Left[j].src1 = i;
				Out[i].src1 = j;
				break;
			}
		for (j = 0; j < Right.count(); j++)
			if (Right[j].label == Out[i].label)
			{
				Right[j].src1 = i;
				Out[i].src2 = j;
				break;
			}
		if (Out[i].src1 != _uintMax_ && Out[i].src2 != _uintMax_)
		{
			Left[Out[i].src1].src2 = Out[i].src2;
			Left[Out[i].src2].src2 = Out[i].src1;
		}
		if (Out[i].vain())
			throw PikaError("contract::Build", "Out[i].vain()", i);
	}
	//std::cout << "checkAndBuild(O, L, R) 2;" << std::endl;
	for (i = 0; i < Right.count(); i++)
		for (j = i + 1; j < Right.count(); j++)
			if (Right[j].label == Right[i].label)
				throw PikaError("contract::Build", "Right[j].label == Right[i].label", i);
	for (i = 0; i < Left.count(); i++)
	{
		for (j = i + 1; j < Left.count(); j++)
			if (Left[j].label == Left[i].label)
				throw PikaError("contract::Build", "Left[j].label == Left[i].label", i);
		if (Left[i].src2 != _uintMax_) continue;
		for (j = 0; j < Right.count(); j++)
			if (Right[j].label == Left[i].label)
			{
				Right[j].src2 = i;
				Left[i].src2 = j;
				break;
			}
		if (Left[i].vain())
			throw PikaError("contract::Build", "Left[i].vain()", i);
	}
		
		
	for (i = 0; i < Right.count(); i++)
		if (Right[i].vain())
			throw PikaError("contract::Build", "Right[i].vain()", i);

	


	completed = true;
}
void contract::Build(const vector<size_t>& O, const vector<size_t>& L, const vector<size_t>& R)
{
	size_t i;
	SetDim(O.count(), L.count(), R.count());
	for (i = 0; i < O.count(); i++)
		Out[i].label = O[i];
	for (i = 0; i < L.count(); i++)
		Left[i].label = L[i];
	for (i = 0; i < R.count(); i++)
		Right[i].label = R[i];
	try
	{
		Build();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "Build::Build->");
	}
}
void contract::Build(const tensor& TensorSrc, size_t SrcDim, const tensor& BackSrc, size_t OutCount)
{
	size_t Front;
	size_t Output;
	size_t Last;
	size_t Extra;
	size_t i;
	Output = OutCount;
	Front = SrcDim;
	if(TensorSrc.GetOrder() < (1 + Front))
		throw PikaError("contract::Build", "TensorSrc.GetOrder() < (1 + Front)", (1 + Front));
	Last = TensorSrc.GetOrder() - (1 + Front);
	if (BackSrc.GetOrder() < (Output + Front + Last))
		throw PikaError("contract::Build", "BackSrc.GetOrder() < (Output + Front + Last)", BackSrc.GetOrder());
	Extra = BackSrc.GetOrder() - (Output + Front + Last);

	for (i = 0; i < Front; i++)
		if (TensorSrc[i] != BackSrc[i])
			throw PikaError("contract::Build", "TensorSrc[i] != BackSrc[i]", i);

	for (i = 0; i < Last; i++)
		if (TensorSrc[i + Front + 1] != BackSrc[i + Front + Output])
			throw PikaError("contract::Build", "2TensorSrc[i] != BackSrc[i]", i);
	Build(Front, Output, Last, Extra);
}
void contract::Build(size_t Front, size_t Output, size_t Last, size_t Extra)
{
	size_t i, label;
	size_t Loffset, Roffset;
	SetDim(Front + Output + 1 + Last, Front + Output + Last + Extra, Front + 1 + Last + Extra);
	label = 0;
	for (i = 0; i < Front; i++)
	{
		Out[i].label = label;
		Left[i].label = label;
		Right[i].label = label;
		label += 1;
	}
	for (i = 0; i < Output; i++)
	{
		Left[i + Front].label = label;
		Right[i + Front].label = label;
		label += 1;
	}
	Left[Front + Output].label = label;
	Out[Front].label = label;
	label += 1;
	for (i = 0; i < Last; i++)
	{
		Out[i + Front + 1].label = label;
		Left[i + Front + Output + 1].label = label;
		Right[i + Front + Output].label = label;
		label += 1;
	}
	for (i = 0; i < Extra; i++)
	{
		Out[i + Front + 1 + Last].label = label;
		Right[i + Front + Output + Last].label = label;
		label += 1;
	}
	Build();
}
void contract::ForwardBuild(const tensor& TensorSrc, size_t SrcDim, const tensor& FrontSrc, size_t OutCount)
{
	size_t Front;
	size_t Output;
	size_t Last;
	size_t Extra;
	size_t i, label;
	size_t Loffset, Roffset;
	Output = OutCount;
	Front = SrcDim;
	if (TensorSrc.GetOrder() < (1 + Front))
		throw PikaError("contract::ForwardBuild", "TensorSrc.GetOrder() < (1 + Front)", (1 + Front));
	Last = TensorSrc.GetOrder() - (1 + Front);
	if (FrontSrc.GetOrder() < TensorSrc.GetOrder())
		throw PikaError("contract::ForwardBuild", "FrontSrc.GetOrder() < TensorSrc.GetOrder()", FrontSrc.GetOrder());
	Extra = FrontSrc.GetOrder() - TensorSrc.GetOrder();

	for (i = 0; i < TensorSrc.GetOrder(); i++)
		if (TensorSrc[i] != FrontSrc[i])
			throw PikaError("contract::ForwardBuild", "TensorSrc[i] != FrontSrc[i]", i);

	SetDim(Front + Output + 1 + Last, FrontSrc.GetOrder(), Front + Output + Last + Extra);
	label = 0;
	for (i = 0; i < Front; i++)
	{
		Out[i].label = label;
		Left[i].label = label;
		Right[i].label = label;
		label += 1;
	}
	for (i = 0; i < Output; i++)
	{
		Left[i + Front].label = label;
		Out[i + Front].label = label;
		label += 1;
	}
	Left[Front + Output].label = label;
	Right[Front].label = label;
	label += 1;
	for (i = 0; i < Last; i++)
	{
		Out[i + Front + Output].label = label;
		Left[i + Front + Output + 1].label = label;
		Right[i + Front + 1 ].label = label;
		label += 1;
	}
	for (i = 0; i < Extra; i++)
	{
		Out[i + Front + Output + Last].label = label;
		Right[i + Front + 1 + Last].label = label;
		label += 1;
	}
	Build();
}
void contract::LabelShrink(void)
{
	size_t index;
	size_t i, j, temp;
	index = 0;
	for (i = 0; i < Out.count(); i++)
	{
		temp = Out[i].src1;
		if (temp != _uintMax_)
			Left[temp].label = i;
		temp = Out[i].src2;
		if (temp != _uintMax_)
			Right[temp].label = i;
		Out[i].label = i;
	}
	index = Out.count();
	for (i = 0; i < Left.count(); i++)
	{
		temp = Left[i].src1;
		if (temp != _uintMax_) continue;
		Left[i].label = index;
		Right[Left[i].src2].label = index;
		index += 1;
	}
}
size_t contract::MaxLabel(void)const
{
	size_t label, i;
	label = 0;
	for (i = 0; i < Left.count(); i++)
		label = label > Left[i].label ? label : Left[i].label;
	for (i = 0; i < Right.count(); i++)
		label = label > Right[i].label ? label : Right[i].label;
	for (i = 0; i < Out.count(); i++)
		label = label > Out[i].label ? label : Out[i].label;
	return label;
}
void contract::backward(const tensor& BackSrc, const contract& forward, bool right)
{
	size_t i, j, k, index, temp;
	size_t extra;
	if (BackSrc.GetOrder() < forward.Out.count())
		throw PikaError("contract::backward", "BackSrc.GetOrder() < forward.Out.count()", 10);

	extra = BackSrc.GetOrder() - forward.Out.count();

	index = forward.MaxLabel() + 1;

	if (right)
	{
		SetDim(forward.Right.count() + extra, forward.Left.count(), BackSrc.GetOrder());
		for (i = 0; i < forward.Left.count(); i++)
			Left[i].label = forward.Left[i].label;
		for (i = 0; i < forward.Right.count(); i++)
			Out[i].label = forward.Right[i].label;
		for (i = 0; i < forward.Out.count(); i++)
			Right[i].label = forward.Out[i].label;
		for (i = 0; i < extra; i++)
		{
			Right[i + forward.Out.count()].label = index;
			Out[i + forward.Right.count()].label = index;
			index++;
		}
	}
	else
	{
		SetDim(forward.Left.count() + extra, BackSrc.GetOrder(), forward.Right.count());
		for (i = 0; i < forward.Right.count(); i++)
			Right[i].label = forward.Right[i].label;
		for (i = 0; i < forward.Left.count(); i++)
			Out[i].label = forward.Left[i].label;
		for (i = 0; i < forward.Out.count(); i++)
			Left[i].label = forward.Out[i].label;
		for (i = 0; i < extra; i++)
		{
			Left[i + forward.Out.count()].label = index;
			Out[i + forward.Left.count()].label = index;
			index++;
		}

	}

	try
	{
		Build();
		LabelShrink();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "contract::backward->");
	}
}
void contract::forward(const tensor& ForwardSrc, const contract& DescSrc, bool left)
{
	size_t i, j, k, index, temp, inputDim;
	size_t extra;
	inputDim = left ? DescSrc.Left.count() : DescSrc.Right.count();
	if (ForwardSrc.GetOrder() < inputDim)
		throw PikaError("contract::forward", "ForwardSrc.GetOrder() < inputDim", 10);

	extra = ForwardSrc.GetOrder() - inputDim;

	index = DescSrc.MaxLabel() + 1;

	if (left)
		SetDim(DescSrc.Out.count() + extra, DescSrc.Left.count() + extra, DescSrc.Right.count());
	else
		SetDim(DescSrc.Out.count() + extra, DescSrc.Left.count(), DescSrc.Right.count() + extra);
	for (i = 0; i < DescSrc.Left.count(); i++)
		Left[i].label = DescSrc.Left[i].label;
	for (i = 0; i < DescSrc.Right.count(); i++)
		Right[i].label = DescSrc.Right[i].label;
	for (i = 0; i < DescSrc.Out.count(); i++)
		Out[i].label = DescSrc.Out[i].label;
	for (i = 0; i < extra; i++)
	{
		Out[i + DescSrc.Out.count()].label = index;
		if (left)  Left[i + DescSrc.Left.count()].label = index;
		else Right[i + DescSrc.Right.count()].label = index;
		index++;
	}
	try
	{
		Build();
		LabelShrink();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "contract::backward->");
	}
}
void contract::Demo(FILE* fp)
{
	size_t i;
	if (!completed)
	{
		fprintf(fp, "not completed\n");
		return;
	}
	fprintf(fp, "Out: [");
	for (i = 0; i < Out.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %zu)", Out[i].label, Out[i].src1, (size_t)Out[i].src2);
	}
	fprintf(fp, "]\n");
	fprintf(fp, "Left: [");
	for (i = 0; i < Left.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %zu)", Left[i].label, Left[i].src1, (size_t)Left[i].src2);
	}
	fprintf(fp, "]\n");
	fprintf(fp, "Right: [");
	for (i = 0; i < Right.count(); i++)
	{
		fprintf(fp, "(%zu, %zu, %zu)", Right[i].label, Right[i].src1, (size_t)Right[i].src2);
	}
	fprintf(fp, "]\n");


}
void contract::Set(const contract& source)
{
	Out.copy(source.Out);
	Left.copy(source.Left);
	Right.copy(source.Right);
	completed = source.completed;
}

/*
size_t perish;
	size_t i, j, count_;
	array<bool> temp;
	temp.Realloc(sourceL.order + sourceR.order);
	temp.value(true);
	if (sourceL.order != descLtoR.count()) return 1;
	for (i = 0; i < sourceL.order; i++)
	{
		if (descLtoR[i] > sourceR.order) return 2;
	}
	for (i = 0; i < sourceL.order; i++)
	{
		j = descLtoR[i];
		if (j == sourceR.order) continue;
		temp[i] = false;
		if (temp[j + sourceL.order] == false) return 3;
		temp[j + sourceL.order] = false;
	}
	order = 0;
	for (i = 0; i < sourceL.order + sourceR.order; i++)
		if (temp[i]) order += 1;
	dim = (size_t*)realloc(dim, sizeof(size_t) * order);
	j = 0;
	for (i = 0; i < sourceL.order; i++)
	{
		if (temp[i])
		{
			dim[j] = sourceL[i];
			j += 1;
		}
	}
	for (i = 0; i < sourceR.order; i++)
	{
		if (temp[i + sourceL.order])
		{
			dim[j] = sourceR[i];
			j += 1;
		}
	}
	count = 1;
	for (i = 0; i < order; i++) count *= dim[i];
	return (count != j) * 4;
*/


elementwise::elementwise()
{
	completed = false;
}
elementwise::~elementwise()
{
}
void elementwise::build(const vector<size_t>& L, const vector<size_t>& R)
{
	size_t i;
	LeftDim = 0;
	RightDim = 0;
	if (L.count() != R.count())
		throw PikaError("elementwise::build", "L.count() != R.count()", 1);
	Desc.recount(L.count());
	for (i = 0; i < Desc.count(); i++)
	{
		Desc[i].left = L[i];
		if (L[i] != _uintMax_)
		{
			LeftDim += 1;
		}
		Desc[i].right = R[i];
		if (R[i] != _uintMax_)
		{
			RightDim += 1;
		}
		if(L[i] == _uintMax_ && R[i] == _uintMax_)
			throw PikaError("elementwise::build", "L[i] == _uintMax_ && R[i] == _uintMax_", i + 1);
	}
	try
	{
		check();
	}
	catch (PikaError& E)
	{	

		throw PikaError(E, "elementwise::build->");
	}
	completed = true;
}
void elementwise::build(const size_t trival)
{
	size_t i;
	Desc.recount(trival);
	for (i = 0; i < trival; i++)
	{
		Desc[i].left = i;
		Desc[i].right = i;
	}
	LeftDim = trival;
	RightDim = trival;
}
void elementwise::build(const size_t Ltrival, const size_t Rtrival)
{
	size_t i, Max;
	Max = (Ltrival > Rtrival ? Ltrival : Rtrival);
	Desc.recount(Max);
	for (i = 0; i < Max; i++)
	{
		Desc[i].left = (Ltrival > i ? i : _uintMax_);
		Desc[i].right = (Rtrival > i ? i : _uintMax_);
	}
	LeftDim = Ltrival;
	RightDim = Rtrival;
}
void elementwise::check(void)
{
	size_t i, MaxL, MaxR;
	array<bool> labelL, labelR;
	MaxL = 0;
	MaxR = 0;
	for (i = 0; i < Desc.count(); i++)
	{
		if (Desc[i].left != _uintMax_)
			MaxL = (MaxL >= Desc[i].left ? MaxL : Desc[i].left);
		if (Desc[i].right != _uintMax_)
			MaxR = (MaxR >= Desc[i].right ? MaxR : Desc[i].right);
		if (Desc[i].left == _uintMax_ && Desc[i].right == _uintMax_)
			throw PikaError("elementwise::check", "L[i] == _uintMax_ && R[i] == _uintMax_", i + 1);
	}
	if ((LeftDim != 0) && (LeftDim != MaxL + 1))
		throw PikaError("elementwise::check", "(LeftDim != 0) && (LeftDim != MaxL + 1)", 1);
	if ((RightDim != 0) && (RightDim != MaxR + 1))
		throw PikaError("elementwise::check", "(RightDim != 0) && (RightDim != MaxR + 1)", 1);

	labelL.Realloc(LeftDim);
	labelL.value(true);
	labelR.Realloc(RightDim);
	labelR.value(true);
	for (i = 0; i < Desc.count(); i++)
	{
		if (Desc[i].left != _uintMax_) labelL[Desc[i].left] = false;
		if (Desc[i].right != _uintMax_) labelR[Desc[i].right] = false;
	}
	for (i = 0; i < LeftDim; i++)
		if (labelL[i]) throw PikaError("elementwise::check", "labelL[i]", i + 1);
	for (i = 0; i < RightDim; i++)
		if (labelR[i]) throw PikaError("elementwise::check", "labelR[i]", i + 1);
	completed = true;
}
void elementwise::backward(const tensor& BackSrc, const elementwise& forward, bool left)
{
	size_t extra, i, offset, temp;
	if (BackSrc.GetOrder() < forward.Desc.count())
		throw PikaError("elementwise::backward(const tensor&, const elementwise&, bool)", "BackSrc.GetOrder() < forward.Desc.count()", 1);

	Desc.recount(BackSrc.GetOrder());
	LeftDim = BackSrc.GetOrder();
	for (i = 0; i < LeftDim; i++)
		Desc[i].left = i;

	extra = LeftDim - forward.Desc.count();
	for (i = 0; i < extra; i++)
		Desc[i + forward.Desc.count()].right = _uintMax_;
	if (left)
	{
		for (i = 0; i < forward.Desc.count(); i++)
			Desc[i].right = forward.Desc[i].right;
		RightDim = forward.RightDim;
	}
	else
	{
		for (i = 0; i < forward.Desc.count(); i++)
			Desc[i].right = forward.Desc[i].left;
		RightDim = forward.LeftDim;
	}


	try
	{
		check();
	}
	catch (PikaError& E)
	{
		throw PikaError(E, "elementwise::(const tensor&, const elementwise&, bool)->");
	}
	completed = true;
}
void elementwise::Set(const elementwise& source)
{
	Desc.copy(source.Desc);
	LeftDim = source.LeftDim;
	RightDim = source.RightDim;
	completed = source.completed;
}
void elementwise::forward(const tensor& ForwardSrcL, const tensor& ForwardSrcR, const elementwise& DescSrc)
{
	size_t extra, i, length;
	if (ForwardSrcL.GetOrder() < DescSrc.LeftDim)
		throw PikaError("elementwise::forward 1", "ForwardSrcL.GetOrder() < DescSrc.LeftDim", 1); 
	if (ForwardSrcR.GetOrder() < DescSrc.RightDim)
		throw PikaError("elementwise::forward 1", "ForwardSrcR.GetOrder() < DescSrc.RightDim", 1);
	
	extra = DescSrc.LeftDim - ForwardSrcL.GetOrder();
	if (DescSrc.RightDim - ForwardSrcR.GetOrder() != extra)
		throw PikaError("elementwise::forward 1", "DescSrc.RightDim - ForwardSrcR.GetOrder() != extra", 1);

	for (i = 0; i < extra; i++)
		if (ForwardSrcL[i + DescSrc.LeftDim] != ForwardSrcR[i + DescSrc.RightDim])
			throw PikaError("elementwise::forward 1", "ForwardSrcL[i + DescSrc.LeftDim]!= ForwardSrcR[i + DescSrc.RightDim]", i);

	length = DescSrc.Desc.count();
	Desc.recount(length + extra);
	for (i = 0; i < length; i++)
	{
		Desc[i].left = DescSrc.Desc[i].left;
		Desc[i].right = DescSrc.Desc[i].right;
	}
	for (i = 0; i < extra; i++)
	{
		Desc[i].left = i + DescSrc.LeftDim;
		Desc[i].right = i + DescSrc.RightDim;
	}
	LeftDim = ForwardSrcL.GetOrder();
	RightDim = ForwardSrcR.GetOrder();
	completed = true;
	check();
	return;
}
void elementwise::forward(const tensor& ForwardSrc, bool left, const elementwise& DescSrc)
{
	size_t extra, i, length, inputDim;
	inputDim = left ? DescSrc.LeftDim : DescSrc.RightDim;
	if (ForwardSrc.GetOrder() < inputDim)
		throw PikaError("elementwise::forward", "ForwardSrc.GetOrder() < inputDim", 1);

	extra = ForwardSrc.GetOrder() - inputDim;

	length = DescSrc.Desc.count();
	Desc.recount(length + extra);
	for (i = 0; i < length; i++)
	{
		Desc[i].left = DescSrc.Desc[i].left;
		Desc[i].right = DescSrc.Desc[i].right;
	}
	for (i = 0; i < extra; i++)
	{
		Desc[i].left = left ? i + DescSrc.LeftDim : _uintMax_;
		Desc[i].right = left ? _uintMax_ : i + DescSrc.RightDim;
	}
	LeftDim = left ? ForwardSrc.GetOrder() : DescSrc.LeftDim;
	RightDim = left ? DescSrc.RightDim : ForwardSrc.GetOrder();
	completed = true;
	check();
	return;
}

condensation::condensation()
{
	completed = false;
}
condensation::~condensation()
{
}
void condensation::build(vector<bool>& input)
{
	size_t i, prefix;
	dummy = 0;
	Desc.copy(input);
	for (i = 0; i < Desc.count(); i++)
	{
		if (Desc[i]) dummy += 1;
	}
	OutSource.recount(Desc.count() - dummy);
	prefix = 0;
	for (i = 0; i < Desc.count(); i++)
		if (!Desc[i])
		{
			OutSource[prefix] = i;
			prefix += 1;
		}
	completed = true;
}
size_t condensation::OutOrder(void)const
{
	return Desc.count() - dummy;
}
void condensation::backward(const tensor& BackSrc, const dispatch& forward)
{
	size_t extra, i;
	if(BackSrc.GetOrder() < forward.Desc.count())
		throw PikaError("condensation::backward", "BackSrc.GetOrder() < forward.Desc.count()", 1);
	extra = BackSrc.GetOrder() - forward.Desc.count();
	Desc.recount(BackSrc.GetOrder());
	for (i = 0; i < extra; i++)
		Desc[i + forward.Desc.count()] = false;
	dummy = 0;
	for (i = 0; i < forward.Desc.count(); i++)
	{
		Desc[i] = (forward.Desc[i] == _uintMax_);
		dummy += (Desc[i] ? 1 : 0);
	}
	OutSource.recount(BackSrc.GetOrder() - dummy);
	
	for (i = 0; i < forward.Desc.count(); i++)
		if (!Desc[i])
			OutSource[forward.Desc[i]] = i;
	for (i = 0; i < extra; i++)
		OutSource[forward.sourceOrder + i] = i + forward.Desc.count();
	completed = true;
}
void condensation::backward(const tensor& BackSrc, const elementwise& forward, bool left)
{
	size_t extra, i, offset, temp;
	if (BackSrc.GetOrder() < forward.Desc.count())
		throw PikaError("condensation::backward(const tensor&, const elementwise&, bool)", "BackSrc.GetOrder() < forward.Desc.count()", 1);
	extra = BackSrc.GetOrder() - forward.Desc.count();
	Desc.recount(BackSrc.GetOrder());
	offset = (left ? forward.LeftDim : forward.RightDim);
	 
	dummy = forward.Desc.count() - offset;
	OutSource.recount(BackSrc.GetOrder() - dummy);
	for (i = 0; i < extra; i++)
	{
		Desc[i + offset] = false;
		OutSource[offset + i] = i + forward.Desc.count();
	}
	for (i = 0; i < forward.Desc.count(); i++)
	{
		temp = (left ? forward.Desc[i].left : forward.Desc[i].right);
		Desc[i] = (temp == _uintMax_);
		if (temp != _uintMax_)
		{
			OutSource[temp] = i;
		}
	}
	completed = true;
}
void condensation::Set(const condensation& source)
{
	Desc.copy(source.Desc);
	OutSource.copy(source.OutSource);
	dummy = source.dummy;
	completed = source.completed;
}
void condensation::forward(const tensor& ForwardSrc, const condensation& DescSrc)
{
	size_t extra, i, length, LL;
	if (DescSrc.Desc.count() < ForwardSrc.GetOrder())
		throw PikaError("condensation::forward", "DescSrc.Desc.count() < ForwardSrc.GetOrder()", DescSrc.Desc.count());
	extra = ForwardSrc.GetOrder() - DescSrc.Desc.count();
	
	length = DescSrc.Desc.count();
	Desc.recount(length + extra);
	for (i = 0; i < length; i++) Desc[i] = DescSrc.Desc[i];
	for (i = 0; i < extra; i++) Desc[i + length] = false;
	
	LL = DescSrc.OutSource.count();
	OutSource.recount(LL + extra);
	for (i = 0; i < LL; i++) OutSource[i] = DescSrc.OutSource[i];
	for (i = 0; i < extra; i++) OutSource[i + LL] = i + length;

	dummy = DescSrc.dummy;
	completed = true;
}


dispatch::dispatch()
{
	completed = false;
}
dispatch::~dispatch()
{
}
void dispatch::build(vector<size_t>& input)
{
	size_t i, count, Max;
	array<bool> label;
	count = 0;
	Max = 0;
	Desc.copy(input);
	for (i = 0; i < Desc.count(); i++)
		if (Desc[i] != _uintMax_)
		{
			Max = Max >= Desc[i] ? Max : Desc[i];
			count += 1;
		}
	if ((count != 0) && (count != Max + 1))
		throw PikaError("dispatch::build", "(count != 0) && count!= Max + 1", 1);
	label.Realloc(count);
	label.value(true);
	for (i = 0; i < Desc.count(); i++)
		if (Desc[i] != _uintMax_) label[Desc[i]] = false;

	for (i = 0; i < count; i++)
		if(label[i]) throw PikaError("dispatch::build", "label[i]", 1);

	sourceOrder = count;

	completed = true;
}
void dispatch::backward(const tensor& BackSrc, const condensation& forward)
{
	size_t extra, i, prefix;
	if(BackSrc.GetOrder() < forward.OutOrder())
		throw PikaError("dispatch::backward", "BackSrc.GetOrder() < forward.OutOrder()", 1);
	extra = BackSrc.GetOrder() - forward.OutOrder();
	sourceOrder = BackSrc.GetOrder();
	
	Desc.recount(extra + forward.Desc.count());
	for (i = 0; i < extra; i++)
	{
		Desc[i + forward.Desc.count()] = forward.OutOrder() + i;
	}
	prefix = 0;
	for (i = 0; i < forward.Desc.count(); i++)
	{
		if (forward.Desc[i])
		{
			Desc[i] = _uintMax_;
		}
	}
	for (i = 0; i < forward.OutSource.count(); i++)
	{
		Desc[forward.OutSource[i]] = i;
	}
	completed = true;
}
void dispatch::Set(const dispatch& source)
{
	Desc.copy(source.Desc);
	sourceOrder = source.sourceOrder;
	completed = source.completed;
}
void dispatch::forward(const tensor& ForwardSrc, const dispatch& DescSrc)
{
	size_t extra, i, length;
	length = DescSrc.Desc.count();
	if (DescSrc.sourceOrder < ForwardSrc.GetOrder())
		throw PikaError("dispatch::forward", "DescSrc.sourceOrder < ForwardSrc.GetOrder()", DescSrc.sourceOrder);
	extra = ForwardSrc.GetOrder() - DescSrc.sourceOrder;
	sourceOrder = DescSrc.sourceOrder + extra;
	Desc.recount(length + extra);
	for (i = 0; i < length; i++) Desc[i] = DescSrc.Desc[i];
	for (i = 0; i < extra; i++)
		Desc[i + length] = DescSrc.sourceOrder + i;

	completed = true;
}
void dispatch::forward(const tensor& ForwardSrc, const elementwise& DescSrc, bool left)
{
	size_t extra, i, length, inputDim;
	inputDim = left ? DescSrc.LeftDim : DescSrc.RightDim;
	if (ForwardSrc.GetOrder() < inputDim)
		throw PikaError("elementwise::forward 1", "ForwardSrc.GetOrder() < inputDim", 1);
	extra = ForwardSrc.GetOrder() - inputDim;

	length = DescSrc.Desc.count();
	Desc.recount(length + extra);
	for (i = 0; i < length; i++)
		Desc[i] = left ? DescSrc.Desc[i].left : DescSrc.Desc[i].right;
	for (i = 0; i < extra; i++)
		Desc[length + i] = inputDim + i;
	
	sourceOrder = inputDim + extra;
	completed = true;
}
























