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

	// Updates the length of the words and the total length
	void UpdateContent()
	{
		int wordStartPos = 0;

		wordsLength.clear();

		for (int i = 0; i < content.length(); i++)
		{
			if (content.at(i) == (char)' ' || content.at(i) == (char)'\n' || i == content.length() -1)
			{
				wordsLength.push_back(i - wordStartPos);
				wordStartPos = i + 1;
			}
		}

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

	// Gets the alphabet position of an letter 
	static int getAlphabetPosition(char letter);

	// gets the letter at the wanted alphabet position
	static char getCharAtAlphabetPosition(int position, bool lowerCase);

	// gets the letter at the wanted alphabet position in reverse
	static char getCharAtReverseAlphabetPosition(int position, bool lowerCase);

	static bool charIsVocal(char letter);

	// needed for Bacon Code
	static bool WordOnlyContainsAandBs(std::string* toDecode);

	// Wraps the text according to the maximim line size
	static void SolveWordWrap(TextData& textInput, int linesize);

	// Erases (unncessary) spaces and new lines
	// Used before word wrapping
	static void EraseNewLinesAndSpaces(std::string& mainStr, bool eraseUnnecessarySpaces = true);

private:
	static const int decimalStartUpperletter = 65;
	static const int decimalEndUpperletter = 90;
	static const int decimalStartLowerletter = 97;
	static const int decimalEndLowerletter = 122;

	// Adds the new lines to the text
	// called by SolveWordWrap()
	static void FormatText(TextData& textInput, std::vector<int> formatting);
};

