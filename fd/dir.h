#pragma once
#include "cube\fd\def.h"
#include "cube\fd\exp.h"
BEGIN_CUBE_DIR_NS
//exceptions
typedef fd::cexception error;
/*
*	make directory by specified directory path
*@param path: directory path
*@return:
*	0 for success, otherwise <0
*/
int mkdir(const std::string &path);

/*
*	make directory by specified directory path, create parent directory if not exist
*@param path: directory path
*@return:
*	0 for success, otherwise <0
*/
int mkdirs(const std::string &path);
END_CUBE_DIR_NS
