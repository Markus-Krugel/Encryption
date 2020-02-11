#include "WordHelper.h"

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

	char* WordHelper::transformStringToChar(std::string& text)
	{
		char* output = reinterpret_cast<char*> (&text);

		return output;
	}

	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;
