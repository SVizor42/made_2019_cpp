#include <iostream>
#include <assert.h>
#include "alloc.h"

int main(int argc, const char* argv[])
{
	LinearAllocator allocator(10);

	char* ptr1 = allocator.alloc(7);
	assert(ptr1 != nullptr);

	allocator.reset();
	ptr1 = allocator.alloc(7);
	char* ptr2 = allocator.alloc(3);
	assert(ptr2 != nullptr);

	ptr1 = allocator.alloc(5);
	assert(ptr1 == nullptr);

	allocator.reset();
 	ptr2 = allocator.alloc(5);
	assert(ptr2 != nullptr);
	
	std::cout << "All tests were passed!" << std::endl;

    return 0;
}
