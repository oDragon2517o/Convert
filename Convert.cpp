#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

class Convert
{

public:
    string fileName2 = "hello2.txt";
    string line{};
    string lineN{};

    int a = 1; // dss.page.a.key.b.
    int b = 1; // dss.page.a.key.b.
    // std::string numbers[];
    vector<string> v1;
    vector<string> v2;

    Convert(string p_fileName) // Передает имя файла
    {
        fileName = p_fileName;
    }

    void read() // Читает первую строку файла
    {
        ifstream textFileName(fileName);
        getline(textFileName, line);
    }

    void getText() // Парсит номер и имя
    {
        int x = 1;
        v1.clear();
        v2.clear();
        for (auto c : line)
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

        for (size_t i = 0; i < line.size() && !exitLoop; ++i)
        {
            auto row = line[i];

            switch (x)
            {
                if (line[i] == ',')
                {
                    x++;
                    break;
                }
            case 1:
                v1.push_back({row});
                break;
            case 3:
                v2.push_back({row});
                break;
            case 4:
                exitLoop = true;
                break;
            case ',':
                x++;
                break;
            }
        }
    }

    void vriteFile() // Запись в файл
    {

        ofstream out;                  // поток для записи
        out.open(fileName2, ios::app); // открываем файл для записи еще текста

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
        string to_delete{'"'};              // какую подстроку удалить
        size_t start{text.find(to_delete)}; // находим позицию подстроки
        while (start != string::npos)       // находим и удаляем все вхождения to_delete
        {
            text.erase(start, to_delete.length());
            start = text.find(to_delete, start + to_delete.length());
        }
        line = text;
    }
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
};

int main()
{
    string fileName = "hello.txt";
    Convert convert(fileName = "hello.txt");
    // convert.read();
    // convert.getText();
    convert.vriteFileAll();
    // convert.print();
}