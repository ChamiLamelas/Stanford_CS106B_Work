#include <string>
#include <stack>
#include <iostream>
using namespace std;

template <typename T>
int operatorCmp(T &x, T &y) {
    if (x < y) {
        return -1;
    }
    else if (x > y) {
        return 1;
    }
    return 0;
}


/* Displays a message and waits till the user has pressed the enter key before exiting. Sample usage: display some info, wait till user has confirmed they have read them,
start a game.
@param msg - a reference to a string to display before the pause that can't be edited
 */
void pause(const string& msg) {
	cout << msg;
	string s;
	getline(cin, s);
	cout << endl;
}

/* Prints a string underlined on new line and any text that follows will be on a new line. 
@param str - a reference to string to print underlined that can't be edited

Warning:
	- Doesn't flush cout 
 */
void printUnderlined(const string& str) {
	cout << '\n' << str << '\n';
	for (size_t i = 0; i < str.length(); i++) {
		cout << '-';
	}
	cout << '\n';
}

template <typename T>
void printStack(const stack<T> &s) {
	stack<T> cpy = s;
	while (!cpy.empty()) {
		cout << cpy.top();
		cpy.pop();
	}
	cout << '\n';
}

string convertToUpper(const string &s) {
	string upper;
	for (char ch : s) {
		upper.push_back(toupper(ch));
	}
	return upper;
}

string convertToLower(const string &s) {
	string lower;
	for (char ch : s) {
		lower.push_back(tolower(ch));
	}
	return lower;
}