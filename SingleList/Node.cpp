#include "Node.h"

using namespace std;

Node::Node(int data_val, Node* next_ptr = nullptr): data {data_val}, next {next_ptr} {
}

Node::Node(): Node(0, nullptr) {
}

int Node::get_data() const {
  return this->data;
};
  
void Node::set_data(int data_val) {
  this->data = data_val;
};
  
Node* Node::get_next() const {
  return this->next;
}

void Node::set_next(Node* next_val) {
  this->next = next_val;
}

