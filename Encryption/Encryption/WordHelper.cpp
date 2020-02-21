#include "WordHelper.h"
#pragma warning(disable : 4996)

	int WordHelper::getAlphabetPosition(char letter)
	{
		int decimalOfChar = int(letter);

		if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
			return decimalOfChar - decimalStartUpperletter;
		else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
			return decimalOfChar - decimalStartLowerletter;
	}

	char WordHelper::getCharAtAlphabetPosition(int position, bool lowerCase)
	{
		if (lowerCase)
			return decimalStartLowerletter + position;
		else
			return decimalStartUpperletter + position;
	}

	char WordHelper::getCharAtReverseAlphabetPosition(int position, bool lowerCase)
	{
		if (lowerCase)
			return decimalEndLowerletter - position;
		else
			return decimalEndUpperletter - position;
	}

	void WordHelper::transformStringToChar(std::string& text,char* outChar)
	{
		strcpy(outChar, text.c_str());
	}


	bool WordHelper::charIsVocal(char* letter)
	{
		int decimalOfChar = int(letter);

		if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
			return decimalOfChar == 65 || decimalOfChar == 69 || decimalOfChar == 73|| decimalOfChar == 79 || decimalOfChar == 85;
		else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
			return decimalOfChar == 97 || decimalOfChar == 101 || decimalOfChar == 105 || decimalOfChar == 111 || decimalOfChar == 117;

		return false;
	}

	bool WordHelper::WordOnlyContainsAandBs(std::string* toDecode)
	{
		for (size_t i = 0; i < toDecode->length(); i++)
		{
			if (isalpha(toDecode->at(i)) && toDecode->at(i) != 'a' && toDecode->at(i) != 'b')
				return false;
		}

		return true;
	}

	std::vector<std::string> WordHelper::SplitText(std::string& text)
	{
		std::string delimiter = " ";

		size_t pos = 0;
		std::vector<std::string> output;

		// Have a rough pre allocation
		output.reserve(text.length() / 7);

		while ((pos = text.find(delimiter)) != std::string::npos) {
			output.push_back(text.substr(0, pos));
			text.erase(0, pos + delimiter.length());
		}

		return output;
	}

    void WordHelper::EraseNewLines(std::string& str)
    {
        std::regex newlines_re("\n+");

        str = std::regex_replace(str, newlines_re, "");
    }

    // from https://www.geeksforgeeks.org/word-wrap-problem-dp-19/

    std::string WordHelper::SolveWordWrap(std::vector<std::string>& textInput, int k)
    {
        int i, j;

        int textInputSize = textInput.size();

        std::vector<int> output;
        output.reserve(textInputSize);

        // Variable to store number of 
        // characters in given line. 
        int currlen;

        // Variable to store possible 
        // minimum cost of line. 
        int cost;

        // DP table in which dp[i] represents 
        // cost of line starting with word 
        // arr[i]. 
        std::vector<int> dp;
        dp.resize(textInputSize);

        // Array in which ans[i] store index 
        // of last word in line starting with 
        // word arr[i]. 
        std::vector<int> ans;
        ans.resize(textInputSize);

        // If only one word is present then 
        // only one line is required. Cost 
        // of last line is zero. Hence cost 
        // of this line is zero. Ending point 
        // is also n-1 as single word is 
        // present. 
        dp[textInputSize - 1] = 0;
        ans[textInputSize - 1] = textInputSize - 1;

        // Make each word first word of line 
        // by iterating over each index in arr. 
        for (i = textInputSize - 2; i >= 0; i--) {
            currlen = -1;
            dp[i] = INT_MAX;

            // Keep on adding words in current 
            // line by iterating from starting 
            // word upto last word in arr. 
            for (j = i; j < textInputSize; j++) {

                // Update number of characters 
                // in current line. arr[j] is 
                // number of characters in 
                // current word and 1 
                // represents space character 
                // between two words. 
                currlen += (textInput[j].length() + 1);

                // If limit of characters 
                // is violated then no more 
                // words can be added to 
                // current line. 
                if (currlen > k)
                    break;

                // If current word that is 
                // added to line is last 
                // word of arr then current 
                // line is last line. Cost of 
                // last line is 0. Else cost 
                // is square of extra spaces 
                // plus cost of putting line 
                // breaks in rest of words 
                // from j+1 to n-1. 
                if (j == textInputSize - 1)
                    cost = 0;
                else
                    cost = (k - currlen) * (k - currlen) + dp[j + 1];

                // Check if this arrangement gives 
                // minimum cost for line starting 
                // with word arr[i]. 
                if (cost < dp[i]) {
                    dp[i] = cost;
                    ans[i] = j;
                }
            }
        }

        // Store starting index and ending index 
        // of words present in each line. 
        i = 0;
        while (i < textInputSize) {
            output.push_back(i);
            output.push_back(ans[i]);
            i = ans[i] + 1;
        }

        return FormatText(textInput, output);
    }

    std::string WordHelper::FormatText(std::vector<std::string>& textInput, std::vector<int> formatting)
    {
        std::string output;

        for (size_t i = 0; i < formatting.size(); i +=2)
        {
            for (size_t j = formatting[i]; j <= formatting[i+1]; j++)
            {
                output.append(textInput[j]+ " ");
            }
            output.append("\n");
        }

        return output;
    }