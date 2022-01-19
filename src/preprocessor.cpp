#include <iostream>
#include <utils.h>
#include <indexing.h>
#include <invertedindex.h>
#include <paths.h>
#include <csv.h>

// lexicon loaded from csv
void loadLexicon(const string &filename, HashMap<string, uint32_t> &lexiconMap) {
  io::CSVReader<2, io::trim_chars<' '>, io::double_quote_escape<',', '\"'> > in(filename);
  in.read_header(io::ignore_extra_column, "word", "wordId");

  string word;
  uint32_t wordId;
  // iterate each tuple
  while (in.read_row(word, wordId)) {
    lexiconMap[word] = wordId;
  }
}

// test main
int main() {
  cout << "Hashmap-uh!" << endl;

  // Loading the stopwords
  HashMap<string, char> stopWords;
  populateStopWords(STOPWORDS_FILENAME, stopWords);

  cout << "Sizeof Stopwords " << stopWords.size() << endl;

  // Loading the metadata
  HashMap<uint32_t, ArticleMeta> metadata;
  populateMetadata(METADATA_FILENAME, metadata);

  cout << "Sizeof metadata " << metadata.size() << endl;

  // Loading the lexicon
  HashMap<string, uint32_t> lexiconMap;
  // generateLexicon(METADATA_FILENAME, lexiconMap, stopWords);
  loadLexicon(INDEXING_DIR + "lexicon.csv", lexiconMap);

  InvertedIndex invertedIndex;
  cout << "populating inverted index" << endl;
  populateInvertedIndex(invertedIndex, lexiconMap, metadata);
  for (auto it : invertedIndex.index) {
    if (it.first == 0) {
      cout << it.first << ": ";
      for (auto it2 : it.second.files) {
        cout << it2.first << ": " << it2.second.frequency << " ";
      }
      cout << endl;
    }
  }
  // invertedIndex.print();
  cout << "Writing to the file" << endl;
  invertedIndex.writeToFile(INDEXING_DIR + "inverted-index-remake-complete-pakka-wala(2).csv");

  return 0;
}
