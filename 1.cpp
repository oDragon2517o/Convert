#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::vector<std::string>> readCSV(const std::string &filename)
{
    std::vector<std::vector<std::string>> table;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return table;
    }

    std::string line;
    std::getline(file, line); // Пропускаем заголовок

    while (std::getline(file, line))
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        if (!row.empty())
        {
            table.push_back(row);
        }
    }
    file.close();
    return table;
}

int main()
{
    std::vector<std::vector<std::string>> table = readCSV("commands.csv");
    bool exitLoop = false;

    // Цикл for для обработки строк таблицы
    for (size_t i = 0; i < table.size() && !exitLoop; ++i)
    {
        const auto &row = table[i];
        if (row.size() < 2)
        {
            std::cerr << "Неверный формат строки\n";
            continue;
        }

        const std::string &command = row[0];

        // switch-case для обработки команды
        switch (command[0])
        {
        case 'm': // move
            if (command == "move")
            {
                std::cout << "Двигаться на " << row[1] << " шагов\n";
            }
            break;
        case 's': // stop
            if (command == "stop")
            {
                std::cout << "Остановить и выйти\n";
                exitLoop = true; // Устанавливаем флаг для выхода
            }
            break;
        case 't': // turn
            if (command == "turn")
            {
                std::cout << "Повернуть на " << row[1] << " градусов\n";
            }
            break;
        default:
            std::cout << "Неизвестная команда: " << command << "\n";
            break;
        }
    }

    return 0;
}