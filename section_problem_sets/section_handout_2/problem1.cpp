#include <vector> 
#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>  
using namespace std;

// Provided struct: 
// struct eMailMsg {
//     string to;
//     string from;
//     string message; 
//     string subject; 
//     int date;
//     int time; 
// };

// New struct (1c):
struct eMailMsg {
    vector<string> to;
    string from;
    string message;
    string subject;
    int date;
    int time;
};

// for handout 
void removeSpam(vector<eMailMsg>& emailMessages);
// for testing
void fillWithEmailMessages(vector<eMailMsg>& emailMessages, unsigned int num = 10, unsigned int minRecipients = 0, unsigned int maxRecipients = 5);

int main() {
    // 1a) If I wanted to create a vector of emailMsg structures called "emailMessages", I would declare it like so: vector<emailMsg> emailMessages;
    vector<eMailMsg> emailMessages;
    /* 1c) Given an emailMsg structure called "emailMessage", I could access its last recipient in 2 different ways after checking that there is at least 1 recipient by seeing if
    emailMessage.to.empty() is false.
        i) Using operator[] to access the last element determined using the size() method: emailMessage.to[emailMessage.to.size()-1]
        ii) Using the back() function built-in to the vector class for accessing the last element: emailMessage.to.back()
    */
    fillWithEmailMessages(emailMessages);
    cout << "No. of email messages: " << emailMessages.size() << endl; 
    removeSpam(emailMessages);
    cout << "No. of email messages post-spam removal: " << emailMessages.size() << endl; 
    return 0;
}

void removeSpam(vector<eMailMsg>& emailMessages) {
    // soln. manual moves backwards (in a standard for loop) as opposed to forwards (in a while loop/modified for loop), thus no need to worry about shift
    vector<eMailMsg>::iterator itr = emailMessages.begin();
    while (itr!=emailMessages.end()) {
        if ((*itr).subject.find("SPAM") == 0) {
            itr = emailMessages.erase(itr);
        }
        else {
            itr++;
        }
    }
}

 // as in Java, I doubt that this function uses the best method for RNG - however, it's the only one I know at the moment.
void fillWithEmailMessages(vector<eMailMsg>& emailMessages, unsigned int num, unsigned int minRecipients, unsigned int maxRecipients) {
    srand(time(0));
    const unsigned short MSG_LEN = 20;
    for (unsigned int i = 0; i < num; i++) {
        eMailMsg emailMessage;
        emailMessage.from = "Robot Overlord";
        vector<string> recipients;
        int numRecipients = rand() % (maxRecipients - minRecipients) + minRecipients;
        for (int i = 0; i < numRecipients; i++) {
            char recipientChr = rand() % 26 + 41;
            string recipient = "Robot " + recipientChr + to_string(i);
            emailMessage.to.push_back(recipient);
        }     
        for (unsigned short i = 0; i < MSG_LEN; i++) {
            emailMessage.message += char(rand() % (126-32+1) + 32);
        }
        emailMessage.subject = "Dominion of the WorldSPAM";
        emailMessage.date = 2012;
        emailMessage.time = time(0);
        emailMessages.push_back(emailMessage);
    }
}