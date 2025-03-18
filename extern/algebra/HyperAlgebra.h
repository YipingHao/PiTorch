#ifndef HYPER_Algebra_HHHHHH___
#define HYPER_Algebra_HHHHHH___

#include<stdlib.h>

namespace HyperAlgebra
{
	enum func
	{
		Identity,
		Tanh,
		Algebraic,
		Gaussain,
		Cos,
		Reciprocal
	};
	enum Uplo
	{
		upper,
		lower
	};
	enum instruction
	{
		vain,
		gemm,
		syrk,
		activation,
		activation_back,
		jacobi,
		bias_give,
		shard_copy,
		sum_of_rows
	};
    class HyperAlgebraCore
    {
    private:
	/* data */
    public:
	    HyperAlgebraCore(/* args */);
	    ~HyperAlgebraCore();
	    double *Free(double *vector);
	    double *Malloc(size_t length);
	    double *Malloc(size_t row, size_t ld);

        //void initial(unsigned int cores, unsigned int use);
	    //void set_cores_use(unsigned int use);
	    //void shut_down(void);

        double* CopyMalloc(size_t length, const double* old);
	    int* CopyMalloc(size_t length, const int* old);
	    void Copy(const double* from, double* to, size_t data_amount);
	
	    
    protected:
	    //static int if_intial;
	    //static unsigned int Cores;
	    //static unsigned int cores_uses;
	    //static pthread_t *handle;
	    //static sem_t barrier_sem;
    };

    class BasicVector : public HyperAlgebraCore
    {
    private:
	    /* data */
    public:
	    BasicVector(/* args */);
	    ~BasicVector();
	    void value(double*vec, double value, size_t length);
	    void copy(const double* from, double *to, size_t length);
	    void copy(double* from, double *to, size_t length, double alpha, double beta);//to = from*alpha + beta
	    void add(double* from, double *to, size_t length, double alpha, double beta);//to = from*alpha + to*beta
		void add(double *to, size_t length, double alpha1, const double* vec1, double alpha2, const double* vec2);//to = vec1*alpha1 + vec2*alpha2
	    void AddElementwiseSquare(double* from, double *to, size_t length, double alpha, double beta);//to = from_elementwise_square*alpha + to*beta
    	void AdamRefresh(double* w_b, const double *m1, const double *m2, size_t length, double alpha, double epsilon);

	    void Tanh(double* from, double *to, size_t length);
	    void algebraic(double* from, double *to, size_t length);
	    void Cos(double* from, double *to, size_t length);
	    void gaussain(double* from, double *to, size_t length);
	    void reciprocal(double* from, double *to, size_t length);

	    void BackwardTanh(double* from, double *to, const double* forward, size_t length);
        void BackwardAlgebraic(double* from, double *to, const double* forward, size_t length);
        void BackwardCos(double *from, double *to, const double* forward_in, size_t length);
        void BackwardGaussain(double *from, double *to, const double* forward_in, size_t length);
        void BackwardReciprocal(double *from, double *to, const double* forward_in, size_t length);

	    double InnerDot(const double* left, const double* right, size_t length);
		void ElemwiseDot(double ele, double* vector, size_t length);
		void Add(size_t length, double* to, const double*vec1, double beta, const double*vec2); 
	    double Norm2(const double* vector, size_t length); 
		double Norm2(const double* vec1, const double* vec2, size_t length); 
	    void Substract(double *vector, size_t length, const double *subtrahend, double Norm2Square);
	    void Norm2Normalization(double* vector, size_t length);
	    void FiniteDifference(double *result, size_t length, double DeltaReverse, const double *minuend, const double *subtrahend);
		void Inverse(size_t length, double *vector);
		void ElemwiseProd(size_t length, const double *vec1, const double *vec2, double *dst);
    };

	class BasicMatrix : public BasicVector
	{
	private:
		/* data */
	public:
		BasicMatrix(/* args */);
		~BasicMatrix();
		void CopyVectorToMatrixLine(double*mat, size_t ldm, const double* vec, size_t incr, size_t row, size_t column);
		void SumMatrixLine(const double *temp, size_t ld, size_t row, size_t column, double *result, double alpha, double beta);
		void MatrixCopy(const double* from, size_t ldf, double* to, size_t ldt, size_t rows, size_t column);
		void MatrixShardProduct(const double* major, size_t ldm, const double* follow, size_t ldf, double* to, size_t ldt, size_t ld_index, size_t row_m, size_t row_f, size_t EleCount);
		void DiagonalAdd(double* mat, size_t row, size_t ld, double addend);
		void DiagonalExpand(double* mat, size_t row, size_t ld, double addend);
		void SymMatCompress(size_t row_col, size_t ld, const double* mat, double* compressed, enum Uplo T);
		void SymMatUncompress(size_t row_col, size_t ld, double* mat, const double* compressed, enum Uplo T);
		void SymMatUncompress(size_t row_col, size_t ld, double lambda, double* mat, const double* compressed, enum Uplo T);
		void SymMatUncompressExpand(size_t row_col, size_t ld, double factor, double* mat, const double* compressed, enum Uplo T);

		void Tanh(double* from, double* to, size_t row, size_t column, size_t ldf, size_t ldt);
		void algebraic(double* from, double* to, size_t row, size_t column, size_t ldf, size_t ldt);
		void Cos(double* from, double* to, size_t row, size_t column, size_t ldf, size_t ldt);
		void gaussain(double* from, double* to, size_t row, size_t column, size_t ldf, size_t ldt);
		void reciprocal(double* from, double* to, size_t row, size_t column, size_t ldf, size_t ldt);

		void BackwardTanh(double* from, double* to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
		void BackwardAlgebraic(double* from, double* to, const double* forward, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
		void BackwardCos(double* from, double* to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
		void BackwardGaussain(double* from, double* to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);
		void BackwardReciprocal(double* from, double* to, const double* forward_in, size_t row, size_t column, size_t ldf, size_t ldt, size_t ldforward);

		void GEMVn(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col);
		void GEMVt(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col);
		//dst = Mat ^ T * vec Mat: row * col row * ldM
		void MatColValueFromVec(double* MatTo, size_t ldM, size_t row, const double* vector);//
		void MatRowValueFromVec(double* MatTo, size_t col, const double* vector);
		double NormMax(size_t row, size_t column, const double *mat1, size_t ld1, const double *mat2, size_t ld2);
	};

	class AlgebraMKL : public BasicMatrix
	{
	private:
		/* data */
	public:
		AlgebraMKL(/* args */);
		~AlgebraMKL();
		double InnerDot(const double* left, const double* right, size_t amount, size_t incr_l, size_t incr_r);
		double InnerDot(const double* left, const double* right, size_t length); 
		void gemmNN(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O);
		void gemmNT(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O);
		void gemmTN(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O);
		void gemmTT(size_t left, size_t middle, size_t right, const double* L, size_t ld_L, const double* R, size_t ld_R, double* Out, size_t ld_O);
		void syrkJJTlower(size_t middle, size_t result, const double* J, size_t ld_J, double* C, size_t ld_C);
		void syrkJTJlower(size_t middle, size_t result, const double* J, size_t ld_J, double* C, size_t ld_C);


		//Calpha*op(A)*op(B) + beta*C
		void gemmNN(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O);
		void gemmNT(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O);
		void gemmTN(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O);
		void gemmTT(size_t left, size_t middle, size_t right, double alpha, const double* L, size_t ld_L, const double* R, size_t ld_R, double beta, double* Out, size_t ld_O);

		void syrkJJTlower(size_t middle, size_t result, double alpha, const double* J, size_t ld_J, double beta, double* C, size_t ld_C);
		void syrkJTJlower(size_t middle, size_t result, double alpha, const double* J, size_t ld_J, double beta, double* C, size_t ld_C);

		//int pdpotrf(double *mat, size_t dim, size_t ld, enum Uplo T); 
		//int pdpotrs(double *mat, size_t dim, size_t ld, enum Uplo T, double *xb, int nrhs, size_t ldxb);
		int LAPACKE_dppsv(double *mat, size_t ld, size_t dim, enum Uplo T, double *xb, int nrhs, size_t ldxb);

		double Norm2(const double* vector, size_t length); 
	    void Substract(double *vector, size_t length, const double *subtrahend, double Norm2Square);
		void Norm2Normalization(double* vector, size_t length);
	    void FiniteDifference(double *result, size_t length, double DeltaReverse, const double *minuend, const double *subtrahend);

		void GEMVn(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col);
		void GEMVt(const double* Mat, size_t ldM, const double* vec, double* dst, size_t row, size_t col);
		//dst = Mat ^ T * vec Mat: row * col row * ldM
		void MatColValueFromVec(double* MatTo, size_t ldM, size_t row, const double* vector);//
		void MatRowValueFromVec(double* MatTo, size_t col, const double* vector);

		int MKLdsyev(enum Uplo T, size_t row, double *MatAH, size_t ldm, double* eigenvalues);
		//A = (H)(D)(H^T)
	};

	class SimpleRandom
	{
	public:
		SimpleRandom() {}
		~SimpleRandom() {}
		void SetSeed(int seed);
		void SetParameter(int a, int b);
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

	class SimpleRandomLocal
	{
	public:
		SimpleRandomLocal();
		~SimpleRandomLocal();
		void SetSeed(int seed);
		void SetParameter(int a, int b);
		int rand(void);
		double rand(double lower, double upper);
		int judge(double probability);
		int select(int N);
		int rand(int down_close, int up_open);

		void Rand(double lower, double upper, double* vector, size_t length);
		void Rand(double lower, double upper, double* mat, size_t ld, size_t row, size_t column);
	private:
		int HYPER_seed;
		int HYPER_length;
		int A;
		int B;
		int Q;
		int R;
		double reciprocal;
};

	class MersenneTwisters
	{
	public:
		MersenneTwisters();
		~MersenneTwisters();
		void SetSeed(unsigned long long seed);
		unsigned long long  rand(void);
		double real(void);
		double RealCloseCLose(void);
		double RealOpenOpen(void);
		size_t select(size_t N);//[0, N)
	private:
		unsigned long long mt[312];
		int mti;
		void twist(void);
	};
}
#endif // !HYPER_CUDA_HHHHHH___

/*
class algebra_core
    {
    public:
	    algebra_core();
	    ~algebra_core();
	    
	    int normalize_each_row(double* mat, const double* min, const double* max, size_t row, size_t column);
	    void minmax_of_row_and_trans(const double* from, double *to, double* min, double* max, size_t row, size_t column);
	    void minmax_of_row_and_trans(const double* from, double* to, const int* sort, double* min, double* max, size_t row, size_t column);
	    void result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const double* min, const double* max, size_t row, size_t column);
	    void result_retrieval(const double*from, size_t ldf, double* to, size_t ldt, const int* sort, const double* min, const double* max, size_t row, size_t column);
	    
	
	double Euclidean_norm_distance(const double* mat1, size_t ld1, const double *mat2, size_t ld2, const double *weights_ld, const double *weights_follow, size_t row, size_t column);
	void error_gradient_back_init(const double* mat_real, size_t ldr, const double *mat_out, size_t ldo, const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld);
    void energy_gradient_back_init(const double *weights_ld, const double *weights_row, size_t row, size_t column, double *init, size_t ld);

	
	//void matrix_from_vector_per_row(double*mat, const double* vec, size_t row, size_t column, size_t ldm, size_t incr);

};

*/
