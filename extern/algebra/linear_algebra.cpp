#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
#define _MKL_LIB_EXIST_YET_LALALA_						 
#ifdef _MKL_LIB_EXIST_YET_LALALA_
extern "C" {
	#include <mkl.h>
	#include <mkl_scalapack.h>
}
#endif // _MKL_LIB_EXIST_YET_LALALA_
#include"linear_algebra.h"





int algebra_core::if_intial = 0;
unsigned int algebra_core::Cores = 1;
unsigned int algebra_core::cores_uses = 1;
pthread_t *algebra_core::handle = NULL;
sem_t algebra_core::barrier_sem;
enum algebra_core_instruct
{
	shut_down,
	sum_of_mat_row
};
struct algebra_core_argu
{
	sem_t *barrier_sem;
	enum algebra_core_instruct *aci;
};
void algebra_core_server(void* argu);
void algebra_core::initial(unsigned int cores, unsigned int use)
{
	if_intial = 1;
	Cores = cores;
	cores_uses = use < Cores ? use : Cores;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	mkl_set_num_threads(cores_uses);
	#endif
	sem_init(&barrier_sem, 0, 0); 
	handle = NULL;
}
void algebra_core::shut_down(void)
{
	if(!if_intial) return;
	if_intial = 0;
	free((void*)handle);
	sem_destroy(&barrier_sem);
}
void algebra_core::set_cores_use(unsigned int use)
{
	cores_uses = use < Cores ? use : Cores;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	mkl_set_num_threads(cores_uses);
	#endif
}
algebra_core::algebra_core()
{
}
algebra_core::~algebra_core()
{
}
void algebra_core_server(void* argu)
{
	sem_t *barrier_sem;
	enum algebra_core_instruct *Ins;
	struct algebra_core_argu *Argu;
	Argu = (algebra_core_argu *)argu;
	int judge;
	judge = 1;
	while(judge){
	sem_wait(barrier_sem);
	switch(*Ins)
	{
		case sum_of_mat_row:
			break;
		case shut_down:
			judge = 0;
			break;
		default:
			judge = 0;
			break;
	}
}}
int algebra_core::normalize_each_row(double* mat, const double* min, const double* max, size_t row, size_t column)
{
	size_t i, j;
	double half, coeff, temp;
	for (i = 0; i < row; i++)
	{
		half = (max[i] + min[i]) * 0.5;
		coeff = 2.0 / (max[i] - min[i]);
		if (coeff <= 0.0) return 1;
		for (j = 0; j < column; j++)
		{
			temp = mat[i * column + j];
			temp = (temp - half) * coeff;
			mat[i * column + j] = temp;
		}
	}
	return 0;
}
void algebra_core::minmax_of_row_and_trans(const double* from, double* to, double* min, double* max, size_t row, size_t column)
{
	size_t i, j;
	double temp;
	for (j = 0; j < column; j++)
	{
		temp = from[j];
		min[j] = temp;
		max[j] = temp;
		to[j * row] = temp;
	}
	for (j = 0; j < column; j++)
	{
		for (i = 1; i < row; i++)
		{
			temp = from[i * column + j];
			min[j] = (min[j] < temp ? min[j] : temp);
			max[j] = (max[j] > temp ? max[j] : temp);
			to[j * row + i] = temp;
		}
	}
}
void algebra_core::minmax_of_row_and_trans(const double* from, double* to, const int* sort, double* min, double* max, size_t row, size_t column)
{
	size_t i, j;
	size_t site;
	double temp;
	site = sort[0];
	for (j = 0; j < column; j++)
	{
		temp = from[site * column + j];
		min[j] = temp;
		max[j] = temp;
		to[j * row] = temp;
	}
	for (j = 0; j < column; j++)
	{
		for (i = 1; i < row; i++)
		{
			site = sort[i];
			temp = from[site * column + j];
			min[j] = (min[j] < temp ? min[j] : temp);
			max[j] = (max[j] > temp ? max[j] : temp);
			to[j * row + i] = temp;
		}
	}
}
void algebra_core::result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const double* min, const double* max, size_t row, size_t column)
{
	size_t i, j;
	double middle, interval;
	const double *From;
	double *To;
	for(i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To =  to + i * ldt;
		middle = (max[i] + min[i]) * 0.5;
		interval = (max[i] - min[i]) * 0.5;
		for(j = 0; j < column; j++)
			To[j] = From[j] * interval + middle;
	}
	return;
}
void algebra_core::result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const int* sort, const double* min, const double* max, size_t row, size_t column)
{
	size_t i, j, site;
	double middle, interval;
	const double *From;
	double *To;
	for(i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To =  to + i * ldt;
		middle = (max[i] + min[i]) * 0.5;
		interval = (max[i] - min[i]) * 0.5;
		for(j = 0; j < column; j++)
		{
			site = sort[j];
			To[site] = From[j] * interval + middle;
		}	
	}
	return;
}


double* algebra_core::copy_malloc(size_t length, const double* old)
{
	double* new_one;
	size_t i;
	new_one = (double*)malloc(sizeof(double) * length);
	for (i = 0; i < length; i++)
		new_one[i] = old[i];
	return new_one;
}
int* algebra_core::copy_malloc(size_t length, const int* old)
{
	int* new_one;
	size_t i;
	new_one = (int*)malloc(sizeof(int) * length);
	for (i = 0; i < length; i++)
		new_one[i] = old[i];
	return new_one;
}
void algebra_core::data_copy_core(const double* from, double* to, size_t data_amount) 
{
	size_t i;
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	cblas_dcopy(data_amount, from, 1, to, 1);
#else
	for (i = 0; i < data_amount; i++)
		to[i] = from[i];
#endif
}
inline double algebra_core::inner_dot(const double* left, const double* right, size_t amount, size_t incr_l, size_t incr_r)
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



double algebra_core::Euclidean_norm_distance(const double* mat1, size_t ld1, const double *mat2, size_t ld2, const double *weights_ld, const double *weights_follow, size_t row, size_t column)
{
	double rmse, weights, temp, line;
	size_t i, j;
	rmse = 0.0;
	if(weights_ld == NULL)
	{
		for	(i = 0; i < row; i++)
		{
			line = 0.0;
			for	(j = 0; j < column; j++)
			{
				temp = mat1[i * ld1 + j] - mat2[i * ld2 + j];
				line += temp * temp;
			}
			rmse += weights_follow == NULL ? line :  line * weights_follow[i];
		}
	}
	else
	{
		for	(i = 0; i < row; i++)
		{
			line = 0.0;
			for	(j = 0; j < column; j++)
			{
				weights = weights_ld[j];
				temp = mat1[i * ld1 + j] - mat2[i * ld2 + j];
				line += temp * temp * weights;
			}
			rmse += weights_follow == NULL ? line :  line * weights_follow[i];
		}
	}
	return sqrt(rmse);
}
void algebra_core::error_gradient_back_init(const double* mat_real, size_t ldr, const double *mat_out, size_t ldo, const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld)
{
	size_t i, j;
	double weight, weight_major;
	double *line;
	const double *Real, *Out;
	if(weights_ld == NULL)
	{
		for	(i = 0; i < row; i++)
		{
			line = init + i * ld;
			Real = mat_real + i * ldr;
			Out = mat_out + i * ldo;
			weight_major = ((weights_row == NULL) ? 1.0 : weights_row[i]);
			for	(j = 0; j < column; j++)
			{
				weight = Real[j] - Out[j];
				line[j] = weight_major * weight;
			}
		}
	}
	else
	{
		for	(i = 0; i < row; i++)
		{
			line = init + i * ld;
			Real = mat_real + i * ldr;
			Out = mat_out + i * ldo;
			weight_major = ((weights_row == NULL) ? 1.0 : weights_row[i]);
			for	(j = 0; j < column; j++)
			{
				weight = weights_ld[j] * (Real[j] - Out[j]);
				line[j] = weight_major * weight;
			}
		}
	}
	
}
void algebra_core::energy_gradient_back_init(const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld)
{
	size_t i, j;
	double weight, weight_major;
	double *line;
	if(weights_ld == NULL)
	{
		for	(i = 0; i < row; i++)
		{
			line = init + i * ld;
			weight_major = ((weights_row == NULL) ? 1.0 : sqrt(weights_row[i]));
			for	(j = 0; j < column; j++)
				line[j] = weight_major;
		}
	}
	else
	{
		for	(i = 0; i < row; i++)
		{
			line = init + i * ld;
			weight_major = ((weights_row == NULL) ? 1.0 : sqrt(weights_row[i]));
			for	(j = 0; j < column; j++)
			{
				weight = sqrt(weights_ld[j]);
				line[j] = weight_major * weight;
			}
		}
	}
	
}



//void algebra_core::matrix_from_vector_per_row(double*mat, const double* vec, size_t row, size_t column, size_t ldm, size_t incr)
//{
//	size_t i, j;
//	double temp, *line;
//	for(i = 0; i < row; i++)
//	{
//		temp = vec[i * incr];
//		line = mat + i * ldm;
//		for	(j = 0; j < column; j++)
//			line[j] = temp;
//	}
//}

//========================================================================
//class algebra_vector
//========================================================================
algebra_vector::algebra_vector(/* args */)
{
}
algebra_vector::~algebra_vector()
{
}
void algebra_vector::value(double*vec, double value, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
		vec[i] = value;
}
void algebra_vector::copy(double* from, double *to, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i];
}
void algebra_vector::copy(double* from, double *to, size_t length, double alpha, double beta)//to = from*alpha + beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * alpha + beta;
}
void algebra_vector::add(double* from, double *to, size_t length, double alpha, double beta)//to = from*alpha + to*beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * alpha + to[i] * beta;
}
void algebra_vector::add_elementwise_square(double* from, double *to, size_t length, double alpha, double beta)//to = from_elementwise_square*alpha + to*beta
{
	size_t i;
	for (i = 0; i < length; i++)
		to[i] = from[i] * from[i] * alpha + to[i] * beta;
	return;
}
void algebra_vector::Adam_refresh(double* w_b, const double *m1, const double *m2, size_t length, double alpha, double epsilon)
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

void algebra_vector::Tanh(double* from, double *to, size_t length)
{
	size_t i;
	for (i = 0; i < length; i++)
         to[i] = tanh(from[i]);
}
void algebra_vector::algebraic(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = x / sqrt(x * x + 1.0);
	}
         
}
void algebra_vector::Cos(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = cos(x);
	}     
}
void algebra_vector::gaussain(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = exp(-0.5 * x * x);
	}     
}
void algebra_vector::reciprocal(double* from, double *to, size_t length)
{
	size_t i;
	double x;
	for (i = 0; i < length; i++)
	{
		x = from[i];
		to[i] = 1.0 / sqrt(x * x + 1.0);
	}     
}


void algebra_vector::backward_tanh(double* from, double *to, const double* forward, size_t length)
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
void algebra_vector::backward_algebraic(double* from, double *to, const double* forward, size_t length)
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
void algebra_vector::backward_cos(double *from, double *to, const double* forward_in, size_t length)
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
void algebra_vector::backward_gaussain(double *from, double *to, const double* forward_in, size_t length)
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
void algebra_vector::backward_reciprocal(double *from, double *to, const double* forward_in, size_t length)
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

size_t algebra_vector::count_nan(const double *vector, size_t length)
{
	size_t count, i;
	count = 0;
	for (i = 0; i < length; i++)
		count += (isnan(vector[i]) ? 1 : 0);
	return count;
}

//========================================================================
//class algebra_matrix
//========================================================================
algebra_matrix::algebra_matrix(/* args */)
{
}
algebra_matrix::~algebra_matrix()
{
}

void algebra_matrix::transposition(double **mat, size_t row, size_t column, size_t ld, size_t new_extra_ld)
{
	size_t i, j;
	size_t New_ld;
	double *temp, *old;
	New_ld = new_extra_ld + row;
	temp = (double*)malloc(sizeof(double) * New_ld * column);
	old = *mat;
	for ( i = 0; i < row; i++)
		for ( j = 0; j < column; j++)
			temp[j * New_ld + i] = old[i * ld + j];
	free((void*)old);
	*mat = temp;
	return;
}
void algebra_matrix::transposition(size_t row, size_t column, const double *from, size_t ldf, double *to, size_t ldt)
{
	size_t i, j;
	for ( i = 0; i < row; i++)
		for ( j = 0; j < column; j++)
			to[j * ldt + i] = from[i * ldf + j];
}


void algebra_matrix::diagonal_add(double *mat, size_t row, size_t ld, double addend)
{
	size_t i;
	for	(i = 0; i < row; i++)
		mat[i * ld + i] += addend;
}
void algebra_matrix::diagonal_expand(double *mat, size_t row, size_t ld, double addend)
{
	size_t i;
	for	(i = 0; i < row; i++)
		mat[i * ld + i] += addend * mat[i * ld + i];
}
void algebra_matrix::sym_mat_compress(size_t row_col, size_t ld, const double *mat, double *compressed, enum HyperAlgebra::Uplo T)
{
	size_t i, j, site;
	const double *temp;
	site = 0;
	if(T == HyperAlgebra::lower)
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
void algebra_matrix::sym_mat_uncompress(size_t row_col, size_t ld, double *mat, const double *compressed, enum HyperAlgebra::Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == HyperAlgebra::lower)
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
void algebra_matrix::sym_mat_uncompress(size_t row_col, size_t ld, double lambda, double *mat, const double *compressed, enum HyperAlgebra::Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == HyperAlgebra::lower)
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
void algebra_matrix::sym_mat_uncompress_expand(size_t row_col, size_t ld, double factor, double *mat, const double *compressed, enum HyperAlgebra::Uplo T)
{
	size_t i, j, site;
	double *temp;
	site = 0;
	if(T == HyperAlgebra::lower)
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
void algebra_matrix::matrix_from_vector_per_row(double*mat, const double* vec, size_t row, size_t column, size_t ldm, size_t incr)
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
void algebra_matrix::matrix_shard_copy(size_t ldf, size_t ldt, size_t rows, size_t ele_per_rows, const double* from, double* to)
{
	size_t i, j;
	double *target;
	const double *source;
	for (i = 0; i < rows; i++)
	{
		target = to + i * ldt;
		source = from + i * ldf;
		for (j = 0; j < ele_per_rows; j++)
			target[j] = source[j];
	}
	return;
}
void algebra_matrix::sum_of_mat_row(size_t row, size_t column, size_t ld, const double *temp, double *result, double alpha, double beta)
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
void algebra_matrix::sum_of_column(size_t row, size_t column, size_t ld, const double *temp, double *result, double alpha, double beta)
{
	size_t i, j;
	double sum;
	const double *From;
	for (i = 0; i < column; i++)
	{
		sum = 0.0;
		From = temp + i;
		for(j = 0; j < row; j++)
			sum += From[j * ld];
		result[i] = alpha * sum + beta * result[i];
	}
	
}
void algebra_matrix::matrix_shard_product(size_t ldm, size_t ldf, size_t ldt, size_t ld_index, size_t row_m, size_t row_f, size_t ele_per_row, const double* major, const double* follow, double* to)
{
	size_t i, j, k;
	size_t index, index_base;
	double left, right, temp;
	const double *Major, *Follow;
	double *To;
	for (k = 0; k < ele_per_row; k++)
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


void algebra_matrix::Tanh(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
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
void algebra_matrix::algebraic(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
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
void algebra_matrix::Cos(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
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
void algebra_matrix::gaussain(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
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
void algebra_matrix::reciprocal(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt)
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

void algebra_matrix::backward_tanh(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
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
void algebra_matrix::backward_algebraic(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
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
void algebra_matrix::backward_cos(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
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
void algebra_matrix::backward_gaussain(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
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
void algebra_matrix::backward_reciprocal(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward)
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

void algebra_matrix::set_matrix(size_t row, size_t column, const double* from, size_t ldf, double* to, size_t ldt)
{
	size_t i, j;
	const double *From;
	double* To;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
			To[j] = From[j];
	}
}
void algebra_matrix::get_matrix(size_t row, size_t column, const double* from, size_t ldf, double* to, size_t ldt)
{
	size_t i, j;
	const double *From;
	double* To;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
			To[j] = From[j];
	}
}
double *algebra_matrix::dmat_malloc(size_t ld, size_t row)
{
	return (double*)malloc(sizeof(double) * ld * row);
}
double *algebra_matrix::dmat_reshape(size_t ld, size_t row, double *old)
{
	free((void*)old);
	return (double*)malloc(sizeof(double) * ld * row);
}

void algebra_matrix::copy(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, double alpha, double beta)
{
	size_t i, j;
	const double *From;
	double* To;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		for (j = 0; j < column; j++)
			To[j] = From[j] * alpha + beta;
	}
	
}
void algebra_matrix::copysy(enum HyperAlgebra::Uplo T, const double *from, size_t ldf, double *to, size_t ldt, size_t dim, double alpha, double beta)
{
	size_t i, j;
	if(T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
			for (j = i; j < dim; j++)
				to[i * ldt + j] = from[i * ldf + j] * alpha + beta;
	}
	else
	{
		for (i = 0; i < dim; i++)
			for (j = 0; j <= i; j++)
				to[i * ldt + j] = from[i * ldf + j] * alpha + beta;
	}
}
void algebra_matrix::copy(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, const double* alpha, const double* beta)
{
	size_t i, j;
	const double *From;
	double* To;
	double Alpha, Beta;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Alpha = alpha[i];
		Beta = beta[i];
		for (j = 0; j < column; j++)
			To[j] = From[j] * Alpha + Beta;
	}
	
}
void algebra_matrix::add(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, double alpha, const double *beta, const double *gamma)
{
	size_t i, j;
	const double *From;
	double* To;
	double Gamma, Beta;
	for (i = 0; i < row; i++)
	{
		From = from + i * ldf;
		To = to + i * ldt;
		Gamma = gamma[i];
		Beta = beta[i];
		for (j = 0; j < column; j++)
			To[j] = To[j] * alpha + From[j] * Beta + Gamma;
	}
}
void algebra_matrix::value(double *mat, size_t ld, size_t row, size_t column, double value)
{
	size_t i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			mat[i * ld + j] = value;
}
double algebra_matrix::norm(const double *mat1, size_t ld1, const double *mat2, size_t ld2, size_t row, size_t column)
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
double algebra_matrix::normsy(enum HyperAlgebra::Uplo T, const double *mat1, size_t ld1, const double *mat2, size_t ld2, size_t dim)
{
	double result, temp;
	const double * Line1, *Line2;
	size_t i, j;
	result = 0.0;
	if(T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
		{
			Line1 = mat1 + i * ld1;
			Line2 = mat2 + i * ld2;
			for (j = i; j < dim; j++)
			{
				temp = fabs(Line1[j] - Line2[j]);
				result = result > temp ? result : temp;
			}
		}
	}
	else
	{
		for (i = 0; i < dim; i++)
		{
			Line1 = mat1 + i * ld1;
			Line2 = mat2 + i * ld2;
			for (j = 0; j <= i; j++)
			{
				temp = fabs(Line1[j] - Line2[j]);
				result = result > temp ? result : temp;
			}
		}
	}
	
	return result;
}
void algebra_matrix::foldsy(enum HyperAlgebra::Uplo T, double *mat, size_t ld, size_t dim)
{
	size_t i, j;
	if(T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
			for (j = i + 1; j < dim; j++)
				mat[j * ld + i] = mat[i * ld + j];
	}
	else
	{
		for (i = 0; i < dim; i++)
			for (j = 0; j < i; j++)
				mat[j * ld + i] = mat[i * ld + j];
	}
}
void algebra_matrix::symv(enum HyperAlgebra::Uplo T, const double *mat, size_t ldm, size_t dim, const double *x, double alpha, double* y, double beta)
{
	size_t i, j;
	double sum;
	if(T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
		{
			sum = 0.0;
			for (j = 0; j < i; j++)
				sum += mat[j * ldm + i] * x[j]; 
			for (j = i; j < dim; j++)
				sum += mat[i * ldm + j] * x[j]; 
			y[i] = sum * alpha + y[i] * beta;
		}
	}
	else
	{
		for (i = 0; i < dim; i++)
		{
			sum = 0.0;
			for (j = 0; j < i; j++)
				sum += mat[i * ldm + j] * x[j]; 
			for (j = i; j < dim; j++)
				sum += mat[j * ldm + i] * x[j]; 
			y[i] = sum * alpha + y[i] * beta;
		}
	}
}
double algebra_matrix::syfabsmax(enum HyperAlgebra::Uplo T, const double *mat, size_t ldm, size_t dim)
{
	double Max;
	double temp;
	size_t i, j;
	Max = 0.0;
	if(T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
		{
			for (j = i; j < dim; j++)
			{
				temp = abs(mat[i * ldm + j]);
				Max = (Max > temp ? Max : temp);
			}
		}
	}
	else
	{
		for (i = 0; i < dim; i++)
		{
			for (j = 0; j <= i; j++)
			{
				temp = abs(mat[i * ldm + j]);
				Max = (Max > temp ? Max : temp);
			}
		}
	}
	return Max;
}
void algebra_matrix::dotscalar(double *mat, size_t ldm, size_t row, size_t column, double alpha)
{
	size_t i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
			mat[i * ldm + j] *= alpha;
	}
}
//========================================================================
//class algebra_mkl
//========================================================================
algebra_mkl::algebra_mkl(/* args */)
{
}
algebra_mkl::~algebra_mkl()
{
}
void algebra_mkl::gemmNN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = inner_dot(L + i * ld_L, R + j, middle, 1, ld_R);
	return;
}
void algebra_mkl::gemmNT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = inner_dot(L + i * ld_L, R + j * ld_R, middle, 1, 1);
}
void algebra_mkl::gemmTN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = inner_dot(L + i, R + j, middle, ld_L, ld_R);
}
void algebra_mkl::gemmTT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out)
{
	size_t i, j;
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = inner_dot(L + i, R + j * ld_R, middle, ld_L, 1);
}
void algebra_mkl::syrk_JJT_lower(size_t middle, size_t result, const double* J, double* C, size_t ld_J, size_t ld_C)
{
	size_t i, j;
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = inner_dot(J + i * ld_J, J + j * ld_J, middle, 1, 1);
	return;
}
void algebra_mkl::syrk_JTJ_lower(size_t middle, size_t result, const double* J, double* C, size_t ld_J, size_t ld_C)
{
	size_t i, j;
	for (i = 0; i < result; i++)
		for (j = 0; j <= i; j++)
			C[i * ld_C + j] = inner_dot(J + i, J + j, middle, ld_J, ld_J);
	return;
}

void algebra_mkl::gemmNN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out)
{
	size_t i, j;
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE transL, trnasR;
	Layout = CblasRowMajor;
	transL = CblasNoTrans;
	trnasR = CblasNoTrans;
	cblas_dgemm(Layout, transL, trnasR, left, right, middle, alpha, L, ld_L, R, ld_R, beta, Out, ld_O);
	#else
	for (i = 0; i < left; i++)
		for (j = 0; j < right; j++)
			Out[i * ld_O + j] = alpha * inner_dot(L + i * ld_L, R + j, middle, 1, ld_R) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void algebra_mkl::gemmNT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out)
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
			Out[i * ld_O + j] = alpha * inner_dot(L + i * ld_L, R + j * ld_R, middle, 1, 1) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void algebra_mkl::gemmTN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out)
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
			Out[i * ld_O + j] = alpha * inner_dot(L + i, R + j, middle, ld_L, ld_R) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void algebra_mkl::gemmTT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out)
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
			Out[i * ld_O + j] = alpha * inner_dot(L + i, R + j * ld_R, middle, ld_L, 1) + beta * Out[i * ld_O + j];
	#endif
	return;
}
void algebra_mkl::syrk_JJT_lower(size_t middle, size_t result, double alpha, const double* J, double beta, double* C, size_t ld_J, size_t ld_C)
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
			C[i * ld_C + j] = alpha * inner_dot(J + i * ld_J, J + j * ld_J, middle, 1, 1) + beta * C[i * ld_C + j];
	#endif
	return;
}
void algebra_mkl::syrk_JTJ_lower(size_t middle, size_t result, double alpha, const double* J, double beta, double* C, size_t ld_J, size_t ld_C)
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
			C[i * ld_C + j] = alpha * inner_dot(J + i, J + j, middle, ld_J, ld_J) + beta * C[i * ld_C + j];
	#endif
	return;
}

void algebra_mkl::syrkAAT(enum HyperAlgebra::Uplo T, const double* A, double alpha, size_t ldA, double* to, double beta, size_t ldt, size_t dummy, size_t dim)
{
	//if trans=CblasNoTrans, then C := alpha*A*A' + beta*C;
	//void cblas_dsyrk (const CBLAS_LAYOUT Layout, const CBLAS_UPLO uplo, const
	//CBLAS_TRANSPOSE trans, const MKL_INT n, const MKL_INT k, const double alpha, const
	//	double* a, const MKL_INT lda, const double beta, double* c, const MKL_INT ldc);
	// n :Specifies the order of the matrix C. The value of n must be at least zero.
	//k On entry with trans=CblasNoTrans, k specifies the number of columns of
	//the matrix a, and on entry with trans = CblasTrans or
	//trans = CblasConjTrans, k specifies the number of rows of the matrix a.
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	CBLAS_UPLO uplo;
	Layout = CblasRowMajor;
	trans = CblasNoTrans;
	uplo = (T == HyperAlgebra::upper ? CblasUpper : CblasLower);
	cblas_dsyrk(Layout, uplo, trans, dim, dummy, alpha, A, ldA, beta, to, ldt);
#else
	size_t i, j, k;
	double value;
	if (T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
			for (j = i; j < dim; j++)
			{
				value = 0.0;
				for (k = 0; k < dummy; k++)
					value += A[i * ldA + k] * A[j * ldA + k];
				to[i * ldt + j] = alpha * value + beta * to[i * ldt + j];
			}
	}
	else
	{
		for (i = 0; i < dim; i++)
			for (j = 0; j <= i; j++)
			{
				value = 0.0;
				for (k = 0; k < dummy; k++)
					value += A[i * ldA + k] * A[j * ldA + k];
				to[i * ldt + j] = alpha * value + beta * to[i * ldt + j];
			}
	}
	
#endif
}
void algebra_mkl::syrkATA(enum HyperAlgebra::Uplo T, const double* A, double alpha, size_t ldA, double* to, double beta, size_t ldt, size_t dummy, size_t dim)
{
#ifdef _MKL_LIB_EXIST_YET_LALALA_
	CBLAS_LAYOUT Layout;
	CBLAS_TRANSPOSE trans;
	CBLAS_UPLO uplo;
	Layout = CblasRowMajor;
	trans = CblasTrans;
	uplo = (T == HyperAlgebra::upper ? CblasUpper : CblasLower);
	cblas_dsyrk(Layout, uplo, trans, dim, dummy, alpha, A, ldA, beta, to, ldt);
#else
	size_t i, j, k;
	double value;
	if (T == HyperAlgebra::upper)
	{
		for (i = 0; i < dim; i++)
			for (j = i; j < dim; j++)
			{
				value = 0.0;
				for (k = 0; k < dummy; k++)
					value += A[k * ldA + i] * A[k * ldA + j];
				to[i * ldt + j] = alpha * value + beta * to[i * ldt + j];
			}
	}
	else
	{
		for (i = 0; i < dim; i++)
			for (j = 0; j <= i; j++)
			{
				value = 0.0;
				for (k = 0; k < dummy; k++)
					value += A[k * ldA + i] * A[k * ldA + j];
				to[i * ldt + j] = alpha * value + beta * to[i * ldt + j];
			}
	}
#endif
}

/*
int algebra_mkl::pdpotrf(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T)
{
	//void pdpotrf (char *uplo , MKL_INT *n , double *a , MKL_INT *ia , MKL_INT *ja , MKL_IN *desca , MKL_INT *info );
	//distributed n-by-n matrix A(ia:ia+n-1, ja:ja+n-1),
	//desca (global and local) array of size dlen_. The array descriptor for the distributed matrix A.
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	MKL_INT info;
	MKL_INT zero;
	MKL_INT N;
	MKL_INT desca;
	desca = ld;
	zero = 0;
	N = dim;
	if(T == HyperAlgebra::lower)
		pdpotrf('L', &N, mat, &zero, &zero, &desca, &info);
	else
		pdpotrf('U', &N, mat, &zero, &zero, &desca, &info);
	return info;
	#else
	return 0;
	#endif
}
int algebra_mkl::pdpotrs(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T, double *xb, int nrhs, size_t ldxb)
{
	//void pdpotrs (char *uplo , MKL_INT *n , MKL_INT *nrhs , double *a , MKL_INT *ia ,
	//MKL_INT *ja , MKL_INT *desca , double *b , MKL_INT *ib , MKL_INT *jb , MKL_INT *descb ,
	//MKL_INT *info );
	//B(ib:ib+n-1, jb:jb+nrhs-1) 
	//
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	MKL_INT info;
	MKL_INT zero;
	MKL_INT N, Nrhs;
	MKL_INT desca, descb;
	Nrhs = nrhs;
	desca = ld;
	descb = ldxb;
	zero = 0;
	N = dim;
	if(T == HyperAlgebra::lower)
		pdpotrs('L', &N, &Nrhs, mat, &zero, &zero, &desca, xb, &zero, &zero, &descb, &info);
	else
		pdpotrs('U', &N, &Nrhs, mat, &zero, &zero, &desca, xb, &zero, &zero, &descb, &info);
	return info;
	#else
	return 0;
	#endif
}
*/
int algebra_mkl::LAPACKE_dppsv(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T, double *xb, int nrhs, size_t ldxb)
{
	//lapack_int LAPACKE_dposv (int matrix_layout, char uplo, lapack_int n, lapack_int nrhs,
	//double * a, lapack_int lda, double * b, lapack_int ldb);
	#ifdef _MKL_LIB_EXIST_YET_LALALA_
	if(T == HyperAlgebra::lower)
		return LAPACKE_dposv(LAPACK_ROW_MAJOR, 'L', dim, nrhs, mat, ld, xb, ldxb);
	else
		return LAPACKE_dposv(LAPACK_ROW_MAJOR, 'U', dim, nrhs, mat, ld, xb, ldxb);
	#else
	return 0;
	#endif
}
int algebra_mkl::potrf(enum HyperAlgebra::Uplo T, double *mat, size_t dim, size_t ld)
{
	size_t i, j, k;
	int info;
	double aii, lii;
	if (T == HyperAlgebra::lower)
	{
		for (i = 0; i < dim; i++)
		{
			aii = mat[i * ld + i];
			if (aii <= 0)
			{
				info = i;
				return -info;
			}
			lii = sqrt(aii);
			mat[i * ld + i] = lii;
			lii = 1.0 / lii;
			for (j = i + 1; j < dim; j++)
				mat[j * ld + i] *= lii;
			for (j = i + 1; j < dim; j++)
				for (k = j; k < dim; k++)
					mat[k * ld + j] -= mat[j * ld + i] * mat[k * ld + i];
		}
	}
	else
	{
		for (i = 0; i < dim; i++)
		{
			aii = mat[i * ld + i];
			if (aii <= 0)
			{
				info = i;
				return -info;
			}
			lii = sqrt(aii);
			mat[i * ld + i] = lii;
			lii = 1.0 / lii;
			for (j = i + 1; j < dim; j++)
				mat[i * ld + j] *= lii;
			for (j = i + 1; j < dim; j++)
				for (k = j; k < dim; k++)
					mat[j * ld + k] -= mat[i * ld + j] * mat[i * ld + k];
		}
	}
	return 0;
}
void algebra_mkl::potrs(enum HyperAlgebra::Uplo T, const double *mat, size_t dim, size_t ld, double *xb, int nrhs, size_t ldxb)
{
	size_t i, j, index;
	int k;
	double aii;
	if (T == HyperAlgebra::lower)
	{
		for (i = 0; i < dim; i++)
		{
			aii = mat[i * ld + i];
			for (k = 0; k < nrhs; k++)
				xb[i * ldxb + k] = xb[i * ldxb + k] / aii;
			for (j = i + 1; j < dim; j++)
			{
				for (k = 0; k < nrhs; k++)
					xb[j * ldxb + k] -= xb[i * ldxb + k] * mat[j * ld + i];
			}
		}
		for (index = 1; index <= dim; index++)
		{
			i = dim - index;
			aii = mat[i * ld + i];
			for (k = 0; k < nrhs; k++)
				xb[i * ldxb + k] = xb[i * ldxb + k] / aii;
			for (j = 0; j < i; j++)
			{
				for (k = 0; k < nrhs; k++)
					xb[j * ldxb + k] -= xb[i * ldxb + k] * mat[i * ld + j];
			}
		}
	}
	else
	{
		for (i = 0; i < dim; i++)
		{
			aii = mat[i * ld + i];
			for (k = 0; k < nrhs; k++)
				xb[i * ldxb + k] = xb[i * ldxb + k] / aii;
			for (j = i + 1; j < dim; j++)
			{
				for (k = 0; k < nrhs; k++)
					xb[j * ldxb + k] -= xb[i * ldxb + k] * mat[i * ld + j];
			}
		}
		for (index = 1; index <= dim; index++)
		{
			i = dim - index;
			aii = mat[i * ld + i];
			for (k = 0; k < nrhs; k++)
				xb[i * ldxb + k] = xb[i * ldxb + k] / aii;
			for (j = 0; j < i; j++)
			{
				for (k = 0; k < nrhs; k++)
					xb[j * ldxb + k] -= xb[i * ldxb + k] * mat[j * ld + i];
			}
		}
	}
}
int algebra_mkl::potrfs(enum HyperAlgebra::Uplo T, double *mat, size_t dim, size_t ld, double *xb, int nrhs, size_t ldxb)
{
	int info;
	info = potrf(T, mat, dim, ld);
	if(info == 0) potrs(T, mat, dim, ld, xb, nrhs, ldxb);
	return info;
}


special_func::special_func()
{
}
special_func::~special_func()
{
}
double special_func::special_error_2_6(const double *true_value, const double *result, size_t length, const double* weight)
{
	size_t i;
	double loss, delta, accum;
	loss = 0.0;
	for (i = 0; i < length; i++)
	{
		delta = true_value[i] - result[i];
		delta = delta * delta;
		accum = delta * weight[2 * i] + delta * delta * delta * weight[2 * i + 1];
		loss += accum;
	}
	return sqrt(loss);
}
void special_func::special_gradient_2_6(const double *true_value, const double *result, size_t length, const double* weight, double *output)
{
	size_t i;
	double loss, delta, square;
	for (i = 0; i < length; i++)
	{
		delta = true_value[i] - result[i];
		square = delta * delta;
		loss = delta * weight[2 * i] + 3.0 * delta * square * square * weight[2 * i + 1];
		output[i] = loss;
	}
	return;
}
void special_func::special_jacobi_2_6(const double *true_value, const double *result, size_t length, const double* weight, double *output)
{
	size_t i;
	double loss, delta, square;
	for (i = 0; i < length; i++)
	{
		delta = true_value[i] - result[i];
		square = delta * delta;
		loss = sqrt(weight[2 * i]) + 3.0 * square * sqrt(weight[2 * i + 1]);
		output[i] = loss;
	}
	return;
}
//========================================================================
//algebra_log 
//========================================================================
//algebra_log::algebra_log()
//{
//	log = NULL;
//	inout = NULL;
//}


string static path_add_file_name(const string& path, const string& name)
{
	string fusion;
	if (path[path.length() - 1] == '/')
		fusion = path + name;
	else
		fusion = path + '/' + name;
	return fusion;
}


algebra_log::algebra_log()
{
	//log = fopen("./log/algebra_log.txt", "a+");
	//if (log == NULL)
	//{
	//	fprintf(stderr, "WARNING: FAILURE OPEN:%s\n", "./log/algebra_log.txt");
	//	exit(1);
	//}
	inout = NULL;
	return;
}
algebra_log::~algebra_log()
{
	//if (log != NULL)
	//	fclose(log);
	if (inout != NULL)
	{
		fclose(inout);
		//printf("aAAAAaaa\n");
	}
	return;
}
void algebra_log::open_log(void)
{
	//this->log = fopen("./log/algebra_log.txt", "a+");
	//if (this->log == NULL)
	//{
	//	fprintf(stderr, "WARNING: FAILURE OPEN:%s\n", "./log/algebra_log.txt");
	//	exit(1);
	//}
}
void algebra_log::bitwise_store_open(const char* path, const char* name)
{
	string dir;
	string file;
	string Name;
	if (path == NULL)
		dir = "./log/";
	else
		dir = path;
	if (name == NULL)
		file = "default.bitwise";
	else
		file = name;
	Name = path_add_file_name(dir, file);
	this->inout = fopen(Name.c_str(), "wb");
	if (this->inout == NULL)
	{
		fprintf(stderr, "WARNING: FAILURE OPEN:%s\n", Name.c_str());
		exit(1);
	}
	//if (this->log != NULL)
	//	fprintf(this->log, "OPEN:%s\n", dir.c_str());
}
void algebra_log::bitwise_store_lld(const size_t& store)
{
	if (this->inout == NULL) return;
	fwrite(&store, sizeof(size_t), 1, this->inout);
}
void algebra_log::bitwise_store_lld(const long long int& store)
{
	if (this->inout == NULL) return;
	fwrite(&store, sizeof(long long int), 1, this->inout);
}
void algebra_log::bitwise_store_lfvector(size_t size, const double* store)
{
	if (this->inout == NULL) return;
	fwrite(store, sizeof(double), size, this->inout);
}
void algebra_log::bitwise_load_open(const char* path, const char* name)
{
	string dir;
	string file;
	string Name;
	if (path == NULL)
		dir = "./log/";
	else
		dir = path;
	if (name == NULL)
		file = "default.bitwise";
	else
		file = name;
	Name = path_add_file_name(dir, file);
	this->inout = fopen(Name.c_str(), "rb");
	if (this->inout == NULL)
	{
		fprintf(stderr, "WARNING: FAILURE OPEN:%s\n", Name.c_str());
		exit(1);
	}
	//if (this->log != NULL)
	//	fprintf(this->log, "OPEN:%s\n", dir.c_str());
}
void algebra_log::bitwise_load_lld(long long int* load)
{
	if (this->inout == NULL) return;
	*load = 0;
	fread(load, sizeof(long long int), 1, this->inout);
}
void algebra_log::bitwise_load_lld(size_t* load)
{
	if (this->inout == NULL) return;
	*load = 0;
	fread(load, sizeof(size_t), 1, this->inout);
}
void algebra_log::bitwise_load_lfvector(size_t size, double* load)
{
	if (this->inout == NULL) return;
	fread(load, sizeof(double), size, this->inout);
}
void algebra_log::check_input_equal(long long int a, long long int b, const char* function)
{
	if (a == b) return;
	fprintf(stderr, "The input parameters of function %s is incorrect,", function);
	fprintf(stderr, "they are %lld and %lld \n", a, b);
	fprintf(stderr, "To process the function successfully, they must be the same.\n");
	//fprintf(this->log, "The input parameters of function %s is incorrect,", function);
	//fprintf(this->log, "they are %lld and %lld \n", a, b);
	//fprintf(this->log, "To process the function successfully, they must be the same.\n");
	//if (this->log != NULL)
	//	fclose(this->log);
	if (this->inout != NULL)
		fclose(this->inout);
	exit(1);
	return;
}




