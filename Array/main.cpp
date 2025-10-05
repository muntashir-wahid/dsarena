#include <iostream>
#include "Array.h"
using namespace std;

int main() {
    Array arr(10); 
    cout << "Size of the array is: " << arr.getLength() << endl;

    arr.append(2);
    arr.append(4);
    arr.append(6);
    arr.append(9);
    arr.append(12);
    arr.append(16);

    arr.insert(3, 8);

    arr.display();

    int index = 7;
    cout << "Element at index: " << index << ", is: " << arr.at(index) << endl;
    
    return 0;
}