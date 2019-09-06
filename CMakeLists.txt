# CMake Version reference.
# This provides rationale for the cmake_minimum_required version.
#
# 3.11.3 : Travis Mac images
# 3.12.4 : Travis Xenial images
# 3.13.0 : Supports Boost1.68, 1.69.
#          The install(TARGETS) command learned to install targets created outside the current directory.
# 3.14.0 : Supports Boost 1.70
# 3.14.4 : Installed by travis_before_script.sh
# 3.15.1 : AppVeyor Windows images (VS2015+)
#
# Reference : https://stackoverflow.com/a/42124857
#             https://stackoverflow.com/a/34444949
#             https://cmake.org/cmake/help/v3.13/release/3.13.html
#             https://www.appveyor.com/docs/windows-images-software/#tools
#             https://docs.travis-ci.com/user/reference/osx#compilers-and-build-toolchain
#             https://docs.travis-ci.com/user/reference/xenial/#compilers-and-build-toolchain
cmake_minimum_required(VERSION 3.13)

# Read version from cache
set(hotplate_VERSION 0.1.4 CACHE STRING "Hotplate version (ex: 1.2.3)")

project(hotplate VERSION ${hotplate_VERSION})
enable_testing()

# Cache variables
set(hotplate_COMMIT "0" CACHE STRING "Git commit hash for this build of hotplate")
set(hotplate_CI_SERVICE "local" CACHE STRING "Name of CI service that created this build (local, travis, appveyor)")
set(hotplate_CI_BUILD_NUMBER "0" CACHE STRING "Build number assigned by the CI service")

# Create a full version string and print it
set(hotplate_SEMVER "${PROJECT_VERSION}+${hotplate_CI_SERVICE}#${hotplate_CI_BUILD_NUMBER}-${hotplate_COMMIT}")
message(STATUS "${PROJECT_NAME} version: ${hotplate_SEMVER}")

# Load utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(HotplateUtils)

# Boost version reference.
# This provides rationale for the find_package(Boost) version.
#
# 1.32 : Added program_options
# 1.59 : Added BOOST_AUTO_TEST_CASE and BOOST_DATA_TEST_CASE
# 1.67 : Default on OSX in Travis
# 1.69 : Default on Windows on AppVeyor (VS2015, VS2017)
#        Installed by travis_before_script.sh
#
# References : https://www.boost.org/users/history/version_1_59_0.html
#              https://www.boost.org/doc/libs/1_32_0/doc/html/program_options.html
#              https://www.boost.org/doc/libs/1_59_0/libs/test/doc/html/index.html
#              https://packages.ubuntu.com/xenial/libboost-all-dev
#              https://www.appveyor.com/docs/windows-images-software/#boost
find_package(Boost 1.59 REQUIRED
	COMPONENTS unit_test_framework
	           program_options)

# Add targets from the src directory
add_subdirectory(src)

# CMake package configuration files
include(CMakePackageConfigHelpers)
set(hotplate_INSTALLDIR_INCLUDE include/)
set(hotplate_INSTALLDIR_LIB lib/)
configure_package_config_file(
	hotplateConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/hotplateConfig.cmake
	PATH_VARS hotplate_INSTALLDIR_INCLUDE
	          hotplate_INSTALLDIR_LIB
	INSTALL_DESTINATION lib/hotplate/cmake)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/hotplateConfigVersion.cmake
	VERSION ${hotplate_VERSION}
	COMPATIBILITY SameMajorVersion)

# Installation steps
include(GNUInstallDirs)
install(TARGETS hotplate_lib hotplate_app
	EXPORT hotplate_targets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(DIRECTORY include/hotplate
	DESTINATION include
	FILES_MATCHING PATTERN "*.h")
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/hotplateConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/hotplateConfigVersion.cmake"
	"${CMAKE_CURRENT_LIST_DIR}/LICENSE"
	"${CMAKE_CURRENT_LIST_DIR}/README.md"
	DESTINATION share/hotplate)

# Install a path-agnostic hotplateTargets.cmake file.
install(EXPORT hotplate_targets
	DESTINATION share/hotplate
	NAMESPACE hotplate::
	FILE hotplateTargets.cmake)

# Generate a local hotplateTargets.cmake file with paths to the current build.
export(
	EXPORT hotplate_targets
	NAMESPACE hotplate::
	FILE hotplateTargets.cmake)
