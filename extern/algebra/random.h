#ifndef _RANDOM___H_
#define _RANDOM___H_
#include<stdlib.h>
class HYPER_random
{
public:
	HYPER_random() {}
	~HYPER_random() {}
	void set_seed(int seed);
	void set_parameter(int a, int b);
	int rand(void);
	double rand(double lower, double upper);
	int judge(double probability);
	int select(int N);
	int rand(int down_close, int up_open);

	void Rand(double lower, double upper, double* vector, size_t length);
	void Rand(double lower, double upper, double* mat, size_t ld, size_t row, size_t column);
private:
	static int HYPER_seed;
	static int HYPER_length;
	static int A;
	static int B;
	static int Q;
	static int R;
	static double reciprocal;
	static double set_length(void);
};



#endif
