#ifndef FCRISAN_FORMATTED_IO_UTIL_TYPE_INFO_HPP
#define FCRISAN_FORMATTED_IO_UTIL_TYPE_INFO_HPP

#include <iosfwd>
#include <typeinfo>

std::ostream & operator<<(std::ostream &, const std::type_info &);

#endif // FCRISAN_FORMATTED_IO_UTIL_TYPE_INFO_HPP
