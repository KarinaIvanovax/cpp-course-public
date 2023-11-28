#include <cstdio>
#include <exception>
#include <string>
 
class CannotOpenFileException {
};
 
class FileRaiiWrapper {
private:
    std::FILE* f; // тот самый файловый дескриптор, который мы оборачиваем

public:
    // если файл не открылся, например его нет на диске, то нужно выбросить ошибку CannotOpenFileException
    FileRaiiWrapper(const std::string& name) {
        // реализации открытия файла и выброса ошибки тут
    }

    FileRaiiWrapper(const FileRaiiWrapper&) = delete;
    FileRaiiWrapper& operator = (const FileRaiiWrapper&) = delete;


// File&& — ссылка на временный объект
// забираем владение дескриптором у временного объекта other
    // Конструктор перемещения
    FileRaiiWrapper(FileRaiiWrapper&& other) noexcept {
        // реализация перемещения тут
    }

    // Оператор присваивания с семантикой перемещения
    FileRaiiWrapper& operator = (FileRaiiWrapper&& other) noexcept {
        // реализация перемещения тут
    }

    // Закрываем файл, но только если он валидный
    ~FileRaiiWrapper() noexcept {
        // реализация закрытия валидного файла тут
    }

    // функция для чтения строки длинной bytes_count из файла
    std::string ReadBytes(const size_t bytes_count) const {
        char* buf = new char[bytes_count + 1]{};
        std::ignore = std::fgets(buf, bytes_count, f);
        return buf;
    }
};