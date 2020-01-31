#include "EncryptCommand.h"
#include <iostream>
#include <vector>

// Stores the word in a different order, where every x th char is grouped together

class Transposition
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			return Encode(toEncode, 5);
		}
	
		std::string Encode(std::string* toEncode, int optional)
		{
			std::string output;
			output.reserve(toEncode->length());
	
			std::vector<std::string> wordList;
			wordList.resize(optional);
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				int position = i % optional;
	
				wordList[position].push_back(toEncode->at(i));
			}
	
			for (size_t i = 0; i < wordList.size(); i++)
			{
				output.append(wordList[i]);
			}
	
			return output;
		}
	
		std::string EncodeFromeFile(const char* filePath)
		{
			return EncodeFromeFile(filePath, 5);
		}

		std::string EncodeFromeFile(const char* filePath, int optional)
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

			return Encode(&text, optional);
		}

		std::string Decode(std::string* filePath)
		{
			return Decode(filePath, 5);
		}
	
		std::string Decode(std::string* toDecode, int optional)
		{
			std::string output;
			output.resize(toDecode->length());

			int groupSize = ceil((double)toDecode->length() / optional);

			// There are possibly some columns which have one more char, as there aren't enough chars for thre remaining columns
			int countColumnsWithExtraChar = toDecode->length() % optional;

			int extra = 0;

			for (int i = 0; i < toDecode->length(); i++)
			{
				int group = (i + extra) / groupSize;
				int position = 0;

				//if(countColumnsWithLessChar < group)
				//	position = group + ((i % (groupSize)) * optional);
				//else
					position = group + (((i + extra) % groupSize) * optional);
				
				if(position >= toDecode->length())
				{
					extra ++;
					position = countColumnsWithExtraChar + extra;
				}

				output[position] = toDecode->at(i);
			}

			return output;
		}
	
		std::string DecodeFromeFile(const char* filePath)
		{
			return DecodeFromeFile(filePath, 5);
		}

		std::string DecodeFromeFile(const char* filePath, int optional)
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

			return Decode(&text, optional);
		}
};

