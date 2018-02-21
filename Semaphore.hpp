#ifndef Semaphore_hpp_INCLUDED
#define Semaphore_hpp_INCLUDED

#include  "Condition.hpp"
#define UNIT_MAX 10000000

class Semaphore
{
private:
	unsigned counter;
	unsigned maxCount;
	Mutex mutex;
	Condition cond;

public:
	Semaphore(unsigned iCount = 0, unsigned mCount=UNIT_MAX);
	~Semaphore();
	void give();
	void flush();
	void take();
	bool take(double timeout_ms);
	unsigned getcounter();
	unsigned getmax();
};

Semaphore::Semaphore(unsigned iCount, unsigned mCount)
{
	counter = iCount;
	maxCount = mCount;
}

Semaphore::~Semaphore()
{
}

void Semaphore::give()
{
	//if(counter < maxCount)
	{
		try
		{
			{
				Lock lock(&mutex);
  	  			counter = counter + 1;
			}
		}
		catch(std::exception &e)
		{
			std::cout<<"error with give\n";
		} 
	}
}

void Semaphore::flush()
{
	std::cout<<"error, try to take when counter is 0!! go to flush\n";
	Lock lock(&mutex);	
	cond.notify(&lock);
	cond.notifyAll(&lock);
}


void Semaphore::take()
{
	if(counter > 0)
	{
		try
		{
			{
				Lock lock(&mutex);
  	  			counter = counter - 1;
			}
		}
		catch(std::exception &e)
		{
			flush();
		} 
	}
	else
	{
		flush();
	}
}


bool Semaphore::take(double timeout_ms)
{
	Lock lock(&mutex);
	cond.wait( &lock,timeout_ms);
	if(counter > 0)
	{
		try
		{
			{
				Lock lock(&mutex);
  	  			counter = counter - 1;
				return 1;
			}
		}
		catch(std::exception &e)
		{
			flush();
			return 0;
		} 
	}
	else
	{
		flush();
		return 0;
	}
}

unsigned Semaphore::getcounter()
{
	return counter;
}


unsigned Semaphore::getmax()
{
	return maxCount;
}

#endif
