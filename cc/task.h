#pragma once
#include "cube\cc\def.h"
BEGIN_CUBE_CC_NS
//runnable task
class task {
public:
	virtual void run() = 0;
};

END_CUBE_CC_NS
