#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#define NUMBER_OF_ALPHABETS 91

using namespace std;

class TrieNode
{
public:
    bool isEndOfWord;
    int id;
    
    TrieNode *children[NUMBER_OF_ALPHABETS];
    ~TrieNode();

    TrieNode();
};

class Trie
{
public:
    TrieNode *root;
    Trie();
    ~Trie();

    // Inserts a word into the trie.
    void insert(string word, int id);

    // Returns if the word is in the trie.
    int search(string word);    

    bool isEmpty();

    // Returns if there is any word in the trie
    bool deleteWord(string word);

    // Returns true if node has no children
    bool isLeafNode(TrieNode *node);

    // 
    void prefixSearch(TrieNode *root, string prefix);
    void prefixSearchHelper(TrieNode *root, string prefix);
    
};

#endif