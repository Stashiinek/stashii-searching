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
  /*std::ifstream filedata;
  filedata.open("file.json");
  json data = json::parse(filedata);
  fts::input inputData;
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.text = std::string(argv[1]);
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>(); */

  std::string be = std::string(argv[1]);
  be = parse(be, 3, 4);

  /* std::cout << inputData.min_ngram_length << "   " <<
  inputData.max_ngram_length
            << "\n"
            << inputData.text << "\n";

  for (auto word : inputData.stop_words) {
    std::cout << word << "  ";
  }
  std::cout << "\n"; */

  return 0;
}
