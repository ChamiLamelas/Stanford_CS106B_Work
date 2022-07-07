#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

/* In general, to templatize a class do the following things marked with a *. */

template <typename T> // * this marks the class as a templatized class
class Mob {
    public: 
        Mob();
        void enqueue(T entry); // * change any instance of where the old (fixed) parameter type was being used: e.g function param
        T dequeue(); // * or as function return type 
        size_t size() const;  

    private:
        vector<T> entries; // * change any member variables such as this wrapped container 
};

// * for each method, add a template declaration and change Mob to Mob<T>. Make sure to carry over any changes to the method declarations above to their definitions below
template <typename T>
Mob<T>::Mob() {
    srand(time(0));
}

template <typename T>
void Mob<T>::enqueue(T entry) {
    entries.push_back(entry);
}

template <typename T>
T Mob<T>::dequeue() {
    int r = rand() % entries.size();
    auto i = entries.begin();
    i += r;
    T copy = entries.at(r);
    entries.erase(i);
    return copy;
}

template <typename T>
size_t Mob<T>::size() const {
    return entries.size();
}

int main() {
    Mob<char> mob; // * in the client code, make sure to provide the desired type to the template parameter (e.g. char)
    mob.enqueue('a');
    mob.enqueue('b');
    mob.enqueue('c');
    while (mob.size() > 0) {
        cout << mob.dequeue() << ' ';
    }
    return 0;
}


