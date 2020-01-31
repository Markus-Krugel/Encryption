#include <string>

class WordHelper
{
	public:
		static int getAlphabetPosition(char letter)
		{
			int decimalOfChar = int(letter);

			if (decimalOfChar >= decimalStartUpperletter && decimalOfChar <= decimalEndUpperletter)
				return decimalOfChar - decimalStartUpperletter;
			else if (decimalOfChar >= decimalStartLowerletter && decimalOfChar <= decimalEndLowerletter)
				return decimalOfChar - decimalStartLowerletter;
		}

		static char getCharAtAlphabetPosition(int position, bool lowerCase)
		{
			if (lowerCase)
				return decimalStartLowerletter + position;
			else
				return decimalStartUpperletter + position;
		}

	private:
		static const int decimalStartUpperletter = 65;
		static const int decimalEndUpperletter = 90;
		static const int decimalStartLowerletter = 97;
		static const int decimalEndLowerletter = 122;
};