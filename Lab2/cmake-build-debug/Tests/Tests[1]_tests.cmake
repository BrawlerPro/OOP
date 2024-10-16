add_test( SimpleForecastTests.DefaultConstructor /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=SimpleForecastTests.DefaultConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( SimpleForecastTests.DefaultConstructor PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SimpleForecastTests.ParameterizedConstructor /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=SimpleForecastTests.ParameterizedConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( SimpleForecastTests.ParameterizedConstructor PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SimpleForecastTests.AverageTemperature /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=SimpleForecastTests.AverageTemperature]==] --gtest_also_run_disabled_tests)
set_tests_properties( SimpleForecastTests.AverageTemperature PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SimpleForecastTests.InvalidForecast /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=SimpleForecastTests.InvalidForecast]==] --gtest_also_run_disabled_tests)
set_tests_properties( SimpleForecastTests.InvalidForecast PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ComplexForecastTests.AddForecast /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=ComplexForecastTests.AddForecast]==] --gtest_also_run_disabled_tests)
set_tests_properties( ComplexForecastTests.AddForecast PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ComplexForecastTests.RemoveForecast /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=ComplexForecastTests.RemoveForecast]==] --gtest_also_run_disabled_tests)
set_tests_properties( ComplexForecastTests.RemoveForecast PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ComplexForecastTests.FindColdestDay /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=ComplexForecastTests.FindColdestDay]==] --gtest_also_run_disabled_tests)
set_tests_properties( ComplexForecastTests.FindColdestDay PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ComplexForecastTests.Resize /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests/Tests [==[--gtest_filter=ComplexForecastTests.Resize]==] --gtest_also_run_disabled_tests)
set_tests_properties( ComplexForecastTests.Resize PROPERTIES WORKING_DIRECTORY /mnt/c/Users/rasul/CLionProjects/OOP/Lab2/cmake-build-debug/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( Tests_TESTS SimpleForecastTests.DefaultConstructor SimpleForecastTests.ParameterizedConstructor SimpleForecastTests.AverageTemperature SimpleForecastTests.InvalidForecast ComplexForecastTests.AddForecast ComplexForecastTests.RemoveForecast ComplexForecastTests.FindColdestDay ComplexForecastTests.Resize)
