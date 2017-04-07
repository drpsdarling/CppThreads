#include <iostream>
#include <thread>
using namespace std;
void some_function()
{
	cout << "some_function()" << endl;
}
void some_other_function(int i)
{
	int temp = i;
	cout << "some_other_function(int)" << endl;
}

std::thread f()
{
	return std::thread(some_function);
}


std::thread g()
{
	std::thread t(some_other_function, 42);
	return t;
}

int main()
{
	cout << "call f()" << endl;
	thread t1 = f();
	cout << "call g()" << endl;
	thread t2 = g();
	cout << "t1.join()" << endl;
	t1.join();
	cout << "t2.join()" << endl;
	t2.join();
	cout << "return 0" << endl;
	return 0;
}
/*
call f()
some_function()call g()

some_other_function(int)
t1.join()
t2.join()
return 0
Press any key to continue . . .
*/