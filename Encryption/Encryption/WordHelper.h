#pragma once
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

struct TextData
{
	static const int maxTextSize = 1000;
	std::vector<int> wordsLength;

	// !!!IMPORTANT!!! call UpdateContent if you change the content of the reference
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

	void UpdateContent()
	{
		int wordStartPos = 0;

		wordsLength.clear();

		for (int i = 0; i < content.length(); i++)
		{
			if (content.at(i) == (char)' ' || content.at(i) == (char)'\n')
			{
				wordsLength.push_back(i - wordStartPos);
				wordStartPos = i + 1;
			}
		}

		//for single words
		if (wordsLength.empty() && content != "")
			wordsLength.push_back(content.length());


		length = content.length();
	}

	void SetContent(std::string newContent)
	{
		content = newContent;
		UpdateContent();
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

	static void EraseNewLinesAndSpaces(std::string& mainStr);

private:
	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;

	static void FormatText(TextData& textInput, std::vector<int> formatting);
};

