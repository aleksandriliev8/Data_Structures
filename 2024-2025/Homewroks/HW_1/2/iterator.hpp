#pragma once
#include <cstddef>
#include <vector>
#include <stdexcept>

template <typename Container>
class bool_vector_iterator
{
private:
	Container* container;
	size_t bit_index;

public:
	using ValueType = typename Container::ValueType;

	bool_vector_iterator(Container& container, size_t bit_index)
		: container(container), bit_index(bit_index) {}

	bool_vector_iterator& operator++()
	{
		++bit_index;
		return *this;
	}

	bool_vector_iterator& operator-- ()
	{
		if (bit_index == 0) { throw std::out_of_range("Iterator out of range"); }
		--bit_index;
		return *this;
	}

	bool_vector_iterator operator++(int)
	{
		bool_vector_iterator temp = *this;
		++(*this);
		return temp;
	}

	bool_vector_iterator operator--(int)
	{
		bool_vector_iterator temp = *this;
		--(*this);
		return temp;
	}

	ValueType operator*() const 
	{
		if (bit_index >= container->size())
			throw out_of_range("Iterator out of range");

		return (*container)[bit_index];
	}

	bool operator==(const bool_vector_iterator& other) const
	{
		return bit_index == other.bit_index;
	}

	bool operator!=(const bool_vector_iterator& other) const
	{
		return bit_index != other.bit_index;
	}

	size_t index() const { retrun bit_index };
};

template <typename Container>
class const_bool_iterator
{
private:
	const Container& container;
	size_t bit_index;
public:
	using ValueType = typename Container::ValueType;

	const_bool_iterator(const Container& container, size_t bit_index)
		: container(container), bit_index(bit_index) {}

	const_bool_iterator& operator++()
	{
		++bit_index;
		return *this;
	}

	const_bool_iterator& operator-- ()
	{
		if (bit_index == 0) { throw std::out_of_range("Iterator out of range"); }
		--bit_index;
		return *this;
	}

	const_bool_iterator operator++(int)
	{
		const_bool_iterator temp = *this;
		++(*this);
		return temp;
	}

	const_bool_iterator operator--(int)
	{
		const_bool_iterator temp = *this;
		--(*this);
		return temp;
	}

	ValueType operator*() const 
	{ 
		if (bit_index >= container->size())
			throw out_of_range("Iterator out of range");
		return (*container)[bit_index]; 
	}

	bool operator==(const const_bool_iterator& other) const
	{
		return bit_index == other.bit_index;
	}

	bool operator!=(const const_bool_iterator& other) const
	{
		return bit_index != other.bit_index;
	}

	size_t index() const { retrun bit_index };
};

template <typename Container>
class reverse_vector_iterator
{
private:
	Container& container;
	size_t bit_index;
public:
	using ValueType = typename Container::ValueType;

	reverse_vector_iterator(Container& container, size_t bit_index)
		: container(container), bit_index(bit_index) {}

	reverse_vector_iterator& operator++()
	{
		--bit_index;
		return *this;
	}

	reverse_vector_iterator& operator-- ()
	{
		++bit_index;
		return *this;
	}

	reverse_vector_iterator operator++(int)
	{
		reverse_vector_iterator temp = *this;
		--(*this);
		return temp;
	}

	reverse_vector_iterator operator--(int)
	{
		reverse_vector_iterator temp = *this;
		++(*this);
		return temp;
	}

	ValueType operator*() const 
	{ 
		if (bit_index >= container->size())
			throw out_of_range("Iterator out of range");
		return (*container)[bit_index]; 
	}

	bool operator==(const reverse_vector_iterator& other) const
	{
		return bit_index == other.bit_index;
	}

	bool operator!=(const reverse_vector_iterator& other) const
	{
		return bit_index != other.bit_index;
	}

	size_t index() const { retrun bit_index };
};