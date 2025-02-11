#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include <algorithm>

/**
 * @brief Template class for a matrix container that stores elements in a contiguous memory block.
 *
 * @tparam T The type of elements stored in the matrix.
 */
template <typename T>
class Matrix {
private:
    size_t rows, cols;            ///< Number of rows and columns.
    std::unique_ptr<T[]> data;    ///< Dynamic array for storing matrix elements.

public:
    /**
     * @brief Random access iterator for the Matrix class.
     */
    class Iterator {
    private:
        T* ptr;  ///< Pointer to the current element.
    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::random_access_iterator_tag;

        /**
         * @brief Constructor.
         *
         * @param p Pointer to an element.
         */
        explicit Iterator(T* p = nullptr) : ptr(p) {}

        /// Dereference operator.
        reference operator*() const { return *ptr; }
        /// Arrow operator.
        pointer operator->() const { return ptr; }

        /// Pre-increment operator.
        Iterator& operator++() { ++ptr; return *this; }
        /// Post-increment operator.
        Iterator operator++(int) { Iterator temp(*this); ++ptr; return temp; }
        /// Pre-decrement operator.
        Iterator& operator--() { --ptr; return *this; }
        /// Post-decrement operator.
        Iterator operator--(int) { Iterator temp(*this); --ptr; return temp; }

        /// Addition operator.
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        /// Subtraction operator.
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
        /// Difference operator.
        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }

        /// Equality operator.
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        /// Inequality operator.
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        /// Less-than operator.
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
        /// Greater-than operator.
        bool operator>(const Iterator& other) const { return ptr > other.ptr; }
        /// Less-than-or-equal operator.
        bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
        /// Greater-than-or-equal operator.
        bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }

        /// Subscript operator.
        reference operator[](difference_type n) const { return *(ptr + n); }
    };

    /**
     * @brief Constructs a matrix of size r x c.
     *
     * @param r Number of rows.
     * @param c Number of columns.
     */
    Matrix(size_t r, size_t c)
            : rows(r), cols(c), data(std::make_unique<T[]>(r * c))
    {}

    /**
     * @brief Copy constructor.
     *
     * @param other The matrix to copy from.
     */
    Matrix(const Matrix& other)
            : rows(other.rows), cols(other.cols), data(std::make_unique<T[]>(other.rows * other.cols))
    {
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Move constructor.
     *
     * @param other The matrix to move from.
     */
    Matrix(Matrix&& other) noexcept
            : rows(other.rows), cols(other.cols), data(std::move(other.data))
    {
        other.rows = 0;
        other.cols = 0;
    }

    /**
     * @brief Copy assignment operator.
     *
     * @param other The matrix to copy from.
     * @return Matrix& Reference to the assigned matrix.
     */
    Matrix& operator=(const Matrix& other) {
        if (this == &other)
            return *this;
        rows = other.rows;
        cols = other.cols;
        data = std::make_unique<T[]>(rows * cols);
        for (size_t i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     *
     * @param other The matrix to move from.
     * @return Matrix& Reference to the assigned matrix.
     */
    Matrix& operator=(Matrix&& other) noexcept {
        if (this == &other)
            return *this;
        rows = other.rows;
        cols = other.cols;
        data = std::move(other.data);
        other.rows = 0;
        other.cols = 0;
        return *this;
    }

    /**
     * @brief Access operator using (row, col) with bounds checking.
     *
     * @param r Row index.
     * @param c Column index.
     * @return T& Reference to the element.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T& operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix index out of range");
        return data[r * cols + c];
    }

    /**
     * @brief Const version of access operator using (row, col) with bounds checking.
     *
     * @param r Row index.
     * @param c Column index.
     * @return const T& Reference to the element.
     * @throws std::out_of_range if the index is out of bounds.
     */
    const T& operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix index out of range");
        return data[r * cols + c];
    }

    /**
     * @brief Access element using at() with bounds checking.
     *
     * @param r Row index.
     * @param c Column index.
     * @return T& Reference to the element.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T& at(size_t r, size_t c) {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix::at() - index out of range");
        return data[r * cols + c];
    }

    /**
     * @brief Const version of at() for accessing an element with bounds checking.
     *
     * @param r Row index.
     * @param c Column index.
     * @return const T& Reference to the element.
     * @throws std::out_of_range if the index is out of bounds.
     */
    const T& at(size_t r, size_t c) const {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix::at() - index out of range");
        return data[r * cols + c];
    }

    /**
     * @brief Proxy class for row access using the [] operator.
     */
    class RowProxy {
    private:
        Matrix& matrix;  ///< Reference to the matrix.
        size_t row;      ///< Row index.
    public:
        /**
         * @brief Constructor for RowProxy.
         *
         * @param m Reference to the matrix.
         * @param r Row index.
         */
        RowProxy(Matrix& m, size_t r) : matrix(m), row(r) {}

        /**
         * @brief Access operator for columns with bounds checking.
         *
         * @param col Column index.
         * @return T& Reference to the element.
         * @throws std::out_of_range if the column index is out of bounds.
         */
        T& operator[](size_t col) {
            if (col >= matrix.cols)
                throw std::out_of_range("Column index out of range");
            return matrix.data[row * matrix.cols + col];
        }
    };

    /**
     * @brief Const proxy class for row access using the [] operator.
     */
    class ConstRowProxy {
    private:
        const Matrix& matrix;  ///< Reference to the matrix.
        size_t row;            ///< Row index.
    public:
        /**
         * @brief Constructor for ConstRowProxy.
         *
         * @param m Reference to the matrix.
         * @param r Row index.
         */
        ConstRowProxy(const Matrix& m, size_t r) : matrix(m), row(r) {}

        /**
         * @brief Const access operator for columns with bounds checking.
         *
         * @param col Column index.
         * @return const T& Reference to the element.
         * @throws std::out_of_range if the column index is out of bounds.
         */
        const T& operator[](size_t col) const {
            if (col >= matrix.cols)
                throw std::out_of_range("Column index out of range");
            return matrix.data[row * matrix.cols + col];
        }
    };

    /**
     * @brief Non-const row access operator using [].
     *
     * @param rowIndex Row index.
     * @return RowProxy Proxy object for row access.
     * @throws std::out_of_range if the row index is out of bounds.
     */
    RowProxy operator[](size_t rowIndex) {
        if (rowIndex >= rows)
            throw std::out_of_range("Row index out of range");
        return RowProxy(*this, rowIndex);
    }

    /**
     * @brief Const row access operator using [].
     *
     * @param rowIndex Row index.
     * @return ConstRowProxy Proxy object for row access.
     * @throws std::out_of_range if the row index is out of bounds.
     */
    ConstRowProxy operator[](size_t rowIndex) const {
        if (rowIndex >= rows)
            throw std::out_of_range("Row index out of range");
        return ConstRowProxy(*this, rowIndex);
    }

    /**
     * @brief Returns an iterator to the beginning of the matrix.
     *
     * @return Iterator Iterator to the first element.
     */
    Iterator begin() { return Iterator(data.get()); }

    /**
     * @brief Returns an iterator to one past the last element of the matrix.
     *
     * @return Iterator Iterator to the end.
     */
    Iterator end() { return Iterator(data.get() + rows * cols); }

    /**
     * @brief Returns a const iterator to the beginning of the matrix.
     *
     * @return const Iterator Iterator to the first element.
     */
    Iterator begin() const { return Iterator(data.get()); }

    /**
     * @brief Returns a const iterator to one past the last element of the matrix.
     *
     * @return const Iterator Iterator to the end.
     */
    Iterator end() const { return Iterator(data.get() + rows * cols); }

    /**
     * @brief Returns the number of rows in the matrix.
     *
     * @return size_t Number of rows.
     */
    [[nodiscard]] size_t getRowCount() const { return rows; }

    /**
     * @brief Returns the number of columns in the matrix.
     *
     * @return size_t Number of columns.
     */
    [[nodiscard]] size_t getColCount() const { return cols; }

    /**
     * @brief Inserts a new row into the matrix at the specified index.
     *
     * The range [rowBegin, rowEnd) must contain exactly getColCount() elements.
     *
     * @tparam InputIterator Type of input iterator.
     * @param index Row index where the new row will be inserted.
     * @param rowBegin Iterator to the beginning of the new row data.
     * @param rowEnd Iterator to the end of the new row data.
     * @throws std::out_of_range if the index is out of bounds.
     * @throws std::invalid_argument if the number of elements does not match the number of columns.
     */
    template<typename InputIterator>
    void insertRow(size_t index, InputIterator rowBegin, InputIterator rowEnd) {
        if (index > rows)
            throw std::out_of_range("Invalid row index for insertion");
        if (std::distance(rowBegin, rowEnd) != static_cast<std::ptrdiff_t>(cols))
            throw std::invalid_argument("The number of elements in the row does not match the number of columns");

        size_t newRows = rows + 1;
        auto newData = std::make_unique<T[]>(newRows * cols);

        for (size_t i = 0; i < index; i++) {
            for (size_t j = 0; j < cols; j++) {
                newData[i * cols + j] = data[i * cols + j];
            }
        }
        auto it = rowBegin;
        for (size_t j = 0; j < cols; j++) {
            newData[index * cols + j] = *it;
            ++it;
        }
        for (size_t i = index; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                newData[(i + 1) * cols + j] = data[i * cols + j];
            }
        }
        rows = newRows;
        data = std::move(newData);
    }

    /**
     * @brief Inserts a new column into the matrix at the specified index.
     *
     * The range [colBegin, colEnd) must contain exactly getRowCount() elements.
     *
     * @tparam InputIterator Type of input iterator.
     * @param index Column index where the new column will be inserted.
     * @param colBegin Iterator to the beginning of the new column data.
     * @param colEnd Iterator to the end of the new column data.
     * @throws std::out_of_range if the index is out of bounds.
     * @throws std::invalid_argument if the number of elements does not match the number of rows.
     */
    template<typename InputIterator>
    void insertCol(size_t index, InputIterator colBegin, InputIterator colEnd) {
        if (index > cols)
            throw std::out_of_range("Invalid column index for insertion");
        if (std::distance(colBegin, colEnd) != static_cast<std::ptrdiff_t>(rows))
            throw std::invalid_argument("The number of elements in the column does not match the number of rows");

        size_t newCols = cols + 1;
        auto newData = std::make_unique<T[]>(rows * newCols);

        auto it = colBegin;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < index; j++) {
                newData[i * newCols + j] = data[i * cols + j];
            }
            newData[i * newCols + index] = *it;
            ++it;
            for (size_t j = index; j < cols; j++) {
                newData[i * newCols + (j + 1)] = data[i * cols + j];
            }
        }
        cols = newCols;
        data = std::move(newData);
    }

    /**
     * @brief Deletes a row from the matrix at the specified index.
     *
     * @param index Row index to be deleted.
     * @throws std::out_of_range if the index is out of bounds.
     */
    void deleteRow(size_t index) {
        if (index >= rows)
            throw std::out_of_range("Invalid row index for deletion");

        size_t newRows = rows - 1;
        auto newData = std::make_unique<T[]>(newRows * cols);

        for (size_t i = 0; i < index; i++) {
            for (size_t j = 0; j < cols; j++) {
                newData[i * cols + j] = data[i * cols + j];
            }
        }
        for (size_t i = index + 1; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                newData[(i - 1) * cols + j] = data[i * cols + j];
            }
        }
        rows = newRows;
        data = std::move(newData);
    }

    /**
     * @brief Deletes a column from the matrix at the specified index.
     *
     * @param index Column index to be deleted.
     * @throws std::out_of_range if the index is out of bounds.
     */
    void deleteCol(size_t index) {
        if (index >= cols)
            throw std::out_of_range("Invalid column index for deletion");

        size_t newCols = cols - 1;
        auto newData = std::make_unique<T[]>(rows * newCols);

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < index; j++) {
                newData[i * newCols + j] = data[i * cols + j];
            }
            for (size_t j = index + 1; j < cols; j++) {
                newData[i * newCols + (j - 1)] = data[i * cols + j];
            }
        }
        cols = newCols;
        data = std::move(newData);
    }

    /**
     * @brief Finds the first occurrence of a given value in the matrix.
     *
     * @param value The value to find.
     * @return Iterator Iterator pointing to the found element, or end() if not found.
     */
    Iterator find(const T& value) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == value)
                return it;
        }
        return end();
    }
};
