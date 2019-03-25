#define BOOST_TEST_MODULE hotplate_boost_test
#include <boost/test/unit_test.hpp>
#include <hotplate/hotplate.h>

BOOST_AUTO_TEST_SUITE(hotplate_test_suite)

BOOST_AUTO_TEST_CASE(hotplate_test_1)
{
	hotplate::hotplate hp(42);
	BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_SUITE_END()
