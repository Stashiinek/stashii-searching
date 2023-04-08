#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <libfts/funct.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(summTest, parsingOne) {
  fts::inData testingOne;
  std::ifstream filedata;
  std::string path = fts::find_path() + "/src/libfts/libfts/file.json";
  filedata.open(path);
  json data = json::parse(filedata);

  std::string text = {"Hel/lo! This is the test."};
  testingOne.stop_words = data["stopwords"].get<std::vector<std::string>>();
  testingOne.max_ngram_length = 5;
  testingOne.min_ngram_length = 2;

  std::vector<fts::ngrams> expectedResult(5);
  expectedResult.at(0).index = 0;
  expectedResult.at(0).peach = {"he", "hel", "hell", "hello"};

  expectedResult.at(4).index = 4;
  expectedResult.at(4).peach = {"te", "tes", "test"};

  text = fts::restring(text);

  std::vector<std::string> vec = fts::splitString(text);

  std::vector<fts::ngrams> result;
  std::size_t id = 4;
  result = fts::parsing(testingOne, vec, id);

  EXPECT_EQ(result.at(0).peach, expectedResult.at(0).peach);
  EXPECT_EQ(result.at(4).peach, expectedResult.at(4).peach);
}

TEST(summTest, parsingAnother) {
  fts::inData testingOne;
  std::ifstream filedata;
  std::string path = fts::find_path() + "/src/libfts/libfts/file.json";
  filedata.open(path);
  json data = json::parse(filedata);

  std::string text = {"i am little meow"};
  testingOne.stop_words = data["stopwords"].get<std::vector<std::string>>();
  testingOne.max_ngram_length = 5;
  testingOne.min_ngram_length = 2;

  std::vector<fts::ngrams> expectedResult(5);
  expectedResult.at(0).index = 0;
  expectedResult.at(0).peach = {"i"};

  expectedResult.at(1).index = 1;
  expectedResult.at(1).peach = {"am"};

  expectedResult.at(2).index = 2;
  expectedResult.at(2).peach = {"li", "lit", "litt", "littl"};

  expectedResult.at(3).index = 3;
  expectedResult.at(3).peach = {"me", "meo", "meow"};

  text = fts::restring(text);

  std::vector<std::string> vec = fts::splitString(text);

  std::vector<fts::ngrams> result;
  std::size_t id = 7;
  result = fts::parsing(testingOne, vec, id);

  EXPECT_EQ(result.at(0).peach, expectedResult.at(0).peach);
  EXPECT_EQ(result.at(1).peach, expectedResult.at(1).peach);
  EXPECT_EQ(result.at(2).peach, expectedResult.at(2).peach);
  EXPECT_EQ(result.at(3).peach, expectedResult.at(3).peach);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
