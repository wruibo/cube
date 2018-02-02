#include "cube\fd\path.h"
#include "cube\fd\strip.h"
BEGIN_CUBE_PATH_NS
////////////////////////////////////////////////path class//////////////////////////////////////////////////

std::string make(const std::string &parent, const std::string &child) {
	const char* SEP = "\\";

	//trim parent's and child's left path seperators, add seperator between them
	return fd::rstrip(fd::rstrip(parent), SEP) + SEP + fd::lstrip(fd::rstrip(child), SEP);
}
END_CUBE_PATH_NS
