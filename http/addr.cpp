#include "cube\http\addr.h"
#include "cube\str\type.h"
#include "cube\str\strip.h"
#include "cube\str\format.h"

BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////address class/////////////////////////////////////////
std::string addr::pack() const {
	int sz = 0;
	char data[BUFSZ] = { 0 };
	if (_port == 80)
		sz = snprintf(data, BUFSZ, "%s", _host.c_str());
	else
		sz = snprintf(data, BUFSZ, "%s:%d", _host.c_str(), _port);

	return std::string(data, sz);
}

int addr::parse(const char *data, int sz, std::string *err) {
	//find seperator of host and port
	const char *start = data, *end = data + sz, *pos = data;
	while (*pos != ':' && pos < end)
		pos++;

	//parse host and port
	std::string host(""), port("80");
	if (*pos == ':') {
		host = str::strip(start, pos - start);
		port = str::strip(pos + 1, end - pos - 1);
	} else {
		//only host found
		host = str::strip(data, sz);
	}

	//check host and port
	if (host.empty()) {
		safe_assign<std::string>(err, "address: empty host");
		return -1;
	}

	if (!str::isdigit(port.c_str())) {
		safe_assign<std::string>(err, str::format("address: %s, invalid port", port.c_str()));
		return -1;
	}

	//set host and port
	_host = host;
	_port = (ushort)::atoi(port.c_str());

	return sz;
}
END_CUBE_HTTP_NS
