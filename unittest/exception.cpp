#include <stdexcept>
#include <sstream>
#include <boost/test/auto_unit_test.hpp>
#include <fcrisan/formatted-io-util/exception.hpp>

std::string Write(const std::exception &value) {
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

BOOST_AUTO_TEST_CASE(WriteException)
{
	BOOST_CHECK_EQUAL(Write(std::runtime_error("Blah blah blah")), "std::runtime_error: Blah blah blah");
}
