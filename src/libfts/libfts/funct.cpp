#include <libfts/funct.hpp>

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
      local_vector.peach.push_back(str.at(i).substr(0, ng_len)); //почему то не работает
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

  return outputData;
}

namespace ind {

void IndexBuilder::set_config(inData &inputData){
  config = inputData;
}

void IndexBuilder::add_term(std::size_t doc_id, std::size_t pos, std::string &term){
  std::vector<unsigned char> hash(picosha2::k_digest_size);
  picosha2::hash256(term.begin(), term.end(), hash.begin(), hash.end());
  std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.begin()+6);
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
    //а то я забуду какую фигню я тут написала :'(

    auto founded_term =
      std::find_if(find_hex->second.term_docs.begin(), find_hex->second.term_docs.end(),
                   [doc_id](term_data &data) { return data.doc_id == doc_id; });

    if (founded_term == find_hex->second.term_docs.end()){
      term_data meow_pos_entries;
      meow_pos_entries.doc_id = doc_id;
      meow_pos_entries.pos.push_back(pos);

      find_hex->second.term_docs.push_back(meow_pos_entries);
    }
    else {
      if (std::find(founded_term->pos.begin(), founded_term->pos.end(),
          pos) == founded_term->pos.end())
        founded_term->pos.push_back(pos);
    }
  }
}

void IndexBuilder::add_document(std::size_t document_id, std::string &text) {
  std::vector<std::string> splitText = splitString(text);
  std::vector<ngrams> terms = parsing(config, splitText, document_id);

  index.docs.insert(std::make_pair(document_id, text));
  for (std::size_t i = 0; i < terms.size(); i++){
    for (auto be : terms.at(i).peach){
      this->add_term(document_id, i, be);
    }
  }
}

Index& IndexBuilder::retIndex(){
  return index;
}

void TextIndexWriter::write(Index &miau) {
  std::ofstream file;
  std::string fpath;

  int magic_num = 16; //нужно чтобы норм путь был
  std::string path = std::filesystem::current_path();
  path = path.substr(0, path.size() - magic_num);

  std::string doc_path = path + "/index/docs/";
  std::string entry_path = path + "/index/entries/";

  std::filesystem::create_directories(doc_path);
  std::filesystem::create_directories(entry_path);

  for (auto &be : miau.docs){
    fpath = doc_path + "/" + std::to_string(be.first) + ".txt";
    file.open(fpath);

    file << be.second;
    file.close();
  }

  for (auto &be: miau.rev_docs){
    fpath = entry_path + "/" + be.first + ".txt";
    file.open(fpath);
    file << be.second.term << " " << be.second.term_docs.size() << " ";

    for (auto &write_terms: be.second.term_docs){
      file << write_terms.doc_id << " " << write_terms.pos.size() << " ";
      for (auto &write_pos: write_terms.pos){
        file << write_pos << " ";
      }
    }
    file.close();
  }
}
} // namespace ind
} // namespace fts
