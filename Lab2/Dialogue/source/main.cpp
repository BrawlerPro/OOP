#include <WeatherReport/SimpleForecast.h>
#include <WeatherReport/ComplexForecast.h>
#include <iostream>
#include <limits>

/**
 * @brief Функция для ввода данных прогноза от пользователя.
 * @return SimpleForecast Объект прогноза погоды.
 */
SimpleForecast inputForecast() {
    long timestamp;
    float morningTemp, dayTemp, eveningTemp, precipitation;
    std::string weather;

    std::cout << "Введите данные для прогноза:\n";
    std::cout << "Дата (unix timestamp): ";
    std::cin >> timestamp;

    std::cout << "Температура утром (°C): ";
    std::cin >> morningTemp;

    std::cout << "Температура днем (°C): ";
    std::cin >> dayTemp;

    std::cout << "Температура вечером (°C): ";
    std::cin >> eveningTemp;

    std::cout << "Количество осадков (в мм): ";
    std::cin >> precipitation;

    // Выбор погодного явления
    std::cout << "Выберите погодное явление:\n";
    std::cout << "1. Солнечно\n";
    std::cout << "2. Облачно\n";
    std::cout << "3. Дождь\n";
    std::cout << "4. Снег\n";
    std::cout << "5. Ветрено\n";
    std::cout << "6. Туман\n";
    std::cout << "Введите номер: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            weather = "солнечно";
            break;
        case 2:
            weather = "облачно";
            break;
        case 3:
            weather = "дождь";
            break;
        case 4:
            weather = "снег";
            break;
        case 5:
            weather = "ветрено";
            break;
        case 6:
            weather = "туман";
            break;
        default:
            std::cout << "Некорректный выбор, будет установлено значение по умолчанию: солнечно.\n";
            weather = "солнечно";
            break;
    }

    return {timestamp, morningTemp, dayTemp, eveningTemp, weather, precipitation};
}

/**
 * @brief Функция для вывода всех прогнозов.
 * @param forecast Коллекция прогнозов.
 */
void printForecasts(const ComplexForecast& forecast) {
    std::cout << "\nВсе прогнозы:\n";
    std::cout << forecast;
}

/**
 * @brief Основное меню взаимодействия с пользователем.
 */
void menu() {
    ComplexForecast forecastCollection;
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить прогноз\n";
        std::cout << "2. Удалить прогноз\n";
        std::cout << "3. Показать все прогнозы\n";
        std::cout << "4. Найти самый холодный день\n";
        std::cout << "5. Найти ближайший солнечный день\n";
        std::cout << "6. Удалить все ошибочные прогнозы\n";
        std::cout << "7. Сортировка прогнозов по дате\n";
        std::cout << "8. Выйти\n";
        std::cout << "Введите номер команды: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    SimpleForecast newForecast = inputForecast();
                    forecastCollection.addForecast(newForecast);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                std::size_t index;
                std::cout << "Введите индекс прогноза для удаления: ";
                std::cin >> index;
                try {
                    forecastCollection.removeForecast(index);
                    std::cout << "Прогноз успешно удалён.\n";
                } catch (const std::out_of_range& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 3: {
                printForecasts(forecastCollection);
                break;
            }
            case 4: {
                try {
                    SimpleForecast coldest = forecastCollection.findColdestDay();
                    std::cout << "Самый холодный день:\n" << coldest;
                } catch (const std::runtime_error& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                long currentTimestamp;
                std::cout << "Введите текущую дату (unix timestamp): ";
                std::cin >> currentTimestamp;
                try {
                    SimpleForecast sunnyDay = forecastCollection.findNearestSunnyDay(currentTimestamp);
                    std::cout << "Ближайший солнечный день:\n" << sunnyDay;
                } catch (const std::runtime_error& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            }
            case 6: {
                forecastCollection.removeInvalidForecasts();
                std::cout << "Все ошибочные прогнозы удалены.\n";
                break;
            }
            case 7: {
                forecastCollection.sortForecasts();
                std::cout << "Прогнозы отсортированы по дате.\n";
                break;
            }
            case 8:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }

        // Очищаем входной поток в случае неверного ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
