#ifndef alloc_h
#define alloc_h

#include <cstdio>

class LinearAllocator
{
public:
	LinearAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~LinearAllocator();

private:
	char* base;
	size_t maxSize_;
	size_t offset;
};

#endif
