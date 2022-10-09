#include "funct.hpp"

double fts::summ(double a, double b) { return a + b; }

std::string fts::deletePunct(std::string str) {
  std::string result = " ";
  int length = 0;
  for (auto letter : str) {
    if (std::ispunct(static_cast<unsigned char>(letter)) == 0) {
      result[length] = letter;
      length++;
    }
  }
  return result;
}

std::string fts::deleteSpace(std::string str) { return str; }

std::string fts::parse(std::string str, int min_ngram_length,
                       int max_ngram_length) {
  std::cout << str << "\n";
  std::string unpunctString = fts::deletePunct(str);
  unpunctString = fts::deleteSpace(unpunctString);
  return unpunctString;
}
