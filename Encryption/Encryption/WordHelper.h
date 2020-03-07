#pragma once
#include <string>
#include <vector>
#include <regex>

struct TextData
{
	static const int maxTextSize = 1000;
	std::vector<int> wordsLength;

	std::string& GetContent()
	{
		return content;
	}

	int GetLength()
	{
		// length could be wrong as you can change the content via the getContent function, alternative would be for the getter to return
		// a copy, would be too costly for long strings

		if (length != content.size())
			length = content.size();

		return length;
	}

	void SetContent(std::string newContent)
	{
		if (newContent == content)
			return;

		wordsLength.clear();
		int wordStartPos = 0;

		for (int i = 0; i < newContent.length(); i++)
		{
			if (newContent.at(i) == (char)' ' || newContent.at(i) == (char)'\n')
			{
				wordsLength.push_back(i - wordStartPos);
				wordStartPos = i + 1;
			}
		}
		length = newContent.length();
		content = newContent;
	}

private:
	std::string content;
	int length;
};

class WordHelper
{
public:
	static int getAlphabetPosition(char letter);

	static char getCharAtAlphabetPosition(int position, bool lowerCase);

	static char getCharAtReverseAlphabetPosition(int position, bool lowerCase);

	static void transformStringToChar(std::string& text, char* outChar);

	static bool charIsVocal(char letter);

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

