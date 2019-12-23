#include <cassert>
#include <iostream>
#include "threadpool.h"

struct A {
	void Print() const {
		std::cout << "Test A" << std::endl;
	}
};

void foo(const A& a) {
	a.Print();
}

int main()
{

	ThreadPool pool(8);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { 
		std::cout << 1 << std::endl;        
		return 1; 
	});
	assert(task2.get() == 1);

	auto sum = ([](int a, int b) { return a + b; });
	auto task3 = pool.exec(sum, 3, 5);
	assert(task3.get() == 8);

	return 0;
}
