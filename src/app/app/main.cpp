#include "libfts/funct.hpp"

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <nlohmann/json.hpp>

#include <iostream>

using json = nlohmann::json;

int main(int argc, char **argv) {
  std::ifstream filedata;
  CLI::App app{"App description"};
  filedata.open("file.json");
  json data = json::parse(filedata);

  fts::inData inputData;
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();

  std::string document_data = "hello this is a test";
  std::size_t doc_id = 4;
  std::vector<std::string> text = fts::splitString(document_data);

  for (auto &be : text) {
    be = fts::restring(be);
  }

  fts::ind::IndexBuilder snacks;    //в этот момент я не знала как назвать экземпляр класса и ела чипсеки
  snacks.set_config(inputData);
  snacks.add_document(doc_id, document_data);
  fts::ind::Index &testIndex = snacks.retIndex();

  fts::ind::TextIndexWriter cringe;
 
  cringe.write(testIndex);


  std::string query = "hello";
  fts::srch::TextIndexAccessor trying_find;
  //trying_find.search(query, inputData);

  std::string namefile = "4";
  namefile = fts::srch::doc_reader(namefile);
  //TextIndexAccessor::search(std::string &doc, inData &config);

  return 0;
}
