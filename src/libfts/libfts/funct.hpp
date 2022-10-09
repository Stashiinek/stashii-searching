#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fts {
double summ(double a, double b);
std::string deletePunct(std::string str);
std::string deleteSpace(std::string str);
std::string parse(std::string str, int min_ngram_length, int max_ngram_length);

struct input {
  int min_ngram_length;
  int max_ngram_length;
  std::string text;
  std::vector<std::string> stop_words;
};
} // namespace fts
