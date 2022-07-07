#include <iostream> 
using namespace std; 

int numCannonballs(int height) {
    if (height <= 1) {
        return height;
    }
    else {
        return height*height + numCannonballs(height - 1);
    }
}

int main() {
    int h;
    bool gotValidHeight = false;
    cout << "Enter a valid height: ";
    while (!gotValidHeight) {
        cin >> h;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cerr << "Height must be a positive integer, try again: ";
        }
        else if (h < 0) {
            cerr << "Height (" << h << ") cannot be negative, try again: ";
        }
        else {
            gotValidHeight = true;
        }
    }

    cout << "Cannonball pyramid has " << numCannonballs(h) << " cannonballs." << endl;
    return 0;
}