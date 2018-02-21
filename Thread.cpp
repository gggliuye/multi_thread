#include  "thread.h"

Thread::Thread(int t)
{
	 schedPolicy = t;
}


Thread::~Thread()
{

}

void* Thread::call_run(void* vv)
{
	Thread* va = (Thread*) vv;
	va->run();
	return va;
}

bool Thread::start(int priority)
{
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, schedPolicy);
	schedParams.sched_priority = priority;
	pthread_attr_setschedparam(&attr, &schedParams);
	bool temp;
	temp = pthread_create(&posix_id, &attr, &Thread::call_run , this);
	if( temp == 0)
	{
		started = 1;
	}	
	else
	{
		started = 0;
	}

	return temp;
}


void Thread::setStackSize(size_t stackSize)
{
	pthread_attr_setstacksize(&attr, stackSize);
}

void Thread::join()
{
	pthread_join(posix_id,NULL);
}

bool Thread::join(double timeout_ms)
{
	struct timespec ts;
	double timeout = timeout_ms / 1000;
	ts.tv_sec += int(timeout);
	double temp;
	temp = (timeout - int(timeout))*1000000;
	ts.tv_nsec += int(temp);
	return pthread_timedjoin_np(posix_id,NULL, &ts);
}

void Thread::sleep(double timeout_ms)
{
    	struct timespec ts;
    	struct timespec rem;
    	double timeout = timeout_ms / 1000;
    	ts.tv_sec += int(timeout);
    	double temp;
    	temp = (timeout - int(timeout))*1000000;
    	ts.tv_nsec += int(temp);
    	do
	{
		nanosleep(&ts, &rem);
    	}
   	while(!(rem.tv_sec==0 && rem.tv_nsec==0));
}


void Thread::run()
{

}
