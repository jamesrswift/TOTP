#include "TOTP.h"
#include <iostream>
#include <string>
#include <windows.h>

int main()
{

	TOTP MyTokenGenerator(TOTPConf("Hello, World!", 1024, 0, 1));

	while (true) {
		std::cout << MyTokenGenerator() << std::endl;
		Sleep(1000);
	}

	return 0;
}
