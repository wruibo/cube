#include "cube\str\part.h"
#include "cube\str\format.h"
#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS
///////////////////////////////////////////////request class//////////////////////////////////////
int request::on_head_transfered(std::string *err) {
	//parse request line
	std::vector<std::string> items;
	str::part(_start_line.c_str(), " ", items, 3);
	if (items.size() != 3) {
		safe_assign<std::string>(err, str::format("query line: %s, invalid request", _start_line.c_str()));
		return -1;
	}

	//parse method
	_method = items[0];

	//parse request uri
	if (_uri.parse(items[1].c_str(), items[1].length(), err) != 0)
		return -1;

	//parse protocol & version
	if (_version.parse(items[2].c_str(), items[2].length(), err) != 0)
		return -1;

	return 0;
}

END_CUBE_HTTP_NS
