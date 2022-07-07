#include <queue>
#include <iostream>
using namespace std;

queue<int> extractStrand(queue<int> &q);

int main() {
    queue<int> input;

    while (true) {
        cout << "Enter a number (non-number to exit): ";
        int entry;
        cin >> entry;
        if (cin.fail()) {
            break;
        }
        else {
            input.push(entry);
        }
    }

    queue<int> output = extractStrand(input);
    cout << "Extracted Strand: ";
    while (!output.empty()) {
        cout << output.front() << ' ';
        output.pop();
    }
    cout << "\nRemaining input: ";
    while (!input.empty()) {
        cout << input.front() << ' ';
        input.pop();
    }
    cout << endl;

    return 0;
}

queue<int> extractStrand(queue<int> &q) {
    queue<int> out;
    if (!q.empty()) {
        out.push(q.front());
        int lastAdded = q.front();
        q.pop();

        // not needed, could just condense into the following loop.. nothing gained here
        // while (!q.empty() && lastAdded <= q.front()) {
        //     out.push(q.front());
        //     lastAdded = q.front();
        //     q.pop();
        // }

        int numLeft = q.size();
        for (int i = 0; i < numLeft; i++) {
            if (lastAdded <= q.front()) {
                out.push(q.front());
                lastAdded = q.front();
                q.pop();
            }
            else {
                q.push(q.front());
                q.pop();
            }
        }
    }
    return out;
}