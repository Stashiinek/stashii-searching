#include "libfts/funct.hpp"

namespace fts {

double summ(double a, double b) { return a + b; }

std::string deletePunct(std::string str) {
  std::string result = "";
  for (auto letter : str) {
    // std::cout << std::ispunct(letter) << "\n";
    if (std::ispunct(letter) == 0) {
      result += letter;
    }
  }
  // std::cout << result << "\n";
  return result;
}

std::string lowerLetters(std::string &str) {
  for (auto &letter : str) {
    letter = std::tolower(letter);
  }
  return str;
}

void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops) {
  for (auto &checkStop : stops) {
    for (auto &word : str) {
      if (word.compare(checkStop) == 0)
        word.erase();
    }
  }
}

std::string restring(std::string str) {
  std::string unpunctString = deletePunct(str);
  unpunctString = lowerLetters(unpunctString);
  return unpunctString;
}

std::vector<fts::ngrams> parse(std::vector<std::string> &str, int &min_length,
                               int &max_length) {
  std::vector<fts::ngrams> result(str.size());
  int actual_max = max_length, actual_min = min_length;

  for (std::size_t i = 0; i < str.size(); i++) {
    fts::ngrams local_vector;
    local_vector.index = i;
    actual_max = std::min(static_cast<int>(str.at(i).size()), max_length);
    actual_min = std::min(static_cast<int>(str.at(i).size()), min_length);

    for (int ng_len = actual_min; ng_len <= actual_max; ng_len++) {
      local_vector.peach.push_back(str.at(i).substr(0, ng_len));
    }
    if (!local_vector.peach.empty()) {
      result.at(i).peach = local_vector.peach;
      result.at(i).index = local_vector.index;
    }
  }

  return result;
}
} // namespace fts
