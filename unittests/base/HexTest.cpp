#define BOOST_TEST_MODULE base_test_suite
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <string>

#include <base/Hex.h>

using namespace ultrainio;
using namespace std;

BOOST_AUTO_TEST_SUITE(base_test_suite)
    BOOST_AUTO_TEST_CASE(fromHex) {
        std::string src = std::string("775331799d6eb0379e4e2d253f363c3c33a709cd");
        unsigned char c[20];
        BOOST_CHECK(Hex::fromHex<unsigned char>(src, c, 20) == 20);
        std::string des = Hex::toHex<unsigned char>(c, 20);
        BOOST_CHECK(src == des);
    }

BOOST_AUTO_TEST_SUITE_END()
