#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
    static const int NOT_FOUND = -1;

protected:
    int *data;
    int size;
    int capacity;

    // Private helper methods
    bool has_capacity() const;

    bool is_valid_position(int index) const;

    bool is_valid_index(int index) const;

public:
    // Constructor
    Array(int capacity);

    // Destructor
    ~Array();

    int get_length() const;

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

    void merge(const Array&);

    void swap(int index_one, int index_two);

    // Sorting Algorithms
    void selection_sort();
};

#endif
