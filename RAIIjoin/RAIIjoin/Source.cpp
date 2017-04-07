#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
		t(t_)
	{}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

void do_something(int i)
{
	cout << "do_something(1): " << i << endl;
	cout.flush();
	std::this_thread::sleep_for(std::chrono::milliseconds(30000));
	cout << "do_something(2): " << i << endl;
}

void do_something_in_current_thread()
{
	cout << "do_something_in_current_thread"<< endl;
	cout << "throw an exception" << endl;
	throw runtime_error("Exception in do_something_in_current_thread()");
}

struct func
{
	int& i;
	func(int& i_) :i(i_) {}
	void operator()()
	{
		do_something(i);
	}
};

int main()
{
	int some_local_state = 42;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
	return 0;
}