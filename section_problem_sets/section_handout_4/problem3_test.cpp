// tests my answer in problem3.txt

#include <iostream>
#include <map>
#include <string> 
#include <vector> 
using namespace std; 

struct bookT {
    string author; 
    string title;
    string publisher;  
};

typedef vector<bookT>::iterator book_set_i;
typedef vector<bookT*>::iterator book_ptr_set_i;

void simulateDBv1();
void simulateDBv2();
void simulateDBv3();

vector<bookT> createSetOfBooks();
void printBook(const bookT& book);

int main() {
    simulateDBv1();
    simulateDBv2();
    simulateDBv3();
    return 0;
}

void simulateDBv1() {
    cout << "Simulating Database #1\n-----------------------------------------\nUsing bookT copies in vector values of map entries and tries updates with unshared data (wrong).\n";
    vector<bookT> books = createSetOfBooks();
    map<string, vector<bookT>> authorLookup;
    map<string, vector<bookT>> titleLookup;
    map<string, vector<bookT>> publisherLookup;

    for(book_set_i itr = books.begin(); itr != books.end(); itr++) {
        authorLookup[itr->author].push_back(*itr);
        titleLookup[itr->title].push_back(*itr);
        publisherLookup[itr->publisher].push_back(*itr);
    }

    cout << "Changing the author of LOTR by Alex to \"Alexander\" through author lookup (on copied data).\n";
    authorLookup["Alex"][0].author = "Alexander";

    cout << "Check the change was made using author lookup. Alexander's book is listed under Alex's lookup:\n";
    vector<bookT> alexBks = authorLookup["Alex"];
    for (book_set_i itr = alexBks.begin(); itr != alexBks.end(); itr++) {
        printBook(*itr);
    }

    cout << "Using title lookup, displaying information on all books titled LOTR. Alex should now be Alexander.\n";
    vector<bookT> lotrs = titleLookup["LOTR"];
    for (book_set_i itr = lotrs.begin(); itr != lotrs.end(); itr++) {
        printBook(*itr);
    }

    cout << endl;
}

void simulateDBv2() {
    cout << "Simulating Database #2\n-----------------------------------------\nUsing bookT pointers in vector values of map entries and does updates on shared data (correct).\n";
    vector<bookT> books = createSetOfBooks();
    map<string, vector<bookT*>> authorLookup;
    map<string, vector<bookT*>> titleLookup;
    map<string, vector<bookT*>> publisherLookup;

    for (book_set_i itr = books.begin(); itr != books.end(); itr++) {
        authorLookup[itr->author].push_back(&(*itr));
        titleLookup[itr->title].push_back(&(*itr));
        publisherLookup[itr->publisher].push_back(&(*itr));
    }

    cout << "Changing the author of LOTR by Alex to \"Alexander\" through author lookup (through dereference & shared data).\n";
    authorLookup["Alex"][0]->author = "Alexander";

    cout << "Check the change was made using author lookup. Alexander's book is listed under Alex's lookup:\n";
    vector<bookT*> alexBks = authorLookup["Alex"];
    for (book_ptr_set_i itr = alexBks.begin(); itr != alexBks.end(); itr++) {
        printBook(*(*itr));
    }

    cout << "Using the title lookup displaying all books titled LOTR. Alex should now be Alexander.\n";
    vector<bookT*> lotrBks = titleLookup["LOTR"];
    for (book_ptr_set_i itr = lotrBks.begin(); itr != lotrBks.end(); itr++) {
        printBook(*(*itr));
    }
    cout << "Using the publisher lookup displaying all books published by Pearson. Alex should now be Alexander.\n";
    vector<bookT*> pearsonBks = titleLookup["Pearson"];
    for (book_ptr_set_i itr = pearsonBks.begin(); itr != pearsonBks.end(); itr++) {
        printBook(*(*itr));
    }

    cout << endl;
}

void simulateDBv3() {
    cout << "Simulating Database #3\n-----------------------------------------\nUsing new heap allocation (unshared) to replace old shared data (wrong).\n";
    vector<bookT> books = createSetOfBooks();
    map<string, vector<bookT*>> authorLookup;
    map<string, vector<bookT*>> titleLookup;
    map<string, vector<bookT*>> publisherLookup;

    for (book_set_i itr = books.begin(); itr != books.end(); itr++) {
        authorLookup[itr->author].push_back(&(*itr));
        titleLookup[itr->title].push_back(&(*itr));
        publisherLookup[itr->publisher].push_back(&(*itr));
    }

    cout << "Changing the author of LOTR by Alex to \"Alexander\" through author lookup (by allocating new memory on the heap).\n";
    bookT* updated = new bookT;
    updated->author = "Alexander";
    updated->title = "LOTR";
    updated->publisher = "Pearson";
    authorLookup["Alex"][0] = updated;

    cout << "Check the change was made using author lookup. Alexander's book is listed under Alex's lookup:\n";
    vector<bookT*> alexBks = authorLookup["Alex"];
    for (book_ptr_set_i itr = alexBks.begin(); itr != alexBks.end(); itr++) {
        printBook(*(*itr));
    }

    cout << "Using title lookup, displaying information on all books titled LOTR. Alex should now be Alexander.\n";
    vector<bookT*> lotrs = titleLookup["LOTR"];
    for (book_ptr_set_i itr = lotrs.begin(); itr != lotrs.end(); itr++) {
        printBook(*(*itr));
    }

    delete updated; 
    cout << endl;
}

vector<bookT> createSetOfBooks() {
    vector<bookT> books;
    bookT alexLotr;
    alexLotr.author = "Alex";
    alexLotr.title = "LOTR";
    alexLotr.publisher = "Pearson";
    books.push_back(alexLotr);
    bookT tolkienLotr; 
    tolkienLotr.author = "Tolkien";
    tolkienLotr.title = "LOTR";
    tolkienLotr.publisher = "Springer Verlag";
    books.push_back(tolkienLotr);
    bookT alexHobbit;
    alexHobbit.author = "Alex";
    alexHobbit.title = "Hobbit";
    alexHobbit.publisher = "Springer Verlag";
    books.push_back(alexHobbit);
    bookT introToProb;
    introToProb.author = "Dr. Smith";
    introToProb.title = "Intro. to Probability";
    introToProb.publisher = "Pearson";
    books.push_back(introToProb);
    return books;
}

void printBook(const bookT& book) {
    cout << book.author << ' ' << book.title << ' ' << book.publisher << "\n";
}