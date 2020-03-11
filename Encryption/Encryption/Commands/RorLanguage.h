#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Adds an 'o' after every consonant and repeats the consonant.
class RorLanguage : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};