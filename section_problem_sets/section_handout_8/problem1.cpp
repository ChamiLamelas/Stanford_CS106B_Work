#include <vector> 
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\linked_lists.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
#include <stack>
#include <fstream>
#include <string>
using namespace std; 

// in array implementation, buffer[cursor] should point to the character after the cursor (i.e. if cursor is after x chars, cursor at buffer[x]). This will allow the proper 
// use of vector.insert and vector.erase 
void moveToWordBegin(const vector<char> &buffer, int &cursor);
// after holds all elements after the cursor, before holds all elements before 
void moveToWordBegin(stack<char> &before, stack<char> &after);
// if the cursor is after the first letter on the screen, the cursor pointer points to the first node in the list 
void moveToWordBegin(const Node<char> * const head, const Node<char> *&cursor);

/* Runtime Analysis: let N = no. of chars in the buffer 

For both the stack and vector implementations, moveToWordBegin() can move backwards. Therefore, the runtime could be O(N) if the buffer is all one very long word. However, this
is unlikely, and the runtime will be O(K) where K is the length of the word before the cursor. However, for the singly linked list, since one cannot go backwards, one must use
a different approach. I chose a lead & lag pointer method which leads to O(N) behavior more frequently than the stack & vector implementations. Consider the case where the user
has placed the cursor at the end/in the last word of the editor. To find the beginning of the last word (assuming it takes up a reasonable chunk of the buffer and isn't really
long), the lead & lag pointer method will have to traverse nearly N characters to get there. This could happen quite frequently and shows the weakness of the linked list 
implementation. moveToWordBegin() would only work well with the linked list version when (as expected with SLLs) the cursor is close to the front of the buffer. However, in
this case it would still probably perform worse than the other 2 implementations.
*/

int main() {
    printUnderlined("Preparing Input - Data file should have cursor position on 1st line and sentence on 2nd.");
    cout << "Loading input file...";
    ifstream f;
    f.open("C:/Users/Chami/Stanford_Cpp_Class/organized_materials_and_my_code/section_problem_sets/section_handout_8/problem1.txt");
    int cursorAfter; 
    f >> cursorAfter;
    f.ignore();
    string sentence;
    getline(f, sentence);
    f.close();

    if (sentence.length() < cursorAfter) {
        cerr << "invalid input";
        return 1;
    }

    cout << "\tDONE.\nPreparing Buffer v.1...";
    vector<char> input;
    for (char ch : sentence) {
        input.push_back(ch);
    }

    cout << "\tDONE.\nPreparing Buffer v.2...";
    stack<char> before, after;
    for (int i = 0; i < cursorAfter; i++){ 
        before.push(input[i]);
    }
    for (int i = input.size()-1; i >= cursorAfter; i--) {
        after.push(input[i]);
    }

    cout << "\tDONE.\nPreparing Buffer v.3...";
    Node<char> *head = nullptr;
    for (vector<char>::reverse_iterator itr = input.rbegin(); itr != input.rend(); itr++){ 
        Node<char> *newNode = new Node<char>;
        newNode->data = *itr;
        newNode->next = nullptr;
        addToHead(head, newNode);
    }
    const Node<char> *cursor = nullptr;
    if (cursorAfter > 0) {
        cursor = head;
        for (int i = 1; i < cursorAfter; i++) {
            cursor = cursor->next;
        }
    }
    cout << "\tDONE." << endl;

    printUnderlined("Testing Buffer v.1");
    cout << "Array contents: ";
    for (char c : input) {
        cout << c;
    }
    if (cursorAfter < input.size()) {
        cout << "\nCursor before " << input[cursorAfter];
    }
    else {
        cout << "\nCursor at the end of the sentence.";
    }
    cout << endl;
    moveToWordBegin(input, cursorAfter);
    if (cursorAfter < input.size()) {
        cout << "Cursor before " << input[cursorAfter];
    }
    else {
        cout << "Cursor at the end of the sentence.";
    }
    cout << endl;

    printUnderlined("Testing Buffer v.2");
    cout << "Before Stack: ";
    printStack(before);
    cout << "After Stack: ";
    printStack(after);
    cout << endl;
    moveToWordBegin(before, after);
    cout << "Before Stack: ";
    printStack(before);
    cout << "After Stack: ";
    printStack(after);
    cout << endl;

    printUnderlined("Testing Buffer v.3");
    cout << "List: ";
    printList(head);
    cout << "Cursor before ";
    if (cursor == nullptr) {
        if (head == nullptr) {
            cout << "";
        }
        else {
            cout << head->data;
        }
    }
    else {
        if (cursor->next != nullptr) {
            cout << cursor->next->data;
        }
        else {
            cout << " N/A (at the end of the sentence)";
        }
    }
    cout << endl;
    moveToWordBegin(head, cursor);
    cout << "Cursor before ";
    if (cursor == nullptr) {
        if (head != nullptr) {
            cout << head->data;
        }
        else {
            cout << "";
        }
    }
    else {
        if (cursor->next != nullptr) {
            cout << cursor->next->data;
        }
        else {
            cout << " N/A (at the end of the sentence)";
        }
    }
    cout << endl;
    deallocateList(head);
    return 0;
}

void moveToWordBegin(const vector<char> &buffer, int &cursor) {
    // while the cursor isn't at the start and the character before the cursor is whitespace, move the cursor backwards until its after a non-ws char. This will locate the
    // end of the previous word if one exists. Also, if the cursor is before the 1st char in a word, this will move it to the end of the previous word (the next loop will move
    // it to the front of that word)
    while (cursor > 0 && isspace(buffer[cursor-1])) {
        cursor--;
    }
    // while the cursor isn't at the start/before the 1st char and the char before the cursor is ws, move the character backwards until it is after a whitespace char. The cursor
    // will end after a whitespace char (or at the beginning) and before the 1st char of a word 
    while (cursor > 0 && !isspace(buffer[cursor-1])) {
        cursor--;
    }
}

// similar logic to above ^ 
void moveToWordBegin(stack<char> &before, stack<char> &after) {
    // while there are characters before the cursor (i.e. not at the start) and they are whitespace, move the cursor backwards till its after a non-ws char
    while (!before.empty() && isspace(before.top())) {
        after.push(before.top());
        before.pop();
    }
    // while the cursor is after a ws char, move it till its after a ws char
    while (!before.empty() && !isspace(before.top())) {
        after.push(before.top());
        before.pop();
    }
}

void moveToWordBegin(const Node<char> * const head, const Node<char> *&cursor) {
    if (cursor == nullptr) { // cursor's already at the beginning of the sentence 
        return;
    }

    // use lead & lag pointer method. That is, one pointer leads forward looking for the cursor while the other lags behind only updating whenever a word is found that doesn't
    // have the cursor pointing to the first char. Then, the lagging pointer will point to the beginning of the word that follows.
    const Node<char> *wordStart = nullptr;
    const Node<char> *wordSearch = head; // start search from head (that is the cursor is starting after the 1st char)
    while (wordSearch != nullptr) { // somewhat unneeded b/c cursor should be in the list, but it's a valid precaution 
        // if we have found the cursor, update the cursor to be wordStart and exit. Thus, the cursor will now be displayed before the 1st char of the last found word 
        if (wordSearch == cursor) {
            cursor = wordStart;
            return;
        }
        // if wordSearch holds ws but wordSearch->next holds non-ws char and wordSearch != cursor (i.e. a cursor at wordSearch would be displayed in the editor 
        // between a ws char and a non-ws char), then update wordStart to be wordSearch. As in the (i.e.) clause, a cursor at wordSearch would be preceding a new word whose 
        // first letter is not before the original cursor. Observe how this handles the case of cursor being before the 1st letter of a word. 
        if (isspace(wordSearch->data) && wordSearch->next != nullptr && !isspace(wordSearch->next->data) && cursor != wordSearch) {
            wordStart = wordSearch;
        }
        wordSearch = wordSearch->next;
    }
}