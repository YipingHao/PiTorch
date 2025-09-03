#include"../header/Pikachu.h"
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

enum BackEndType
{
	unknown,
	CPU,
	CUDA,
};

static bool compare(const char* str1, const char* str2)
{
	size_t i;
	for (i = 0; (str1[i] != '\0') && (str1[i] == str2[i]); i++);
	return str1[i] == str2[i];
}

static BackEndType BackEndGet(const char* name)
{
	if (compare(name, "CPU")) return CPU;
	if (compare(name, "CUDA")) return CUDA;
	return unknown;
}

BackEnd::BackEnd()
{
}
BackEnd::~BackEnd()
{
}
int BackEnd::build(const char* machine, NetWork* net, const char* output)
{
	hyperlex::FilePath FileName;
	FileName.build(output);
	FILE* fp = fopen(FileName.path(), "w");
	if (fp == NULL)
	{
		hyperlex::dictionary* error;
		error = new  hyperlex::dictionary;
		error->append("location", "BackEnd::build");
		error->append("path", output); 
		error->append("RecognitedPath", FileName.path());
		error->append("error", "failure open");
		throw error;
	}
	BackEndType type = BackEndGet(machine);
	switch (type)
	{
	case CPU:
		return CPUbackEnd(net, fp);
	case CUDA:
		return CUDAbackEnd(net, fp);
	default:
	{
		hyperlex::dictionary* error;
		error = new  hyperlex::dictionary;
		error->append("location", "BackEnd::build");
		error->append("machine", machine);
		error->append("error", "unknown machine");
		throw error;
	}
	}
	return 0;
}
namespace example//CPU back end example
{
	size_t ParameterCount = 12;
	size_t OutputCount = 48;
	size_t InputCount = 36;

	// 计算整个神经网络的前向传播,包括用户定义的神经网络输出对输入导数的计算
	void compute(size_t count, const double* input, const double* parameter, double* output);
	// 计算神经网络的原始输出,不包括用户定义的神经网络输出对输入导数的计算
	void computeOringinal(size_t count, const double* input, const double* parameter, double* output);
	// 计算神经网络的损失梯度,包括用户定义的神经网络输出对输入导数的计算
	void computeGradient(size_t count, const double* input, const double* parameter, const double* outputGrad, double* inputGrad, double* parameterGrad);
}
/*

*/
static void PrintBegin(FILE* fp);
static void PrintEnd(FILE* fp);
static void PrintConstant(NetWork* net, FILE* fp);


int BackEnd::CPUbackEnd(NetWork* net, FILE* fp)
{
	PrintBegin(fp);
	PrintConstant(net, fp);

	PrintEnd(fp);
	return 0;
}
int BackEnd::CUDAbackEnd(NetWork* net, FILE* fp)
{
	return 0;
}

static void PrintBegin(FILE* fp)
{
	fprintf(fp, "namespace example\n{\n");
}
static void PrintEnd(FILE* fp)
{
	fprintf(fp, "}\n");
}
static void PrintConstant(NetWork* net, FILE* fp)
{
	fprintf(fp, "\tconst size_t ParameterCount = %zu;\n", net->ParameterCount());
	fprintf(fp, "\tconst size_t OutputCount = %zu;\n", net->OutputCount());
	fprintf(fp, "\tconst size_t InputCount = %zu;\n", net->InputCount());
	fprintf(fp, "\n");
	
	fprintf(fp, "\tvoid compute(size_t count, const double* input, const double* parameter, double* output);\n");
	fprintf(fp, "\tvoid computeOringinal(size_t count, const double* input, const double* parameter, double* output);\n");


}















