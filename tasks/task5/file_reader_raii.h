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
		f = std::fopen(name.c_str(), "r");
		if (f == nullptr) {
			throw CannotOpenFileException();

		}
	}

	FileRaiiWrapper(const FileRaiiWrapper&) = delete;
	FileRaiiWrapper& operator = (const FileRaiiWrapper&) = delete;


	// File&& — ссылка на временный объект
	// забираем владение дескриптором у временного объекта other
		// Конструктор перемещения
	FileRaiiWrapper(FileRaiiWrapper&& other) noexcept {
		// реализация перемещения тут
		f = other.f;
		other.f = nullptr;
	}

	// Оператор присваивания с семантикой перемещения
	FileRaiiWrapper& operator = (FileRaiiWrapper&& other) noexcept {
		// реализация перемещения тут
		if (this != &other) {
			if (f != nullptr) {
				std::fclose(f);
			}
			f = other.f;
			other.f = nullptr;
		}
		return *this;
	}

	// Закрываем файл, но только если он валидный
	~FileRaiiWrapper() noexcept {
		// реализация закрытия валидного файла тут
		if (f) std::fclose(f);
	}

	// функция для чтения строки длинной bytes_count из файла
	std::string ReadBytes(const size_t bytes_count) const {
		if (!f) {
			throw std::runtime_error("not open");
		}
		std::unique_ptr<char[]> buf(new char[bytes_count + 1]{});
		char* result = std::fgets(buf.get(), static_cast<int>(bytes_count + 1), f);
		if (!result) {
			throw std::runtime_error("can't read");
		}
		return buf.get();
	}
};