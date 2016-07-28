#include "TOTP.h"
#include <iostream>
#include <string>
#include <windows.h>

int main()
{

	std::string SecretKey("Hello, World!");
	TOTP MyGenerator(TOTPConf(1024, 0, 1));

	while (true) {
		std::cout << MyGenerator.get(SecretKey) << std::endl;
		Sleep(1000);
	}

	return 0;
}
