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
  //app.add_option("--parse", text);
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();
  //CLI11_PARSE(app, argc, argv);

  std::string document_data = "hello this is a test";
  std::size_t doc_id = 4;
  std::vector<std::string> text = fts::splitString(document_data);

  for (auto &be : text) {
    be = fts::restring(be);
    // std::cout << be << " ";
  }

  fts::ind::IndexBuilder snacks;    //в этот момент я не знала как назвать экземпляр класса и ела чипсеки
  snacks.set_config(inputData);
  snacks.add_document(doc_id, document_data);
  fts::ind::Index &testIndex = snacks.retIndex();

  fts::ind::TextIndexWriter cringe;
 
  cringe.write(testIndex);  //пофиксить запись обратного индекса в Index

  return 0;
}
