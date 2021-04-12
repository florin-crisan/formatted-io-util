cmake_minimum_required(VERSION 3.5)
project(fc-formatted-io-util CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

enable_testing()

find_package(Boost 1.33 REQUIRED COMPONENTS unit_test_framework)

add_library(fc-formatted-io-util
	include/fcrisan/formatted-io-util/chars.hpp
	src/chars.cpp
	include/fcrisan/formatted-io-util/type_info.hpp
	src/type_info.cpp
	)
set_property(
	TARGET fc-formatted-io-util
	PROPERTY PUBLIC_HEADER
	include/fcrisan/formatted-io-util/chars.hpp
	include/fcrisan/formatted-io-util/type_info.hpp
	)
target_link_libraries(fc-formatted-io-util
	PUBLIC
		Boost::boost
	)
target_include_directories(fc-formatted-io-util
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)
add_library(FCrisanFormattedIOUtil::fc-formatted-io-util ALIAS fc-formatted-io-util)


add_executable(fc-formatted-io-util-test
	unittest/chars.cpp
	unittest/type_info.cpp
	)
target_link_libraries(fc-formatted-io-util-test
	PRIVATE
		fc-formatted-io-util
		Boost::unit_test_framework
	)
add_test(fc-formatted-io-util-test fc-formatted-io-util-test)

#-----------------------------------------------------------------------------

install(TARGETS fc-formatted-io-util
	EXPORT FCrisanFormattedIOUtil
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fcrisan/formatted-io-util/
	)
configure_package_config_file(
	FCrisanFormattedIOUtilConfig.cmake.in
	FCrisanFormattedIOUtilConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FCrisanFormattedIOUtil
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/FCrisanFormattedIOUtilConfig.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FCrisanFormattedIOUtil
	)
install(EXPORT FCrisanFormattedIOUtil
	NAMESPACE FCrisanFormattedIOUtil::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FCrisanFormattedIOUtil
	FILE FCrisanFormattedIOUtil_Targets.cmake
	)
