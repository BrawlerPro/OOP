#include <gtest/gtest.h>
#include "CrosswordSolver/CrosswordSolver.h"

// Тест на проверку валидности шаблонов
TEST(CrosswordSolverTest, ValidPatternTest) {
    EXPECT_TRUE(isValidPattern("apple"));
    EXPECT_TRUE(isValidPattern("?pple"));
    EXPECT_TRUE(isValidPattern("?????"));
    EXPECT_FALSE(isValidPattern("app1e"));
    EXPECT_FALSE(isValidPattern("app e"));
    EXPECT_FALSE(isValidPattern(""));
}

// Тест функции solveCrossword со std::string
TEST(CrosswordSolverTest, SolveCrosswordString) {
    std::string pattern = "?ppl?";

    std::vector<std::string> dictionary = {"apple", "apply", "ample", "grape"};

    auto results = solveCrossword(pattern, dictionary);


    EXPECT_NE(std::find(results.begin(), results.end(), "apple"), results.end());
    EXPECT_NE(std::find(results.begin(), results.end(), "apply"), results.end());
}

// Тест функции solveCrossword с C строкой
TEST(CrosswordSolverTest, SolveCrosswordCString) {
    const char* pattern = "?ppl?";

    std::vector<std::string> dictionary = {"apple", "apply", "ample", "grape"};

    auto results = solveCrossword(pattern, dictionary);

    EXPECT_NE(std::find(results.begin(), results.end(), "apple"), results.end());
    EXPECT_NE(std::find(results.begin(), results.end(), "apply"), results.end());
}

// Тест на некорректный шаблон
TEST(CrosswordSolverTest, InvalidPatternTest) {
    std::string pattern = "app1e";

    std::vector<std::string> dictionary = {"apple", "apply", "ample", "grape"};

    EXPECT_THROW(solveCrossword(pattern, dictionary), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
