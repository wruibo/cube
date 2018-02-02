#include "cube\http\cookie.h"
#include <time.h>
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////cookie class/////////////////////////////////////////
cookie::cookie(const std::string &name, const std::string &value) : _name(name), _value(value), _domain(""), _path(""), _expires(0), _maxage(0) {

}

cookie::cookie(const std::string &name, const std::string &value, const std::string &domain, const std::string &path, int maxage) : _name(name), _value(value), _domain(domain), _path(path), _maxage(maxage) {
	_expires = time(0) + _maxage;
}

std::string cookie::expires() const {
	return ctime(&_expires);
}

//////////////////////////////////////////cookies class/////////////////////////////////////////
std::string cookies::get(const std::string &name) {
	std::map<std::string, cookie>::const_iterator citer = _cookies.find(name);
	if (citer != _cookies.end()) {
		return citer->second.value();
	}
	return "";
}

void cookies::set(const std::string &name, const std::string &value, const std::string &domain, const std::string &path, int maxage) {
	_cookies[name] = cookie(name, value, domain, path, maxage);
}
END_CUBE_HTTP_NS
