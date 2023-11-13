#include "bin_search.hpp"

#include "iostream"

int main()
{
    int arr[] = {1, 2, 4, 4, 6, 7};
    int digit;
    std::cin >> digit;
    int* result = LowerBound(std::begin(arr), std::end(arr), digit);

    if (result != std::end(arr)) {
        std::cout << "Первое большее или равное число: " << *result << std::endl;
    } else {
        std::cout << "Числа больше введенного нет" << std::endl;
    }

    return 0;
    // nullptr - не должны падать, вернуть nullptr
    // ТУТ ЗАГЛУШКА, ЧТОБЫ КОД КОМПИЛИРОВАЛСЯ
    LowerBound(nullptr, nullptr, 0);
    return 0;
}
