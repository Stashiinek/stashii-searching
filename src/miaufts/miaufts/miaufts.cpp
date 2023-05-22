#include <miaufts/miaufts.hpp>
#include <csv.h>
#include <iostream>

std::string subpath(){
    std::string path = std::filesystem::current_path();
    path = path.substr(0, path.size() - 7);
    return path;
}

fts::inData ret_inData(){
    fts::inData inputData;
    inputData.min_ngram_length = 3;
    inputData.max_ngram_length = 7;
    inputData.stop_words = {"a", "an", "and","are","as","at","be","but","by","for","if","in",
              "into","is","it","no","not","of","on","or","s","such","t","that",
              "the","their","then","there","these","they","this","to","was","will","with"};
    return inputData;
}

void indexator(){
    fts::inData inputData = ret_inData();

    std::string path = subpath();
    std::string path1 = path + "/src/libfts/libfts/books.csv";

    io::CSVReader<2> meowlib (path1);
    try{
        //открываем файл и обрабатываем вхождения
        meowlib.read_header(io::ignore_extra_column, "bookID", "title");
    } 
    catch (const std::ios_base::failure &e){
        std::cout << "Ошибка! Отстутствует файл индексации или неправильно указан путь\n";
        return;
    }

    fts::ind::IndexBuilder snacks;
    snacks.set_config(inputData);

    fts::clearNum(path);
    std::string document_data = "hello this is a test";
    std::size_t doc_id = 4;
    fts::ind::Index &testIndex = snacks.retIndex();
    fts::ind::TextIndexWriter cringe;

    while (meowlib.read_row(doc_id, document_data)){
      snacks.add_document(doc_id, document_data);
      testIndex = snacks.retIndex();
    }
    cringe.writedocs(testIndex, path);
}

void search(){
    fts::inData inputData = ret_inData();
    
    std::string path1 = subpath();

    std::string query;
    std::cout << "Введите запрос: ";
    getline(std::cin, query);

    fts::srch::TextIndexAccessor trying_find;
    
    std::cout << "\n";

    trying_find.search(query, inputData, path1);
    //std::cout << "miau\n";
    trying_find.write(path1);
    //std::cout << "miau\n";
}