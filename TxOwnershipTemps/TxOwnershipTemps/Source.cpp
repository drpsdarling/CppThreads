#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void some_function()
{
	cout << "some_function()" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
void some_other_function()
{
	cout << "some_other_function()" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

int main()
{
	// only one instance of function calls
	std::thread t1(some_function);
	cout << "t1->t2" << endl;
	std::thread t2 = std::move(t1);
	cout << "temp->t1" << endl;
	t1 = std::thread(some_other_function); // moving from temps (rvalues) is automatic/implicit
	std::thread t3;
	cout << "t2->t3" << endl;
	t3 = std::move(t2);
	cout << "t3->t1" << endl;
	t1 = std::move(t3); // t1 already had an associated thread - std::terminate() is called
	cout << "return 0" << endl;
	return 0;
}
/*
some_function()
t1->t2
temp->t1
some_other_function()
t2->t3
t3->t1
*/