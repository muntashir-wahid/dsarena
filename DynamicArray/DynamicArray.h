#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Array.h"

class DynamicArray : public Array {
private:
    void resize();

public:
    DynamicArray(int initial_capacity);

    ~DynamicArray();

    void append(int new_element);

    void insert(int index, int new_element);
};

#endif