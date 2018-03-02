#pragma once
#include <vector>
#include <algorithm>
#include "cube\http\pair.h"
BEGIN_CUBE_HTTP_NS
//parameter
class param : public pair {
public:
	param() {}
	param(const std::string &name, const std::string &value) : pair(name, value) {}
	virtual ~param() {}

public:
	inline bool operator==(const std::string &name) const {
		return param::name() == name;
	}
};

//parameters
class params {
public:
	params() {}
	virtual ~params() {}

	bool has(const std::string &name) const {
		return std::find(_params.begin(), _params.end(), name) != _params.end();
	}

	void add(const std::string &name, const std::string &value) { 
		_params.push_back(param(name, value));
	}

	std::string get(const std::string &name) const {
		return get(name, "");
	}

	std::string get(const std::string &name, const char *default) const {
		std::vector<param>::const_iterator citer = std::find(_params.begin(), _params.end(), name);
		if (citer != _params.end())
			return (*citer).value();
		return default;
	}

	void gets(const std::string &name, std::vector<std::string> &values) const {
		for (size_t i = 0; i < _params.size(); i++) {
			if (_params[i].name() == name) {
				values.push_back(_params[i].value());
			}
		}
	}

private:
	std::vector<param> _params;
};

END_CUBE_HTTP_NS
