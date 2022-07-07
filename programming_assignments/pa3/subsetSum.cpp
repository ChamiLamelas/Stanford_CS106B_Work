#include <iostream>
#include <fstream> 
#include <vector>
#include <ctime>
using namespace std; 

int count = 0;

bool canMakeSum(vector<int>& nums, int target);

int main() {
    cout << "File format: target is first number, all following numbers are put into list." << endl;
    vector<int> data;
    // ofstream of("nums.dat");
    // of << 500 << '\n';
    // for (int i = -25; i <= 25; i++) {
    //     of << i << '\n';
    // }
    // of.close();
    ifstream f("nums.dat");
    if (f.fail()) {
        cerr << "Could not open file.\n";
        return 1;
    }
    int x; 
    while (f >> x) {
        data.push_back(x);
    }
    if (!f.eof()) {
        cerr << "Error interrupted file reading.\n";
        return 2;
    }
    f.close();
    int tar = data.front();
    data.erase(data.begin());
    time_t initial = time(NULL);
    if (canMakeSum(data, tar)) {
        cout << "Found sum " << tar << '!' << endl;
    }
    else {
        cout << "Did not find sum " << tar << '!' << endl;
    }
    cout << "Finished in " << (time(NULL) - initial) << " seconds." << endl;
    return 0;
}

bool canMakeSum(vector<int>& nums, int target, int sumSoFar, int i) {
    /* Soln. 1: Based off of 'Subsets' Recursion idea 

    If we have reached target then 
        report success 
    If we have run out of choices then
        report failure b/c target was never reached 

    (Since choices remain...)
    Recursively attempt to find sum without adding the choice to the sum and with adding the choice to the sum
    report the result of the above 

    Notes: 
        - To track the current choice, use @param i as an index in the nums vector 
        - Could alternatively reduce target to 0 
        - In general, finds soln. using exhaustive "in/out" recurison. That is, keep finding subsets of num and seeing if their sum equals target. If so, then exit the recursion.
     */

    // if (target == sumSoFar) {
    //     return true;
    // }
    // if (i >= nums.size()) {
    //     return false;
    // }

    // return canMakeSum(nums, target, sumSoFar, i + 1) || canMakeSum(nums, target, sumSoFar + nums[i], i+1);
    
    /* Soln. 2: Based off of 'Permutations' Recursion idea & Recursive Backtracking

    If we have reached target then
        report success 
    If we have passed target then
        report failure, current attempt has overshot the target. This isn't necessary, but it can trigger backtracking earlier than the loop condition below

    for each choice in the ones that remain
        Remove the choice from the remaining choices, add it to sum, and recursively attempt to find the sum 
        If Recursion was successful then
            report success

    report failure b/c all remaining choices were tried and sum was never reached (trigger backtracking)

    Notes:
        - Here, @param i is used to track which choices have been used and which remain. That is, for len(nums)=n, nums[0...i] have been used and nums[i+1...n] remain. This makes
        sure entries in nums are not reused when they are known not to have led to a soln. 
        - In general, finds soln. using a modified permutations & recursive backtracking algorithm that doesn't revisit choices. The algorithm tries to find a sum starting at 
        a certain point. If that overshoots or we run out of choices then backtracking is triggered. If backtracking leads all the way back to the bottom of the stack, then we
        try again starting from the second choice. At this point the first choice has permanently been discarded and cannot be used by any further recursive calls in the stack.
        - To visualize, it may be best to print 'sumSoFar' to observe its updating.
     */

    if (target == sumSoFar) {
        return true;
    }
    if (sumSoFar > target) {
        return false;
    }

    for (int j = i; j < nums.size(); j++) {
        if (canMakeSum(nums, target, sumSoFar + nums[j], j + 1)) {
            return true;
        }
    }
    return false;
}

bool canMakeSum(vector<int>& nums, int target) {
    return canMakeSum(nums, target, 0, 0);
}