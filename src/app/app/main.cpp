#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "libfts/funct.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <map>

using namespace fts;
using json = nlohmann::json;

int main(int argc, char **argv) {
  std::ifstream filedata;
  CLI::App app{"App description"};
  filedata.open("file.json");
  json data = json::parse(filedata);

  fts::input inputData;
  app.add_option("--parse", inputData.text, "");
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();
  CLI11_PARSE(app, argc, argv);

  for (auto &be : inputData.text) {
    be = parse(be, inputData.min_ngram_length, inputData.max_ngram_length);
    // std::cout << be << " ";
  }
  std::cout << inputData.min_ngram_length << "   " << inputData.max_ngram_length
            << "\n";

  deleteStops(inputData.text, inputData.stop_words);

  for (auto &word : inputData.text) {
    std::cout << word << "  ";
  }
  std::cout << "\n";

  return 0;
}
