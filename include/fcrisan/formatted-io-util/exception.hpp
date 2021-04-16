#ifndef FCRISAN_FORMATTED_IO_UTIL_EXCEPTION_HPP
#define FCRISAN_FORMATTED_IO_UTIL_EXCEPTION_HPP

#include <exception>
#include <iosfwd>

std::ostream &operator<<(std::ostream &, const std::exception &ex);

#endif // FCRISAN_FORMATTED_IO_UTIL_EXCEPTION_HPP
