// game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;


string inventory[5];
string player_name;
int player_health = 85;
int player_gold = 10;

int xp = 0;
int player_level = 1;
int max_health = 100;

void levelUp()
{
	player_level++;
	max_health += 15;
	player_gold += 5;
	xp = 0;
    cout << "\n\tВы повысили свой уровень на " << player_level << ". +15 к максимальному здоровью. +5 золота\n";
}

void addXp(int i)
{
	xp += i;
	if (xp >= 100)
	{
		levelUp();
	}
}

int damage_max = 10;
int damage_min = 5;

void addtoinv(string item)
{
    int a = 0;
    for (int i = 0; i < 6; i++)
    {
        if (inventory[i] == "")
        {
            inventory[i] = item;
            break;
        }
        else
        {
            a++;
        }
        if (a == 5)
        {
            cout << "Инвентарь полон\n";
        }
    }
}
void useitem(int inv_id)
{
    if (inventory[inv_id] == "Яблоко")
    {
        if (player_health < 100)
        {
            if (player_health > 80)
            {
                cout << "+" << (100 - player_health) << " здоровья\n";
                player_health += (100 - player_health);
            }
            else
            {
                cout << "+20 здоровья\n";
                player_health += 20;
            }
            inventory[inv_id] = "";
        }
    }
	
}

void showInventory()
{
    cout << "\nВаш инвентарь:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << (i + 1) << ". " << inventory[i] << "\n";
    }
    cout << "6. Выход из инвентаря\n";
    cout << "\nВыберите предмет или действие:\n";
    int choise3;
    cin >> choise3;
    if (choise3 < 6 && choise3 > 0)
    {
        useitem(choise3 - 1);
    }
    else
    {
        cout << "Выход из инвентаря" << endl;
    }
}
void goVillage()
{
    int choise4;
    cout << "1. Отдохнуть в деревне\n";
    cout << "2. Купить яблоко(2 золота)\n";
    cin >> choise4;
    switch (choise4)
    {
    case 1:
    {
        cout << "Ваш выбор: " << choise4 << endl;
        if (player_health < 100)
        {
            if (player_health > 90)
            {
                cout << "Вы отдохнули в деревне. +" << (100 - player_health) << " здоровья\n";
                player_health += (100 - player_health);
            }
            else
            {
                cout << "Вы отдохнули в деревне. +10 здоровья\n";
                player_health += 10;
            }

        }
        else
        {
            cout << "Ваше здоровье полное!" << endl;
        }
        cout << "+10 опыта\n";
        cout << "Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << ", Уровень: " << player_level << ", Опыт: " << xp << endl << endl;
        addXp(10);
        break;
    }
    case 2:
    {
        if (player_gold >= 2)
        {
            player_gold -= 2;
            addtoinv("Яблоко");
            cout << "Вы купили яблоко. Оно добавлено в инвентарь...\n";
            break;
        }
    }
    default:
        break;
    }
}

void fightEnemy()
{
    int wolf_health = 30;

    cout << "В лесу на вас напал Волк!\n" << endl << endl;
    cout << "Здоровье Волка: " << wolf_health << "| Ваше здоровье: " << player_health << endl << endl;

    int choise2 = 0;

    while (player_health > 0 && wolf_health > 0 && choise2 != 2)
    {
        cout << "Ваши действия:\n" << "1.Ударить\n" << "2.Убежать\n" << "3.Инвентарь\n";
        cin >> choise2;
        cout << "Ваш выбор: " << choise2 << endl;

        switch (choise2)
        {
        case 1:
        {
            int i = rand() % damage_max + 1;
            if (i <= damage_min)
            {
                i = damage_min;
            }
            wolf_health -= i;
            cout << "Вы ударили Волка. Урон = " << i << endl;
            i = rand() % damage_max + 1;
            if (i <= damage_min)
            {
				i = damage_min;
            }
            player_health -= i;
            cout << "Волк кусает вас. Урон = " << i << endl;
            choise2 = 0;
            break;
        }
        case 2:
        {
            cout << "Вы убежали. Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << ", Уровень: " << player_level << ", Опыт: " << xp << endl << endl;
            //choise2 = 0;
            break;
        }
        case 3:
        {
            showInventory();
            break;
        }
        default:
            break;
        }

        if (player_health > 0 && wolf_health > 0)
        {
            cout << "Здоровье Волка: " << wolf_health << "| Ваше здоровье: " << player_health << endl << endl;
        }
        if (player_health <= 0)
        {
            cout << "Вы проиграли. Ваши характеристики: Здоровье: 0" << ", Золото: " << player_gold << endl << endl;
            system("pause");
            exit(0);
            break;
        }
        if (wolf_health <= 0)
        {
            player_gold += 10;
            cout << "Вы победили Волка! +10 золота\n";
            cout << "Вы победили Волка! Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << " +20 опыта" << ", Уровень: " << player_level << ", Опыт: " << xp  << endl << endl;
            addXp(20);
            break;
        }

        if (choise2 == 2)
        {
            break;
        }
    }
}
void goForest()
{
    int i = rand() % 2;
    if (i == 0)
    {
        fightEnemy();
    }
    else
    {
        player_gold += 5;
        cout << "Вы вошли в лес. +5 золота\n" << " +5 опыта";
        cout << "Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << ", Уровень: " << player_level << ", Опыт: " << xp  << endl << endl;
        addXp(5);
    }
}

int main()
{
    system("chcp 1251");
    bool gameisrunning = true;

    while (gameisrunning)
    {
        cout << "Меню:\n";
        cout << "1. Начать игру\n";
        cout << "2. Показать характеристики\n";
        cout << "0. Выход\n";
        int choise;
        cin >> choise;
        cout << "Ваш выбор: " << choise << endl;

        switch (choise)
        {
        case 0:
        {
            gameisrunning = false;
            break;
        }
        case 1:
        {
            //cout << "Функция ёще не реализована" << endl;
            
            cout << "Введите имя игрока: ";
            cin >> player_name;
            cout << " " << endl;
            cout << "Добро пожаловать " << player_name << "!" << endl;
            cout << "Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << ", Урон(min-max): " << damage_min << "-" << damage_max << endl << endl;

            while (true) 
            {
                cout << "Вы на развилке дорог.\n";
                cout << "1. Пойти в деревню\n";
				cout << "2. Пойти в лес\n";
                cout << "3. Показать инвентарь\n";
                cout << "4. Показать характеристики\n";
				int choise1;
				cin >> choise1;
				cout << "Ваш выбор: " << choise1 << endl;

                switch (choise1)
                {
                case 1:
                {
                    goVillage();
					break;
                }
                case 2:
                {
                    goForest();
                    break;
                }
                case 3:
                {
                    showInventory();
                    break;
                }
                case 4:
                    cout << "Ваши характеристики: Здоровье: " << player_health << ", Золото: " << player_gold << ", Уровень: " << player_level << ", Опыт: " << xp << endl << endl;
                    break;
                default:
					break;
				}
            }

            system("pause");
            break;
        }
        case 2:
        {
            if (player_name != "")
            {
                cout << "--- Характеристики героя ---" << endl;
                cout << "Имя: " << player_name << endl;
                cout << "Здоровье: " << player_health << endl;
                cout << "Золото: " << player_gold << endl;
            }
            else cout << "Для начала начните игру" << endl;
            system("pause");
            break;
        }
        default:
            break;
        }
    }
    cout << "Выход из игры\n";
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
