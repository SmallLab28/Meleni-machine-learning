#include <iostream>
#include "core/map_file.hpp"
#include "token/vocab.hpp"
#include "token/bpe.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

#ifdef _WIN32
    const char *file_path = "C:\\MELENI-MLNI\\tokenizer.json";
#else
    const char *file_path = "tokenizer.json";
#endif

    map_file file{};
    vocab vocab_data{};
    open_file(file_path, file);
    test_file(file);
    map_from_json(file, vocab_data);

    std::string text = "hello";
    std::cout << "INPUT: " << text << "\n";
    std::vector<int> tokens = encode(vocab_data, text);
    std::string out = decode(vocab_data, tokens);
    std::cout << "AI RESPONE: " << out << "\n";

    drop_file(file);
    return 0;
}
