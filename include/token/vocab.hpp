#pragma once

#include "core/map_file.hpp"
#include <unordered_map>
#include <nlohmann/json.hpp> 
using json = nlohmann::json;
typedef struct vocab vocab;

typedef enum {
    MLN_VC_OK,
    MLN_VC_ERR,
}state_vocab;


struct vocab {
    json json_data;
    json json_tokens;
    std::vector<std::string> merge_string;
    std::unordered_map<std::string, int> word_combine;
    std::unordered_map<std::string, int> vocab;
    std::unordered_map<int, std::string> reverse_vocab;
};

state_vocab map_from_json(map_file &data, vocab &vocab_data);
int lookup_vocab_id(vocab &vocab_data, const std::string &key);
std::string lookup_vocab_token(vocab &vocab_data, int id);
std::string lookup_merge(vocab &vocab_data, std::string key);
