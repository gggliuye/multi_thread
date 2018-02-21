
#include  "Lock.hpp"
#include  "thread.cpp"
#include  "Semaphore.hpp"
using namespace std;

class Incrthread: public Thread
{
private:
        Semaphore* sema;

public:
	Incrthread(Semaphore* sema_p, int t = SCHED_OTHER);
	~Incrthread();
	void run();
};

Incrthread::Incrthread(Semaphore* sema_p,int t)
{
	schedPolicy = t;
	sema = sema_p;

}

Incrthread::~Incrthread()
{

}


void Incrthread::run()
{
  	int i;
  	for (i =0 ; i < sema->getmax() ; i ++)
  	{	
		sema->give();
	}
}

class Decrthread: public Thread
{
private:
        Semaphore* sema;

public:
	Decrthread(Semaphore* sema_p, int t = SCHED_OTHER);
	~Decrthread();
	void run();
};

Decrthread::Decrthread(Semaphore* sema_p,int t)
{
	schedPolicy = t;
	sema = sema_p;

}

Decrthread::~Decrthread()
{

}


void Decrthread::run()
{
  	int i;
  	for (i =0 ; i < sema->getmax() ; i ++)
  	{	
		sema->take();
	}
}


int main(int argc, char* argv[])
{
  	timespec debut, fin, duree;
  
 	unsigned int nLoops;
  	sscanf(argv[1], "%d", &nLoops);

  	unsigned int nTasks1;
  	sscanf(argv[2], "%d", &nTasks1);
  	
	unsigned int nTasks2;
  	sscanf(argv[3], "%d", &nTasks2);

	Semaphore sema(0, nLoops);

  	vector <Incrthread> thread1(nTasks1,Incrthread(&sema));
	vector <Decrthread> thread2(nTasks2,Decrthread(&sema));
 
  	clock_gettime(CLOCK_REALTIME, &debut);
  	for (int i = 0 ; i < nTasks1 ; i++)
  	{
		thread1[i].start(9);
  
  	}
	for (int i = 0 ; i < nTasks2 ; i++)
  	{
		thread2[i].start(9);
  
  	}

 	 for (int i = 0 ; i < nTasks1 ; i++)
  	{
     		thread1[i].join();
  
  	}
	for (int i = 0 ; i < nTasks2 ; i++)
  	{
     		thread2[i].join();
  
  	}
  
  	clock_gettime(CLOCK_REALTIME, &fin);

  	printf("the counter is %d \n",sema.getcounter());

  	duree.tv_sec = fin.tv_sec - debut.tv_sec;
  	if (fin.tv_nsec < debut.tv_nsec)
  	{
    		duree.tv_sec -= 1;
    		fin.tv_nsec += 1000000000;
  	}
  	duree.tv_nsec = fin .tv_nsec - debut.tv_nsec;
  	printf("Measured duration is %ld seconds and %ld nanoseconds, equivalent to %f millisconds\n", 
    	duree.tv_sec, duree.tv_nsec, duree.tv_sec*1000. + duree.tv_nsec/1000000.);

  	return 0;
}
