#pragma once
#include "cube\str\def.h"
#include <vector>
BEGIN_CUBE_STR_NS
/*
*	format string
*@param format: in, format string
*@...: in, arguments meet the format
*@return:
*	formated string
*/
std::string print(const char *format, ...);
void print(std::string &result, const char *format, ...);

/*
*	print table data to console
*@param table: in, table want to print
*@return
*	void
*/
static void print(const std::vector<std::vector<std::string>> &table, int colwidth = 10);
END_CUBE_STR_NS
