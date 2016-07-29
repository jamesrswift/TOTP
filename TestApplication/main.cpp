/*
TOTP - A time based one time password generator library
Copyright(C) 2016, James Rupert Swift

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#include "TOTP.h"
#include "sha1/sha1.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace TOTP_Library;

struct TOTPConf_sha1 : public TOTPConf {
	TOTPConf_sha1(std::string key) : TOTPConf(key, sha1) {
		setPadding(0x11, 0x55);
		blocksize = 64;
	}
};

int main()
{
	std::cout << "TOTP Copyright (C) 2016, James Rupert Swift" << std::endl;
	std::cout << "This program comes with ABSOLUTELY NO WARRANTY" << std::endl;
	std::cout << "This is free software, and you are welcome to redistribute it under certain conditions" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	TOTP MyTokenGenerator(TOTPConf_sha1("This is my secret key"));
	std::string token = MyTokenGenerator();

	while (true) {
		std::cout << "Current token is " << MyTokenGenerator() << std::endl;
		std::cout << "Is token valid? " << (MyTokenGenerator.validate(token) ? "true" : "false") << std::endl;
		std::cout << std::endl;

		Sleep(1000);
	}

	return 0;
}
