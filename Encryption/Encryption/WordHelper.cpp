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

	bool WordHelper::charIsVocal(char letter)
	{
		int decimalOfChar = int(letter);

		if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
			return decimalOfChar == (unsigned char)'A' || decimalOfChar == (unsigned char)'E' || decimalOfChar == (unsigned char)'I' || decimalOfChar == (unsigned char)'O' || decimalOfChar == (unsigned char)'U';
		else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
			return decimalOfChar == (unsigned char)'a' || decimalOfChar == (unsigned char)'e' || decimalOfChar == (unsigned char)'i' || decimalOfChar == (unsigned char)'o' || decimalOfChar == (unsigned char)'u';

		return false;
	}

	bool WordHelper::WordOnlyContainsAandBs(std::string* toDecode)
	{
		for (int i = 0; i < toDecode->length(); i++)
		{
            // returns false if its a letter and its neither a or b
			if (isalpha(toDecode->at(i)) && toDecode->at(i) != 'a' && toDecode->at(i) != 'b')
				return false;
		}

		return true;
	}

    void WordHelper::EraseNewLinesAndSpaces(std::string& str, bool eraseUnnecessarySpaces)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            // removes unneccessary spaces
            if (eraseUnnecessarySpaces && i > 0 && str[i - 1] == ' ' && (str[i] == '\n' || str[i] == ' '))
                str.erase(i, 1);
            else if (str[i] == '\n')
                str[i] = ' ';
        } 
    }

    // from https://www.geeksforgeeks.org/word-wrap-problem-space-optimized-solution/

    void WordHelper::SolveWordWrap(TextData& textInput, int linesize)
    {
        // returns empty String if the input is empty
        if (textInput.wordsLength.empty())
        {
            textInput.SetContent("");
            return;
        }

        int i, j;
        int n = textInput.wordsLength.size();

        std::vector<int> output;

        // can somtimes end in an endless loop


        // Variable to store number of 
        // characters in given line. 
        int currlen;

        // Variable to store possible 
        // minimum cost of line. 
        int cost;

        // DP table in which dp[i] represents 
        // cost of line starting with word 
        // arr[i]. 

        int* dp = new int[n];

        // Array in which ans[i] store index 
        // of last word in line starting with 
        // word arr[i]. 
        int* ans = new int[n];

        // If only one word is present then 
        // only one line is required. Cost 
        // of last line is zero. Hence cost 
        // of this line is zero. Ending point 
        // is also n-1 as single word is 
        // present. 
        dp[n - 1] = 0;
        ans[n - 1] = n - 1;

        // Make each word first word of line 
        // by iterating over each index in arr. 
        for (i = n - 2; i >= 0; i--) {
            currlen = -1;
            dp[i] = INT_MAX;

            // Keep on adding words in current 
            // line by iterating from starting 
            // word upto last word in arr. 
            for (j = i; j < n; j++) {

                // Update number of characters 
                // in current line. arr[j] is 
                // number of characters in 
                // current word and 1 
                // represents space character 
                // between two words. 
                currlen += (textInput.wordsLength[j] + 1);

                // If limit of characters 
                // is violated then no more 
                // words can be added to 
                // current line. 

                // if its the same length as the previous word that means that this single word is longer than the line
                if (currlen > linesize && currlen != textInput.wordsLength[j])
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
                if (j == n - 1)
                    cost = 0;
                else
                    cost = (linesize - currlen) * (linesize - currlen) + dp[j + 1];

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
        while (i < n) {
            output.push_back(i);
            output.push_back(ans[i]);
            i = ans[i] + 1;
        }

        delete[] dp;
        delete[] ans;

        FormatText(textInput, output);
    }

    void WordHelper::FormatText(TextData& textInput, std::vector<int> formatting)
    {
        std::string output = textInput.GetContent();

        int wordPos = 0;
        int positon = 0;

        // first position is index of the first word in the line
        // second position the index of the last word in the line
        for (int i = 0; i < formatting.size(); i += 2)
        {
            int combinedWordLengths = 0;

            int amountOfWords = formatting[i + 1] - formatting[i];

            int iteration = 0;
            for (iteration; iteration <= amountOfWords; iteration++)
            {
                // add + 1 for space after the word
                combinedWordLengths += textInput.wordsLength[wordPos] + 1;
                wordPos++;
            }


            positon += combinedWordLengths;

            if (positon < textInput.GetLength())
                output[positon - 1] = '\n';
        }

        textInput.SetContent(output);

    }