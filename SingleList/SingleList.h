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
};

#endif