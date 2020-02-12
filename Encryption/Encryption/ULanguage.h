#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Adds an 'U' to the beginning of a word, if the word starts with
// a vocal it replaces it with an 'U'.

class ULanguage : public EncryptCommand
{
public:

	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};