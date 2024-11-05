#pragma once
#include "../iterator/iterator.hpp"
#include <utility>
#include <algorithm>
namespace Constants
{
	//constexpr is calculated only in COMPILE_TIME
	constexpr unsigned GROWTH_FACTOR = 2;
}

//It uses the default allocator, Could be done with template allocator.
template <class T>
class vector
{
	public:
		using iterator = vector_iterator<T>;
		using const_iterator = const_vector_iterator<T>;
		using reverse_iterator = reverse_vector_iterator<T>;

		vector() = default;

		//'explicit' prevents unexpected and implicit conversion of types when calling constructors
		explicit vector(size_t count);
		vector(size_t count, const T& initial);


	private:
		T* _data = nullptr;
		size_t size = 0;
		size_t capacity = 0;
};

// Constructs the container with count copies of elements with default value.
// Why dont we call `new` here?
// When you choose a memory managment strategy
// to stick with it for concistency.

template <class T>
vector<T>::vector(size_t count)

//operator new - allocating ONLY memory (without calling the object constructors)
//			   - does not initiallize(as 'new' does)
//			   - we want to manage the initiallization by ourselves
//static_cast - converting the memory block(void* type) to (T* type)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// default construct all elements
	for (size_t i = 0; i < count; i++)
		// placement new - we give a specific address in memory, where we want to put the object
		//				 - syntax: new (address) type(constructor parameters)
		new (&_data[i]) T();
//WHY??
	// 1. Memory control 
	//		- with 'operator new' we allocate memory without constructors colling
	//		- we gain memory and initialization control
	// 2. Manual initialization
	//		- we can initialize parts of the objects, or to cancle it
	// 3. Better productivity
	//		- operator new + placement new = operations could be spared
}

template <class T>
vector<T>::vector(size_t count, const T& initial)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// construct all elements copying initial
	for (size_t i = 0; i < count; i++)
		new (&_data[i]) T(initial);
}

template <class T>
vector<T>::vector(const vector& other)
{
	copy(other);
}

template <class T>
vector<T>& vector<T>::operator=(const vector& other)
{
	if (this != other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <class T>
vector<T>& vector(vector&& other)
{
	move(std::move(other));
}

template <class T>
vector<T>& vector<T>::operator=(vector&& other)
{
	if (this != other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}

template <class T>
vector<T>::~vector()
{
	free();
}

template <class T>
void vector<T>::copy(const vector<T>& other)
{
	//allocate enough memory
	_data = static_cast<T*>(operator new(other.capacity() * sizeof(T)));

	//copy construct elements
	for (size_t i = 0; i < other.size(); i++)
		new (&_data[i]) T(other[i]);

	_size = other.size;
	_capacity = other.capacity();
}

template <class T>
void vector<T>::free()
{
	//call destructor on constructed elements
	for (size_t i = 0; i < size(); i++)
		_data[i].~T();

	//deallocate memory (which is allocated with operator new)
	operator delete(_data, capacity() * sizeof(T));
}

template <class T>
void vector<T>::move(vector<T>&& other)
{
	_size = other.size();
	_capacity = other.capacity();
	_data = other._data;

	ohter._data = nullptr;
	other._size = other._capacity = 0;
}

template <class T>
size_t vector<T>::size() const
{
	return _size;
}

template <class T>
size_t vector<T>::capacity() const
{
	return _capacity;
}

template class <T>
size_t vector<T>::calculate_capacity() const
{
	if (capacity() == 0)
		return 1;
	return capacity() * Constants::GROWTH_FACTOR;
}

// Resizes the container to contain `n` elements, does nothing if `n` == size(). 
// If the current size is greater than `n`, the container is reduced to its first count elements. 
// If the current size is less than `n`, then additional default-inserted elements are appended.
template <class T>
void vector<T>::resize(size_t n)
{
	if (n < size())
	{
		//call destructor on constructed elements
		for (size_t i = n; i < size(); i++)
			(_data + i)->~T();

		_size = n;
	}
	else if (n > size())
	{
		if (n <= capacity())
		{
			//default construct elements in range [size(), n)
			for (size_t i = size(); i < n; i++)
				new (&_data[i]) T();

			_size = n;
		}
		else
		{
			T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

			for (size_t i = 0; i < size(); i++)
				//NOTE: we use std::move, not vector::move to convert elements from data to r-values
				new (&new_data[i]) T(std::move(_data[i]));

			for (size_t i = size(); i < n; i++)
				new (&new_data[i]) T();

			operator delete(_data, capacity() * sizeof(T));

			_data = new_data;
			_capacity = n;
			_size = n;
		}
	}
}