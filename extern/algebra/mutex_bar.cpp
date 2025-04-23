#include"linear_algebra.h"
#include<stdlib.h>
mutex_bar::mutex_bar(unsigned int amount_mutex, unsigned int thread_amount)
{
	unsigned int i;
	amount = amount_mutex;
	amount_thread = thread_amount;
	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * amount_mutex);
	for (i = 0; i < amount_mutex; i++)
		pthread_mutex_init(mutex + i, NULL);
	barrier_count = 0;
	sem_init(&count_sem, 0, 1);
	sem_init(&barrier_sem, 0, 0);
	sem_init(&reset_sem, 0, 0);
}
mutex_bar::~mutex_bar()
{
	unsigned int i;
	for (i = 0; i < amount; i++)
		pthread_mutex_destroy(mutex + i);
	free((void*)mutex);
	sem_destroy(&count_sem);
	sem_destroy(&barrier_sem);
	sem_destroy(&reset_sem);
}
void mutex_bar::lock(unsigned int No)
{
	pthread_mutex_lock(mutex + No);
}
void mutex_bar::unlock(unsigned int No)
{
	pthread_mutex_unlock(mutex + No);
}
void mutex_bar::lock(void)
{
	pthread_mutex_lock(mutex);
}
void mutex_bar::unlock(void)
{
	pthread_mutex_unlock(mutex);
}
void mutex_bar::barrier(void)
{
	sem_wait(&count_sem);
	if(barrier_count + 1 == amount_thread)
	{
		sem_post(&barrier_sem);
		sem_wait(&reset_sem);
		sem_post(&count_sem);
	}
	else
	{
		barrier_count += 1;
		sem_post(&count_sem);
		sem_wait(&barrier_sem);
		barrier_count -= 1;
		if(barrier_count == 0) sem_post(&reset_sem);
		else sem_post(&barrier_sem);
	}
}

signal_bar::signal_bar(unsigned int thread_amount)
{
	amount = thread_amount;
	sem_init(&arrival_sem, 0, 1);
	sem_init(&wait_sem, 0, 0);
}
signal_bar::~signal_bar()
{
	sem_destroy(&arrival_sem);
	sem_destroy(&wait_sem);
}
void signal_bar::arrival(int sig)
{
	sem_wait(&arrival_sem);
	signal = sig;
	No = 0;
	sem_post(&wait_sem);
}
void signal_bar::arrival_wait(int sig)
{
	arrival(sig);
	sem_wait(&arrival_sem);
	sem_post(&arrival_sem);
}
int signal_bar::wait(void)
{
	int signal_store;
	sem_wait(&wait_sem);
	No += 1;
	signal_store = signal;
	if (No == amount) sem_post(&arrival_sem);
	else sem_post(&wait_sem);
	return signal_store;
}

report_bar::report_bar(unsigned int thread_amount)
{
	amount = thread_amount;
	No = 0; 
	sem_init(&arrival_sem, 0, 1);
	sem_init(&wait_sem, 0, 0);
}
report_bar::~report_bar()
{
	sem_destroy(&arrival_sem);
	sem_destroy(&wait_sem);
}
void report_bar::report(void)
{
	sem_wait(&arrival_sem);
	No++;
	if(No == amount) sem_post(&wait_sem);
	else sem_post(&arrival_sem);
}
void report_bar::wait(void)
{
	sem_wait(&wait_sem);
	No = 0;
	sem_post(&arrival_sem);
}

//pthread_handle::pthread_handle(unsigned int thread_amount, void* (*F)(void*))
//{
//	f = F;
//	amount = thread_amount;
//}
pthread_handle::pthread_handle(unsigned int thread_amount, void* (*F)(void*), void **Arg)
{
    type = 0;
	handle = (pthread_t*)malloc(sizeof(pthread_t) * thread_amount);
	f = F;
	amount = thread_amount;
	arg = Arg;
	//No = No__;
}
pthread_handle::pthread_handle(unsigned int thread_amount, void* (*F)(void*), void *Arg, size_t sizeof_arg)
{
    int i;
    type = 1;
    handle = (pthread_t*)malloc(sizeof(pthread_t) * thread_amount);
	f = F;
	amount = thread_amount;
	arg = (void**)malloc(sizeof(void*) * thread_amount);
    for (i = 0; i < thread_amount; i++)
        arg[i] = Arg + (size_t)i * sizeof_arg;
    
}
pthread_handle::~pthread_handle()
{
	unsigned int i;
	for(i = 0; i < amount; i++)
		pthread_join(handle[i], NULL);
	free((void*)handle);
    if(type != 0) free(arg);
}
//void pthread_handle::arg_set(void *Arg, unsigned int No__)
//{
//	arg = Arg;
//	No = No__;
//}
void pthread_handle::launch(void)
{
	unsigned int i;
	for(i = 0; i < amount; i++)
		pthread_create(handle + i, NULL, f, arg[i]);
	
}

