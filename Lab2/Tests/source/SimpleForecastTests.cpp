#include <WeatherReport/SimpleForecast.h>
#include <gtest/gtest.h>

TEST(SimpleForecastTests, DefaultConstructor) {
    SimpleForecast forecast;
    EXPECT_EQ(forecast.getTimestamp(), 0);
    EXPECT_FLOAT_EQ(forecast.getMorningTemp(), 0.0);
    EXPECT_FLOAT_EQ(forecast.getDayTemp(), 0.0);
    EXPECT_FLOAT_EQ(forecast.getEveningTemp(), 0.0);
    EXPECT_EQ(forecast.getWeather(), "солнечно");
    EXPECT_FLOAT_EQ(forecast.getPrecipitation(), 0.0);
}

TEST(SimpleForecastTests, ParameterizedConstructor) {
    SimpleForecast forecast(1234567890, -5.0, 0.0, 5.0, "облачно", 0.0);
    EXPECT_EQ(forecast.getTimestamp(), 1234567890);
    EXPECT_FLOAT_EQ(forecast.getMorningTemp(), -5.0);
    EXPECT_FLOAT_EQ(forecast.getDayTemp(), 0.0);
    EXPECT_FLOAT_EQ(forecast.getEveningTemp(), 5.0);
    EXPECT_EQ(forecast.getWeather(), "облачно");
    EXPECT_FLOAT_EQ(forecast.getPrecipitation(), 0.0);
}

TEST(SimpleForecastTests, AverageTemperature) {
    SimpleForecast forecast(1234567890, 10.0, 15.0, 20.0, "солнечно", 0.0);
    EXPECT_FLOAT_EQ(forecast.getAverageTemp(), 15.0);
}

TEST(SimpleForecastTests, InvalidForecast) {
    SimpleForecast forecast1(1234567890, 10.0, 15.0, 20.0, "солнечно", 5.0);
    EXPECT_TRUE(forecast1.isInvalidForecast());

    SimpleForecast forecast2(1234567890, 10.0, 15.0, 20.0, "снег", 0.0);
    EXPECT_TRUE(forecast2.isInvalidForecast());

    SimpleForecast forecast3(1234567890, -5.0, 0.0, 5.0, "дождь", 10.0);
    EXPECT_FALSE(forecast3.isInvalidForecast());
}
