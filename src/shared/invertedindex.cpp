
#include <invertedindex.h>

// add word to word map hashmap
void InvertedIndex::addWord(const uint32_t wordId, uint32_t fileId, size_t position)
{
  // if (index.find(word) == index.end()) {
  //   // No such word in the index
  //   FilesMap wordMap;
  //   index[word] = wordMap;
  // }
  // Word exists in the index
  FilesMap &wordMap = index[wordId];
  if (wordMap.files.find(fileId) == wordMap.files.end())
  {
    // No such file in the word map
    // FilesMap::WordDetail fileMap;
    // fileMap.frequency = 1;
    // fileMap.positions.push_back(position);
    wordMap.files[fileId].frequency = 1;
    wordMap.files[fileId].positions.push_back(position);
  }
  else
  {
    // File exists in the word map
    // increment frequency, add new position
    FilesMap::WordDetail &fileMap = wordMap.files[fileId];
    fileMap.frequency++;
    fileMap.positions.push_back(position);
  }
}

// get the struct back for the corresponding word
InvertedIndex::FilesMap &InvertedIndex::searchWord(const uint32_t wordId)
{
  return index[wordId];
}

// remove word from index
void InvertedIndex::deleteWord(const uint32_t wordId)
{
  index.erase(wordId);
}

// print all details of index
void InvertedIndex::print()
{
  for (auto it = index.begin(); it != index.end(); ++it)
  {
    cout << it->first << ": ";
    for (auto it2 = it->second.files.begin(); it2 != it->second.files.end(); ++it2)
    {
      cout << it2->first << ": " << it2->second.frequency << " ";
    }
    cout << endl;
  }
}

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, uint32_t> &lexicon, HashMap<uint32_t, ArticleMeta> &metadata)
{
  size_t filesread = 0;
  for (auto it : metadata)
  {
    // iterate through meta data
    uint32_t fileId = it.first;
    ArticleMeta &article = it.second;
    ifstream file(CLEANED_ARTICLES_DIR + article.filename);
    string line;

    // stemming is done to make sure same suffix words mapped
    char *segment;
    string originalWord;
    string stemmedWord;
    size_t position = 0;

    // iterate through words in the article
    while (getline(file, line))
    {
      position = 0;
      for (segment = strtok((char *) line.c_str(), " "); segment != NULL; segment = strtok(NULL, " "))
      {
        originalWord = string(segment);
        stemWord(originalWord, stemmedWord);

        if (lexicon.find(stemmedWord) == lexicon.end())
        {
          // Word not found in the lexicon
          continue;
        }

        // get the word id from lexicon and add to file
        uint32_t wordId = lexicon[stemmedWord];
        invertedIndex.addWord(wordId, fileId, position);
        ++position;
      }

      // cout << "Processed " << article.filename << endl;
    }
    // if (++filesread == 100000)
    //   break;
  }
}

void InvertedIndex::writeToFile(const string &filename)
{
  // make csv file
  ofstream file(filename);
  file << "wordId"
    << ","
    << "fileId"
    << ","
    << "frequency"
    << ","
    << "positions" << endl;
  string wordId, fileId, frequency, positions;
  positions.reserve(256);

  // iterate over all indexes
  for (auto &it0 : index)
  {
    for (auto &it1 : it0.second.files)
      // for each file
    {
      // wordId = to_string( it0.first;
      // fileId = it1.first;
      // frequency = it1.second.frequency;

      // convert data to strings
      wordId = to_string(it0.first);
      fileId = it1.first;
      frequency = to_string(it1.second.frequency);

      positions = "\"";
      // iterate over positions
      // append to strinf
      for (auto &it2 : it1.second.positions)
      {
        positions += to_string(it2) + ",";
      }
      positions += "\"";
      // write to file
      file << wordId << "," << fileId << "," << frequency << "," << positions << endl;
      // cout << it0.first << ": file: " << it1.first << " frequency: " << it1.second.frequency << " positions:[";
      // for (auto &it2 : it1.second.positions) {
      //   cout << it2 << ",";
      // }
      // cout << "]" << endl;
    }
  }
  file.close();
}
