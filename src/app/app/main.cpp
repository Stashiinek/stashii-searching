#include "libfts/funct.hpp"
#include <csv.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <nlohmann/json.hpp>

#include <iostream>

using json = nlohmann::json;

int main(int argc, char **argv) {
  std::string js_path = fts::find_path() + "/src/libfts/libfts/file.json";   //хвала аллаху не надо пихать теперь это файл к исполняемому после удаления пресета

  std::ifstream filedata;
  CLI::App app{"App description"};
  filedata.open(js_path);

  json data = json::parse(filedata);

  fts::inData inputData;
  inputData.min_ngram_length = data["min_length"].get<int>();
  inputData.max_ngram_length = data["max_length"].get<int>();
  inputData.stop_words = data["stopwords"].get<std::vector<std::string>>();
  filedata.close();

  std::string comm, path1, path2;
  path1 = "default";
  path2 = "def";

  CLI::App* sub = app.add_subcommand("search", "path to index");
  sub->add_option("--index", path1);
  sub->add_option("--query", path2);

  CLI::App* sub2 = app.add_subcommand("index", "this is for index");
  sub2->add_option("--csv", path1);
  sub2->add_option("--index", path2);

  CLI11_PARSE(app, argc, argv);
  std::string path = fts::find_path();

  if(sub->parsed()){
    if ((path1 =="default")||(path1 == ".")||(path1 == " "))
      path1 = path;

    /*if ((path2 !="default")||(path2 != ".")||(path2 != " "))
      path = path1;*/

    std::string query;
    fts::srch::TextIndexAccessor trying_find;
    
    if (path2 == "def"){
      std::cout << "Введите запрос: ";
      getline(std::cin, query);
    
      while (!query.empty()){
        std::cout << "\x1B[2J\x1B[H";

        std::cout << "\n";
        trying_find.search(query, inputData, path1);
        trying_find.write(path1);

        std::cout << "\n";
        std::cout << "Введите запрос: ";
        getline(std::cin, query);

        std::cout << "\x1B[2J\x1B[H";
      }

      std::cout << "\x1B[2J\x1B[H";
    } else {
      std::cout << "\n";

      trying_find.search(path2, inputData, path1);
      trying_find.write(path1);
    }
    
  }
  else if (sub2->parsed()){
    if ((path1 == "default")||(path1 == ".")||(path1 == " "))
      path1 = fts::find_path() + "/src/libfts/libfts/books.csv";

    if ((path2 =="default")||(path2 == ".")||(path2 == " "))
      path2 = path;

    io::CSVReader<2> meowlib (path1);
    try{
        //открываем файл и обрабатываем вхождения
        
        meowlib.read_header(io::ignore_extra_column, "bookID", "title");
    } 
    catch (const std::ios_base::failure &e){
        std::cout << "Ошибка! Отстутствует файл индексации или неправильно указан путь\n";
        return 0;
    }
    fts::ind::IndexBuilder snacks;    //в этот момент я не знала как назвать экземпляр класса и ела чипсеки
    snacks.set_config(inputData);

    fts::clearNum(path2);
    std::string document_data = "hello this is a test";
    std::size_t doc_id = 4;
    fts::ind::Index &testIndex = snacks.retIndex();
    fts::ind::TextIndexWriter cringe;

    while (meowlib.read_row(doc_id, document_data)){
      snacks.add_document(doc_id, document_data);
      testIndex = snacks.retIndex();
    }
    cringe.writedocs(testIndex, path2);
  } else std::cout << "Ошибка! Неверно введена команда\n";

  return 0;
}
