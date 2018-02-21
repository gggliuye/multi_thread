#ifndef Lock_hpp_INCLUDED
#define Lock_hpp_INCLUDED

#include "mutex.cpp"

class Lock 
{
protected:
	Mutex* mutex;
public:
	Lock(Mutex* mutexx);
	Lock(Mutex* mutexx, double timeout_ms);
	~Lock();
	pthread_mutex_t* getmutexid();


};

Lock::Lock(Mutex* mutexx)
{
	mutex = mutexx;
	mutex->lock();
}

Lock::Lock(Mutex* mutexx,double timeout_ms)
{
	mutex = mutexx;
	mutex->lock(timeout_ms);
}


Lock::~Lock()
{
	mutex->unlock();
}

pthread_mutex_t* Lock::getmutexid()
{
	return mutex->getid();
}


#endif
