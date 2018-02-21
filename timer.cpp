#include "timer.h"

Timer::Timer()
{	
  	sa.sa_flags = SA_SIGINFO;
  	sa.sa_sigaction = call_callback;
  	sigemptyset(&sa.sa_mask);
  	sigaction(SIGRTMIN, &sa, NULL);	
	sev.sigev_notify = SIGEV_SIGNAL;
  	sev.sigev_signo = SIGRTMIN;  
  	sev.sigev_value.sival_ptr = this;
        cout << "successful constructor" << endl;
}

Timer::~Timer()
{
	timer_delete(tid);
}

void Timer::start(double duration_ms)
{
	int sec = (int)duration_ms/1000;
        int nsec = (int)((duration_ms-sec*1000)*1000000);
	timer_create(CLOCK_REALTIME, &sev, &tid);
	itimerspec its;
	its.it_value.tv_sec = 0;
  	its.it_value.tv_nsec = 0;
  	its.it_interval.tv_sec = sec;
  	its.it_interval.tv_nsec = nsec; 
	//its.it_value.tv_sec = 1;
  	//its.it_value.tv_nsec = 0;
  	//its.it_interval.tv_sec = 0;
  	//its.it_interval.tv_nsec = 0; 
	timer_settime(tid,0,&its,NULL);
}

void Timer::stop()
{
	itimerspec its;
	its.it_value.tv_sec = 0;
  	its.it_value.tv_nsec = 0;
  	its.it_interval.tv_sec = 0;
  	its.it_interval.tv_nsec = 0; 
	timer_settime(tid,0,&its,NULL);
}



void Timer::call_callback(int sig, siginfo_t* si, void* user)
{
	Timer* t = (Timer*)si->si_value.sival_ptr;
	t->callback();
}





