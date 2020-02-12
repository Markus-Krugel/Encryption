#include "BaconCode.h"

std::string BaconCode::Encode(std::string& toEncode)
{
	std::string output;

	// as this is a 5 bit binary code it has 32 options maximum
	int numberOfOptions = 32;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (isalpha(toEncode.at(i)))
		{
			int alpPos = WordHelper::getAlphabetPosition(toEncode.at(i));

			if (alpPos < numberOfOptions / 2)
				output.push_back('a');
			else
				output.push_back('b');

			if ((alpPos % 16) < 8)
				output.push_back('a');
			else
				output.push_back('b');

			if ((alpPos % 8) < 4)
				output.push_back('a');
			else
				output.push_back('b');

			if ((alpPos % 4) < 2)
				output.push_back('a');
			else
				output.push_back('b');

			if (alpPos % 2 == 0)
				output.push_back('a');
			else
				output.push_back('b');
			
			break;
		}
		else
			output.push_back(toEncode.at(i));
	}

	return output;
}

std::string BaconCode::Decode(std::string& toDecode)
{
	std::string output;

	int position = 0;

	if(!WordHelper::WordOnlyContainsAandBs(&toDecode))
		return "Algorithm not applicable";
	else
	{
		for (std::string::size_type i = 0; i < toDecode.length(); i ++)
		{
			if (isalpha(toDecode.at(i)))
			{
				position = 0;

				if (toDecode.at(i) == 'b')
					position += 16;

				if (toDecode.at(i + 1) == 'b')
					position += 8;

				if (toDecode.at(i + 2) == 'b')
					position += 4;

				if (toDecode.at(i + 3) == 'b')
					position += 2;

				if (toDecode.at(i + 4) == 'b')
					position += 1;

				output.push_back(WordHelper::getCharAtAlphabetPosition(position, true));

				i += 4;
			}
			else
				output.push_back(toDecode.at(i));
		}
	}

	return output;
}
