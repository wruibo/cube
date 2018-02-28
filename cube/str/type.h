#pragma once
#include "cube\str\def.h"
BEGIN_CUBE_STR_NS
/*
*	functions to classify characters
*@param str: in, string to classify
*@return:
*	true if match the classifier, otherwise false
*/
bool isnum(const char* str);
bool isdigit(const char* str);
bool isxdigit(const char* str);
bool isalpha(const char* str);
bool isalnum(const char* str);
bool islower(const char* str);
bool isupper(const char* str);
bool isfloat(const char* str);
END_CUBE_STR_NS
