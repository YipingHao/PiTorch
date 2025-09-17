namespace BackEnd//CPU back end example
{
	typedef double real;
	typedef const real Creal;
	class ANetWork
	{
	public:
		//前向传播所需的内存
		//这部分传播仅由用户定义网络决定
		//不涉及用户定义的网络输出对输入导数的计算
		real* InputDevice;
		real* InputHost;
		real* ParaDevice;
		real* ParaHost;
		real* HiddenDevice;
		real* HiddenHost;
		real* OutputDevice;
		real* OutputHost;
		//尺寸与维度获得接口
		size_t GetParaDim(void) const;
		size_t GetInputDim(void) const;
		size_t GetHiddenDim(void) const;
		size_t GetOutputDim(void) const;

		// 前向传播的输出包括用户定义的神经网络网络输出对输入导数的计算
		real* OutputGradDevice;
		real* OutputGradHost;
		real* HiddenDevice02;
		real* HiddenHost02;

		size_t GetOutputGradDim(void) const;
		size_t GetHiddenDim02(void) const;

		// 对损失函数进行反向传播所需的内存
		real* LossInputDevice;
		real* LossInputHost;
		real* LossGradDevice;
		real* LossGradHost;
		real* LossHiddenDevice;
		real* LossHiddenHost;

		size_t GetLossInputDim(void) const;
		size_t GetLossGradDim(void) const;
		size_t GetLossHiddenDim(void) const;

		// 计算海塞矩阵乘以矢量的前向传播微分所需的内存
		real* HvInputDevice;
		real* HvInputHost;
		real* HvOutputDevice;
		real* HvOutputHost;
		real* HvHiddenDevice;
		real* HvHiddenHost;

		size_t GetHvInputDim(void) const;
		size_t GetHvOutputDim(void) const;
		size_t GetHvHiddenDim(void) const;

		// 计算雅可比矩阵所需的内存
		real* JacobiInputDevice;
		real* JacobiInputHost;
		real* JacobiOutputDevice;
		real* JacobiOutputHost;
		real* JacobiHiddenDevice;
		real* JacobiHiddenHost;

		size_t GetJacobiInputDim(void) const;
		size_t GetJacobiOutputDim(void) const;
		size_t GetJacobiHiddenDim(void) const;
	private:
		size_t ld;
		size_t count;//BacthSize
		//并非指代神经网络的前向传播是否已经被计算，
		//而是记录相关前向传播所需要的内存是否已经被分配。
		//懒分配策略:调用相关计算的时候分配相应内存
		bool forwardOri_mem;
		bool forward_mem;
		bool loss_mem;
		bool Hv_mem;
		bool jacobi_mem;
		//记录相关计算是否已经完成。
		bool forwardOri;
		bool forward;
		bool loss;
		bool Hv;
		bool jacobi;
		bool LeadingDimLast;
		void MemRelease();
		//Leading Dim 是不是数组的最后一个维度
	
	private:
		//内存分配接口
		void forwardOriMemAlloc();
		void forwardMemAlloc();
		void lossMemAlloc();
		void HvMemAlloc();
		void jacobiMemAlloc();
	public:
		ANetWork(size_t newld = 1024);
		~ANetWork();
		inline bool IfLeadingDimLast() const { return LeadingDimLast; }
		inline size_t GetBatchSize(void) const { return count; }
		inline size_t GetLd(void) const { return ld; }

		void SetLd(size_t newld);
		void refresh(void);
		void SetBatchSize(void);
		void SetBatchSize(size_t BatchSize);
	
				
		
		
	public://计算接口
		// 计算整个神经网络的前向传播,包括用户定义的神经网络输出对输入导数的计算
		void compute();
		// 计算神经网络的原始输出,不包括用户定义的神经网络输出对输入导数的计算
		void ComputeOringinal();
		// 计算神经网络的损失梯度,包括用户定义的神经网络输出对输入导数的计算
		void ComputeLoss();
		// 计算神经网络的损失梯度,包括用户定义的神经网络输出对输入导数的计算
		void ComputeHv();

		void ComputeJacobi();
	private:
		void ComputeCore();
		void ForwardOriCore();
		void LossCore();
		void HvCore();
		void JacobiCore();
	};
}