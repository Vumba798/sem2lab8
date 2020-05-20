// sem2_lab8.cpp: определяет точку входа для приложения.
//
#include "sem2_lab8.h"

using std::endl;
using std::cin;
using std::cout;


std::vector<int> maxNum;

std::mutex m;

void findMax(std::vector<int>::iterator it1, std::vector<int>::iterator it2) {

	int value = *std::max_element(it1, it2);
	maxNum.push_back(value);
	m.lock();
	cout << endl;
	cout << "Max element: " << value << endl;
	cout << "End of ";
	cout << std::this_thread::get_id();
	cout << " thread" << endl;
	m.unlock();
}


int main()
{
	cout << "Input amount of elements: ";
	size_t amount;
	cin >> amount;

	std::vector<int> vec;
	for (size_t i = 0; i < amount; ++i) {
		vec.push_back(std::rand());
	}
	cout << endl << endl;


	int size = vec.size() / 3;
	auto it = vec.begin();
	size_t index1 = 0;
	size_t index2 = size;
	std::thread* threads[3];


	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	for (size_t i = 0; i < 3; ++i) {
		if (index2 > vec.size()) {
			index2 = vec.size();
		}
		threads[i] = new std::thread(findMax, vec.begin() + index1, vec.begin() + index2);
		index1 += size;
		index2 += size;
	}
	
	for (size_t i = 0; i < 3; ++i) {
		threads[i]->join();
	}



	std::chrono::system_clock::time_point finish = std::chrono::system_clock::now();
	std::chrono::duration<double> def = finish - start;
	cout << "Time used : " << def.count() << endl;


	int max = *std::max_element(maxNum.begin(), maxNum.end());
	cout << "MAX = " << max << endl;




	return 0;
}
