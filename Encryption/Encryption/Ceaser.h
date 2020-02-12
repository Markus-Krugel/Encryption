#pragma once
#include "EncryptCommand.h"
#include <iostream>


// The alphabet is moved by x amount of letters.
// e.g. for x = 3 : 'A' is 'D' and 'Z' is 'C'

class Ceaser : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Encode(std::string& toEncode, int moveValue);
	std::string Decode(std::string& toDecode) override;
	std::string Decode(std::string& toDecode, int moveValue);
};