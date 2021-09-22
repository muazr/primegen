#include "primenumbergenerator.h"
#include <iostream>
#include <string>
#include <unistd.h>

enum class Mode
{
	GeneratePrimes,
	PrimalityTest,
	NextPrime
};

int main(int argc, char *argv[])
{
	uint_fast64_t number = 0;

	Mode mode = Mode::GeneratePrimes;
	int c = -1;

	while ((c = getopt(argc, argv, "nth")) != -1)
	{
		switch (c)
		{
			case 'n':
				mode = Mode::NextPrime;
				break;
			case 't':
				mode = Mode::PrimalityTest;
				break;
			case '?':
				if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,
							"Unknown option character `\\x%x'.\n",
							optopt);
			case 'h':
			default :
				printf("Help/Usage Example\n");
				return 0;
		}
	}

	if (optind >= argc)
	{
        fprintf(stderr, "Expected argument after options\n");
        return 0;
    }

	number = std::stoull(argv[optind], nullptr);
	
	PrimeNumberGenerator cocoa(number);

	switch (mode)
	{
		case Mode::PrimalityTest:
			std::cout << number << " is " << (cocoa.isPrime(number) ? "" : "NOT ") << "a prime number" << std::endl;
			break;
		case Mode::NextPrime:
			std::cout << "Next prime number: " << cocoa.getNextPrime(number) << std::endl;
			break;
		case Mode::GeneratePrimes:
		default:
			std::cout << "ココア：じゃあ、どっちがたくさん素数言えるか勝負だよ！\n";
			std::cout << "シャロ：なんで素数よ！？\n";
			std::cout << "ココア：";
			cocoa.segmentedSieve();
			std::cout << "\nシャロ：だからなんで素数よ！？\n";
			break;
	}

	return 0;
}