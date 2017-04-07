#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

template<typename Iterator, typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = accumulate(first, last, result);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = distance(first, last);
	if (!length)
		return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = thread::hardware_concurrency();
	unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads;
	vector<T> results(num_threads);
	vector<thread> threads(num_threads - 1);
	Iterator block_start = first;
	for (unsigned long i = 0;i<(num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		advance(block_end, block_size);
		threads[i] = thread(accumulate_block<Iterator, T>(), block_start, block_end, ref(results[i]));
		block_start = block_end;
	}
	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
	return accumulate(results.begin(), results.end(), init);
}

/*
You can’t return a value directly from a thread, you must pass in a reference to the relevant
entry in the results vector
Alternative ways of returning results from threads are addressed through the use of futures
*/

int main()
{
	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int parallel = parallel_accumulate(v.begin(), v.end(), 0);
	cout << "Sum(p): " << parallel << endl;
	int serial = accumulate(v.begin(), v.end(), 0);
	cout << "Sum(s): " << serial << endl;
	return 0;
}