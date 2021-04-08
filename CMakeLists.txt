cmake_minimum_required(VERSION 3.5)
project(fc-formatted-io-util CXX)

enable_testing()

find_package(Boost 1.33 REQUIRED COMPONENTS unit_test_framework)

add_library(fc-formatted-io-util
	include/fcrisan/formatted-io-util/chars.hpp
	src/chars.cpp
	)
set_property(
	TARGET fc-formatted-io-util
	PROPERTY PUBLIC_HEADER
	include/fcrisan/formatted-io-util/chars.hpp
	)
target_link_libraries(fc-formatted-io-util
	PUBLIC
		Boost::boost
	)
target_include_directories(fc-formatted-io-util
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	)


add_executable(fc-formatted-io-util-test
	unittest/chars.cpp
	)
target_link_libraries(fc-formatted-io-util-test
	PRIVATE
		fc-formatted-io-util
		Boost::unit_test_framework
	)
add_test(fc-formatted-io-util-test fc-formatted-io-util-test)
