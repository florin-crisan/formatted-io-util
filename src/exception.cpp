#include <iostream>
#include <fcrisan/formatted-io-util/exception.hpp>
#include <fcrisan/formatted-io-util/type_info.hpp>

std::ostream & operator<<(std::ostream &stream, const std::exception &ex) {
	return stream << typeid(ex) << ": " << ex.what();
}
