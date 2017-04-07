#include <iostream>
#include <thread>
using namespace std;

struct Data
{
	int i;
};

void update_data(Data& data)
{
	data.i = 77;
}

int main()
{
	Data data;
	data.i = 42;
	cout << "Old value i: " << data.i << endl;
	thread t(update_data, std::ref(data));
	t.join();
	cout << "New value i: " << data.i << endl;
	return 0;
}