#include"HyperAlgebra.h"
//#include<stdio.h>
//#include<stdlib.h>
#include<cmath>

using namespace HyperAlgebra;


//int HyperAlgebraCore::if_intial = 0;
//unsigned int HyperAlgebraCore::Cores = 1;
//unsigned int HyperAlgebraCore::cores_uses = 1;
//pthread_t *HyperAlgebraCore::handle = NULL;
//sem_t HyperAlgebraCore::barrier_sem;




HyperAlgebraCore::HyperAlgebraCore(/* args */)
{
}

HyperAlgebraCore::~HyperAlgebraCore()
{
}

double *HyperAlgebraCore::Free(double *vector)
{
    free((void*)vector);
    return NULL;
}
double *HyperAlgebraCore::Malloc(size_t length)
{
    double *vector;
    vector = (double*)malloc(sizeof(double) * length);
    return vector;
}
double *HyperAlgebraCore::Malloc(size_t row, size_t ld)
{
    double *vector;
    vector = (double*)malloc(sizeof(double) * row * ld);
    return vector;
}

double* HyperAlgebraCore::CopyMalloc(size_t length, const double* old)
{
	double* new_one;
	size_t i;
	new_one = (double*)malloc(sizeof(double) * length);
	for (i = 0; i < length; i++)
		new_one[i] = old[i];
	return new_one;
}
int* HyperAlgebraCore::CopyMalloc(size_t length, const int* old)
{
	int* new_one;
	size_t i;
	new_one = (int*)malloc(sizeof(int) * length);
	for (i = 0; i < length; i++)
		new_one[i] = old[i];
	return new_one;
}
void HyperAlgebraCore::Copy(const double* from, double* to, size_t data_amount) 
{
	size_t i;
//#ifdef _MKL_LIB_EXIST_YET_LALALA_
//	cblas_dcopy(data_amount, from, 1, to, 1);
//#else
	for (i = 0; i < data_amount; i++)
		to[i] = from[i];
//#endif
}






//========================================================================
//class algebra_vector
//========================================================================
BasicVector::BasicVector(/* args */)
{
}
BasicVector::~BasicVector()
{
}
void BasicVector::value(double*vec, double value, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
		vec[i] = value;
}
void BasicVector::copy(const double* from, double *to, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i];
}
void BasicVector::copy(double* from, double *to, size_t length, double alpha, double beta)//to = from*alpha + beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * alpha + beta;
}
void BasicVector::add(double* from, double *to, size_t length, double alpha, double beta)//to = from*alpha + to*beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * alpha + to[i] * beta;
}
//to = vec1*alpha1 + vec2*alpha2
void BasicVector::add(double *to, size_t length, double alpha1, const double* vec1, double alpha2, const double* vec2)
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = vec1[i] * alpha1 + vec2[i] * alpha2;
}
void BasicVector::Add(size_t length, double* to, const double*vec1, double beta, const double*vec2)
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = vec1[i] + vec2[i] * beta;
}
void BasicVector::AddElementwiseSquare(double* from, double *to, size_t length, double alpha, double beta)//to = from_elementwise_square*alpha + to*beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * from[i] * alpha + to[i] * beta;
	return;
}
void BasicVector::AdamRefresh(double* w_b, const double *m1, const double *m2, size_t length, double alpha, double epsilon)
{
	size_t i;
	double temp;
	for (i = 0; i < length; i++)
	{
		temp = sqrt(m2[i]) + epsilon;
		temp = alpha * m1[i] / temp;
		w_b[i] = w_b[i] + temp;
	}
	return;
}

void BasicVector::Tanh(double* from, double *to, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
         to[i] = tanh(from[i]);
}
void BasicVector::algebraic(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = x / sqrt(x * x + 1.0);
	}
         
}
void BasicVector::Cos(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = cos(x);
	}     
}
void BasicVector::gaussain(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = exp(-0.5 * x * x);
	}     
}
void BasicVector::reciprocal(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = 1.0 / sqrt(x * x + 1.0);
	}     
}


void BasicVector::BackwardTanh(double* from, double *to, const double* forward, size_t length)
{
	size_t i;
	double temp;
	for (i = 0; i < length; i++)
	{
		temp = forward[i];
		to[i] = from[i] * (1.0 - temp * temp);
	}  
	return;
}
void BasicVector::BackwardAlgebraic(double* from, double *to, const double* forward, size_t length)
{
	size_t i;
	double temp;
	for (i = 0; i < length; i++)
	{
		temp = forward[i];
		temp = sqrt(1.0 - temp * temp);
		to[i] = from[i] * temp * temp * temp;
	}  
	return;
}
void BasicVector::BackwardCos(double *from, double *to, const double* forward_in, size_t length)
{
	size_t i;
	double temp;
	for (i = 0; i < length; i++)
	{
		temp = forward_in[i];
		temp = -sin(temp);
		to[i] = from[i] * temp;
	}  
	return;
}
void BasicVector::BackwardGaussain(double *from, double *to, const double* forward_in, size_t length)
{
	size_t i;
	double temp;
	for (i = 0; i < length; i++)
	{
		temp = forward_in[i];
		temp = -temp * exp(-0.5 * temp * temp);
		to[i] = from[i] * temp;
	}  
	return;
}
void BasicVector::BackwardReciprocal(double *from, double *to, const double* forward_in, size_t length)
{
	size_t i;
	double temp, y;
	for (i = 0; i < length; i++)
	{
		temp = forward_in[i];
		y = sqrt(1.0 / (1.0 + temp * temp));
		to[i] = -from[i] * y * y * y * temp;
	}  
	return;
}

double BasicVector::InnerDot(const double* left, const double* right, size_t length)
{
	size_t i;
	double inner;
	inner = 0.0;
	for (i = 0; i < length; i++)
		inner += left[i] * right[i];
	return inner;
}
void BasicVector::ElemwiseDot(double ele, double* vector, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
		vector[i] *= ele;
	return;
}
double BasicVector::Norm2(const double* vector, size_t length)
{
	size_t i;
	double inner;
	inner = 0.0;
	for (i = 0; i < length; i++)
		inner += vector[i] * vector[i];
	return std::sqrt(inner);
}
double BasicVector::Norm2(const double* vec1, const double* vec2, size_t length)
{
	size_t i;
	double inner, temp;
	inner = 0.0;
	for (i = 0; i < length; i++)
	{
		temp = vec1[i] - vec2[i];
		inner += temp * temp;
	}
	return std::sqrt(inner);
}
void BasicVector::Substract(double *vector, size_t length, const double *subtrahend, double Norm2Square)
{
	size_t i;
	double inner, coeff;
	inner = 0.0;
	for (i = 0; i < length; i++)
		inner += vector[i] * subtrahend[i];
	if(Norm2Square != 0.0) inner = inner / Norm2Square;
	coeff = -inner;
	for (i = 0; i < length; i++)
		vector[i] += coeff * subtrahend[i];
	return;
}
void BasicVector::Norm2Normalization(double* vector, size_t length)
{
	size_t i;
	double inner, coeff;
	inner = 0.0;
	for (i = 0; i < length; i++)
		inner += vector[i] * vector[i];
	inner = std::sqrt(inner);
	if(inner != 0.0)
	{
		coeff = 1.0 / inner;
		for (i = 0; i < length; i++)
			vector[i] *= coeff;
	}
}
void BasicVector::FiniteDifference(double *result, size_t length, double DeltaReverse, const double *minuend, const double *subtrahend)
{
	size_t i;
	for (i = 0; i < length; i++)
		result[i] = (minuend[i] - subtrahend[i]) * DeltaReverse;
}
void BasicVector::Inverse(size_t length, double *vector)
{
	size_t i;
	for (i = 0; i < length; i++)
	{
		vector[i] = (vector[i] != 0.0 ? 1.0 / vector[i] : 0.0);
	}
	return;
}
void BasicVector::ElemwiseProd(size_t length, const double *vec1, const double *vec2, double *dst)
{
	size_t i;
	for (i = 0; i < length; i++)
	{
		dst[i] = vec1[i] * vec2[i];
	}
	return;
}
//========================================================================
//class BasicMatrix
//========================================================================

BasicMatrix::BasicMatrix(/* args */)
{
}
BasicMatrix::~BasicMatrix()
{
}
void BasicMatrix::DiagonalAdd(double *mat, size_t row, size_t ld, double addend)
{
	size_t i;
	for	(i = 0; i < row; i++)
		mat[i * ld + i] += addend;
}
void BasicMatrix::DiagonalExpand(double *mat, size_t row, size_t ld, double addend)
{
	size_t i;
	for	(i = 0; i < row; i++)
		mat[i * ld + i] += addend * mat[i * ld + i];
}
void BasicMatrix::SymMatCompress(size_t row_col, size_t ld, const double *mat, double *compressed, enum Uplo T)
{
	size_t i, j, site;
	const double *temp;
	site = 0;
	if(T == lower)
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = 0; j < i + 1; j++)
			{
				compressed[site] = temp[j];
				site++;
			}
		}
	}
	else
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = i; j < row_col; j++)
			{
				compressed[site] = temp[j];
				site++;
			}
		}
	}
}
void BasicMatrix::SymMatUncompress(size_t row_col, size_t ld, double *mat, const double *compressed, enum Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == lower)
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = 0; j < i + 1; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
		}
	}
	else
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = i; j < row_col; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
		}
	}
}
void BasicMatrix::SymMatUncompress(size_t row_col, size_t ld, double lambda, double *mat, const double *compressed, enum Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == lower)
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = 0; j < i; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
			temp[i] = compressed[site] + lambda;
			site++;
		}
	}
	else
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			temp[i] = compressed[site] + lambda;
			site++;
			for(j = i + 1; j < row_col; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
		}
	}
}
void BasicMatrix::SymMatUncompressExpand(size_t row_col, size_t ld, double factor, double *mat, const double *compressed, enum Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == lower)
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			for(j = 0; j < i; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
			temp[i] = compressed[site] * (factor + 1.0);
			site++;
		}
	}
	else
	{
		for	(i = 0; i < row_col; i++)
		{
			temp = mat + ld * i;
			temp[i] = compressed[site] * (factor + 1.0);
			site++;
			for(j = i + 1; j < row_col; j++)
			{
				temp[j] = compressed[site];
				site++;
			}
		}
	}
}
void BasicMatrix::CopyVectorToMatrixLine(double*mat, size_t ldm, const double* vec, size_t incr, size_t row, size_t column)
{
	size_t i, j;
	double temp;
	double*target;
	for (i = 0; i < row; i++)
	{
		temp = vec[i * incr];
		target = mat + i * ldm;
		for (j = 0; j < column; j++)
			target[j] = temp;
	}
	return;
}
void BasicMatrix::MatrixCopy(const double* from, size_t ldf, double* to, size_t ldt, size_t rows, size_t column)
{
	size_t i, j;
	double *target;
	const double *source;
	for (i = 0; i < rows; i++)
	{
		target = to + i * ldt;
		source = from + i * ldf;
		for (j = 0; j < column; j++)
			target[j] = source[j];
	}
	return;
}
void BasicMatrix::SumMatrixLine(const double *temp, size_t ld, size_t row, size_t column, double *result, double alpha, double beta)
{
	size_t i, j;
	double sum;
	const double *From;
	for(i = 0; i < row; i++)
	{
		sum = 0.0;
		From = temp + i * ld;
		for(j = 0; j < column; j++)
			sum += From[j];
		result[i] = alpha * sum + beta * result[i];
	}
}
void BasicMatrix::MatrixShardProduct(const double* major, size_t ldm, const double* follow, size_t ldf, double* to, size_t ldt, size_t ld_index, size_t row_m, size_t row_f, size_t EleCount)
{
	size_t i, j, k;
	size_t index, index_base;
	double left, right, temp;
	const double *Major, *Follow;
	double *To;
	for (k = 0; k < EleCount; k++)
	{
		Major = major + k;
		Follow = follow + k;
		To = to + k;
		for (i = 0; i < row_m; i++)
		{
			left = Major[i * ldm];
			//left = major[i * ldm + k];
			index_base = i * ld_index;
			for (j = 0; j < row_f; j++)
			{
				index = index_base + j;
				//right = follow[j * ldf + k];
				right = Follow[j * ldf];
				temp = left * right;
				//to[index * ldt + k] = temp;
				To[index * ldt] = temp;
			}
		}
	}
}




void BasicMatrix::Tanh(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
{
	size_t i, j;
	double *From, *To;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
			To[j] = tanh(From[j]);
	}
}
void BasicMatrix::algebraic(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
{
	size_t i, j;
	double *From, *To;
	double x;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
		{
			x = From[j];
			To[j] = x / sqrt(x * x + 1.0);
		}
	}
}
void BasicMatrix::Cos(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
{
	size_t i, j;
	double *From, *To;
	double x;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
		{
			x = From[j];
			To[j] = cos(x);
		}
	}
}
void BasicMatrix::gaussain(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
{
	size_t i, j;
	double *From, *To;
	double x;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
		{
			x = From[j];
			To[j] = exp(-0.5 * x * x);
		}
	}
}
void BasicMatrix::reciprocal(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
{
	size_t i, j;
	double *From, *To;
	double x;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
		{
			x = From[j];
			To[j] = 1.0 / sqrt(x * x + 1.0);
		}
	}
}

void BasicMatrix::BackwardTanh(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
{
	size_t i, j;
	double *From, *To;
	const double *Forward;
	double temp;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Forward = forward + i * ldforward;
		for (j = 0; j < column; j++)
		{
			temp = Forward[j];
			To[j] = From[j] * (1.0 - temp * temp);
		}
	}
}
void BasicMatrix::BackwardAlgebraic(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
{
	size_t i, j;
	double *From, *To;
	const double *Forward;
	double temp;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Forward = forward + i * ldforward;
		for (j = 0; j < column; j++)
		{
			temp = Forward[j];
			temp = sqrt(1.0 - temp * temp);
			To[j] = From[j] * temp * temp * temp;
		}
	}
}
void BasicMatrix::BackwardCos(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
{
	size_t i, j;
	double *From, *To;
	const double *Forward;
	double temp;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Forward = forward_in + i * ldforward;
		for (j = 0; j < column; j++)
		{
			temp = Forward[j];
			temp = -sin(temp);
			To[j] = From[j] * temp;
		}
	}
}
void BasicMatrix::BackwardGaussain(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
{
	size_t i, j;
	double *From, *To;
	const double *Forward;
	double temp;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Forward = forward_in + i * ldforward;
		for (j = 0; j < column; j++)
		{
			temp = Forward[j];
			temp = -temp * exp(-0.5 * temp * temp);
			To[j] = From[j] * temp;
		}
	}
}
void BasicMatrix::BackwardReciprocal(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
{
	size_t i, j;
	double *From, *To;
	const double *Forward;
	double temp, y;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Forward = forward_in + i * ldforward;
		for (j = 0; j < column; j++)
		{
			temp = Forward[j];
			y = sqrt(1.0 / (1.0 + temp * temp));
			To[j] = -From[j] * y * y * y * temp;
		}
	}
}

void BasicMatrix::GEMVn(const double* Mat, size_t ldM, const double* vec, double *dst, size_t row, size_t col)
{
	size_t i, j;
	double value;
	for (i = 0; i < row; i++)
	{
		value = 0.0;
		for (j = 0; j < col; j++)
			value += Mat[i * ldM + j] * vec[j];
		dst[i] = value;
	}
}
void BasicMatrix::GEMVt(const double* Mat, size_t ldM, const double* vec, double *dst, size_t row, size_t col)
{
	size_t i, j;
	double value;
	for (i = 0; i < col; i++)
	{
		value = 0.0;
		for (j = 0; j < row; j++)
			value += Mat[j * ldM + i] * vec[j];
		dst[i] = value;
	}
}
//dst = Mat ^ T * vec Mat: row * col row * ldM
void BasicMatrix::MatColValueFromVec(double* MatTo, size_t ldM, size_t row, const double* vector)
{
	size_t i;
	for (i = 0; i < row; i++)
		MatTo[i * ldM] = vector[i];
}
void BasicMatrix::MatRowValueFromVec(double* MatTo, size_t col, const double* vector)
{
	size_t i;
	for (i = 0; i < col; i++)
		MatTo[i] = vector[i];
}

double BasicMatrix::NormMax(size_t row, size_t column, const double *mat1, size_t ld1, const double *mat2, size_t ld2)
{
	double result, temp;
	const double * Line1, *Line2;
	size_t i, j;
	result = 0.0;
	for (i = 0; i < row; i++)
	{
		Line1 = mat1 + i * ld1;
		Line2 = mat2 + i * ld2;
		for (j = 0; j < column; j++)
		{
			temp = fabs(Line1[j] - Line2[j]);
			result = result > temp ? result : temp;
		}
	}
	return result;
}
//========================================================================
//class BasicMatrix
//========================================================================
						 




