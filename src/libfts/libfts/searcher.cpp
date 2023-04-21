#include <libfts/funct.hpp>

#include <picosha2.h>

using namespace fts::ind;

namespace fts{
namespace srch{

std::size_t id = 0;

std::string doc_reader(std::string &filename){
    std::string docdata;
    std::string path = find_path() + "/index/docs/" + filename + ".txt";

    std::ifstream file;
    try{
        //открываем файл и обрабатываем вхождения
        file.open(path);
    } 
    catch (const std::ios_base::failure &e){
        file.close();
        return e.what();
    }
    std::getline(file, docdata); //"чтение" из файла
    file.close();

    return docdata;
}

int get_num(){
    std::string path = find_path() + "/index/doc_count.txt";
    std::ifstream file;
    int num;
    file.open(path);

    file >> num;
    file.close();

    return num;
}

double TextIndexAccessor::score(int doc_freq, int term_freq, int doc_count){
    double score = term_freq * (static_cast<double>(doc_count) /
                   static_cast<double>(doc_freq));
    return score;
}

void TextIndexAccessor::doc_scores(std::string &filename){
    std::string termdata;
    std::string path = find_path() + "/index/entries/" + filename + ".txt";

    if (!std::filesystem::exists(path)){
        //на всякий запустим парсинг нашей либы
    }

    if (!std::filesystem::exists(path)){
        return;     // все таки ничего нету
    }

    std::ifstream file;
    try{
        //открываем файл и обрабатываем вхождения
        file.open(path);
    } 
    catch (const std::ios_base::failure &e){
        file.close();
        std::cout << "Ошибка! Файл " << filename << ".txt не открывается \n";
        return;
    }
    
    int num;
    std::string term;
    int trashpos;

    file >> term >> num;
    std::size_t calcId = 0;
    double tscore;
    int counter;
    auto find_id = id_scores.find(calcId);

    while (!file.eof()){
        file >> calcId >> counter;

        find_id = id_scores.find(calcId);

        for (int i = 0; i < counter; i++){
            file >> trashpos;       // меня смешит этот костыль
            tscore = score(num, counter, get_num());
            id_scores[calcId] += tscore;
        }  
    }

    file.close();
}

void TextIndexAccessor::write(){
    Result timely_res;
    std::vector<Result> result_data;
    for (auto terms: id_scores){
        timely_res.document_id = terms.first;
        timely_res.score = terms.second;
        result_data.push_back(timely_res);
    }

    std::sort(result_data.begin(), result_data.end(),
              [](Result a, Result b) { return a.score > b.score;});
    
    std::string docname;
    
    for (auto terms: result_data){
        docname = std::to_string(terms.document_id);
        docname = doc_reader(docname);
        std::cout << docname << "       " << terms.score << "\n";
    }
}

void TextIndexAccessor::search(std::string &doc, inData &config){
    //при обновлении запроса нужно сбросить result_data и term_score
    id_scores.clear();

    doc = restring(doc);
    std::vector<std::string> doc_words = splitString(doc);
    deleteStops(doc_words, config.stop_words);
    std::vector<ngrams> doc_terms = parsing(config, doc_words, id);  //получили термы для поиска

    std::vector<unsigned char> hash(picosha2::k_digest_size);

    for (auto &i : doc_terms)
        for (auto &term : i.peach){
            std::string &t = term;
            picosha2::hash256(t.begin(), t.end(), hash.begin(), hash.end());
            t = picosha2::bytes_to_hex_string(hash.begin(), hash.begin()+6); //хешируем наконец

            doc_scores(t); //открываем файлы обратного индекса, там же считаем score документов
        }

    write();
}

} // namespace srch
}