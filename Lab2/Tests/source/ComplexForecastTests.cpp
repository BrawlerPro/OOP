#include <WeatherReport/ComplexForecast.h>
#include <gtest/gtest.h>

TEST(ComplexForecastTests, AddForecast) {
    ComplexForecast forecasts;
    SimpleForecast forecast(1234567890, -5.0, 0.0, 5.0, "солнечно", 0.0);
    forecasts.addForecast(forecast);

    EXPECT_EQ(forecasts[0].getTimestamp(), 1234567890);
    EXPECT_FLOAT_EQ(forecasts[0].getMorningTemp(), -5.0);
    EXPECT_FLOAT_EQ(forecasts[0].getDayTemp(), 0.0);
    EXPECT_FLOAT_EQ(forecasts[0].getEveningTemp(), 5.0);
}

TEST(ComplexForecastTests, RemoveForecast) {
    ComplexForecast forecasts;
    SimpleForecast forecast1(1234567890, -5.0, 0.0, 5.0, "солнечно", 0.0);
    SimpleForecast forecast2(2234567890, 0.0, 5.0, 10.0, "облачно", 0.0);
    forecasts.addForecast(forecast1);
    forecasts.addForecast(forecast2);

    forecasts.removeForecast(0);

    EXPECT_EQ(forecasts[0].getTimestamp(), 2234567890);
}

TEST(ComplexForecastTests, FindColdestDay) {
    ComplexForecast forecasts;
    SimpleForecast forecast1(1234567890, -5.0, 0.0, 5.0, "солнечно", 0.0);
    SimpleForecast forecast2(2234567890, -10.0, -5.0, 0.0, "облачно", 0.0);
    forecasts.addForecast(forecast1);
    forecasts.addForecast(forecast2);

    SimpleForecast coldest = forecasts.findColdestDay();
    EXPECT_EQ(coldest.getTimestamp(), 2234567890);
}

TEST(ComplexForecastTests, Resize) {
    ComplexForecast forecasts;
    for (int i = 0; i < 15; ++i) {
        SimpleForecast forecast(1234567890 + i, -5.0, 0.0, 5.0, "солнечно", 0.0);
        forecasts.addForecast(forecast);
    }

    EXPECT_EQ(forecasts[14].getTimestamp(), 1234567890 + 14);
}
