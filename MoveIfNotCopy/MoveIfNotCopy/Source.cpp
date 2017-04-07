#include <iostream>
#include <thread>
using namespace std;

class big_object
{
public:
	void prepare_data(int i_)
	{
		i = 2*i_;
	}
	int getI()
	{
		return i;
	}
private:
	int i;
};

void process_big_object(unique_ptr<big_object> pbo)
{
	cout << "process_big_object i: " << pbo->getI() << endl;
}

int main()
{
	unique_ptr<big_object> p(new big_object);
	p->prepare_data(21);
	std::thread t(process_big_object, std::move(p));
	t.join();
	return 0;
}


