#include "../output/BackEnd.h"
#include"stdlib.h"
using namespace BackEnd;





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
	, HvParaDevice(NULL)
	, HvParaHost(NULL)
	, HvHiddenDevice(NULL)
	, HvHiddenHost(NULL)
	, JacobiInputDevice(NULL)
	, JacobiInputHost(NULL)
	, JacobiParaDevice(NULL)
	, JacobiParaHost(NULL)
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
	// 直接 free，再置 NULL；free(NULL) 安全，不需要 if 判断
	free(InputDevice);      InputDevice = NULL;
	free(InputHost);        InputHost = NULL;
	free(ParaDevice);       ParaDevice = NULL;
	free(ParaHost);         ParaHost = NULL;
	free(HiddenDevice);     HiddenDevice = NULL;
	free(HiddenHost);       HiddenHost = NULL;
	free(OutputDevice);     OutputDevice = NULL;
	free(OutputHost);       OutputHost = NULL;

	free(OutputGradDevice); OutputGradDevice = NULL;
	free(OutputGradHost);   OutputGradHost = NULL;
	free(HiddenDevice02);   HiddenDevice02 = NULL;
	free(HiddenHost02);     HiddenHost02 = NULL;

	free(LossInputDevice);  LossInputDevice = NULL;
	free(LossInputHost);    LossInputHost = NULL;
	free(LossGradDevice);   LossGradDevice = NULL;
	free(LossGradHost);     LossGradHost = NULL;
	free(LossHiddenDevice); LossHiddenDevice = NULL;
	free(LossHiddenHost);   LossHiddenHost = NULL;

	free(HvInputDevice);    HvInputDevice = NULL;
	free(HvInputHost);      HvInputHost = NULL;
	free(HvParaDevice);     HvParaDevice = NULL;
	free(HvParaHost);       HvParaHost = NULL;
	free(HvHiddenDevice);   HvHiddenDevice = NULL;
	free(HvHiddenHost);     HvHiddenHost = NULL;

	free(JacobiInputDevice); JacobiInputDevice = NULL;
	free(JacobiInputHost);   JacobiInputHost = NULL;
	free(JacobiParaDevice);  JacobiParaDevice = NULL;
	free(JacobiParaHost);    JacobiParaHost = NULL;
	free(JacobiHiddenDevice); JacobiHiddenDevice = NULL;
	free(JacobiHiddenHost);  JacobiHiddenHost = NULL;

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
void ANetWork::ANetWork::SetBatchSize(size_t BatchSize)
{
	refresh();
	if (BatchSize == 0 || BatchSize >= ld) count = ld;
	else count = BatchSize;
}


void ANetWork::computeOringinal()
{

}
void ANetWork::compute()
{

}
void ANetWork::computeLoss()
{
	
}
void ANetWork::computeHv()
{

}
void ANetWork::computeJacobi()
{

}