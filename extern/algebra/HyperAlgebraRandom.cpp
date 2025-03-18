#include"HyperAlgebra.h"
//#include<stdio.h>
//#include<stdlib.h>
#include<cmath>

using namespace HyperAlgebra;


static double Pi = 3.1415926535897932384626;
static int num_thread = 0;

int SimpleRandom::HYPER_seed = 177749;
int SimpleRandom::A;
int SimpleRandom::B;
int SimpleRandom::Q;
int SimpleRandom::R;
int SimpleRandom::HYPER_length;
double SimpleRandom::reciprocal = set_length();
void SimpleRandom::SetSeed(int seed)
{
	HYPER_seed = seed;
}
int SimpleRandom::rand(void)
{
	int seed;
	int temp;
	seed = HYPER_seed;
	temp = (seed / Q) * R;
	seed -= ((seed / Q) * Q);
	seed *= A;
	seed -= temp;
	seed = (seed < 0 ? seed : seed - HYPER_length);
	seed += B;
	seed = (seed < 0 ? seed + HYPER_length : seed);
	HYPER_seed = seed;
	return seed;
}
double SimpleRandom::set_length(void)
{
	int i, length, limit;
	double L;
	length = 1;
	limit = 8 * sizeof(int) - 1;
	for (i = 1; i < limit; i++)
		length *= 2;
	length--;
	length *= 2;
	length++;

	A = 16870;
	B = 0;
	Q = length / A;
	R = length % A;
	HYPER_length = length;
	L = (double)length;
	return 1.0 / L;
}
void SimpleRandom::SetParameter(int a, int b)
{
	A = a;
	B = b;
	Q = HYPER_length / A;
	R = HYPER_length % A;
	return;
}
double SimpleRandom::rand(double lower, double upper)
{
	double core;
	core = (double)rand() * reciprocal;
	core *= (upper - lower);
	core += lower;
	return core;
}
int SimpleRandom::judge(double probability)
{
	double temp;
	temp = rand(0.0, 1.0);
	return (temp <= probability);
}
int SimpleRandom::select(int N)
{
	double k;
	k = rand(0.0, (double)N);
	N = (int)k + 1;
	return N;
}
int SimpleRandom::rand(int down_close, int up_open)
{
	int length;
	int rand_result;
	length = up_open - down_close;
	if (length < 1) return down_close;
	rand_result = select(length) % length;
	return rand_result + down_close;
}

void SimpleRandom::Rand(double lower, double upper, double* vector, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++) 
		vector[i] = rand(lower, upper);
}
void SimpleRandom::Rand(double lower, double upper, double* mat, size_t ld, size_t row, size_t column)
{
	size_t i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			mat[i * ld + j] = rand(lower, upper);
}


SimpleRandomLocal::SimpleRandomLocal()
{
    int i, length, limit;
	double L;
	length = 1;
	limit = 8 * sizeof(int) - 1;
	for (i = 1; i < limit; i++)
		length *= 2;
	length--;
	length *= 2;
	length++;

	A = 16870;
	B = 0;
	Q = length / A;
	R = length % A;
	HYPER_length = length;
	L = (double)length;
	reciprocal =  1.0 / L;

    HYPER_seed = 177749;
}
SimpleRandomLocal::~SimpleRandomLocal()
{

}
void SimpleRandomLocal::SetSeed(int seed)
{
	HYPER_seed = seed;
}
int SimpleRandomLocal::rand(void)
{
	int seed;
	int temp;
	seed = HYPER_seed;
	temp = (seed / Q) * R;
	seed -= ((seed / Q) * Q);
	seed *= A;
	seed -= temp;
	seed = (seed < 0 ? seed : seed - HYPER_length);
	seed += B;
	seed = (seed < 0 ? seed + HYPER_length : seed);
	HYPER_seed = seed;
	return seed;
}
void SimpleRandomLocal::SetParameter(int a, int b)
{
	A = a;
	B = b;
	Q = HYPER_length / A;
	R = HYPER_length % A;
	return;
}
double SimpleRandomLocal::rand(double lower, double upper)
{
	double core;
	core = (double)rand() * reciprocal;
	core *= (upper - lower);
	core += lower;
	return core;
}
int SimpleRandomLocal::judge(double probability)
{
	double temp;
	temp = rand(0.0, 1.0);
	return (temp <= probability);
}
int SimpleRandomLocal::select(int N)
{
	double k;
	k = rand(0.0, (double)N);
	N = (int)k + 1;
	return N;
}
int SimpleRandomLocal::rand(int down_close, int up_open)
{
	int length;
	int rand_result;
	length = up_open - down_close;
	if (length < 1) return down_close;
	rand_result = select(length) % length;
	return rand_result + down_close;
}

void SimpleRandomLocal::Rand(double lower, double upper, double* vector, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++) 
		vector[i] = rand(lower, upper);
}
void SimpleRandomLocal::Rand(double lower, double upper, double* mat, size_t ld, size_t row, size_t column)
{
	size_t i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			mat[i * ld + j] = rand(lower, upper);
}



