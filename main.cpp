#include "primenumbergenerator.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	uint_fast64_t upperLimit = 0;
	uint_fast64_t number = 0;

	if (argc >= 2)
	{
		std::string arg(argv[1]);

		if (arg.find("-n") != std::string::npos)
		{
			std::cout << "Enter number: ";
			std::cin >> number;
			std::cout << "Next prime number: " << PrimeNumberGenerator::getNextPrimeNumber(number) << std::endl;
			return 0;
		}
		else if (arg.find("-t") != std::string::npos)
		{
			std::cout << "Enter number to test: ";
			std::cin >> number;
			std::cout << number << " is " << (PrimeNumberGenerator::isPrimeNumber(number) ? "" : "NOT ") << "a prime number" << std::endl;
			return 0;
		}
		else
		{
			upperLimit = std::stoull(arg, nullptr);
		}
	}
	else
	{
		std::cout << "Enter upper limit: ";
		std::cin >> upperLimit;
		std::cout << std::endl;
	}

	std::cout << "ココア：じゃあ、どっちがたくさん素数言えるか勝負だよ！\n";
	std::cout << "シャロ：なんで素数よ！？\n";
    std::cout << "ココア：";
	PrimeNumberGenerator cocoa(upperLimit);
	cocoa.segmentedSieve();
	std::cout << "\nシャロ：だからなんで素数よ！？\n";

	return 0;
}