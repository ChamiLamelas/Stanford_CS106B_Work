#include "vector.h"
#include "vector.cpp"
#include "testing_lib.h"
#include "testing_lib.cpp"
using namespace std;

int main() {
    Tester t;

    Vector<int> v; // tests on v don't resize
    // testing add using get & size
    v.add(1);
    v.add(2);
    v.add(3);
    
    for (int i = 0; i < v.size(); i++) {
        t.report(v.get(i), i+1);
    }

    t.report(v.size(), (unsigned int)3);
    
    // testing insert using get & size 
    v.insert(0, 5);
    t.report(v.get(0), 5);
    v.insert(v.size(), 4);
    t.report(v.get(v.size()-1), 4);

    for (int i = 1; i < v.size()-1; i++) {
        t.report(v.get(i), i);
    }

    t.report(v.size(), (unsigned int)5);

    // testing set using get & size
    for (int i = 0; i < v.size(); i++) {
        int tmp = v.get(i);
        v.get(i) = tmp*-1;
        t.report(v.get(i), tmp*-1);
    }

    t.report(v.size(), (unsigned int)5);

    int k = 1;
    while (v.size() > 0) {
        v.remove(0);
        for (int i = 0; i < v.size(); i++) {
            t.report(v.get(i), -1*(i+k));
        }
        k++;
    }

    Vector<string> s; // tests s.resize() using cout
    string alpha[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

    for (int i = 0; i < 26; i++) { // should resize up 2x 
        s.add(alpha[i]);
    }

    for (int i = 0; i < 26; i++) {
        t.report(s.get(i), alpha[i]);
    }

    for (int i = 0; i < 6; i++) { // shouldn't resize down yet
        s.remove(0);
        
        for (int j = 0; j < s.size(); j++) {
            t.report(s.get(j), alpha[j+i+1]);
        }
    }
    
    s.remove(0); // now should resize down b/c there were 20 entries and now a request has been made to remove 1

    for (int i = 0; i < 9; i++)  { // shouldn't resize down yet
        s.remove(0);
        for (int j = 0; j < s.size(); j++) {
            t.report(s.get(j), alpha[j+i+8]);
        }
    }

    s.remove(0); // now should resize down b/c there were 10 entries and now a request has been made to remove 1

    for (int i = 0; i < 5; i++) { // should not resize down even though this loop leaves vector with 4 entries (less than half of 10)
        s.remove(0);
        for (int j = 0; j < s.size(); j++) {
            t.report(s.get(j), alpha[j+i+18]);
        }
    }

    t.report(s.empty(), false);
    s.clear();
    t.report(s.empty(), true);

    for (int i = 0; i < 10; i++) { // shouldn't resize up yet
        s.insert(0, alpha[26-i-1]);
    }

    for (int i = 0; i < 10; i++) { // shouldn't resize up yet
        t.report(s.get(i), alpha[26-10+i]);
    }

    s.insert(s.size(), "new last letter"); // now should resize up
    t.report(s.get(s.size()-1), string("new last letter"));

    for (int i = 0; i < 10; i++) { // shouldn't resize up yet
        t.report(s.get(i), alpha[26-10+i]);
    }

    // demonstrates an issue with up & down resizing: that is, simply adding and removing 2 elements in a small vector leads 
    // to repeated resizing while only small changes are being made to the data. This would cause a performance decrease if repeated

    s.remove(0);
    s.remove(0);
    // should now resize down 
    s.insert(5, "?");
    t.report(s.get(5), string("?"));
    s.insert(5, "!");
    t.report(s.get(5), string("!"));
    // should now resize back up

    return 0;
}