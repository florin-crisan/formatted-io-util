#define BOOST_TEST_MODULE formatted_io_util_test
#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>
#include <fcrisan/formatted-io-util/chars.hpp>

template <typename T>
std::string Write(T value) {
	std::ostringstream stream;
	stream << value;
	BOOST_CHECK(stream.good());
	return stream.str();
}

template <typename T, typename Manip1>
std::string Write(T value, Manip1 manip1) {
	std::ostringstream stream;
	stream
		<< manip1
		<< value;
	BOOST_CHECK(stream.good());
	return stream.str();
}

template <typename T, typename Manip1, typename Manip2>
std::string Write(T value, Manip1 manip1, Manip2 manip2) {
	std::ostringstream stream;
	stream
		<< manip1
		<< manip2
		<< value;
	BOOST_CHECK(stream.good());
	return stream.str();
}

template <typename T, typename Manip1, typename Manip2, typename Manip3>
std::string Write(T value, Manip1 manip1, Manip2 manip2, Manip3 manip3) {
	std::ostringstream stream;
	stream
		<< manip1
		<< manip2
		<< manip3
		<< value;
	BOOST_CHECK(stream.good());
	return stream.str();
}

template <typename T, typename Manip1, typename Manip2, typename Manip3, typename Manip4>
std::string Write(T value, Manip1 manip1, Manip2 manip2, Manip3 manip3) {
	std::ostringstream stream;
	stream
		<< manip1
		<< manip2
		<< manip3
		<< value;
	BOOST_CHECK(stream.good());
	return stream.str();
}

BOOST_AUTO_TEST_CASE(WriteTest)
{
	using namespace std;

	BOOST_CHECK_EQUAL(Write<char>('a'), "a");
	BOOST_CHECK_EQUAL(Write<char>('\xFF'), "\xFF");

	BOOST_CHECK_EQUAL(Write<unsigned char>(0), "0");
	BOOST_CHECK_EQUAL(Write<signed char>(0), "0");

	BOOST_CHECK_EQUAL(Write<unsigned char>(255), "255");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, oct), "377");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, oct, showbase), "0377");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, hex), "ff");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, hex, showbase), "0xff");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, hex, uppercase), "FF");
	BOOST_CHECK_EQUAL(Write<unsigned char>(255, hex, uppercase, showbase), "0XFF");

	BOOST_CHECK_EQUAL(Write<signed char>(-128), "-128");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, oct), "200");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, oct, showbase), "0200");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, hex), "80");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, hex, showbase), "0x80");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, hex, uppercase), "80");
	BOOST_CHECK_EQUAL(Write<signed char>(-128, hex, uppercase, showbase), "0X80");

	BOOST_CHECK_EQUAL(Write<signed char>(127), "127");
	BOOST_CHECK_EQUAL(Write<signed char>(127, oct), "177");
	BOOST_CHECK_EQUAL(Write<signed char>(127, oct, showbase), "0177");
	BOOST_CHECK_EQUAL(Write<signed char>(127, hex), "7f");
	BOOST_CHECK_EQUAL(Write<signed char>(127, hex, showbase), "0x7f");
	BOOST_CHECK_EQUAL(Write<signed char>(127, hex, uppercase), "7F");
	BOOST_CHECK_EQUAL(Write<signed char>(127, hex, uppercase, showbase), "0X7F");
}
