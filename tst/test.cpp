#define BOOST_TEST_MODULE TestSuite
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(FirstTest)
{
	BOOST_CHECK_EQUAL(2+2, 4);
}