#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "primenumbergenerator.h"

TEST_CASE("Numbers are tested for primality", "[primality]")
{
    REQUIRE(PrimeNumberGenerator::isPrime(0) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(1) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(2) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(3) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(4) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(5) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(91) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(97) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(98) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(7917) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(7918) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(7919) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(7920) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(7921) == false);
    REQUIRE(PrimeNumberGenerator::isPrime(2305843009213693949ULL) == false);
    // Mersenne prime (2^61-1)
    REQUIRE(PrimeNumberGenerator::isPrime(2305843009213693951ULL) == true);
    REQUIRE(PrimeNumberGenerator::isPrime(2305843009213693953ULL) == false);
}

TEST_CASE("The next prime number is checked", "[nextprime]")
{
    REQUIRE(PrimeNumberGenerator::getNextPrime(0) == 2);
    REQUIRE(PrimeNumberGenerator::getNextPrime(1) == 2);
    REQUIRE(PrimeNumberGenerator::getNextPrime(2) == 3);
    REQUIRE(PrimeNumberGenerator::getNextPrime(3) == 5);
    REQUIRE(PrimeNumberGenerator::getNextPrime(4) == 5);
    REQUIRE(PrimeNumberGenerator::getNextPrime(5) == 7);
    REQUIRE(PrimeNumberGenerator::getNextPrime(7917) == 7919);
    // Mersenne prime (2^61-1)
    REQUIRE(PrimeNumberGenerator::getNextPrime(2305843009213693949ULL) == 2305843009213693951ULL);
}

TEST_CASE("Prime number generation is tested", "[primegen]")
{
    std::ostringstream out;

    SECTION("0")
    {
        PrimeNumberGenerator primegen(0, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "");
    }

    SECTION("1")
    {
        PrimeNumberGenerator primegen(1, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "");
    }

    SECTION("2")
    {
        PrimeNumberGenerator primegen(2, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "2 ");
    }

    SECTION("96")
    {
        PrimeNumberGenerator primegen(96, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 ");
    }

    SECTION("97")
    {
        PrimeNumberGenerator primegen(97, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 ");
    }

    SECTION("100")
    {
        PrimeNumberGenerator primegen(100, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 ");
    }

    SECTION("1000")
    {
        PrimeNumberGenerator primegen(1000, out);
        primegen.segmentedSieve();
        REQUIRE(out.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 "
        "67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 "
        "163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 "
        "263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 "
        "373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 "
        "479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 "
        "601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 "
        "719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 "
        "839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 "
        "971 977 983 991 997 ");
    }
}
