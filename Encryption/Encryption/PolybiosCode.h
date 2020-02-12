#pragma once
#include "EncryptCommand.h"
#include <iostream>


// Stores the alphabet in a 5x5 table where i and j shares the same cell . The row is the ten's digit and the column the single unit.

class PolybiosCode : public EncryptCommand
{
public:
	std::string Encode(std::string& toEncode) override;
	std::string Decode(std::string& toDecode) override;
};