#include "funct.hpp"

double fts::summ(double a, double b) { return a + b; }

std::string fts::deletePunct(std::string str) {
  std::string result = " ";
  for (auto letter : str) {
    // std::cout << std::ispunct(letter) << "\n";
    if (std::ispunct(letter) == 0) {
      result += letter;
    }
  }
  // std::cout << result << "\n";
  return result;
}

std::string fts::lowerLetters(std::string str) {
  for (auto &letter : str) {
    letter = std::tolower(letter);
  }
  return str;
}

/* std::string deleteStopsSecondVersion(std::string &str,
                                     std::vector<std::string> &stops) {
  for (auto &checks : stops)
    if (str == checks)
      return " ";

  return str;
} */

void fts::deleteStops(std::vector<std::string> &str,
                      std::vector<std::string> &stops) {
  for (auto &checkStop : stops) {
    auto be = std::remove(str.begin(), str.end(), checkStop);
    if (be != str.end())
      str.erase(be, str.end());
  }
}

std::string fts::parse(std::string str, int min_ngram_length,
                       int max_ngram_length) {
  std::string unpunctString = fts::deletePunct(str);
  unpunctString = fts::lowerLetters(unpunctString);
  return unpunctString;
}
