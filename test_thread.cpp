
#include  "thread.cpp"
using namespace std;

class Incrthread: public Thread
{
private:
        Data* data;
public:
	Incrthread(Data* datat,int t = SCHED_OTHER);
	~Incrthread();
	void run();
};

Incrthread::Incrthread(Data *datat, int t)
{
	data = datat;
	schedPolicy = t;
}

Incrthread::~Incrthread()
{

}

void Incrthread::run()
{
  	int i;
  	for (i =0 ; i < data->nLoops ; i ++)
  	{
  	  *(data->pCounter) += 1.0;
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

	vector <Incrthread> thread(nTasks,Incrthread(&data));
	
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
