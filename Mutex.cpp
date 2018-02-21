#include "mutex.h"

Mutex::Mutex(bool safe)
{
	isInversionSafe = safe;
	pthread_mutex_init(&mutex_id,NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mutex_id);
}

int Mutex::lock()
{
	if(isInversionSafe)
	{
		return pthread_mutex_lock(&mutex_id);
	}	
	else
	{
		return 1;
	}
}

int Mutex::lock(double timeout_ms)
{
	if(isInversionSafe)
	{
		struct timespec ts;
		double timeout = timeout_ms / 1000;
		ts.tv_sec += int(timeout);
		double temp;
		temp = (timeout - int(timeout))*1000000;
		ts.tv_nsec += int(temp);
		return pthread_mutex_timedlock(&mutex_id, &ts);
	}	
	else
	{
		return 1;
	}	

}

int Mutex::trylock()
{
	if(isInversionSafe)
	{
		pthread_mutex_trylock(&mutex_id);
	}	
	else
	{
		return 1;
	}
}


int Mutex::unlock()
{
	
	return pthread_mutex_unlock(&mutex_id);
}


pthread_mutex_t* Mutex::getid()
{
	return &mutex_id;
}



