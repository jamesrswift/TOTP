# TOTP
Time-based one time password generator

This repository stores a library designed to generate time-based one-time-passwords, following as closely as possible the industry standard. This library allows you to specify the private key used, how often the tokens should change, the margin of error when validating tokens, among other options.

### Example usage

```cpp
TOTP MyTokenGenerator(TOTPConf("Hello, World!", 1024, 0, 10, 2, [](std::string message)->std::string{ return sha1(message); }));

std::string token = MyTokenGenerator();
std::cout << "Is token valid? " << (MyTokenGenerator.validate(token)) << std::endl;
```

An example console application can be found in the repository.

### Configuration Explained

```cpp
auto MyConfig = TOTPConf(
    "Hello, World!",                                              // The private key
    1024,                                                         // the blocksize
    0,                                                            // start of epoch, seconds since unix epoch when first time slot starts
    10,                                                           // interval between new time slots, this is the interval between new tokens
    2,                                                            // margin of error when validation tokens, in seconds.
    [](std::string message)->std::string{ return sha1(message); } // hashing algorithm to be used
);
```

### History

* Version 0.0.2 - Custom hashing algorithms may now by used
* Version 0.0.1 - Initial release.
