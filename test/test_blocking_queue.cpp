#include <string>
#include <sstream>
#include <iostream>
#include "test_blocking_queue.h"
#include "cube/thread/thread.h"
#include "cube/container/blocking_deque.h"

using namespace std;

class producer : public cube::thread::runnable
{
public:
	producer(int identifier, cube::container::blocking_deque<string> *queue):_identifier(identifier),_queue(queue){}

	void loop()
	{
		int i = 0;
		while(true)
		{
			stringstream ss;
			ss<<"producer id: "<<_identifier<<", num: "<<i;
			_queue->push_back(ss.str());
			i++;
		}
	}

private:
	int _identifier;
	cube::container::blocking_deque<string> *_queue;
};

class consumer : public cube::thread::runnable
{
public:
	consumer(int identifier, cube::container::blocking_deque<string> *queue):_identifier(identifier),_queue(queue){}

	void loop()
	{
		while(true)
		{
			string str;
			_queue->pop_front(str);
			cout<<"consumer id: "<<_identifier<<","<<str.c_str()<<endl;
		}
	}

private:
	int _identifier;
	cube::container::blocking_deque<string> *_queue;
};

void test_blocking_queue()
{
	cube::container::blocking_deque<string> q(1000);
	
	producer p1(1, &q);
	producer p2(2, &q);

	consumer c1(1, &q);
	consumer c2(2, &q);

	cube::thread::thread th1, th2, th3, th4;
	th1.start(&p1);
	th2.start(&p2);

	th3.start(&c1);
	th4.start(&c2);


	while (true)
	{
		cube::thread::sleep(10000);
	}
}