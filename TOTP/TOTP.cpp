#include <time.h>
#include "sha1.h"
#include "TOTP.h"

//
// Inline function definitions
//

inline unsigned int max( unsigned int x, unsigned int y) {
	return (x > y ? x : y);
}

inline std::string xor (std::string left, std::string right) {
	std::string result = "";

	const unsigned int limit = max(left.length(), right.length());
	for (size_t i = 0; i < limit; ++i) {

		result += left.at( i%left.length() ) ^ right.at( i%right.length() );

	}

	return result;
}

//
// TOTPConf structure definition
//

TOTPConf::TOTPConf(std::string key, int blocksize, unsigned int epoch, unsigned int interval, unsigned int margin) {
	this->key = key;
	this->blocksize = blocksize;
	this->epoch = epoch;
	this->interval = interval;
	this->margin = margin;
}

TOTPConf::TOTPConf(TOTPConf* config) {
	this->key = config->key;
	this->blocksize = config->blocksize;
	this->epoch = config->epoch;
	this->interval = config->interval;
	this->margin = config->margin;
}

//
// TOTP Class definition
//

TOTP::TOTP(TOTPConf config) {
	this->config = new TOTPConf(config);
}

TOTP::~TOTP() {
	delete this->config;
}

std::string TOTP::operator()(){
	return this->generate( time(nullptr) );
}

bool TOTP::validate(std::string token) {
	double now = time(nullptr);
	double margin = now - this->config->margin;

	return ( token == this->generate(now) || token == this->generate(margin) );
}

std::string TOTP::hash(std::string message) {
	return sha1(message);
}

std::string TOTP::hmac(std::string key, std::string message) {

	if (key.length() < this->config->blocksize) {
		key = this->hash(key + std::string(this->config->blocksize - key.length(), (char)0x00));
	}
	else {
		key = this->hash(key);
	}

	std::string o_key_pad = xor (std::string(this->config->blocksize, (char)0x5c), key);
	std::string i_key_pad = xor (std::string(this->config->blocksize, (char)0x36), key);

	return this->hash(o_key_pad + this->hash(i_key_pad + message));
}

std::string TOTP::generate(double when) {
	double tc = floor((when - this->config->epoch) / this->config->interval);
	return this->hmac(this->config->key, std::to_string(tc));
}

