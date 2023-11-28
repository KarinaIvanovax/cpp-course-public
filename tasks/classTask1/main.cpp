/**
 * @file main.cpp
 * @brief задача написать программу, которая будет обслуживать текстовую key-value базу данных в файле db.txt
 * 
 * Должен компилироваться бинарник db, и откликаться на команды (команды подаются как аргументы при запуске приложения *argv)
 * `INSERT KEY=VALUE` - операция вставки пары в базу данных (если добавляется ключ который уже есть в файле, то он обновляется)
 * `DELETE KEY` - удалить пару из базы данных
 * `FIND KEY` - вывести значение по ключу в базе данных (возврашает сообщение с элементов в консоль `FOUND: VALUE`,
 *              или выдаёт на вывод `NOT FOUND`, если элемента нет в базе данных; после `FOUND: VALUE` или `NOT FOUND` вывести символ конца строки)
 * `PRINT KEYS/VALUES` - вывести значение всех ключей/значений в базе данных (каждое должно заканчиваться символом конца строки '\n' или std::endl)
 * `DROPALL` - удалить всю базу данных (все значения из базы)
 * Любая команда должна заканчиваться на '?' , можно обрабатывать сразу несколько команд
 * 
 * KEY и VALUE - гарантированно не пустые строки (используют символы букв и цифр, не используют знаки и не используют пробелы)
 * Как вы будете хранить в файле данные - на ваше усмотрение. Главное - чтобы пользовательское API не нарушалось.
 * Главное - база данных храниться в файле, но не в памяти и программу запускаем по необходимости.
 * Программа может быть неоптимальна с точки зрения вычислений, главное чтобы правильно выполнялась основная логика команд.
 */

#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>

namespace {
    constexpr char end_command_delimiter{'?'};
}


class FileReader {

};

class FileWriter {

};

class KeyValueDB {

};

class KeyValueManager : public KeyValueDB {

};

class ArgumentsParser {

};

int main(int argc, char** argv)
{
    // auto db = KeyValueManager("db.txt");
    // auto ap = ArgumentsParser(argc, argv);
    
    // // return false if no more commands
    // while(ap.ProcessNextCommand(db)) {}

    return 0;
}
