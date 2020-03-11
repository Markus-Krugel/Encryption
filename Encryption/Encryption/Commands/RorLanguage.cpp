#include "RorLanguage.h"


std::string RorLanguage::Encode(std::string& toEncode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		output.push_back(toEncode.at(i));

		if (isalpha(toEncode.at(i)) && !WordHelper::charIsVocal(toEncode.at(i)))
		{
			output.append("o");
			// lower letter because it does look less obvious if word starts with consonant
			output.push_back(tolower(toEncode.at(i)));
		}
	}

	return output;
}

std::string RorLanguage::Decode(std::string& toDecode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toDecode.length(); ++i)
	{
		output.push_back(toDecode.at(i));

		if (isalpha(toDecode.at(i)) && !WordHelper::charIsVocal(toDecode[i]))
		{
			char n = toDecode.at(i);
			if (toDecode.at(i + 1) == 'o' && tolower(toDecode.at(i)) == toDecode.at(i + 2))
				i += 2;
			else
				return "Algorithm not applicable";
		}
	}

	return output;
}
