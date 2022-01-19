#pragma once 

#include <iostream>

#include <utils.h>

using namespace std;

// lexicon of word with id
void generateLexicon(const string &filename, HashMap<string, uint32_t> &lexiconMap, HashMap<string, char> &stopWords);

// stop words mapped 
void populateStopWords(const string &filename, HashMap<string, char> &stopWords);
