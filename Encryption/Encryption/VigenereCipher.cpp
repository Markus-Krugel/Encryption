#include "EncryptCommand.h"
#include <iostream>
#include <vector>

// Stores the alphabet in a 5x5 table where i and j shares the same cell . The row is the ten's digit and the column the single unit.

class VigenereCipher
{
	public:
	
		std::string Encode(std::string* toEncode, std::string* codeword)
		{
			std::string output;

			std::vector<int> encodeToInt;
			std::vector<int> codeToInt;

			// store the alphabetical position of the letters in the words
			encodeToInt.reserve(toEncode->length());
			codeToInt.reserve(codeword->length());
	
			for (size_t i = 0; i < toEncode->length(); i++)
			{
				for (size_t j = 0; j < alphabet.length(); j++)
				{
					if (!isalpha(toEncode->at(i)))
					{
						encodeToInt.push_back(-1);	
						break;
					}
					else if(toupper(toEncode->at(i)) == alphabet[j])
					{
						encodeToInt.push_back(j);
						break;
					}
				}	
			}

			for (size_t i = 0; i < codeword->length(); i++)
			{
				for (size_t j = 0; j < alphabet.length(); j++)
				{
					if (!isalpha(codeword->at(i)))
					{
						codeToInt.push_back(-1);
						break;
					}
					else if (toupper(codeword->at(i)) == alphabet[j])
					{
						codeToInt.push_back(j);
						break;
					}
				}
			}

			// stores the position of the codeword so that you dont enocode non alpha chars
			int codePosition = 0;

			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				if (isalpha(toEncode->at(i)))
				{
					int position = encodeToInt[i] + codeToInt[codePosition];

					if (position >= alphabet.length())
						position = position - alphabet.length();

					// Ensures that the correct letter case is used
					if(isupper(toEncode->at(i)))
						output.push_back(alphabet[position]);
					else
						output.push_back(tolower(alphabet[position]));

					if (codePosition == codeToInt.size() - 1)
						codePosition = 0;
					else
						codePosition++;
				}
				else
				{
					output.push_back(toEncode->at(i));
				}
			}
	
			return output;
		}
	
		std::string EncodeFromeFile(const char* filePath, std::string* codeword)
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
	
			return Encode(&text, codeword);
		}
	
		std::string Decode(std::string* toDecode, std::string* codeword)
		{
			std::string output;

			std::vector<int> encodeToInt;
			std::vector<int> codeToInt;

			// store the alphabetical position of the letters in the words
			encodeToInt.reserve(toDecode->length());
			codeToInt.reserve(codeword->length());

			for (size_t i = 0; i < toDecode->length(); i++)
			{
				for (size_t j = 0; j < alphabet.length(); j++)
				{
					if (!isalpha(toDecode->at(i)))
					{
						encodeToInt.push_back(-1);
						break;
					}
					else if (toupper(toDecode->at(i)) == alphabet[j])
					{
						encodeToInt.push_back(j);
						break;
					}
				}
			}

			for (size_t i = 0; i < codeword->length(); i++)
			{
				for (size_t j = 0; j < alphabet.length(); j++)
				{
					if (!isalpha(codeword->at(i)))
					{
						codeToInt.push_back(-1);
						break;
					}
					else if (toupper(codeword->at(i)) == alphabet[j])
					{
						codeToInt.push_back(j);
						break;
					}
				}
			}

			// stores the position of the codeword so that you dont enocode non alpha chars
			int codePosition = 0;

			for (std::string::size_type i = 0; i < toDecode->length(); ++i)
			{
				if (isalpha(toDecode->at(i)))
				{
					int position = encodeToInt[i] - codeToInt[codePosition];

					if (position < 0)
						position = alphabet.length() + position;

					// Ensures that the correct letter case is used
					if (isupper(toDecode->at(i)))
						output.push_back(alphabet[position]);
					else
						output.push_back(tolower(alphabet[position]));

					if (codePosition == codeToInt.size() - 1)
						codePosition = 0;
					else
						codePosition++;
				}
				else
				{
					output.push_back(toDecode->at(i));
				}
			}

			return output;
		}
	
		std::string DecodeFromeFile(const char* filePath, std::string* codeword)
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

			return Decode(&text, codeword);
		}
	
	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

