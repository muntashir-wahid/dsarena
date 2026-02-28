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

  list_two.display();

  for(int i = 1; i <= 10; i++) {
    list_two.append(i * 5);
  }

  cout << "----- Second List Before Remove ------" << endl;
  list_two.display();

  list_two.remove_at(0);

  cout << "----- Second List After Remove ------" << endl;
  list_two.display();

  return 0;
}
