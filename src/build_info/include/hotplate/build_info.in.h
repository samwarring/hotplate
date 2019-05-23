#ifndef __HOTPLATE_BUILD_INFO__
#define __HOTPLATE_BUILD_INFO__

namespace hotplate
{
	namespace build_info
	{
		constexpr const char * VERSION = "@PROJECT_VERSION@";
		constexpr const char * COMMIT = "@hotplate_COMMIT@";
		constexpr const char * SEMVER = "@PROJECT_VERSION@+@hotplate_COMMIT@";
		constexpr int VERSION_MAJOR = @PROJECT_VERSION_MAJOR@;
		constexpr int VERSION_MINOR = @PROJECT_VERSION_MINOR@;
		constexpr int VERSION_PATCH = @PROJECT_VERSION_PATCH@;
	}
}

#endif
