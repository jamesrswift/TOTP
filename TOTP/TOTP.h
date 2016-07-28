#pragma once
#include <string>

struct TOTPConf {
	TOTPConf(unsigned int blocksize, unsigned int epoch, unsigned int interval);
	TOTPConf(TOTPConf* config);

	unsigned int blocksize;
	unsigned int epoch;
	unsigned int interval;
};

class TOTP {
public:
	TOTP();
	TOTP(TOTPConf config);
	~TOTP();

	std::string operator()(std::string key);
	std::string get(std::string key);
private:
	TOTPConf* config;

	std::string hash(std::string message);
	std::string hmac(std::string key, std::string message);
};
