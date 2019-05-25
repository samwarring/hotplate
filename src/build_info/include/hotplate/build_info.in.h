#ifndef __HOTPLATE_BUILD_INFO__
#define __HOTPLATE_BUILD_INFO__

namespace hotplate
{
	namespace build_info
	{
		constexpr const char * VERSION = "@PROJECT_VERSION@";
		constexpr const char * VERSION_MAJOR = "@PROJECT_VERSION_MAJOR@";
		constexpr const char * VERSION_MINOR = "@PROJECT_VERSION_MINOR@";
		constexpr const char * VERSION_PATCH = "@PROJECT_VERSION_PATCH@";
		constexpr const char * COMMIT = "@hotplate_COMMIT@";
		constexpr const char * CI_SERVICE = "@hotplate_CI_SERVICE@";
		constexpr const char * CI_BUILD_NUMBER = "@hotplate_CI_BUILD_NUMBER@";
		constexpr const char * SEMVER = "@PROJECT_VERSION@+@hotplate_CI_SERVICE@#@hotplate_CI_BUILD_NUMBER@-@hotplate_COMMIT@";
	}
}

#endif
