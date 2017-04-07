#include <iostream>
#include <thread>
void newThreadCallback(int * p)
{
	std::cout << "Inside Thread :  "" : p = " << *p << std::endl;
	std::chrono::milliseconds dura(10000);
	std::this_thread::sleep_for(dura);
	*p = 19;
}
// local variable in Thread 1 goes out of scope but
// Thread 2 is still trying to access it through it’s address
void startNewThread()
{
	int i = 10;
	std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
	std::thread t(newThreadCallback, &i);
	std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
	t.detach();
	std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
}
int main()
{
	startNewThread();
	std::chrono::milliseconds dura(25000);
	std::this_thread::sleep_for(dura);
	return 0;
}