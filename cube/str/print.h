#pragma once
#include "cube\str\def.h"
#include <vector>
BEGIN_CUBE_STR_NS
/*
*	print table data to console
*@param table: in, table want to print
*@return
*	void
*/
void print(const std::vector<std::vector<std::string>> &table, int colwidth = 10);
END_CUBE_STR_NS
