#include "test_hex.h"
#include <iostream>
#include <string.h>

void test_hex()
{
	const char * str = "0123456789abcdefABCDEF";
	std::cout<<"input string: "<<str<<std::endl;

	std::string hexStr = cube::string::byte2hexstr(str, strlen(str)).c_str();
	std::cout<<"convert to hex string: "<<hexStr.c_str()<<std::endl;

	std::string originalStr = cube::string::hexstr2byte(hexStr.c_str(), hexStr.length());
	std::cout<<"convert to original string: "<<originalStr.c_str()<<std::endl;

	std::string originalStr1 = cube::string::hexstr2byte(hexStr.c_str(), hexStr.length()-1);
	std::cout<<"convert to original string with dump last character: "<<originalStr1.c_str()<<std::endl;

}
