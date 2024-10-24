#include <WeatherReport/ComplexForecast.h>

// Конструктор по умолчанию
ComplexForecast::ComplexForecast() : size(0), capacity(10) {
    forecasts = new SimpleForecast[capacity];
}

// Конструктор с инициализацией
ComplexForecast::ComplexForecast(const SimpleForecast* forecastsArray, std::size_t count)
{
    if (count < 1) {
        throw std::invalid_argument("Количество прогнозов должно быть больше 0.");
    }
    forecasts = new SimpleForecast[count];
    size = count;
    capacity = count;
    for (std::size_t i = 0; i < size; ++i) {
        forecasts[i] = forecastsArray[i];
    }
}

// Копирующий конструктор
ComplexForecast::ComplexForecast(const ComplexForecast& other)
{
    forecasts = new SimpleForecast[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (std::size_t i = 0; i < size; ++i) {
        forecasts[i] = other.forecasts[i];
    }
}



// Перемещающий конструктор
ComplexForecast::ComplexForecast(ComplexForecast&& other) noexcept
        : forecasts(other.forecasts), size(other.size), capacity(other.capacity) {
    other.forecasts = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Оператор присваивания (копирующий)
ComplexForecast& ComplexForecast::operator=(const ComplexForecast& other) {
    if (this != &other) {
        delete[] forecasts;
        forecasts = new SimpleForecast[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (std::size_t i = 0; i < size; ++i) {
            forecasts[i] = other.forecasts[i];
        }
    }
    return *this;
}

// Оператор присваивания (перемещающий)
ComplexForecast& ComplexForecast::operator=(ComplexForecast&& other) noexcept {
    if (this != &other) {
        delete[] forecasts;
        forecasts = other.forecasts;
        size = other.size;
        capacity = other.capacity;

        // Обнуляем перемещаемый объект
        other.forecasts = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Деструктор
ComplexForecast::~ComplexForecast() {
    delete[] forecasts;
}

// Увеличение ёмкости массива
void ComplexForecast::resize() {
    auto* newForecasts = new SimpleForecast[capacity * 2];
    capacity *= 2;
    for (std::size_t i = 0; i < size; ++i) {
        newForecasts[i] = forecasts[i];
    }
    delete[] forecasts;
    forecasts = newForecasts;
}

// Добавление нового прогноза
void ComplexForecast::addForecast(const SimpleForecast& forecast) {
    if (size == capacity) {
        resize();
    }
    forecasts[size++] = forecast;
}

// Получение прогноза по индексу
const SimpleForecast& ComplexForecast::operator[](std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Неверный индекс!");
    }
    return forecasts[index];
}

// Удаление прогноза по индексу
void ComplexForecast::removeForecast(std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Неверный индекс!");
    }
    for (std::size_t i = index; i < size - 1; ++i) {
        forecasts[i] = forecasts[i + 1];
    }
    --size;
}

// Поиск самого холодного дня
SimpleForecast ComplexForecast::findColdestDay() const {
    if (size == 0) {
        throw std::runtime_error("Нет прогнозов для анализа.");
    }
    SimpleForecast coldest = forecasts[0];
    for (std::size_t i = 1; i < size; ++i) {
        if (forecasts[i].getAverageTemp() < coldest.getAverageTemp()) {
            coldest = forecasts[i];
        }
    }
    return coldest;
}

// Поиск ближайшего солнечного дня
SimpleForecast& ComplexForecast::findNearestSunnyDay(std::time_t currentTimestamp) const {
    for (std::size_t i = 0; i < size; ++i) {
        if (forecasts[i].getTimestamp() > currentTimestamp && forecasts[i].getWeather() == Weather::Sunny) {
            return forecasts[i];
        }
    }
    throw std::runtime_error("Нет ближайшего солнечного дня.");
}

// Удаление всех ошибочных прогнозов
void ComplexForecast::removeInvalidForecasts() {
    std::size_t validCount = 0;
    for (std::size_t i = 0; i < size; ++i) {
        if (!forecasts[i].isInvalidForecast()) {
            forecasts[validCount++] = forecasts[i];
        }
    }
    size = validCount;
}

// Сортировка прогнозов по дате
void ComplexForecast::sortForecasts() {
    std::sort(forecasts, forecasts + size, [](const SimpleForecast& a, const SimpleForecast& b) {
        return a < b;
    });
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, const ComplexForecast& forecast) {
    for (std::size_t i = 0; i < forecast.size; ++i) {
        out << forecast.forecasts[i] << "\n";
    }
    return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, ComplexForecast& forecast) {
    SimpleForecast temp;
    while (in >> temp) {
        forecast.addForecast(temp);
    }
    return in;
}
