#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
class object {
public:
	object() {}
	virtual ~object() {}
};

class object_content_type : public object{
public:
	object_content_type() : _type(""), _sub_type(""), _charset("") {}
	virtual ~object_content_type() {}

	
private:
	std::string _type;
	std::string _sub_type;
	std::string _charset;
};

END_CUBE_HTTP_NS

