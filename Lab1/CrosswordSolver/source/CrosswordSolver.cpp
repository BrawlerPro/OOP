#include <cctype>
#include <stdexcept>
#include <filesystem>
#include <algorithm>
#include <CrosswordSolver/CrosswordSolver.h>

bool matchesPattern(const std::string& word, const std::string& pattern) {
    if (word.length() != pattern.length()) return false;

    return std::equal(word.begin(), word.end(), pattern.begin(),
                      [](char w, char p) {
        return p == '?' || std::tolower(w) == std::tolower(p);
    });
}

bool isValidPattern(const std::string& pattern) {
    if (pattern.empty()) {
        return false;
    }
//    for (char c : pattern) {
//        if (std::isalpha(c) || c == '?') {
//            return false;
//        }
//    }
//    return true;
    return std::all_of(pattern.begin(), pattern.end(), [](char c) {
        return std::isalpha(c) || c == '?';
    });
}

std::vector<std::string> solveCrossword(const std::string& pattern, const std::vector<std::string>& words) {
    if (!isValidPattern(pattern)) {
        throw std::invalid_argument("The template contains invalid characters.");
    }

    std::vector<std::string> result;
    std::copy_if(words.begin(), words.end(), std::back_inserter(result),
                 [&](const std::string& word) {
                     return matchesPattern(word, pattern);
                 });
    return result;
}

std::vector<std::string> solveCrossword(const char* pattern, const std::vector<std::string>& words) {
    if (pattern == nullptr) {
        throw std::invalid_argument("The template must not be nullptr.");
    }
    std::string patternStr(pattern);
    return solveCrossword(patternStr, words);
}


