#pragma once 

#include <iostream>
#include <codecvt>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <olestem/stemming/english_stem.h>
#include <paths.h>
#include <linkedlist.h>
#include <hashmap.h>
#include <set.h>
#include <trie.h>

#define LEXICON_SIZE 1300000
#define METADATA_SIZE 22000

#define SAMPLE_SIZE 100

using namespace std;
using namespace boost::gregorian;

// Article 
struct ArticleMeta {
  uint32_t id;
  string title;
  string filename;
  date updated_at;

  ArticleMeta() { }

  // constructor
  ArticleMeta(uint32_t id, string title, string filename, date updated_at) {
    this->id = id;
    this->title = title;
    this->filename = filename;
    this->updated_at = updated_at;
  };
};

// convert to date format
void toISODate(string &date);
// generate metadatqa
void populateMetadata(const string &filename, HashMap<uint32_t, ArticleMeta> &metadata);

// stemming of a word
void stemWord(const string &input, string &output);

// fill trie with data
void populateTrie(Trie &trie);

// load lexicon csv to hashmap
void loadLexicon(HashMap<string, uint32_t> &lexiconMap);

// load metadata csv to hashmap
void loadMetadata(HashMap<uint32_t, ArticleMeta> &metadata);

// file id of words 
void getWordIdsFromQuery(const string &query, DoublyLinkedList<uint32_t> &fileIds, DoublyLinkedList<string> &words, HashMap<string, uint32_t> &lexiconMap);

//get final resutls
void fetchResults(DoublyLinkedList<string> &words, DoublyLinkedList<uint32_t> &wordFileIds, HashMap<uint32_t, ArticleMeta> &metadata);

// check if query is supposed to feth title of any article
bool compareTitleWithQuery(const string &articleTitle, DoublyLinkedList<string> words, Set<string> *articleWordsSet, Set<string> *queryWordsSet, Set<string> *intersectionSet);

