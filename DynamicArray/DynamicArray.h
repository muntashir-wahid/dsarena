#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

class DynamicArray {
private:
    int *data;
    int size;
    int capacity;
    static const int NOT_FOUND = -1;

    // Private helper methods
    bool has_capacity() const;

    bool is_valid_position(int index) const;

    bool is_valid_index(int index) const;

    void resize();
public:
    // Constructor
    DynamicArray(int capacity);

    // Destructor
    ~DynamicArray();

    int get_length() const;

    void append(int new_element);

    void display() const;

    void insert(int index, int new_element);

    int remove(int index);

    int at(int index) const;

    void set(int index, int new_element);
};

#endif