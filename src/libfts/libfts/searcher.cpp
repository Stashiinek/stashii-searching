#include <libfts/funct.hpp>

#include <picosha2.h>

using namespace fts::ind;

namespace fts{
namespace srch{

std::size_t id = 0;

std::string doc_reader(std::string &filename){
    std::string docdata;
    std::string path = std::filesystem::current_path();
    path = path.substr(0, path.size() - 16);
    path = path + "/index/docs/" + filename + ".txt";

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

std::string TextIndexAccessor::term_entries(std::string &filename){
    std::string termdata;
    std::string path = std::filesystem::current_path();
    path = path.substr(0, path.size() - 16);
    path = path + "/index/entries/" + filename + ".txt";

    if (!std::filesystem::exists(path)){
        //на всякий запустим парсинг нашей либы
    }

    std::ifstream file;
    try{
        //открываем файл и обрабатываем вхождения
        file.open(path);
    } 
    catch (const std::ios_base::failure &e){
        file.close();
        return e.what();
    }
    std::getline(file, termdata); //"чтение" из файла
    file.close();

    return termdata;
}


double TextIndexAccessor::score(int doc_freq, int term_freq, int doc_count){
    double score = term_freq * (static_cast<double>(doc_count) /
                   static_cast<double>(doc_freq));
    return score;
}

//std::unordered_map<std::string, double> term_score;

int get_num(){
    std::string path = std::filesystem::current_path();
    path = path.substr(0, path.size() - 16);
    path = path + "/index/doc_count.txt";
    std::ifstream file;
    file.open(path);

    std::getline(file, path); //"чтение" из файла
    file.close();

    return std::stoi(path);
}

entry_data TextIndexAccessor::write_term_data(std::string &termdata){
    entry_data term;

    std::vector<std::string> splitdata = splitString(termdata);
    term.term = splitdata.at(0);  //записываем терм
    term.term_docs.resize(std::stoi(splitdata.at(1)));

    //term_score.insert(splitdata.at(0), score())
    std::pair<std::string, double> term_n_score = std::make_pair(splitdata.at(0), 0);
    //это нам надо чтобы посчитать score терма

    int count = 2, term_count = 0;
    while (count > splitdata.size()){
        term.term_docs.at(term_count).doc_id = static_cast<size_t>  //записываем id доки
                                    (std::stoi(splitdata.at(count)));
        count++;     //сдвигаем счетчик

        /*for (int i = 0; i < std::stoi(splitdata.at(count)); i++){
            term.term_docs.at(term_count).pos.at(i) =     //записываем позиции вхождений (а зачем)
                                std::stoi(splitdata.at(count + i));
        }*/

        term.term_docs.at(term_count).pos.at(0) =     //записываем количество вхождений в доке
                                std::stoi(splitdata.at(count));

        term_n_score.second += score(std::stoi(splitdata.at(1)), std::stoi(splitdata.at(count)),
                                    get_num());             //считаем score для терма

        count += std::stoi(splitdata.at(count));           // снова сдвиг счетчика
        term_count++;
    }
    return term;
}

void TextIndexAccessor::write(){
    std::sort(search_data.begin(), search_data.end(), []
              (Result &one, Result &two){return one.score < two.score;});

    std::string doc_id_str;
    for (auto &pr : search_data){
        doc_id_str = std::to_string(static_cast<int>(pr.document_id));
        std::cout << pr.score << "   " << doc_reader(doc_id_str) << "\n";
    }
}

void TextIndexAccessor::doc_scores(entry_data &tdata){
    std::pair<std::string, double> founded_term;
    try{
        founded_term = term_score.at(tdata.term);
    }
    /*std::find_if(term_score.begin(), term_score.end(),
                                    [term](std::pair<std::string, double> &miau)       //тут ошибка в лямбде
                                    { return miau.first == term; });*/

    //[doc_id](term_data &data) { return data.doc_id == doc_id; }
    if (founded_term == term_score.end()){  //если не нашлось
        return;
    }

    std::size_t doc_id = 0;
    for (int i = 0; i < tdata.term_docs.size(); i++){
        //здесь короче вписываем score
        //если еще не считали то начинаем считать, а если есть то прибавляем
        doc_id = tdata.term_docs.at(i).doc_id;
        auto search_id = std::find_if(search_data.begin(), search_data.end(),
                                    [doc_id](Result &miau)
                                    { return miau.document_id == doc_id; });
        if (search_id == search_data.end()){
            Result add_res;
            add_res.document_id = doc_id;
            add_res.score = founded_term->second;
            search_data.push_back(add_res);
        } else {
            search_id->score += founded_term->second;
        }
    }
}

void TextIndexAccessor::search(std::string &doc, inData &config){
    //при обновлении запроса нужно сбросить search_data и term_score
    search_data.clear();
    term_score.clear();

    doc = restring(doc);
    std::vector<std::string> doc_words = splitString(doc);
    std::vector<ngrams> doc_terms = parsing(config, doc_words, id);  //получили термы для поиска

    std::unordered_map<std::string, double> miau;

    std::vector<unsigned char> hash(picosha2::k_digest_size);
    std::vector<entry_data> entries;
    entry_data timely_data;

    for (auto &i : doc_terms)
        for (auto &term : i.peach){
            std::string &t = term;
            picosha2::hash256(t.begin(), t.end(), hash.begin(), hash.end());
            t = picosha2::bytes_to_hex_string(hash.begin(), hash.begin()+6); //хешируем наконец
            term = term_entries(t);  //я не должна его перезаписывать

            timely_data = write_term_data(term);
            entries.push_back(timely_data); 

        }
    
    for (auto &entr : entries){
        doc_scores(entr);
    }

    write();
}

} // namespace srch
}