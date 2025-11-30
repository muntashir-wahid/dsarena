#include <iostream>
#include "Array.h"
using namespace std;

int main() {
    Array arr(10); 

    arr.append(20);
    arr.append(4);
    arr.append(2);
    arr.append(19);
    arr.append(12);
    arr.append(16);

    cout << "---- First Array before sort ----" << endl;
    arr.display();

    cout << "---- First Array before sort ----" << endl;
    arr.selection_sort();
    arr.display();




    return 0;
}