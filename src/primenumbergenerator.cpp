#include "primenumbergenerator.h"
#include <algorithm>
#include <iostream>
#include <cmath>

PrimeNumberGenerator::PrimeNumberGenerator(uint_fast64_t limit, std::ostream &output)
        : upperLimit(limit), out(output)
{
    segmentSize = sqrt(upperLimit);
}

void PrimeNumberGenerator::simpleSieve()
{
    isPrime1stSegment.assign(segmentSize + 1, true); // [0, Nsqrt]
    isPrime1stSegment[0] = false;
    isPrime1stSegment[1] = false;

    for (uint_fast64_t p = 2; p <= segmentSize; ++p)
    {
        if (isPrime1stSegment[p])
        {
            out << p << " ";

            for (uint_fast64_t multiple = p * p; multiple <= segmentSize; multiple += p)
            {
                isPrime1stSegment[multiple] = false;
            }
        }
    }
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
        std::vector<bool> isPrimeCurrentSegment(high - low + 1, true);

        for (uint_fast64_t p = 2; p <= segmentSize; ++p)
        {
            if (isPrime1stSegment[p])
            {
                for (uint_fast64_t multiple = getNextMultiple(low, p); multiple <= high; multiple += p)
                {
                    isPrimeCurrentSegment[multiple - low] = false;
                }
            }
        }

        print(isPrimeCurrentSegment, low);
    }
}

void PrimeNumberGenerator::print(const std::vector<bool> &isPrime, uint_fast64_t offset)
{
    for (std::size_t i = 0; i < isPrime.size(); ++i)
    {
        if (isPrime[i])
            out << i + offset << " ";
    }
}

bool PrimeNumberGenerator::isPrime(uint_fast64_t number)
{
    if (number <= 1)
        return false;
    else if (number <= 3)
        return true;
    else if (number % 2 == 0 || number % 3 == 0)
        return false;

    for (uint_fast64_t i = 5; i * i <= number; i = i + 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }

    return true;
}

uint_fast64_t PrimeNumberGenerator::getNextPrime(uint_fast64_t number)
{
    for (uint_fast64_t i = number + 1;; ++i)
    {
        if (isPrime(i))
            return i;
    }
}

uint_fast64_t PrimeNumberGenerator::getNextMultiple(uint_fast64_t number, uint_fast64_t factor)
{
    return (number + factor - 1) / factor * factor;
}
