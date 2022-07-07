#include <queue>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
void filter(queue<T> &q, bool (filterFn)(const T&)) {
    size_t qSize = q.size();
    for (size_t i = 0; i < qSize; i++) {
        T tmp = q.front();
        q.pop();
        if (!filterFn(tmp)) {
            q.push(tmp);
        }
    }
}

struct recordingT {
    string title;
    string genre;
    int rating;
};

bool recordingFilter(const recordingT &record) {
    return record.genre == "animation" && record.rating < 8;
}

int main() {
    queue<recordingT> q;

    while (true) {
        cout << "Adding recording into Queue.\nTitle (RETURN to exit): ";
        recordingT rec;
        getline(cin, rec.title);
        if (rec.title.empty()) {
            break;
        }
        cout << "Genre: ";
        getline(cin, rec.genre);
        cout << "Rating: ";
        cin >> rec.rating;
        cin.ignore();
        q.push(rec);
    }

    filter(q, recordingFilter);

    cout << "Emptying Queue: ";
    while (!q.empty()) {
        recordingT front = q.front();
        cout << '(' << front.title << ", " << front.genre << ", " << front.rating << ") ";
        q.pop();
    }
    cout << endl;

    return 0;
}