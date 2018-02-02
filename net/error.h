#pragma once
#include "cube\net\def.h"
BEGIN_CUBE_NET_NS
int last_error_code();
std::string last_error();
std::string last_error(int error_code);
END_CUBE_NET_NS
