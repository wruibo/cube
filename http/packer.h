#pragma once
#include "cube\http\header.h"
BEGIN_CUBE_HTTP_NS
class packer {
public:
	static int pack(const header *header, std::string *str, std::string *err = 0);
	static int pack(const headers *headers, std::string *str, std::string *err = 0);

};
END_CUBE_HTTP_NS


