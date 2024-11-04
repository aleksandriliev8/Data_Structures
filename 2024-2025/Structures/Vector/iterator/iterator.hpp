#pragma once
#include <stddef.h>

template<class T>
class const_vector_iterator
{
	private:
		T* memPointer;
	public:
		const_vector_iterator(T* passedVal) : memPointer {}
		const_vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {}

		const_vector_iterator<T> operator+(int off) const
		{
			return { memPointer + off };
		}

		//off - offset
		const_vector_iterator<T> operator-(int off) const
		{
			return { mempointer - off };
		}

		//operator - for calculating the distance between two iterators
		int operator-(const_vector_iterator<T> other) const
		{
			return memPointer - other.memPointer;
		}

		//access operator (returns pointer to the object)
		const T& operator->() const noexcept
		{
			return memPointer;
		}
		//constant reference to the object(pointed by memPointer)
		const T& operator*() const noexcept
		{
			return *(memPointer);
		}

		//checks if (this) and (it) are pointing to the same memory
		bool operator==(const const_vector_iterator& it) const
		{
			return (memPointer == it.memPointer);
		}

		bool operator!=(const const_vector_iterator& it) const
		{
			return !(memPointer == it.memPointer);
		}
};

template<class T>
class vector_iterator
{
	private:
		T* memPointer;

	public:
		vector_iterator(T* passedVal) : memPointer{ passedVal } {};
		vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {};

		//prefix operator
		vector_iterator<T>& operator++()
		{
			memPointer++;
			return *this;
		}

		//postfix operator

		//(int) is for helping the compilator make the difference between
		// the prefix and postfix operator
		// example++ - it will search the operator++ version with one (fake/fictive) parameter
		vector_iterator<T> operator++(int)
		{
			vector_iterator it = *this;
			++(*this);
			return it;
		}

		vector_iterator<T>& operator--()
		{
			memPointer--;
			return *this;
		}

		vector_iterator<T> operator--(int)
		{
			vector_iterator it = *this;
			--(*this);
			return it;
		}

		operator const_vector_iterator<T>() const
		{
			return const_vector_iterator<T>(memPointer);
		}

		vector_iterator<T> operator+(int off) const
		{
			return { memPointer + off };
		}

		vector_iterator<T> operator-(int off) const
		{
			return { memPointer - off };
		}

		T* operator->()
		{
			return memPointer;
		}

		const T* operator->() const
		{
			return memPointer;
		}

		T& operator*()
		{
			return *(memPointer);
		}

		bool operator==(const vector_iterator<T>& it) const
		{
			return (memPointer == it.memPointer);
		}

		bool operator!=(const vector_iterator<T>& it) const
		{
			return !(memPointer == it.memPointer);
		}
};

template<class T>
class reverse_vector_iterator
{
	public:
		reverse_vector_iterator(T* passedVal) : memPointer{ passedVal } {};
		reverse_vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {};

		reverse_vector_iterator<T>& operator++()
		{
			memPointer--;
			return *this;
		}

		reverse_vector_iterator<T> operator++(int)
		{
			reverse_vector_iterator it = memPointer;
			++(*this);
			return it;
		}

		reverse_vector_iterator<T>& operator--()
		{
			memPointer++;
			return *this;
		}

		reverse_vector_iterator<T> operator--(int)
		{
			reverse_vector_iterator it = memPointer;
			--(*this);
			return it;
		}

		reverse_vector_iterator<T> operator+(int off) const
		{
			return { memPointer + off };
		}

		reverse_vector_iterator<T> operator-(int off) const
		{
			return { memPointer - off };
		}

		T* operator->()
		{
			return memPointer;
		}

		const T* operator->() const
		{
			return memPointer;
		}

		T& operator*()
		{
			return *(memPointer);
		}

		bool operator==(const reverse_vector_iterator<T>& it) const
		{
			return (memPointer == it.memPointer);
		}

		bool operator!=(const reverse_vector_iterator<T>& it) const
		{
			return !(memPointer == it.memPointer);
		}

	private:
		T* memPointer;
};