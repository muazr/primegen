#include "primenumbergenerator.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <unistd.h>

enum class Mode
{
	GeneratePrimes,
	PrimalityTest,
	NextPrime
};

void printHelp()
{
	std::cout <<
		R"(Usage:
 prime-number-generator [-n|-t] NUM
 prime-number-generator -h

Generate prime numbers up to NUM.
Find the next prime number after NUM if -n is specified.
Test whether NUM is a prime number if -t is specified.

Options:
 -t		perform primality test on NUM
 -n		find the next prime number after NUM
 -h		display this help
)";
}

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
			if (isprint(optopt))
			{
				fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				printHelp();
				return EXIT_FAILURE;
			}
			else
			{
				fprintf(stderr,
						"Unknown option character '\\x%x'.\n",
						optopt);
				return EXIT_FAILURE;
			}
			break;
		case 'h':
		default:
			printHelp();
			return EXIT_SUCCESS;
		}
	}

	if (optind >= argc)
	{
		fprintf(stderr, "Expected argument after options\n");
		printHelp();
		return EXIT_FAILURE;
	}

	try
	{
		number = std::stoull(argv[optind], nullptr);
	}
	catch (const std::out_of_range &err)
	{
		std::cerr << "Argument value is out of range. Expected an integer between "
				  << std::numeric_limits<decltype(number)>::min()
				  << " and "
				  << std::numeric_limits<decltype(number)>::max() << "\n";
		printHelp();
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument &err)
	{
		std::cerr << "Argument is not an integer\n";
		printHelp();
		return EXIT_FAILURE;
	}

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
		std::cout << "Prime numbers:\n";
		cocoa.segmentedSieve();
		std::cout << std::endl;
		break;
	}

	return EXIT_SUCCESS;
}
