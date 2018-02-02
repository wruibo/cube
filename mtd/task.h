#pragma once
#include "cube\mtd\def.h"
BEGIN_CUBE_MTD_NS
//runnable task
class task {
public:
	virtual void run() = 0;
};

END_CUBE_MTD_NS
