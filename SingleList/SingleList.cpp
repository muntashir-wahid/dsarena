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

void SingleList::prepend(int val) {
  Node* new_node = new Node(val, nullptr);

  if(this->is_empty()) {
    this->head = new_node;
    this->tail = new_node;
  } else {
    new_node->set_next(this->head);
    this->head = new_node;
  }

  this->size++;
}

void SingleList::display() const {
  if(this->is_empty()) {
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

int SingleList::remove_first() {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  Node* to_be_deleted = this->head;
  int deleted_node_val = to_be_deleted->get_data();

  this->head = to_be_deleted->get_next();

  if(this->size == 1) {
    this->tail = nullptr;
  }

  this->size--;
  delete to_be_deleted;

  return deleted_node_val;
}

int SingleList::remove_last() {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  int deleted_node_val = this->tail->get_data();

  if(this->size == 1) {
    this->head = nullptr;
    this->tail = nullptr;
    this->size--;
    return deleted_node_val;
  }

  Node* curr_node = this->head;
  for(int i = 0; i < this->size - 2; i++) {
    curr_node = curr_node->get_next();
  }

  delete this->tail;
  this->size--;
  this->tail = curr_node;
  this->tail->set_next(nullptr);

  return deleted_node_val;
}

int SingleList::get_first() const {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  return this->head->get_data();
}

int SingleList::get_last() const {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  return this->tail->get_data();
}

int SingleList::get(int index) const {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  if(index >= this->size || index < 0) {
    throw out_of_range("Out of range");
  }

  Node* curr_node = this->head;
  
  for(int i = 0; i < index; i++) {
    curr_node = curr_node->get_next();
  }

  return curr_node->get_data();
}

void SingleList::set(int index, int val) {
  if(this->is_empty()) {
    throw out_of_range("List is empty");
  }

  if(index >= this->size || index < 0) {
    throw out_of_range("Out of range");
  }

  Node* curr_node = this->head;
  
  for(int i = 0; i < index; i++) {
    curr_node = curr_node->get_next();
  }

  curr_node->set_data(val);
}

int SingleList::find(int val) const {
  if(this->is_empty()) {
    return -1;
  }

  Node* curr_node = this->head;
  int index = 0;

  while(curr_node) {
    if(curr_node->get_data() == val) {
      return index;
    }

    curr_node = curr_node->get_next();

    index++;
  }


  return -1;
}