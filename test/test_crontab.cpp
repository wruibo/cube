#include "test_crontab.h"
#include <iostream>
#include "cube/timer/crontab.h"

class echo_task : public cube::timer::task
{
public:
	int run()
	{
		std::cout<<"task run: "<<cube::time::now("%Y%m%d %H:%M:%S")<<std::endl;
		return 0;
	}
};
void test_crontab()
{
	cube::timer::crontab crontab_impl;
	cube::timer::task *t = new echo_task();
	crontab_impl.init();
	crontab_impl.schedule(t, -1, -1, -1, -1, -1);
	
	cube::thread::sleep_for_ever();
}
