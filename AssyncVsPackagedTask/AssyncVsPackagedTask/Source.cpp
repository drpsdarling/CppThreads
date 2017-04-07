#include <iostream>
#include <thread>
#include <chrono>
#include <future>

int delay = 5;

//! sleeps for five seconds and returns 77
auto sleep = []() {
	std::this_thread::sleep_for(std::chrono::seconds(delay));
	return 77;
};

int main()
{
	std::packaged_task<int()> task(sleep);

	auto ft = task.get_future();
	task(); // invoke the function

			// You have to wait until task returns. Since task calls sleep
			// you will have to wait at least 3 seconds.
	std::cout << "You can see this after 5 seconds" << std::endl ;

	// However, f.get() will be available, since task has already finished.
	std::cout << ft.get() << std::endl;

	auto fa = std::async(std::launch::async, sleep);
	std::cout << "You can see this immediately!" << std::endl;

	// However, the value of the future will be available after sleep has finished
	// so f.get() can block up to 5 seconds.
	std::cout << std::endl;
	std::cout << fa.get() << "This will be shown after five seconds!" << std::endl ;

	return 0;
}
