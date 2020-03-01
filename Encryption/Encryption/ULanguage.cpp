#include "ULanguage.h"


std::string ULanguage::Encode(std::string& toEncode)
{
	bool wordStart = true;
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		if (wordStart)
		{
			wordStart = false;

			if (WordHelper::charIsVocal(toEncode.at(i)))
			{
				if (isupper(toEncode.at(i)))
					output.append("U");
				else
					output.append("u");

				continue;
			}
			output.append("U");
		}
		else if ((isspace(toEncode.at(i)) || toEncode.at(i) == '\n') && i != toEncode.length() - 1 && !(isspace(toEncode.at(i + 1)) || toEncode.at(i + 1) == '\n'))
			wordStart = true;
		
		char temp = (char)(tolower(toEncode.at(i)));

		output.push_back(temp);
	}

	return output;
}

std::string ULanguage::Decode(std::string& toDecode)
{
	std::string output;
	bool wordStart = true;

	for (int i = 0; i < toDecode.length(); i++)
	{
		if (wordStart && tolower(toDecode.at(i)) == tolower('u'))
		{
			// As it is impossible to find out if the U replaced a vocal, therefore
			// we give the vocals as a possible answer
			if (islower(toDecode.at(i)))
				output.append("(a/e/i/o/u)");
			else
				output.append("(A/E/I/O/U)");

			wordStart = false;

			continue;
		}
		else if (wordStart && tolower(toDecode.at(i)) != tolower('u'))
			return "Algorithm not applicable";
		else if ((isspace(toDecode.at(i)) || toDecode.at(i) == '\n') && i != toDecode.length() - 1 && !(isspace(toDecode.at(i + 1)) || toDecode.at(i + 1) == '\n'))
			wordStart = true;

		output.push_back(toDecode.at(i));
	}

	return output;
}


