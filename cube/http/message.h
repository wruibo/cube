#pragma once
#include "cube\ns.h"
BEGIN_CUBE_HTTP_NS
class message {
public:
	/*
	*	check if entity has completed
	*/
	virtual bool has_entity_done() const = 0;

	/*
	*	put start line data to message
	*/
	virtual int put_start_line(const char *data, int sz) = 0;

	/*
	*	put header line data to message
	*/
	virtual int put_header_line(const char *data, int sz) = 0;

	/*
	*	put entity data to message
	*/
	virtual int put_entity_data(const char *data, int sz) = 0;
};
END_CUBE_HTTP_NS
