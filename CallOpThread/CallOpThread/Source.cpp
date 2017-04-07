#include <iostream>
#include <thread>
using namespace std;

void do_something()
{
	cout << "do_something()" << endl;
}

class background_task
{
public:
	void operator()() const
	{
		do_something();
	}
};

int main()
{
	//background_task f;
	//std::thread my_thread(f);
	std::thread my_thread{ background_task() };
	return 0;
}