#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
    int *data;
    int size;
    int capacity;

    // Private helper methods
    bool has_capacity() const;

public:
    // Constructor
    Array(int capacity);

    // Destructor
    ~Array();

    int getLength() const;

    void append(int new_element);

    void display() const;
};

#endif
