#include <boost/test/auto_unit_test.hpp>
#include <fcrisan/formatted-io-util/type_info.hpp>

std::string Write(const std::type_info &value) {
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

BOOST_AUTO_TEST_CASE(WriteTypeId)
{
	BOOST_CHECK_EQUAL(Write(typeid(bool)), "bool");
	BOOST_CHECK_EQUAL(Write(typeid(char)), "char");
	BOOST_CHECK_EQUAL(Write(typeid(int)), "int");
	BOOST_CHECK(Write(typeid(std::exception)).find("std::exception") != std::string::npos);
}
