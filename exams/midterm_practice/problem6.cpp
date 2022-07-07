#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\linked_lists.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
#include <iostream>
using namespace std;

bool contains(Node<int> *list, Node<int> *sub);

int main() {
    Node<int> *list = nullptr, *sub = nullptr;
    printUnderlined("Building List (Backwards)");
    while (true) {
        cout << "Enter integer (-1 to exit): ";
        int in;
        cin >> in;
        if (cin.fail()) {
            return 1;
        }
        else if (in == -1) {
            break;
        }
        else {
            Node<int> *newNode = new Node<int>;
            newNode->data = in;
            addToHead(list, newNode);
        }
    }
    printUnderlined("Building Sub-List (Backwards)");
    while (true) {
        cout << "Enter integer (-1 to exit): ";
        int in;
        cin >> in;
        if (cin.fail()) {
            return 1;
        }
        else if (in == -1) {
            break;
        }
        else {
            Node<int> *newNode = new Node<int>;
            newNode->data = in;
            addToHead(sub, newNode);
        }
    }

    cout << "List contains sub-list? " << contains(list, sub);

    deallocateList(list);
    deallocateList(sub);
    return 0;
}

bool contains(Node<int> *list, Node<int> *sub) {
    /* Technically don't need these iterating nodes because if we changed what list and sub point to, those changes wont be reflected outside
    of this method's scope since the pointers are being passed by value. However, this will cover the case if list, sub were ever passed as 
    const pointers. */
    Node<int> *listCurr = list, *subCurr = sub; 
    while (listCurr != nullptr && subCurr != nullptr){ 
        if (listCurr->data == subCurr->data) {
            /* Note: memory that subCurr points to is not deallocated at this step. This is because we don't want to destroy the parameter sub that
            the user has provided. This also won't cause a resource leak because sub will still point to the data subCurr no longer will point to.*/
            subCurr = subCurr->next;
        }
        listCurr = listCurr->next;
    }

    return subCurr == nullptr;
}