// Tag.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>

using std::vector;
using std::cout;

const unsigned short SIZE = 4; // размер игрового поля

vector<int> in_game_map(SIZE);
vector<vector<int>> game_map(SIZE, in_game_map); // игровая карта

vector<int> in_right_map(SIZE);
vector<vector<int>> right_map(SIZE, in_right_map); // правильная итоговая карта

struct coordinate // хранилище координат нулевого элемента
{
    unsigned x;
    unsigned y;
} zero; // объект

void create_right_map() // создаем правильную карту заполненую по порядку
{
    unsigned right_value = 1;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
            right_map[i][j] = right_value++;
    }
    right_map[SIZE - 1][SIZE - 1] = 0; // нулевой элемент в нижний правый угол
}

void create_game_map() // рандомно создаем игровую карту
{
    unsigned limit = SIZE * SIZE;
    vector<int> temporary; // временный массив из которого будем брать значения в игровую карту
    for (unsigned i = 0; i < limit; i++)
        temporary.push_back(i);

    int value;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            value = rand() % limit--;
            game_map[i][j] = temporary[value];
            if (temporary[value] == 0) // сохраняем координаты нулевого элемента
            {
                zero.x = j;
                zero.y = i;
            }
            temporary.erase(temporary.begin() + value);
        }
    }
}

bool check_map() // сравнение игровой и правильной карты для определения конца игры
{
    if (game_map == right_map)
        return true;
    return false;
}

void up_move() // ход вверх (нулевой элемент вниз)
{
    if (zero.y < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
        zero.y++;
        game_map[zero.y][zero.x] = 0;
    }
}

void down_move() // ход вниз (нулевой элемент вверх)
{
    if (zero.y > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
        zero.y--;
        game_map[zero.y][zero.x] = 0;
    }
}

void right_move() // ход вправо (нулевой элемент влево)
{
    if (zero.x > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
        zero.x--;
        game_map[zero.y][zero.x] = 0;
    }
}

void left_move() // ход влево (нулевой элемент вправо)
{
    if (zero.x < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
        zero.x++;
        game_map[zero.y][zero.x] = 0;
    }
}

void get_direction() // определяем нажатую игроком стрелку
{
    int move = static_cast<int> (_getch()); // UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
    switch (move)
    {
    case 72:
    {
        up_move(); break;
    }
    case 80:
    {
        down_move(); break;
    }
    case 77:
    {
        right_move(); break;
    }
    case 75:
    {
        left_move(); break;
    }
    default:
    {
        get_direction();
    }
    }
}
void screen() // выводим массив на экран
{
    system("cls");
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (game_map[i][j] != 0)
                cout << std::setw(2) << std::setfill('0') << game_map[i][j] << ' ';
            else
                cout << "** "; // нулевой элемент
        }
        cout << '\n';
    }
}

int main()
{
    setlocale(0, "");

    system("Color B5");

    srand(static_cast<int>(time(NULL)));

    create_right_map(); //создание игровых карт
    do
    {
        create_game_map();
    } while (check_map());

    do
    {
        screen();
        get_direction();
    } while (!check_map());

    cout << "\nТы выйграл!\nТы проиграл!\n";
    _getch();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
