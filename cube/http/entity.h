#pragma once
#include "cube\http\header.h"
#include <vector>
#include <memory>
#include <iostream>
BEGIN_CUBE_HTTP_NS
//http entity class
class entity {
public:
	entity(){}
	virtual ~entity() {}

private:
};

//form entity class
class form : public entity {
public:
	form() {}
	virtual ~form() {}


private:
};

//data entity class
class data : public entity {
public:
	data() {}
	virtual ~data() {}

};

//file entity class
class file : public entity {
public:
	file() {}
	virtual ~file() {}

};

END_CUBE_HTTP_NS
