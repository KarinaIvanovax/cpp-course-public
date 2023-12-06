#include <iostream>
#include <cassert>
#include <vector>
#include <memory>

#include "file_reader_raii.h"
#include "rectangle.h"


// � ���� ������� �������� ������ ��� �������, � ������� if
// ������� ������ ������� ������ �� heap

template<typename T>
void value_should_be_deleted_in_this_function(T p_value)
{
	assert(p_value);
	if constexpr (std::is_pointer<T>::value) {
		// ��� ����� ������� ���, ���� ��� T - ����� ���������
		delete p_value; 
	}
	else {
		// ��� ����� ������� ���, ���� ��� T - ����� ��������� ���������z
		assert(!p_value);
	}
}

// ������� ������ ������� ��������� shared_ptr, � ������� ���������� ����� ��������� �� ����� 5
// ���������: ��������� ��� �������������� ����������� �������� ������ ��������� � ������� make... �������
std::shared_ptr<int> function_should_return_shared_ptr_to_any_int_5_in_heap()
{
	return std::make_shared<int>(5);
}

struct DeleterString
{
	// �������������� ����������� ����������� ������ ������
};

struct DeleterStringPtr
{
	// �������������� ����������� ����������� ������ ������
};


int main()
{

	// ��������� �������� � ������� ������
	int* ptr = new int{ 20 };
	std::vector<int>* vector_ptr = new std::vector<int>();
	for (int* i = new int{ 0 }; *i < 20; ++(*i)) {
		vector_ptr->push_back(*ptr * *i);
	}
	delete ptr;
	for (int* i = new int{ 0 }; *i < 20; ++(*i)) {
		delete i;
	}
	delete vector_ptr;

	int* ptr_to_vector_value = nullptr;
	if (!vector_ptr->empty()) {
		ptr_to_vector_value = &(*vector_ptr)[0]; 
		std::cout << "dereference [0] element of vector before clean = " << *ptr_to_vector_value << std::endl;
	}
	vector_ptr->clear();
	// ���� ��� �� ������ ����������, �.�. ������� �����
    // ������� ���, ����� ��� �������� �� ������������� ��������
	if (ptr_to_vector_value) {
		std::cout << "dereference [0] element of vector after clean = " << *ptr_to_vector_value << std::endl;
	}
	else {
		std::cout << "clean" << std::endl;
	}

	// ����������� FileRaiiWrapper ��� ���������� FILE* �� ��������� RAII
	FileRaiiWrapper file("test_read.txt");
	assert(file.ReadBytes(10) == "some text");
	std::cout << file.ReadBytes(10) << std::endl;

	// ������� ��������� ����� ����� ���������
	std::unique_ptr<FileRaiiWrapper> fRaiiWrapper = nullptr;
	try {
		fRaiiWrapper = std::make_unique<FileRaiiWrapper>("not_existing_filename.txt");
	}
	catch (CannotOpenFileException) {
		std::cout << "CannotOpenFileException caught" << std::endl;
		assert(!fRaiiWrapper);
	}

	// �������� � ���� test_write.txt ������ `hello text` � �������������� ����� ���������� ��� ��������� ������
    // ��������� ������ ��� � ������ �������� � ���� � ��� ������, ��� ��� ��� ����
	std::vector<std::unique_ptr<FILE, decltype(&std::fclose)>> vector_files;
	FILE* tmpfile = std::fopen("test_write.txt", "w");
	vector_files.emplace_back(tmpfile, &std::fclose);
	std::fputs("hello text", vector_files[0].get());

	// ����� ������ ������� ��������� ������� ������ �� ������������ ������
	int* some_value = new int{ 42 };
	value_should_be_deleted_in_this_function(some_value);

	auto unique_some_value = std::make_shared<int>(42);
	// ������� ���, ����� ������ �������� ������ ������ �������, � �� �������
	value_should_be_deleted_in_this_function<decltype(unique_some_value)>(unique_some_value);

	// ������� ������ ������ ����������� ������� �������� 5, �� ������ ��� ��������� (������ ��� �������� ������� ����������� � �������)
	auto shared_to_5 = function_should_return_shared_ptr_to_any_int_5_in_heap();
	assert(*shared_to_5 == 5);

	// �������������� ������� CalculateRectArea � CalculateRectRelationsOfTheParties, ����� ������ � ��� ����� Rect �� ���� ����������
	int Result = CalculateRectArea(10, 20);
	assert(Result == 200);

	try {
		// some not good code
		double Result2 = CalculateRectRelationsOfTheParties(10, 0);
	}
	catch (std::runtime_error& error) {
		std::cout << "Catched error: " << error.what() << ", this is ok" << std::endl;
		// nothing to do and clear.
		// ��� ��� ����������� ��������� ������ Rect
	}


	// ����������� ����� ����� ����������
	// ����� ������������ ����� DeleterString ��� ������ �� ����� � DeleterStringPtr ��� ������ �� ���� � ������ �������� ��� ��� ������������ ������ ������

		// �� ����� �������� ������ ������� � � cout
	std::string* string_to_cout = new std::string{ "cout this string when delete it" };

	// �� ����� �������� ������ ����� ������� � � cout
	std::string string_to_cout_too{ "also cout this string when delete it" };

	return 0;
}