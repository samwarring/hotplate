#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <hotplate/build_info.h>
#include <string>
#include <cctype>

BOOST_AUTO_TEST_SUITE(build_info_test_suite)

const char* string_values[]
{
	hotplate::build_info::VERSION,
	hotplate::build_info::COMMIT,
	hotplate::build_info::SEMVER,
	hotplate::build_info::CI_SERVICE,
	hotplate::build_info::VERSION_MAJOR,
	hotplate::build_info::VERSION_MINOR,
	hotplate::build_info::VERSION_PATCH
};

BOOST_DATA_TEST_CASE(string_values_not_null, string_values)
{
	BOOST_REQUIRE(sample != nullptr);
}

BOOST_DATA_TEST_CASE(string_values_not_empty, string_values)
{
	BOOST_REQUIRE(!std::string(sample).empty());
}

const char* build_number_values[]
{
	hotplate::build_info::VERSION_MAJOR,
	hotplate::build_info::VERSION_MINOR,
	hotplate::build_info::VERSION_PATCH,
	hotplate::build_info::CI_BUILD_NUMBER
};

BOOST_DATA_TEST_CASE(build_numbers_valid, build_number_values)
{
	int parsed = std::stoi(sample);
	BOOST_REQUIRE(parsed >= 0);
}

BOOST_AUTO_TEST_CASE(build_info_commit_is_hex)
{
	std::string commit(hotplate::build_info::COMMIT);
	for (char c : commit)
		BOOST_REQUIRE(std::isxdigit(c));
}

BOOST_AUTO_TEST_SUITE_END()
