#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fts {
struct ngrams {
  std::vector<std::string> peach; // idk how to name it, ehhhhh,,, ngrams????
  //std::unordered_map<int, std::string> peach;
  std::string document; //this is original document without stop words pasha dushnila
  std::size_t index;
};

void clearNum(std::string &path);
void numberOfDocs(std::size_t num, std::string &path);
std::string find_path();

double summ(double a, double b);
bool ifspace(char i);
bool ifalpha(char i);
std::vector<std::string> splitString(const std::string str);
std::string deletePunct(std::string &str);
void deleteStops(std::vector<std::string> &str,
                 std::vector<std::string> &stops);
std::string lowerLetters(std::string &str);
std::string restring(std::string &str);
std::vector<fts::ngrams> parse(std::vector<std::string> &str, std::size_t &docId, int &min_length,
                               int &max_length);
struct inData {
  int min_ngram_length;
  int max_ngram_length;
  //std::vector<std::string> text;
  std::vector<std::string> stop_words;
};

std::vector<ngrams> parsing(inData &inputData, std::vector<std::string> words, std::size_t &ids);

//std::vector<ngrams> littlemain(inData *inputData);

namespace ind {
struct term_data {
  std::size_t doc_id = 0;
  std::vector<std::size_t> pos;
};

struct entry_data {
  std::string term;
  std::vector<term_data> term_docs;
};

//std::vector<entry_pair> entry_search(std::vector<std::vector<ngrams>> &terms, std::vector<ngrams> &check);

struct Index {
  std::unordered_map<std::size_t, std::string> docs;
  std::unordered_map<std::string, entry_data> rev_docs;
};

class IndexBuilder {
public:
  void set_config(inData &inputData);
  void add_document(std::size_t document_id, std::string &text);
  Index& retIndex();

private:
  Index index;
  inData config;
  void add_term(std::size_t doc_id, std::size_t pos, std::string &term);
  //std::unordered_map<std::string, entry_data> find_entry(std::string &checking, std::vector<ngrams> &terms);
};

class TextIndexWriter {
public:
  void write(Index &miau, std::string &path);
};
} // namespace ind

namespace srch {
  struct Result{
    double score;
    std::size_t document_id;
  };

  std::string doc_reader(std::string &filename, std::string &path);
  int get_num(std::string &path);

  class TextIndexAccessor{
  public:
    void doc_scores(std::string &termdata, std::string &path);
    double score(int doc_freq, int term_freq, int doc_count);
    //void count_scores();
    void search(std::string &doc, inData &config, std::string &path);
    void write(std::string &path);

  private:
    std::unordered_map<std::size_t, double> id_scores;
    std::vector<ngrams> doc_terms;
  };
} // namespace srch

} // namespace fts
