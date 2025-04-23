#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<cstring>
#include<string>
//#include"GPU_switch.h"
using namespace std;
#define _MKL_LIB_EXIST_YET_LALALA_
#ifdef _MKL_LIB_EXIST_YET_LALALA_
extern "C" {
	#include <mkl.h>
	#include <mkl_scalapack.h>
}
#endif // _MKL_LIB_EXIST_YET_LALALA_
#include"linear_algebra.h"
#include"../../HyperLex/extern_head/HyperLex.h"
//========================================================================
	//===One===class matrix
	//===Two===class dvector
	//==Three==class ivector
	//==Four===class matrix_list
	//==Five===class cuda_status
	//===Six===class algebra_log
//========================================================================
//========================================================================
//class matrix
//========================================================================
matrix::matrix()
{
	size = 0;
	mat = NULL;
	row = 0;
	column = 0;
}
matrix::matrix(size_t R, size_t C)
{
	row = R;
	column = C;
	size = column * row;
	mat = (double*)malloc(size * sizeof(double));
	return;
}
matrix::~matrix()
{
	this->ruin();
	return;
}
void matrix::create(size_t R, size_t C)
{
	if ((R == this->row) && (C == this->column)) return;
	if (this->mat != NULL)
		free((void*)this->mat);
	this->row = R;
	this->column = C;
	this->size = this->column * this->row;
	this->mat = (double*)malloc(this->size * sizeof(double));
	return;
}
void matrix::ruin(void)
{
	if (this->mat != NULL)
		free((void*)this->mat);
	this->row = 0;
	this->column = 0;
	this->size = 0;
	return;
}
//========================================================================
size_t matrix::Row(void)
{
	return this->row;
}
size_t matrix::Column(void)
{
	return this->column;
}
size_t matrix::Size(void)
{
	return this->size;
}
//========================================================================
void matrix::value(double alpha, int method)
{
	size_t i, j, offset;
	if (method == 0)
	{
		for (i = 0; i < this->size; i++)
			*(this->mat + i) = alpha;
	}
	else if (method == 1)
	{
		for (i = 0; i < this->size; i++)
			*(this->mat + i) = alpha * ((double)(i + 1));
	}
	else
	{
		offset = 0;
		for (i = 0; i < this->row; i++)
			for (j = 0; j < this->column; j++)
			{
				if (i == j)
					*(this->mat + offset) = ((double)(this->row * this->column));
				else
					*(this->mat + offset) = alpha;
				offset++;
			}
	}

}
void matrix::fprintf_matrix(FILE* fp, int format)
{
	long long int i, j, length, offset;
	if (format == 0)
	{
		offset = 0;
		for (i = 0; i < this->row; i++)
			for (j = 0; j < this->column; j++)
			{
				fprintf(fp, "A[%lld][%lld] = %lf\n", i, j, this->mat[offset]);
				offset++;
			}		
	}
	else if (format == 1)
	{
		length = this->column;
		offset = 0;
		for (i = 0; i < this->row; i++)
		{
			for (j = 0; j < length; j++)
			{
				fprintf(fp, "%+21.16E  ", this->mat[offset]);
				offset++;
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
	}
	else
	{
		offset = 0;
		for (i = 0; i < this->row; i++)
		{
			for (j = 0; j < this->column; j++)
			{
				fprintf(fp, "%.16lf  ", this->mat[offset]);
				offset++;
			}
			fprintf(fp, "\n");
		}
	}
	return;
}
void matrix::store(const char* path, const char* name)
{
	algebra_log log;
	log.bitwise_store_open(path, name);
	log.bitwise_store_lld(this->row);
	log.bitwise_store_lld(this->column);
	log.bitwise_store_lfvector(this->column * this->row, this->mat);
	return;
}
void matrix::load(const char* path, const char* name)
{
	algebra_log log;
	long long int r, c;
	log.bitwise_load_open(path, name);
	log.bitwise_load_lld(&r);
	log.bitwise_load_lld(&c);
	this->create(r, c);
	log.bitwise_load_lfvector(r * c, this->mat);
	return;
}
//========================================================================
void matrix::operator*=(const double alpha)
{
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	cblas_dscal(this->column * this->row, alpha, this->mat, 1);
	#else
	size_t i;
	for (i = 0; i < this->size; i++)
		*(this->mat + i) *= alpha;
	#endif
	return;
}
void matrix::operator+=(const double alpha)
{
	size_t i;
	for (i = 0; i < this->size; i++)
		*(this->mat + i) += alpha;
	return;
}
void matrix::operator=(const double alpha)
{
	size_t i;
	for (i = 0; i < this->size; i++)
		*(this->mat + i) = alpha;
	return;
}
void matrix::operator<=(const matrix & A)
{
	if ((this->row != A.row) || (this->column != A.column))
		this->create(A.row, A.column);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
/*void cblas_dcopy (const MKL_INT n, const double *x, const MKL_INT incx, double *y,const MKL_INT incy); y = x*/
	cblas_dcopy(this->size, A.mat, 1, this->mat, 1);
#else
	size_t i;
	for (i = 0; i < this->size; i++)
		*(this->mat + i) = *(A.mat + i);
#endif
}
void matrix::from_matrix_list(size_t h, const matrix_list & ml, const dvector & V)
{
	h = h % ml.amount;
	this->column = *(ml.column + h);
	this->row = *(ml.row + h);
	this->size = this->column * this->row;
	this->mat = V.vector + *(ml.offset + h);
}
//========================================================================
void matrix::transposition()
{
	size_t i, j, length;
	double temp, * Mat;
	if (this->mat == NULL) return;
	if (this->column == this->row)
	{
		length = this->column;
		Mat = this->mat;
		for (i = 0; i < length; i++)
			for (j = i + 1; j < length; j++)
			{
				temp = Mat[i * length + j];
				Mat[i * length + j] = Mat[j * length + i];
				Mat[j * length + i] = temp;
			}
	}
	else
	{
		Mat = (double*)malloc(this->row * this->column * sizeof(double));
		for (i = 0; i < this->row; i++)
			for (j = 0; j < this->column; j++)
				Mat[j * this->row + i] = *(this->mat + i * this->column + j);
		length = this->row;
		this->row = this->column;
		this->column = length;
		length = this->row * this->column;
#ifdef _MKL_LIB_EXIST_YET_LALALA_
		cblas_dcopy(length, Mat, 1, this->mat, 1);
#else
		for (i = 0; i < length; i++)
			*(this->mat + i) = Mat[i];
#endif
		free((void*)Mat);
	}
}
double matrix::induced_1_norm(void)
{
	size_t i, j;
	double max, column, temp;
	max = 0.0;
	for (j = 0; j < this->column; j++)
	{
		column = 0.0;
		for (i = 0; i < this->row; i++)
		{
			temp = (this->mat)[i * this->column + j];
			column += ((double)(2 * (temp > 0.0) - 1)) * temp;
		}
		max += ((double)(column > max)) * (column - max);
	}
	return max;
}
double matrix::induced_inf_norm(void) 
{
	size_t i, j;
	double max, column, temp;
	max = 0.0;
	for (i = 0; i < this->row; i++)
	{
		column = 0.0;
		for (j = 0; j < this->column; j++)
		{
			temp = (this->mat)[i * this->column + j];
			column += ((double)(2 * (temp > 0.0) - 1)) * temp;
		}
		max += ((double)(column > max)) * (column - max);
	}
	return max;
}
double matrix::Frobenius_norm(void)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	return cblas_dnrm2(this->size, this->mat, 1); 
#else
	size_t i;
	double norm, temp;
	norm = 0.0;
	for (i = 0; i < this->size; i++)
	{
		temp = *(this->mat + i);
		norm += temp * temp;
	}
	norm = sqrt(norm);
	return norm;
#endif
	
}
void matrix::diagon_add(double addend)
{
	size_t i, count, temp;
	double* Augend;
	count = (this->column <= this->row ? this->column : this->row);
	temp = 1 + count;
	for (i = 0, Augend = this->mat; i < count; i++, Augend = Augend + temp)
		*Augend += addend;
	return;
}
//========================================================================
void matrix::tanh(void)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	vdTanh(this->size, this->mat, this->mat);
#else
	size_t i;
	for (i = 0; i < this->size; i++)
		*(this->mat + i) = std::tanh(*(this->mat + i));
#endif
	return;
}
void matrix::algebraic(void)
{
	size_t i;
	double x;
	for (i = 0; i < this->size; i++)
	{
		x = *(this->mat + i);
		*(this->mat + i) = x / sqrt(1.0 + x * x);
	}
	return;
}
//========================================================================
void matrix::muliple(matrix & left, matrix & right)
{
	this->muliple_core(left, right, 1.0, 0.0);
	return;
}
void matrix::muliple_core(matrix & left, matrix & right, double alpha, double beta)
{
	size_t L;
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	MKL_INT m, n, k;
#else
	size_t i, j, k;
	double sum;
#endif
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	L = left.column;
	log.check_input_equal(left.column, right.row, "void matrix::muliple(matrix right, matrix result)");
#else
	L = (left.column < right.row ? left.column : right.row);
#endif
	this->create(left.row, right.column);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	Layout = CblasRowMajor;
	trans = CblasNoTrans;
	m = (MKL_INT)left.row;
	k = (MKL_INT)L;
	n = (MKL_INT)right.column;
	cblas_dgemm(Layout, trans, trans, m, n, k, alpha, left.mat, k, right.mat, n, beta, this->mat, n);
#else
	for (i = 0; i < this->row; i++)
	{
		for (j = 0; j < this->column; j++)
		{
			this->mat[i * this->column + j] *= beta;
			sum = 0.0;
			for (k = 0; k < L; k++)
				sum += left.mat[i * this->column + k] * right.mat[k * right.column + j];
			this->mat[i * this->column + j] += alpha * sum;
		}
	}
#endif
}
//========================================================================
//class dvector
//========================================================================
dvector::dvector()
{
	length = 0;
	vector = NULL;
}
dvector::dvector(size_t size)
{
	length = size;
	vector = (double*)malloc(length * sizeof(double));
}
dvector::dvector(size_t size, const double *input)
{
	size_t i;
	length = size;
	vector = (double*)malloc(length * sizeof(double));
	for (i = 0; i < length; i++) vector[i] = input[i];
}
dvector::~dvector()
{
	this->ruin();
	return;
}
void dvector::create(size_t size)
{
	if (size == this->length) return;
	if (this->vector != NULL)
		free((void*)this->vector);
	this->length = size;
	this->vector = (double*)malloc(this->length * sizeof(double));
	return;
}
void dvector::append(double ele, size_t site)
{
	site %= this->length;
	vector[site] = ele;
	return;
}
void dvector::ruin(void)
{
	if (this->vector != NULL)
		free((void*)this->vector);
	this->length = 0;
	return;
}
size_t dvector::Length(void)
{
	return this->length;
}
double* dvector::Vector(void)
{
	return this->vector;
}
void dvector::store(const char* path, const char* name)
{
	algebra_log log;
	log.bitwise_store_open(path, name);
	log.bitwise_store_lld(this->length);
	log.bitwise_store_lfvector(this->length, this->vector);
	return;
}
void dvector::load(const char* path, const char* name)
{
	algebra_log log;
	long long int L;
	log.bitwise_load_open(path, name);
	log.bitwise_load_lld(&L);
	this->create(L);
	log.bitwise_load_lfvector(L, this->vector);
	return;
}
//========================================================================
void dvector::operator*=(const double alpha)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	cblas_dscal(this->length, alpha, this->vector, 1);
#else
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) *= alpha;
#endif
	return;
}
double dvector::operator*(const dvector & Right)
{
	size_t L;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	L = this->length;
	log.check_input_equal(this->length, Right.length, "double dvector::operator*(const dvector Right)");
#else
	L = (this->length < Right.length ? this->length : Right.length);
#endif
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	/*double cblas_ddot (const MKL_INT n, const double *x, const MKL_INT incx, const double
*y, const MKL_INT incy);
*/
	return cblas_ddot(L, this->vector, 1, Right.vector, 1);
#else
	long long int i;
	double inner_dot;
	inner_dot = 0.0;
	for (i = 0; i < L; i++)
		inner_dot += *(this->vector + i) * (*(Right.vector + i));
	return inner_dot;
#endif
}
void dvector::operator-=(const dvector & subtrahend)
{
	size_t L;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	L = this->length;
	log.check_input_equal(this->length, subtrahend.length, "void dvector::operator-=(const dvector subtrahend)");
#else
	L = (this->length < subtrahend.length ? this->length : subtrahend.length);
#endif
#ifdef _MKL_LIB_EXIST_YET_LALALA_
/*void cblas_daxpy (const MKL_INT n, const double a, const double *x, const MKL_INT incx,
double *y, const MKL_INT incy);y := a*x + y*/
	cblas_daxpy(length, -1.0, subtrahend.vector, 1, this->vector, 1);
#else
	size_t i;
	for (i = 0; i < L; i++)
		*(this->vector + i) -=  *(subtrahend.vector + i);
	return;
#endif
}
void dvector::operator+=(const dvector & addend)
{
	size_t L;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	L = this->length;
	log.check_input_equal(this->length, addend.length, "void dvector::operator+=(const dvector addend)");
#else
	L = (this->length < addend.length ? this->length : addend.length);
#endif
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	/*void cblas_daxpy (const MKL_INT n, const double a, const double *x, const MKL_INT incx,
	double *y, const MKL_INT incy);y := a*x + y*/
	cblas_daxpy(length, 1.0, addend.vector, 1, this->vector, 1);
#else
	size_t i;
	for (i = 0; i < L; i++)
		*(this->vector + i) += *(addend.vector + i);
	return;
#endif
}
void dvector::operator+=(const double alpha)
{
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) += alpha;
	return;
}
void dvector::operator=(const double alpha)
{
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) = alpha;
	return;
}
void dvector::operator=(matrix & A)
{
	this->length = A.size;
	this->vector = A.mat;
	return;
}
void dvector::operator<=(const dvector & V)
{
	if (this->length != V.length)
		this->create(V.length);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	/*void cblas_dcopy (const MKL_INT n, const double *x, const MKL_INT incx, double *y,const MKL_INT incy); y = x*/
	cblas_dcopy(this->length, V.vector, 1, this->vector, 1);
#else
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) = *(V.vector + i);
#endif
}
//========================================================================
double dvector::norm2(void)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	return cblas_dnrm2(this->length, this->vector, 1);
#else
	size_t i;
	double norm, temp;
	norm = 0.0;
	for (i = 0; i < this->length; i++)
	{
		temp = *(this->vector + i);
		norm += temp * temp;
	}
	norm = sqrt(norm);
	return norm;
#endif
}
double dvector::distance(dvector & V)
{
	size_t i;
	double norm, temp;
	norm = 0.0;
	for (i = 0; i < this->length; i++)
	{
		temp = *(this->vector + i) - *(V.vector + i);
		norm += temp * temp;
	}
	norm = sqrt(norm);
	return norm;
}
void dvector::min_max_dvector(double* min, double* max)
{
	double temp, * temp_vector, temp_min, temp_max;
	size_t i, length;
	length = this->length;
	temp_vector = this->vector;
	temp_min = temp_vector[0];
	temp_max = temp_vector[0];
	for (i = 1; i < length; i++)
	{
		temp = temp_vector[i];
		temp_min = (temp_min < temp ? temp_min : temp);
		temp_max = (temp_max > temp ? temp_max : temp);
	}
	*min = temp_min;
	*max = temp_max;
	return;
}
void dvector::value_Arithmetic_progression(double d, double initial)
{
	size_t i, length;
	double *VECtor;
	VECtor = this->vector;
	length = this->length;
	for (i = 0; i < length; i++)
	{
		VECtor[i] = initial;
		initial += d;
	}
	return;
}
void dvector::file_printf(FILE* fp, int format, int message)
{
	size_t i, j, length, L;
	double* V;
	length = this->length;
	V = this->vector;
	if (format == 0 || format == 1)
	{
		if (format == 0)
			L = 20;
		else
			L = message;
		for (i = 0; i < length; i++)
			if (i % L == 0)
				fprintf(fp, "%+.8lf", *(V + i));
			else if (i % L == L - 1)
				fprintf(fp, "    %+.8lf\n", *(V + i));
			else
				fprintf(fp, "    %+.8lf", *(V + i));
		if (i % L != L)
			fprintf(fp, "\n");
	}
	else if (format == 2 || format == 3)
	{
		if (format == 2)
			L = 8;
		else
			L = message;
		for (i = 0; i < length; i++)
			if (i % L == 0)
				fprintf(fp, "%+25.16E", *(V + i));
			else if (i % L == L - 1)
				fprintf(fp, "    %+25.16E\n", *(V + i));
			else
				fprintf(fp, "    %+25.16E", *(V + i));
		if (i % L != L)
			fprintf(fp, "\n");
	}
	else
	{
		i = 0;
		if (message < 0)
		{
			L = -message;
			fprintf(fp, "    %+23.16E", *(V + i));
			for (i = 1; i < length; i++)
				if (i % L == 0)
					fprintf(fp, "\n%+23.16E", *(V + i));
				else
					fprintf(fp, "    %+23.16E", *(V + i));
			fprintf(fp, "\n");
		}
		else
		{
			L = message;
			fprintf(fp, "    %+14.6E", *(V + i));
			for (i = 1; i < length; i++)
				if (i % L == 0)
					fprintf(fp, "\n%+14.6E", *(V + i));
				else
					fprintf(fp, "    %+14.6E", *(V + i));
			fprintf(fp, "\n");
		}
	}
	return;
}
void dvector::file_printf(FILE* fp)
{
	size_t i, length;
	double* V;
	length = this->length;
	V = this->vector;
	for (i = 0; i < length; i++)
		fprintf(fp, "%+25.16E\n", V[i]);
	return;
}

//========================================================================
//class ivector
//========================================================================
ivector::ivector()
{
	vector = NULL;
	length = 0;
}
ivector::ivector(size_t size)
{
	length = size;
	vector = (long long int*)malloc(length * sizeof(long long int));
}
ivector::~ivector()
{
	this->ruin();
	return;
}
void ivector::create(size_t size)
{
	if (this->vector != NULL)
		free((void*)this->vector);
	this->length = size;
	this->vector = (long long int*)malloc(this->length * sizeof(long long int));
	return;
}
void ivector::append(long long int ele, size_t site)
{
	site %= this->length;
	vector[site] = ele;
	return;
}
void ivector::ruin(void)
{
	if (this->vector != NULL)
		free((void*)this->vector);
	this->length = 0;
	return;
}
size_t ivector::Length(void)
{
	return this->length;
}
//========================================================================
void ivector::operator*=(const long long int alpha)
{
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) *= alpha;
	return;
}
long long int ivector::operator*(const ivector & Right)
{
	long long int L;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	L = this->length;
	log.check_input_equal(this->length, Right.length, "long long int ivector::operator*(const ivector Right)");
#else
	L = (this->length < Right.length ? this->length : Right.length);
#endif
	size_t i;
	long long int inner_dot;
	inner_dot = 0.0;
	for (i = 0; i < L; i++)
		inner_dot += *(this->vector + i) * (*(Right.vector + i));
	return inner_dot;
}
void ivector::operator+=(const long long int alpha)
{
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) += alpha;
	return;
}
void ivector::operator=(const long long int alpha)
{
	size_t i;
	for (i = 0; i < this->length; i++)
		*(this->vector + i) = alpha;
	return;
}
void ivector::operator<=(const ivector & V)
{
	size_t i;
	if (this->length != V.length)
		this->create(V.length);
	for (i = 0; i < this->length; i++)
		*(this->vector + i) = *(V.vector + i);
}
//========================================================================
void ivector::value_Arithmetic_progression(long long int d, long long int initial)
{
	long long int i, length;
	long long int* VECtor;
	VECtor = this->vector;
	length = this->length;
	for (i = 0; i < length; i++)
	{
		VECtor[i] = initial;
		initial += d;
	}
	return;
}
void ivector::file_printf(FILE* fp, int format, int message)
{
	long long int i, j, length, L;
	long long int* V;
	length = this->length;
	V = this->vector;
	if (format == 0 || format == 1)
	{
		if (format == 0)
			L = 20;
		else
			L = message;
		for (i = 0; i < length; i++)
			if (i % L == 0)
				fprintf(fp, "%lld", *(V + i));
			else if (i % L == L - 1)
				fprintf(fp, "    %lld\n", *(V + i));
			else
				fprintf(fp, "    %lld", *(V + i));
		if (i % L != L)
			fprintf(fp, "\n");
	}
	else if (format == 2 || format == 3)
	{
		if (format == 0)
			L = 8;
		else
			L = message;
		for (i = 0; i < length; i++)
			if (i % L == 0)
				fprintf(fp, "%+16lld", *(V + i));
			else if (i % L == L - 1)
				fprintf(fp, "    %+16lld\n", *(V + i));
			else
				fprintf(fp, "    %+16lld", *(V + i));
		if (i % L != L)
			fprintf(fp, "\n");
	}
	else
	{
		i = 0;
		if (message < 0)
		{
			L = -message;
			fprintf(fp, "    %+lld", *(V + i));
			for (i = 1; i < length; i++)
				if (i % L == 0)
					fprintf(fp, "\n%+lld", *(V + i));
				else
					fprintf(fp, "    %+lld", *(V + i));
			fprintf(fp, "\n");
		}
		else
		{
			L = message;
			fprintf(fp, "    %+16lld", *(V + i));
			for (i = 1; i < length; i++)
				if (i % L == 0)
					fprintf(fp, "\n%+16lld", *(V + i));
				else
					fprintf(fp, "    %+16lld", *(V + i));
			fprintf(fp, "\n");
		}
	}
	return;
}
size_t ivector::count_value(long long int value)
{
	size_t i, count;
	count = 0;
	for (i = 0; i < this->length; i++)
		if (*(this->vector + i) == value)
			count++;
	return count;
}
long long int ivector::sum(void)
{
	long long int value, i, length, *list;
	length = this->length;
	list = this->vector;
	for (i = 0, value = 0; i < length; i++)
		value += list[i];
	return value;
}


//========================================================================
//class matrix_list
//========================================================================
matrix_list::matrix_list()
{
	column = NULL;
	row = NULL;
	offset = NULL;
	amount = 0;
}
void matrix_list::create(ivector & Row, ivector & Column)
{
	size_t L;
	size_t i;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	log.check_input_equal(Row.length, Column.length, "void matrix_list::create(ivector Row, ivector Column)");
	L = Row.length;
#else
	L = (Row.Length() < Column.Length() ? Row.Length() : Column.Length());
#endif
	this->amount = L;
	this->row = (size_t*)malloc(this->amount * sizeof(size_t));
	this->column = (size_t*)malloc(this->amount * sizeof(size_t));
	this->offset = (size_t*)malloc(this->amount * sizeof(size_t));
	this->column[0] = *(Column.vector + 0);
	this->row[0] = *(Row.vector + 0);
	this->offset[0] = 0;
	for (i = 1; i < this->amount; i++)
	{
		this->column[i] = *(Column.vector + i);
		this->row[i] = *(Row.vector + i);
		this->offset[i] = this->offset[i - 1] + this->column[i - 1] * this->row[i - 1];
	}
	return;
}
void matrix_list::create(ivector & r1, ivector & c1, ivector & r2, ivector & c2)
{
	size_t L1, L2;
	size_t i, j;
#ifdef UNDER_DEBUG_NOW
	algebra_log log;
	log.check_input_equal(r1.Length(), c1.Length(), "void matrix_list::create(ivector Row, ivector Column) 1");
	log.check_input_equal(r2.Length(), c2.Length(), "void matrix_list::create(ivector Row, ivector Column) 2");
	L1 = r1.length;
	L2 = r2.length;
#else
	L1 = (r1.Length() < c1.Length() ? r1.Length() : c1.Length());
	L2 = (r2.Length() < c2.Length() ? r2.Length() : c2.Length());
#endif
	this->amount = L1 + L2;
	this->row = (size_t*)malloc(this->amount * sizeof(size_t));
	this->column = (size_t*)malloc(this->amount * sizeof(size_t));
	this->offset = (size_t*)malloc(this->amount * sizeof(size_t));
	for (i = 0, j = 0; i < this->amount; i++, j++)
	{
		if (j < L1 && j < L2)
		{
			this->row[i] = *(r1.vector + j);
			this->column[i] = *(c1.vector + j);
			i++;
			this->row[i] = *(r2.vector + j);
			this->column[i] = *(c2.vector + j);
		}
		else if (j < L1)
		{
			this->row[i] = *(r1.vector + j);
			this->column[i] = *(c1.vector + j);
		}
		else
		{
			this->row[i] = *(r2.vector + j);
			this->column[i] = *(c2.vector + j);
		}
	}
	this->offset[0] = 0;
	for (i = 1; i < this->amount; i++)
		this->offset[i] = this->offset[i - 1] + this->column[i - 1] * this->row[i - 1];
	return;
}
matrix_list::~matrix_list()
{
	this->ruin();
	return;
}
void matrix_list::ruin(void)
{
	if (amount != 0)
	{
		free((void*)this->column);
		free((void*)this->row);
		free((void*)this->offset);
	}
	column = NULL;
	row = NULL;
	offset = NULL;
	amount = 0;
}
size_t matrix_list::Amount(void)
{
	return this->amount;
}
//========================================
void matrix_list::operator<=(const matrix_list & V)
{
	size_t i;
	this->amount = V.amount;
	this->row = (size_t*)malloc(this->amount * sizeof(size_t));
	this->column = (size_t*)malloc(this->amount * sizeof(size_t));
	this->offset = (size_t*)malloc(this->amount * sizeof(size_t));
	for (i = 0; i < this->amount; i++)
	{
		*(this->row + i) = *(V.row + i);
		*(this->column + i) = *(V.column + i);
		*(this->offset + i) = *(V.offset + i);
	}
	return;
}
void matrix_list::matout(dvector & V, size_t h, matrix & M)
{
	h = h % this->amount;
	M.row = *(this->row + h);
	M.column = *(this->column + h);
	M.mat = V.Vector() + *(this->offset + h);
	M.size = M.row * M.column;
	return;
}
