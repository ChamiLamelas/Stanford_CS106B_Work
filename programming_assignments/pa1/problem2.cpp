#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std; 

void calculateInvalidResultChance(unsigned int numVoters, double percentSpread, double errorPercent, unsigned int numTrials = 500); 
bool runTrial(unsigned int numVoters, double percentSpread, double errorPercent);
void registerVote(double errorPercent, unsigned int& correct, unsigned int& incorrect);

int main() {
    unsigned int numVoters; 
    cout << "Enter number of voters: ";
    cin >> numVoters; 
    if (cin.fail() || numVoters <= 0) {
        cerr << "Number of voters must be a positive integer." << endl;
        return 1; 
    }
    double percentSpread; 
    cout << "Enter percentage spread between candidates: ";
    cin >> percentSpread;
    if (cin.fail() || percentSpread < 0 || percentSpread > 1.0) {
        cerr << "Percentage spread must be a real number in [0, 1.0]." << endl;
        return 1;
    }
    double errorPercent; 
    cout << "Enter voting error percentage: ";
    cin >> errorPercent;
    if (cin.fail() || errorPercent < 0 || errorPercent > 1.0) {
        cerr << "Error percentage must be a real number in [0, 1.0]." << endl;
        return 1;
    }
    calculateInvalidResultChance(numVoters, percentSpread, errorPercent);
    return 0;
}

void calculateInvalidResultChance(unsigned int numVoters, double percentSpread, double errorPercent, unsigned int numTrials) {
    unsigned int failedTrialCount = 0;
    srand(time(0));
    for (unsigned int i = 0; i < numTrials; i++) {
        if (!runTrial(numVoters, percentSpread, errorPercent)) {
            failedTrialCount++;
        }
    }
    cout << "Chance of an invalid election result after " << numTrials << " trials = " << ((double(failedTrialCount)/numTrials)*100) << "%" << endl;
}

bool runTrial(unsigned int numVoters, double percentSpread, double errorPercent) {
    /* Note: there is the possibility of some data loss in the following 2 calculations. Let dp = no. of digits after the decimal point in percentSpread and dn = no. of digits in
    numVoters. If dp >= dn then there is the possibility of numVoters*percentSquad being a decimal value. Then, when it is cast to an int, the decimal portion is lost.
     */
    unsigned int voterDiff = int(numVoters*percentSpread);
    unsigned int forCandW = numVoters/2 + voterDiff/2; // no. of people who were supposed to have voted for winning candidate 
    unsigned int forCandL = numVoters/2 - voterDiff/2; // no. of people who were supposed to have voted for losing candidate 
    unsigned int votesW = 0; // no. of votes registered with the winning candidate by the voting system simulator 
    unsigned int votesL = 0; // no. of votes registered with the losing candidate by the voting system simulator 
    for (int i = 0; i < forCandW; i++) { // these are people voting for winning candidate, aiming to be placed in votesW but if register fails, should go into votesL 
        registerVote(errorPercent, votesW, votesL); 
    }
    for (int i = 0; i < forCandL; i++) { // these are people voting for losing candidate, aiming to be placed in votesL but if register fails, should go into votesW
        registerVote(errorPercent, votesL, votesW);
    }
    return (forCandW > forCandL && votesW > votesL) || (forCandW == forCandL && votesW == votesL);
}

/* Registers a vote with 1 candidate or the other based on the chance of the system assigning it incorrectly.
@param errorPercent - chance of the vote being incorrectly registered 
@param correct - the count of votes that should be updated if the vote was correctly registered (i.e. for the candidate the voter supports)
@param incorrect - the count of votes that should be updated if the vote was incorrectly registered (i.e. for the candidate the voter is against)
 */
void registerVote(double errorPercent, unsigned int& correct, unsigned int& incorrect) {
    if (rand()/double(RAND_MAX) > errorPercent) {
        correct++;
    }
    else {
        incorrect++;
    }
}