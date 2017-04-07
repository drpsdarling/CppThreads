#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class X
{
public:
	void do_lengthy_work()
	{
		cout << "X.do_lengthly_work()" << endl;
	};
};

int main()
{
	X my_x;
	thread t(&X::do_lengthy_work, &my_x);
	t.join();
	return 0;
}


