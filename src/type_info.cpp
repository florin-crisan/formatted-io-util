#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp>
#include <fcrisan/formatted-io-util/type_info.hpp>

#ifdef __GNUC__
#	include <cxxabi.h>
#endif

namespace {

void DoNothing(const void *) {}

boost::shared_ptr<const char> Demangle(const char *mangled) {
#ifdef __GNUC__
	boost::shared_ptr<char> demangled(abi::__cxa_demangle(mangled, 0, 0, 0), &free);
	if (demangled)
		return demangled;
#endif
	return boost::shared_ptr<const char>(mangled, DoNothing);
}

} // anonymous namespace

std::ostream & operator<<(std::ostream &stream, const std::type_info &type) {
	return stream << Demangle(type.name());
}
