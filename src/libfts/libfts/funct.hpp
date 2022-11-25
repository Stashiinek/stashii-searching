#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace fts {
struct ngrams {
  std::vector<std::string> peach; // idk how to name it, ehhhhh,,, ngrams????
  std::string document;
  int index;
};
double summ(double a, double b);
bool ifspace(char i);
bool ifalpha(char i);
std::vector<std::string> splitString(const std::string str);
std::string deletePunct(std::string &str);
void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops);
std::string lowerLetters(std::string &str);
std::string restring(std::string &str);
std::vector<fts::ngrams> parse(std::vector<std::string> &str, int &min_length,
                               int &max_length);
struct inData {
  int min_ngram_length;
  int max_ngram_length;
  std::string text;
  std::vector<std::string> stop_words;
};
std::vector<ngrams> parsing(inData *inputData);

std::vector<ngrams> littlemain(inData *inputData);

namespace ind {
struct term_data {
  std::size_t doc_id = 0;
  std::vector<std::size_t> pos;
};

struct entry_data {
  std::string term;
  std::vector<term_data> term_docs;
};
class Index {
public:
  std::map<std::size_t, std::string> docs;
  std::multimap<std::string, entry_data> entires;
};

class IndexBuilder {
public:
  void add_document(int document_id, std::string text);

private:
  Index index;
};

class TextUndexWriter {
public:
  void write(std::string path, int index);
};
} // namespace ind

} // namespace fts
