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

int Array::get_length() const {
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

  if(!has_capacity()) throw out_of_range("Array is full");

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

void Array::left_shift() {
  for(int i = 0; i < size - 1; i++) {
    data[i] = data[i + 1];
  }

  data[size - 1] = 0;
}

void Array::left_rotate() {
  if(size <= 1) return;

  int first_element = data[0];

  for(int i = 0; i < size - 1; i++) {
    data[i] = data[i + 1];
  }

  data[size - 1] = first_element;
}

void Array::right_shift() {
  if (size == 0) return; 

  for(int i = size - 1; i > 0; i--) {
    data[i] = data[i - 1];
  }

  data[0] = 0;
}

void Array::right_rotate() {
  if(size <= 1) return;

  const int LAST_INDEX = size - 1;
  int last_element = data[LAST_INDEX];

  for(int i = LAST_INDEX; i > 0; i--) {
    data[i] = data[i - 1];
  }

  data[0] = last_element;
}

void Array::merge(const Array &new_array) {
  
  if(!this->is_sorted() || !new_array.is_sorted()) {
    throw runtime_error("Both arrays must be sorted in ascending order before merging.");
  }

  const int required_capacity = new_array.get_length() + this->size;
  const int merged_array_capacity = required_capacity > this->capacity ? required_capacity : this->capacity;

  int *merged_data = new int[merged_array_capacity];

  int i = 0; 
  int j = 0; 
  int k = 0;

  while(i < this->size && j < new_array.get_length()) {
    if(data[i] < new_array.at(j)) {
      merged_data[k] = data[i];
      i++;
      k++;
    } else {
      merged_data[k] = new_array.at(j);
      j++;
      k++;
    }
  }

  while (i < this->size) {
    merged_data[k] = data[i];
    i++;
    k++; 
  }
  
  while (j < new_array.get_length()) {
    merged_data[k] = new_array.at(j);
    j++;
    k++; 
  }

  this->capacity = merged_array_capacity;
  this->size = k;
  delete[] this->data;
  this->data = merged_data;
}

void Array::swap(int index_one, int index_two) {
  if(!this->is_valid_index(index_one) || !this->is_valid_index(index_two)) {
    throw out_of_range("Invalid index");
  }

  int temp_val = this->data[index_one];

  this->data[index_one] = this->data[index_two];
  this->data[index_two] = temp_val;
}

void Array::selection_sort() {

  for(int i = 0; i < this->size - 1; i++) {
    int min_index = i;

    for(int j = i + 1; j < this->size; j++) {
      if(this->data[j] < this->data[min_index]) {
        min_index = j;
      }
    }

    this->swap(i, min_index);
  }
}