#include "alloc.h"

LinearAllocator::LinearAllocator(size_t maxSize){
	maxSize_ = maxSize;
	offset = 0;
	base = new char[maxSize];
}

char* LinearAllocator::alloc(size_t size) {
	if (size <= 0 || (maxSize_ - offset) < size) {
		return nullptr;
	} else {
		offset += size;
		return base + offset - size;
	}
}

void LinearAllocator::reset() {
	offset = 0; 
}

LinearAllocator::~LinearAllocator(){
	delete[] base;
	base = nullptr; 
}
