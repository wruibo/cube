#include "cube\http\uri.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////uri class/////////////////////////////////////////
std::string uri::pack() const {
	//data buffer
	int sz = BUFSZ;
	char data[BUFSZ] = { 0 };

	//data pos
	int pos = 0;

	//add scheme
	if (!_scheme.empty()) {
		pos += snprintf(data + pos, sz - pos, "%s:", _scheme.c_str());
	}

	//add auth string
	if (!_auth.empty()) {
		pos += snprintf(data + pos, sz - pos, "//%s", _auth.c_str());
	}

	//add path string
	if (!_path.empty()) {
		pos += snprintf(data + pos, sz - pos, "/%s", _path.c_str());
	}

	//add query string
	if (!_query.empty()) {
		pos += snprintf(data + pos, sz - pos, "?%s", _query.c_str());
	}

	//add fragment string
	if (!_fragment.empty()) {
		pos += snprintf(data + pos, sz - pos, "#%s", _fragment.c_str());
	}

	return std::string(data, pos);
}

int uri::parse(const char *data, int sz, std::string *err) {
	//skip space characters
	const char *start = data, *end = data + sz;
	while (::isspace(*start))
		start++;

	while (::isspace(*end))
		end--;

	if (start > end) {
		safe_assign<std::string>(err, "uri: empty uri data.");
		return -1;
	}

	const char *pos = start;
	////parse scheme////
	//find scheme end flag
	while (*pos != ':' && pos < end)
		pos++;

	//save scheme if flag found
	if (*pos == ':') {
		_scheme = std::string(start, pos - start);
		start = ++pos;
	} else {
		pos = start;
	}

	////parse authority & address////
	//find authority start flag
	int slashnum = 0;
	while (slashnum != 2 && pos < end) {
		//skip space character
		if (::isspace(*pos)) {
			pos++;
			continue;
		}

		if (*pos == '/') {
			slashnum++;
			pos++;
		} else {
			//authority flag not found
			break;
		}
	}

	if (slashnum == 2) {
		//set authority start pos
		start = pos;

		//find authority end flag
		while (*pos != '/' && *pos != '?' && *pos != '#' && pos < end)
			pos++;

		//uri authority
		std::string auth = std::string(start, pos - start);

		//parse address
		if (_addr.parse(auth.c_str(), auth.length(), err) != 0)
			return -1;

		//set authority
		_auth = auth;

		//reset start pos
		start = pos;
	} else {
		//authority flag not found, reset pos
		pos = start;
	}

	////parse path////
	if (*pos == '/' && pos < end) {
		//skip path start flag
		start = pos++;

		//find path end flag(query or fragment start flag)
		while (*pos != '?' && *pos != '#' && pos < end)
			pos++;

		//save path
		_path = std::string(start, pos - start);
	}

	////parse query & params////
	if (*pos == '?' && pos < end) {
		//skip query start flag
		start = ++pos;

		while (*pos != '#' && pos < end)
			pos++;

		//query string
		std::string query = std::string(start, pos - start);

		//parse params
		if (_params.parse(query.c_str(), query.length(), err) != 0)
			return -1;

		//save query string
		_query = query;
	}

	////parse fragment////
	if (*pos == '#' && pos < end) {
		//skip fragment start flag
		start = ++pos;

		//save fragment
		_fragment = std::string(start, end - start);
	}

	return 0;
}
END_CUBE_HTTP_NS
