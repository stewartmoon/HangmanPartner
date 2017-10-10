#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

/**
* Precondition: Read the input file for the words of hangman.
*      Choose 1 of them for word we will try.
* Postcondition: Found a word to play against.
*/
void getWords(string s[], int nelem = 0);

/**
* Precondition: Given a mystery word, perform a round of quessing the word.
* Postcondition: We've done a guessing round of hangman.
*/
bool playGame(string MysteryWord = "");

/**
* Precondition: need a word from the array of words.
* Postcondition: found a word to use.
*/
string pickWord(string s[], int nelem = 0);


/**
* Precondition:
* The HangMan word game.
*
* Postcondition:
* We've run a guessing round of hangman.
*
* Input:
* Return:
*      exit code. zero (0) if ok. non-zero for errors.
*
* Author: Lyndon VanWagner, Stewart Moon
* Date: 2017.10.05
* Version: 1.0
*/
int main() {
	bool newGame = true;                            // another game?
	string myWords[20]{};                         // word array
	srand(time(NULL));                              // seed rand()

													// load the words
													// and pick 1 of them.
													// then play the game.
	getWords(myWords, 20);
	do {
		string MysteryWord = pickWord(myWords, 20);
		newGame = playGame(MysteryWord);
	} while (newGame);
	return 0;
}


/**
* Precondition:
* Read the input file for the words of hangman.
* Choose 1 of them for word we will try.
*
* Postcondition:
* Found a word to play against.
*
* Input:
* Output:
* Result:
*      MysteryWord - string, the word user needs to spell.
*
* Author: Lyndon VanWagner, Stewart Moon
* Date: 2017.10.05
* Version: 1.0
*/
void getWords(string myWords[], int nelem) {
	int count = 0;                                  // word counter
	string temp = "";                               // temp word
	fstream myfile;                                 // file stream

													// count the number of lines (words)
	myfile.open("words.txt");
	while (myfile >> temp) count++;
	myfile.close();

	// read 20 words from the input stream
	myfile.open("words.txt");
	for (int i = 0; i < nelem; i++) {
		myfile >> myWords[i];
	}
	myfile.close();
}


/**
* Precondition:
* Given the array of words and its size...
* Choose 1 of them for word we will try.
*
* Postcondition:
* Found a word to play against.
*
* Input:
*      s - string[], array of words.
*      nelem - size of the array.
* Output:
* Result:
*      MysteryWord - string, the word user needs to spell.
*
* Author: Lyndon VanWagner, Stewart Moon
* Date: 2017.10.05
* Version: 1.0
*/
string pickWord(string s[], int nelem) {
	int randomNum = (rand() % nelem);
	return s[randomNum];
}


/**
* Precondition:
* Given a mystery word, perform a round of quessing the word.
*
* Postcondition:
* We've done a guessing round of hangman.
*
* Input:
*      MysterWord      - string, a word to guess
* Return:
*      true, if whether player wants to play again.
*      false, otherwise.
*
* Author: Lyndon VanWagner, Stewart Moon
* Date: 2017.10.05
* Version: 1.0
*/
bool playGame(string MysteryWord) {
	int playagain = 0;                              // do we play again ?
	char userinput = 'Y';                           // user input
	int loss = 0;                                   // turns lost

	string UnknownWord(MysteryWord.length(), '*');  // string of stars
	bool tryAgain = true;                      // repeat condition
	do {
		int win = 0;                                // # found characters
		string tempUknownWord = "";                 // copy of unknown words

		cout << "(Guess) Enter a letter in word: " << UnknownWord << " >";
		cin >> userinput;

		int tmp = win;                              // track # found
		bool foundNow = false;
		bool foundBefore = false;
		tempUknownWord = UnknownWord;
		for (int i = 0; i < MysteryWord.length(); i++) {
			//Check if letter has already been guessed
			//Check if user guess is = to a character in the MysteryWord
			if (userinput == UnknownWord.at(i)) {
				foundBefore = true;
				break;
			}
			else if (userinput == MysteryWord.at(i)) {
				foundNow = true;
				UnknownWord[i] = userinput;
				win++;
			}
		}

		if (foundBefore) {
			cout << userinput << " is already in the word" << endl;
		}
		else if (foundNow) {
		}
		else {
			cout << userinput << " is not in the word" << endl;
		}
	} while (UnknownWord != MysteryWord);

	cout << "The word is " << MysteryWord << ". You missed " << ++loss << " times." << endl;
	cout << "Would you like to play again? (Y/(N))";
	cin >> userinput;
	return (userinput == 'Y');
}

