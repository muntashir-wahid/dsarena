#include <iostream>
#include "SingleList.h"

using namespace std;

int main() {
  SingleList list(10);
  list.append(20);
  list.append(30);

  cout << "----- First List ------" << endl;
  list.display();


  SingleList list_two;


  cout << "----- Second List ------" << endl;
  list_two.display();

  for(int i = 1; i <= 10; i++) {
    list_two.append(i * 5);
  }
  list_two.display();

  return 0;
}
