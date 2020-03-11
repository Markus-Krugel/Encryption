#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Replaces an letter based on its alphabet position as a 5 bit binary with a and b's
// e.g. D is aaabb and Z is babbb
class BaconCode : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};