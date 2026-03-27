#include <cassert>
#include <iostream>
 
struct Node {
  std::string key;
  std::string val;
 
  Node* l = nullptr;
  Node* r = nullptr;
  Node* parent = nullptr;
 
  Node(const std::string& key, const std::string& val)
      : key(key), val(val), l(nullptr), r(nullptr), parent(nullptr) {};
};
 
struct SplayTree {
 private:
  Node* root_ = nullptr;
 
  static void SetLeft(Node* parent, Node* child) {
    if (Exists(parent)) {
      parent->l = child;
    }
    if (Exists(child)) {
      child->parent = parent;
    }
  }
 
  static void SetRight(Node* parent, Node* child) {
    if (Exists(parent)) {
      parent->r = child;
    }
    if (Exists(child)) {
      child->parent = parent;
    }
  }
 
  static void LeftRotation(Node* cur_vertex) {
    Node* cur = cur_vertex->r;
    Node* grand = cur_vertex->parent;
    SetRight(cur_vertex, cur->l);
    SetLeft(cur, cur_vertex);
    cur->parent = grand;
    if (Exists(grand)) {
      if (grand->l == cur_vertex) {
        grand->l = cur;
      } else {
        grand->r = cur;
      }
    }
  }
 
  static void RightRotation(Node* cur_vertex) {
    Node* cur = cur_vertex->l;
    Node* grand = cur_vertex->parent;
    SetLeft(cur_vertex, cur->r);
    SetRight(cur, cur_vertex);
    cur->parent = grand;
    if (Exists(grand)) {
      if (grand->l == cur_vertex) {
        grand->l = cur;
      } else {
        grand->r = cur;
      }
    }
  }
 
  Node* Splay(Node* cur) {
    if (!Exists(cur)) {
      return cur;
    }
    while (Exists(cur->parent)) {
      Node* par = cur->parent;
      Node* grand = par->parent;
      if (cur == par->l) {
        if (!Exists(grand)) {
          RightRotation(par);
        } else if (par == grand->l) {
          RightRotation(grand);
          RightRotation(par);
        } else {
          RightRotation(par);
          LeftRotation(grand);
        }
      } else {
        if (!Exists(grand)) {
          LeftRotation(par);
        } else if (par == grand->r) {
          LeftRotation(grand);
          LeftRotation(par);
        } else {
          LeftRotation(par);
          RightRotation(grand);
        }
      }
    }
    root_ = cur;
    return cur;
  }
 
  std::pair<Node*, Node*> Split(Node* cur, const std::string& key) {
    if (!Exists(cur)) {
      return {nullptr, nullptr};
    }
 
    cur = Find(cur, key);
    Splay(cur);
    Node* left;
    Node* right;
    if (cur->key >= key) {
      left = cur->l;
      cur->l = nullptr;
      if (Exists(left)) {
        left->parent = nullptr;
      }
      right = cur;
    } else {
      right = cur->r;
      cur->r = nullptr;
      if (Exists(right)) {
        right->parent = nullptr;
      }
      left = cur;
    }
    return {left, right};
  }
 
  Node* Find(Node* cur, const std::string& key) {
    if (!Exists(cur)) {
      return nullptr;
    }
 
    Node* cur_ans = nullptr;
    if (cur->key == key) {
      cur_ans = cur;
    }
    if (cur->key < key) {
      cur_ans = Find(cur->r, key);
    }
    if (cur->key > key) {
      cur_ans = Find(cur->l, key);
    }
 
    return (Exists(cur_ans) ? cur_ans : cur);
  }
 
 public:
  static bool Exists(Node* cur) { return (cur != nullptr); }
 
  void Insert(const std::string& key, const std::string& val) {
    auto [left, right] = Split(root_, key);
    Node* cur_node = new Node(key, val);
 
    cur_node->l = left;
    if (Exists(left)) {
      left->parent = cur_node;
    }
    cur_node->r = right;
    if (Exists(right)) {
      right->parent = cur_node;
    }
    root_ = cur_node;
  }
 
  Node* Find(const std::string& key) {
    Node* cur = Find(root_, key);
    root_ = Splay(cur);
    return root_;
  }
 
  static void Clear(Node* cur) {
    if (!Exists(cur)) {
      return;
    }
    Clear(cur->l);
    Clear(cur->r);
    delete cur;
  }
 
  ~SplayTree() { Clear(root_); }
};