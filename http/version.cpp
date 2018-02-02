#include "cube\http\version.h"
#include "cube\str\case.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////http version class/////////////////////////////////////////
std::string version::pack() const {
	//data buffer
	int sz = BUFSZ;
	char data[BUFSZ] = { 0 };

	//pack version
	sz = snprintf(data, sz, "%s/%s", _name.c_str(), _code.c_str());
	return std::string(data, sz);
}

int version::parse(const char *data, int sz, std::string *err) {
	std::vector<std::string> items;
	str::part(data, sz, "/", items);
	if (items.size() != 2) {
		safe_assign<std::string>(err, str::format("http version: %s, invalid http version", std::string(data, sz).c_str()));
		return -1;
	}

	//check protocol
	if (str::lower(items[0]) != "http") {
		safe_assign<std::string>(err, str::format("http version: %s, protocol not supported", items[0].c_str()));
		return -1;
	}

	//set name & code
	_name = items[0];
	_code = items[1];

	return 0;
}
END_CUBE_HTTP_NS
