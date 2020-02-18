#include "VigenereCipher.h"


std::string VigenereCipher::Encode(std::string& toEncode)
{
	return Encode(toEncode, (std::string&) "code");
}

std::string VigenereCipher::Encode(std::string& toEncode, std::string& codeword)
{
	std::string output;

	if (codeword == "")
		return "Codeword needed.";

	// stores the position of the codeword so that you dont enocode non alpha chars
	int codePosition = 0;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (isalpha(toEncode.at(i)))
		{
			int encodeAlpPos = WordHelper::getAlphabetPosition(toEncode.at(i));
			int codeAlpPos = WordHelper::getAlphabetPosition(codeword.at(codePosition));

			int position = encodeAlpPos + codeAlpPos;

			// if over alphabet size then start at the beginning of alphabet
			if (position >= 26)
				position = position - 26;

			output.push_back(WordHelper::getCharAtAlphabetPosition(position, islower(toEncode.at(i))));

			if (codePosition == codeword.length() - 1)
				codePosition = 0;
			else
				codePosition++;
		}
		else
		{
			output.push_back(toEncode.at(i));
		}
	}

	return output;
}

std::string VigenereCipher::Decode(std::string& toEncode)
{
	return Decode(toEncode, (std::string&) "code");
}

std::string VigenereCipher::Decode(std::string& toDecode, std::string& codeword)
{
	std::string output;

	// stores the position of the codeword so that you dont enocode non alpha chars
	int codePosition = 0;

	for (std::string::size_type i = 0; i < toDecode.length(); ++i)
	{
		if (isalpha(toDecode.at(i)))
		{
			int decodeAlpPos = WordHelper::getAlphabetPosition(toDecode.at(i));
			int codeAlpPos = WordHelper::getAlphabetPosition(codeword.at(codePosition));

			int position = decodeAlpPos - codeAlpPos;

			if (position < 0)
				position = 26 + position;

			output.push_back(WordHelper::getCharAtAlphabetPosition(position, islower(toDecode.at(i))));

			if (codePosition == codeword.length() - 1)
				codePosition = 0;
			else
				codePosition++;
		}
		else
		{
			output.push_back(toDecode.at(i));
		}
	}

	return output;
}
