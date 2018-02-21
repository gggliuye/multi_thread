#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include  "Condition.hpp"

class Fifo
{
private:
	Mutex mutex;
	Condition cond;
	std::queue<T> elements;
	class EmptyException : public exception
	{
 		virtual const char* what() const throw()
  		{
   	 	return "exception happened";
  		}	
	} myex;

public:
	Fifo();
	~Fifo();
	void push(T element);
	T pop();
	T pop(double timeout_ms);
}

Fifo::Fifo()
{

}

Fifo::~Fifo()
{

}

void Fifo::push(T element)
{
	elements.push(element);
}

T Fifo::pop()
{
	while (!elements.empty())
	{
		return elements.pop();
	}
}

T Fifo::pop(double timeout_ms)
{
	Lock lock(&mutex);
	cond.thread_cond_wait( &lock,timeout_ms);
	try
  	{
    		return pop();
 	}
  	catch (exception& e)
  	{
		throw myex;
    		cout << e.what() << '\n';
  	}
  	return 0;
}

}



#endif
