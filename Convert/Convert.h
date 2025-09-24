#pragma once

#include <string>
#include <vector>
#include <fstream>

class Convert
{
private:
    // Приватные переменные
    std::string fileName;
    std::string x6U;
    std::string x210;
    std::string lineN;
    std::vector<std::string> v1;
    std::vector<std::string> v2;
    int a = 1;
    int b = 1;

    // Приватные методы
    void getText();
    void getTextSwitchCase();
    void vriteFile();
    void print();
    void deleteSimvol();

public:
    Convert(string p_fileName, string p_x6U = "x6U.txt", string p_x210 = "x210.txt") // Передает имя файла
    {
    }
    ~Convert();

    void vriteFileAll() {}
};
