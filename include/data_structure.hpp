#pragma once
#include "node.hpp"
// Заголовочный файл с объявлением структуры данных

namespace itis {

  struct SplayTree {
   public:
    Node *root;

    static void zig(Node *x);
    static void zig_zig(Node *x);
    static void zig_zag(Node *x);
    void splay(Node *x);

    SplayTree();
    explicit SplayTree(Node *x);
    Node *search(int x);
    void insert(int x);
    void remove(int x);
    void split(Node *x);
    Node *merge(SplayTree *s, SplayTree *t);
    void prettyPrint(Node *x);
    ~SplayTree();
  };

}  // namespace itis