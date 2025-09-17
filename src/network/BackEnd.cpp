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

void static AppendFile(FILE* fpSrc, FILE* fpDst)
{
	if (fpSrc == NULL || fpDst == NULL)
	{
		return;
	}
	// 将fpDst的文件指针移到末尾
	//fseek(fpDst, 0, SEEK_END);

	char buffer[4096];
	size_t n;
	while ((n = fread(buffer, 1, sizeof(buffer), fpSrc)) > 0)
	{
		fwrite(buffer, 1, n, fpDst);
	}
}
void ThrowErrorFO(const char* location, const char* filename)
{
	hyperlex::dictionary* err;
	err = new hyperlex::dictionary;
	err->append("location", location);
	err->append("path", filename);
	err->append("error", "failure open");
	throw err;
}
void static AppendFile(const char* location, const char* path, FILE* fpDst)
{
	FILE* fpSrc = fopen(path, "r");
	if (fpSrc == NULL)
	{
		ThrowErrorFO(location, path);
	}
	AppendFile(fpSrc, fpDst);
	fclose(fpSrc);
}

static void PrintBegin(FILE* fp);
static void PrintEnd(FILE* fp);
static void PrintConstant(NetWork* net, FILE* fp);


int BackEnd::CPUbackEnd(NetWork* net, FILE* fp)
{
	AppendFile("BackEnd::CPUbackEnd", "../data/material/all.cpp", fp);
	PrintConstant(net, fp);
	

	AppendFile("BackEnd::CPUbackEnd", "../data/material/CPUcode.cpp", fp);
	return 0;
}
int BackEnd::CUDAbackEnd(NetWork* net, FILE* fp)
{
	return 0;
}

static void PrintBegin(FILE* fp)
{
	fprintf(fp, "#include <BackEnd.h>\n");
	fprintf(fp, "using namespace example;\n");
}
static void PrintEnd(FILE* fp)
{
	//fprintf(fp, "}\n");
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















