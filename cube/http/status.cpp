#include "cube\http\status.h"
#include "cube\str\cast.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
BEGIN_CUBE_HTTP_NS
/////////////////////////////////////////status class/////////////////////////////////////////////
std::map<int, std::pair<std::string, std::string>> status::_status;
status::setter s_ok(200, "OK");
status::setter r_moved_permanently(301, "Moved Permanently");
status::setter r_moved_temporarily(302, "Found");
status::setter cerr_bad_request(400, "Bad Request");
status::setter cerr_not_found(404, "Not Found");
status::setter cerr_method_not_allowed(405, "Method Not Allowed");
status::setter serr_interval_server_error(500, "Internal Server Error");

status::setter::setter(int code, const std::string &reason) {
	status::_status[code] = std::pair<std::string, std::string>(str::string(code), reason);
}

std::string status::pack() const {
	int sz = BUFSZ;
	char data[BUFSZ] = { 0 };

	sz = snprintf(data, sz, "%s %s %s\r\n", _version.pack().c_str(), _code.c_str(), _reason.c_str());
	return std::string(data, sz);
}

int status::set(int code, std::string *err) {
	std::map<int, std::pair<std::string, std::string>>::const_iterator citer = _status.find(code);
	if (citer == _status.end()) {
		safe_assign<std::string>(err, str::format("status line: %d, not supported", code));
		return -1;
	}

	//set code & reason
	_code = citer->second.first;
	_reason = citer->second.second;

	return 0;
}

int status::parse(const char *str, std::string *err) {
	//split status line
	std::vector<std::string> items;
	str::part(str, " ", items, 3);
	if (items.size() != 3) {
		safe_assign<std::string>(err, str::format("status line: %s, invalid response", str));
		return -1;
	}

	//parse http version
	if (_version.parse(items[0].c_str(), items[0].length(), err) != 0)
		return -1;

	//parse status code
	_code = items[1];

	//parse status phrase reason
	_reason = items[2];

	return 0;
}

END_CUBE_HTTP_NS
