#include "DynamicArray.h"
#include <iostream>

using namespace std;

// Private helper methods
void DynamicArray::resize() {
  capacity *= 2;
  int *new_data = new int[capacity];

  for(int i = 0; i < size; i++) {
    new_data[i] = data[i];
  }

  delete[] data;

  data = new_data;
}


// Public methods
DynamicArray::DynamicArray(int initial_capacity) : Array(initial_capacity) {
}

DynamicArray::~DynamicArray() {
  // Base class destructor is called automatically - no need to call it explicitly
}

void DynamicArray::append(int new_element) {
  if(!has_capacity()) {
    cout << "Array capacity short: " << capacity << endl;
    resize();

    cout << "Increased capacity: " << capacity << endl;
  }

  Array::append(new_element);
}

void DynamicArray::insert(int index, int new_element) {
  if(!has_capacity()) {
    cout << "Array capacity short: " << capacity << endl;
    resize();

    cout << "Increased capacity: " << capacity << endl;
  }

  Array::insert(index, new_element);
}

