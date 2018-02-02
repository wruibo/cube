#pragma once
#include "cube\http\def.h"
#include <map>
#include <vector>
BEGIN_CUBE_HTTP_NS
//parameters structure
class params {
public:
	params() {}
	virtual ~params() {}

	//pack/parse params with data string
	std::string pack() const;
	int parse(const char *data, int sz, std::string *err = 0);

	/*
	*	get param value by specfied key
	*@param key: in, param key
	*@param val: in/out, value of specified key
	*@return:
	*	value of param
	*/
	std::vector<std::string> get(const std::string &key) const;
	std::string get(const std::string &key, const char *default) const;
private:
	//params
	std::map<std::string, std::vector<std::string>> _params;
};
END_CUBE_HTTP_NS

