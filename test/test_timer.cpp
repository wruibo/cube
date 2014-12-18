#include "test_timer.h"
#include "cube/timer/timer.h"
#include <string>
#include <iostream>

class timer_task : public cube::timer::task
{
public:
	timer_task(const char* name): _name(name)
	{

	}

	int run()
	{
		std::cout<<"run task "<<_name.c_str()<<": "<<cube::time::now("%Y%m%d %H:%M:%S")<<std::endl;
		return 0;
	}

private:
	std::string _name;
};
void test_timer()
{
	cube::timer::task *t1 = new timer_task("1");
	cube::timer::task *t2 = new timer_task("2");
	cube::timer::task *t3 = new timer_task("3");
	cube::timer::task *t4 = new timer_task("4");

	cube::timer::timer mytimer;
	mytimer.init();
	mytimer.schedule(t3, 5000, 3000);
	mytimer.schedule(t2, 3000, 2000);
	mytimer.schedule(t1, 1000, 500);

	cube::thread::sleep(10000);
	mytimer.schedule(t4, 0, 4000);

	cube::thread::sleep_for_ever();
}