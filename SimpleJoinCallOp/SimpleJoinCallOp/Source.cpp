#include <iostream>
#include <thread>
using namespace std;

void do_something(int i)
{
	cout << "do_something("<<i<<")" << endl;
}
class func
{
public:
	int& i;
	func(int& i_) :i(i_) {}
	void operator()()
	{
		for (unsigned j = 0;j<3;++j)
		{
			do_something(i);
		}
	}
};

int main()
{
	cout << "main(1)" << endl;
	int some_local_state = 42;
	func my_func(some_local_state);
	cout << "main(2)" << endl;
	std::thread my_thread(my_func);
	cout << "main(3)" << endl;
	my_thread.join();
	cout << "main(4)" << endl;
	return 0;
}
/*
main(1)
main(2)
do_something(42)
main(3)
do_something(42)
do_something(42)
main(4)
Press any key to continue . . .
*/