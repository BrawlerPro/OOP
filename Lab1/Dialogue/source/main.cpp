#include <CrosswordSolver/CrosswordSolver.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


std::vector<std::string> loadWordsFromFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("The file could not be opened.");
    }

    std::string word;
    while (std::getline(file, word)) {
        word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

int main() {
    try {
        std::cout << "Введите имя файла со словами: ";

        std::string filename;
        std::getline(std::cin, filename);

        std::vector<std::string> dictionary = loadWordsFromFile(filename);

        for (const auto& word : dictionary) {
            std::cout << word << '\n';
        }

        std::string input;
        while (true) {
            std::cout << "Введите шаблон слова (используйте '?' для неизвестных букв).\n";
            std::getline(std::cin, input);

            if (input.empty()) {
                std::cout << "Завершение программы.\n";
                break;
            }

            try {
                auto results = solveCrossword(input, dictionary);

                if (results.empty()) {
                    std::cout << "Слов не найдено.\n";
                } else {
                    std::cout << "Найденные слова:\n";
                    for (const auto& word : results) {
                        std::cout << word << '\n';
                    }
                }
            } catch (const std::exception& ex) {
                std::cerr << "error: " << ex.what() << '\n';
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
