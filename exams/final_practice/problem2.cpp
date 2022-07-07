#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\linked_lists.h"

template <typename T>
class Set {
    public:
        Set(int (cmpFn)(T &x, T &y) = operatorCmp) {
            comparisonFunc = cmpFn;
            head = nullptr;
            numEntries = 0;
        }

        ~Set() {
            deallocateList(head);
        }

        bool contains(const T &entry) const {
            Node *curr = head;
            while (curr != nullptr && comparisonFunc(curr->data, entry) < 0) {
                curr = curr->next;
            }
            if (curr != nullptr && comparisonFunc(curr->data, entry) == 0) { 
                return true;
            }
            // else curr==nullptr (that is, the entire list was iterated) or curr!=nullptr and comparisonFunc(curr->data,entry) > 0 (entry couldn't be in list since it's sorted)
            return false;
        }

        void unionWith(const Set &other) {
            if (other.head == nullptr) { // nothing to add to this Set
                return;
            }

            // sets up next loop. That is, if this Set's empty or the first element of the other Set is smaller, the head needs to be updated
            // for furhter insertions to be possible
            Node *otherTrack = other->head;
            if (head == nullptr || comparisonFunc(otherTrack->data, head->data) < 0) {
                Node *newHead = new Node;
                newHead->next = head;
                newHead->data = otherTrack->data;
                head = newHead;
                otherTrack = otherTrack->next;
                numEntries = 1; // bug! remember to update Set's size 
            }

            // know that otherTrack->data >= head->data 
            Node *addPoint = head;
            while (otherTrack != nullptr) {
                if (comparisonFunc(addPoint->data, otherTrack->data) == 0) {
                    otherTrack = otherTrack->next;
                    continue;
                }

                if (addPoint->next == nullptr || comparisonFunc(otherTrack->data, addPoint->next->data) < 0) {
                    Node *cpy = new Node;
                    cpy->next = addPoint->next;
                    cpy->data = otherTrack->data;
                    addPoint->next = cpy;
                    otherTrack = otherTrack->next;
                    numEntries++; // bug! remember to update Set's size
                }
                addPoint = addPoint->next;
            }

        }

    private:
        Node *head;
        unsigned int numEntries;
        int (*comparisonFunc)(T &x, T &y);
};