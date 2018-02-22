#include "cube\http\header.h"
#include "cube\str\case.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
#include <stdarg.h>
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////element class///////////////////////////////////////
std::string element::pack() const {

}

int element::parse(const std::string &data, std::string *err) {
	
}


//////////////////////////////////////////elements class///////////////////////////////////////
int elements::has(const std::string &name) const {
	
}

element elements::get(const std::string &name) const {

}

//////////////////////////////////////////header class/////////////////////////////////////////
const header headers::_empty_header;

bool headers::has(const std::string &name) const {
	return _headers.find(cube::str::lower(name)) != _headers.end();
}

int headers::count() const {
	return (int)_headers.size();
}

int headers::count(const std::string &name) const {
	return (int)_headers.count(cube::str::lower(name));
}

void headers::set(const header &header) {
	_headers.insert(std::pair<std::string, http::header>(cube::str::lower(header.name()), header));
}

const header &headers::get(const std::string &name) const {
	std::multimap<std::string, header>::const_iterator citer = _headers.find(cube::str::lower(name));
	if (citer != _headers.end()) {
		return citer->second;
	}

	return _empty_header;
}

void headers::set(const headers *headers) {
	std::multimap<std::string, header>::const_iterator citer = headers->_headers.begin(), citerend = headers->_headers.end();
	while (citer != _headers.end()) {
		set(citer->second);
		citer++;
	}
}
END_CUBE_HTTP_NS
