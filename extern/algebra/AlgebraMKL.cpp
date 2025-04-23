#include"HyperAlgebra.h"
//#include<stdio.h>
//#include<stdlib.h>
#include<cmath>

using namespace HyperAlgebra;

#define _MKL_LIB_EXIST_YET_LALALA_


#ifdef _MKL_LIB_EXIST_YET_LALALA_
extern "C" {
	#include <mkl.h>
	#include <mkl_scalapack.h>
}
#endif // _MKL_LIB_EXIST_YET_LALALA_
AlgebraMKL::AlgebraMKL(/* args */)
{
}
AlgebraMKL::~AlgebraMKL()
{
}

double AlgebraMKL::InnerDot(const double* left, const double* right, size_t amount, size_t incr_l, size_t incr_r)
{
	double dot;
	size_t i;
	dot = 0.0;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	dot = cblas_ddot(amount, left, incr_l, right, incr_r);
	#else
	for (i = 0; i < amount; i++)
		dot += left[i * incr_l] * right[i * incr_r];
	#endif

	return dot;
}
double AlgebraMKL::InnerDot(const double* left, const double* right, size_t length)
{
    double dot;
	size_t i;
	dot = 0.0;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	dot = cblas_ddot(length, left, 1, right, 1);
	#else
	for (i = 0; i < length; i++)
		dot += left[i] * right[i];
	#endif

	return dot;
}
void AlgebraMKL::gemmNN(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = InnerDot(L + i * ld_L, R + j, middle, 1, ld_R);
	return;
}
void AlgebraMKL::gemmNT(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = InnerDot(L + i * ld_L, R + j * ld_R, middle, 1, 1);
}
void AlgebraMKL::gemmTN(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = InnerDot(L + i, R + j, middle, ld_L, ld_R);
}
void AlgebraMKL::gemmTT(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = InnerDot(L + i, R + j * ld_R, middle, ld_L, 1);
}
void AlgebraMKL::syrkJJTlower(size_t middle, size_t result, const double* J, size_t ld_J, double* C, size_t ld_C)
{
	size_t i, j;
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = InnerDot(J + i * ld_J, J + j * ld_J, middle, 1, 1);
	return;
}
void AlgebraMKL::syrkJTJlower(size_t middle, size_t result, const double* J, size_t ld_J, double* C, size_t ld_C)
{
	size_t i, j;
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = InnerDot(J + i, J + j, middle, ld_J, ld_J);
	return;
}

//void cblas_dgemm (const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE transa, const
//CBLAS_TRANSPOSE transb, const MKL_INT m, const MKL_INT n, const MKL_INT k, const double
//alpha, const double *a, const MKL_INT lda, const double *b, const MKL_INT ldb, const
//double beta, double *c, const MKL_INT ldc);
void AlgebraMKL::gemmNN(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O)
{
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE transL, trnasR;
	Layout = CblasRowMajor;
	transL = CblasNoTrans;
	trnasR = CblasNoTrans;
	//Calpha*op(A)*op(B) + beta*C
	cblas_dgemm(Layout, transL, trnasR, left, right, middle, alpha, L, ld_L, R, ld_R, beta, Out, ld_O);
	#else
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = alpha * InnerDot(L + i * ld_L, R + j, middle, 1, ld_R) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void AlgebraMKL::gemmNT(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O)
{
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE transL, trnasR;
	Layout = CblasRowMajor;
	transL = CblasNoTrans;
	trnasR = CblasTrans;
	cblas_dgemm(Layout, transL, trnasR, left, right, middle, alpha, L, ld_L, R, ld_R, beta, Out, ld_O);
	#else
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = alpha * InnerDot(L + i * ld_L, R + j * ld_R, middle, 1, 1) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void AlgebraMKL::gemmTN(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O)
{
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE transL, trnasR;
	Layout = CblasRowMajor;
	transL = CblasTrans;
	trnasR = CblasNoTrans;
	cblas_dgemm(Layout, transL, trnasR, left, right, middle, alpha, L, ld_L, R, ld_R, beta, Out, ld_O);
	#else
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = alpha * InnerDot(L + i, R + j, middle, ld_L, ld_R) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void AlgebraMKL::gemmTT(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O)
{
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE transL, trnasR;
	Layout = CblasRowMajor;
	transL = CblasTrans;
	trnasR = CblasTrans;
	cblas_dgemm(Layout, transL, trnasR, left, right, middle, alpha, L, ld_L, R, ld_R, beta, Out, ld_O);
	#else
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = alpha * InnerDot(L + i, R + j * ld_R, middle, ld_L, 1) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void AlgebraMKL::syrkJJTlower(size_t middle, size_t result, double alpha, const double* J, size_t ld_J, double beta, double* C, size_t ld_C)
{
	//if trans=CblasNoTrans, then C := alpha*A*A' + beta*C;
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	Layout = CblasRowMajor;
	trans = CblasNoTrans;
	cblas_dsyrk(Layout, CblasLower, trans, result, middle, alpha, J, ld_J, beta, C, ld_C);
	#else
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = alpha * InnerDot(J + i * ld_J, J + j * ld_J, middle, 1, 1) + beta * C[i * ld_C + j];
	#endif
	return;
}
void AlgebraMKL::syrkJTJlower(size_t middle, size_t result, double alpha, const double* J, size_t ld_J, double beta, double* C, size_t ld_C)
{
	//if trans=CblasTrans, then C := alpha*A'*A + beta*C
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	Layout = CblasRowMajor;
	trans = CblasTrans;
	cblas_dsyrk(Layout, CblasLower, trans, result, middle, alpha, J, ld_J, beta, C, ld_C);
	#else
	size_t i, j;
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = alpha * InnerDot(J + i, J + j, middle, ld_J, ld_J) + beta * C[i * ld_C + j];
	#endif
	return;
}
int AlgebraMKL::LAPACKE_dppsv(double *mat, size_t ld, size_t dim, enum Uplo T, double *xb, int nrhs, size_t ldxb)
{
	//lapack_int LAPACKE_dposv (int matrix_layout, char uplo, lapack_int n, lapack_int nrhs,
	//double * a, lapack_int lda, double * b, lapack_int ldb);
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	if(T == lower)
		return LAPACKE_dposv(LAPACK_ROW_MAJOR, 'L', dim, nrhs, mat, ld, xb, ldxb);
	else
		return LAPACKE_dposv(LAPACK_ROW_MAJOR, 'U', dim, nrhs, mat, ld, xb, ldxb);
	#else
	return 0;
	#endif
}

double AlgebraMKL::Norm2(const double* vector, size_t length)
{
    double dot;
    //double cblas_dnrm2 (const MKL_INT n, const void *x, const MKL_INT incx);
    #ifdef _MKL_LIB_EXIST_YET_LALALA_
	dot = cblas_dnrm2(length, vector, 1);
	#else
    BasicVector BV;
	dot = BV.Norm2(vector, length);
	#endif
    return dot;
}

void AlgebraMKL::Substract(double *vector, size_t length, const double *subtrahend, double Norm2Square)
{
//void cblas_daxpy (const MKL_INT n, const double a, const double *x, const MKL_INT incx, double *y, const MKL_INT incy);
//y := a*x + y 
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    double inner, coeff;
    inner = cblas_ddot(length, vector, 1, subtrahend, 1);
    if(Norm2Square != 0.0) inner = inner / Norm2Square;
	coeff = -inner;
    cblas_daxpy(length, coeff, subtrahend, 1, vector, 1);
#else
    size_t i;
	double inner, coeff;
	inner = 0.0;
	for (i = 0; i < length; i++)
		inner += vector[i] * subtrahend[i];
	if(Norm2Square != 0.0) inner = inner / Norm2Square;
	coeff = -inner;
	for (i = 0; i < length; i++)
		vector[i] += coeff * subtrahend[i];
#endif
}
void AlgebraMKL::Norm2Normalization(double* vector, size_t length)
{
//void cblas_dscal (const MKL_INT n, const double a, double *x, const MKL_INT incx);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    double inner, coeff;
	inner = cblas_dnrm2(length, vector, 1);
    if(inner != 0.0)
	{
		coeff = 1.0 / inner;
		cblas_dscal(length, coeff, vector, 1);
	}
#else
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
#endif
}
void AlgebraMKL::FiniteDifference(double *result, size_t length, double DeltaReverse, const double *minuend, const double *subtrahend)
{
//void cblas_dcopy (const MKL_INT n, const double *x, const MKL_INT incx, double *y, const MKL_INT incy);
//void cblas_daxpy (const MKL_INT n, const double a, const double *x, const MKL_INT incx, double *y, const MKL_INT incy);
//y := a*x + y 
//void cblas_dscal (const MKL_INT n, const double a, double *x, const MKL_INT incx);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    cblas_dcopy (length, minuend, 1, result, 1);
    cblas_daxpy(length, -1.0, subtrahend, 1, result, 1);
    cblas_dscal(length, DeltaReverse, result, 1);
#else
	size_t i;
	for (i = 0; i < length; i++)
		result[i] = (minuend[i] - subtrahend[i]) * DeltaReverse;
#endif
}
//void cblas_dgemv (const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE trans, const MKL_INT
//m, const MKL_INT n, const double alpha, const double *a, const MKL_INT lda, const
//double *x, const MKL_INT incx, const double beta, double *y, const MKL_INT incy);
//if trans=CblasNoTrans, then y := alpha*A*x + beta*y;
//if trans=CblasTrans, then y := alpha*A'*x + beta*y;
// m row; n col
void AlgebraMKL::GEMVn(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	double alpha;
	double beta;
	Layout = CblasRowMajor;
	trans = CblasNoTrans;
	alpha = 1.0;
	beta = 0.0;
	cblas_dgemv(Layout, trans, row, col, alpha, Mat, ldM, vec, 1, beta, dst, 1);
#else
    size_t i, j;
	double value;
	for (i = 0; i < row; i++)
	{
		value = 0.0;
		for (j = 0; j < col; j++)
			value += Mat[i * ldM + j] * vec[j];
		dst[i] = value;
	}
#endif
}
void AlgebraMKL::GEMVt(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	double alpha;
	double beta;
	Layout = CblasRowMajor;
	trans = CblasTrans;
	alpha = 1.0;
	beta = 0.0;
	cblas_dgemv(Layout, trans, row, col, alpha, Mat, ldM, vec, 1, beta, dst, 1);
#else
    size_t i, j;
	double value;
	for (i = 0; i < col; i++)
	{
		value = 0.0;
		for (j = 0; j < row; j++)
			value += Mat[j * ldM + i] * vec[j];
		dst[i] = value;
	}
#endif
}
//dst = Mat ^ T * vec Mat: row * col row * ldM
void AlgebraMKL::MatColValueFromVec(double* MatTo, size_t ldM, size_t row, const double* vector)
{
//void cblas_dcopy (const MKL_INT n, const double *x, const MKL_INT incx, double *y, const MKL_INT incy);
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    cblas_dcopy(row, vector, 1, MatTo, ldM);
#else
    size_t i;
	for (i = 0; i < row; i++)
		MatTo[i * ldM] = vector[i];
#endif
}
void AlgebraMKL::MatRowValueFromVec(double* MatTo, size_t col, const double* vector)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
    cblas_dcopy(col, vector, 1, MatTo, 1);
#else
    size_t i;
	for (i = 0; i < col; i++)
		MatTo[i] = vector[i];
#endif
}


//lapack_int LAPACKE_dsyev (int matrix_layout, char jobz, char uplo, lapack_int n,
//double* a, lapack_int lda, double* w);

//If jobz = 'N', then only eigenvalues are computed.
//If jobz = 'V', then eigenvalues and eigenvectors are computed
int AlgebraMKL::MKLdsyev(enum Uplo T, size_t row, double *mat, size_t ldm, double* eigenvalues)
{
	int info;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	int matrix_layout;
	char jobz;
	char uplo;
	matrix_layout = (LAPACK_ROW_MAJOR);
	jobz = 'V';
	uplo = (T == upper ? 'U': 'L');
	info = LAPACKE_dsyev(matrix_layout, jobz, uplo, row, mat, ldm, eigenvalues);
	#else
	#endif
	return info;
}
