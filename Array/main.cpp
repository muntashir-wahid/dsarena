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

    cout << "---- First Array ----" << endl;
    arr.display();

    Array arr_new(10);
    arr_new.append(1);
    arr_new.append(3);
    arr_new.append(5);
    arr_new.append(15);
    arr_new.append(20);
    arr_new.append(22);

    cout << "---- Second Array ----" << endl;
    arr_new.display();

    arr.merge(arr_new);

    cout << "---- After Merge ----" << endl;
    arr.display();

    // arr.append(12);
    // arr.display();

    return 0;
}