// find number of 1's in binary representation of a number
#include <iostream>
#include <string>

int findOnes(int a);

int main()
{
	int a;

	std::cout<<"Enter number\n";
	std::cin>>a;

	std::string str;
	int i;
	for(i=0; i<32; i++)
	{
		if( a & (1<<i) )
			str = "1" + str;
		else
			str = "0" + str;
	}
	std::cout<<a<<" = "<<str<<"\n";
	std::cout<<findOnes(a)<<"\n";
	return 0;
}

int findOnes(int a)
{
	int count = 0;

	while( a & (a-1) )
	{
		count++;
		a = a & (a-1);
	}

	if (a)
		count++;

	return count;
}
