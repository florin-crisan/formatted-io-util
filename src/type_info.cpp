#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/smart_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <fcrisan/formatted-io-util/type_info.hpp>

#ifdef __GNUC__
#	include <cxxabi.h>
#endif

namespace {

std::string Demangle(const char *mangled) {
#ifdef __GNUC__
	boost::shared_ptr<char> demangled(abi::__cxa_demangle(mangled, 0, 0, 0), &free);
	if (demangled)
		return demangled.get();
#endif
	return mangled;
}

inline std::string Demangle(const std::type_info &type) {
	return Demangle(type.name());
}

} // anonymous namespace

std::ostream & operator<<(std::ostream &stream, const std::type_info &type) {
	using namespace std;
	string typeName = Demangle(type);

#ifdef FCRISAN_FORMATTED_IO_UTIL_BEAUTIFY_TYPENAMES
	using namespace boost;
	using namespace boost::algorithm;
	using namespace boost::regex_constants;

	struct Replacement {
		string what;
		const char *replaceWith;
	};
	// Order is important here: replace the full name of string before trying to get rid of 'class' and 'struct'.
	static const Replacement replacements[] = {
		// prefer short names for standard types, i.e. 'std::string' instead of 'class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >'
#define SHORTNAME(type) {Demangle(typeid(type)), #type}

		SHORTNAME(std::string),
		SHORTNAME(std::wstring),

		SHORTNAME(std::iostream),
		SHORTNAME(std::wiostream),
		SHORTNAME(std::istream),
		SHORTNAME(std::wistream),
		SHORTNAME(std::ostream),
		SHORTNAME(std::wostream),

		SHORTNAME(std::fstream),
		SHORTNAME(std::wfstream),
		SHORTNAME(std::ifstream),
		SHORTNAME(std::wifstream),
		SHORTNAME(std::ofstream),
		SHORTNAME(std::wofstream),

		SHORTNAME(std::stringstream),
		SHORTNAME(std::wstringstream),
		SHORTNAME(std::istringstream),
		SHORTNAME(std::wistringstream),
		SHORTNAME(std::ostringstream),
		SHORTNAME(std::wostringstream),

#ifdef _MSC_VER
		SHORTNAME(long long), // instead of '__int64'
		{"* __ptr64", "*"},
#endif // _MSC_VER
	};

	for (size_t i = 0; i < sizeof(replacements)/sizeof(replacements[0]); ++i) {
		const Replacement &r = replacements[i];
		replace_all(typeName, r.what, r.replaceWith);
	}

	struct RegexReplacement {
		regex what;
		string replaceWith;
	};
	static const RegexReplacement regexReplacements[] = {
		{
			// trim whitespace from '*'
			regex("\\s*\\*\\s*", format_perl),
			"*"
		},
#ifdef _MSC_VER
		{
			// 'class std::exception' --> 'std::exception'
			regex("\\<class\\>\\s*", format_perl),
			""
		},
		{
			regex("\\<struct\\>\\s*", format_perl),
			""
		},
#endif // _MSC_VER
		{
			// std::map<std::string, std::string, std::less<std::string>, std::allocator<std::pair<std::string const, std::string> > >
			regex("std::map\\s*<\\s*([a-zA-Z0-9_:]+)\\s*,\\s*([a-zA-Z0-9_:]+)\\s*,\\s*"
				"std::less\\s*<\\s*\\1\\s*>\\s*,\\s*"
				"std::allocator\\s*<\\s*std::pair\\s*<\\s*\\1\\s+const\\s*,\\s*\\2\\s*>\\s*>\\s*>\\s*",
				format_perl),
			"std::map<$1, $2>"
		}
	};

	for (size_t i = 0; i < sizeof(regexReplacements) / sizeof(regexReplacements[0]); ++i) {
		const RegexReplacement &r = regexReplacements[i];
		replace_all_regex(typeName, r.what, r.replaceWith);
	}

#endif // FCRISAN_FORMATTED_IO_UTIL_BEAUTIFY_TYPENAMES

	return stream << typeName;
}
