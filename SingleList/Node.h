#ifndef NODE_H
#define NODE_H


class Node {
private:
  int data;
  Node* next;

public:
  Node();
  Node(int data, Node* next);


  int get_data() const;
  void set_data(int data_val);
  Node* get_next() const;
  void set_next(Node* next_val);
};

#endif