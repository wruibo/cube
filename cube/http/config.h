#pragma once
#include "cube\ns.h"
BEGIN_CUBE_HTTP_NS
class config {
public:
	static const char * server;
	static const char * domain;
	static const char * default_charset;

	static int max_entity_length;
};
END_CUBE_HTTP_NS
