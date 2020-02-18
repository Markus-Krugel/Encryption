#include "Ceaser.h"

std::string Ceaser::Encode(std::string& toEncode)
{
	return Encode(toEncode, 3);
}

std::string Ceaser::Encode(std::string& toEncode, int moveAmount)
{
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (isalpha(toEncode.at(i)))
		{
			int alphPos = WordHelper::getAlphabetPosition(toEncode.at(i));
			
			// if it extends the last letter of the alphabet, change to the start of the alphabet
			if (alphPos + moveAmount >= 26)
				output.push_back(WordHelper::getCharAtAlphabetPosition(alphPos + moveAmount - 26, islower(toEncode.at(i))));
			else 
				output.push_back(WordHelper::getCharAtAlphabetPosition(alphPos + moveAmount, islower(toEncode.at(i))));;
		}
		else
			output.push_back(toEncode.at(i));
	}

	return output;
}

std::string Ceaser::Decode(std::string& toDecode)
{
	return Decode(toDecode, 3);
}

std::string Ceaser::Decode(std::string& toDecode, int moveAmount)
{
	std::string output;

	for (std::string::size_type i = 0; i < toDecode.length(); ++i)
	{
		if (isalpha(toDecode.at(i)))
		{
			int alphPos = WordHelper::getAlphabetPosition(toDecode.at(i));

			// if it extends the last letter of the alphabet, change to the start of the alphabet
			int temp = alphPos - moveAmount;

			if (temp < 0)
				output.push_back(WordHelper::getCharAtReverseAlphabetPosition(temp + 1, islower(toDecode.at(i))));
			else
				output.push_back(WordHelper::getCharAtAlphabetPosition(temp, islower(toDecode.at(i))));
		}
		else
			output.push_back(toDecode.at(i));
	}

	return output;
}
