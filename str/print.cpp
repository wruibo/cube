#include "cube\str\print.h"
#include <stdarg.h>
#include <iomanip>
#include <iostream>
BEGIN_CUBE_STR_NS
std::string print(const char *format, ...) {
	/*this buffer is properly not safe*/
	static const int BUFSZ = 1024;
	char buf[BUFSZ] = { 0 };

	va_list va;
	va_start(va, format);
	vsnprintf(buf, BUFSZ, format, va);
	va_end(va);

	return std::string(buf);
}

void print(std::string &result, const char *format, ...) {
	static const int BUFSZ = 1024;
	char buf[BUFSZ] = { 0 };

	va_list va;
	va_start(va, format);
	vsnprintf(buf, BUFSZ, format, va);
	va_end(va);

	result.assign(buf);
}

void print(const std::vector<std::vector<std::string>> &table, int colwidth) {
	for (size_t nrow = 0; nrow < table.size(); nrow++) {
		for (size_t ncol = 0; ncol < table[nrow].size(); ncol++) {
			std::cout << std::setw(colwidth) << table[nrow][ncol].c_str();
		}
		std::cout << std::endl;
	}
}
END_CUBE_STR_NS
