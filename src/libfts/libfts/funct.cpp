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

void fts::deleteStops(std::vector<std::string> &str,
                      std::vector<std::string> &stops) {
  for (auto &checkStop : stops) {
    auto be = std::remove(str.begin(), str.end(), checkStop);
    if (be != str.end())
      str.erase(be, str.end());
  }
}

std::string fts::restring(std::string str) {
  std::string unpunctString = fts::deletePunct(str);
  unpunctString = fts::lowerLetters(unpunctString);
  return unpunctString;
}

std::vector<std::vector<fts::ngrams>>
fts::parse(std::vector<std::string> str, int &min_length, int &max_length) {
  std::vector<std::vector<fts::ngrams>> result(str.size());
  int otstup = 0, k = 0, count = min_length, adekvatno = max_length;
  int actual_max = max_length;
  std::string ekarniy_babay = str.at(0);
  for (int i = 0; i != str.size(); i++) {
    k = 0;
    ekarniy_babay = str.at(i);
    actual_max =
        ekarniy_babay.size() > max_length ? ekarniy_babay.size() : max_length;
    while (count < adekvatno) {
      result.at(i).at(k).peach = ekarniy_babay.substr(otstup, otstup + count);
      result.at(i).at(k).index = i;
      otstup++;
      k++;
    }
  }

  return result;
}
