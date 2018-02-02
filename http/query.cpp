#include "cube\http\query.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////query class///////////////////////////////////////////
std::string query::pack() const {
	int sz = BUFSZ;
	char data[BUFSZ] = { 0 };

	sz = snprintf(data, sz, "%s %s %s\r\n", _method.c_str(), _uri.pack().c_str(), _version.pack().c_str());
	return std::string(data, sz);
}

int query::parse(const char *str, std::string *err) {
	std::vector<std::string> items;
	str::part(str, " ", items, 3);
	if (items.size() != 3) {
		safe_assign<std::string>(err, str::format("query line: %s, invalid request", str));
		return -1;
	}

	//parse method
	_method = items[0];

	//parse query
	if (_uri.parse(items[1].c_str(), items[1].length(), err) != 0)
		return -1;

	//parse protocol & version
	if (_version.parse(items[2].c_str(), items[2].length(), err) != 0)
		return -1;

	return 0;
}

END_CUBE_HTTP_NS
