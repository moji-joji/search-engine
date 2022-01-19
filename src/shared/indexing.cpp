
#include <fstream>

#include <indexing.h>
#include <paths.h>

#include <csv.h>
#include <utils.h>
#include <stringutils.h>

using namespace std;

// lexicon is unique wordid for each word
void generateLexicon(const string &metadataFilename,
  HashMap<string, uint32_t> &lexiconMap,
  HashMap<string, char> &stopWords)
{

  cout << "Generating lexicon..." << endl;
  uint32_t wordId = 1;

  // read each file line by line
  // for each word in line
  //   if word is not in lexicon and is not a stopword
  //     add word to lexicon
  //   else
  //     increment the index of the word in the lexicon

  io::CSVReader<1, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(metadataFilename.c_str());


  in.read_header(io::ignore_extra_column, "filename");

  // open lexicon file 
  ofstream output;
  string lexiconFilename = INDEXING_DIR + "lexicon.csv";

  cout << "Writing to " << lexiconFilename << endl;

  output.open(lexiconFilename);
  if (!output.is_open())
  {
    cout << "ERROR: Output file cannot be opened" << endl;
    return;
  }

  int iterations = 0;

  // read each word from each file
  string filename;
  cout << "Reading metadata" << endl;
  while (in.read_row(filename))
  {
    if (iterations > 100000)
      break;
    iterations++;

    // main loop
    // open file for reading
    string inputFile = CLEANED_ARTICLES_DIR + filename;

    ifstream file;
    file.open(inputFile);

    if (!file.is_open())
    {
      cout << "ERROR: Input file cannot be opened" << endl;
      return;
    }

    string originalWord;
    string stemmedWord;

    // cout << "Filename: " << filename << endl;
    while (file >> originalWord)
    {
      // stem the word
      stemWord(originalWord, stemmedWord);

      // if word is not a common word and not already in map
      // put it in map
      if (!stopWords[stemmedWord])
        if (!lexiconMap[stemmedWord]) {
          output << "word,wordId" << endl;
          lexiconMap[stemmedWord] = wordId++;
          output << stemmedWord << "," << wordId << endl;


        }
    }

    file.close();
  }
  return;

  // iterate and save lexicon to csv file
   // output << "word,wordId" << endl;
   // for (auto &it : lexiconMap)
   // {
   //   // cout << it->first << ", " << it->second << endl;
   //   output << it.first << "," << it.second << "\n";
   // }

   // [fileId, frequency], wordId

   // wordId, [fileId, frequency]

  output.close();
}

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
stemming::english_stem<> stemmer;

void populateStopWords(const std::string &filename,
  HashMap<string, char> &stopWords)
{ // load stop words from file to map
  io::CSVReader<1> in(filename.c_str());
  in.read_header(io::ignore_extra_column, "words");

  string words;
  while (in.read_row(words))
  { // set non null value
    stopWords[words] = 'f';
  }
}

void populateMetadata(const string &in_filename, HashMap<uint32_t, ArticleMeta> &metadata)
{ // read csv of metadata 
  io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(in_filename.c_str());
  in.read_header(io::ignore_extra_column, "id", "title", "filename", "updated_at");

  uint32_t id;
  string title, filename, updated_at;
  while (in.read_row(id, title, filename, updated_at))
  { // load to memoru
    toISODate(updated_at);
    filename = toLower(filename);
    ArticleMeta article(id, title, filename, date_from_iso_string(updated_at));
    // metadata[id] = article;
    metadata.insert(id, article);
  }
}
