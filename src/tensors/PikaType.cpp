#include"Pikachu.h"
using namespace Pikachu;

#ifndef _uintMax_
#define _uintMax_ 0xffffffffffffffff
#endif

#ifdef UnderDebugMode

void PrintDebug(FILE* fp)
{
#ifdef Debug01
	fprintf(fp, "Debug01:\n");
	fprintf(fp, "\tvoid NeuralNetwork::TopologicalSortingBack(vector<size_t>& sequence)const\n");
#endif // Debug01

}
#endif // UnderDebugMode




PikaString::PikaString()
{
}
PikaString::~PikaString()
{
}
void PikaString::operator<<(FILE* fp)
{
	while (feof(fp) == 0)
		append((const char)getc(fp));
}
void PikaString::operator=(const char* input)
{
	size_t i;
	Head = 0;
	Rear = 0;
	for (i = 0; input[i] != '\0'; i++) append(input[i]);
}
void PikaString::operator+=(const char* input)
{
	size_t i;
	for (i = 0; input[i] != '\0'; i++) append(input[i]);
}
void PikaString::operator+=(long long int source)
{
	size_t i;
	long long int r, ele, top;
	char stack[32];
	ele = source;
	if (source < 0)
	{
		ele = -ele;
		append('-');
	}
	if (ele == 0) append('0');
	top = 0;
	while (ele != 0)
	{
		r = ele % 10;
		ele = ele / 10;
		stack[top] = ((char)r) + '0';
		top += 1;
	}
	while (top != 0)
	{
		top -= 1;
		append(stack[top]);
	}
}
#include<cmath>
void PikaString::operator+=(double source)
{
	double x = 123.456;
	double mantissa;
	int exponent, top, r;
	char stack[32];
	mantissa = std::frexp(source, &exponent);
	if (mantissa < 0)
	{
		mantissa = -mantissa;
		append('-');
	}
	append((char)((int)mantissa) + '0');
	mantissa = (mantissa - (double)((int)mantissa))* 10.0;
	append('.');
	for (top = 0; top < 16; top++)
	{
		append((char)((int)mantissa) + '0');
		mantissa = (mantissa - (double)((int)mantissa)) * 10.0;
	}
	*this += " * 2^{";
	if (exponent < 0)
	{
		exponent = -exponent;
		append('-');
	}
	if (exponent == 0) append('0');
	top = 0;
	while (exponent != 0)
	{
		r = exponent % 10;
		exponent = exponent / 10;
		stack[top] = ((char)r) + '0';
		top += 1;
	}
	while (top != 0)
	{
		top -= 1;
		append(stack[top]);
		
	}
	append('}');
}




char* PikaString::array(void)
{
	append('\0');
	return content + Head;
}
char* PikaString::CopyVector(void) const
{
	char* Newchar;
	size_t i;
	Newchar = (char*)malloc(sizeof(char) * (Rear - Head + 1));
	for (i = 0; i < Rear - Head; i++)
		Newchar[i] = content[i + Head];
	Newchar[i] = '\0';
	return Newchar;
}
size_t PikaString::CopyVector(vector<char>& dst, size_t& length) const
{
	size_t i;
	size_t Newchar;
	length = Rear - Head;
	Newchar = dst.count();
	for (i = 0; i < Rear - Head; i++)
		dst.append(content[i + Head]);
	return Newchar;
}



static char* CopyMalloc(const char* s);
static char* connect(const char* head, const char* rear);

PikaError::PikaError(const char* Source, const char* Error, int Code)
{
	source = CopyMalloc(Source);
	error = CopyMalloc(Error);
	code = Code;
}
PikaError::PikaError(const PikaError& Old, const char* prefix)
{
	//char* New;
	source = connect(prefix, Old.source);
	error = CopyMalloc(Old.error);
	code = Old.code;
}
PikaError::~PikaError()
{
	free(source);
	free(error);
}

void PikaError::show(FILE* fp)const
{
	fprintf(fp, "source: %s, error: %s, code: %d\n", source, error, code);
}





static int Strlen(const char* str)
{
	int length = 0;
	while (str[length] != '\0') 
	{
		length++;
	}
	return length;
}
static void Strcpy(char* dest, const char* src) 
{
	size_t i = 0;
	while (src[i] != '\0') 
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; 
}
void static Strncpy(char* dest, const char* src, size_t n)
{
	size_t i;
	for (i = 0; i < n ; i++)
	{
		dest[i] = src[i];
	}
	return;
}
static char* CopyMalloc(const char* s)
{
	char* v;
	size_t size;
	size = Strlen(s);
	v = (char*)malloc(sizeof(char) * (size + 4));
	Strcpy(v, s);
	return v;
}
static char* connect(const char* head, const char* rear)
{
	size_t head_len = Strlen(head);
	size_t rear_len = Strlen(rear);
	size_t total_len = head_len + rear_len + 1;

	char* result = (char*)malloc(total_len * sizeof(char));
	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	Strncpy(result, head, head_len);
	Strncpy(result + head_len, rear, rear_len);
	result[total_len - 1] = '\0';

	return result;
}






class ManifoldDesc
{
public:
	ManifoldDesc();
	~ManifoldDesc();

private:
	size_t LeftDim;
	size_t RightDim;
	size_t OutDim;
	size_t ParaDim;

	size_t LeftIndex;
	size_t RightIndex;
	size_t ParaIndex;
	size_t OutIndex;



};

ManifoldDesc::ManifoldDesc()
{
}

ManifoldDesc::~ManifoldDesc()
{
}








