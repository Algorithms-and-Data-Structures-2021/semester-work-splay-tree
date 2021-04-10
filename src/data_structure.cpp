#include "data_structure.hpp"
#include <iostream>

namespace itis {

  SplayTree::SplayTree() {
    this->root = nullptr;
  }

  void Clear(Node *x) {
    if (x->left_child != nullptr || x->right_child != nullptr) {
      if (x->left_child != nullptr && x->right_child == nullptr) {
        Clear(x->left_child);
        delete x;
      } else if (x->left_child == nullptr && x->right_child != nullptr) {
        Clear(x->right_child);
        delete x;
      } else {
        Clear(x->left_child);
      }
    } else {
      delete x;
    }
  }

  SplayTree::SplayTree(Node *root) {
    this->root = root;
  }

  SplayTree::~SplayTree() {
    Node *curr = this->root;
    Clear(curr);
  }

  void SplayTree::zig(Node *x) {
    Node *parent_node = x->parent;

    if (parent_node->left_child == x) {
      Node *A = x->right_child;

      x->parent = nullptr;
      x->right_child = parent_node;

      parent_node->parent = x;
      parent_node->left_child = A;

      if (A != nullptr) {
        A->parent = parent_node;
      }
    } else {
      Node *A = x->left_child;

      x->parent = nullptr;
      x->left_child = parent_node;

      parent_node->parent = x;
      parent_node->right_child = A;

      if (A != nullptr) {
        A->parent = parent_node;
      }
    }
  }

  void SplayTree::zig_zig(Node *x) {
    Node *parent_node = x->parent;
    Node *grandparent_node = parent_node->parent;

    if (parent_node->left_child == x) {
      Node *A = x->right_child;
      Node *B = parent_node->right_child;

      x->parent = grandparent_node->parent;
      x->right_child = parent_node;

      parent_node->parent = x;
      parent_node->left_child = A;
      parent_node->right_child = grandparent_node;

      grandparent_node->parent = parent_node;
      grandparent_node->left_child = B;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }
      if (A != nullptr) {
        A->parent = parent_node;
      }
      if (B != nullptr) {
        B->parent = grandparent_node;
      }
    } else {
      Node *A = parent_node->left_child;
      Node *B = x->left_child;

      x->parent = grandparent_node->parent;
      x->left_child = parent_node;

      parent_node->parent = x;
      parent_node->left_child = grandparent_node;
      parent_node->right_child = B;

      grandparent_node->parent = parent_node;
      grandparent_node->right_child = A;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }

      if (A != nullptr) {
        A->parent = grandparent_node;
      }

      if (B != nullptr) {
        B->parent = parent_node;
      }
    }
  }

  void SplayTree::zig_zag(Node *x) {
    Node *parent_node = x->parent;
    Node *grandparent_node = parent_node->parent;

    if (parent_node->right_child == x) {
      Node *A = x->left_child;
      Node *B = x->right_child;

      x->parent = grandparent_node->parent;
      x->left_child = parent_node;
      x->right_child = grandparent_node;

      parent_node->parent = x;
      parent_node->right_child = A;

      grandparent_node->parent = x;
      grandparent_node->left_child = B;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }

      if (A != nullptr) {
        A->parent = parent_node;
      }

      if (B != nullptr) {
        B->parent = grandparent_node;
      }
    } else {
      Node *A = x->left_child;
      Node *B = x->right_child;

      x->parent = grandparent_node->parent;
      x->left_child = grandparent_node;
      x->right_child = parent_node;

      parent_node->parent = x;
      parent_node->left_child = B;

      grandparent_node->parent = x;
      grandparent_node->right_child = A;

      if (x->parent != nullptr) {
        if (x->parent->left_child == grandparent_node) {
          x->parent->left_child = x;
        } else {
          x->parent->right_child = x;
        }
      }

      if (A != nullptr) {
        A->parent = grandparent_node;
      }

      if (B != nullptr) {
        B->parent = parent_node;
      }
    }
  }

  void SplayTree::splay(Node *x) {
    while (x->parent != nullptr) {
      Node *parent_node = x->parent;
      Node *grandparent_node = parent_node->parent;
      if (grandparent_node == nullptr) {
        zig(x);
      }
      else if (grandparent_node->left_child == parent_node && parent_node->left_child == x) {
        zig_zig(x);
      }
      else if (grandparent_node->right_child == parent_node && parent_node->right_child == x) {
        zig_zig(x);
      }
      else {
        zig_zag(x);
      }
    }
    this->root = x;
  }

  Node *tree_max_key(Node *root) {
    Node *curr = root;
    while (curr->right_child != nullptr) {
      curr = curr->right_child;
    }
    return curr;
  }

  Node *tree_min_key(Node *subRoot) {
    Node *curr = subRoot;
    while (curr->left_child != nullptr) {
      curr = curr->left_child;
    }
    return curr;
  }

  void SplayTree::remove(int x) {
    Node *del = search(x);
    if (del == nullptr) {
      return;
    }
    Node *L = del->left_child;
    if (L == nullptr) {
      root = del->right_child;
      root->parent = nullptr;
      delete del;
      return;
    }
    while (L->right_child != nullptr) {
      L = L->right_child;
    }
    if (del->right_child != nullptr) {
      L->right_child = del->right_child;
      del->right_child->parent = L;
    }
    root = del->left_child;
    root->parent = nullptr;
    delete del;
  }

  void SplayTree::insert(int x) {
    if (root == nullptr) {
      root = new Node(x);
      return;
    }
    Node *curr = this->root;
    while (curr != nullptr) {
      if (x < curr->data) {
        if (curr->left_child == nullptr) {
          Node *new_node = new Node(x);
          curr->left_child = new_node;
          new_node->parent = curr;
          splay(new_node);
          this->root = new_node;
          return;
        } else {
          curr = curr->left_child;
        }
      } else if (x >= curr->data) {
        if (curr->right_child == nullptr) {
          Node *new_node = new Node(x);
          curr->right_child = new_node;
          new_node->parent = curr;
          splay(new_node);
          this->root = new_node;
          return;
        } else {
          curr = curr->right_child;
        }
      } else {
        splay(curr);
        return;
      }
    }
  }

  Node *SplayTree::search(int x) {
    Node *ret = nullptr;
    Node *curr = this->root;
    Node *prev = nullptr;
    while (curr != nullptr) {
      prev = curr;
      if (x < curr->data) {
        curr = curr->left_child;
      } else if (x > curr->data) {
        curr = curr->right_child;
      } else {
        ret = curr;
        break;
      }
    }
    if (ret != nullptr) {
      splay(ret);
    } else if (prev != nullptr) {
      splay(prev);
    }
    return ret;
  }

  Node *SplayTree::merge(SplayTree *s, SplayTree *t) {
    Node *x = tree_max_key(s->root);
    splay(x);
    x->right_child = t->root;
    t->root->parent = x;
    return x;
  }

  void SplayTree::split(Node *x) {
    splay(x);
    Node *s = nullptr;
    Node *t = nullptr;
    if (x->right_child) {
      t = x->right_child;
      t->parent = nullptr;
    } else {
      t = nullptr;
    }
    s = x;
    s->right_child = nullptr;
    x = nullptr;
  }

  void SplayTree::prettyPrint(Node *vertex) {
    if (vertex->left_child != nullptr && vertex->right_child != nullptr) {
      std::cout << vertex->data << ": " << vertex->left_child->data << ", " << vertex->right_child->data << std::endl;
    } else if (vertex->left_child != nullptr) {
      std::cout << vertex->data << ": " << vertex->left_child->data << std::endl;
    } else if (vertex->right_child != nullptr) {
      std::cout << vertex->data << ": " << vertex->right_child->data << std::endl;
    } else {
      std::cout << vertex->data << ": no children" << std::endl;
    }
    if (vertex->left_child != nullptr && vertex->right_child != nullptr) {
      prettyPrint(vertex->left_child);
      prettyPrint(vertex->right_child);
    } else if (vertex->left_child != nullptr) {
      prettyPrint(vertex->left_child);
    } else if (vertex->right_child != nullptr) {
      prettyPrint(vertex->right_child);
    }
  }

  int main() {
    SplayTree *sTree = new SplayTree();
    sTree->insert(7);
    sTree->insert(7);
    sTree->insert(7);
    sTree->insert(9);
    sTree->insert(1);
    sTree->insert(5);
    sTree->insert(5);
    sTree->insert(6);
    Node *tree_root = sTree->root;
    sTree->prettyPrint(tree_root);
    return 0;
  }

}  // namespace itis