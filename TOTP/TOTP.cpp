#include "TOTP.h"
#include "sha1.h"
#include <time.h>
#include <iostream>

std::string hash(std::string message) {
	return sha1(message);
}

inline unsigned int max( unsigned int x, unsigned int y) {
	return (x > y ? x : y);
}

inline std::string xor (std::string left, std::string right) {
	std::string result = "";

	const unsigned int limit = max(left.length(), right.length());
	for (size_t i = 0; i < limit; ++i) {

		result +=
			( i > left.length() ? (char) 0x00 : left.at(i) ) ^
			( i > right.length() ? (char) 0x00 : right.at(i) );

	}

	return result;
}

std::string hmac(std::string key, std::string message) {
	if (key.length() > TOTP_BLOCKSIZE) {
		key = hash(key);
	}else if(key.length() < TOTP_BLOCKSIZE) {
		key = key + std::string(TOTP_BLOCKSIZE - key.length(), (char) 0x00);
	}

	std::string o_key_pad = xor(std::string(TOTP_BLOCKSIZE, (char)0x5c), key);
	std::string i_key_pad = xor(std::string(TOTP_BLOCKSIZE, (char)0x36), key);

	return hash(o_key_pad + hash(i_key_pad + message));
}

std::string TOTP(std::string key) {
	double tc = floor((time(nullptr) - TOTP_EPOCH) / TOTP_INTERVAL);
	std::string TOTP_var = hmac(key, std::to_string(tc));

	return TOTP_var;
}