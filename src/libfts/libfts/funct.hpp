#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

namespace fts {
double summ(double a, double b);
std::string deletePunct(std::string str);
void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops);
std::string lowerLetters(std::string str);
std::string parse(std::string str, int min_ngram_length, int max_ngram_length);

struct input {
  int min_ngram_length;
  int max_ngram_length;
  std::vector<std::string> text;
  std::vector<std::string> stop_words;
};
} // namespace fts
