#include <cassert>
#include <iostream>
#include "vector.h"

template<class T>
void print_vector(Vector<T>& v) {
	std::cout << "current_size = " << v.size() << std::endl;
	std::cout << "items:" << std::endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

int main() {
	
	std::cout << "Vector v:" << std::endl;
	Vector<size_t> v(5, 42);
	print_vector(v);	
	
	std::cout << "Vector v2 (copy of v):" << std::endl;
	Vector<size_t> v2 = v;
	print_vector(v2);
	
	std::cout << "Vector v3 from init list:" << std::endl;
	Vector<int> v3 = {-3, 6, 0, 5, 5};
	print_vector(v3);

	
	std::cout << "Clear v and push items again:" << std::endl;
	v.clear();
	for (size_t i = 1; i < 10; i++) {
		v.push_back(i);
	}
	print_vector(v);

	std::cout << "=====Resize test=====" << std::endl;	
	std::cout << "Making vector v resize:" << std::endl;
	v.resize(5);
	std::cout << "current_size = " << v.size() << std::endl;

	v.resize(8, 100);
	std::cout << "current_size = " << v.size() << std::endl;
	
	v.resize(12);
	std::cout << "current_size = " << v.size() << std::endl;

	std::cout << "Extract 2 items from v:" << std::endl;    
	v.pop_back();
	v.pop_back();
	print_vector(v);

	std::cout << "=====Reserve test=====" << std::endl;
	Vector<int>::size_type sz;
	Vector<int> foo;
	sz = foo.capacity();
	std::cout << "Making foo grow:" << std::endl;
	for (size_t i = 0; i < 100; i++) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << std::endl;;
		}
	}

	Vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);
	std::cout << "Making bar grow:" << std::endl;
	for (size_t i = 0; i < 100; i++) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << std::endl;;
		}
	}

	return 0;
}
