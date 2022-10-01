#include "funct.hpp"

double fts::summ(double a, double b) { return a + b; }

/*static_cast<char> deletePunct(static_cast<char> string) {
  char result;
  int count = 0;
  while (string != '\0') {
    if (std::ispunct(string) == 1)
      result = +string;
    string++;
    count++;
  }
  return string - count;
}

char parse(static_cast<char> string, int min_ngram_length,
           int max_ngram_length) {
  char unpunctString = std::tolower(deletePunct(string));
  int i = 0;
  char word = "";
  //здесь будет цикл по разделению слов для парсинга
} */
