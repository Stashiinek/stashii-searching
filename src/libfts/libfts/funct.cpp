#include "libfts/funct.hpp"

#include <picosha2.h>

namespace fts {

double summ(double a, double b) { return a + b; }

bool ifspace(char i) { return std::isspace(i) > 0; }
bool ifalpha(char i) { return std::isalpha(i) > 0; }

std::vector<std::string> splitString(const std::string str) {
  auto start = std::find_if(str.begin(), str.end(), ifalpha);
  auto end = start;
  std::vector<std::string> words;
  while (start != str.end()) {
    end = std::find_if(start, str.end(), ifspace);
    words.push_back(str.substr(start - str.begin(), end - start));
    start = std::find_if(end, str.end(), ifalpha);
  }
  return words;
}

std::string deletePunct(std::string &str) {
  std::string result = "";
  for (auto letter : str) {
    // std::cout << std::ispunct(letter) << "\n";
    if (std::ispunct(letter) == 0) {
      result += letter;
    }
  }
  // std::cout << result << "\n";
  return result;
}

std::string lowerLetters(std::string &str) {
  for (auto &letter : str) {
    letter = std::tolower(letter);
  }
  return str;
}

void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops) {
  for (auto &checkStop : stops) {
    for (auto &word : str) {
      if (word.compare(checkStop) == 0)
        word.erase();
    }
  }
}

std::string restring(std::string &str) {
  std::string unpunctString = deletePunct(str);
  unpunctString = lowerLetters(unpunctString);
  return unpunctString;
}

std::vector<fts::ngrams> parse(std::vector<std::string> &str, int &min_length,
                               int &max_length) {
  std::vector<fts::ngrams> result(str.size());
  int actual_max = max_length, actual_min = min_length;

  for (std::size_t i = 0; i < str.size(); i++) {
    fts::ngrams local_vector;
    local_vector.index = i;
    actual_max = std::min(static_cast<int>(str.at(i).size()), max_length);
    actual_min = std::min(static_cast<int>(str.at(i).size()), min_length);
    local_vector.document = str.at(i);

    for (int ng_len = actual_min; ng_len <= actual_max; ng_len++) {
      local_vector.peach.push_back(str.at(i).substr(0, ng_len));
    }
    if (!local_vector.peach.empty()) {
      result.at(i).peach = local_vector.peach;
      result.at(i).index = local_vector.index;
      result.at(i).document = local_vector.document;
    }
  }

  return result;
}

std::vector<ngrams> parsing(inData *inputData, std::vector<std::string> words) {
  fts::deleteStops(words, inputData->stop_words);
  std::vector<fts::ngrams> outputData;

  outputData =
      parse(words, inputData->min_ngram_length, inputData->max_ngram_length);
  std::cout << "\n";

  /*for (auto &i : outputData) {
    for (auto &k : i.peach) {
      if (!(k.empty()))
        std::cout << k << "  ";
    }
    if (!(i.peach.at(0).empty()))
      std::cout << i.index << "\n";
  } */

  return outputData;
}

void mainfunct(inData *inputData, std::vector<std::vector<std::string>> words){
  std::vector<std::vector<ngrams>> terms;
  for (auto be : words)
    terms.push_back(fts::parsing(inputData, be));

  std::vector<std::vector<std::pair<int, int>>> rev_entr;
  int ind, entr;
  for (int i = 0; i < words.size(); i++){
    std::vector<ngrams> wordTerms = parsing(inputData, words.at(i));
    std::vector<std::pair<int, int>> pairs = ind::entry_search(terms, wordTerms);
    for (auto be : pairs)
      rev_entr.at(i).push_back(be);
  }
}

namespace ind {

int meow_search(std::vector<std::vector<ngrams>> &terms, std::vector<std::string> &meow_ng){
  int meow_result = 0;
  for ()

  return meow_result;
}
std::vector<std::pair<int, int>> entry_search(std::vector<std::vector<ngrams>> &terms, std::vector<ngrams> &check){
  std::vector<std::pair<int, int>> result;
  for (auto be : check){
    int meow_ret = meow_search(terms, be.peach);
  }

  return result;
}

void IndexBuilder::add_document(int document_id, inData *inputData) {
  std::vector<std::string> splitText = splitString(inputData->text.at(document_id));
  std::vector<ngrams> terms = parsing(inputData, splitText);
  //std::vector<int> ntry =

  index.docs.insert(std::make_pair(document_id, inputData->text.at(document_id)));

  // any STL sequantial container (vector, list, dequeue...)

  // std::map<std::size_t, std::string> docs;
  // std::multimap<std::string, entry_data> entires;
}

void TextUndexWriter::write(std::string path, int index) {}
} // namespace ind
} // namespace fts
