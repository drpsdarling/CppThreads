// packaged_task example
// A packaged_task wraps a callable element and allows its result to be retrieved asynchronously.
// It is similar to std::function, but transferring its result automatically to a future object.
// std::function: Function wrapper
// Class that can wrap any kind of callable element(such as functions and function objects)
// into a copyable object, and whose type depends solely on its call signature(and not on the callable element type itself)
//
#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for

// count down taking a second for each value:
int countdown(int from, int to) {
	for (int i = from; i != to; --i) {
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Lift off!\n";
	return from - to;
}

int main()
{
	std::packaged_task<int(int, int)> tsk(countdown);   // set up packaged_task
	std::future<int> ret = tsk.get_future();            // get future

	std::thread th(std::move(tsk), 10, 0);   // spawn thread to count down from 10 to 0

											 // ...

	int value = ret.get();                  // wait for the task to finish and get result

	std::cout << "The countdown lasted for " << value << " seconds.\n";

	th.join();

	return 0;
}