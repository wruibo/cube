#pragma once
#include "cube\str\def.h"
BEGIN_CUBE_STR_NS
char *find(char *str, int sz, int ch);
const char *find(const char *str, int sz, int ch);
char *find(char *str, int sz, const char *substr);
const char *find(const char *str, int sz, const char *substr);
END_CUBE_STR_NS
