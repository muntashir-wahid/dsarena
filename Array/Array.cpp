#include "Array.h"
#include <iostream>
using namespace std;

// Private helper methods
bool Array::has_capacity() const {
  return size < capacity;
}

bool Array::is_valid_position(int index) const {
  return index > -1 && index <= size; // For insert position checking
}

bool Array::is_valid_index(int index) const {
  return index > -1 && index < size; // For valid index checking
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

void Array::insert(int index, int new_element) {
  if(!is_valid_position(index)) {
    throw out_of_range("Invalid index");
  }

  for(int i = size; i > index; i--) {
    data[i] = data[i - 1];
  }

  data[index] = new_element;
  size++;
}

int Array::remove(int index) {
  if(!is_valid_index(index)) {
    throw out_of_range("Invalid index");
  }

  int removed_element = data[index];

  for(int i = index; i < size - 1; i++) {
    data[i] = data[i + 1];
  }

  size--;

  return removed_element;
}

int Array::first_index_of(int key) const {
  int key_index = NOT_FOUND;

  for(int i = 0; i < size; i++) {
    if(data[i] == key) {
      key_index = i;
      break;
    }
  }

  return key_index;
}

int Array::at(int index) const {
  if(!is_valid_index(index)) {
    throw out_of_range("Invalid index");
  }

  return data[index];
}

void Array::set(int index, int new_element) {
  if(!is_valid_index(index)) {
    throw out_of_range("Invalid index");
  }

  data[index] = new_element;
}

bool Array::is_sorted(bool ascending) const {
  for(int i = 0; i < size - 1; i++) {
    if(ascending && data[i] > data[i + 1]) return false;
    if(!ascending && data[i] < data[i + 1]) return false;
  }

  return true;
}

void Array::reverse() {
  if(size <= 1) return;

  int left = 0;
  int right = size - 1;

  while(left < right) {
    int temp = data[left];
    data[left] = data[right];
    data[right] = temp;

    left++;
    right--;
  }

}