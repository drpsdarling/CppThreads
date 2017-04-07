#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

void do_work(unsigned id)
{
	cout << "do_work(" << id << ")" << endl;
}
void f()
{
	std::vector<std::thread> threads;
	for (unsigned i = 0;i<4;++i)
	{
		threads.push_back(std::thread(do_work, i));
	}
	for_each(threads.begin(), threads.end(), mem_fn(&std::thread::join));
}

int main()
{
	f();
	return 0;
}
/*
do_work(do_work(1)do_work(2)0
)
do_work(3)
Press any key to continue . . .
*/