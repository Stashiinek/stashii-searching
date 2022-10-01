#pragma once
#include <string>
#include <vector>

namespace fts {
double summ(double a, double b);

struct input {
  int min_ngram_length;
  int max_ngram_length;
  std::string text;
  std::vector<std::string> stop_words;
};
} // namespace fts
