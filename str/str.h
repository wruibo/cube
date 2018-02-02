#pragma once
#include "cube\str\case.h"
#include "cube\str\cast.h"
#include "cube\str\find.h"
#include "cube\str\format.h"
#include "cube\str\hex.h"
#include "cube\str\part.h"
#include "cube\str\print.h"
#include "cube\str\rand.h"
#include "cube\str\split.h"
#include "cube\str\strip.h"
#include "cube\str\type.h"
#include "cube\str\url.h"

BEGIN_CUBE_STR_NS
/*
*	check if input string is empty
*@param str: string to check
*@return:
*	true if input string is empty, otherwise false
*/
bool empty(const char* str);
END_CUBE_STR_NS
