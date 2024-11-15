#pragma once
#include <vector>
#include "./iterator.hpp"
#include "./bit_proxy.hpp"
using namespace std;

template <typename T>
class Vector
{
private:
	vector<T> data;
public:
	using ValueType = T;

	void push_back(const T& value) { data.push_back(value); }
	void pop_back()
	{
		if (data.empty())
		{
			throw runtime_error
			("Unable to remove from an empty vector");
		}

		data.pop_back();
	}

	T& operator[](size_t index)
	{
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

	size_t size() const { return data.size(); }
};

template <>
class Vector<bool>
{
private:
	std::vector<uint8_t> data;
	size_t all_bits = 0;
	size_t free_bits = 0;

public:
	using ValueType = bool;
	using iterator = bool_vector_iterator<Vector<bool>>;
	using const_iterator = const_bool_iterator<Vector<bool>>;
	using reverse_iterator = reverse_vector_iterator<Vector<bool>>;

	void push_back(bool value)
	{
		if (free_bits == 0)
		{
			data.push_back(0);
			free_bits = 8;
		}

		--free_bits;

		if (value) { data.back() |= (1 << free_bits); }
		++all_bits;
	}

	void pop_back()
	{
		if (all_bits == 0)
			throw runtime_error
			("Unable to remove from an empty vector");

		size_t bit_pos = (all_bits - 1) % 8;
		size_t byte_index = (all_bits - 1) / 8;
		data[byte_index] &= ~(1 << (7 - bit_pos));

		--all_bits;
		if (all_bits % 8 == 0 && !data.empty())
		{
			data.pop_back();
			free_bits = 8;
		}
		else { ++free_bits; }
	}

	void insert(iterator iter, bool value)
	{
		size_t index = iter.index();

		if (index > all_bits)
			throw out_of_range("Iterator out of range");

		if (free_bits == 0)
		{
			data.push_back(0);
			free_bits = 8;
		}

		for (size_t i = all_bits; i > index; --i)
		{
			size_t byte_from = (i - 1) / 8;
			size_t bit_from = (i - 1) % 8;
			size_t byte_to = i / 8;
			size_t bit_to = i % 8;

			if (data[byte_from] & (1 << (7 - bit_from)))
				data[byte_to] |= (1 << (7 - bit_to));
			else
				data[byte_to] &= ~(1 << (7 - bit_to));
		}

		size_t index_byte = index / 8;
		size_t bit_pos = 7 - (index % 8);

		if (value)
			data[index_byte] |= (1 << bit_pos);
		else
			data[index_byte] &= ~(1 << bit_pos);

		++all_bits;
		--free_bits;
	}

	void remove(iterator iter)
	{
		size_t index = iter.index();

		if (index >= all_bits)
			throw out_of_range("Iterator out of range");

		for (size_t i = index; i < all_bits; ++i)
		{
			size_t byte_from = (i + 1) / 8;
			size_t bit_from = (i + 1) % 8;
			size_t byte_to = i / 8;
			size_t bit_to = i % 8;

			if (data[byte_from] & (1 << (7 - bit_from)))
				data[byte_to] |= (1 << (7 - bit_to));
			else
				data[byte_to] &= ~(1 << (7 - bit_to));
		}

		size_t pos_last_bit = (all_bits - 1) % 8;
		size_t last_byte = (all_bits - 1) / 8;
		data[last_byte] &= ~(1 << (7 - pos_last_bit));

		--all_bits;
		++free_bits;

		if (all_bits % 8 == 0 && !data.empty())
		{
			data.pop_back();
			free_bits = 8;
		}
	}

	void pop_front()
	{
		if (all_bits == 0)
			throw runtime_error
			("Unable to remove from an empty vector");

		for (size_t i = 0; i < all_bits - 1; ++i)
		{
			size_t byte_from = (i + 1) / 8;
			size_t bit_from = (i + 1) % 8;
			size_t byte_to = i / 8;
			size_t bit_to = i % 8;

			if (data[byte_from] & (1 << (7 - bit_from)))
				data[byte_to] |= (1 << (7 - bit_to));
			else
				data[byte_to] &= ~(1 << (7 - bit_to));
		}

		size_t pos_last_bit = (all_bits - 1) % 8;
		size_t last_byte = (all_bits - 1) / 8;
		data[last_byte] &= ~(1 << (7 - pos_last_bit));

		--all_bits;
		++free_bits;

		if (all_bits % 8 == 0 && !data.empty())
		{
			data.pop_back();
			free_bits = 8;
		}
	}

	bool operator[](size_t index) const
	{
		if (index >= all_bits)
			throw out_of_range("Out of range");

		size_t bit_pos = 7 - (index % 8);
		size_t byte_index = index / 8;
		return (data[byte_index] & (1 << bit_pos)) != 0;
	}

	BitProxy operator[](size_t index)
	{
		if (index >= all_bits)
			throw out_of_range("Out of range");

		size_t pos_bit = 7 - (index % 8);
		size_t index_byte = index / 8;

		return BitProxy(data, index_byte, pos_bit);
	}

	iterator begin(){ return iterator(*this, 0); }

	iterator end() { return iterator(*this, all_bits); }

	const_iterator begin() const { return const_iterator(*this, 0); }
	
	const_iterator end() const { return const_iterator(*this, all_bits); }

	reverse_iterator rev_begin() { return reverse_iterator(*this, all_bits - 1); }

	reverse_iterator rev_end() { return reverse_iterator(*this, 0); }

	size_t size() const { return all_bits; }
};