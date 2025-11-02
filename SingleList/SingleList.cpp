#include <iostream>
#include "SingleList.h"

using namespace std;


SingleList::SingleList(int val) {
  this->head = new Node(val, nullptr);
  this->tail = this->head;
  this->size = 1;
}

SingleList::SingleList(): head {nullptr}, tail {nullptr}, size {0} {
}


SingleList::~SingleList() {
  Node* curr_node = this->head;

  while(curr_node) {
    Node* to_be_deleted = curr_node;
    curr_node = curr_node->get_next();

    delete to_be_deleted;
  }
}

bool SingleList::is_empty() const {
  return this->size == 0;
}

int SingleList::get_size() const {
  return this->size;
}

void SingleList::append(int val) {
  Node* new_node = new Node(val, nullptr);

  if(this->is_empty()) {
    this->head = new_node;
    this->tail = new_node;
  } else {
    this->tail->set_next(new_node);
    this->tail = new_node;
  }

  this->size++;
  
}

void SingleList::display() const {
  if(this->size == 0) {
    cout << "{empty}" << endl;
    return;
  }

  Node* curr_node = this->head;

  cout << "{";
  while(curr_node) {
    cout << curr_node->get_data();
    if(curr_node->get_next()) {
      cout << " -> ";
    }

    curr_node = curr_node->get_next();
  }
  cout << "}";

  cout << endl;
}