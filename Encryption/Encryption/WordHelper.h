#pragma once
#include <string>

class WordHelper
{
public:
	static int getAlphabetPosition(char letter);

	static char getCharAtAlphabetPosition(int position, bool lowerCase);

	static char getCharAtReverseAlphabetPosition(int position, bool lowerCase);

	static void transformStringToChar(std::string& text, char* outChar);

	static bool charIsVocal(char* letter);

	static bool WordOnlyContainsAandBs(std::string* toDecode);

private:
	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;
};

