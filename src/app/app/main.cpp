#include "libfts/funct.hpp"

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <nlohmann/json.hpp>

#include <iostream>

using json = nlohmann::json;

int main() {
  std::string path = std::filesystem::current_path();
  path = path.substr(0, path.size() - 16);
  path = path + "/src/libfts/libfts/file.json";   //хвала аллаху не надо пихать теперь это файл к исполняемому после удаления пресета

  std::ifstream filedata;
  CLI::App app{"App description"};
  filedata.open(path);
  json data = json::parse(filedata);

  fts::inData inputData;
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();

  fts::ind::IndexBuilder snacks;    //в этот момент я не знала как назвать экземпляр класса и ела чипсеки
  snacks.set_config(inputData);

  fts::clearNum();
  std::string document_data = "hello this is a test";
  std::size_t doc_id = 4;
  snacks.add_document(doc_id, document_data);

  document_data = "what the hell";
  doc_id = 666;
  snacks.add_document(doc_id, document_data);

  document_data = "hey! real miau!";
  doc_id = 31;
  snacks.add_document(doc_id, document_data);
  fts::ind::Index &testIndex = snacks.retIndex();

  fts::ind::TextIndexWriter cringe;
  cringe.write(testIndex);


  std::string query;
  std::cout << "Введите запрос: ";
  getline(std::cin, query);
  std::cout << "\n";

  fts::srch::TextIndexAccessor trying_find;

  trying_find.search(query, inputData);

  return 0;
}
