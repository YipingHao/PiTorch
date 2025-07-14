#include"../header/Pikachu.h"
using namespace Pikachu;
#include<cmath>

manifold::manifold()
{
}
manifold::~manifold()
{
}
void manifold::OutputAppned(size_t X1, size_t X2, operation OP)
{
	size_t i, now, in_;
	node* here, * New;

	for (i = 0; i < formula.capacity(); i++)
	{
		if (!formula[i].IfValid()) continue;
		here = formula[i].content;
		if (here->Type == _LeafX_ && here->src1 == X1 && here->src2 == X2) break;
	}
	if (i < formula.capacity()) in_ = i;
	else
	{
		New = new node();
		New->Type = _LeafX_;
		New->src1 = X1;
		New->src2 = X2;
		in_ = formula.MoveAppend(New);
	}
	New = new node(OP);
	now = formula.MoveAppend(New);
	formula.append(in_, output[0], now);
	output[0] = now;
}
void manifold::Backdiff(size_t dx, size_t y, const manifold* in)
{
	copy(*in);
	differetial(0, dx, true);
	OutputAppned(1, y, _mul_);
	return;
}
manifold* manifold::MonoForward(size_t y, vector<size_t>& OutputDim) const
{
	manifold* here, now;
	size_t i, j;
	for (i = 0; i < InputDim.count(); i++)
	{
		for (j = 0; j < InputDim[i]; j++)
		{
			now.copy(*this);
			now.differetial(i, j, true);
			now.InputExpand(0);
			now.OutputAppned(i + 1, 0, _add_);
			if (here == NULL)
			{
				here = new manifold;
				here->copy(now);
			}
			else
			{
				here->elementwise(now, _add_);
			}
		}
	}
	return here;
}
manifold* manifold::DiForward(size_t y, vector<size_t>& OutputDim) const
{

}
bool manifold::Simplify(void)
{
	bool changed_;
	size_t round_;
	round_ = 0;
	do
	{
		round_ += 1;
		changed_ = false;
		changed_ = changed_ || Simplify02();
		changed_ = changed_ || Simplify01();
		changed_ = changed_ || Simplify03();


	} while (changed_);
	changed_ = changed_ || Simplify05();
	if (round_ > 1)
	{

	}
	return round_ > 1;
}



manifolds::manifolds()
{
	size_t i;
	mono = false;
	InitialOutDim = 0;
	InitialInDim = 0;
	XDim = 0;

	
}
manifolds::~manifolds()
{
}
void manifolds::ResetStorage(const vector<manifold*>& source, bool copy)
{
	size_t i;
	for (i = 0; i < storage.count(); i++)
		delete storage[i];
	storage.recount(source.count());
	if (copy)
	{
		for (i = 0; i < source.count(); i++)
		{
			storage[i] = new manifold();
			storage[i]->copy(*(source[i]));
		}
	}
	else
	{
		for (i = 0; i < source.count(); i++)
			storage[i] = source[i];
	}
}
void manifolds::backward(void)
{
	size_t i, j;
	vector<manifold*> temp;
	manifold sum, now;
	if (InputDim.count() > 1 || !mono)
		throw PikaError("manifold::backward", "(InputDim.count() >1) ", InputDim.count());

	mono = true;

	InputDim.append(InitialOutDim);
	OutputDim[0] = InitialInDim;
	temp.recount(InitialInDim);
	for (i = 0; i < InitialInDim; i++)
	{
		sum.Backdiff(i, 0, temp[0]);
		for (j = 1; j < InitialOutDim; j++)
		{
			now.Backdiff(i, j, temp[j]);
			sum.elementwise(now, _add_);
		}
		sum.InputExpand(InitialOutDim);
		temp[i] = new manifold();
		temp[i]->copy(sum);
	}
	ResetStorage(temp, false);
}
void manifolds::copy(const manifolds& source)
{
	size_t i;
	mono = source.mono;
	InitialOutDim = source.InitialOutDim;
	InitialInDim = source.InitialInDim;
	XDim = source.XDim;

	OutputDim.copy(source.OutputDim);
	InputDim.copy(source.InputDim);

	ResetStorage(source.storage, true);
}
void manifolds::forward(size_t Xin)
{
	XDim = Xin;
	forward();
	return;
}
void manifolds::forward(void)
{
	if (OutputDim.count() >= (mono + 2))
		throw PikaError("manifolds::forward", "(!mono) + OutputDim.count()) >= 3", OutputDim.count());
	if (XDim == 0)
		throw PikaError("manifolds::forward", "XDim == 0", (size_t)this);
	if (mono)
		ForwardMono();
	else
		ForwardBi();
}
void manifolds::StackNext(vector<size_t>&stack, long long int& top, const long long int label, bool& delta)const
{
	while (top != -1)
	{
		if (top == label)
		{
			delta = false;
			top -= 1;
			return;
		}
		else
		{
			if (delta)
			{
				stack[top] = 0;
				top += 1;
			}
			else
			{
				stack[top] += 1;
				delta = (stack[top] != OutputDim[top]);
				top += delta ? 1 : -1;
			}
		}
	}
}
void manifolds::ForwardMono(void)
{
	size_t count__;
	vector<size_t> stack;
	long long int top, label;
	bool delta;
	vector<manifold*> temp;
	size_t SiteSrc, i;
	manifold sum, now;
	count__ = InputDim.count();
	InputDim.append(InputDim[count__ - 1] * XDim);
	OutputDim.append(XDim);

	stack.recount(OutputDim.count());
	top = 0;
	label = OutputDim.count();
	delta = true;
	do
	{
		StackNext(stack, top, label, delta);
		if (top == -1) break;
		SiteSrc = stack[0];
		for (i = 1; i + 1 < label; i++)
		{
			SiteSrc *= OutputDim[i];
			SiteSrc += stack[i];
		}
		






	} while (true);
	ResetStorage(temp, false);
	return;
}
void manifolds::ForwardBi(void)
{

}

cluster::cluster()
{
}
cluster::~cluster()
{
}
void cluster::differential(void)
{
	size_t count, i;
	vector<manifold*> temp;
	vector<size_t> stack;
	size_t SiteSrc, SiteDst;
	bool next;
	long long int label;
	OutputDim.append(InitialInDim);
	count = 1;
	for (i = 0; i < OutputDim.count(); i++)
		count *= OutputDim[i];

	temp.recount(count);
	stack.recount(OutputDim.count());
	stack.value(0);
	label = OutputDim.count();
	do
	{
		SiteSrc = stack[0];
		for (i = 1; i + 1 < label; i++)
		{
			SiteSrc *= OutputDim[i];
			SiteSrc += stack[i];
		}
		SiteDst = SiteSrc * OutputDim[label - 1] + stack[label - 1];
		temp[SiteDst] = new manifold;
		temp[SiteDst]->copy(*(storage[SiteSrc]));
		temp[SiteDst]->differetial(0, stack[label - 1], true);
		temp[SiteDst]->Simplify();
		next = StackNext(stack, label);
	} while (next);

	ResetStorage(temp, false);
}
void cluster::copy(const cluster& source)
{
	InitialOutDim = source.InitialOutDim;
	InitialInDim = source.InitialInDim;
	OutputDim.copy(source.OutputDim);
	ResetStorage(source.storage, true);
}

size_t cluster::GetOrder(void) const
{
	return OutputDim.count();
}
size_t cluster::GetDim(size_t No) const
{
	return OutputDim[No];
}

void cluster::ResetStorage(const vector<manifold*>& source, bool copy)
{
	size_t i;
	for (i = 0; i < storage.count(); i++)
		delete storage[i];
	storage.recount(source.count());
	if (copy)
	{
		for (i = 0; i < source.count(); i++)
		{
			storage[i] = new manifold();
			storage[i]->copy(*(source[i]));
		}
	}
	else
	{
		for (i = 0; i < source.count(); i++)
			storage[i] = source[i];
	}
}
void cluster::StackNext(vector<size_t>& stack, long long int& top, const long long int label, bool& delta)const
{
	while (top != -1)
	{
		if (top == label)
		{
			delta = false;
			top -= 1;
			return;
		}
		else
		{
			if (delta)
			{
				stack[top] = 0;
				top += 1;
			}
			else
			{
				stack[top] += 1;
				delta = (stack[top] != OutputDim[top]);
				top += delta ? 1 : -1;
			}
		}
	}
}
bool cluster::StackNext(vector<size_t>& stack, const long long int label)const
{
	long long int top;
	bool delta;
	delta = false;
	top = label - 1;
	for (top = label - 1; top >= 0; top--)
	{
		stack[top] += 1;
		if (stack[top] != OutputDim[top]) break;
	}
	if (top == -1) return false;
	for (top += 1; top < label; top++) stack[top] = 0;
	return true;
}
/*

	class manifolds
	{
	public:
		manifolds();
		~manifolds();
		void backward(void);
		//void forward(size_t No, );
	protected:
		size_t count;//output Count
		vector <size_t> InputDim;
		vector<manifold*> storage;
		// count = output count

	};
manifolds::manifolds()
{
}
manifolds::~manifolds()
{
}
void manifolds::backward(void)
{
	size_t i, j;
	vector<manifold*> temp;
	manifold sum, now;
	if (InputDim.count() > 1)
		throw PikaError("manifold::backward", "(InputDim.count() >1) ", InputDim.count());
	InputDim.append(count);
	count = InputDim[0];
	temp.recount(count);
	for (i = 0; i < count; i++)
	{
		sum.Backdiff(i, 0, temp[0]);
		for (j = 1; j < InputDim[1]; j++)
		{
			now.Backdiff(i, j, temp[j]);
			sum.elementwise(now, _add_);
		}
	}
	for (i = 0; i < storage.count(); i++)
		delete storage[i];
	storage.recount(count);
	for (i = 0; i < count; i++)
		storage[i] = temp[i];
}

*/


MonoFunc::MonoFunc()
{
	InputDim = 0;
	OutputDim = 0;
	order = 0;

	OutputFusion = true;
}
MonoFunc::~MonoFunc()
{
	clear();
}
void MonoFunc::build(Expres* source)
{
	configurations Config;
	OutputDim = source->OutputAmount();
	InputDim = source->InputCount();
	OutputFusion = Config.OutputFusion(source->NodeCount()) || OutputDim == 1;
	if (OutputFusion)
	{
		Expres* dst = new Expres;
		dst->copy(*source);
		cluster.recount(1);
		cluster[0] = dst;
	}
	else
	{
		cluster.recount(OutputDim);
		for (size_t i = 0; i < OutputDim; i++)
		{
			cluster[i] = new Expres;
			cluster[i]->copy(*source);
			cluster[i]->ShrinkOutput(i);//
			cluster[i]->Simplify();
		}
	}
	dims.recount(1);
	dims[0] = OutputDim;
}
void MonoFunc::clear(void)
{
	for (size_t i = 0; i < cluster.count(); i++)
	{
		delete cluster[i];
	}
	cluster.clear();
	dims.clear();
	InputDim = 0;
	OutputDim = 0;
	OutputFusion = true;
	order = 0;
}
void MonoFunc::differential(void)
{
	order += 1;
	if (InputDim == 1)
	{
		for (size_t i = 0; i < cluster.count(); i++)
		{
			cluster[i]->differetial(0, 0, true);
		}
	}
	else
	{
		vector<Expres*>primitive;
		Expres* temp;
		size_t oldDim = cluster.count();
		primitive.recount(oldDim);
		for (size_t i = 0; i < oldDim; i++) primitive[i] = cluster[i];
		cluster.recount(oldDim * InputDim);
		for (size_t i = 0; i < oldDim; i++)
		{
			for (size_t j = 0; j < InputDim; j++)
			{
				temp = new Expres;
				temp->copy(*primitive[i]);
				temp->differetial(0, j, true);
				temp->Simplify();
				cluster[i * InputDim + j] = temp;
			}
		}
		for (size_t i = 0; i < oldDim; i++) delete primitive[i];
		dims.append(InputDim);
	}
}
void MonoFunc::copy(const MonoFunc& source)
{
	OutputFusion = source.OutputFusion;
	OutputDim = source.OutputDim;
	InputDim = source.InputDim;
	order = source.order;

	dims.copy(source.dims);
	cluster.recount(source.cluster.count());
	for (size_t i = 0; i < cluster.count(); i++)
	{
		cluster[i] = new Expres();
		cluster[i]->copy(*(source[i]));
	}
}
void MonoFunc::demo(FILE* fp) const
{
	fprintf(fp, "MonoFunc: OutputDim = %zu, InputDim = %zu, ", OutputDim, InputDim);
	fprintf(fp, "Order = %zu, OutputFusion = %s\n", order, OutputFusion ? "true" : "false");
	for (size_t i = 0; i < dims.count(); i++)
	{

	}
	if (InputDim == 1 || order == 0)
	{
		for (size_t i = 0; i < cluster.count(); i++)
		{
			fprintf(fp, "Function %zu:\n", i);
			cluster[i]->demo(fp);
		}
	}
	else 
	{
		vector<size_t> indice;
		indice.recount(order);
		for (size_t i = 0; i < cluster.count(); i++)
		{
			// Calculate the indices for the current function
			/*
			
			*/
			size_t index = i;
			for (size_t j = 0; j < order; j++)
			{
				indice[order - j - 1] = index % InputDim;
				index /= InputDim;
			}
			if (OutputFusion || OutputDim == 1)
			{
				fprintf(fp, "No[%zu] diff:", i);
			}
			else
			{
				fprintf(fp, "No[%zu] diff[%zu]:", i, index);
			}
			for (size_t j = 0; j < order; j++)
			{
				fprintf(fp, "[%zu]", indice[j]);
			}
			fprintf(fp, "\n");
			cluster[i]->demo(fp);
		}
	}
}

DiFunc::DiFunc()
{
	OutputFusion = true;
	OutputDim = 0;
	InputDim = 0;
	ParameterDim = 0;
	order = 0;

}
DiFunc::~DiFunc()
{
	for (size_t i = 0; i < cluster.count(); i++)
	{
		delete cluster[i];
	}
	for (size_t i = 0; i < original.count(); i++)
	{
		delete original[i];
	}
}
void DiFunc::diffX(void)
{
	order += 1;
	if (InputDim == 1)
	{
		for (size_t i = 0; i < cluster.count(); i++)
		{
			cluster[i]->differetial(0, 0, true);
		}
	}
	else
	{
		vector<Expres*>primitive;
		Expres* temp;
		size_t oldDim = cluster.count();
		primitive.recount(oldDim);
		for (size_t i = 0; i < oldDim; i++) primitive[i] = cluster[i];
		cluster.recount(oldDim * InputDim);
		for (size_t i = 0; i < oldDim; i++)
		{
			for (size_t j = 0; j < InputDim; j++)
			{
				temp = new Expres;
				temp->copy(*primitive[i]);
				temp->differetial(0, j, true);
				temp->Simplify();
				cluster[i * InputDim + j] = temp;
			}
		}
		for (size_t i = 0; i < oldDim; i++) delete primitive[i];
		dims.append(InputDim);
	}
}
void DiFunc::differential(bool X)
{
	order += 1;
	diffInfor.append(X);
	if (X)
	{
		if (InputDim == 1)
		{
			for (size_t i = 0; i < cluster.count(); i++)
			{
				cluster[i]->differetial(0, 0, true);
			}
		}
		else
		{
			vector<Expres*>primitive;
			Expres* temp;
			size_t oldDim = cluster.count();
			primitive.recount(oldDim);
			for (size_t i = 0; i < oldDim; i++) primitive[i] = cluster[i];
			cluster.recount(oldDim * InputDim);
			for (size_t i = 0; i < oldDim; i++)
			{
				for (size_t j = 0; j < InputDim; j++)
				{
					temp = new Expres;
					temp->copy(*primitive[i]);
					temp->differetial(0, j, true);
					temp->Simplify();
					cluster[i * InputDim + j] = temp;
				}
			}
			for (size_t i = 0; i < oldDim; i++) delete primitive[i];
			dims.append(InputDim);
		} 
		
	}
	else
	{
		if (ParameterDim == 1)
		{
			for (size_t i = 0; i < cluster.count(); i++)
			{
				cluster[i]->differetial(0, 0, true);
			}
		}
		else
		{
			vector<Expres*>primitive;
			Expres* temp;
			size_t oldDim = cluster.count();
			primitive.recount(oldDim);
			for (size_t i = 0; i < oldDim; i++) primitive[i] = cluster[i];
			cluster.recount(oldDim * ParameterDim);
			for (size_t i = 0; i < oldDim; i++)
			{
				for (size_t j = 0; j < ParameterDim; j++)
				{
					temp = new Expres;
					temp->copy(*primitive[i]);
					temp->differetial(0, j, false);
					//
					temp->Simplify();
					cluster[i * ParameterDim + j] = temp;
				}
			}
			for (size_t i = 0; i < oldDim; i++) delete primitive[i];
			dims.append(ParameterDim);
		}
	
	}
}
void DiFunc::copy(const DiFunc& source)
{
	OutputFusion = source.OutputFusion;
	OutputDim = source.OutputDim;
	InputDim = source.InputDim;
	ParameterDim = source.ParameterDim;
	order = source.order;

	diffInfor.copy(source.diffInfor);
	dims.copy(source.dims);
	cluster.recount(source.cluster.count());
	for (size_t i = 0; i < cluster.count(); i++)
	{
		cluster[i] = new Expres();
		cluster[i]->copy(*(source[i]));
	}
	for (size_t i = 0; i < original.count(); i++)
	{
		original[i] = new Expres();
		original[i]->copy(*(source.original[i]));
	}
}
void DiFunc::clear(void)
{
	for (size_t i = 0; i < cluster.count(); i++)
	{
		delete cluster[i];
	}
	cluster.clear();
	dims.clear();
	InputDim = 0;
	OutputDim = 0;
	ParameterDim = 0;
	OutputFusion = true;
	order = 0;
	for (size_t i = 0; i < original.count(); i++)
	{
		delete original[i];
	}
	original.clear();
	diffInfor.clear();
}
void DiFunc::demo(FILE* fp) const
{
	fprintf(fp, "DiFunc: OutputDim = %zu, InputDim = %zu, ParameterDim = %zu\n", OutputDim, InputDim, ParameterDim);
	fprintf(fp, "Order = %zu, OutputFusion = %s\n", order, OutputFusion ? "true" : "false");
	if (InputDim == 1 || order == 0)
	{
		for (size_t i = 0; i < cluster.count(); i++)
		{
			fprintf(fp, "Function %zu:\n", i);
			cluster[i]->demo(fp);
		}
		return;
	}
	vector<size_t> indice;
	indice.recount(order);
	for (size_t i = 0; i < cluster.count(); i++)
	{
		fprintf(fp, "No[%zu] diff:", i);
		size_t index = i;
		for (size_t j = 0; j < order; j++)
		{
			indice[order - j - 1] = index % (diffInfor[j] ? InputDim : ParameterDim);
			index /= (diffInfor[j] ? InputDim : ParameterDim);
		}
		for (size_t j = 0; j < order; j++)
		{
			fprintf(fp, "[%zu]", indice[j]);
		}
		fprintf(fp, "\n");
		cluster[i]->demo(fp);
	}
	for (size_t i = 0; i < cluster.count(); i++)
	{
		fprintf(fp, "Function %zu:\n", i);
		cluster[i]->demo(fp);
	}
}
void DiFunc::build(Expres* source)
{
	configurations Config;
	OutputDim = source->OutputAmount();
	InputDim = source->InputCount();
	ParameterDim = source->ParameterAmount();
	OutputFusion = Config.OutputFusion(source->NodeCount()) || OutputDim == 1;

	dims.recount(1);
	dims[0] = OutputDim;

	if (OutputFusion)
	{
		Expres* dst = new Expres;
		dst->copy(*source);
		original.recount(1);
		original[0] = dst;
	}
	else
	{
		original.recount(OutputDim);
		for (size_t i = 0; i < OutputDim; i++)
		{
			original[i] = new Expres;
			original[i]->copy(*source);
			original[i]->differetial(0, i, true);
			original[i]->Simplify();
		}
	}
	cluster.recount(original.count());
	for (size_t i = 0; i < original.count(); i++)
	{
		Expres* dst = new Expres;
		dst->copy(*(original[i]));
		cluster[i] = dst;
	}
}


