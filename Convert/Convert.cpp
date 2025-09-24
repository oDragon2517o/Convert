#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "Convert.h"
using namespace std;

class Convert
{

public:
    Convert(string p_fileName, string p_x6U = "x6U.txt", string p_x210 = "x210.txt") // Передает имя файла
    {
        fileName = p_fileName;
        x6U = p_x6U;
        x210 = p_x210;
    }

    // void read() // Читает первую строку файла
    // {
    //     ifstream textFileName(fileName);
    //     getline(textFileName, line);
    // }

    void vriteFileAll()
    {
        ifstream textFileName(fileName);

        while (getline(textFileName, lineN))
        {
            // std::cout << "lineN = \"" << lineN << "\"" << std::endl;
            deleteSimvol();

            getTextSwitchCase();
            // print();
            vriteFile();
        }
    }

private:
    string fileName{};
    // string fileName2 = "hello2.txt";
    string x6U; // Имя файлов x6U x210
    string x210;
    // string line{};
    string lineN{};

    // Векторы символов
    vector<string> v1;
    vector<string> v2;

    int a = 1;     // dss.page.a.key.b.
    int b = 1;     // dss.page.a.key.b.
    void getText() // Парсит номер и имя. Старая версия
    {
        int x = 1;
        v1.clear();
        v2.clear();
        for (auto c : lineN)
        {

            if (c == ',')
            {
                x++;
                continue;
            }
            if (x == 4)
            {
                break;
            }

            if (x == 1)
            {
                v1.push_back({c});
            }
            if (x == 3)
            {
                v2.push_back({c});
            }
            // std::cout << c << std::endl;
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

    void vriteFile() // Запись в файл
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
    void print()
    {
        // std::cout << lineN << std::endl;

        for (string n : v1)
            cout << n << "\t";
        for (string n : v2)
            cout << "dss.page.1.key.2.Title" << n << "\t";
        cout << std::endl;
    }
    void deleteSimvol()
    {
        string text = lineN;
        string to_delete{'"'};               // какую подстроку удалить
        size_t start{lineN.find(to_delete)}; // находим позицию подстроки
        while (start != string::npos)        // находим и удаляем все вхождения to_delete
        {
            lineN.erase(start, to_delete.length());
            start = lineN.find(to_delete, start + to_delete.length());
        }
        // line = lineN;
    }
};
