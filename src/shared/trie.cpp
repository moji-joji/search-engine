#include <trie.h>
#include <utils.h>

#include <iostream>
#include <string>

using namespace std;

// node class
TrieNode::TrieNode()
{
    isEndOfWord = false;

    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        children[i] = NULL;
    }
}

// destructor
TrieNode::~TrieNode()
{
    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        if (children[i] != NULL)
        {
            delete children[i];
        }
    }
}
// constructor
Trie::Trie() { root = new TrieNode(); }

// destructor
Trie::~Trie() { delete root; }

bool Trie::isEmpty()
{
    return root == NULL;
}

void Trie::insert(string word, int id)
{
    // start from root
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        // calculating ascii index
        int index = word[i] - ' ';
        if (curr->children[index] == NULL)
        {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
    curr->id = id;
}

int Trie::search(string word)
{
    // start from root
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        // calculating index
        int index = word[i] - ' ';
        if (curr->children[index] == NULL)
        {
            // if word alphabet not found return 1
            return -1;
        }
        // go deeper
        curr = curr->children[index];
    }
    // if it is an acutal word, return the title id we stored
    if (curr->isEndOfWord)
        return curr->id;
    else
        return -1;
}

bool Trie::deleteWord(string word)
{
    // traverse
    TrieNode *currNode = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        int index = word[i] - ' ';
        if (currNode->children[index] != NULL)
        {
            currNode = currNode->children[index];
        }
        else
        {
            return false;
        }
    }
    // just set flag to false
    currNode->isEndOfWord = false;
    return true;
}

bool Trie::isLeafNode(TrieNode *node)
{
    // check if it has atleast one leaf node
    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        if (node->children[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

void Trie::prefixSearchHelper(TrieNode *root, string prefix)
{
    if (root->isEndOfWord)
    {
        // print if the root was end of word
        cout << prefix << endl;
    }

    // base case
    if (isLeafNode(root))
        return;

    for (int i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        // call recursicely for child i and append next alphabet of child.
        if (root->children[i])
        {
            prefixSearchHelper(root->children[i], prefix + (char)(i + ' '));
        }
    }
}

// get all prefix matching strings
void Trie::prefixSearch(TrieNode *root, const string prefix)
{
    {
        TrieNode *currentNode = root;

        // traverse depth first
        for (u_int32_t i = 0; i < prefix.length(); i++)
        {
            int index = prefix[i] - ' ';

            // if not child, retunr
            if (!currentNode->children[index])
                return;

            currentNode = currentNode->children[index];
        }
        // if a word is found, print
        if (currentNode->isEndOfWord && isLeafNode(currentNode))
        {
            cout << prefix << endl;
            return;
        }
        else if (!isLeafNode(currentNode))
        {
            // current node is made root.
            prefixSearchHelper(currentNode, prefix);
            return;
        }
    }
}