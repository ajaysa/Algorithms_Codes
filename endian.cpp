// find endianess of the system
#include <iostream>

union checkEndian
{
	int a;
	bool bl;
}cEndian;

int main()
{
	cEndian.a = 1;

	if (cEndian.bl)
		std::cout<<"Architecture is little endian\n";
	else
		std::cout<<"Architecture is big endian\n";

	return 0;
}
