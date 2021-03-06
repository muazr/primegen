#include <vector>
#include <cstdint>
#include <iostream>

class PrimeNumberGenerator
{
private:
    uint_fast64_t upperLimit = 0;
    std::vector<bool> isPrime1stSegment;
    uint_fast64_t segmentSize = 0;
    std::ostream &out;
    void simpleSieve();
    void print(const std::vector<bool> &isPrime, uint_fast64_t offset);
    static uint_fast64_t getNextMultiple(uint_fast64_t number, uint_fast64_t factor);

public:
    PrimeNumberGenerator(uint_fast64_t limit, std::ostream &output = std::cout);
    void segmentedSieve();
    static bool isPrime(uint_fast64_t number);
    static uint_fast64_t getNextPrime(uint_fast64_t number);
};
