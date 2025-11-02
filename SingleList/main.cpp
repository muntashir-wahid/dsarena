#include <iostream>
#include "Node.h"

using namespace std;

int main() {
  Node *first_node = new Node(20, nullptr);

  cout << first_node->get_data() << endl;

  delete first_node;

  return 0;
}
