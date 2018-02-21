#ifndef Condition_hpp_INCLUDED
#define Condition_hpp_INCLUDED

#include  "Lock.hpp"


class Condition
{
protected:
	pthread_cond_t condid;

public:
	Condition();
	~Condition();
	void wait(Lock* lock);
	bool wait(Lock* lock, double timeout_ms);
	void notify(Lock* lock);
	void notifyAll(Lock* lock);

};

Condition::Condition()
{
	pthread_cond_init(&condid,NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&condid);
}

void Condition::wait(Lock* lock)
{
	pthread_cond_wait(&condid, lock->getmutexid());
}

bool Condition::wait(Lock* lock, double timeout_ms)
{
	struct timespec ts;
	double timeout = timeout_ms / 1000;
	ts.tv_sec += int(timeout);
	double temp;
	temp = (timeout - int(timeout))*1000000;
	ts.tv_nsec += int(temp);
	return pthread_cond_timedwait(&condid, lock->getmutexid(),&ts);
}

void Condition::notify(Lock* lock)
{
	std::cout<<"notify the lock! \n";
	pthread_cond_signal(&condid);
}


void Condition::notifyAll(Lock* lock)
{
	pthread_cond_broadcast(&condid);
}



#endif
