#ifndef SIMPLEFORECAST_H
#define SIMPLEFORECAST_H

#include <string>
#include <iostream>

/**
 * @brief Класс для представления суточного прогноза погоды.
 *
 * Класс хранит данные о погоде за одни сутки, включая дату, температуры утром, днем и вечером,
 * погодное явление и количество осадков. Также включает методы для проверки корректности данных.
 */
class SimpleForecast {
private:
    long timestamp;          ///< Дата прогноза (unix timestamp)
    float morningTemp;       ///< Температура утром (в градусах Цельсия)
    float dayTemp;           ///< Температура днем (в градусах Цельсия)
    float eveningTemp;       ///< Температура вечером (в градусах Цельсия)
    std::string weather;     ///< Погодное явление (солнечно, облачно, дождь, снег)
    float precipitation;     ///< Количество осадков (в мм)

public:
    /**
     * @brief Конструктор по умолчанию.
     *
     * Инициализирует объект с начальными значениями: нулевая дата, нулевая температура, солнечно и без осадков.
     */
    SimpleForecast();

    /**
     * @brief Конструктор с параметрами.
     *
     * Инициализирует объект с заданными значениями даты, температур, погодного явления и осадков.
     *
     * @param timestamp Дата прогноза (unix timestamp).
     * @param morningTemp Температура утром.
     * @param dayTemp Температура днем.
     * @param eveningTemp Температура вечером.
     * @param weather Погодное явление (солнечно, облачно, дождь, снег).
     * @param precipitation Количество осадков (в мм).
     *
     * @throw std::invalid_argument Если температуры выходят за допустимые пределы [-273, +60] градусов или количество осадков превышает 1500 мм.
     */
    SimpleForecast(long timestamp, float morningTemp, float dayTemp, float eveningTemp, std::string weather, float precipitation);

    /**
     * @brief Конструктор с автоматическим выбором погодного явления.
     *
     * Если осадки больше 0, выбирается дождь или снег в зависимости от температуры.
     *
     * @param timestamp Дата прогноза (unix timestamp).
     * @param morningTemp Температура утром.
     * @param dayTemp Температура днем.
     * @param eveningTemp Температура вечером.
     * @param precipitation Количество осадков (в мм).
     *
     * @throw std::invalid_argument Если температуры выходят за допустимые пределы [-273, +60] градусов или количество осадков превышает 1500 мм.
     */
    SimpleForecast(long timestamp, float morningTemp, float dayTemp, float eveningTemp, float precipitation);

    // --- Геттеры ---
    /**
     * @brief Получить дату прогноза.
     *
     * @return Дата прогноза (unix timestamp).
     */
    [[nodiscard]] long getTimestamp() const;

    /**
     * @brief Получить температуру утром.
     *
     * @return Температура утром (в градусах Цельсия).
     */
    [[nodiscard]] float getMorningTemp() const;

    /**
     * @brief Получить температуру днем.
     *
     * @return Температура днем (в градусах Цельсия).
     */
    [[nodiscard]] float getDayTemp() const;

    /**
     * @brief Получить температуру вечером.
     *
     * @return Температура вечером (в градусах Цельсия).
     */
    [[nodiscard]] float getEveningTemp() const;

    /**
     * @brief Получить погодное явление.
     *
     * @return Погодное явление (солнечно, облачно, дождь или снег).
     */
    [[nodiscard]] std::string getWeather() const;

    /**
     * @brief Получить количество осадков.
     *
     * @return Количество осадков (в мм).
     */
    [[nodiscard]] float getPrecipitation() const;

    /**
    * @brief Получить дату в читаемом формате.
       *
    * @return Дата в строковом формате.("%Y-%m-%d %H:%M:%S")
    */
    static std::string getReadableDate(long timestamp);

    // --- Сеттеры ---
    /**
     * @brief Установить дату прогноза.
     *
     * @param timestamp Дата прогноза (unix timestamp).
     */
    void setTimestamp(long timestamp);

    /**
     * @brief Установить температуру утром.
     *
     * @param temp Температура утром (в градусах Цельсия).
     */
    void setMorningTemp(float temp);

    /**
     * @brief Установить температуру днем.
     *
     * @param temp Температура днем (в градусах Цельсия).
     */
    void setDayTemp(float temp);

    /**
     * @brief Установить температуру вечером.
     *
     * @param temp Температура вечером (в градусах Цельсия).
     */
    void setEveningTemp(float temp);

    /**
     * @brief Установить погодное явление.
     *
     * @param weather Погодное явление (солнечно, облачно, дождь, снег).
     */
    void setWeather(const std::string &weather);

    /**
     * @brief Установить количество осадков.
     *
     * @param precipitation Количество осадков (в мм).
     */
    void setPrecipitation(float precipitation);

    // --- Прочие методы ---
    /**
     * @brief Проверить, является ли прогноз ошибочным.
     *
     * Ошибочным прогноз считается, если при солнечной или облачной погоде есть осадки, или если при снеге температура выше 0.
     *
     * @return true Если прогноз ошибочный.
     * @return false Если прогноз корректный.
     */
    [[nodiscard]] bool isInvalidForecast() const;

    /**
     * @brief Рассчитать среднюю температуру за сутки.
     *
     * @return Средняя температура за сутки (в градусах Цельсия).
     */
    [[nodiscard]] float getAverageTemp() const;

    /**
     * @brief Оператор += для объединения двух прогнозов за одну дату.
     *
     * При объединении берется среднее значение температур и осадков, а для погодного явления выбирается наихудшее из двух.
     *
     * @param other Другой прогноз для объединения.
     * @return Ссылка на обновленный объект этого прогноза.
     *
     * @throw std::invalid_argument Если прогнозы относятся к разным датам.
     */
    SimpleForecast& operator+=(const SimpleForecast &other);

    // --- Операторы ввода и вывода ---
    /**
     * @brief Оператор ввода для прогноза.
     *
     * @param in Входной поток.
     * @param forecast Объект SimpleForecast для ввода данных.
     * @return Ссылка на входной поток.
     */
    friend std::istream& operator>>(std::istream &in, SimpleForecast &forecast);

    /**
     * @brief Оператор вывода для прогноза.
     *
     * @param out Выходной поток.
     * @param forecast Объект SimpleForecast для вывода данных.
     * @return Ссылка на выходной поток.
     */
    friend std::ostream& operator<<(std::ostream &out, const SimpleForecast &forecast);

    // --- Операторы сравнения ---
    /**
     * @brief Оператор < для сравнения прогнозов по дате.
     *
     * @param other Другой прогноз для сравнения.
     * @return true Если дата текущего прогноза меньше даты другого прогноза.
     */
    bool operator<(const SimpleForecast &other) const;

    /**
     * @brief Оператор == для сравнения прогнозов по дате.
     *
     * @param other Другой прогноз для сравнения.
     * @return true Если дата обоих прогнозов совпадает.
     */
    bool operator==(const SimpleForecast &other) const;
};

#endif // SIMPLEFORECAST_H
