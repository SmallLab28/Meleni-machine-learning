#pragma once
#include "token/vocab.hpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
typedef struct  word word;

struct word {
    std::string token;

};

std::vector<int> encode (vocab &vocab_data, const std::string &key);
std::string decode (vocab &vocab_data, const std::vector<int>&list_id);
