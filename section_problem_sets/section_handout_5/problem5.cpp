#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

int getMaxSumv1(const vector<int> &v); // ans. to part a
int getMaxSumv2(const vector<int> &v); // ans. to part b
int getMaxSumv3(const vector<int> &v); // ans. to part c
int getMaxSumv3(const vector<int> &v, int &maxSum, int l, int r, int &lbound, int &rbound); // helper to above function 
int getMaxSumv4(const vector<int> &v); // ans. to part d

/* Answer to part e:

Algorithm: O(N^3)         O(N^2)          O(NlogN)            O(N)
Size of N
100        3s.            .1s             .03s                .003s      
200        24s.           .4s             .07s                .006s  
1000       3000s.         10s             .45s (*)            .03s  
10000      3000000s       1000s           6s   (*)            .3s  

THe values marked * seem a little off for some reason
 */

int main() {
    ifstream f;
    f.open("problem5.dat");
    if (f.fail()) {
        cerr << "error opening file";
        return 1;
    }

    vector<int> nums;
    int num; 
    while (f >> num) {
        nums.push_back(num);
    }
    if (!f.eof()) {
        cerr << "error interrupt";
        return 2;
    }
    f.close();

    cout << getMaxSumv1(nums) << endl;
    cout << getMaxSumv2(nums) << endl;
    cout << getMaxSumv3(nums) << endl;
    cout << getMaxSumv4(nums) << endl;
    return 0;
}

/* 
runtime analysis:

loop runs n-1 times, then 2(n-2) times, then 3(n-3) times, and so on till n-1 times again before the method exits. 
In general, the runtime is expressed by the sum of k(n-k) for k from 1 to n-1
Or: nk-k^2 for k=1...n-1
That is, the input in the sum has a dominant term of power 2. 

Since the summation formula for the sum of k^2 from 1 to n is:
(n(n+1)(2n+1))/6 

That is, a function with a dominant term of n^3, I will guess that this function's runtime - which will be a sum with a input whose highest term is k^2 - will also have a dominant 
term of n^3 and will thus be O(n^3).
*/
int getMaxSumv1(const vector<int> &v) {
    if (v.empty()) {
        throw invalid_argument("empty input");
    }
    int maxSum = v[0];
    for (int portionSize = 1; portionSize <= v.size(); portionSize++) { 
        for (int i = 0; i < v.size(); i++) {
            if (i + portionSize <= v.size()) {
                int currSum = 0;
                for (int j = i; j < i + portionSize; j++) {
                    currSum += v[j];
                }
                if (currSum > maxSum) {
                    maxSum = currSum;
                }
            }
        }
    }
    return maxSum;
}

/*
runtime analysis: 

inner loop first runs n times, then n-1 times, then n-2 times, down to 1 time. Using Gauss's summation formula, this algorithm is O(n^2)

1st loop: checks all sums that start with 1st entry
2nd loop: checks all sums that start with 2nd entry
...
kth loop: checks all sums that start with kth entry 

Since all subvectors must start at some index in the vector, by going through each index and using the inner loop on it, all possible subvector sums are covered. 
Differs from previous algorithm which does all 1 element subvectors, then all 2 element, then all 3 element, etc.
 */
int getMaxSumv2(const vector<int> &v) {
    if (v.empty()) {
        throw invalid_argument("empty input");
    }
    int maxSum = v[0];
    for (int i = 0; i < v.size(); i++) {
        int sum = 0; // building a sum starting at index i
        for (int j = i; j < v.size(); j++) {
            /* add next element to sum & check if this is the max 
            Note: suppose sum holds the sum of subvector v[p...q]
            Now, to calculate the sum of subvector v[p...q+1] no longer requires readding all the entries in it, but just performing v[p...q] + v[q+1] where the prior is stored in sum
             */
            sum += v[j]; 
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

int getMaxSumv3(const vector<int> &v) {
    if (v.empty()) {
        throw invalid_argument("empty input");
    }
    int maxSum = v[0];
    bool reached;
    int lbound, rbound;
    getMaxSumv3(v, maxSum, 0, v.size()-1, lbound, rbound);
    return maxSum;
}

/*
runtime analysis:

recurrence relation: 

T(n) = c                    when n = 1
T(n) = 2T(n/2) + n          otherwise

same as merge sort, which is O(nlogn)

Idea:

base case: n=1
the greatest subvector of a 1 element list is that list, its bounds are its index 

recursive case: n>1

calculate a mid point and:
1) recursively find the value of the greatest subvector of the left side and its left & right bounds
2) recursively find the value of the greatest subvector of the right side and its left & right bounds 

Let:
vL be the portion of v that is the left side
vR be "                          " right side
lhL be the left bound of the greatest subvector of the left side 
lhR be the right bound "                                        "
rhL be the left bound of the greatest subvector of the right side
rhR be the right bound "                                        "

In this part of the algorithm, we are trying to build the greatest subvector of v[l...r] and find its bounds. I will refer to the greatest subvector of v[l...r] as G and have 
bounds gL, gR. 

Observe:
If v[lhL...lhR] is the greatest subvector of the left side, then using the entries v[l...lhL] would not increase the value of G. Otherwise, they would have been included in the 
greatest subvector of vL.
If v[rhL...rhR] is the greatest subvector of the right side, then using the entries v[rhR...r] would not increase the value of G. Otherwise, they would have been included in the
greatest subvector of vR.

Let L = vL[lhL...lhR], R = vR[rhL...rhR]
Now: to create G, I will try to "expand" L and R. To do this I will try adding values from v[rhL-1...lhL] to R and values from v[lhR+1...rhR] to L. I have chosen these value sets
based on the observation above.

If either of these expansions increase the size of L and/or R, update L, R and their bounds. Compare the greater of L and R with the algorithm's tracked max. sum (see ref. param. 
maxSum). If greater(L, R) > maxSum, update maxSum. Using the updated bounds of greater(L, R), one can now set gL and gR. Then, return greater(L, R).

Now, all of the necessary information has been passed on to recursive calls higher up in the stack that can use this information to find the greatest subvector of a larger portion
of v.

Soln. manual: find max crossing over sum first, then recursively find left and right sums, then compare and return. Still O(NlogN), just that the O(N) work and recursive calls are
done in opp. order. 
  */
int getMaxSumv3(const vector<int> &v, int &maxSum, int l, int r, int &lbound, int &rbound) {
    if (l==r) {
        if (v[l] > maxSum) {
            maxSum = v[l];
        }
        lbound = l;
        rbound = r;
        return v[l];
    }

    int m = (l + r)/2;
    
    int lhLbound, lhRbound, rhLbound, rhRbound;
    int maxSumLH = getMaxSumv3(v, maxSum, l, m, lhLbound, lhRbound);        // pass 1st half of input to 1st rec. call
    int maxSumRH = getMaxSumv3(v, maxSum, m+1, r, rhLbound, rhRbound);      // pass other half to 2nd rec. call

    int expandedLHSum = maxSumLH; 
    for (int i = lhRbound + 1; i <= rhRbound; i++) { // in the worst case this runs from l to r which is O(n)
        expandedLHSum += v[i];
        if (maxSumLH < expandedLHSum) {
            lhRbound = i;
            maxSumLH = expandedLHSum;
        }
    }
    
    int expandedRHSum = maxSumRH;
    for (int j = rhLbound - 1; j >= lhLbound; j--) { // in the worst case this runs from r to l which is O(n)
        expandedRHSum += v[j];
        if (maxSumRH < expandedRHSum) {
            rhLbound = j;
            maxSumRH + expandedRHSum;
        }
    }

    if (maxSumLH > maxSumRH) {
        lbound = lhLbound;
        rbound = lhRbound;
        if (maxSumLH > maxSum) {
            maxSum = maxSumLH;
        }
        return maxSumLH;
    }
    else {
        lbound = rhLbound;
        rbound = rhRbound;
        if (maxSumRH > maxSum) {
            maxSum = maxSumRH;
        }
        return maxSumRH;
    }
    
}

/* my answer: 
int maxSum = v[0];
    int curr = v[0];

    for (int i = 1; i < v.size(); i++) {
        if (curr + v[i] < v[i]) {
            maxSum = v[i];
            curr = maxSum;
        }
        else {
            curr += v[i];
        }
        if (curr > maxSum) {
            maxSum = curr; 
        }
    }
 */
// my answer above doesn't work consider the v = {-3, -4} - but neither does the one provided in the soln. manual. 
/* Here is a soln. that seems to work from editing the one in the manual:

Keep track of the sum of the greatest subvector found so far (maxSum) as well as the sum of entries that could later be the start of a subvector greater than the one found so far
(curr). Since curr would be the sum of entries at the start of a later greater subvector, it can never be allowed to fall below 0. The fact that the greatest subvector must start
with a positive entry follows from its definition and is why curr must be >= 0. 

That is, the greatest subvector would not contain any entries on the end whose sum leads to its overall sum being lower. Otherwise, it wouldn't be the greatest b/c the greatest
would be the subvector with the entries of the former greatest subvector removed minus the ones at the start that decreased its value. 
 */
int getMaxSumv4(const vector<int> &v) {
    if (v.empty()) {
        throw invalid_argument("empty input");
    }

    int maxSum = v[0]; 
    int curr = 0;
    
    for (int i = 0; i < v.size(); i++) {
        // if the sum of the new greatest subvector being built up using curr surpasses the currently tracked greatest subvector's sum, update the stored maxSum
        maxSum = max(curr + v[i], maxSum);
        // If curr < 0, it would never be used to contribute a future greater subvector (as it would only decrease its sum), therefore, whatever negative value it holds can
        // be cast away. Reset curr to 0 so that the creation of a future greater subvector will start at v[i+1]. It doesn't matter if v[i+1] itself is positive or negative, 
        // having v[i] < 0 in its subvector would decrease its sum regardless. Vector entries that are negative should be recorded in maxSum and not replaced with 0 in the event
        // of the input vector being made up entirely of negative numbers (as discussed in the comment above the method). In that case the negative number with the smallest abs. value
        // would solely make up the greatest subvector. observe: the only way this can be identified is if curr is set to 0 here, allowing a later negative number with a smaller abs.
        // value to be compared with maxSum and then replace it. 
        curr = max(0, curr + v[i]);
        // note: curr does not include JUST the elements of v that follow the elements of the subvector whose sum is maxSum. They could overlap. For example, in the case of a vector v
        // such that the sum of v[0...k] >= 0 for all k in [0, n-1], maxSum and curr would be tracking sums starting from 0 and curr <= maxSum. It is <= and not = because
        // there could be some j in [0, n-1] such that v[j] < 0 and |v[j]| < curr where curr would be set to curr = curr + v[j], thus decreasing its value but not enough to bring
        // it below 0. Thus, curr would remain the sum of elements starting from 0. However, maxSum would be greater than curr and would not be replaced by curr. Hence curr < maxSum
        // at this stage. They become equal only if curr becomes > maxSum
    }

    return maxSum;
}