# Encryption
A programm to encode and decode text with different algorithms.
Does currently only support english alphabet.

# The Algorithms
* Atbasch
  * Changes the letter with its version in the reversed alphabet
    * e.g. This is an example Text. -> Gsrh rh zm vcznkov Gvcg.
* BiLanguage    
  * Adds a bi after every vocal
    * e.g. This is an example Text. -> Thibis ibis abin ebixabimplebi Tebixt.
* RorLanguage    
  * Adds an of after every consonant and repeats the consonant afterwards
    * e.g. This is an example Text. -> Tothohisos isos anon exoxamompoplole Totexoxtot.    
* ULanguage    
  * Adds an u to the start of every word unless the word starts with a vocal then it replaces the voacl with an u
    * e.g. This is an example Text. -> Uthis us un uxample Utext.
* Bacon Code    
  * Changes every letter to a 5bit version with a's and b's
    * e.g. This is an example Text. -> baabbaabbbabaaabaaba abaaabaaba aaaaaabbab aabaababbbaaaaaabbaaabbbbababbaabaa baabbaabaababbbbaabb.
* Polybios Code    
  * Stores the alphabet in a 5x5 grid where the row is the ten's digit and the column the single unit.
    * e.g. This is an example Text. -> 44232443 2443 1133 15531132353115 44155344.
* Ceaser Cipher    
  * Shifts the alphabet by x amount of letters
    * e.g. This is an example Text. (x=3) -> Wklv lv dq hadpsoh Whaw.
* Transposition    
  * Groups every x-th letter in a group
    * e.g. This is an example Text. (x=3) -> Tssnxp xh   alTtiiaemee.
* Vigenere Cipher    
  * Looks up the encrypted char by looking at a table, where x and y coordinates are of the alphabet and then going to the crosspoint between the codeword and the word
    * e.g. This is an example Text. (Codeword:Secret) -> Llkj ml sr goefhpg Kiql.   
