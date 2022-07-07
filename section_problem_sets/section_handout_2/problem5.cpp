#include <iostream> 
#include <vector>
using namespace std; 

typedef vector<vector<bool> > locationsGrid; 
typedef vector<vector<int> > neighborhoodCountsGrid;

neighborhoodCountsGrid makeGridOfCounts(locationsGrid loc);
unsigned int scanNeighborhood(unsigned int i, unsigned int j, const locationsGrid& loc);

int main() {
    cout << "Enter the height, a space, then the width: ";
    unsigned int height; 
    cin >> height;
    if (cin.fail()) {
        cerr << "Height value not accepted: it must be a nonnegative integer." << endl;
        return 1; 
    }
    unsigned int width; 
    cin >> width; 
    if (cin.fail()) {
        cerr << "Width value not accepted: it must be a nonnegative integer." << endl;
        return 1;
    }

    locationsGrid loc(height);

    cout << "Now filling locations grid. Will move left->right then top->bottom." << endl;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            cout << "Enter a value for position (" << j << ", " << i << "): ";
            bool val;
            cin >> val;
            if (cin.fail()) {
                cerr << "Input value not accepted." << endl;
                return 1;
            }
            loc[i].push_back(val);
        }
    }

    neighborhoodCountsGrid ngb = makeGridOfCounts(loc);

    cout << "Locations Grid: " << endl;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            cout << loc[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nNeighbordhood Counts Grid: " << endl;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            cout << ngb[i][j] << " ";
        }
        cout  << endl;
    }
    return 0;
}

neighborhoodCountsGrid makeGridOfCounts(locationsGrid loc) {
    neighborhoodCountsGrid ngb(loc.size());

    if (loc.size() > 0) {
        for (unsigned int i = 0; i < ngb.size(); i++) {
           for (unsigned int j = 0; j < loc[0].size(); j++) {
               ngb[i].push_back(scanNeighborhood(i, j, loc));
           }
        }
    }

    return ngb;
}

/* From soln. manual in reference to helper function 'MarkBomb()': 

"Note that MarkBomb uses two for loops to iterate through the 9 squares it needs to update
rather than having a separate case for each square. If it had a separate case for each, this
would not only be more messy and less elegant, but it would be more error prone. This is
because while writing out 9 different cases, you are much more likely to make an error on
one of the lines than if you are only writing out two for loops."

That is both loops go from -1 to 1 and then the 9 combinations are made by adding to i and j respectively. 
 */

// pre-condition: loc has a size > 0 and (x, y) is in the grid.
unsigned int scanNeighborhood(unsigned int i, unsigned int j, const locationsGrid& loc) {
    /* Consider the following grid where A is at (x, y) and is thus on the grid. B-H may or may not be on the grid, and will be checked below. When I say, add some letter X after it has been checked to be in the
    grid, assume I am adding the boolean value represented by it, not a character.

        C | E | H
        ---------
        B | A | G
        ---------
        D | F | I
     */
    unsigned int numMines = loc[i][j]; // adds A to numMines (always possible given pre-condition)
    if (i > 0) { // check if one can add C, B, or D 
        numMines += loc[i - 1][j]; // by virtue of y being in grid by pre-condition, can now add B 
        if (j > 0) { // check if one can add C, if so add it
            numMines += loc[i - 1][j - 1];  
        }
        if (j + 1 < loc[0].size()) { // check if one can add D, if so add it 
            numMines += loc[i - 1][j + 1]; 
        }
    }
    if (j > 0) { // checks if one can add E 
        numMines += loc[i][j - 1];    // by virtue of x being in grid by pre-condition, can now add E 
    }
    if (j + 1 < loc[0].size()) { // checks if one can add F 
        numMines += loc[i][j + 1];  // by virtue of x being in grid by pre-condition, can now add F 
    }
    if (i + 1 < loc.size()) { // checks if one can add H, G, or I 
        numMines += loc[i + 1][j]; // by virtue of y being in grid by ore-condition, can now add G 
        if (j > 0) { // check if one can add H, if so add it 
            numMines += loc[i + 1][j - 1];   
        }
        if (j + 1 < loc.size()) { // checks if one can add I, if so add it
            numMines += loc[i + 1][j + 1];
        }
    }
    return numMines;
}