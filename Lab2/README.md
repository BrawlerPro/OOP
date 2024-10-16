# Lab2: Weather Forecast Application

## Описание проекта

Этот проект представляет собой приложение для прогноза погоды. Оно включает два класса:
- **SimpleForecast**: Представляет собой суточный прогноз с данными о температуре, погодном явлении и осадках.
- **ComplexForecast**: Управляет коллекцией объектов **SimpleForecast**, обеспечивая функциональность для добавления, удаления, поиска и сортировки прогнозов.

### Структура проекта
Иерархия файлов данного проекта имеет следующий вид:

    Lab2/
    |-- CMakeLists.txt
    |-- Lab2_struct.txt
    |-- Dialogue/
    |   |-- source/
    |   |   |-- main.cpp
    |-- Tests/
    |   |-- source/
    |   |   |-- ComplexForecastTests.cpp
    |   |   |-- SimpleForecastTests.cpp
    |-- WeatherReport/
    |   |-- include/
    |   |   |-- ComplexForecast/
    |   |   |   |-- ComplexForecast.h
    |   |   |-- SimpleForecast/
    |   |   |   |-- SimpleForecast.h
    |   |-- source/
    |   |   |-- ComplexForecast.cpp
    |   |   |-- SimpleForecast.cpp

### Библеотека WeatherReport
Иерархия файлов данного проекта имеет следующий вид:

    WeatherReport/
    |-- CMakeLists.txt
    |-- include/
    |   |-- WeatherReport/
    |   |   |-- SimpleForecast.h
    |   |   |-- ComplexForecast.h
    |-- source/
    |   |-- SimpleForecast.h
    |   |-- ComplexForecast.h

Библеотека для прогнозов погоды

### Dialogue

Проект, которые реализовывает прикладную программу, используя библиотеку WeatherReport, его структура:

     Dialogue/
     |-- CMakeLists.txt
     |-- source/
     |   |-- main.cpp

### Тестирование

Проект, который реализует программу тестирования библиотеки WeatherReport с помощью сторонней библиотеки Google Test.

    Tests/
    |-- CMakeLists.txt
    |-- source/
    |   |-- ComplexForecastTests.cpp
    |   |-- SimpleForecastTests.cpp

## Сборка и запуск

```bash
mkdir build
cd build
cmake .. // Эта команда сгенерирует make-файлы для каждой цели в нашем проекте внутри папки build. Сам проект при этом лежит на одну папку выше
make Dialogue  // Скомпилирует программу Dialogue
make Tests     // Скомпилирует программу Tests
make CrosswordSolver    // Скомпилирует библиотеку WeatherReport
```



