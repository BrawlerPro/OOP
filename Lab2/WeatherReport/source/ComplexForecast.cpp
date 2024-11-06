#include <WeatherReport/ComplexForecast.h>
#include <algorithm>
#include <stdexcept>

namespace WeatherReport {

// Конструктор по умолчанию
    ComplexForecast::ComplexForecast() : size(0), capacity(10), forecasts(new SimpleForecast[capacity]) {}

// Конструктор с инициализацией
    ComplexForecast::ComplexForecast(const SimpleForecast* forecastsArray, std::size_t count)
            : size(count), capacity(std::max(count, std::size_t(10))), forecasts(new SimpleForecast[capacity]) {
        if (forecastsArray && count > 0) {
            std::copy(forecastsArray, forecastsArray + count, forecasts);
        }
    }

// Копирующий конструктор
    ComplexForecast::ComplexForecast(const ComplexForecast& other) : ComplexForecast(other.forecasts, other.size) {}

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
        std::copy(other.forecasts, other.forecasts + size, forecasts);
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
    capacity *= 2;
    auto* newForecasts = new SimpleForecast[capacity];
    std::copy(forecasts, forecasts + size, newForecasts);
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
const SimpleForecast& ComplexForecast::operator[](std::size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Invalid index!");
    }
    return forecasts[index];
}

SimpleForecast& ComplexForecast::operator[](std::size_t index) {
    return const_cast<SimpleForecast&>(static_cast<const ComplexForecast&>(*this)[index]);
}

// Удаление прогноза по индексу
void ComplexForecast::removeForecast(std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Invalid index!");
    }
    std::move(forecasts + index + 1, forecasts + size, forecasts + index);
    --size;
}

// Поиск самого холодного дня
SimpleForecast ComplexForecast::findColdestDay() const {
    if (size == 0) {
        throw std::runtime_error("There are no forecasts for analysis.");
    }
    return *std::min_element(forecasts, forecasts + size, [](const SimpleForecast& a, const SimpleForecast& b) {
        return a.getAverageTemp() < b.getAverageTemp();
    });
}

// Поиск ближайшего солнечного дня
SimpleForecast& ComplexForecast::findNearestSunnyDay(std::time_t currentTimestamp) const {
    auto it = std::min_element(forecasts, forecasts + size, [currentTimestamp](const SimpleForecast& a, const SimpleForecast& b) {
        if (a.getTimestamp() <= currentTimestamp || a.getWeather() != Weather::Sunny) {
            return false; // a не является подходящим днем
        }
        if (b.getTimestamp() <= currentTimestamp || b.getWeather() != Weather::Sunny) {
            return true; // b не является подходящим днем, а является
        }
        // Выбираем ближайший солнечный день
        return (a.getTimestamp() - currentTimestamp) < (b.getTimestamp() - currentTimestamp);
    });

    if (it != forecasts + size && it->getWeather() == Weather::Sunny && it->getTimestamp() > currentTimestamp) {
        return *it;
    }
    throw std::runtime_error("There is no nearest sunny day.");
}

// Удаление всех ошибочных прогнозов
void ComplexForecast::removeInvalidForecasts() {
    auto newEnd = std::remove_if(forecasts, forecasts + size, [](const SimpleForecast& forecast) {
        return forecast.isInvalidForecast();
    });
    size = newEnd - forecasts;
}

// Сортировка прогнозов по дате
void ComplexForecast::sortForecasts() {
    std::sort(forecasts, forecasts + size, [](const SimpleForecast& a, const SimpleForecast& b) {
        return a.getTimestamp() < b.getTimestamp();
    });
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, const ComplexForecast& forecast) {
    std::for_each(forecast.forecasts, forecast.forecasts + forecast.size, [&out](const SimpleForecast& f) {
        out << f << "\n";
    });
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

}  // namespace WeatherReport
