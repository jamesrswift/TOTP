#pragma once
#include <string>

struct TOTPConf {
	TOTPConf(std::string key, int blocksize, unsigned int epoch, unsigned int interval, unsigned int margin);
	TOTPConf(TOTPConf* config);

	std::string key;
	unsigned int blocksize;
	unsigned int epoch;
	unsigned int interval;
	unsigned int margin;
};

class TOTP {
public:
	TOTP(TOTPConf config);
	~TOTP();

	std::string operator()();
	bool validate(std::string token);
private:
	TOTPConf* config;

	std::string hash(std::string message);
	std::string hmac(std::string key, std::string message);
	std::string generate(double when);
};
