#include "cube\fd\path.h"
#include "cube\str\strip.h"
BEGIN_CUBE_PATH_NS
////////////////////////////////////////////////path class//////////////////////////////////////////////////

std::string make(const std::string &parent, const std::string &child) {
	const char* SEP = "\\";

	//trim parent's and child's left path seperators, add seperator between them
	return str::rstrip(str::rstrip(parent), SEP) + SEP + str::lstrip(str::rstrip(child), SEP);
}
END_CUBE_PATH_NS
