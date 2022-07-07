/*
a) Here is the client callback function I would define to use the cs106 Set class. Note the use of 'compare()' from stl::string which automatically returns an integer.

int entryTcompare(const entryT& a, const entryT& b) {
    if (a.lastName == b.lastName) {
            return a.firstName.compare(b.firstName);
        }
        else {
            return a.lastName.compare(b.lastName);
    }
}

The cs106 Set object would then be constructed as: Set<entryT> set_name(entryTcompare);

If they have the same first and last name, then the 2 entryT objects would be considered equal. Therefore, if one tried to add both to the Set, only 1 would remain in it. This
is because Sets do not allow duplicates by defintion.

b) Here is a client callback function that would compare strings ignoring their case: 

int caseInsensitiveComp(const string& a, const string& b) {
        a = toLowerCase(a);
        b = toLowerCase(b);
        return a.compare(b);
}

The set object could then be constructed as so: Set<string> set_name(caseInsensitiveComp);
 */

#include <string>
#include <set>
#include <iostream> 
using namespace std; 

struct entryT {
    string firstName;
    string lastName;
    string phoneNumber;
};

// see example here for custom comparison in stl::set -> http://www.cplusplus.com/reference/set/set/set/
// online seems to say function objects such as the one below are better than function pointers (as recommended in class) because compiler can make better optimizations with objects 
// and that functiono objects can have state (i.e. members)
struct entryTcomp {
    bool operator() (const entryT& a, const entryT& b) {
        if (a.lastName == b.lastName) {
            return a.firstName < b.firstName;
        }
        else {
            return a.lastName < b.lastName;
        }
    }
};

struct caseInsentiveComp {
    bool operator() (const string& a, const string& b) {
        string cpyA = a;
        string cpyB = b;
        for (size_t i = 0; i < cpyA.size(); i++) {
            cpyA[i] = tolower(cpyA[i]);
        }
        for (size_t i = 0; i < cpyB.size(); i++) {
            cpyB[i] = tolower(cpyB[i]);
        }
        return cpyA < cpyB;
    }
};

int main() {
    set <entryT, entryTcomp> s; // if using the stl::set, this is how the comparison function is passed into the set 
    entryT entry1;
    entry1.firstName = "Alvin";
    entry1.lastName = "Chipmunk";
    entry1.phoneNumber = "456";
    s.insert(entry1);
    entryT entry2; 
    entry2.firstName = "Billy";
    entry2.lastName = "Chipmunk";
    s.insert(entry2);
    entryT entry3;
    entry3.firstName = "Snoopy";
    entry3.lastName = "Dog";
    s.insert(entry3);
    entryT entry4;
    entry4.firstName = "Alvin";
    entry4.lastName = "Chipmunk";
    entry4.phoneNumber = "123";

    // Alvin..Bob..Snoopy (Alvin has 2 diff. phone #'s but same first & last name so he won't get inserted 2x)
    for (set<entryT, entryTcomp>::iterator itr = s.begin(); itr != s.end(); itr++) {
        cout << itr->firstName << " " << itr->lastName << endl;
    }

    set<string, caseInsentiveComp> strs; 
    strs.insert("ABC");
    strs.insert("abc");
    strs.insert("bob");


    // should be "ABC bob" b/c abc = ABC in w/ this comparator and won't get added to strs
    for (set<string, caseInsentiveComp>::iterator itr = strs.begin(); itr != strs.end(); itr++) {
        cout << *itr << " ";
    }

    return 0;
}

