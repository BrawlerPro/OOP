#include <WeatherReport/SimpleForecast.h>
#include <stdexcept>
#include <iostream>
#include <ctime>

// Конструктор по умолчанию
SimpleForecast::SimpleForecast()
        : timestamp(0), morningTemp(0.0), dayTemp(0.0), eveningTemp(0.0), weather("солнечно"), precipitation(0.0) {}

// Конструктор с полным набором параметров
SimpleForecast::SimpleForecast(long timestamp, float morningTemp, float dayTemp, float eveningTemp, std::string weather,
                               float precipitation)
        : timestamp(timestamp), morningTemp(morningTemp), dayTemp(dayTemp), eveningTemp(eveningTemp),
          weather(std::move(weather)), precipitation(precipitation) {
    if (morningTemp < -273 || dayTemp < -273 || eveningTemp < -273 || morningTemp > 60 || dayTemp > 60 ||
        eveningTemp > 60) {
        throw std::invalid_argument("Температура выходит за допустимые пределы!");
    }
    if (precipitation < 0 || precipitation > 1500) {
        throw std::invalid_argument("Осадки выходят за допустимые пределы!");
    }
}

// Конструктор с автоматическим выбором погодного явления
SimpleForecast::SimpleForecast(long timestamp, float morningTemp, float dayTemp, float eveningTemp, float precipitation)
        : timestamp(timestamp), morningTemp(morningTemp), dayTemp(dayTemp), eveningTemp(eveningTemp),
          precipitation(precipitation) {

    if (precipitation > 0) {
        if (morningTemp <= 0 || dayTemp <= 0 || eveningTemp <= 0) {
            weather = "снег";
        } else {
            weather = "дождь";
        }
    } else {
        weather = "солнечно";
    }
}


// Геттеры
long SimpleForecast::getTimestamp() const { return timestamp; }

float SimpleForecast::getMorningTemp() const { return morningTemp; }

float SimpleForecast::getDayTemp() const { return dayTemp; }

float SimpleForecast::getEveningTemp() const { return eveningTemp; }

std::string SimpleForecast::getWeather() const { return weather; }

float SimpleForecast::getPrecipitation() const { return precipitation; }

std::string SimpleForecast::getReadableDate(long timestamp)
{
    auto t = static_cast<std::time_t>(timestamp);
    std::tm tm = *std::localtime(&t);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return buffer;
}



// Сеттеры
void SimpleForecast::setTimestamp(long timestamp) { this->timestamp = timestamp; }

void SimpleForecast::setMorningTemp(float temp) { this->morningTemp = temp; }

void SimpleForecast::setDayTemp(float temp) { this->dayTemp = temp; }

void SimpleForecast::setEveningTemp(float temp) { this->eveningTemp = temp; }

void SimpleForecast::setWeather(const std::string &weather) { this->weather = weather; }

void SimpleForecast::setPrecipitation(float precipitation) { this->precipitation = precipitation; }

// Проверка, является ли прогноз ошибочным
bool SimpleForecast::isInvalidForecast() const {
    if ((weather == "солнечно" || weather == "облачно") && precipitation != 0) {
        return true;
    }
    if (weather == "снег" && (morningTemp > 0 || dayTemp > 0 || eveningTemp > 0)) {
        return true;
    }
    return false;
}

// Получение средней температуры за сутки
float SimpleForecast::getAverageTemp() const {
    return (morningTemp + dayTemp + eveningTemp) / 3;
}

// Оператор += для объединения прогнозов
SimpleForecast &SimpleForecast::operator+=(const SimpleForecast &other) {
    if (this->timestamp != other.timestamp) {
        throw std::invalid_argument("Прогнозы должны быть за одну и ту же дату!");
    }
    this->morningTemp = (this->morningTemp + other.morningTemp) / 2;
    this->dayTemp = (this->dayTemp + other.dayTemp) / 2;
    this->eveningTemp = (this->eveningTemp + other.eveningTemp) / 2;
    this->precipitation = (this->precipitation + other.precipitation) / 2;

    if (this->weather == "солнечно" &&
        (other.weather == "облачно" || other.weather == "дождь" || other.weather == "снег")) {
        this->weather = other.weather;
    } else if (this->weather == "облачно" && (other.weather == "дождь" || other.weather == "снег")) {
        this->weather = other.weather;
    } else if (this->weather == "дождь" && other.weather == "снег") {
        this->weather = other.weather;
    }

    return *this;
}

// Операторы сравнения
bool SimpleForecast::operator<(const SimpleForecast &other) const {
    return this->timestamp < other.timestamp;
}

bool SimpleForecast::operator==(const SimpleForecast &other) const {
    return this->timestamp == other.timestamp;
}

// Операторы ввода/вывода
std::istream &operator>>(std::istream &in, SimpleForecast &forecast) {
    in >> forecast.timestamp >> forecast.morningTemp >> forecast.dayTemp >> forecast.eveningTemp >> forecast.weather
       >> forecast.precipitation;
    return in;
}

std::ostream &operator<<(std::ostream &out, const SimpleForecast &forecast) {
    out << "Дата: " << SimpleForecast::getReadableDate(forecast.getTimestamp()) << "\n"
        << "Температура утром: " << forecast.getMorningTemp() << " °C\n"
        << "Температура днем: " << forecast.getDayTemp() << " °C\n"
        << "Температура вечером: " << forecast.getEveningTemp() << " °C\n"
        << "Погодное явление: " << forecast.getWeather() << "\n"
        << "Осадки: " << forecast.getPrecipitation() << " мм\n";
    return out;
}

