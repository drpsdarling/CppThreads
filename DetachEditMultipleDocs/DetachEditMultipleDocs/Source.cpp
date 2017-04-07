#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void edit_document(string const& filename)
{
   cout << filename.c_str() << endl;
   string new_name("Second Document");
   thread t1([new_name](){ cout << new_name.c_str() << endl; });
   t1.detach();
   new_name = "Third Document";
   thread t2([new_name]() { cout << new_name.c_str() << endl; });
   t2.detach();
}

int main()
{
	edit_document("First Document");
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	return 0;
}