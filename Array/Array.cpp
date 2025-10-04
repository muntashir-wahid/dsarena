#include "Array.h"
#include <iostream>
using namespace std;

Array::Array(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    data = new int[capacity];
}

Array::~Array() {
    delete[] data;
}

