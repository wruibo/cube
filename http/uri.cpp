#include "cube\http\uri.h"
#include "cube\str\url.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////param class/////////////////////////////////////////
std::string param::pack() const {
	std::string data("");

	data.append(str::escape(_name));
	data.append("=");
	data.append(str::escape(_value));

	return data;
}

int param::parse(const std::string &data, std::string *err) {
	size_t pos = data.find('=');
	if (pos == std::string::npos) {
		safe_assign<std::string>(err, str::format("parse param: %s, missing seperator.", data.c_str()));
		return -1;
	}

	_name = str::unescape(data.substr(0, pos));
	_value = str::unescape(data.substr(pos + 1));
	return 0;
}

//////////////////////////////////////////params class/////////////////////////////////////////
bool params::has(const std::string &name) const {
	return _params.find(name) != _params.end();
}

std::string params::get(const std::string &name) const {
	std::map<std::string, param>::const_iterator citer = _params.find(name);
	if (citer != _params.end())
		return citer->second.value();

	return "";
}

std::string params::get(const std::string &name, const char *default) const {
	std::map<std::string, param>::const_iterator citer = _params.find(name);
	if (citer != _params.end())
		return citer->second.value();

	return std::string(default);
}

std::vector<std::string> params::gets(const std::string &name) const {
	std::vector<std::string> values;

	std::map<std::string, param>::const_iterator citer = _params.lower_bound(name), citerend = _params.upper_bound(name);
	while (citer != citerend) {
		values.push_back(citer->second.value());
		citer++;
	}
	return values;
}

std::string params::pack() const {
	std::string data("");

	bool first = true;
	std::map<std::string, param>::const_iterator citer = _params.begin(), citerend = _params.end();
	while (citer != citerend) {
		if (first) {
			data.append(citer->second.pack());
			first = false;
		} else {
			data.append("&");
			data.append(citer->second.pack());
		}
		citer++;
	}

	return data;
}

int params::parse(const std::string &data, std::string *err) {
	//split data by param seperator
	std::vector<std::string> items;
	str::part(data.c_str(), "&", items);

	//parse key and value of each param
	for (std::size_t i = 0; i < items.size(); i++) {
		param p;
		if(p.parse(items[i], err) != 0)
			return -1;
		_params.insert(std::pair<std::string, param>(p.name(), p));
	}

	return 0;
}

//////////////////////////////////////////uri class/////////////////////////////////////////
std::string uri::pack() const {
	std::string data("");

	//add scheme
	if (!_scheme.empty()) {
		data.append(_scheme);
		data.append(":");
	}
	
	if (!_user.empty()) {
		data.append("//");
		data.append(_user);

		if (!_pwd.empty()) {
			data.append(":");
			data.append(_pwd);
		}

		data.append("@");

		if (!_host.empty()) {
			data.append(_host);

			if (!_port.empty()) {
				data.append(":");
				data.append(_port);
			}
		}
	} else {
		if (!_host.empty()) {
			data.append("//");
			data.append(_host);

			if (!_port.empty()) {
				data.append(":");
				data.append(_port);
			}
		}
	}

	if (!_path.empty()) {
		data.append("/");
		data.append(_path);
	}

	if (!_query.empty()) {
		data.append("?");
		data.append(_query);
	}

	if (!_fragment.empty()) {
		data.append("#");
		data.append(_fragment);
	}
	
	return data;
}

int uri::parse(const std::string &data, std::string *err) {
	size_t pos_right = std::string::npos;

	//find fragment start
	size_t pos_fragment_start = data.rfind('#', pos_right);
	if (pos_fragment_start != std::string::npos) {
		if (pos_right != std::string::npos) {
			_fragment = data.substr(pos_fragment_start, pos_right - pos_fragment_start - 1);
		} else {
			_fragment = data.substr(pos_fragment_start);
		}
		pos_right = pos_fragment_start;
	}

	//find query start
	size_t pos_query_start = data.rfind('?', pos_right);
	if (pos_query_start != std::string::npos) {
		if (pos_right != std::string::npos) {
			_query = data.substr(pos_query_start, pos_right - pos_query_start - 1);
		} else {
			_query = data.substr(pos_query_start);
		}
		pos_right = pos_query_start;
	}

	//find path start
	size_t pos_path_start = data.rfind('/', pos_right);
	if (pos_path_start != std::string::npos) {
		if (pos_right != std::string::npos) {
			_path = data.substr(pos_path_start, pos_right - pos_path_start - 1);
		} else {
			_path = data.substr(pos_path_start);
		}
		pos_right = pos_path_start;
	}

	//find authority start
	size_t pos_auth_start = data.rfind("//", pos_right);
	if (pos_auth_start != std::string::npos) {
		//find user end
		size_t pos_user_end = data.find('@', pos_auth_start);
		if (pos_user_end != std::string::npos && pos_user_end < pos_right) {
			//find password start
			size_t pos_pwd_start = data.find(':', pos_auth_start);
			if (pos_pwd_start != std::string::npos && pos_pwd_start < pos_user_end) {
				_user = data.substr(pos_auth_start + 2, pos_pwd_start - pos_auth_start - 2);
				_pwd = data.substr(pos_pwd_start + 1, pos_user_end - pos_pwd_start - 1);
			} else {
				_user = data.substr(pos_auth_start + 2, pos_user_end - pos_auth_start - 3);
			}

			//find port start
			size_t pos_port_start = data.find(':', pos_user_end);
			if (pos_port_start != std::string::npos && pos_port_start < pos_right) {
				_host = data.substr(pos_user_end + 1, pos_port_start - pos_user_end - 1);
				if (pos_right != std::string::npos)
					_port = data.substr(pos_port_start + 1, pos_right - pos_port_start - 2);
				else
					_port = data.substr(pos_port_start + 1, pos_right);
			} else {
				if (pos_right != std::string::npos)
					_host = data.substr(pos_auth_start + 2, pos_right - pos_auth_start - 3);
				else
					_host = data.substr(pos_auth_start + 2, pos_right);
			}

		} else {
			//find port start
			size_t pos_port_start = data.find(':', pos_auth_start);
			if (pos_port_start != std::string::npos && pos_port_start < pos_right) {
				_host = data.substr(pos_auth_start + 2, pos_port_start - pos_auth_start - 3);
				if(pos_right != std::string::npos)
					_port = data.substr(pos_port_start + 1, pos_right - pos_port_start - 2);
				else
					_port = data.substr(pos_port_start + 1, pos_right);
			} else {
				if(pos_right != std::string::npos)
					_host = data.substr(pos_auth_start + 2, pos_right - pos_auth_start - 3);
				else
					_host = data.substr(pos_auth_start + 2, pos_right);
			}
		}
		
		pos_right = pos_auth_start;
	}

	//find scheme end
	size_t pos_scheme_end = data.rfind(':', pos_right);
	if (pos_scheme_end != std::string::npos) {
		_scheme = data.substr(0, pos_scheme_end);
	}

	return 0;
}
END_CUBE_HTTP_NS
