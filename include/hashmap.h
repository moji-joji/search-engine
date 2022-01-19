#pragma once

#include <iostream>
#include <functional>

// Node class of template type hashmap
template <typename K, typename V>
class Node {
public:
  K key;
  V value;
  // Bucket stores data
  Node<K, V> *nextBucketNode;
  Node<K, V> *nextOverallNode;
  Node(K _key, V _value) {
    key = _key;
    value = _value;
    nextBucketNode = NULL;
    nextOverallNode = NULL;
  }
};

template <typename K, typename V>
class Bucket {
public:
// head tail of single bin
  Node<K, V> *head;
  Node<K, V> *tail;

  // constructor and destructor
  Bucket() {
    head = NULL;
    tail = NULL;
  }

  ~Bucket() {
    Node<K, V> *curr = head;
    while (curr != NULL) {
      Node<K, V> *next = curr->nextBucketNode;
      delete curr;
      curr = next;
    }
  }
};


template <typename K, typename V>
class HashMap {
public:
  Bucket<K, V> *buckets;
  int numBuckets;
  Node<K, V> **nodes;
  int numNodes;
  std::hash<K> hashFunc;
  std::function<bool(Node<K, V>, Node<K, V>)> cmpFunc;

// dynamically allocate array according to need
  HashMap(int _size = 100) {
    buckets = new Bucket<K, V>[_size];
    numBuckets = _size;
    nodes = new Node<K, V>*[numBuckets];
    numNodes = 0;
// comparison function on which basis to sort
    cmpFunc = [](Node<K, V> a, Node<K, V> b) {
      return a.key < b.key;
    };
  }
// constrictor to initializr
  HashMap(int _size, std::function<bool(Node<K, V>, Node<K, V>)> cmpFunc) {
    buckets = new Bucket<K, V>[_size];
    numBuckets = _size;
    nodes = new Node<K, V>*[numBuckets];
    numNodes = 0;

    this->cmpFunc = cmpFunc;
  }

  ~HashMap() {
    delete[] buckets;
    delete[] nodes;
  }

  // module of the bytes of the key
  int hash(K key) {
    return hashFunc(key) % numBuckets;
  }

  // delete a key value pair
  void remove(K key) {
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    Node<K, V> *prev = nullptr;

    while (curr != NULL) {
      if (curr->key == key) {
        if (prev != nullptr) {
          prev->nextBucketNode = curr->nextBucketNode;
        }
        delete curr;
        break;
      }
      prev = curr;
      curr = curr->nextBucketNode;
    }
  }

  // hash the key and store value
  void insert(K key, V value) {
    int bucketIndex = hash(key);

    Node<K, V> *newNode = new Node<K, V>(key, value);
    if (buckets[bucketIndex].head == NULL) {
      // if no collission
      buckets[bucketIndex].head = newNode;
      buckets[bucketIndex].tail = newNode;
    }
    else {
      // if collission, insert by chaining
      buckets[bucketIndex].tail->nextBucketNode = newNode;
      buckets[bucketIndex].tail = newNode;
    }

    nodes[numNodes] = newNode;
    numNodes++;
  }

  bool find(K key) {
    // hash key, find if the value if it exists or chained etc
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      curr = curr->nextBucketNode;
    }
    return false;
  }

  V &get(K key) {
    // hash key, return value if the value if it exists or chained etc
    
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      curr = curr->nextBucketNode;
    }
  }

  V &operator[](K key) {
    return get(key);
  }

  // sort nodes for traversal
  void sortNodes() {
    for (int i = 0; i < numNodes; i++) {
      for (int j = i + 1; j < numNodes; j++) {
        if (cmpFunc(nodes[i]->key, nodes[j]->key)) {
          Node<K, V> *temp = nodes[i];
          nodes[i] = nodes[j];
          nodes[j] = temp;
        }
      }
    }
  }

  // print nodes
  void traverseKeyValuePairs() {
    for (int i = 0; i < numNodes; i++) {
      std::cout << nodes[i]->key << " " << nodes[i]->value << std::endl;
    }
  }

  // get start for iterations
  Node<K, V> **getHead() {
    return nodes;
  }
};
