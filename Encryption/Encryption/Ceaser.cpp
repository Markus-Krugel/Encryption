#include "EncryptCommand.h"
#include <iostream>


// The alphabet is moved by 3 letters.
// e.g. 'A' is 'D' and 'Z' is 'C'

class Caeser : public EncryptCommand
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			std::string output;
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				if (isalpha(toEncode->at(i)))
				{
					for (size_t j = 0; j < alphabet.length(); j++)
					{
						if (toupper(toEncode->at(i)) == alphabet[j])
						{
							// if it extends the last letter of the alphabet, change to the start of the alphabet
							if (j + 3 > alphabet.size())
								output.push_back(alphabet[(j + 3) - alphabet.size()]);
							else 
								output.push_back(alphabet[(j + 3)]);

							// Ensures that the correct letter case is used
							if (islower(toEncode->at(i)))
								output[i] = tolower(output[i]);
						}
					}
				}
				else
					output.push_back(toEncode->at(i));
			}
	
			return output;
		}
	
		std::string EncodeFromeFile(const char* filePath)
		{
			std::string text;
	
			std::ifstream in(filePath, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				text.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&text[0], text.size());
				in.close();
			}
			else
				std::cout << "Could not open file !" << std::endl;
	
			return Encode(&text);
		}
	
		std::string Decode(std::string* toDecode)
		{
			std::string output;

			for (std::string::size_type i = 0; i < toDecode->length(); ++i)
			{
				if (isalpha(toDecode->at(i)))
				{
					for (size_t j = 0; j < alphabet.length(); j++)
					{
						if (toupper(toDecode->at(i)) == alphabet[j])
						{
							// if it extends the last letter of the alphabet, change to the start of the alphabet
							if ((j - 3) < 0)
								output.push_back(alphabet[alphabet.size() - (j - 3)]);
							else
								output.push_back(alphabet[(j - 3)]);

							// Ensures that the correct letter case is used
							if (islower(toDecode->at(i)))
								output[i] = tolower(output[i]);
						}
					}
				}
				else
					output.push_back(toDecode->at(i));
			}

			return output;
		}

		std::string DecodeFromeFile(const char* filePath)
		{
			std::string text;

			std::ifstream in(filePath, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				text.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&text[0], text.size());
				in.close();
			}
			else
				std::cout << "Could not open file !" << std::endl;

			return Encode(&text);
		}

	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

