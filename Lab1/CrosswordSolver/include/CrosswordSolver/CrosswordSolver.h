#ifndef CROSSWORD_SOLVER_H
#define CROSSWORD_SOLVER_H

#include <vector>
#include <string>

/**
 * @brief Проверяет, содержит ли строка допустимые символы (буквы и '?')
 *
 * @param pattern Шаблон искомого слова
 * @return true Если строка валидна
 * @return false Если строка содержит недопустимые символы
 */

bool isValidPattern(const std::string& pattern);

/**
 * @brief Функция разгадывания кроссвордов (перегрузка для const char*)
 *
 * @param pattern Шаблон искомого слова
 * @param words Вектор слов, по которым нужно пройтись
 * @return Вектор строк, подходящих под шаблон
 */

std::vector<std::string> solveCrossword(const std::string& pattern, const std::vector<std::string>& words);

/**
 * @brief Функция разгадывания кроссвордов (перегрузка для std::string)
 *
 * @param pattern Шаблон искомого слова
 * @param words Вектор слов, по которым нужно пройтись
 * @return Вектор строк, подходящих под шаблон
 */

std::vector<std::string> solveCrossword(const char* pattern, const std::vector<std::string>& words);

#endif // CROSSWORD_SOLVER_H
