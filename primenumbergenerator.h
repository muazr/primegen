#include <vector>
#include <cstdint>

class PrimeNumberGenerator
{
private:
    uint_fast64_t upperLimit = 0;
    std::vector<bool> isPrime;
    uint_fast64_t segmentSize = 0;
    void simpleSieve();
    void print(const std::vector<bool> &array, uint_fast64_t offset);
    uint_fast64_t getNextMultiple(uint_fast64_t numToRound, uint_fast64_t multiple);

public:
    PrimeNumberGenerator(uint_fast64_t limit);
    void segmentedSieve();
    static bool isPrimeNumber(uint_fast64_t number);
    static uint_fast64_t getNextPrimeNumber(uint_fast64_t number);
};
