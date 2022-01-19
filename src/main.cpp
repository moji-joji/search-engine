#include <iostream>

#include <hashmap.h>
#include <csv.h>
#include <trie.h>
#include <utils.h>
#include <invertedindex.h>
#include <indexing.h>
#include <linkedlist.h>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cout << "Usage: [-c (Article Suggestion)] <word>" << endl;
    return 0;
  }

  string word;
  if (string(argv[1]) == "-c") {
    Trie *trie = new Trie();
    populateTrie(*trie);

    word = string(argv[2]);

    cout << "Suggestions for: " << endl;
    trie->prefixSearch(trie->root, word);
  }
  else {
    cout << "Loading lexicon..." << endl;
    HashMap<string, uint32_t> lexiconMap(LEXICON_SIZE);
    loadLexicon(lexiconMap);


    cout << "Loading metadata..." << endl;
    HashMap<uint32_t, ArticleMeta> metadata(METADATA_SIZE);
    loadMetadata(metadata);

    word = string(argv[1]);

    // Stores the wordIds of the words the user entered
    DoublyLinkedList<uint32_t> wordIds;

    // Stores the stemmed and lowered cased words
    DoublyLinkedList<string> words;

    getWordIdsFromQuery(word, wordIds, words, lexiconMap);

    fetchResults(words, wordIds, metadata);
  }
}
