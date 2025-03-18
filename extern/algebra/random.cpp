#include"random.h"
static double Pi = 3.1415926535897932384626;
static int num_thread = 0;
int HYPER_random::HYPER_seed = 177749;
int HYPER_random::A;
int HYPER_random::B;
int HYPER_random::Q;
int HYPER_random::R;
int HYPER_random::HYPER_length;
double HYPER_random::reciprocal = set_length();
void HYPER_random::set_seed(int seed)
{
	HYPER_seed = seed;
}
int HYPER_random::rand(void)
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
double HYPER_random::set_length(void)
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
void HYPER_random::set_parameter(int a, int b)
{
	A = a;
	B = b;
	Q = HYPER_length / A;
	R = HYPER_length % A;
	return;
}
double HYPER_random::rand(double lower, double upper)
{
	double core;
	core = (double)rand() * reciprocal;
	core *= (upper - lower);
	core += lower;
	return core;
}
int HYPER_random::judge(double probability)
{
	double temp;
	temp = rand(0.0, 1.0);
	return (temp <= probability);
}
int HYPER_random::select(int N)
{
	double k;
	k = rand(0.0, (double)N);
	N = (int)k + 1;
	return N;
}
int HYPER_random::rand(int down_close, int up_open)
{
	int length;
	int rand_result;
	length = up_open - down_close;
	if (length < 1) return down_close;
	rand_result = select(length) % length;
	return rand_result + down_close;
}

void HYPER_random::Rand(double lower, double upper, double* vector, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++) 
		vector[i] = rand(lower, upper);
}
void HYPER_random::Rand(double lower, double upper, double* mat, size_t ld, size_t row, size_t column)
{
	size_t i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			mat[i * ld + j] = rand(lower, upper);
}



