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
  /* std::ifstream filedata;    //не смотрите сюда, это для второй лабы
  filedata.open("file.json");
  json data = json::parse(filedata);
  fts::input inputData;
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.text = std::string(argv[1]);
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();

  std::cout << inputData.min_ngram_length << "   " << inputData.max_ngram_length
            << "\n"
            << inputData.text << "\n";

  for (auto word : inputData.stop_words) {
    std::cout << word << "  ";
  }
  std::cout << "\n"; */
  CLI::App app{"App description"};

  double a = 0;
  double b = 0;

  app.add_option("--first", a, "");
  app.add_option("--second", b, "");

  CLI11_PARSE(app, argc, argv);
  double c = fts::summ(a, b);
  std::cout << "Result: " << c << std::endl;

  return 0;
}
