//=============================================================
// 不变素材区，所有的结构和硬件架构都需要同一套素材。
// 这个素材固定的写在文件all.txt里面
// 输出固定架构对应的代码时，读入这个文件并输出到最终的代码中
//=============================================================
#include "../output/BackEnd.h"
#include"stdlib.h"
using namespace BackEnd;


static void MemReleaseHost(real*& ptr);
static void MemReleaseDevice(real*& ptr);
static real* MemAllocHost(size_t ld, size_t dim);
static real* MemAllocDevice(size_t ld, size_t dim);
static void MemAllocHD(size_t ld, size_t dim, real*& host, real*& device);



ANetWork::ANetWork(size_t newld)
	: InputDevice(NULL)
	, InputHost(NULL)
	, ParaDevice(NULL)
	, ParaHost(NULL)
	, HiddenDevice(NULL)
	, HiddenHost(NULL)
	, OutputDevice(NULL)
	, OutputHost(NULL)
	, OutputGradDevice(NULL)
	, OutputGradHost(NULL)
	, HiddenDevice02(NULL)
	, HiddenHost02(NULL)
	, LossInputDevice(NULL)
	, LossInputHost(NULL)
	, LossGradDevice(NULL)
	, LossGradHost(NULL)
	, LossHiddenDevice(NULL)
	, LossHiddenHost(NULL)
	, HvInputDevice(NULL)
	, HvInputHost(NULL)
	, HvOutputDevice(NULL)
	, HvOutputHost(NULL)
	, HvHiddenDevice(NULL)
	, HvHiddenHost(NULL)
	, JacobiInputDevice(NULL)
	, JacobiInputHost(NULL)
	, JacobiOutputDevice(NULL)
	, JacobiOutputHost(NULL)
	, JacobiHiddenDevice(NULL)
	, JacobiHiddenHost(NULL)
	
	, forwardOri_mem(false)
	, forward_mem(false)
	, loss_mem(false)
	, Hv_mem(false)
	, jacobi_mem(false)
	, forwardOri(false)
	, forward(false)
	, loss(false)
	, Hv(false)
	, jacobi(false)
{
	LeadingDimLast = true;
	ld = newld;
	count = ld;
}
ANetWork::~ANetWork()
{
	MemRelease();
}
void ANetWork::MemRelease(void)
{
	MemReleaseDevice(InputDevice);      MemReleaseHost(InputHost);
	MemReleaseDevice(ParaDevice);       MemReleaseHost(ParaHost);
	MemReleaseDevice(HiddenDevice);     MemReleaseHost(HiddenHost);
	MemReleaseDevice(OutputDevice);     MemReleaseHost(OutputHost);

	MemReleaseDevice(OutputGradDevice); MemReleaseHost(OutputGradHost);
	MemReleaseDevice(HiddenDevice02);   MemReleaseHost(HiddenHost02);

	MemReleaseDevice(LossInputDevice);  MemReleaseHost(LossInputHost);
	MemReleaseDevice(LossGradDevice);   MemReleaseHost(LossGradHost);
	MemReleaseDevice(LossHiddenDevice); MemReleaseHost(LossHiddenHost);

	MemReleaseDevice(HvInputDevice);    MemReleaseHost(HvInputHost);
	MemReleaseDevice(HvOutputDevice);   MemReleaseHost(HvOutputHost);
	MemReleaseDevice(HvHiddenDevice);   MemReleaseHost(HvHiddenHost);

	MemReleaseDevice(JacobiInputDevice);  MemReleaseHost(JacobiInputHost);
	MemReleaseDevice(JacobiOutputDevice); MemReleaseHost(JacobiOutputHost);
	MemReleaseDevice(JacobiHiddenDevice); MemReleaseHost(JacobiHiddenHost);

	forwardOri_mem = false;
	forward_mem = false;
	loss_mem = false;
	Hv_mem = false;
	jacobi_mem = false;
	refresh();
}
void ANetWork::SetLd(size_t newld)
{
	if (ld == newld) return;
	MemRelease();
	ld = newld;
	count = ld;
}


void ANetWork::forwardOriMemAlloc()
{
	MemAllocHD(ld, GetInputDim(), InputHost, InputDevice);
	MemAllocHD(ld, GetParaDim(), ParaHost, ParaDevice);
	MemAllocHD(ld, GetHiddenDim(), HiddenHost, HiddenDevice);
	MemAllocHD(ld, GetOutputDim(), OutputHost, OutputDevice);
	forwardOri_mem = true;
}
void ANetWork::forwardMemAlloc()
{
	MemAllocHD(ld, GetOutputGradDim(), OutputGradHost, OutputGradDevice);
	MemAllocHD(ld, GetHiddenDim02(), HiddenHost02, HiddenDevice02);
	forward_mem = true;
}
void ANetWork::lossMemAlloc()
{
	MemAllocHD(ld, GetLossInputDim(), LossInputHost, LossInputDevice);
	MemAllocHD(ld, GetLossGradDim(), LossGradHost, LossGradDevice);
	MemAllocHD(ld, GetLossHiddenDim(), LossHiddenHost, LossHiddenDevice);
	loss_mem = true;
}
void ANetWork::HvMemAlloc()
{
	MemAllocHD(ld, GetHvInputDim(), HvInputHost, HvInputDevice);
	MemAllocHD(ld, GetHvOutputDim(), HvOutputHost, HvOutputDevice);
	MemAllocHD(ld, GetHvHiddenDim(), HvHiddenHost, HvHiddenDevice);
	Hv_mem = true;
}
void ANetWork::jacobiMemAlloc()
{
	MemAllocHD(ld, GetJacobiInputDim(), JacobiInputHost, JacobiInputDevice);
	MemAllocHD(1, GetJacobiOutputDim(), JacobiOutputHost, JacobiOutputDevice);
	MemAllocHD(ld, GetJacobiHiddenDim(), JacobiHiddenHost, JacobiHiddenDevice);
	jacobi_mem = true;
}


void ANetWork::refresh(void)
{
	forwardOri = false;
	forward = false;
	loss = false;
	Hv = false;
	jacobi = false;
}
void ANetWork::SetBatchSize(void)
{
	SetBatchSize(ld);
}
void ANetWork::SetBatchSize(size_t BatchSize)
{
	refresh();
	if (BatchSize == 0 || BatchSize >= ld) count = ld;
	else count = BatchSize;
}


void ANetWork::ComputeOringinal()
{
	//不检查forwardOri，如果它是true那么就重新计算
	//检查forwardOri_mem，如果它是false那么就分配内存
	if (!forwardOri_mem) forwardOriMemAlloc();
	ForwardOriCore();
	forwardOri = true;
}
void ANetWork::compute()
{
	if (!forward_mem) forwardMemAlloc();
	if (!forwardOri) ComputeOringinal();
	ComputeCore();
	forward = true;
}
void ANetWork::ComputeLoss()
{
	if (!loss_mem) lossMemAlloc();
	if (!forward) compute();
	LossCore();
	loss = true;
}
void ANetWork::ComputeHv()
{
	if (!Hv_mem) HvMemAlloc();
	if (!loss) ComputeLoss();
	HvCore();
	Hv = true;
}
void ANetWork::ComputeJacobi()
{
	if (!jacobi_mem) jacobiMemAlloc();
	if (!forward) compute();
	JacobiCore();
	jacobi = true;
}


size_t ANetWork::GetLossInputDim(void) const
{
	return GetOutputDim() + GetOutputGradDim();
}
size_t ANetWork::GetLossGradDim(void) const
{
	return GetParaDim();
}

size_t ANetWork::GetHvInputDim(void) const
{
	return GetParaDim();
}
size_t ANetWork::GetHvOutputDim(void) const
{
	return GetParaDim();
}

size_t ANetWork::GetJacobiInputDim(void) const
{
	return GetLossInputDim();
}








//=============================================================
// 变化素材区，每一种硬件架构都需要一套素材，
// 这些素材固定的写在某些文件里面
// 输出固定架构对应的代码时，读入这些文件并输出到最终的代码中
//=============================================================

static void MemReleaseHost(real*& ptr)
{
	ptr = NULL;
}
static void MemReleaseDevice(real*& ptr)
{
	free(ptr);
	ptr = NULL;
}
static real* MemAllocHost(size_t ld, size_t dim)
{
	return (real*)malloc(ld * dim * sizeof(real));
}
static real* MemAllocDevice(size_t ld, size_t dim)
{
	return (real*)malloc(ld * dim * sizeof(real));
}
static void MemAllocHD(size_t ld, size_t dim, real*& host, real*& device)
{
	device = (real*)malloc(ld * dim * sizeof(real));
	host = device;
}


//=============================================================
// 结构决定区，每一个不同的神经网络结构都需要一套素材，
// 这些素材直接由程序计算后写在输出的代码里面
// 下面列出的函数仅作为演示和占位
//=============================================================

size_t ANetWork::GetParaDim(void) const
{
	return 0;
}
size_t ANetWork::GetInputDim(void) const
{
	return 0;
}
size_t ANetWork::GetHiddenDim(void) const
{
	return 0;
}
size_t ANetWork::GetOutputDim(void) const
{
	return 0;
}
size_t ANetWork::GetOutputGradDim(void) const
{
	return 0;
}
size_t ANetWork::GetHiddenDim02(void) const
{
	return 0;
}
size_t ANetWork::GetLossHiddenDim(void) const
{
	return 0;
}
size_t ANetWork::GetHvHiddenDim(void) const
{
	return 0;
}
size_t ANetWork::GetJacobiOutputDim(void) const
{
	return 0;
}
size_t ANetWork::GetJacobiHiddenDim(void) const
{
	return 0;
}


