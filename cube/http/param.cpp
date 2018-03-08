#include "cube\log\log.h"
#include "cube\str\part.h"
#include "cube\str\escape.h"
#include "cube\http\param.h"
BEGIN_CUBE_HTTP_NS
std::string param::pack() const {
	std::string res("");
	res.append(cube::str::escape(name()));
	res.append("=");
	res.append(cube::str::escape(value()));
	return res;
}

int param::parse(const std::string &str) {
	std::size_t sep = str.find('=');
	if (sep != std::string::npos) {
		name(cube::str::unescape(str.substr(0, sep)));
		value(cube::str::unescape(str.substr(sep + 1)));
		return 0;
	} else {
		log::error("params: %s, invalid param", str.c_str());
		return -1;
	}
}

std::string params::pack() const {
	std::string res("");

	bool first = true;
	std::vector<param>::const_iterator iter = _params.begin(), iterend = _params.end();
	while (iter != iterend) {
		if (first) {
			res.append((*iter).pack());
			first = false;
		} else {
			res.append("&");
			res.append((*iter).pack());
		}
	}

	return res;
}

int params::parse(const std::string &str) {
	//split data by param seperator
	std::vector<std::string> items;
	cube::str::part(str.c_str(), "&", items);

	//parse key and value of each param
	for (std::size_t i = 0; i < items.size(); i++) {
		std::size_t sep = items[i].find('=');
		if (sep != std::string::npos) {
			std::string key = str::unescape(items[i].substr(0, sep));
			std::string val = str::unescape(items[i].substr(sep + 1));
			_params[key].push_back(val);
		} else {
			cube::safe_assign<std::string>(err, str::format("params: %s, invalid param", items[i].c_str()));
			return -1;
		}
	}

	return 0;
}
END_CUBE_HTTP_NS
