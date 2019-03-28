cmake_minimum_required(VERSION 3.0)
project(hotplate)
enable_testing()

# Cache variables
set(Boost_USE_STATIC_LIBS OFF CACHE BOOL "Statically link to Boost libraries")

# Dependencies
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Print variables showing which dependencies were selected
message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libs: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost libs (debug): ${Boost_LIBRARY_DIR_DEBUG}")
message(STATUS "Boost libs (release): ${Boost_LIBRARY_DIR_RELEASE}")

# Static library
add_library(hotplate_static STATIC 
	src/hotplate_static/hotplate.cpp
	src/hotplate_static/include/hotplate/hotplate.h)
target_include_directories(hotplate_static
	PUBLIC src/hotplate_static/include)
target_compile_features(hotplate_static
	PUBLIC cxx_strong_enums
	       cxx_noexcept)

# Executable app
add_executable(hotplate_app
	src/hotplate_app/main.cpp)
target_link_libraries(hotplate_app
	PRIVATE hotplate_static)

# Boost unit test binary
add_executable(hotplate_boost_test
	src/hotplate_boost_test/main.cpp
	src/hotplate_boost_test/hotplate_boost_test.cpp
	src/hotplate_boost_test/substance_boost_test.cpp)
target_link_libraries(hotplate_boost_test
	PRIVATE hotplate_static
	        Boost::unit_test_framework)
if(NOT ${Boost_USE_STATIC_LIBS})
	target_compile_definitions(hotplate_boost_test
		PRIVATE BOOST_TEST_DYN_LINK=1)
endif()
		
# Tests
add_test(
	NAME hotplate_app
	COMMAND "${CURRENT_BUILD_DIR}/hotplate_app")
add_test(
	NAME hotplate_boost_test
	COMMAND "${CURRENT_BUILD_DIR}/hotplate_boost_test")
