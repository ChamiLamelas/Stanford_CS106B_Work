#include <stack> 
#include <iostream> 
#include <string> 
using namespace std;

bool IsCorrectlyNested(const string& htmlStr);

int main() {
    while (true) {
        string htmlStr;
        cout << "Enter an HTML string (RETURN to quit): ";
        if (getline(cin, htmlStr)) {
            if (htmlStr.empty()) {
                break;
            }
            cout << "Is correctly nested? " << IsCorrectlyNested(htmlStr) << endl;
        }
        else {
            cerr << "Console input could not be read." << endl;
            return 1;
        }
    }
    return 0;
}

// pre-condition: all HTML tags are not malformed. That is, things like html> or <html>> won't exist.
bool IsCorrectlyNested(const string& htmlStr) {
    stack<string> checker; // will hold all opened tags and will be used to check if future closed tags match the last opened tag 
    // Will hold the index of the start of the next encountered tag. 
    int tagStart; 
    // Holds the end of the last encountered tag. Starts at 0 to make the following while condition work: 
    int tagEnd = 0;
    // search for next tag (starts with a "<") starting from end of the last found tag or 0 if no tags have been located yet
    while ((tagStart = htmlStr.find("<", tagEnd)) != string::npos) { 
        tagEnd = htmlStr.find(">", tagStart); // search for end of tag who was opened at index tagStart (hence tagStart is a good start for the search) 
        /*
        build the tag's id (e.g. html for <html> or /html for </html>) by creating substr using following rules:
        1) tag id starts at 1 pos after tagStart (tagStart marks '<')
        2) the full length of the tag is (tagEnd-tagStart)+1. The tag id doesn't include the < and >, thus its length is ((tagEnd-tagStart)+1)-2 = tagEnd-tagStart-1
         */
        string tagID = htmlStr.substr(tagStart+1, tagEnd-tagStart-1); 
        if (tagID[0] == '/') { // search has led to a closing tag 
            /* If checker is empty, then we have encountered a closing tag that had no opening tag which means the HTML string isn't correctly nested.
            If the last opening tag does not correspond to this tag, (e.g. a <html> tag was the last opened tag and the current tag is </b>) then the HTML string isn't correctly
            nested. Note: if last opening tag corresponds to the encountered closing tag, checker's top should be equal to this tag minus the / at the start 
             */
            if (checker.empty() || checker.top() != tagID.substr(1)) { 
                return false;
            }
            // If the checker was not empty and the last opened tag corresponds to this closing tag, pop the opening tag. This will allow us to process further tags in the HTML string
            checker.pop(); 
        }
        else { // Push any open tags, otherwise future closing tags won't correctly be processed by the above if statement
            checker.push(tagID); 
        }
    }
    /*
    checker should be empty if htmlStr is correctly nested. That is, all discovered opening tags should have been popped due to the if-statement in the above loop correctly 
    locating and identifying their corresponding closing tags. Any remaining entries in checker are opening tags whose corresponding closing tags were never found in htmlStr.
     */
    return checker.empty();
}