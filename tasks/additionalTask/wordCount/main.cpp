/**
 * @file main.cpp
 * @brief напишите программу, которая читает из файла текст состоящий из букв и знаков пунктуации (,.').
 * Необходимый текст находится в файле "input.txt".
 * Нужно для каждого предложения вывести не уникальные слова, это те слова, которые встречаются дважды и более раз в одном предложении.
 * Слова следует учитывать без учёта регистра.
 * Слово не должно содержать знаков пунктуации, но может содержать символ "\'", а концом предложения является только символ ".". Внутри предложения может присутствовать ",".
 * Для каждого такого случая вывести в std::cout номер предложения, а после символа : все неуникальные слова рядом с номером через запятую.
 * В конце списка слов вывести '\n', а не запятую.
 *   подсказка: std::cout << "\b \n"; - код для удаления последнего символа и вместо него вывод перехода на новую строку
 * Если в предложении все слова уникальны, то для этого предложения ничего не нужно выводить
 * пример вывода:
0:the\n
1:a\n
2:one,the\n
3:a,the\n
 *
 */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <iterator>


void removePunctuation(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::ispunct), str.end());
}

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Невозможно открыть файл!" << std::endl;
        return 1;
    }

    std::string line;
    int sentenceNumber = -1;

    while (std::getline(inputFile, line)) {
        removePunctuation(line);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        std::istringstream iss(line);
        std::unordered_map<std::string, int> wordCount;

        std::string word;
        while (iss >> word) {
            wordCount[word]++;
        }

        std::vector<std::string> nonUniqueWords;
        for (const auto& pair : wordCount) {
            if (pair.second >= 2) {
                nonUniqueWords.push_back(pair.first);
            }
        }

        if (!nonUniqueWords.empty()) {
            std::cout << ++sentenceNumber << ":";
            std::copy(nonUniqueWords.begin(), nonUniqueWords.end() - 1, std::ostream_iterator<std::string>(std::cout, ","));
            std::cout << nonUniqueWords.back() << '\n';
        } else {
            sentenceNumber++;
        }
    }

    inputFile.close();

    return 0;
}
