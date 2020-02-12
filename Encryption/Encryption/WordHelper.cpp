#include "WordHelper.h"
#pragma warning(disable : 4996)

	int WordHelper::getAlphabetPosition(char letter)
	{
		int decimalOfChar = int(letter);

		if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
			return decimalOfChar - decimalStartUpperletter;
		else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
			return decimalOfChar - decimalStartLowerletter;
	}

	char WordHelper::getCharAtAlphabetPosition(int position, bool lowerCase)
	{
		if (lowerCase)
			return decimalStartLowerletter + position;
		else
			return decimalStartUpperletter + position;
	}

	char WordHelper::getCharAtReverseAlphabetPosition(int position, bool lowerCase)
	{
		if (lowerCase)
			return decimalEndLowerletter - position;
		else
			return decimalEndUpperletter - position;
	}

	void WordHelper::transformStringToChar(std::string& text,char* outChar)
	{
		strcpy(outChar, text.c_str());
	}


	bool WordHelper::charIsVocal(char* letter)
	{
		int decimalOfChar = int(letter);

		if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
			return decimalOfChar == 65 || decimalOfChar == 69 || decimalOfChar == 73|| decimalOfChar == 79 || decimalOfChar == 85;
		else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
			return decimalOfChar == 97 || decimalOfChar == 101 || decimalOfChar == 105 || decimalOfChar == 111 || decimalOfChar == 117;

		return false;
	}

	bool WordHelper::WordOnlyContainsAandBs(std::string* toDecode)
	{
		for (size_t i = 0; i < toDecode->length(); i++)
		{
			if (isalpha(toDecode->at(i)) && toDecode->at(i) != 'a' && toDecode->at(i) != 'b')
				return false;
		}

		return true;
	}

	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;
