#pragma once
#include <string>

struct TOTPConf {
	TOTPConf(std::string key, int blocksize, unsigned int epoch, unsigned int interval);
	TOTPConf(TOTPConf* config);

	std::string key;
	unsigned int blocksize;
	unsigned int epoch;
	unsigned int interval;
};

class TOTP {
public:
	TOTP(TOTPConf config);
	~TOTP();

	std::string operator()();
private:
	TOTPConf* config;

	std::string hash(std::string message);
	std::string hmac(std::string key, std::string message);
};
