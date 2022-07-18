#ifndef HEX_PRINTING_H
#define HEX_PRINTING_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

typedef unsigned long ulong;
typedef unsigned short ushort;

struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(char _c)
{
	return HexCharStruct(_c);
}

template <typename T>
std::string int_to_hex(T i)
{
	int val = i;
	std::stringstream stream;
	stream 	<< std::hex << std::uppercase << val;
	return stream.str();
}

template <typename T>
std::string int_to_hex_long_format(T i)
{
	int val = i;
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(8)
		<< std::hex << val;
	return stream.str();
}

#endif