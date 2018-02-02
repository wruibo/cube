#include "cube\http\param.h"
#include "cube\str\url.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////params class/////////////////////////////////////////
std::string params::pack() const {
	//data buffer
	char data[BUFSZ] = { 0 };

	//output data
	int dsz = 0;
	bool first = true;
	std::map<std::string, std::vector<std::string>>::const_iterator iter = _params.begin(), iterend = _params.end();
	while (iter != iterend) {
		for (size_t i = 0; i < iter->second.size(); i++) {
			if (first) {
				dsz += snprintf(data + dsz, BUFSZ - dsz, "%s=%s", str::escape(iter->first).c_str(), str::escape(iter->second[i]).c_str());
				first = false;
			} else {
				dsz += snprintf(data + dsz, BUFSZ - dsz, "&%s=%s", str::escape(iter->first).c_str(), str::escape(iter->second[i]).c_str());
			}
		}
	}

	return std::string(data, dsz);
}

int params::parse(const char *data, int sz, std::string *err) {
	//split data by param seperator
	std::vector<std::string> items;
	str::part(data, sz, "&", items);

	//parse key and value of each param
	for (std::size_t i = 0; i < items.size(); i++) {
		std::size_t sep = items[i].find('=');
		if (sep != std::string::npos) {
			std::string key = str::unescape(items[i].substr(0, sep));
			std::string val = str::unescape(items[i].substr(sep + 1));
			_params[key].push_back(val);
		} else {
			safe_assign<std::string>(err, str::format("params: %s, invalid param", items[i].c_str()));
			return -1;
		}
	}

	return 0;
}

std::vector<std::string> params::get(const std::string &key) const {
	std::map<std::string, std::vector<std::string>>::const_iterator citer = _params.find(key);
	if (citer == _params.end())
		return std::vector<std::string>();

	return citer->second;
}

std::string params::get(const std::string &key, const char *default) const {
	std::map<std::string, std::vector<std::string>>::const_iterator citer = _params.find(key);
	if (citer == _params.end() || citer->second.empty())
		return default;

	return citer->second[0];
}
END_CUBE_HTTP_NS
