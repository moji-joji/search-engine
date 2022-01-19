#pragma once 

#include <iostream>
#include <list>

#include <utils.h>
#include <DoublyLinkedList.h>

using namespace std;

// inverted index loaded for searching 
class InvertedIndex {
public:
  struct FilesMap;
  //  word id at what position added to file
  void addWord(const uint32_t wordId, uint32_t fileId, size_t position);

  // get frequency position of a word
  FilesMap &searchWord(const uint32_t wordId);

  // delete entry
  void deleteWord(const uint32_t wordId);

  // print the indexP
  void print();

  void writeToFile(const string &filename);

public:
  struct FilesMap {
    struct WordDetail {
      size_t frequency = 0;
      DoublyLinkedList<size_t> positions;
    };
    // fileId, WordDetail
    HashMap<uint32_t, WordDetail> files;
  };

  // TODO: Move this down
  HashMap<uint32_t, FilesMap> index;
private:
  // wordId, FilesMap
};

void populateInvertedIndex(InvertedIndex &invertedIndex, HashMap<string, uint32_t> &lexicon, HashMap<uint32_t, ArticleMeta> &metadata);
