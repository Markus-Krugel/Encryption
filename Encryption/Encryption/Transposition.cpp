#include "Transposition.h"

std::string Transposition::Encode(std::string& toEncode)
{
	return Encode(toEncode, 5);
}

std::string Transposition::Encode(std::string& toEncode, int columns)
{
	std::string output;
	output.reserve(toEncode.length());

	std::vector<std::string> wordList;
	wordList.resize(columns);

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		int position = i % columns;

		wordList[position].push_back(toEncode.at(i));
	}

	for (int i = 0; i < wordList.size(); i++)
	{
		output.append(wordList[i]);
	}

	return output;
}

std::string Transposition::Decode(std::string& filePath)
{
	return Decode(filePath, 5);
}

std::string Transposition::Decode(std::string& toDecode, int columns)
{
	std::string output;
	output.resize(toDecode.length());

	int groupSize = ceil((double)toDecode.length() / columns);

	// There are possibly some columns which have one more char, as there aren't enough chars for thre remaining columns
	int countColumnsWithExtraChar = toDecode.length() % columns;

	int extra = 0;

	for (int i = 0; i < toDecode.length(); i++)
	{
		int group = (i + extra) / groupSize;
		int position = 0;

		//if(countColumnsWithLessChar < group)
		//	position = group + ((i % (groupSize)) * columns);
		//else
			position = group + (((i + extra) % groupSize) * columns);
		
		if(position >= toDecode.length())
		{
			extra ++;
			position = countColumnsWithExtraChar + extra;
		}

		output[position] = toDecode.at(i);
	}

	return output;
}

