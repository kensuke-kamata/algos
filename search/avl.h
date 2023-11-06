#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "search.h"

namespace avl {
template <typename T>
class tree {
 private:
  struct node {
    T value{};
    std::unique_ptr<node>  left = nullptr;
    std::unique_ptr<node> right = nullptr;
    int height = 0;

    explicit node(T value) : value(value) {}
  };

  std::unique_ptr<node> root = nullptr;
  size_t size = 0;

  int height(const node *node) const {
    return node ? node->height : -1;
  }

  int difference(const node *node) const {
    return height(node->left.get()) - height(node->right.get());
  }

  void reheight(node *node) const {
    node->height = std::max(height(node->left.get()), height(node->right.get())) + 1;
  }

  const T &min(const node *current) const {
    if (!current) {
      throw std::runtime_error("min: tree is empty");
    }
    return  current->left ? min(current->left.get()) : current->value;
  }

  const T &max(const node *current) const {
    if (!current) {
      throw std::runtime_error("max: tree is empty");
    }
    return  current->right ? max(current->right.get()) : current->value;
  }

  std::unique_ptr<node> rrotate(std::unique_ptr<node> node) {
    auto root   = std::move(node->left);
    node->left  = std::move(root->right);
    root->right = std::move(node);

    reheight(root->right.get());
    reheight(root.get());
    return root;
  }

  std::unique_ptr<node> lrotate(std::unique_ptr<node> node) {
    auto root   = std::move(node->right);
    node->right = std::move(root->left);
    root->left  = std::move(node);

    reheight(root->left.get());
    reheight(root.get());
    return root;
  }

  std::unique_ptr<node> balance(std::unique_ptr<node> node) {
    int balance = difference(node.get());

    if (balance > 1) {                         // left skewed
      if (difference(node->left.get()) < 0) {  // left-right skewed
        node->left = lrotate(std::move(node->left));
      }
      return rrotate(std::move(node));
    }
    if (balance < -1) {                        // right skewed
      if (difference(node->right.get()) > 0) { // right-left skewed
        node->right = rrotate(std::move(node->right));
      }
      return lrotate(std::move(node));
    }

    reheight(node.get());
    return node;
  }

  std::unique_ptr<node> insert(std::unique_ptr<node> parent, const T &value) {
    if (!parent) {
      return std::make_unique<node>(value);
    }

    if (value <= parent->value) {
      parent->left  = insert(std::move(parent->left), value);
    } else {
      parent->right = insert(std::move(parent->right), value);
    }

    return balance(std::move(parent));
  }

  std::unique_ptr<node> remove(std::unique_ptr<node> current, const T &value) {
    if (!current) {
      return nullptr;
    }

    if (value < current->value) {
      current->left  = remove(std::move(current->left), value);
      return balance(std::move(current));
    }
    if (value > current->value) {
      current->right = remove(std::move(current->right), value);
      return balance(std::move(current));
    }

    if (!current->left) {
      return std::move(current->right);
    }
    if (!current->right) {
      return std::move(current->left);
    }
    // Find the smallest value in the right subtree
    auto rmin = min(current->right.get());
    current->value = rmin;
    current->right = remove(std::move(current->right), rmin);
    return balance(std::move(current));
  }

  void inorder(const node *node, std::vector<T> &result) const {
    if (!node) {
      return;
    }
    inorder(node->left.get(), result);
    result.push_back(node->value);
    inorder(node->right.get(), result);
  }

 public:
  tree() {}

  int height() const {
    if (!root) {
      return -1;
    }
    return root->height;
  }

  size_t length() const {
    return size;
  }

  void insert(const T &value) {
    root = insert(std::move(root), value);
    size++;
  }

  void remove(const T &value) {
    auto res = remove(std::move(root), value);
    if (res) {
      root = std::move(res);
      size--;
    }
  }

  std::vector<T> inorder() const {
    std::vector<T> result;
    result.reserve(size);
    inorder(root.get(), result);
    return result;
  }

  bool contains(const T &value) const {
    auto iter = root.get();
    while (iter) {
      if (value == iter->value) { return true; }
      if (value <= iter->value) {
        iter = iter->left.get();
      } else {
        iter = iter->right.get();
      }
    }
    return false;
  }

  void clear() {
    root.reset();
  }
};
}  // namespace avl
