#include <libfts/funct.hpp>

#include <picosha2.h>

namespace fts{
  std::string find_path(){
    std::string path = std::filesystem::current_path();
    path = path.substr(0, path.size() - 16);
    return path;
  }

  void clearNum(std::string &path){
  std::string path1 = path + "/index/doc_count.txt";

  std::ofstream file1;

  file1.open(path1);
  file1 << 0;
  file1.close();
}

void numberOfDocs(std::size_t num, std::string &path){
  std::string path1 = path + "/index/doc_count.txt";
  std::ofstream file1;

  file1.open(path1);
  file1 << num;
  file1.close();
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
  std::string orig_text = text;
  text = restring(text);
  std::vector<std::string> splitText = splitString(text);
  std::vector<ngrams> terms = parsing(config, splitText, document_id);

  index.docs.insert(std::make_pair(document_id, orig_text));
  for (std::size_t i = 0; i < terms.size(); i++){
    for (auto be : terms.at(i).peach){
      this->add_term(document_id, i, be);
    }
  }
}

Index& IndexBuilder::retIndex(){
  return index;
}

void TextIndexWriter::write(Index &miau, std::string &path) {
  std::ofstream file;
  std::string fpath;

  std::string doc_path = path + "/index/docs/";
  std::string entry_path = path + "/index/entries/";

  std::filesystem::create_directories(doc_path);
  std::filesystem::create_directories(entry_path);

  fpath = doc_path + "/index/doc_count.txt";
  file.open(fpath);
  file << miau.docs.size();    //сохраняем количество документов
  file.close();

  size_t filenum = 0;
  for (auto &be : miau.docs){
    fpath = doc_path + "/" + std::to_string(be.first) + ".txt";
    file.open(fpath);

    file << be.second;
    file.close();
    filenum++;
  }

  numberOfDocs(filenum, path);

  for (auto &be: miau.rev_docs){
    fpath = entry_path + "/" + be.first + ".txt";
    file.open(fpath);
    file << be.second.term << " " << be.second.term_docs.size();

    for (auto &write_terms: be.second.term_docs){
      file << " " << write_terms.doc_id << " " << write_terms.pos.size();
      for (auto &write_pos: write_terms.pos){
        file << " " << write_pos;
      }
    }
    file.close();
  }
}
} // namespace ind
}