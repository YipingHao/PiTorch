#ifndef Pikatypejfqiwerou34rtq90t4er5q9o0rqegfjoertfhju8o
#define Pikatypejfqiwerou34rtq90t4er5q9o0rqegfjoertfhju8o
#include"PikaTemplate.h"
namespace Pikachu
{
	class tensor;
	class tensorPara;
	class tensorList;
	class ContractDesc;
	class contract;
	class elementwise;
	class condensation;
	class dispatch;

	class PikaString : public buffer<char>
	{
	public:
		PikaString();
		~PikaString();
		void operator<<(FILE* fp);
		char* array(void);
		char* CopyVector(void) const;
		size_t CopyVector(vector<char>& dst, size_t& length) const;

		void operator=(const char* input);
		void operator+=(const char* source);
		void operator+=(long long int source);
		void operator+=(double source);

	private:

	};
	/*class PikaError
	{
	public:
		PikaError(const char* Source, const char*Error, int Code);
		PikaError(const PikaError& Old, const char* prefix);
		~PikaError();
		void show(FILE* fp)const;
	private:
		char* source;
		char* error;
		int code;
	};*/

	class elaboration : public vector<size_t>
	{
	public:
		elaboration();
		~elaboration();
		void attach(const elaboration& old, const size_t NewData);
		bool operator==(const elaboration& Right) const;
	private:

	};
	class tensor
	{
	public:
		tensor();
		~tensor();
		bool operator==(const tensor& Right) const;
		bool CountCompare(const tensor& Right) const;
		bool Equal(const tensor& Right, size_t begin, size_t upper) const;
		void ChangeOrder(size_t NewDim);
		void ChangeDim(size_t No, size_t NewDim);
		void AppendDim(size_t NewDim);
		void Clear(void);
		void Demo(FILE* fp)const;
		void Demo(FILE* fp, const char *name)const;
		void OrderGrowth(void);
		void OrderGrowth(size_t delta);
		void OrderGrowthOne(size_t NewDim);
		void CutLast(const tensor& source);
		void Set(const tensor& source);

		void contraction(const tensor& sourceL, const tensor& sourceR);
		// L_{ijl}R^{kmlj} descLtoR[0] = 4; descLtoR[1] = 3; descLtoR[2] = 2; 
		void contraction(const tensor& sourceL, const tensor& sourceR, const ContractDesc& contract);
		void contraction(const tensor& sourceL, const tensor& sourceR, const contract& contract);


		void Dispatch(const tensor& source, const dispatch& desc);
		void Dispatch(const tensor& source, const dispatch& desc, const tensor& former);
		void Condensation(const tensor& source, const condensation& desc);
		void Elementwise(const tensor& sourceL, const tensor& sourceR, const elementwise& desc);


		size_t GetCount(void)const;
		size_t GetOrder(void)const;
		const size_t& operator[](size_t target) const;
	protected:
		size_t order;
		size_t* dim;
		size_t count;
	};
	
	class Tensor : public vector<size_t>
	{
	public:
		inline Tensor()
		{

		}
		inline ~Tensor()
		{

		}
		void Set(const Tensor& source);
		bool operator==(const Tensor& Right) const;
		bool operator!=(const Tensor& Right) const;
		inline size_t GetOrder(void)const
		{
			return Count;
		}
		inline void ChangeOrder(size_t NewOrder)
		{
			recount(NewOrder);
		}
		inline void ChangeDim(size_t No, size_t NewDim)
		{
			content[No] = NewDim;
		}
		inline size_t GetCount(void)const
		{
			size_t num = 1;
			for (size_t i = 0; i < Count; i++)
			{
				num *= content[i];
			}
			return num;
		}
		void demo(FILE* fp)const;
		void demo(FILE* fp, const char* name)const;
	protected:

	};


	class tensorPara : public tensor
	{
	public:
		friend class tensorList;
		tensorPara();
		~tensorPara();
		size_t site(void)const;
		size_t prefix(void)const;
	private:
		size_t No;
		size_t Prefix;

	};
	class tensorList
	{
	public:
		tensorList();
		~tensorList();
		void clear(void);
		size_t capacity(void) const;
		size_t count(void) const;
		void append(tensor* element);
		size_t append(void);
		tensorPara*& operator[](size_t target);
		size_t Offset(size_t No, size_t ld) const;
		size_t Offset(size_t No) const;
	private:
		size_t Count;
		size_t Capacity;
		tensorPara** content;


	};
	class ContractDesc
	{
	public:
		friend class tensor;
		ContractDesc();
		~ContractDesc();
		
		size_t& out(size_t No);
		size_t& left(size_t No);
		size_t& right(size_t No);
		void CheckAndBuild(const vector<size_t> &O, const vector<size_t>& L, const vector<size_t>& R);
		void CheckAndBuild(const tensor& TeensorSrc, size_t SrcDim, const tensor& BackSrc, size_t OutCount);
		void CheckAndBuild(size_t Front, size_t Output, size_t Last, size_t Extra);
		size_t DummyCount(void)const;
		size_t Max(void) const;
		void backward(const tensor &BackSrc, const ContractDesc &forward);
		void backward(const tensor& BackSrc, const ContractDesc& forward, bool right);
		//x_{ijk}=\sum_{a}w_{ia}y_{ajk}
		// right == true:
		// \frac{\partial O^h}{\partial y_ajk} = \sum_{i} w_{ia}\times \frac{\partial O^h}{\partial x_{ijk}}
		// right != true:
		//\frac{\partial O^h}{\partial w_{ia}} = \sum_{jk} \frac{\partial O^h}{\partial x_{ijk}}\times y_{ajk}
		void Demo(FILE* fp);
		void Set(const ContractDesc& source);
		union type
		{
			bool dummy;
			bool left;
		};
		struct index
		{
			size_t label;
			size_t peer;
			type infor;
		};
	private:
		vector<index> Out;
		vector<index> Left;
		vector<index> Right;
		bool completed;

		void CheckAndBuild(void);
		void SetDim(size_t dimO, size_t dimL, size_t dimR);
		void SetDim(const ContractDesc& forward, size_t dimL, size_t dimR);
	};
	class elementwise
	{
	public:
		friend class tensor;
		friend class condensation;
		friend class dispatch;
		elementwise();
		~elementwise();
		void build(const vector<size_t>& L, const vector<size_t>& R);
		void build(const size_t trival);
		void build(const size_t Ltrival, const size_t Rtrival);
		void check(void);
		void backward(const tensor& BackSrc, const elementwise& forward, bool left);
		void Set(const elementwise& source);
		//muliple if(left) right will be in the multiple 

		void forward(const tensor& ForwardSrcL, const tensor& ForwardSrcR, const elementwise& DescSrc);
		void forward(const tensor& ForwardSrc, bool left, const elementwise& DescSrc);
		//muliple if(left) left is the differential 
		struct index
		{
			size_t left;
			size_t right;
		};
	private:
		vector<index> Desc;
		size_t LeftDim;
		size_t RightDim;
		bool completed;
	};
	class condensation 
	{
	public:
		friend class tensor;
		friend class dispatch;
		condensation();
		~condensation();
		void build(vector<bool>& input);
		size_t OutOrder(void)const;
		void backward(const tensor& BackSrc, const dispatch& forward);
		void backward(const tensor& BackSrc, const elementwise& forward, bool left);
		// left == true,: \frac{\partial output}{\partial left}  
		void Set(const condensation& source);
		void forward(const tensor& ForwardSrc, const condensation& DescSrc);
	private:
		vector<bool> Desc;
		vector<size_t> OutSource;
		size_t dummy;
		bool completed;
	};
	class dispatch
	{
	public:
		friend class tensor;
		friend class condensation;
		dispatch();
		~dispatch();
		void build(vector<size_t>& input);
		void backward(const tensor& BackSrc, const condensation& forward);
		void forward(const tensor& ForwardSrc, const dispatch& DescSrc);
		void forward(const tensor& ForwardSrc, const elementwise& DescSrc, bool left);
		void Set(const dispatch& source);
	private:
		vector<size_t> Desc;
		size_t sourceOrder;
		bool completed;

		
	};

	class contract
	{
	public:
		friend class tensor;
		contract();
		~contract();
		struct index
		{
			size_t label;
			size_t src1;//dst
			//src1: src1 when out, dst when left or right
			size_t src2;//peer
			//src2: src2 when out, peer when left or right
			void initial(void);
			bool vain(void);
		};
		void Build(const vector<size_t>& O, const vector<size_t>& L, const vector<size_t>& R);
		void Build(const tensor& TensorSrc, size_t SrcDim, const tensor& BackSrc, size_t OutCount);
		
		void ForwardBuild(const tensor& TensorSrc, size_t SrcDim, const tensor& FrontSrc, size_t OutCount);
		void LabelShrink(void);
		void backward(const tensor& BackSrc, const contract& forward, bool right);
		//x_{ijkc}=\sum_{a}w_{iac}y_{ajkc}
		// right == true:
		// \frac{\partial O^h}{\partial y_ajkc} = \sum_{i} w_{iac}\times \frac{\partial O^h}{\partial x_{ijkc}}
		// right != true:
		//\frac{\partial O^h}{\partial w_{iac}} = \sum_{jk} \frac{\partial O^h}{\partial x_{ijkc}}\times y_{ajkc}
		void forward(const tensor& ForwardSrc, const contract& DescSrc, bool left);
		void Demo(FILE* fp);
		void Set(const contract& source);
	private:
		vector<index> Out;
		vector<index> Left;
		vector<index> Right;
		bool completed;
		void SetDim(size_t dimO, size_t dimL, size_t dimR);
		void Initial(void);
		void Build(void);
		size_t MaxLabel(void)const;
		void Build(size_t Front, size_t Output, size_t Last, size_t Extra);
	};







}


#endif
