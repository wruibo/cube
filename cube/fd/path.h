#pragma once
#include "cube\fd\def.h"
BEGIN_CUBE_PATH_NS
/*
*	make full path by parent and its child path
*@param parent: in, parent path
*@param child: in, child name/path
*@return:
*	full path combined by parent and child
*/
std::string make(const std::string &parent, const std::string &child);
END_CUBE_PATH_NS
