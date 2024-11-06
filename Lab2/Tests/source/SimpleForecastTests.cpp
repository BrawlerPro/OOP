#include <gtest/gtest.h>
#include <WeatherReport/SimpleForecast.h>

using namespace WeatherReport;

// Тесты для конструктора по умолчанию
TEST(SimpleForecastTest, DefaultConstructor) {
    SimpleForecast forecast;
    EXPECT_EQ(forecast.getMorningTemp(), 0);
    EXPECT_EQ(forecast.getDayTemp(), 0);
    EXPECT_EQ(forecast.getEveningTemp(), 0);
    EXPECT_EQ(forecast.getWeather(), Weather::Sunny);
    EXPECT_EQ(forecast.getPrecipitation(), 0);
}

// Тесты для конструктора с параметрами
TEST(SimpleForecastTest, ParameterizedConstructor) {
    SimpleForecast forecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Rain, 10.0f);
    EXPECT_EQ(forecast.getTimestamp(), 1625256000);
    EXPECT_FLOAT_EQ(forecast.getMorningTemp(), 20.0f);
    EXPECT_FLOAT_EQ(forecast.getDayTemp(), 25.0f);
    EXPECT_FLOAT_EQ(forecast.getEveningTemp(), 15.0f);
    EXPECT_EQ(forecast.getWeather(), Weather::Rain);
    EXPECT_FLOAT_EQ(forecast.getPrecipitation(), 10.0f);
}

// Тест на метод isInvalidForecast
TEST(SimpleForecastTest, InvalidForecastCheck) {
    SimpleForecast forecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 10.0f);
    EXPECT_FALSE(forecast.isInvalidForecast());

    SimpleForecast invalidForecast(1625256000, 1.0f, 5.0f, 0.0f, Weather::Snow, 10.0f);
    EXPECT_TRUE(invalidForecast.isInvalidForecast());
}

// Тест на метод getAverageTemp
TEST(SimpleForecastTest, AverageTemperature) {
    SimpleForecast forecast(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f);
    EXPECT_FLOAT_EQ(forecast.getAverageTemp(), 20.0f);
}

// Тесты на операторы
TEST(SimpleForecastTest, Operators) {
    SimpleForecast forecast1(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 10.0f);
    SimpleForecast forecast2(1625256000, 10.0f, 15.0f, 5.0f, Weather::Rain, 5.0f);

    forecast1 += forecast2;

    EXPECT_FLOAT_EQ(forecast1.getMorningTemp(), 15.0f);
    EXPECT_FLOAT_EQ(forecast1.getDayTemp(), 20.0f);
    EXPECT_FLOAT_EQ(forecast1.getEveningTemp(), 10.0f);
    EXPECT_EQ(forecast1.getWeather(), Weather::Rain);
}

// Тест на оператор сравнения
TEST(SimpleForecastTest, ComparisonOperators) {
    SimpleForecast forecast1(1625256000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f);
    SimpleForecast forecast2(1625266000, 20.0f, 25.0f, 15.0f, Weather::Sunny, 0.0f);

    EXPECT_TRUE(forecast1 < forecast2);
    EXPECT_TRUE(forecast1 == forecast1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
