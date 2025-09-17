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

