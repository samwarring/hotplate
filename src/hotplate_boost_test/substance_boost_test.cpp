#include <boost/test/unit_test.hpp>
#include <hotplate/hotplate.h>

BOOST_AUTO_TEST_SUITE(substance_test_suite)

BOOST_AUTO_TEST_CASE(substance_test_1)
{
	hotplate::substance s(50, 0, 100);
	BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_SUITE_END()

