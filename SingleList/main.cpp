#include <iostream>
#include "SingleList.h"

using namespace std;

int main() {
  // SingleList list(10);
  // list.append(20);
  // list.append(30);
  // list.prepend(2);

  // cout << "----- First List ------" << endl;
  // list.display();

  // list.remove_last();

  // list.display();


  SingleList list_two;


  cout << "----- Second List ------" << endl;
  list_two.display();

  for(int i = 1; i <= 10; i++) {
    list_two.append(i * 5);
  }

  list_two.display();

  cout << list_two.find(26);

  return 0;
}
