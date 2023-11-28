#include <iostream>
#include <cassert>
#include <vector>
#include <memory>

#include "file_reader_raii.h"
#include "rectangle.h"


// в этой функции поменять только две строчки, в условии if
// функция должна удалить объект из heap
template<typename T>
void value_should_be_deleted_in_this_function(T p_value)
{
    assert(p_value);
    if constexpr (std::is_pointer<T>::value) {
        // что нужно сделать тут, если тип T - сырой указатель
    } else {
        // что нужно сделать тут, если тип T - умный указатель указательz
        assert(!p_value);
    }
}

// функция должна вернуть некоторый shared_ptr, в котором обзятально будет указатель на число 5
// подсказка: подумайте над использованием возможности создания умного указателя с помощью make... функции
std::shared_ptr<int> function_should_return_shared_ptr_to_any_int_5_in_heap()
{
    static int value = 5;
    return std::shared_ptr<int>(&value, [](int *){});
}

struct DeleterString
{
    // самостоятельно реализовать недостающие детали класса
};

struct DeleterStringPtr
{
    // самостоятельно реализовать недостающие детали класса
};


int main()
{
// исправить проблемы с утечной памяти
    int* ptr = new int{20};
    std::vector<int>* vector_ptr = new std::vector<int>();
    for (int* i = new int{0}; *i < 20; ++(*i)) {
        vector_ptr->push_back(*ptr * *i);
    }


// убрать проблему чтение элемента, который был удалён в векторе
    int* ptr_to_vector_value = &(*vector_ptr)[0]; // берём указатель на 0 элемент вектора
    if (ptr_to_vector_value) {
        std::cout << "dereference [0] element of vector before clean = " << *ptr_to_vector_value << std::endl;
    }
    vector_ptr->clear();
// этот код не должен вызываться, т.к. элемент удалён
// сделать так, чтобы код проверил на существование элемента
    if (ptr_to_vector_value) {
        std::cout << "dereference [0] element of vector after clean = " << *ptr_to_vector_value << std::endl;
    }


// реализовать FileRaiiWrapper для управления FILE* по парадигме RAII
    assert(FileRaiiWrapper("test_read.txt").ReadBytes(10) == "some text");
    std::cout << FileRaiiWrapper("test_read.txt").ReadBytes(10) << std::endl;


// сделать выделение через умный указатель
    FileRaiiWrapper* fRaiiWrapper = nullptr;
    try {
        fRaiiWrapper = new FileRaiiWrapper("not_existing_filename.txt");
    } catch (CannotOpenFileException) {
        std::cout << "CannotOpenFileException catched" << std::endl;
        assert(!fRaiiWrapper);
    }


// записать в файл test_write.txt данные `hello text` с использованием умных указателей для выделения памяти
// выделение памяти так и должно остаться в куче в тех местах, где оно уже есть
    std::vector<FILE*> vector_files;
    FILE* tmpfile = std::fopen("test_write.txt", "w");
    vector_files.push_back(tmpfile);
    std::fputs(new char[11]{"hello text"}, vector_files[0]); 


// нужно внутри функции правильно удалить объект из динамической памяти
    int* some_value = new int{42};
    value_should_be_deleted_in_this_function(some_value);

    auto unique_some_value = std::make_shared<int>(42);
    // сделать так, чтобы объект удалялся именно внутри функции, а не снаружи
    value_should_be_deleted_in_this_function<decltype(unique_some_value)>(unique_some_value);


// функция должна всегда обязательно вернуть значение 5, но делать это правильно (сейчас это делается слишком небезопасно и неверно)
    auto shared_to_5 = function_should_return_shared_ptr_to_any_int_5_in_heap();
    assert(*shared_to_5 == 5);


// отредактируйте функции CalculateRectArea и CalculateRectRelationsOfTheParties, можно менять и сам класс Rect на ваше усмотрение
    int Result = CalculateRectArea(10, 20);
    assert(Result == 200);

    try {
        // some not good code
        double Result2 = CalculateRectRelationsOfTheParties(10, 0);
    } catch (std::runtime_error& error) {
        std::cout << "Catched error: " << error.what() << ", this is ok" << std::endl;
        // nothing to do and clear.
        // тут нет возможности отчистить память Rect
    }


// используйте опции умных указателей
// можно использовать класс DeleterString для строки на стеке и DeleterStringPtr для строки на куче и менять например его или использовать другие методы

    // во время удаления строки вывести её в cout
    std::string* string_to_cout = new std::string{"cout this string when delete it"};

    // во время удаления строки также вывести её в cout
    std::string string_to_cout_too{"also cout this string when delete it"};

    return 0;
}
