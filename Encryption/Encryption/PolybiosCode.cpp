#include "EncryptCommand.h"
#include <iostream>


// Stores the alphabet in a 5x5 table where i and j shares the same cell . The row is the ten's digit and the column the single unit.

class PolybiosCode : public EncryptCommand
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
							// this is being done because i and j share the same cell
							// and therefore from j on every cell has to go one back
							if (j >= 9)
								j--;
	
							// the + '0' is to convert the int to a char because otherwise pushback would interpret it as an ascii character
	
							// the rounding up does not work if the number is divisible by 5
							if (j % 5 == 0)
								output.push_back(((int)ceil((double)j / 5) +1) + '0');
							else
								output.push_back(((int)ceil((double)j / 5)) + '0');
							output.push_back(((j % 5) + 1) + '0');
							break;
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

			for (size_t i = 0; i < toDecode->length(); i++)
			{
				if(isalpha(toDecode->at(i)))
					return "Algorithm not applicable";

				if (isdigit(toDecode->at(i)) && isdigit(toDecode->at(i + 1)))
				{
					// the -'0' casts the char into an int otherwise it would read the ascii code
					int position = (((toDecode->at(i) - '0') - 1) * 5) + (toDecode->at(i + 1) - '0') - 1;
					if (position > 8)
						position++;

					// As i and j share the same cell it can be either i or j therefore we present both options
					if (position == 8)
						output.append("(i/j)");
					else
						output.push_back(alphabet[position]);

					i++;
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

			return Decode(&text);
		}
	
	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

