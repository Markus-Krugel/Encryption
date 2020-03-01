#include "PolybiosCode.h"

std::string PolybiosCode::Encode(std::string& toEncode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (isalpha(toEncode.at(i)))
		{
			int alphPos = WordHelper::getAlphabetPosition(toEncode.at(i));
			
			// this is being done because i and j share the same cell
			// and therefore from j on every cell has to go one back
			if (alphPos >= 9)
				alphPos--;

			// the + '0' is to convert the int to a char because otherwise pushback would interpret it as an ascii character

			// the rounding up does not work if the number is divisible by 5
			if (alphPos % 5 == 0)
				output.push_back(((int)ceil((double)alphPos / 5) +1) + '0');
			else
				output.push_back(((int)ceil((double)alphPos / 5)) + '0');
			output.push_back(((alphPos % 5) + 1) + '0');
		}
		else
			output.push_back(toEncode.at(i));
	}

	return output;
}

std::string PolybiosCode::Decode(std::string& toDecode)
{
	std::string output;

	for (int i = 0; i < toDecode.length(); i++)
	{
		if(isalpha(toDecode.at(i)))
			return "Algorithm not applicable";

		if (isdigit(toDecode.at(i)) && isdigit(toDecode.at(i + 1)))
		{
			// the -'0' casts the char into an int otherwise it would read the ascii code
			int position = (((toDecode.at(i) - '0') - 1) * 5) + (toDecode.at(i + 1) - '0') - 1;
			if (position > 8)
				position++;

			// As i and j share the same cell it can be either i or j therefore we present both options
			if (position == 8)
				output.append("(i/j)");
			else
				output.push_back(WordHelper::getCharAtAlphabetPosition(position, true));

			i++;
		}
		else
			output.push_back(toDecode.at(i));
	}

	return output;
}


