#ifndef FCRISAN_FORMATTED_IO_UTIL_CHARS_HPP
#define FCRISAN_FORMATTED_IO_UTIL_CHARS_HPP

#include <iostream>
#include <climits>
#include <limits>
#include <boost/static_assert.hpp>

inline std::ostream &operator<<(std::ostream &stream, unsigned char val) {
	return stream << static_cast<unsigned int>(val);
}

inline std::ostream &operator<<(std::ostream &stream, signed char val) {
	// Assume modern machine: 8-bit byte, 2's complement, all bits are used for the value (i.e., no parity bits)
	BOOST_STATIC_ASSERT(CHAR_BIT == 8); // std::numeric_limits<unsigned char>::max() cannot be used in constant expression in C++98
	BOOST_STATIC_ASSERT(UCHAR_MAX == 0xFF);
	BOOST_STATIC_ASSERT(SCHAR_MAX == 127);
	BOOST_STATIC_ASSERT(SCHAR_MIN == -128);
	static const int mask = 0xFF;

	signed int printVal = val;
	if ((stream.flags() & std::ios_base::hex) || (stream.flags() & std::ios_base::oct))
		printVal = static_cast<signed int>(val & mask); // print '80' instead of 'ffffff80'
	return stream << printVal;
}

#endif // FCRISAN_FORMATTED_IO_UTIL_CHARS_HPP
