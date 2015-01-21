#include <list>
#include <iostream>
#include "test_hex.h"
#include "test_timer.h"
#include "test_crontab.h"
#include "test_blocking_queue.h"
using namespace std;

int main(int argc, char* argv[])
{
	//test_hex();
	//test_timer();
	//test_crontab();
	test_blocking_queue();
	return 0;
}