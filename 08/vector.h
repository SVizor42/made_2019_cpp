#ifndef vector_h
#define vector_h

#include <stdexcept>
#include <limits>
#include <iterator>
#include <algorithm>

const size_t DEFAULT_CAPACITY = 8;

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;

	explicit Iterator(pointer ptr) : ptr_(ptr) {};
	Iterator(const Iterator& copied) = default;
	Iterator& operator=(const Iterator& copied) = default;
	Iterator(Iterator&& moved) = default;
	Iterator& operator=(Iterator&& moved) = default;
	~Iterator() = default;

	bool operator==(const Iterator<value_type>& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<value_type>& other) const {
		return !(*this == other);
	}

	bool operator<(const Iterator<value_type>& other) const {
		return ptr_ < other.ptr_;
	}

	bool operator>(const Iterator<value_type>& other) const {
		return (other < *this);
	}

	bool operator<=(const Iterator<value_type>& other) const {
		return (!(*this > other));
	}

	bool operator>=(const Iterator<value_type>& other) const {
		return (!(*this < other));		
	}

	reference operator*() const {
		return *ptr_;
	}

	pointer operator->() const {
		return ptr_;
	}

	Iterator& operator++() {
		++ptr_;
		return *this;
	}

	Iterator& operator--() {
		--ptr_;
		return *this;
	}
	
	Iterator operator++(int) {
		Iterator temp(*this);
		++ptr_;
		return temp;
	}

	Iterator operator--(int) {
		Iterator temp(*this);
		--ptr_;
		return temp;
	}

	Iterator& operator+=(size_type value) {
		ptr_ += value;
		return *this;
	}

	Iterator& operator-=(size_type value) {
		ptr_ -= value;
		return *this;
	}

	Iterator operator+(size_type value) const {
		return Iterator(ptr_ + value);
	}

	Iterator operator-(size_type value) const {
		return Iterator(ptr_ - value);
	}

private:
	pointer ptr_;
};

template <class T, class Alloc = std::allocator<T> >
class Vector {
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = Iterator<T>;
	using reverse_iterator = std::reverse_iterator<Iterator<T>>;
	using allocator_type = Alloc;

	Vector()
		: alloc_(Alloc())
		, size_(0)
		, capacity_(DEFAULT_CAPACITY)
		, data_(alloc_.allocate(capacity_))
	{}

	explicit Vector(size_type count) 
		: alloc_(Alloc())
		, size_(count)
		, capacity_(std::max(count, DEFAULT_CAPACITY))
		, data_(alloc_.allocate(capacity_))
	{}

	Vector(size_type count, const value_type& default_value)
		: alloc_(Alloc())
		, size_(count)
		, capacity_(std::max(count, DEFAULT_CAPACITY))
		, data_(alloc_.allocate(capacity_)) 
	{
		for (size_type i = 0; i < size_; i++) {
			alloc_.construct(data_ + i, default_value);
		}
	}

	Vector(std::initializer_list<value_type> init)
		: alloc_(Alloc())
		, size_(init.size())
		, capacity_(std::max(init.size(), DEFAULT_CAPACITY))
		, data_(alloc_.allocate(capacity_)) 
	{
		for (size_type i = 0; i < size_; i++) {
			alloc_.construct(data_ + i, *(init.begin() + i));
		}
	}

	Vector(const Vector& copied)
		: alloc_(Alloc())
		, size_(copied.size())
		, capacity_(copied.capacity_)
		, data_(alloc_.allocate(capacity_)) 	
	{
		for (size_type i = 0; i < size_; i++) {
			alloc_.construct(data_ + i, copied.data_[i]);
		}
	}

	Vector& operator=(const Vector& copied)	{
		if (this == &copied) {
			return *this;
		}

		if (data_) {
			clear();
			alloc_.deallocate(data_, capacity_);
			capacity_ = 0;
		}

		size_ = copied.size();
		capacity_ = copied.capacity_;
		data_ = alloc_.allocate(capacity_);
		for (size_type i = 0; i < size_; i++) {
			alloc_.construct(data_ + i, copied.data_[i]);
		}

		return *this;
	}

	Vector(Vector&& moved) 
		: alloc_(Alloc())
		, size_(moved.size())
		, capacity_(moved.capacity_)
		, data_(moved.data_) 	
	{
		moved.data_ = nullptr;
		moved.size_ = 0;
		moved.capacity_ = 0;
	}

	Vector& operator=(Vector&& moved) {
		if (this == &moved) {
			return *this;
		}

		if (data_) {
			clear();
			alloc_.deallocate(data_, capacity_);
			capacity_ = 0;
		}

		size_ = moved.size();
		capacity_ = moved.capacity_;
		data_ = moved.data_;
		moved.data_ = nullptr;
		moved.size_ = 0;
		moved.capacity_ = 0;

		return *this;				
	}

	~Vector() {
		clear();
		alloc_.deallocate(data_, capacity_);
		data_ = nullptr;
		capacity_ = 0;
	}

	reference operator[](size_type index) {
		if (index >= size_) {
			throw std::out_of_range("Vector index is out of range!");
		}

		return data_[index];
	}

	const_reference operator[](size_type index) const {
		if (index >= size_) {
			throw std::out_of_range("Vector index is out of range!");
		}

		return data_[index];
	}

	void push_back(value_type&& value) {
		if (size_ == capacity_) {
			reserve(2 * capacity_);
		}
		
		alloc_.construct(data_ + size_, std::forward<value_type>(value));
		size_++;
	}

	void push_back(const_reference value) {
		if (size_ == capacity_) {
			reserve(2 * capacity_);
		}

		alloc_.construct(data_ + size_, value);
		size_++;
	}

	void pop_back() {
		if (!empty()) {
			alloc_.destroy(data_ + size_);
			size_--;
		}
	}

	bool empty() const noexcept {
		return (size_ == 0);
	}

	size_type size() const noexcept {
		return size_;
	}
	
	size_type capacity() const noexcept {
		return capacity_;
	}

	void clear() noexcept {
		for (size_type i = 0; i < size_; i++) {
			alloc_.destroy(data_ + i);
		}
		size_ = 0;		
	}

	iterator begin() noexcept {
		return iterator(data_);
	};

	iterator end() noexcept {
		return iterator(data_ + size_);		
	}

	reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	template<class... Args>
	void resize(size_type new_size, Args... args) {
		if (new_size != capacity_) {
			reserve(new_size);

			for (size_type i = size_; i < new_size; i++) {
				alloc_.construct(data_ + i, args...);
			}
			for (size_type i = new_size; i < size_; i++) {
				alloc_.destroy(data_ + i);
			}

			size_ = new_size;			
		}
	}

	void reserve(size_type new_capacity) {
		if (new_capacity > capacity_) {
			pointer new_data = alloc_.allocate(new_capacity);
			
			for (size_type i = 0; i < size_; i++) {
				alloc_.construct(new_data + i, *(data_ + i));
				alloc_.destroy(data_ + i);
			}
			alloc_.deallocate(data_, capacity_);

			capacity_ = new_capacity;
			data_ = new_data;
		}
	}

private:
	Alloc alloc_;
	size_type size_;
	size_type capacity_;	
	pointer data_;
};

#endif
