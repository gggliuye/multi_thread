#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <vector>
#include <iostream>


struct Data {
   unsigned int nLoops;
   volatile double* pCounter;
};

class Thread
{
private:
	static void* call_run(void* v_thread);
	pthread_t posix_id;
	pthread_attr_t attr;
	sched_param schedParams;
	bool started;
	

public:
	//Thread();
	Thread(int t = SCHED_OTHER);
	virtual ~Thread();	
	void setStackSize(size_t stackSize);
	bool start(int priority);
	void join();
	bool join(double timeout);
	void sleep(double delay_ms);

protected:
	virtual void run();
	int schedPolicy;

};

#endif


