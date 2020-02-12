#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Adds a 'bi' after every vocal.

class BiLanguage : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};