#pragma once
#include "EncryptCommand.h"
#include <iostream>
#include <vector>

// Stores the word in a different order, where every x th char is grouped together
class Transposition : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Encode(std::string& toEncode, int columns);
	std::string Decode(std::string& filePath) override;
	std::string Decode(std::string& toDecode, int columns);
};