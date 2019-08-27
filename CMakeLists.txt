cmake_minimum_required(VERSION 3.5)

# Read version from cache
set(hotplate_VERSION 0.0.0 CACHE STRING "Hotplate version (ex: 1.2.3)")

project(hotplate VERSION ${hotplate_VERSION})
enable_testing()

# Cache variables
set(hotplate_COMMIT "0" CACHE STRING "Git commit hash for this build of hotplate")
set(hotplate_CI_SERVICE "local" CACHE STRING "Name of CI service that created this build (local, travis, appveyor)")
set(hotplate_CI_BUILD_NUMBER "0" CACHE STRING "Build number assigned by the CI service")
set(Boost_USE_STATIC_LIBS OFF CACHE BOOL "Statically link to Boost libraries")

# Create a full version string and print it
set(hotplate_SEMVER "${PROJECT_VERSION}+${hotplate_CI_SERVICE}#${hotplate_CI_BUILD_NUMBER}-${hotplate_COMMIT}")
message(STATUS "${PROJECT_NAME} version: ${hotplate_SEMVER}")

# Write build version information to a header file, and create
# an interface target for it to be used by other targets.
configure_file(
	src/build_info/include/hotplate/build_info.in.h
	src/build_info/include/hotplate/build_info.h)
add_library(build_info INTERFACE)
target_include_directories(build_info
	INTERFACE ${PROJECT_BINARY_DIR}/src/build_info/include)

# Dependencies
find_package(Boost 1.59 REQUIRED
	COMPONENTS unit_test_framework
	           program_options)

# Print variables showing which dependencies were selected
message(STATUS "Boost static link: ${Boost_USE_STATIC_LIBS}")
message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
if(CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Boost libs (debug): ${Boost_LIBRARY_DIR_DEBUG}")
	message(STATUS "Boost libs (release): ${Boost_LIBRARY_DIR_RELEASE}")
else()
	message(STATUS "Boost libs: ${Boost_LIBRARY_DIRS}")
endif()

# Static library
add_library(hotplate_static STATIC 
	src/hotplate_static/hotplate.cpp
	src/hotplate_static/include/hotplate/hotplate.h)
target_include_directories(hotplate_static
	PUBLIC src/hotplate_static/include)
target_compile_features(hotplate_static
	PUBLIC cxx_strong_enums
	       cxx_noexcept)
install(TARGETS hotplate_static)
install(DIRECTORY src/hotplate_static/include
        DESTINATION .
        FILES_MATCHING PATTERN "*.h")

# Executable app
add_executable(hotplate_app
	src/hotplate_app/main.cpp)
target_link_libraries(hotplate_app
	PRIVATE hotplate_static
	        Boost::program_options
	        build_info)
install(TARGETS hotplate_app)

# Boost unit test binary
add_executable(hotplate_boost_test
	src/hotplate_boost_test/main.cpp
	src/hotplate_boost_test/hotplate_boost_test.cpp
	src/hotplate_boost_test/substance_boost_test.cpp
	src/hotplate_boost_test/build_info_boost_test.cpp)
target_link_libraries(hotplate_boost_test
	PRIVATE build_info
	        hotplate_static
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
