#pragma once


#include <iostream>
#include "LinkedList.h"

template <typename T, typename K>
class AVLTree {
public:
  struct TreeNode;

  AVLTree() {
    root = nullptr;
  }

  TreeNode *search(T word) {

    TreeNode *p = root;
    while (p != nullptr) {
      if (word == p->word) {
        return p;
      }
      else if (word < p->word) {
        p = p->left;
      }
      else {
        p = p->right;
      }
    }
    return nullptr;
  }

  void insert(T word, K meaning) {
    root = insert(word, meaning, root);
  }

  void remove(T x) {
    root = remove(x, root);
  }

  void print() {
    InOrder(root);
    std::cout << std::endl;
  }

  ~AVLTree() {
    makeEmpty(root);
  }

  struct TreeNode {
    T word;
    LinkedList<K> meaning;

    TreeNode *left;
    TreeNode *right;
    int height;
  };

private:
  TreeNode *root;

  void makeEmpty(TreeNode *t) {
    if (t == nullptr)
      return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  TreeNode *insert(T word, K meaning, TreeNode *t) {
    if (t == nullptr) {
      t = new TreeNode;

      t->word = word;
      t->meaning.Insert(meaning);

      t->height = 0;
      t->left = t->right = nullptr;
    }
    else if (word < t->word) {
      t->left = insert(word, meaning, t->left);
      if (height(t->left) - height(t->right) == 2) {
        if (word < t->left->word)
          t = singleRightRotate(t);
        else
          t = doubleRightRotate(t);
      }
    }
    else if (word > t->word) {
      t->right = insert(word, meaning, t->right);
      if (height(t->right) - height(t->left) == 2) {
        if (word >= t->right->word)
          t = singleLeftRotate(t);
        else
          t = doubleLeftRotate(t);
      }
    }
    else if (word == t->word) {
      t->meaning.Insert(meaning);
    }

    t->height = std::max(height(t->left), height(t->right)) + 1;
    return t;
  }

  TreeNode *singleRightRotate(TreeNode *&t) {
    TreeNode *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(u->left), t->height) + 1;
    return u;
  }

  TreeNode *singleLeftRotate(TreeNode *&t) {
    TreeNode *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(t->right), t->height) + 1;
    return u;
  }

  TreeNode *doubleLeftRotate(TreeNode *&t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
  }

  TreeNode *doubleRightRotate(TreeNode *&t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
  }

  TreeNode *findMin(TreeNode *t)
  {
    if (t == nullptr)
      return nullptr;
    else if (t->left == nullptr)
      return t;
    else
      return findMin(t->left);
  }

  TreeNode *findMax(TreeNode *t) {
    if (t == nullptr)
      return nullptr;
    else if (t->right == nullptr)
      return t;
    else
      return findMax(t->right);
  }

  TreeNode *remove(int x, TreeNode *t) {
    TreeNode *temp;

    // Element not found
    if (t == nullptr)
      return nullptr;

    // Searching for element
    else if (x < t->word)
      t->left = remove(x, t->left);
    else if (x > t->word)
      t->right = remove(x, t->right);

    // Element found
    // With 2 children
    else if (t->left && t->right) {
      temp = findMin(t->right);
      t->word = temp->word;
      t->right = remove(t->word, t->right);
    }
    // With one or zero child
    else {
      temp = t;
      if (t->left == nullptr)
        t = t->right;
      else if (t->right == nullptr)
        t = t->left;
      delete temp;
    }
    if (t == nullptr)
      return t;

    t->height = std::max(height(t->left), height(t->right)) + 1;

    // If node is unbalanced
    // If left node is deleted, right case
    if (height(t->left) - height(t->right) == 2) {
      // right right case
      if (height(t->left->left) - height(t->left->right) == 1)
        return singleLeftRotate(t);
      // right left case
      else
        return doubleLeftRotate(t);
    }
    // If right node is deleted, left case
    else if (height(t->right) - height(t->left) == 2) {
      // left left case
      if (height(t->right->right) - height(t->right->left) == 1)
        return singleRightRotate(t);
      // left right case
      else
        return doubleRightRotate(t);
    }
    return t;
  }

  int height(TreeNode *t) {
    return (t == nullptr ? -1 : t->height);
  }

  int getBalance(TreeNode *t) {
    if (t == nullptr)
      return 0;
    else
      return height(t->left) - height(t->right);
  }

  void InOrder(TreeNode *t) {
    if (t == nullptr)
      return;
    InOrder(t->left);
    std::cout << t->word << " ";
    InOrder(t->right);
  }

};
