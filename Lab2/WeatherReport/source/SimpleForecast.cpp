#include <WeatherReport/SimpleForecast.h>
#include <stdexcept>
#include <iostream>
#include <ctime>

// --- Конструкторы ---
SimpleForecast::SimpleForecast()
        : timestamp(std::chrono::system_clock::now()), morningTemp(0), dayTemp(0), eveningTemp(0), weather(Weather::Sunny), precipitation(0) {}

SimpleForecast::SimpleForecast(std::time_t ts, float morning, float day, float evening, Weather w, float precip)
        : timestamp(std::chrono::system_clock::from_time_t(ts)), morningTemp(morning), dayTemp(day), eveningTemp(evening), weather(w), precipitation(precip) {}

SimpleForecast::SimpleForecast(std::time_t ts, float morning, float day, float evening, float precip)
        : timestamp(std::chrono::system_clock::from_time_t(ts)), morningTemp(morning), dayTemp(day), eveningTemp(evening), precipitation(precip) {

    if (precip > 0) {
        weather = (morning <= 0 || day <= 0 || evening <= 0) ? Weather::Snow : Weather::Rain;
    } else {
        weather = Weather::Sunny;
    }
}


// --- Геттеры ---
std::time_t SimpleForecast::getTimestamp() const { return std::chrono::system_clock::to_time_t(timestamp); }

float SimpleForecast::getMorningTemp() const { return morningTemp; }

float SimpleForecast::getDayTemp() const { return dayTemp; }

float SimpleForecast::getEveningTemp() const { return eveningTemp; }

Weather SimpleForecast::getWeather() const { return weather;}

float SimpleForecast::getPrecipitation() const { return precipitation; }



// --- Сеттеры ---
void SimpleForecast::setTimestamp(std::time_t temp) { timestamp = std::chrono::system_clock::from_time_t(temp); }

void SimpleForecast::setMorningTemp(float temp) { morningTemp = temp; }

void SimpleForecast::setDayTemp(float temp) { dayTemp = temp; }

void SimpleForecast::setEveningTemp(float temp) { eveningTemp = temp; }

void SimpleForecast::setWeather(Weather temp) { weather = temp; }

void SimpleForecast::setPrecipitation(float temp) { precipitation = temp; }

// --- Проверка, является ли прогноз ошибочным ---
bool SimpleForecast::isInvalidForecast() const {
    if (morningTemp < -100 || morningTemp > 60 || dayTemp < -100 || dayTemp > 60 || eveningTemp < -100 || eveningTemp > 60) {
        return true;
    }
    if (precipitation > 1500) {
        return true;
    }
    if ((weather == Weather::Sunny || weather == Weather::Cloudy) && precipitation > 0) {
        return true;  // При солнечной или облачной погоде не должно быть осадков
    }
    if (weather == Weather::Snow && (morningTemp > 0 || dayTemp > 0 || eveningTemp > 0)) {
        return true;  // Снег при температуре выше 0°C невозможен
    }
    return false;
}


// --- Получение средней температуры за сутки ---
float SimpleForecast::getAverageTemp() const {
    return (morningTemp + dayTemp + eveningTemp) / 3;
}

// --- Оператор += для объединения прогнозов ---
SimpleForecast &SimpleForecast::operator+=(const SimpleForecast &other) {
    if (this->timestamp != other.timestamp) {
        throw std::invalid_argument("Прогнозы должны быть за одну и ту же дату!");
    }
    morningTemp = (morningTemp + other.morningTemp) / 2;
    dayTemp = (dayTemp + other.dayTemp) / 2;
    eveningTemp = (eveningTemp + other.eveningTemp) / 2;
    precipitation = (precipitation + other.precipitation) / 2;

    if (static_cast<int>(other.weather) > static_cast<int>(weather)) {
        weather = other.weather;
    }

    return *this;
}

// --- Операторы сравнения ---
bool SimpleForecast::operator<(const SimpleForecast &other) const {
    return timestamp < other.timestamp;
}

bool SimpleForecast::operator==(const SimpleForecast &other) const {
    return timestamp == other.timestamp;
}

// --- Операторы ввода/вывода ---
std::istream &operator>>(std::istream &in, SimpleForecast &forecast) {
    std::time_t unix_time;
    in >> unix_time;
    forecast.setTimestamp(unix_time);
    in >> forecast.morningTemp >> forecast.dayTemp >> forecast.eveningTemp;
    int weather_choice;
    in >> weather_choice;
    switch (weather_choice) {
        case 1: forecast.setWeather(Weather::Sunny); break;
        case 2: forecast.setWeather(Weather::Cloudy); break;
        case 3: forecast.setWeather(Weather::Rain); break;
        case 4: forecast.setWeather(Weather::Snow); break;
        case 5: forecast.setWeather(Weather::Windy); break;
        case 6: forecast.setWeather(Weather::Fog); break;
        default: std::cerr << "Неверный выбор, установлено значение по умолчанию: Солнечно.\n";
            forecast.setWeather(Weather::Sunny);
    }
    in >> forecast.precipitation;
    return in;
}

std::ostream &operator<<(std::ostream &out, const SimpleForecast &forecast) {
    std::string wh;
    switch (forecast.weather) {
        case Weather::Sunny: wh = "Солнечно"; break;
        case Weather::Cloudy: wh = "Облачно"; break;
        case Weather::Rain: wh = "Дождь"; break;
        case Weather::Snow: wh = "Снег"; break;
        case Weather::Windy: wh = "Ветрено"; break;
        case Weather::Fog: wh = "Туман"; break;
        default: wh = "Неизвестно";
    }
    std::time_t tm = forecast.getTimestamp();
    out << "Дата: " << std::ctime(&tm)
        << "Температура утром: " << forecast.getMorningTemp() << " °C\n"
        << "Температура днем: " << forecast.getDayTemp() << " °C\n"
        << "Температура вечером: " << forecast.getEveningTemp() << " °C\n"
        << "Погодное явление: " << wh << "\n"
        << "Осадки: " << forecast.getPrecipitation() << " мм\n";
    return out;
}

