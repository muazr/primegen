#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "primenumbergenerator.h"

TEST_CASE("Numbers are test for primality", "[primality]")
{
    PrimeNumberGenerator primegen(100);

    REQUIRE(primegen.isPrime(0) == false);
    REQUIRE(primegen.isPrime(1) == false);
    REQUIRE(primegen.isPrime(2) == true);
    REQUIRE(primegen.isPrime(3) == true);
    REQUIRE(primegen.isPrime(97) == true);
    REQUIRE(primegen.isPrime(98) == false);
}
