#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
    int *data;
    int size;
    int capacity;
    static const int NOT_FOUND = -1;

    // Private helper methods
    bool has_capacity() const;

    bool is_valid_position(int index) const;

    bool is_valid_index(int index) const;

public:
    // Constructor
    Array(int capacity);

    // Destructor
    ~Array();

    int getLength() const;

    void append(int new_element);

    void display() const;

    void insert(int index, int new_element);

    int remove(int index);

    int first_index_of(int key) const;

    int at(int index) const;

    void set(int index, int new_element);

    bool is_sorted(bool ascending = true) const;

    void reverse();

    void left_shift();

    void left_rotate();

    void right_shift();

    void right_rotate();
};

#endif
