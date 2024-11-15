#pragma once
#include <vector>
using namespace std;

class BitProxy
{
private:
	vector<uint8_t>& data;
	size_t index_byte;
	size_t pos_bit;

public:
	BitProxy(vector<uint8_t>& _data, size_t _index_byte, size_t _pos_bit)
		: data(_data), index_byte(_index_byte), pos_bit(_pos_bit) {}

	BitProxy& operator=(bool value)
	{
		if (value)
			data[index_byte] |= (1 << pos_bit);
		else
			data[index_byte] &= ~(1 << pos_bit);
		return *this;
	}

	operator bool() const { return (data[index_byte] & (1 << pos_bit)) != 0; }
};
