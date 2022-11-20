#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <libfts/funct.hpp>
#include <nlohmann/json.hpp>

// TEST(summTest, zeroAndZero) { EXPECT_EQ(fts::summ(0, 0), 0); }

using json = nlohmann::json;

TEST(summTest, parsingOne) {
  fts::inData testingOne;
  std::ifstream filedata;
  filedata.open("file.json");
  json data = json::parse(filedata);

  testingOne.text = {"Hel/lo!", "This", "is", "the", "test."};
  testingOne.stop_words = data["stopwords"].get<std::vector<std::string>>();
  testingOne.max_ngram_length = 5;
  testingOne.min_ngram_length = 2;

  std::vector<fts::ngrams> expectedResult(5);
  expectedResult.at(0).index = 0;
  expectedResult.at(0).peach = {"he", "hel", "hell", "hello"};

  expectedResult.at(4).index = 4;
  expectedResult.at(4).peach = {"te", "tes", "test"};

  for (auto &be : testingOne.text) {
    be = fts::restring(be);
  }
  std::vector<fts::ngrams> result;
  result = fts::parsing(&testingOne);

  EXPECT_EQ(result.at(0).peach, expectedResult.at(0).peach);
  EXPECT_EQ(result.at(4).peach, expectedResult.at(4).peach);
}

TEST(summTest, parsingAnother) {
  fts::inData testingOne;
  std::ifstream filedata;
  filedata.open("file.json");
  json data = json::parse(filedata);

  testingOne.text = {"i", "am", "little", "meow"};
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

  std::vector<fts::ngrams> result;
  for (auto &be : testingOne.text) {
    be = fts::restring(be);
  }
  result = fts::parsing(&testingOne);

  EXPECT_EQ(result.at(0).peach, expectedResult.at(0).peach);
  EXPECT_EQ(result.at(1).peach, expectedResult.at(1).peach);
  EXPECT_EQ(result.at(2).peach, expectedResult.at(2).peach);
  EXPECT_EQ(result.at(3).peach, expectedResult.at(3).peach);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
