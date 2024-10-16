# CrosswordSolver

Программа для разгадывания кроссвордов по заданному шаблону.

## Требования

- Компилятор с поддержкой C++20
- CMake версии 3.10 или выше

### Проект CrosswordSolver
Иерархия файлов данного проекта имеет следующий вид: 

    CrosswordSolver/
    |-- CMakeLists.txt
    |-- include/
    |   |-- CrosswordSolver/
    |   |   |-- CrosswordSolver.h
    |-- source/
    |   |-- CrosswordSolver.cpp

Библеотека для решения кроссвордов

### Dialogue

Проект, которые реализовывает прикладную программу, используя библиотеку CrosswordSolver, его структура:

     Dialogue/
     |-- CMakeLists.txt
     |-- source/
     |   |-- main.cpp

### Тестирование

Проект, который реализует программу тестирования библиотеки Locker с помощью сторонней библиотеки Google Test.

    Tests/
    |-- CMakeLists.txt
    |-- source/
    |   |-- test_CrosswordSolver.cpp

В файле test_CrosswordSolver.cpp содержится объявление всех необходимых тестов.
Подробнее про использоване библиотеки google test можно прочитать по [ссылке](https://habr.com/ru/articles/119090/) .

## Сборка и запуск

```bash
mkdir build
cd build
cmake .. // Эта команда сгенерирует make-файлы для каждой цели в нашем проекте внутри папки build. Сам проект при этом лежит на одну папку выше
make Dialogue  // Скомпилирует программу Dialogue
make Tests     // Скомпилирует программу Tests
make Locker    // Скомпилирует библиотеку Locker
```


