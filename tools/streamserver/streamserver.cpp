#include <iostream>
#include <cube/string/case.h>

using namespace std;

int main(int argc, char *argv[])
{
	cout<<"to lower case of ABC:"<<cube::string::to_lower("ABC").c_str()<<endl;
	return 0;
}