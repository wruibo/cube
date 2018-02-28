#include "cube\http\header.h"
#include "cube\str\case.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
#include <algorithm>
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////element class///////////////////////////////////////

//////////////////////////////////////////field class///////////////////////////////////////
bool field::operator==(const field &field) const {
	return str::lower(name()) == str::lower(field.name());
}

bool field::operator==(const std::string &name) const {
	return str::lower(field::name()) == str::lower(name);
}

//////////////////////////////////////////header class/////////////////////////////////////////
void header::add(const std::string &name, const std::string &value) {
	_fields.push_back(field(name, value));
}

void header::set(const std::string &name, const std::string &value) {
	std::vector<field>::iterator iter = std::find(_fields.begin(), _fields.end(), name);
	if (iter != _fields.end()) {
		(*iter).value(value);
	} else {
		_fields.push_back(field(name, value));
	}
}

END_CUBE_HTTP_NS
