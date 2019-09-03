cmake_minimum_required(VERSION 3.5)

# Read version from cache
set(hotplate_VERSION 0.1.4 CACHE STRING "Hotplate version (ex: 1.2.3)")

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

# Dependencies
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
install(TARGETS hotplate_static hotplate_app
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
