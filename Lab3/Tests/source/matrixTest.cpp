// matrixTest.cpp
#include <gtest/gtest.h>
#include <vector>
#include <Utilities/Matrix.h>

//------------------------------------------------------------------------------
// Конструкция и доступ к базовым элементам
//------------------------------------------------------------------------------
TEST(MatrixTest, ConstructionAndAccess) {
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.getRowCount(), 3u);
    EXPECT_EQ(m.getColCount(), 4u);

    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = static_cast<int>(i * 10 + j);
        }
    }
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            EXPECT_EQ(m(i, j), static_cast<int>(i * 10 + j));
        }
    }
    EXPECT_THROW(m(5, 5), std::out_of_range);
}

//------------------------------------------------------------------------------
// Тестирование метода at() и обработка исключений
//------------------------------------------------------------------------------
TEST(MatrixTest, AtMethod) {
    Matrix<int> m(2, 3);
    int counter = 0;
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = counter++;
        }
    }
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            EXPECT_EQ(m.at(i, j), m(i, j));
        }
    }
    EXPECT_THROW(m.at(2, 0), std::out_of_range);
    EXPECT_THROW(m.at(0, 3), std::out_of_range);
}

//------------------------------------------------------------------------------
// Оператор [] тестироване и обработка исключений
//------------------------------------------------------------------------------
TEST(MatrixTest, OperatorSquareBrackets) {
    Matrix<int> m(3, 3);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = static_cast<int>(i * 10 + j);
        }
    }
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            EXPECT_EQ(m[i][j], static_cast<int>(i * 10 + j));
        }
    }
    EXPECT_THROW(m[3], std::out_of_range);
    EXPECT_THROW(m[0][3], std::out_of_range);
}

//------------------------------------------------------------------------------
// Тест вставки строк
//------------------------------------------------------------------------------
TEST(MatrixTest, InsertRow) {
    Matrix<int> m(2, 3);
    for (size_t j = 0; j < m.getColCount(); ++j) {
        m(0, j) = static_cast<int>(j);
        m(1, j) = static_cast<int>(10 + j);
    }
    int newRow[3] = {100, 101, 102};
    m.insertRow(1, newRow, newRow + 3);
    EXPECT_EQ(m.getRowCount(), 3u);
    for (size_t j = 0; j < m.getColCount(); ++j) {
        EXPECT_EQ(m(0, j), static_cast<int>(j));
    }
    for (size_t j = 0; j < m.getColCount(); ++j) {
        EXPECT_EQ(m(1, j), newRow[j]);
    }
    for (size_t j = 0; j < m.getColCount(); ++j) {
        EXPECT_EQ(m(2, j), static_cast<int>(10 + j));
    }
    std::vector<int> shortRow = {1, 2};
    EXPECT_THROW(m.insertRow(1, shortRow.begin(), shortRow.end()), std::invalid_argument);
    EXPECT_THROW(m.insertRow(5, newRow, newRow + 3), std::out_of_range);
}

//------------------------------------------------------------------------------
// Тест вставки столбцов
//------------------------------------------------------------------------------
TEST(MatrixTest, InsertCol) {
    Matrix<int> m(3, 2);

    for (size_t i = 0; i < m.getRowCount(); ++i) {
        m(i, 0) = static_cast<int>(i * 10);
        m(i, 1) = static_cast<int>(i * 10 + 1);
    }

    int newCol[3] = {100, 101, 102};
    m.insertCol(1, newCol, newCol + 3);
    EXPECT_EQ(m.getColCount(), 3u);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        EXPECT_EQ(m(i, 0), static_cast<int>(i * 10));
        EXPECT_EQ(m(i, 1), newCol[i]);
        EXPECT_EQ(m(i, 2), static_cast<int>(i * 10 + 1));
    }

    std::vector<int> shortCol = {1, 2};
    EXPECT_THROW(m.insertCol(1, shortCol.begin(), shortCol.end()), std::invalid_argument);
    EXPECT_THROW(m.insertCol(5, newCol, newCol + 3), std::out_of_range);
}

//------------------------------------------------------------------------------
// Тестирование удаления строк
//------------------------------------------------------------------------------
TEST(MatrixTest, DeleteRow) {
    Matrix<int> m(3, 3);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = static_cast<int>(i * 10 + j);
        }
    }
    m.deleteRow(1);
    EXPECT_EQ(m.getRowCount(), 2u);
    for (size_t j = 0; j < m.getColCount(); ++j) {
        EXPECT_EQ(m(0, j), static_cast<int>(0 * 10 + j));
        EXPECT_EQ(m(1, j), static_cast<int>(2 * 10 + j));
    }
    EXPECT_THROW(m.deleteRow(5), std::out_of_range);
}

//------------------------------------------------------------------------------
// Тестирование удаления столбцов
//------------------------------------------------------------------------------
TEST(MatrixTest, DeleteCol) {
    Matrix<int> m(3, 3);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = static_cast<int>(j + i * 10);
        }
    }
    m.deleteCol(1);
    EXPECT_EQ(m.getColCount(), 2u);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        EXPECT_EQ(m(i, 0), static_cast<int>(0 + i * 10));
        EXPECT_EQ(m(i, 1), static_cast<int>(2 + i * 10));
    }
    EXPECT_THROW(m.deleteCol(5), std::out_of_range);
}

//------------------------------------------------------------------------------
// Тестирование функциональности итератора
//------------------------------------------------------------------------------
TEST(MatrixTest, IteratorOperations) {
    Matrix<int> m(2, 3);
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            m(i, j) = static_cast<int>(i * 10 + j);
        }
    }
    auto begin = m.begin();
    auto end = m.end();
    EXPECT_EQ(end - begin, static_cast<std::ptrdiff_t>(m.getRowCount() * m.getColCount()));

    int sum = 0;
    for (int & it : m) {
        sum += it;
    }
    int expectedSum = (0 + 1 + 2) + (10 + 11 + 12);
    EXPECT_EQ(sum, expectedSum);
    EXPECT_EQ(m.begin()[0], m(0, 0));
    EXPECT_EQ(m.begin()[2], m(0, 2));
    EXPECT_EQ(m.begin()[3], m(1, 0));
}

//------------------------------------------------------------------------------
// Тестирование метода find()
//------------------------------------------------------------------------------
TEST(MatrixTest, FindFunction) {
    Matrix<int> m(2, 2);
    m(0, 0) = 5;
    m(0, 1) = 10;
    m(1, 0) = 15;
    m(1, 1) = 20;
    auto it = m.find(15);
    ASSERT_NE(it, m.end());
    EXPECT_EQ(*it, 15);
    auto it2 = m.find(999);
    EXPECT_EQ(it2, m.end());
}

//------------------------------------------------------------------------------
// Тест копирующего конструктора
//------------------------------------------------------------------------------
TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m(2, 2);
    m(0, 0) = 1; m(0, 1) = 2;
    m(1, 0) = 3; m(1, 1) = 4;
    Matrix<int> copy(m);
    EXPECT_EQ(copy.getRowCount(), m.getRowCount());
    EXPECT_EQ(copy.getColCount(), m.getColCount());
    for (size_t i = 0; i < m.getRowCount(); ++i) {
        for (size_t j = 0; j < m.getColCount(); ++j) {
            EXPECT_EQ(copy(i, j), m(i, j));
        }
    }
    m(0, 0) = 100;
    EXPECT_NE(copy(0, 0), m(0, 0));
}

//------------------------------------------------------------------------------
// Тест оператора присваивания копированием
//------------------------------------------------------------------------------
TEST(MatrixTest, CopyAssignment) {
    Matrix<int> m1(2, 2);
    m1(0, 0) = 5; m1(0, 1) = 6;
    m1(1, 0) = 7; m1(1, 1) = 8;
    Matrix<int> m2(1, 1);
    m2 = m1;
    EXPECT_EQ(m2.getRowCount(), m1.getRowCount());
    EXPECT_EQ(m2.getColCount(), m1.getColCount());
    for (size_t i = 0; i < m1.getRowCount(); ++i) {
        for (size_t j = 0; j < m1.getColCount(); ++j) {
            EXPECT_EQ(m2(i, j), m1(i, j));
        }
    }

    m2 = m2;
    EXPECT_EQ(m2(0, 0), 5);
}

//------------------------------------------------------------------------------
// Тест перемещяющего конструктора
//------------------------------------------------------------------------------
TEST(MatrixTest, MoveConstructor) {
    Matrix<int> m(2, 2);
    m(0, 0) = 9;  m(0, 1) = 10;
    m(1, 0) = 11; m(1, 1) = 12;
    Matrix<int> moved(std::move(m));
    EXPECT_EQ(m.getRowCount(), 0u);
    EXPECT_EQ(m.getColCount(), 0u);
    EXPECT_EQ(moved(0, 0), 9);
    EXPECT_EQ(moved(0, 1), 10);
    EXPECT_EQ(moved(1, 0), 11);
    EXPECT_EQ(moved(1, 1), 12);
}

//------------------------------------------------------------------------------
// Тест оператор присваивания перемещением
//------------------------------------------------------------------------------
TEST(MatrixTest, MoveAssignment) {
    Matrix<int> m1(2, 2);
    m1(0, 0) = 13; m1(0, 1) = 14;
    m1(1, 0) = 15; m1(1, 1) = 16;
    m1 = std::move(m1);
    Matrix<int> m2(1, 1);
    m2 = std::move(m1);
    EXPECT_EQ(m1.getRowCount(), 0u);
    EXPECT_EQ(m1.getColCount(), 0u);
    EXPECT_EQ(m2(0, 0), 13);
    EXPECT_EQ(m2(0, 1), 14);
    EXPECT_EQ(m2(1, 0), 15);
    EXPECT_EQ(m2(1, 1), 16);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
