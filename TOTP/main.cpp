#include "TOTP.h"
#include <iostream>
#include <string>
#include <Windows.h>

int main()
{

	TOTP MyTokenGenerator(TOTPConf("Hello, World!", 1024, 0, 10, 2));
	std::string token = MyTokenGenerator();

	while (true) {

		std::cout << "Current token is " << MyTokenGenerator() << std::endl;
		std::cout << "Is token valid? " << ( MyTokenGenerator.validate(token) ? "true" : "false" ) << std::endl;
		std::cout << std::endl;

		Sleep(1000);
	}

	return 0;
}
