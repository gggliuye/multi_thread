#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include<iostream>
#include <signal.h>
#include <time.h>
#include <pthread.h>
using namespace std;



class Timer
{
public:
	Timer();
	virtual ~Timer();
	virtual void start(double duration_ms);
	void stop();
	
			
protected:
	virtual void callback()=0;
	timer_t tid;
	struct sigevent sev;
private:
	struct sigaction sa;	
	static void call_callback(int sig, siginfo_t* si, void* user);
};

#endif
