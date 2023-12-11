#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void PrintVectorPart(std::vector<T>&& numbers) {
	auto ver = std::find_if(numbers.begin(), numbers.end(), [](auto num) { return num < 0; });
	if (ver != numbers.end()) {
		for (auto i = ver; i != numbers.begin(); --i) {
			std::cout << *(rev - 1) << " ";
		}
	}
	else {
		std::reverse(numbers.begin(), numbers.end());
		for (auto num : numbers) {
			std::cout << num << " ";
		}
	}
}

int main() {
	PrintVectorPart<int>({ 6, 1, 8, -5, 4 });  //  1 6 8  здесь обратный порядок или обратная сортировка?
	std::cout << std::endl;
	PrintVectorPart<int>({ -6, 1, 8, -5, 4 });  //  ничего не выведется
	std::cout << std::endl;
	PrintVectorPart<int>({ 6, 1, 8, 5, 4 });  //  4 5 8 1 6
	std::cout << std::endl;
	return 0;
}