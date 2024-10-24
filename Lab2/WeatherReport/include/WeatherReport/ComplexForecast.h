#ifndef COMPLEXFORECAST_H
#define COMPLEXFORECAST_H

#include <WeatherReport/SimpleForecast.h>
#include <stdexcept>

/**
 * @brief Класс для управления коллекцией суточных прогнозов погоды.
 */
class ComplexForecast {
private:
    SimpleForecast* forecasts;  ///< Указатель на динамический массив прогнозов
    std::size_t size;           ///< Текущее количество прогнозов
    std::size_t capacity;       ///< Максимальная ёмкость массива

    /**
     * @brief Увеличить ёмкость массива прогнозов.
     * Удваивает текущую ёмкость массива при переполнении.
     */
    void resize();

public:
    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует объект с начальной ёмкостью для хранения прогнозов.
     */
    ComplexForecast();

    /**
     * @brief Конструктор с инициализацией заданным количеством прогнозов.
     *
     * @param forecastsArray Массив суточных прогнозов.
     * @param count Количество прогнозов.
     *
     * @throw std::invalid_argument Если количество прогнозов меньше 1.
     */
    ComplexForecast(const SimpleForecast* forecastsArray, std::size_t count);

    /**
     * @brief Копирующий конструктор.
     *
     * Создаёт копию другого объекта `ComplexForecast`.
     *
     * @param other Другой объект `ComplexForecast` для копирования.
     */
    ComplexForecast(const ComplexForecast& other);

    /**
     * @brief Перемещающий конструктор.
     *
     * Перемещает данные из другого объекта `ComplexForecast`.
     *
     * @param other Другой объект `ComplexForecast` для перемещения.
     */
    ComplexForecast(ComplexForecast&& other) noexcept;

    /**
     * @brief Оператор присваивания для копирования.
     *
     * @param other Другой объект `ComplexForecast` для копирования.
     * @return Ссылка на текущий объект `ComplexForecast`.
     */
    ComplexForecast& operator=(const ComplexForecast& other);

    /**
     * @brief Оператор присваивания для перемещения.
     *
     * @param other Другой объект `ComplexForecast` для перемещения.
     * @return Ссылка на текущий объект `ComplexForecast`.
     */
    ComplexForecast& operator=(ComplexForecast&& other) noexcept;

    /**
     * @brief Деструктор.
     *
     * Освобождает динамически выделенную память.
     */
    ~ComplexForecast();

    /**
     * @brief Добавить новый суточный прогноз в коллекцию.
     *
     * @param forecast Новый суточный прогноз.
     *
     * @throw std::bad_alloc Если не удалось выделить память для нового прогноза.
     */
    void addForecast(const SimpleForecast& forecast);

    /**
     * @brief Получить прогноз по индексу.
     *
     * @param index Индекс прогноза в коллекции.
     * @return Ссылка на объект `SimpleForecast`.
     *
     * @throw std::out_of_range Если индекс выходит за границы массива.
     */
    const SimpleForecast& operator[](std::size_t index);

    /**
     * @brief Удалить прогноз по индексу.
     *
     * @param index Индекс прогноза для удаления.
     *
     * @throw std::out_of_range Если индекс выходит за границы массива.
     */
    void removeForecast(std::size_t index);

    /**
     * @brief Найти самый холодный день.
     *
     * @return Прогноз с самой низкой средней температурой.
     *
     * @throw std::runtime_error Если коллекция прогнозов пуста.
     */
    [[nodiscard]] SimpleForecast findColdestDay() const;

    /**
     * @brief Найти ближайший солнечный день от текущей даты.
     *
     * @param currentTimestamp Текущая дата (unix timestamp).
     * @return Ближайший прогноз с солнечной погодой.
     *
     * @throw std::runtime_error Если нет ближайшего солнечного дня.
     */
    [[nodiscard]] SimpleForecast& findNearestSunnyDay(std::time_t currentTimestamp) const;

    /**
     * @brief Удалить все ошибочные прогнозы.
     */
    void removeInvalidForecasts();

    /**
     * @brief Сортировка прогнозов по дате.
     */
    void sortForecasts();

    /**
     * @brief Оператор вывода в поток.
     *
     * @param out Поток вывода.
     * @param forecast Объект `ComplexForecast`.
     * @return Ссылка на поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& out, const ComplexForecast& forecast);

    /**
     * @brief Оператор ввода из потока.
     *
     * @param in Поток ввода.
     * @param forecast Объект `ComplexForecast`.
     * @return Ссылка на поток ввода.
     */
    friend std::istream& operator>>(std::istream& in, ComplexForecast& forecast);
};

#endif // COMPLEXFORECAST_H
