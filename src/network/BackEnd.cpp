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


int BackEnd::CPUbackEnd(NetWork* net, FILE* fp)
{
	return 0;
}
int BackEnd::CUDAbackEnd(NetWork* net, FILE* fp)
{
	return 0;
}
















