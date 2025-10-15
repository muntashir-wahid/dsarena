#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main() {
  DynamicArray arr(2);

  arr.append(2);
  arr.append(4);
  arr.append(6);

  cout << "Length of the array: " << arr.get_length() << endl;
  arr.display();


  return 0;
}
