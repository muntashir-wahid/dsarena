#include <iostream>
#include "Array.h"
using namespace std;

int main() {
    Array arr(10); 

    arr.append(2);
    arr.append(4);
    arr.append(6);
    arr.append(9);
    arr.append(12);
    arr.append(16);
    arr.insert(3, 8);
    // arr.set(4, 160);

    cout << "---- Array before reverse ----" << endl;
    arr.display();
    cout << "Array is sorted in ascending order: " << arr.is_sorted() << endl;

    cout << "---- Array After reverse ----" << endl;
    arr.reverse();
    arr.display();
    cout << "Array is sorted in deacending order: " << arr.is_sorted() << endl;

    return 0;
}