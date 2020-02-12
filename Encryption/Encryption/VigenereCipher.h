#pragma once
#include "EncryptCommand.h"
#include <iostream>
#include <vector>

// Looks up the encrypted char by looking at a table, where x and y coordinates are of the alphabet
// and then going to the crosspoint between the codeword and the word
// e.g. codeword "F" and Word "H" results to "M"

class VigenereCipher : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Encode(std::string& toEncode, std::string& codeWord);
	std::string Decode(std::string& toDecode) override;
	std::string Decode(std::string& toDecode, std::string& codeWord);
};