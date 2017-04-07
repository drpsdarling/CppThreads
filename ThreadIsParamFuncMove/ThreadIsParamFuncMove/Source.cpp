#include <iostream>
#include <thread>
#include <exception>
using namespace std;

void do_something_in_current_thread()
{
	cout << "do_something_in_current_thread()" << endl;
}

void do_something(int i)
{
	cout << "do_something(" << i << ")" << endl;
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

class scoped_thread
{
	thread t;
public:
	// move support of std::thread - actually take ownership of the thread
	explicit scoped_thread(thread t_) : t(std::move(t_))
	{
		if (!t.joinable()) throw logic_error("No thread");
	}
	~scoped_thread()
	{
		cout << "dtor() calls join" << endl;
		t.join();
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};

int main()
{
	int some_local_state = 22;
	scoped_thread t({ thread(func(some_local_state)) }); // thread is passed in directly to the scoped_thread
	do_something_in_current_thread();
	return 0;
}