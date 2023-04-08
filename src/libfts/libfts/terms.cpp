#include <libfts/funct.hpp>

namespace fts {

double summ(double a, double b) { return a + b; }

bool ifspace(char i) { return std::isspace(i) > 0; }
bool ifalpha(char i) { return std::isalpha(i) > 0; }

std::string find_path(){
  std::string path = std::filesystem::current_path();
  path = path.substr(0, path.size() - 16);
  return path;
}

std::vector<std::string> splitString(const std::string str) {
  auto start = std::find_if(str.begin(), str.end(), ifalpha);
  auto end = start;
  std::vector<std::string> words;
  while (start != str.end()) {
    end = std::find_if(start, str.end(), ifspace);
    words.push_back(str.substr(start - str.begin(), end - start));
    start = std::find_if(end, str.end(), ifalpha);
  }
  return words;
}

std::string deletePunct(std::string &str) {
  std::string result = "";
  for (auto letter : str) {
    if (std::ispunct(letter) == 0) {
      result += letter;
    }
  }
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

std::string restring(std::string &str) {
  std::string unpunctString = deletePunct(str);
  unpunctString = lowerLetters(unpunctString);
  return unpunctString;
}

std::vector<fts::ngrams> parse(std::vector<std::string> &str, std::size_t &docId, int &min_length,
                               int &max_length) {
  std::vector<fts::ngrams> result(str.size());
  int actual_max = max_length, actual_min = min_length;

  for (std::size_t i = 0; i < str.size(); i++) {
    if (str.at(i) == "")
      continue;
    
    fts::ngrams local_vector;
    local_vector.index = docId;
    actual_max = std::min(static_cast<int>(str.at(i).size()), max_length);
    actual_min = std::min(static_cast<int>(str.at(i).size()), min_length);
    local_vector.document = str.at(i);

    for (int ng_len = actual_min; ng_len <= actual_max; ng_len++) {
      local_vector.peach.push_back(str.at(i).substr(0, ng_len));
    }
    if (!local_vector.peach.empty()) {
      result.at(i).peach = local_vector.peach;
      result.at(i).index = local_vector.index;
      result.at(i).document = local_vector.document;
    }
  }

  return result;
}

void clearNum(){
  std::string path = find_path();
  path = path + "/index/doc_count.txt";

  std::ofstream file1;

  file1.open(path);
  file1 << 0;
  file1.close();
}

void numberOfDocs(){
  std::string path = find_path();
  path = path + "/index/doc_count.txt";
  std::ifstream file;
  std::ofstream file1;

  file.open(path, std::ios::in | std::ios::out);

  int num;
  if (!file){
    num = 0;
  } else file >> num;
  file.close();

  num++;
  file1.open(path);
  file1 << num;
  file1.close();
}

std::vector<ngrams> parsing(inData &inputData, std::vector<std::string> words, std::size_t &ids) {
  fts::deleteStops(words, inputData.stop_words);
  std::vector<fts::ngrams> outputData;

  outputData =
      parse(words, ids, inputData.min_ngram_length, inputData.max_ngram_length);

  numberOfDocs();

  return outputData;
}

} // namespace fts
