#pragma once
#include <string>
#include <fstream>
#include "WordHelper.h"

class EncryptCommand
{
	public:
		virtual std::string Encode(std::string& toEncode) { return ""; };
		virtual std::string Decode(std::string& toDecode) { return ""; };
};