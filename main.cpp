#include <bits/stdtr1c++.h>

using namespace std;

int main() {
    /*
    pair<int, int> numsPair = {1, 3};

    cout << "First element of the Pair: " << numsPair.first << ", and second element of the pair: " << numsPair.second << endl;

    pair<int, int> numPairs[] = {{2, 3}, {2, 5}, {3, 6}};

    for(int i = 0; i < 3; i++) {
        cout << "First: " << numPairs[i].first << ", second: " << numPairs[i].second << endl;
    } 
    */

    vector<int> numsVec(10, 50);

    for(vector<int>::iterator it = numsVec.begin(); it != numsVec.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}