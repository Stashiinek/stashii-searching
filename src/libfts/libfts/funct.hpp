#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

namespace fts {
struct ngrams {
  std::string peach; // idk how to name it,,,, ehhhhh,,,, ngrams????
  int index;
};
double summ(double a, double b);
std::string deletePunct(std::string str);
void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops);
std::string lowerLetters(std::string str);
std::string restring(std::string str);
std::vector<std::vector<fts::ngrams>> parse(std::vector<std::string> str,
                                            int &min_length, int &max_length);
struct input {
  int min_ngram_length;
  int max_ngram_length;
  std::vector<std::string> text;
  std::vector<std::string> stop_words;
};
} // namespace fts
