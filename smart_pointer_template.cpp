#include <iostream>
#include <string.h>

using namespace std;

class Person
{
	string name;
	int age;
	public:
		Person(string na, int ag)
		{
			name = na;
			age  = ag;
		}
		void print()
		{
			cout<<"Name = "<<name<<"\n";
			cout<<"Age = "<<age<<"\n";
		}
};

template <typename T> class SmartPntr
{
	T *ptr;
	public:
		SmartPntr(T *p)
		{
			ptr = p;
		}
		~SmartPntr()
		{
			cout<<"destroy Pointer\n";
			if ( ptr )
				delete ptr;
		}
		T& operator* ()
		{
			return *ptr;
		}
		T* operator-> ()
		{
			return ptr;
		}
};


int main()
{
	SmartPntr<Person> point(new Person("Ajay", 26));

	point->print();
	(*point).print();
	return 0;
}
