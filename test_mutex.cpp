#include  "thread.cpp"
#include  "Lock.hpp"
using namespace std;

class Incrthread: public Thread
{
private:
        Data* data;
	Mutex* mutex;
public:
	Incrthread(Data* datat,Mutex* mutexx,int t = SCHED_OTHER);
	~Incrthread();
	void run();
};

Incrthread::Incrthread(Data *datat, Mutex* mutexx,int t)
{
	data = datat;
	schedPolicy = t;
	mutex = mutexx;
}

Incrthread::~Incrthread()
{

}


void Incrthread::run()
{
  	int i;
  	for (i =0 ; i < data->nLoops ; i ++)
  	{	
		try
		{
			{
				Lock lock(mutex);
  	  			*(data->pCounter) += 1.0;
			}
		}
		catch(std::exception &e)
		{
			cout<<"error";
		}  	
	}
}



int main(int argc, char* argv[])
{
  	timespec debut, fin, duree;
  
 	unsigned int nLoops;
  	sscanf(argv[1], "%d", &nLoops);

  	unsigned int nTasks;
  	sscanf(argv[2], "%d", &nTasks);
  	double counter = 0.0;
  	Data data;
  	data.nLoops = nLoops;
  	data.pCounter = &counter;
  	Mutex mutex_idd;

  	vector <Incrthread> thread(nTasks,Incrthread(&data,&mutex_idd));
 
  	clock_gettime(CLOCK_REALTIME, &debut);
  	for (int i = 0 ; i < nTasks ; i++)
  	{
		thread[i].start(9);
  
  	}

 	 for (int i = 0 ; i < nTasks ; i++)
  	{
     		thread[i].join();
  
  	}
  
  
  	clock_gettime(CLOCK_REALTIME, &fin);

  	printf("the counter is %lf \n",counter);

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
