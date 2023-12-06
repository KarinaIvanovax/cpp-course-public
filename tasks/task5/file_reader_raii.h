#include <cstdio>
#include <exception>
#include <string>

class CannotOpenFileException {
};

class FileRaiiWrapper {
private:
	std::FILE* f; // ��� ����� �������� ����������, ������� �� �����������

public:
	// ���� ���� �� ��������, �������� ��� ��� �� �����, �� ����� ��������� ������ CannotOpenFileException
	FileRaiiWrapper(const std::string& name) {
		// ���������� �������� ����� � ������� ������ ���
		f = std::fopen(name.c_str(), "r");
		if (f == nullptr) {
			throw CannotOpenFileException();

		}
	}

	FileRaiiWrapper(const FileRaiiWrapper&) = delete;
	FileRaiiWrapper& operator = (const FileRaiiWrapper&) = delete;


	// File&& � ������ �� ��������� ������
	// �������� �������� ������������ � ���������� ������� other
		// ����������� �����������
	FileRaiiWrapper(FileRaiiWrapper&& other) noexcept {
		// ���������� ����������� ���
		f = other.f;
		other.f = nullptr;
	}

	// �������� ������������ � ���������� �����������
	FileRaiiWrapper& operator = (FileRaiiWrapper&& other) noexcept {
		// ���������� ����������� ���
		if (this != &other) {
			if (f != nullptr) {
				std::fclose(f);
			}
			f = other.f;
			other.f = nullptr;
		}
		return *this;
	}

	// ��������� ����, �� ������ ���� �� ��������
	~FileRaiiWrapper() noexcept {
		// ���������� �������� ��������� ����� ���
		if (f) std::fclose(f);
	}

	// ������� ��� ������ ������ ������� bytes_count �� �����
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