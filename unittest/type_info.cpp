#include <string>
#include <map>
#include <boost/test/auto_unit_test.hpp>
#include <fcrisan/formatted-io-util/type_info.hpp>

std::string Write(const std::type_info &value) {
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

struct somestruct123 {};
class someclassoranother {};
class Struct {};
struct Class {};

BOOST_AUTO_TEST_CASE(WriteTypeId)
{
	BOOST_CHECK_EQUAL(Write(typeid(bool)), "bool");
	BOOST_CHECK_EQUAL(Write(typeid(char)), "char");
	BOOST_CHECK_EQUAL(Write(typeid(unsigned char)), "unsigned char");
	BOOST_CHECK_EQUAL(Write(typeid(signed char)), "signed char");
	BOOST_CHECK_EQUAL(Write(typeid(short)), "short");
	BOOST_CHECK_EQUAL(Write(typeid(unsigned short)), "unsigned short");
	BOOST_CHECK_EQUAL(Write(typeid(int)), "int");
	BOOST_CHECK_EQUAL(Write(typeid(unsigned)), "unsigned int");
	BOOST_CHECK_EQUAL(Write(typeid(long)), "long");
	BOOST_CHECK_EQUAL(Write(typeid(unsigned long)), "unsigned long");
	BOOST_CHECK_EQUAL(Write(typeid(long long)), "long long");
	BOOST_CHECK_EQUAL(Write(typeid(unsigned long long)), "unsigned long long");

	// Should remove 'class' and 'struct' from types (they are added on Windows)
	BOOST_CHECK_EQUAL(Write(typeid(std::exception)), "std::exception");
	// but only if it's a lowercase word
	BOOST_CHECK_EQUAL(Write(typeid(Struct)), "Struct");
	BOOST_CHECK_EQUAL(Write(typeid(Class)), "Class");
	BOOST_CHECK_EQUAL(Write(typeid(somestruct123)), "somestruct123");
	BOOST_CHECK_EQUAL(Write(typeid(someclassoranother)), "someclassoranother");


	BOOST_CHECK_EQUAL(Write(typeid(void *)), "void*");
	BOOST_CHECK_EQUAL(Write(typeid(char *)), "char*");
	// TODO: Regularize const position, i.e., 'const char *' instead of the more confusing 'char const *'
	// BOOST_CHECK_EQUAL(Write(typeid(const char *)), "const char*");

	BOOST_CHECK_EQUAL(Write(typeid(std::string)), "std::string");
	BOOST_CHECK_EQUAL(Write(typeid(std::string *)), "std::string*");
	BOOST_CHECK_EQUAL(Write(typeid(std::wstring)), "std::wstring");
	BOOST_CHECK_EQUAL(Write(typeid(std::ostream)), "std::ostream");

	// TODO: get rid of default template parameters, may require some sort of recursive parser
	BOOST_CHECK_EQUAL(Write(typeid(std::map<std::string, std::string>)), "std::map<std::string, std::string>");
}
