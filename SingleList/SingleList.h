#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include "Node.h"


class SingleList {
private:
  Node* head;
  Node* tail;
  int size;

public:
  SingleList(int val);
  SingleList();
  ~SingleList();

  bool is_empty() const;

  int get_size() const;

  void append(int val);

  void prepend(int val);

  void display() const;

  int remove_first();

  int remove_last();

  int get_first() const;

  int get_last() const;

  int get(int index) const;

  void set(int index, int val);

  int find(int val) const;

  void insert(int index, int val);

  int remove_at(int index);

  void clear();
};

#endif