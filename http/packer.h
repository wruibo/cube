#pragma once
#include "cube\http\header.h"
BEGIN_CUBE_HTTP_NS
class packer {
public:
	static std::string pack(const header &header);
	static std::string pack(const headers &headers);

};
END_CUBE_HTTP_NS


