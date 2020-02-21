#pragma once
#include <string>
#include <vector>
#include <regex>

class WordHelper
{
public:
	static int getAlphabetPosition(char letter);

	static char getCharAtAlphabetPosition(int position, bool lowerCase);

	static char getCharAtReverseAlphabetPosition(int position, bool lowerCase);

	static void transformStringToChar(std::string& text, char* outChar);

	static bool charIsVocal(char* letter);

	static bool WordOnlyContainsAandBs(std::string* toDecode);

	static std::vector<std::string> SplitText(std::string& text);

	static std::string SolveWordWrap(std::vector<std::string>& textInput, int k);

	static void EraseNewLines(std::string& mainStr);

private:
	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;

	static std::string FormatText(std::vector<std::string>& textInput, std::vector<int> formatting);
};

