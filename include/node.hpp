#pragma once

namespace itis {
  struct Node {
   public:
    int data;
    Node *parent;
    Node *left_child;
    Node *right_child;

    explicit Node(int data) {
      this->data = data;
      this->parent = nullptr;
      this->left_child = nullptr;
      this->right_child = nullptr;
    }
  };
}  // namespace itis
