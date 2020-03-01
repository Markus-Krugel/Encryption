#include "BiLanguage.h"

std::string BiLanguage::Encode(std::string& toEncode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toEncode.length(); ++i)
	{
		output.push_back(toEncode.at(i));

		if (WordHelper::charIsVocal(toEncode.at(i)))
		{
			output.append("bi");
		}
	}

	return output;
}

std::string BiLanguage::Decode(std::string& toDecode)
{
	std::string output;

	for (std::string::size_type i = 0; i < toDecode.length(); ++i)
	{
		output.push_back(toDecode.at(i));

		if (isalpha(toDecode.at(i)) && WordHelper::charIsVocal(toDecode.at(i)))
		{
			if (toDecode.at(i + 1) == 'b' && tolower(toDecode.at(i + 2)) == 'i')
				i += 2;
			else
				return "Algorithm not applicable";
		}
	}

	return output;
}


