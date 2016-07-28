#pragma once
#include <string>

#define TOTP_BLOCKSIZE 1024
#define TOTP_EPOCH 0
#define TOTP_INTERVAL 30

std::string hash(std::string message);
std::string hmac(std::string key, std::string message);
std::string TOTP(std::string key);