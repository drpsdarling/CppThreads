#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <algorithm>
using namespace std;

list<int> some_list;
mutex some_mutex;

// the accesses in these
// functions are mutually exclusive

void add_to_list(int new_value)
{
	lock_guard<mutex> guard(some_mutex);
	some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
	lock_guard<mutex> guard(some_mutex);
	return find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main()
{
	thread t1(add_to_list, 3);
	t1.detach();
	thread t2(list_contains, 4);
	t2.detach();
	return 0;
}