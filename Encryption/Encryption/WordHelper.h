#pragma once
#include <string>
#include <vector>
#include <regex>

struct TextData
{
	static const int maxTextSize = 1000;
	std::vector<int> wordsLength;
	int length;
	int lines = 1;

	std::string& GetContent()
	{
		return content;
	}

	void SetContent(std::string newContent)
	{
		if (newContent == content)
			return;

		wordsLength.clear();
		int wordStartPos = 0;

		for (size_t i = 0; i < newContent.length(); i++)
		{
			if (newContent.at(i) == (char)' ' || newContent.at(i) == (char)'\n')
			{
				// add a new line unless it is the last char of the string
				if (newContent.at(i) == (char)'\n' && i != newContent.length() - 1)
					lines++;

				wordsLength.push_back(i - wordStartPos);
				wordStartPos = i + 1;
			}
		}

		length = newContent.length();
		content = newContent;
	}

private:
	std::string content;
};

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

	static void SolveWordWrap(TextData& textInput, int k);

	static void EraseNewLines(std::string& mainStr);

private:
	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;

	static void FormatText(TextData& textInput, std::vector<int> formatting);
};

