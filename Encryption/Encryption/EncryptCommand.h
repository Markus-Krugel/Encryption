#pragma once
#include <string>
#include <fstream>

class EncryptCommand
{
	public:
		std::string Encode(std::string* toEncode);
		std::string EncodeFromeFile(const char* filePath);
		std::string Decode(std::string* toDecode);
		std::string DecodeFromeFile(const char* filePath);
	
	protected:
		char vocals[5]{ 'a','e','i','o','u' };
	
		// controls if the char is a vocal
		bool charIsVocal(char* startingChar)
		{			
			for (size_t i = 0; i < 5; i++)
			{
				// Sets the char to lowerletter to compare it
				if (tolower(*startingChar) == vocals[i])
					return true;
			}
	
			return false;
		}
};