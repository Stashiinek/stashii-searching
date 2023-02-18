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

std::vector<fts::ngrams> parse(std::vector<std::string> &str, std::size_t &docId, int &min_length,
                               int &max_length) {
  std::vector<fts::ngrams> result(str.size());
  int actual_max = max_length, actual_min = min_length;

  for (std::size_t i = 0; i < str.size(); i++) {
    fts::ngrams local_vector;
    local_vector.index = docId;
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

std::vector<ngrams> parsing(inData &inputData, std::vector<std::string> words, std::size_t &ids) {
  fts::deleteStops(words, inputData.stop_words);
  std::vector<fts::ngrams> outputData;

  outputData =
      parse(words, ids, inputData.min_ngram_length, inputData.max_ngram_length);
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

namespace ind {

/*std::vector<entry_pair> entry_search(std::vector<std::vector<ngrams>> &terms, std::vector<ngrams> &check){
  std::vector<entry_pair> result;
  entry_pair meow_pair;
  for (auto be : check){
    for (int i = 0; i < terms.size(); i++){
      int meow_res = meow_search(terms.at(i), be.peach);
      if (meow_res < 0){
        meow_pair.doc_id = i;
        meow_pair.countOfEntries = meow_res;
      }
    }
  }

  return result;
} */

/*Index index;
  inData config;
  void find_entry();
*/

void IndexBuilder::set_config(inData &inputData){
  config = inputData;
}

void IndexBuilder::findTerm(std::string &term){

}

void IndexBuilder::add_term(std::size_t doc_id, std::size_t pos, std::string &term){

  // std::unordered_map<std::string, entry_data> rev_docs;

  std::vector<unsigned char> hash(picosha2::k_digest_size);
  picosha2::hash256(term.begin(), term.end(), hash.begin(), hash.end());   //спросить у паши как брать первые три байта хэша
  std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
  auto find_hex = index.rev_docs.find(hex_str);

  if (find_hex == index.rev_docs.end()){
    term_data meow_pos_entries;
    meow_pos_entries.doc_id = doc_id;
    meow_pos_entries.pos.push_back(pos);

    entry_data meow_entries;
    meow_entries.term = term;
    meow_entries.term_docs.push_back(meow_pos_entries);

    index.rev_docs.insert(std::make_pair(hex_str, meow_entries)); //добавить новый экземпляр в мапу
  }
  else {
    //ковыряемся в уже существующих полях
    //евгений сергеевич эти комментарии только для меня честно не смотрите на их наличие
    term_data meow_pos_entries;
    meow_pos_entries.doc_id = doc_id;
    meow_pos_entries.pos.push_back(pos);

    find_hex->second.term_docs.push_back(meow_pos_entries);
  }
}

void IndexBuilder::add_document(std::size_t document_id, std::string &text) {
  std::vector<std::string> splitText = splitString(text);
  std::vector<ngrams> terms = parsing(config, splitText, document_id);

  index.docs.insert(std::make_pair(document_id, text));
  for (std::size_t i = 0; i < terms.size(); i++){
    for (auto be : terms.at(i).peach){
      add_term(document_id, i, be);
    }
  }
}

void TextUndexWriter::write(std::string path, int index) {}
} // namespace ind
} // namespace fts
