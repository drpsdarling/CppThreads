#include <iostream>
#include <thread>
#include <cstdio>
#include <chrono>
using namespace std;

void f(int i, string const& s)
{
	cout.flush();
	cout << "i: " << i << endl;
	cout << "s: " << s.c_str() << endl;
}

void not_oops(int some_param)
{
	char buffer[256];
	sprintf(buffer, "%i", some_param); 
	thread t(f, 3, string(buffer));    // Using std::string avoids dangling pointer
	t.detach();
}

int main()
{
	not_oops(42);
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}
