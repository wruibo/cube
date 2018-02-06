/*
*	field - http message header field class
*/
#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
//header field object
class field {
public:
	field();
	virtual ~field();

private:

};

class field_content_type : public field {
public:
	field_content_type() {}
	virtual ~field_content_type() {}

private:

};

class field_content_length : public field {

};
END_CUBE_HTTP_NS
