#pragma once

#include <iostream>

// Change this to ../data/ when running from Makefile-tools in VSCode
#ifdef MAKEFILETOOLS_
const std::string DATA_DIR = "../data/";
#else
const std::string DATA_DIR = "./data/";
#endif

// paths for files defined
const std::string CLEANED_ARTICLES_DIR = DATA_DIR + "articles/";
const std::string RAW_ARTICLES_DIR = DATA_DIR + "articles-raw/";
const std::string INDEXING_DIR = DATA_DIR + "indexing/";
const std::string INVERTED_INDICES_DIR = DATA_DIR + "barrels/";

const std::string STOPWORDS_FILENAME = DATA_DIR + "stop_words.csv";
const std::string METADATA_FILENAME = DATA_DIR + "metadata.csv";
const std::string LEXICON_FILENAME = INDEXING_DIR + "lexicon.csv";
