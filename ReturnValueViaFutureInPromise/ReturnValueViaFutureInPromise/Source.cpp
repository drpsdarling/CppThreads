#include <iostream>
#include <thread>
#include <future>

void initiazer(std::promise<int> * promObj)
{
	std::cout << "Inside Thread" << std::endl;
	promObj->set_value(35);
	std::cout << "Thread has set the promObj value " << std::endl;
}

int main()
{
	std::promise<int> promiseObj;
	std::cout << "Get future from promise obj" << std::endl;
	std::future<int> futureObj = promiseObj.get_future();
	std::cout << "Pass promise obj into thread" << std::endl;
	std::thread th(initiazer, &promiseObj);
	std::cout << "get value from the future obj: " << futureObj.get() << std::endl;
	th.join();
	return 0;
}
/*
Get future from promise obj
Pass promise obj into thread
Inside Thread
Thread has set the promObj value
get value from the future obj: 35
Press any key to continue . . .
*/