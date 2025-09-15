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

		// 前向传播的输出包括用户定义的神经网络网络输出对输入导数的计算
		real* OutputGradDevice;
		real* OutputGradHost;
		real* HiddenDevice02;
		real* HiddenHost02;

		// 对损失函数进行反向传播所需的内存
		real* LossInputDevice;
		real* LossInputHost;
		real* LossGradDevice;
		real* LossGradHost;
		real* LossHiddenDevice;
		real* LossHiddenHost;

		// 计算海塞矩阵乘以矢量的前向传播微分所需的内存
		real* HvInputDevice;
		real* HvInputHost;
		real* HvParaDevice;
		real* HvParaHost;
		real* HvHiddenDevice;
		real* HvHiddenHost;

		// 计算雅可比矩阵所需的内存
		real* JacobiInputDevice;
		real* JacobiInputHost;
		real* JacobiParaDevice;
		real* JacobiParaHost;
		real* JacobiHiddenDevice;
		real* JacobiHiddenHost;

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
		//Leading Dim 是不是数组的最后一个维度
	public:
		ANetWork(size_t newld = 1024);
		~ANetWork();
		inline bool IfLeadingDimLast()const { return LeadingDimLast; }
		void MemRelease();
		void SetLd(size_t newld);

		void refresh(void);
		void SetBatchSize(void);
		void SetBatchSize(size_t BatchSize);

		// 计算整个神经网络的前向传播,包括用户定义的神经网络输出对输入导数的计算
		void compute();
		// 计算神经网络的原始输出,不包括用户定义的神经网络输出对输入导数的计算
		void computeOringinal();
		// 计算神经网络的损失梯度,包括用户定义的神经网络输出对输入导数的计算
		void computeLoss();
		// 计算神经网络的损失梯度,包括用户定义的神经网络输出对输入导数的计算
		void computeHv();

		void computeJacobi();
	};
}