#pragma once
#include "cube\http\stream.h"
#include <iostream>
BEGIN_CUBE_HTTP_NS
//http entity class
class entity {
public:


private:
	//entity data stream
	stream *_stream;
};

//form entity class
class entity_form : public entity {
public:
	entity_form() {}
	virtual ~entity_form() {}


private:
};

//data entity class
class entity_data : public entity {
public:
	entity_data() {}
	virtual ~entity_data() {}

};

//file entity class
class entity_file : public entity {
public:
	entity_file() {}
	virtual ~entity_file() {}

};
END_CUBE_HTTP_NS
