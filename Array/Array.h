#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
    int *data;
    int size;
    int capacity;

public:
    // Constructor
    Array(int capacity);

    // Destructor
    ~Array();
};

#endif
