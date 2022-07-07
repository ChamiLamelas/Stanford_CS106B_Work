#include "testing_lib.h"
#include "testing_lib.cpp"
#include "map.h"
#include "map.cpp"
#include <string>
using namespace std;

int stringHash(const string &s) {
    const long Multiplier = -1664117991L;
    unsigned long hashcode = 0;
    for (int i = 0; i < s.length(); i++) {
       hashcode = hashcode * Multiplier + s[i];
    }
    return hashcode;
}

int badStringHash(const string &s) { // to test rehashing & collision handling 
    return 0;
}

int main() {
    Tester t;

    //TreeMap<string, int> pb;
    HashMap<string, int> pb(badStringHash);
    t.report(pb.containsKey("Home"), false);
    t.report(pb.size(), (unsigned int)0);
    pb.put("Home", 1324523454);
    t.report(pb.containsKey("Home"), true);
    t.report(pb.size(), (unsigned int)1);
    t.report(pb.containsKey("home"), false);
    t.report(pb.get("Home"), 1324523454);
    pb.put("Home", 1234920384);
    t.report(pb.containsKey("Home"), true);
    t.report(pb.size(), (unsigned int)1);
    t.report(pb.get("Home"), 1234920384);
    pb.put("Work", 1234568902);
    t.report(pb.size(), (unsigned int)2);
    pb.put("Dentist", 1010000010);
    t.report(pb.size(), (unsigned int)3);
    pb.put("Doctor", 1230980983);
    t.report(pb.size(), (unsigned int)4);
    pb.put("Garage", 1999999999);
    t.report(pb.size(), (unsigned int)5);
    t.report(pb.containsKey("Work"), true);
    t.report(pb.containsKey("Home"), true);
    t.report(pb.containsKey("Dentist"), true);
    t.report(pb.containsKey("Doctor"), true);
    t.report(pb.containsKey("Garage"), true);
    t.report(pb.get("Work"), 1234568902);
    t.report(pb.get("Dentist"), 1010000010);
    t.report(pb.get("Doctor"), 1230980983);
    t.report(pb.get("Garage"), 1999999999);
    t.report(pb.get("Home"), 1234920384);
    pb.put("Work", 1928745938);
    t.report(pb.size(), (unsigned int)5);
    t.report(pb.get("Work"), 1928745938);
    pb.put("Dentist", 1928990903);
    t.report(pb.get("Dentist"), 1928990903);
    t.report(pb.size(), (unsigned int)5);
    pb.put("Doctor", 1911911911);
    t.report(pb.get("Doctor"), 1911911911);
    t.report(pb.size(), (unsigned int)5);
    pb.put("Garage", 1333333333);
    t.report(pb.size(), (unsigned int)5);
    t.report(pb.get("Garage"), 1333333333);
    t.report(pb.get("Home"), 1234920384);

    
    return 0;
}