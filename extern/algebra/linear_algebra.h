#ifndef _LINEAR_algebra_HYP_H
#define _LINEAR_algebra_HYP_H
//#define UNDER_DEBUG_NOW
//#include"GPU_switch.h"
//#define _NVIDIA_GPU_ERVER_EXIST_
//#define _GPU_DEVICE_amount_Limit_ 16
//#define _MKL_LIB_EXIST_YET_LALALA_
#include<stdio.h>
#define GPU_OUTER___
#include"HyperAlgebra.h"
#include"random.h"
#undef GPU_OUTER___
class dvector;
class matrix;
class ivector;
class matrix_list;
class cuda_status;
class algebra_log;

extern "C"
{
	#include<pthread.h>
	#include<semaphore.h>
}





class algebra_core
{
public:
	algebra_core();
	~algebra_core();
	void initial(unsigned int cores, unsigned int use);
	void set_cores_use(unsigned int use);
	void shut_down(void);
	int normalize_each_row(double* mat, const double* min, const double* max, size_t row, size_t column);
	void minmax_of_row_and_trans(const double* from, double *to, double* min, double* max, size_t row, size_t column);
	void minmax_of_row_and_trans(const double* from, double* to, const int* sort, double* min, double* max, size_t row, size_t column);
	void result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const double* min, const double* max, size_t row, size_t column);
	void result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const int* sort, const double* min, const double* max, size_t row, size_t column);
	double* copy_malloc(size_t length, const double* old);
	int* copy_malloc(size_t length, const int* old);
	void data_copy_core(const double* from, double* to, size_t data_amount);
	
	inline double inner_dot(const double* left, const double* right, size_t amount, size_t incr_l, size_t incr_r);
	
	double Euclidean_norm_distance(const double* mat1, size_t ld1, const double *mat2, size_t ld2, const double *weights_ld, const double *weights_follow, size_t row, size_t column);
	void error_gradient_back_init(const double* mat_real, size_t ldr, const double *mat_out, size_t ldo, const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld);
    void energy_gradient_back_init(const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld);

	
	//void matrix_from_vector_per_row(double*mat, const double* vec, size_t row, size_t column, size_t ldm, size_t incr);
protected:
	static int if_intial;
	static unsigned int Cores;
	static unsigned int cores_uses;
	static pthread_t *handle;
	static sem_t barrier_sem;
};

class algebra_vector : public algebra_core
{
private:
	/* data */
public:
	algebra_vector(/* args */);
	~algebra_vector();
	void value(double*vec, double value, size_t length);
	void copy(double* from, double *to, size_t length);
	void copy(double* from, double *to, size_t length, double alpha, double beta);//to = from*alpha + beta
	void add(double* from, double *to, size_t length, double alpha, double beta);//to = from*alpha + to*beta
	void add_elementwise_square(double* from, double *to, size_t length, double alpha, double beta);//to = from_elementwise_square*alpha + to*beta
	void Adam_refresh(double* w_b, const double *m1, const double *m2, size_t length, double alpha, double epsilon);


	void Tanh(double* from, double *to, size_t length);
	void algebraic(double* from, double *to, size_t length);
	void Cos(double* from, double *to, size_t length);
	void gaussain(double* from, double *to, size_t length);
	void reciprocal(double* from, double *to, size_t length);

	void backward_tanh(double* from, double *to, const double* forward, size_t length);
    void backward_algebraic(double* from, double *to, const double* forward, size_t length);
    void backward_cos(double *from, double *to, const double* forward_in, size_t length);
    void backward_gaussain(double *from, double *to, const double* forward_in, size_t length);
    void backward_reciprocal(double *from, double *to, const double* forward_in, size_t length);

	size_t count_nan(const double *vector, size_t length);

};

class algebra_matrix : public algebra_core
{
private:
	/* data */
public:
	algebra_matrix(/* args */);
	~algebra_matrix();
	void transposition(double **mat, size_t row, size_t column, size_t ld, size_t new_extra_ld);
	void transposition(size_t row, size_t column, const double *from, size_t ldf, double *to, size_t ldt);
	void matrix_from_vector_per_row(double*mat, const double* vec, size_t row, size_t column, size_t ldm, size_t incr);
	void sum_of_mat_row(size_t row, size_t column, size_t ld, const double *temp, double *result, double alpha, double beta);
	void sum_of_column(size_t row, size_t column, size_t ld, const double *temp, double *result, double alpha, double beta);
	void matrix_shard_copy(size_t ldf, size_t ldt, size_t rows, size_t ele_per_rows, const double* from, double* to);
	void matrix_shard_product(size_t ldm, size_t ldf, size_t ldt, size_t ld_index, size_t row_m, size_t row_f, size_t ele_per_row, const double* major, const double* follow, double* to);
	void diagonal_add(double *mat, size_t row, size_t ld, double addend);
	void diagonal_expand(double *mat, size_t row, size_t ld, double addend);
	void sym_mat_compress(size_t row_col, size_t ld, const double *mat, double *compressed, enum HyperAlgebra::Uplo T);
	void sym_mat_uncompress(size_t row_col, size_t ld, double *mat, const double *compressed, enum HyperAlgebra::Uplo T);
	void sym_mat_uncompress(size_t row_col, size_t ld, double lambda, double *mat, const double *compressed, enum HyperAlgebra::Uplo T);
	void sym_mat_uncompress_expand(size_t row_col, size_t ld, double factor, double *mat, const double *compressed, enum HyperAlgebra::Uplo T);

	void Tanh(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt);
	void algebraic(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt);
	void Cos(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt);
	void gaussain(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt);
	void reciprocal(double* from, double *to, size_t row, size_t column, size_t ldf, size_t ldt);

	void backward_tanh(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
    void backward_algebraic(double* from, double *to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
    void backward_cos(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
    void backward_gaussain(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
    void backward_reciprocal(double *from, double *to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);


	void set_matrix(size_t row, size_t column, const double* from, size_t ldf, double* to, size_t ldt);
	void get_matrix(size_t row, size_t column, const double* from, size_t ldf, double* to, size_t ldt);
	double *dmat_malloc(size_t ld, size_t row);
	double *dmat_reshape(size_t ld, size_t row, double *old);

	void copy(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, double alpha, double beta); //to = from * alpha + beta;
	void copysy(enum HyperAlgebra::Uplo T, const double *from, size_t ldf, double *to, size_t ldt, size_t dim, double alpha, double beta);//to = from * alpha + beta;
	void copy(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, const double* alpha, const double* beta); 
	//to = from * alpha[i] + beta[i]; 0 < i < column
	void add(const double *from, size_t ldf, double *to, size_t ldt, size_t row, size_t column, double alpha, const double *beta, const double *gamma);
	void value(double *mat, size_t ld, size_t row, size_t column, double value);

	//to = from * alpha + to * beta[i] + gamma[i];
	double norm(const double *mat1, size_t ld1, const double *mat2, size_t ld2, size_t row, size_t column);
	double normsy(enum HyperAlgebra::Uplo T, const double *mat1, size_t ld1, const double *mat2, size_t ld2, size_t dim);
	void foldsy(enum HyperAlgebra::Uplo T, double *mat, size_t ld, size_t dim);
	//if T == upper, fold up to down
	void symv(enum HyperAlgebra::Uplo T, const double *mat, size_t ldm, size_t dim, const double *x, double alpha, double* y, double beta);
	// y = mat * x * alpha + beta * y
	double syfabsmax(enum HyperAlgebra::Uplo T, const double *mat, size_t ldm, size_t dim);
	void dotscalar(double *mat, size_t ldm, size_t row, size_t column, double alpha);
};

class algebra_mkl : public algebra_core
{
private:
	/* data */
public:
	algebra_mkl(/* args */);
	~algebra_mkl();
	

	void gemmNN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out);
	void gemmNT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out);
	void gemmTN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out);
	void gemmTT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, const double* L, const double* R, double* Out);
	void syrk_JJT_lower(size_t middle, size_t result, const double* J, double* C, size_t ld_J, size_t ld_C);
	void syrk_JTJ_lower(size_t middle, size_t result, const double* J, double* C, size_t ld_J, size_t ld_C);

	

	void gemmNN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out);
	void gemmNT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out);
	void gemmTN(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out);
	void gemmTT(size_t left, size_t middle, size_t right, size_t ld_L, size_t ld_R, size_t ld_O, double alpha, const double* L, const double* R, double beta, double* Out);

	void syrk_JJT_lower(size_t middle, size_t result, double alpha, const double* J, double beta, double* C, size_t ld_J, size_t ld_C);
	void syrk_JTJ_lower(size_t middle, size_t result, double alpha, const double* J, double beta, double* C, size_t ld_J, size_t ld_C);
	
	void syrkAAT(enum HyperAlgebra::Uplo T, const double* A, double alpha, size_t ldA, double* to, double beta, size_t ldt, size_t dummy, size_t dim);
	void syrkATA(enum HyperAlgebra::Uplo T, const double* A, double alpha, size_t ldA, double* to, double beta, size_t ldt, size_t dummy, size_t dim);
	//int pdpotrf(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T); 
	//int pdpotrs(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T, double *xb, int nrhs, size_t ldxb);
	int LAPACKE_dppsv(double *mat, size_t dim, size_t ld, enum HyperAlgebra::Uplo T, double *xb, int nrhs, size_t ldxb);
	
	int potrf(enum HyperAlgebra::Uplo T, double *mat, size_t dim, size_t ld);
	void potrs(enum HyperAlgebra::Uplo T, const double *mat, size_t dim, size_t ld, double *xb, int nrhs, size_t ldxb);
	// ldxb >= nrhs
	int potrfs(enum HyperAlgebra::Uplo T, double *mat, size_t dim, size_t ld, double *xb, int nrhs, size_t ldxb);
};


class special_func : public algebra_core
{
private:
	/* data */
public:
	special_func();
	~special_func();
	double special_error_2_6(const double *true_value, const double *result, size_t length, const double* weight);
	void special_gradient_2_6(const double *true_value, const double *result, size_t length, const double* weight, double *output);
	void special_jacobi_2_6(const double *true_value, const double *result, size_t length, const double* weight, double *output);
};


class ivector
{
public:
	friend class matrix_list;
	ivector();
	~ivector();
	ivector(size_t size);
	size_t Length(void);
	void append(long long int ele, size_t site);
	void create(size_t size);
	void ruin(void);
	//========================================
	void operator*=(const long long int alpha);
	long long int operator*(const ivector & Right);
	void operator+=(const long long int alpha);
	void operator=(const long long int alpha);
	void operator<=(const ivector & V);
	//========================================
	void value_Arithmetic_progression(long long int d, long long int initial);
	void file_printf(FILE* fp, int format, int message);
	size_t count_value(long long int value);
	long long int sum(void);
private:
	long long int* vector;
	size_t length;
};

class matrix_list
{
public:
	friend class matrix;
	matrix_list();
	void create(ivector & row, ivector & column);
	void create(ivector & r1, ivector & c1, ivector & r2, ivector & c2);
	~matrix_list();
	size_t Amount(void);
	//void create(long long int size);
	void ruin(void);
	//========================================
	void operator<=(const matrix_list & V);
	void matout(dvector & V, size_t h, matrix & M);
private:
	size_t* column;
	size_t* row;
	size_t* offset;
	size_t amount;
};
class matrix
{
public:
	friend class dvector;
	friend class matrix_list;
	//========================================
	matrix();
	matrix(size_t R, size_t C);
	~matrix();
	size_t Row(void);
	size_t Column(void);
	size_t Size(void);
	void create(size_t R, size_t C);
	void ruin();
	void value(double alpha, int method);
	void fprintf_matrix(FILE* fp, int format);
	void store(const char* path, const char *name);
	void load(const char* path, const char* name);
	//========================================
	void operator*=(const double alpha);
	void operator+=(const double alpha);
	void operator=(const double alpha);
	void operator<=(const matrix & A);
	void from_matrix_list(size_t h, const matrix_list & ml, const dvector & V);
	//========================================
	void transposition();
	double induced_1_norm(void);
	double induced_inf_norm(void);
	double Frobenius_norm(void);
	void diagon_add(double addend);
	//========================================
	void tanh(void);
	void algebraic(void);
	//========================================
	void muliple(matrix & left, matrix & right);
	void muliple_core(matrix & left, matrix & right, double alpha, double beta);
private:
	size_t row;
	size_t column;
	size_t size;
	double* mat;
};

class dvector
{
public:
	friend class matrix;
	//========================================
	dvector();
	dvector(size_t size);
	dvector(size_t size, const double *input);
	~dvector();
	size_t Length(void);
	void create(size_t size);
	void append(double ele, size_t site);
	void ruin(void);
	void store(const char* path, const char* name);
	void load(const char* path, const char* name);
	//========================================
	void operator*=(const double alpha);
	double operator*(const dvector & Right);
	void operator-=(const dvector & subtrahend);
	void operator+=(const dvector & addend);
	void operator+=(const double alpha);
	void operator=(const double alpha);
	void operator=(matrix & A);
	void operator<=(const dvector & V);
	//========================================
	double norm2(void);
	double distance(dvector & V);
	void min_max_dvector(double* min, double* max);
	void value_Arithmetic_progression(double d, double initial);
	void file_printf(FILE* fp, int format, int message);
	void file_printf(FILE* fp);
//protected:
	double* Vector();
private:
	double* vector;
	size_t length;
};

class algebra_log
{
public:
	algebra_log();
	//algebra_log(const char*s);
	~algebra_log();
	void open_log(void);
	void bitwise_store_open(const char* path, const char* name);
	void bitwise_store_lld(const size_t& store);
	void bitwise_store_lld(const long long int& store);
	void bitwise_store_lfvector(size_t size, const double* store);
	void bitwise_load_open(const char* path, const char* name);
	void bitwise_load_lld(size_t* load);
	void bitwise_load_lld(long long int* load);
	void bitwise_load_lfvector(size_t size, double* load);
	//=====================================
	void check_input_equal(long long int a, long long int b, const char* function);
private:
	//static FILE* log;
	FILE* inout;
	//static const char logname[] = "./log/algebra_log.txt";
};


class mutex_bar
{
public:
	mutex_bar(unsigned int amount_mutex, unsigned int thread_amount);
	~mutex_bar();
	void lock(unsigned int No);
	void unlock(unsigned int No);
	void lock(void);
	void unlock(void);
	void barrier(void);
private:
	unsigned int amount;
	pthread_mutex_t *mutex;
	unsigned int amount_thread;
	unsigned int barrier_count;
	sem_t count_sem;
	sem_t barrier_sem;
	sem_t reset_sem;
};

class signal_bar
{
public:
	signal_bar(unsigned int thread_amount);
	~signal_bar();
	void arrival(int sig);
	void arrival_wait(int sig);
	int wait(void);
private:
	int signal;
	unsigned int amount;
	unsigned int No;
	sem_t arrival_sem;
	sem_t wait_sem;
};

class report_bar
{
public:
	report_bar(unsigned int thread_amount);
	~report_bar();
	void report(void);
	void wait(void);
private:
	unsigned int amount;
	unsigned int No;
	sem_t arrival_sem;
	sem_t wait_sem;
};




class pthread_handle
{
private:
	pthread_t *handle;
	void* (*f)(void*);
	//unsigned int No;
	unsigned int amount;
	void **arg;
	// ret_val_p = NULL;
	int type;
public:
	//pthread_handle(unsigned int thread_amount, void* (*F)(void*));
	pthread_handle(unsigned int thread_amount, void* (*F)(void*), void **Arg);
	pthread_handle(unsigned int thread_amount, void* (*F)(void*), void *Arg, size_t sizeof_arg);
	~pthread_handle();
	//void arg_set(void *Arg, unsigned int No__);
	void launch(void);
};

#endif