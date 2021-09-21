#include "primenumbergenerator.h"
#include <algorithm>
#include <iostream>
#include <cmath>

PrimeNumberGenerator::PrimeNumberGenerator(uint_fast64_t limit) : upperLimit(limit)
{
    segmentSize = sqrt(upperLimit);
}

void PrimeNumberGenerator::simpleSieve()
{
    isPrime.assign(segmentSize + 1, true); // [0, Nsqrt]
    isPrime[0] = false;
    isPrime[1] = false;

    for (uint_fast64_t p = 2; p <= segmentSize; ++p)
    {
        if (isPrime[p])
        {
            for (uint_fast64_t multiple = p * p; multiple <= segmentSize; multiple += p)
            {
                isPrime[multiple] = false;
            }
        }
    }

    print(isPrime, 0);
}

void PrimeNumberGenerator::segmentedSieve()
{
    uint_fast64_t low = 0;
    uint_fast64_t high = segmentSize;

    simpleSieve();

    while (high < upperLimit)
    {
        low = high + 1;
        high = std::min(low + segmentSize - 1, upperLimit);
        std::vector<bool> offsetIsPrime(high - low + 1, true);

        for (uint_fast64_t p = 2; p <= segmentSize; ++p)
        {
            if (isPrime[p])
            {
                for (uint_fast64_t multiple = getNextMultiple(low, p); multiple <= high; multiple += p)
                {
                    offsetIsPrime[multiple - low] = false;
                }
            }
        }

        print(offsetIsPrime, low);
    }
}

void PrimeNumberGenerator::print(const std::vector<bool> &array, uint_fast64_t offset)
{
    for (std::size_t i = 0; i < array.size(); ++i)
    {
        if (array[i])
        {
            std::cout << i + offset << " ";
        }
    }
}

bool PrimeNumberGenerator::isPrimeNumber(uint_fast64_t number)
{
    if (number < 2)
    {
        return false;
    }
    else if (number == 2)
    {
        return true;
    }

    uint_fast64_t squareRoot = sqrt(number);

    for (uint_fast64_t i = 2; i <= squareRoot; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}

uint_fast64_t PrimeNumberGenerator::getNextPrimeNumber(uint_fast64_t number)
{
    for (uint_fast64_t i = number + 1;; ++i)
    {
        if (isPrimeNumber(i))
        {
            return i;
        }
    }
}

uint_fast64_t PrimeNumberGenerator::getNextMultiple(uint_fast64_t numToRound, uint_fast64_t multiple)
{
    return (numToRound + multiple - 1) / multiple * multiple;
}
