#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <vector>
#include <iostream>

class Mutex
{
   protected:
	pthread_mutex_t mutex_id;
	bool isInversionSafe;

   public:
	Mutex(bool safe=1);
	~Mutex();
	int lock();
	int lock(double timeout_ms);
	int trylock();
	int unlock();
	pthread_mutex_t* getid();


};


#endif

