#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Replaces letters with the letter from the other side of the alphabet.
// e.g 'A' with 'Z' and 'G' with 'T'
class Atbasch : public EncryptCommand
{
public:

	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};