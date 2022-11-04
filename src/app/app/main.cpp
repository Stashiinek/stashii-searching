#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "libfts/funct.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <map>

using json = nlohmann::json;

int main(int argc, char **argv) {
  std::ifstream filedata;
  CLI::App app{"App description"};
  filedata.open("file.json");
  json data = json::parse(filedata);

  fts::input inputData;
  app.add_option("--parse", inputData.text);
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();
  CLI11_PARSE(app, argc, argv);

  for (auto &be : inputData.text) {
    be = fts::restring(be);
    // std::cout << be << " ";
  }
  std::cout << inputData.min_ngram_length << "   " << inputData.max_ngram_length
            << "\n";

  fts::deleteStops(inputData.text, inputData.stop_words);
  std::vector<fts::ngrams> outputData;
  //(
  //  inputData.text.size(), std::vector<fts::ngrams>(10));

  for (auto &word : inputData.text) {
    if (!word.empty())
      std::cout << word << "  ";
  }
  outputData = fts::parse(inputData.text, inputData.min_ngram_length,
                          inputData.max_ngram_length);
  std::cout << "\n";

  for (auto &i : outputData) {
    for (auto &k : i.peach) {
      if (!(k.empty()))
        std::cout << k << "  ";
    }
    if (!(i.peach.at(0).empty()))
      std::cout << i.index << "\n";
  }

  return 0;
}
