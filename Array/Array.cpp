#include "Array.h"
#include <iostream>
using namespace std;

// Private helper methods
bool Array::has_capacity() const {
  return this->size < this->capacity;
}

Array::Array(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    data = new int[capacity];
}

Array::~Array() {
    delete[] data;
}

int Array::getLength() const {
  return size;
}

void Array::append(int new_element) {
  if(!has_capacity()) {
    throw out_of_range("Array is full. Cannot append element.");
  }

  data[size] = new_element;
  size++;

}

void Array::display() const {
  cout << "{";

  for(int i = 0; i < size; i++) {
    if(i != size - 1) {
      cout << data[i] << ", ";
    } else {
      cout << data[i];
    }
  }

  cout << "}" << endl;
}