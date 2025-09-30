#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "Convert.h"

using namespace std;

Convert::Convert(string fileName, string x6U, string x210) // Передает имя файла
{
    this->fileName = fileName;
    this->x6U = x6U;
    this->x210 = x210;
}

void Convert::vriteFileAll()
{
    ifstream textFileName(fileName);

    while (getline(textFileName, lineN))
    {
        deleteSimvol();

        getTextSwitchCase();
        vriteFile();
    }
}

void Convert::deleteSimvol()
{
    string to_delete{'"'};               // какую подстроку удалить
    size_t start{lineN.find(to_delete)}; // находим позицию подстроки
    while (start != string::npos)        // находим и удаляем все вхождения to_delete
    {
        lineN.erase(start, to_delete.length());
        start = lineN.find(to_delete, start + to_delete.length());
    }
}

void getTextSwitchCase()
{
    int x = 1;
    v1.clear();
    v2.clear();

    bool exitLoop = false;

    for (size_t i = 0; i < lineN.size() && !exitLoop; ++i)
    {
        auto row = lineN[i];
        if (lineN[i] == ',')
        {
            x++;
            continue;
        }

        switch (x)
        {
        case 1:
            v1.push_back({row});
            break;
        case 3:
            v2.push_back({row});
            break;
        case 4:
            exitLoop = true;
            break;
        }
    }
}

void Convert::vriteFile() // Запись в файл
{

    ofstream out;            // поток для записи
    out.open(x6U, ios::app); // открываем файл для записи еще текста

    // 1 строка
    out << "dss.page." << a << ".key." << b << ".Type = 1" << std::endl;

    // 2 строка
    out << "dss.page." << a << ".key." << b << ".Value = ";
    for (string n : v1)
        out << n;
    out << "@-1" << std::endl;

    // 3 строка
    out << "dss.page." << a << ".key." << b << ".Title = ";
    for (string n : v2)
        out << n;
    out << endl;
    b++;
    if (b > 12)
    {
        a++;
        b = 1;
    }
    out.close(); // закрываем файл
}
