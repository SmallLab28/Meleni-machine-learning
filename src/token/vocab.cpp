#include "core/map_file.hpp"
#include <iostream>
#include <unordered_map>
#include "token/vocab.hpp"
#include <nlohmann/json.hpp>
#include <string.h>
#include <stdlib.h>
using json = nlohmann::json;

state_vocab map_from_json(map_file &data, vocab &vocab_data){
    vocab_data.json_data = json::parse(data.file, data.file + data.file_size);
    vocab_data.vocab = vocab_data.json_data["model"]["vocab"].get<std::unordered_map<std::string, int>>();
    for (const auto &pair : vocab_data.vocab) {
        vocab_data.reverse_vocab[pair.second] = pair.first;
    }
    vocab_data.merge_string = vocab_data.json_data["model"]["merges"].get<std::vector<std::string>>();
    for(size_t i = 0; i < vocab_data.merge_string.size(); i++){
        vocab_data.word_combine[vocab_data.merge_string[i]] = i;
    }
    return MLN_VC_OK;
}

int lookup_vocab_id(vocab &vocab_data, const std::string &key){
    auto it = vocab_data.vocab.find(key);
    if (it != vocab_data.vocab.end()){
        return it->second;
    }
    return -1;
}
std::string lookup_vocab_token(vocab &vocab_data,  int id){
    auto it = vocab_data.reverse_vocab.find(id);
    if (it != vocab_data.reverse_vocab.end()){
        return it->second;
    }
    return "MLN_NOT_FOUND_VOCAB";
}

std::string lookup_merge(vocab &vocab_data, std::string key){
    auto it = vocab_data.word_combine.find(key);
    if(it != vocab_data.word_combine.end()){
        return it->first;
    }
    else return "MLN_NOT_FOUND";
}
