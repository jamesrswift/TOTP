#include "TOTP.h"
#include <iostream>
#include <string>
#include <windows.h>

int main()
{

	std::string SecretKey("Hello, World!");

	while (true) {
		std::cout << TOTP(SecretKey) << std::endl;
		Sleep(30000);
	}

	return 0;
}

