#include "cube\str\part.h"
#include "cube\str\case.h"
#include "cube\str\strip.h"
#include "cube\str\format.h"
#include "cube\http\parser.h"

BEGIN_CUBE_HTTP_NS
int parser::parse_header(const std::string &str, header *header, std::string *err = 0) {
	//check data
	std::vector<std::string> item;
	str::part(str.c_str(), ":", item, 2);
	if (item.size() != 2) {
		safe_assign<std::string>(err, str::format("header: %s invalid header", str.c_str()));
		return -1;
	}

	//parse header
	header->name(item[0]);
	header->value(item[1]);

	return 0;
}
END_CUBE_HTTP_NS
