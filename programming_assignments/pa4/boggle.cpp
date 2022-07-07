/* File: boggle.cpp
 * ----------------
 * Your name here!
 */
 
#include <string>
#include <iostream>
#include <set>
#include <ctime> 
#include <cstdlib>
#include <stdexcept>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\lexicon.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\lexicon.cpp"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
using namespace std; 

struct playerT {
	set<string> wordList; 
	unsigned int score; 
	time_t turnTimeSecs;
};

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
// string BigBoggleCubes[25]  = 
// {"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
// "BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
// "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

const unsigned int BOARD_SIZE = 4;
const unsigned int MIN_WORD_LEN = 4;

// Provided - prints welcome info 
void Welcome();
// Provided - prints instruction info & waits for user to respond before moving on
void GiveInstructions();
/* Creates a custom board from user input
@param board - reference to a 2d char array
 */
void createCustomBoard(char (&board)[BOARD_SIZE][BOARD_SIZE]);
/* Creates a random board
@param board - reference to a 2d char array
@throws invalid_argument if user enters a non-alphabetic character to put into the board
 */
void createRandomBoard(char (&board)[BOARD_SIZE][BOARD_SIZE]);
/* Prints a board 
@param board - reference to a 2d char array that can't be edited 
 */
void printBoard(const char (&board)[BOARD_SIZE][BOARD_SIZE]);
/* Checks if a given (row, column) position is a valid board position
@param row - row of position 
@param col - column of position
@return whether (row, col) is valid 
 */
bool posOnBoard(int row, int col);
/* Runs the human's turn
@param board - reference to a 2d char array that can't be edited 
@param human - reference to a playerT representing the human
@param l - reference to a Lexicon that can't be edited
 */
void runHumanTurn(const char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& human, const Lexicon& l);
/* Checks if a given word can be found in a board 
@param board - reference to a 2d char array that can't be edited 
@param word - reference to a string that can't be edited 
@return whether word was found in board
 */
bool boardHasWord(const char (&board)[BOARD_SIZE][BOARD_SIZE], const string& word);
/* Helper function that is wrapped by previous function
@param board - reference to a 2d char array that can't be edited
@param word - string variable that tracks the progress of how much have the word passed by wrapper has been discovered 
@param row - current row in the board being looked at 
@param col - current column in the board being looked at 
@param visited - reference to a 2d boolean array that tracks which chars in the board have been visited 
@return whether word was found in board
 */
bool boardHasWord(const char (&board)[BOARD_SIZE][BOARD_SIZE], string word, unsigned int row, unsigned int col, bool (&visited)[BOARD_SIZE][BOARD_SIZE]);
/* Runs the computer's turn after the human has taken their turn
@param board - reference to a 2d char array that can't be edited 
@param computer - reference to a playerT representing the computer
@param human - reference to a playerT representing the human that can't be edited. Needed so computer doesn't reuse human's found words.
@param l - reference to a Lexicon that can't be edited
 */
void runComputerTurn(char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& computer, const playerT& human, const Lexicon& l);
/* Finds the words in a board - helper function wrapped by previous function
@param board - reference to a 2d char array that can't be edited
@param computer - reference to a playerT representing the computer
@param human - reference to a playerT representing the human that can't be edited. Needed so computer doesn't reuse human's found words.
@param row - current row in the board being looked at
@param col - current column in the board being looked at
@param curr - current word being built up 
@param visited - reference to a 2d boolean array that tracks which chars in the board have been visited
 */
void findWords(const char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& computer, const playerT& human, unsigned int row, unsigned int col, string curr, bool (&visited)[BOARD_SIZE][BOARD_SIZE], const Lexicon& l);


int main()
{
	// Display initial info
	Welcome();
	GiveInstructions();

	printUnderlined("Setting up Lexicon & Board");
	Lexicon l("C:\\Users\\Chami\\Stanford_Cpp_Class\\organized_materials_and_my_code\\my_lib\\words_alpha.txt"); 

	// Set up board based on whether user wants a custom board or random board
	char board[BOARD_SIZE][BOARD_SIZE];
	cout << "Would you like to enter a custom board?\nEnter \"y\" or \"yes\" if so: ";
	string answer; 
	getline(cin, answer);
	for (string::iterator itr = answer.begin(); itr != answer.end(); itr++) {
		*itr = tolower(*itr);
	}
	if (answer == "y" || answer == "yes") {
		createCustomBoard(board);
	}
	else {
		createRandomBoard(board);
	}

	// Run human's turn, then computer's turn
	playerT human, computer;
	printUnderlined("Turn 1: Human");
	pause("Press RETURN when you are ready...");
	runHumanTurn(board, human, l);
	printUnderlined("Turn 2: Computer");
	runComputerTurn(board, computer, human, l);

	// Display the results 
	printUnderlined("Results");
	if (human.score > computer.score) {
		cout << "VICTORY!\n";
	}
	else if (computer.score > human.score) {
		cout << "DEFEAT!\n";
	}
	else {
		cout << "TIE!\n";
	}
	cout << "You found " << human.wordList.size() << " words and scored " << human.score << " point(s) in " << human.turnTimeSecs 
	<< " second(s).\nThe computer found " << computer.wordList.size() << " words and scored " << computer.score << " point(s) in " << 
	computer.turnTimeSecs << " second(s).\n";

	// In case the user wishes to see what the computer came up with
	cout << "\nWould you like to view what the computer found?\nEnter \"y\" or \"yes\" if so: ";
	getline(cin, answer);
	for (string::iterator itr = answer.begin(); itr != answer.end(); itr++) {
		*itr = tolower(*itr);
	}
	if (answer == "y" || answer == "yes") {
		for (set<string>::iterator itr = computer.wordList.begin(); itr != computer.wordList.end(); itr++) {
			cout << *itr << ' ';
		}
	}
	cout << endl;

	return 0;
}

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;
	
    cout << "\nHit return when you're ready...";
	string s;
    getline(cin, s);
}

void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void createRandomBoard(char (&board)[BOARD_SIZE][BOARD_SIZE]) {
	srand(time(NULL));
	unsigned int cubeCtr = 0;
	// Assign a rand char for each cube 
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = StandardCubes[cubeCtr++][rand() % 6];
		}
	}
	// Shuffle cubes' locations 
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			unsigned int randRow = rand() % BOARD_SIZE;
			unsigned int randCol = rand() % BOARD_SIZE;
			char tmp = board[randRow][randCol];
			board[randRow][randCol] = board[i][j];
			board[i][j] = tmp;
		}
	}
}

void createCustomBoard(char (&board)[BOARD_SIZE][BOARD_SIZE]) {
	string setup;
	bool receivedSetup = false;
	while (!receivedSetup) {
		cout << "Enter the letters that will make up the board as 1 string.\nThe order of the characters should be left->right, top->down.\n";
		getline(cin, setup);
		if (setup.length() < BOARD_SIZE*BOARD_SIZE) {
			cerr << "Input too short! Must be at least " << (BOARD_SIZE * BOARD_SIZE) << " characters long.\n";
		}
		else {
			receivedSetup = true;
		}
	}
	unsigned int setupCtr = 0;
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			if (!isalpha(setup[setupCtr])) {
				throw invalid_argument("Non-alphabetic characters cannot be used in board.");
			}
			board[i][j] = toupper(setup[setupCtr++]);
		}
	}
}

void runHumanTurn(const char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& human, const Lexicon& l) {
	printBoard(board);
	time_t start = time(NULL);
	bool playing = true;
	human.score = 0;
	while (playing) {
		string word;
		cout << "Enter a word (RETURN to finish): ";
		if (getline(cin, word)) {
			if (word.empty()) {
				playing = false;
			}
			else {
				/* When the computer creates words from the board, they will be uppercase. It will then search to see if the human has found that word, and since
				playerT.wordList is a set which is case-sensitive, it will expect uppercase entries. Thus, the word will be made uppercase before being stored in
				the human's wordList. Furthermore, if the user enters the same word twice with different case, converting it to uppercase will make sure that it is
				found in the human's wordList and not be duplicated.
				 */
				for (string::iterator itr = word.begin(); itr != word.end(); itr++) { 
					*itr = toupper(*itr);
				}
				/* check if the word has the minimum length, hasn't been used before, is a word in the lexicon, and can be made on the board.
				The first check (integer comparison) is the easiest. 
				Since the human's word list will be a smaller set than the lexicon, do that check 2nd. That way if the word is found, there is no point checking
				if it is in the lexicon b/c it had to have been in the lexicon to be added to the human's word list. 
				Do the lexicon check 3rd, even if it may not be any slower than the previous check (set queries are theoretically O(1)).
				Lastly, do the most expensive check: if the word is in the board 
				 */
				if (word.length() >= MIN_WORD_LEN && human.wordList.find(word) == human.wordList.end() && l.hasWord(word) && boardHasWord(board, word)) {
					human.wordList.insert(word);
					human.score += (word.length() - MIN_WORD_LEN) + 1;
				}
				else {
					cerr << "Invalid word!\n"; 
				}
			}
		}
		else {
			cin.ignore();
			cin.clear();
			cout << "Try again.\n";
		}
	}
	human.turnTimeSecs = time(NULL) - start;
}

bool boardHasWord(const char (&board)[BOARD_SIZE][BOARD_SIZE], const string& word) {
	string cpy = word; // Used by helper 
	// Initialize visited 2d array to state that no entries have been discovered 
	bool visited[BOARD_SIZE][BOARD_SIZE];
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			visited[i][j] = false;
		}
	}
	// (DFS-based) For each entry in the board, see if the word can be started from that point. Once a starting point has been found, report the success to terminate early
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			visited[i][j] = true; // mark this entry as visited to start search 
			if (boardHasWord(board, cpy, i, j, visited)) {  // DFS-visit
				return true;
			}
			// if search failed, mark this entry as unvisited so other starting points can use this entry in their search
			visited[i][j] = false; 
		}
	}
	return false; // Report failure if word could not be found starting from any point in the board
}

bool boardHasWord(const char (&board)[BOARD_SIZE][BOARD_SIZE], string word, unsigned int row, unsigned int col, bool (&visited)[BOARD_SIZE][BOARD_SIZE]) {
	if (word.empty()) { // chars are only removed from word if they were found along a valid path in the board. Thus, if word is empty, all chars were found -> report success
		return true;
	}
	// if this board entry does not equal the next char in the word, that means the last decision failed to find a valid path to form the word, report failure to trigger backtracking
	if (board[row][col] != word[0]) { 
		return false;
	}
	// iteration of 8 adjacent entries (i.e. choices) put into a loop that moves over all 9 entries in the 3x3 block surrounding this entry but skipping this entry
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			// if this entry actually has an adjacent tile in the given direction on the board that has not been visited 
			if (posOnBoard(row+i, col+j) && !visited[row+i][col+j]) {
				visited[row+i][col+j] = true; // visit it 
				// see if a word can be built from that point, removing the 1st char from word b/c it has been found on the board (i.e. board[row][col]=word[0])
				if (boardHasWord(board, word.substr(1), row+i, col+j, visited)) { 
					return true; // report success 
				}
				// mark the entry as unvisited so that it can be used in future recursive calls on other paths from other starting points
				visited[row+i][col+j] = false;
			}
		}
	}
	// Recursion did not progress successfully in any direction (i.e. through anny choice) from the current point. Report failure to trigger backtracking & reverse last decision
	return false; 
}

void runComputerTurn(const char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& computer, const playerT& human, const Lexicon& l) {
	time_t start = time(NULL);
	computer.score = 0;

	// Initialize visited 2d array to state that no entries have been discovered 
	bool visited[BOARD_SIZE][BOARD_SIZE];
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			visited[i][j] = false;
		}
	}
	// For each entry in the board, try creating words from that point (DFS-based)
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			visited[i][j] = true; // Visiting this entry 
			string curr; // Initialize 'curr' param of helper to be this entry's char 
			curr.push_back(board[i][j]);
			findWords(board, computer, human, i, j, curr, visited, l); // DFS-visit
			// Mark this entry as no longer visited so that calls to findWords() in future loop iterations can use this entry in creating words from other starting points
			visited[i][j] = false; 
		}
	}

	computer.turnTimeSecs = time(NULL) - start;
}

void findWords(const char (&board)[BOARD_SIZE][BOARD_SIZE], playerT& computer, const playerT& human, unsigned int row, unsigned int col, string curr, bool (&visited)[BOARD_SIZE][BOARD_SIZE], const Lexicon& l) {
	/* Using a similar idea as in runHumanTurn(), doing least expensive check first (integer comparison) followed by set searches. Since the playerT wordLists are smaller than the lexicon,
	they may be fastever even though they are all O(1) set queries 

	The current word built must be at least the minimum length, cannot have been found by the human, cannot have been found by the computer before, and must be in the
	lexicon
	 */
	if (curr.length() >= MIN_WORD_LEN && human.wordList.find(curr) == human.wordList.end() && computer.wordList.find(curr) == computer.wordList.end() && l.hasWord(curr)) {
		computer.wordList.insert(curr); 
		computer.score += (curr.length() - MIN_WORD_LEN) + 1;
	}
	
	// If the current character path has led to something that doesn't prefix any word, break this path; no point in continuing 
	if (!l.hasPrefix(curr)) {
		return;
	}
	
	/* Similarly, loop over adjacent entries and see if they are on the board & haven't been visited. If so, mark the entry as visited before trying to find more
	words from that point 
	 */
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			if (posOnBoard(row+i, col+j) && !visited[row+i][col+j]) {
				visited[row+i][col+j] = true; // mark as visited
				// find words from adjacent, that is add the adjacent entry's value to the current word build 
				findWords(board, computer, human, row+i, col+j, curr+board[row+i][col+j], visited, l);
				// mark entry as no longer visited so that other word building paths from other starting points can use this entry in building other words
				visited[row+i][col+j] = false; 
			}
		}
	}
}

void printBoard(const char (&board)[BOARD_SIZE][BOARD_SIZE]) {
	cout << "\n";
	for (unsigned int i = 0; i < BOARD_SIZE; i++) {
		for (unsigned int j = 0; j < BOARD_SIZE; j++) {
			cout << board[i][j] << ' ';
		}
		cout << "\n";
	}
	cout << endl;
}

bool posOnBoard(int row, int col) {
	return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

