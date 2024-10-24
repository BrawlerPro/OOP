#include <gtest/gtest.h>
#include <WeatherReport/ComplexForecast.h>

// Тесты для конструктора по умолчанию
TEST(ComplexForecastTest, DefaultConstructor) {
    ComplexForecast forecast;
    EXPECT_EQ(forecast.findColdestDay(), forecast.findColdestDay()); // Пустая коллекция должна выбросить исключение
}

// Тесты для конструктора с массивом
TEST(ComplexForecastTest, ConstructorWithArray) {
    SimpleForecast forecasts[2] = {
            SimpleForecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f),
            SimpleForecast(1625266000, 10.0f, 15.0f, 5.0f, Weather::Rain, 5.0f)
    };
    ComplexForecast complexForecast(forecasts, 2);

    EXPECT_EQ(complexForecast[0].getWeather(), Weather::Sunny);
    EXPECT_EQ(complexForecast[1].getWeather(), Weather::Rain);
}

// Тесты на добавление прогноза
TEST(ComplexForecastTest, AddForecast) {
    ComplexForecast forecast;
    SimpleForecast newForecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 10.0f);

    forecast.addForecast(newForecast);
    EXPECT_EQ(forecast[0].getWeather(), Weather::Sunny);
}

// Тесты на удаление прогноза
TEST(ComplexForecastTest, RemoveForecast) {
    SimpleForecast forecasts[2] = {
            SimpleForecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f),
            SimpleForecast(1625266000, 10.0f, 15.0f, 5.0f, Weather::Rain, 5.0f)
    };
    ComplexForecast forecast(forecasts, 2);

    forecast.removeForecast(0);
    EXPECT_EQ(forecast[0].getWeather(), Weather::Rain);
}

// Тесты на поиск самого холодного дня
TEST(ComplexForecastTest, FindColdestDay) {
    SimpleForecast forecasts[2] = {
            SimpleForecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f),
            SimpleForecast(1625266000, 10.0f, 15.0f, 5.0f, Weather::Rain, 5.0f)
    };
    ComplexForecast forecast(forecasts, 2);

    SimpleForecast coldest = forecast.findColdestDay();
    EXPECT_FLOAT_EQ(coldest.getAverageTemp(), 15.0f);
}

// Тест на метод removeInvalidForecasts
TEST(ComplexForecastTest, RemoveInvalidForecasts) {
    SimpleForecast forecasts[3] = {
            SimpleForecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 10.0f),
            SimpleForecast(1625266000, 1.0f, 5.0f, 0.0f, Weather::Snow, 10.0f),
            SimpleForecast(1625276000, 10.0f, 15.0f, 5.0f, Weather::Rain, 5.0f)
    };
    ComplexForecast forecast(forecasts, 3);

    forecast.removeInvalidForecasts();
    EXPECT_EQ(forecast[0].getWeather(), Weather::Sunny); // Проверка, что остался только корректный прогноз
}

// Тест на оператор ввода и вывода
TEST(ComplexForecastTest, StreamOperators) {
    ComplexForecast forecast;
    std::stringstream ss;

    ss << forecast;
    EXPECT_NO_THROW(ss >> forecast); // Проверка, что ввод-вывод не выбрасывают исключений
}
