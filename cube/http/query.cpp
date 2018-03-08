#include "cube\log\log.h"
#include "cube\str\part.h"
#include "cube\http\query.h"
BEGIN_CUBE_HTTP_NS
std::string query::pack() const {
	const int BUFSZ = 4096;
	char data[BUFSZ] = { 0 };

	int sz = snprintf(data, BUFSZ, "%s %s HTTP/%s\r\n", _method.c_str(), _uri.pack().c_str(), _version.c_str());
	return std::string(data, sz);
}

int query::parse(const std::string &str) {
	std::vector<std::string> items;
	cube::str::part(str.c_str(), " ", items, 3);
	if (items.size() != 3) {
		log::error("query line: %s, invalid request", str);
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
