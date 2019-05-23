#include <boost/test/unit_test.hpp>
#include <hotplate/build_info.h>
#include <string>
#include <cctype>

BOOST_AUTO_TEST_SUITE(build_info_test_suite)

BOOST_AUTO_TEST_CASE(build_info_strings_not_null)
{
	BOOST_REQUIRE(hotplate::build_info::VERSION);
	BOOST_REQUIRE(hotplate::build_info::COMMIT);
	BOOST_REQUIRE(hotplate::build_info::SEMVER);
}

BOOST_AUTO_TEST_CASE(build_info_strings_not_emtpy)
{
	BOOST_REQUIRE(!std::string(hotplate::build_info::VERSION).empty());
	BOOST_REQUIRE(!std::string(hotplate::build_info::COMMIT).empty());
	BOOST_REQUIRE(!std::string(hotplate::build_info::SEMVER).empty());
}

BOOST_AUTO_TEST_CASE(build_info_ints_not_negative)
{
	BOOST_REQUIRE_LT(-1, hotplate::build_info::VERSION_MAJOR);
	BOOST_REQUIRE_LT(-1, hotplate::build_info::VERSION_MINOR);
	BOOST_REQUIRE_LT(-1, hotplate::build_info::VERSION_PATCH);
}

BOOST_AUTO_TEST_CASE(build_info_commit_is_hex)
{
	std::string commit(hotplate::build_info::COMMIT);
	for (char c : commit)
		BOOST_REQUIRE(std::isxdigit(c));
}

BOOST_AUTO_TEST_SUITE_END()
