#include "Atbasch.h"

std::string Atbasch::Encode(std::string& toEncode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (isalpha(toEncode.at(i)))
		{
			int pos = WordHelper::getAlphabetPosition(toEncode.at(i));
			output.push_back(WordHelper::getCharAtReverseAlphabetPosition(pos, islower(toEncode.at(i))));					
		}
		else
			output.push_back(toEncode.at(i));
	}

	return output;
}

// its the same procedure as encoding
std::string Atbasch::Decode(std::string& toDecode)
{
	return Encode(toDecode);
}


