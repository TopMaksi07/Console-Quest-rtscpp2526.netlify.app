// game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;


string inventory[5];

bool quest1 = false;
bool quest2 = false;

struct Player
{
    string name;
	int health = 100;
	int gold = 1100;
    int level = 1;
	int xp = 0;
    int max_health = 100;
    int dop_damage = 0;
};

struct Enemy
{
	string name;
	int health = 0;
};

string enemy[3] = { "Волк", "Разбойник", "Дракон" };

Player player;

void levelUp()
{
	player.level++;
	player.max_health += 15;
	player.gold += 5;
	player.xp = 0;
    cout << "\n\tВы повысили свой уровень на " << player.level << ". +15 к максимальному здоровью. +5 золота\n";
}

void addXp(int i)
{
    cout << "\n +" << i << " опыта.\n";
	player.xp += i;
	if (player.xp >= 100)
	{
		levelUp();
	}
}

int damage_max = 10;
int damage_min = 5;
void useitem(int inv_id)
{
    if (inventory[inv_id] == "Яблоко")
    {
        if (player.health < player.max_health)
        {
            if (player.health > player.max_health - 20)
            {
                cout << "+" << (player.max_health - player.health) << " здоровья\n";
                player.health += (player.max_health - player.health);
            }
            else
            {
                cout << "+20 здоровья\n";
                player.health += 20;
            }
            inventory[inv_id] = "";
        }
    }
    if (inventory[inv_id] == "Меч")
    {
        cout << "Вы снарядили Меч. +10 дополнительного урона\n";
        player.dop_damage += 10;
        inventory[inv_id] = "";

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
            cout << "Выберите предмет который вы жедлаета заменить(1-5 выбор ячейки,0 - отмена)\n";
            showInventory();
            int i = 0;
            cin >> i;
            if (i == 0)
            {
                break;
            }
            else
            {
                inventory[i] = item;

            }
        }
    }
}



void goVillage()
{
    int choise4;
    cout << "1. Отдохнуть в деревне\n";
    cout << "2. Купить яблоко(2 золота)\n";
    cout << "3. Взять квест у Старейшины\n";
    cin >> choise4;
    switch (choise4)
    {
    case 1:
    {
        cout << "Ваш выбор: " << choise4 << endl;
        if (player.health < player.max_health)
        {
            if (player.health > (player.max_health - 10))
            {
                cout << "Вы отдохнули в деревне. +" << (player.max_health - player.health) << " здоровья\n";
                player.health += (player.max_health - player.health);
            }
            else
            {
                cout << "Вы отдохнули в деревне. +10 здоровья\n";
                player.health += 10;
            }

        }
        else
        {
            cout << "Ваше здоровье полное!" << endl;
        }
        addXp(10);
        cout << "Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
        
        break;
    }
    case 2:
    {
        if (player.gold >= 2)
        {
            player.gold -= 2;
            addtoinv("Яблоко");
            cout << "Вы купили яблоко. Оно добавлено в инвентарь...\n";
            
        }
        else
        {
            cout << "У вас недостаточно золота!";
        }
        break;
    }
    case 3:
        if (quest1 == false)
        {
            cout << "Старейшина: Победи разбойника...\n";
			quest1 = true;
        }
        if (quest2 == true)
        {
            cout << "К нам в лес прилетел дракон! Победи его!\n";
        }
        else
        {
			cout << "Вы уже взяли квест у Старейшины\n";
        }
        

        break;
    default:
        break;
    }
}

void fightEnemy(string enemy_name)
{
    Enemy wolf;
    Enemy bandit;
    wolf.health = 30;
    bandit.health = 50;

    int choise2 = 0;

    if (enemy_name == "Волк")
    {
        cout << "В лесу на вас напал Волк!\n" << endl << endl;
        cout << "Здоровье Волка: " << wolf.health << "| Ваше здоровье: " << player.health << endl << endl;

        while (player.health > 0 && wolf.health > 0 && choise2 != 2)
        {
            cout << "Ваши действия:\n" << "1.Ударить\n" << "2.Убежать\n" << "3.Инвентарь\n";
            cin >> choise2;
            cout << "Ваш выбор: " << choise2 << endl;

            switch (choise2)
            {
            case 1:
            {
                int i = rand() % damage_max + 1;
                if (i <= damage_min + player.dop_damage)
                {
                    i = damage_min + player.dop_damage;
                }
                wolf.health -= i;
                cout << "Вы ударили Волка. Урон = " << i << endl;
                i = rand() % damage_max + 1;
                if (i <= damage_min)
                {
                    i = damage_min;
                }
                player.health -= i;
                cout << "Волк кусает вас. Урон = " << i << endl;
                choise2 = 0;
                break;
            }
            case 2:
            {
                cout << "Вы убежали. Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
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

            if (player.health > 0 && wolf.health > 0)
            {
                cout << "Здоровье Волка: " << wolf.health << "| Ваше здоровье: " << player.health << endl << endl;
            }
            if (player.health <= 0)
            {
                cout << "Вы проиграли. Ваши характеристики: Здоровье: 0" << ", Золото: " << player.gold << endl << endl;
                system("pause");
                exit(0);
                break;
            }
            if (wolf.health <= 0)
            {
                player.gold += 10;
                cout << "Вы победили Волка! +10 золота\n";
                addXp(20);
                cout << "Вы победили Волка! Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;

                break;
            }

            if (choise2 == 2)
            {
                break;
            }
        }
    }
    if (enemy_name == "Разбойник")
	{
		cout << "В лесу на вас напал Разбойник!\n" << endl << endl;
		cout << "Здоровье Разбойника: " << bandit.health << "| Ваше здоровье: " << player.health << endl << endl;

        while (player.health > 0 && bandit.health > 0 && choise2 != 2)
        {
            cout << "Ваши действия:\n" << "1.Ударить\n" << "2.Убежать\n" << "3.Инвентарь\n";
            cin >> choise2;
            cout << "Ваш выбор: " << choise2 << endl;

            switch (choise2)
            {
            case 1:
            {
                int i = rand() % damage_max + 1;
                if (i <= damage_min + player.dop_damage)
                {
                    i = damage_min + player.dop_damage;
                }
                bandit.health -= i;
                cout << "Вы ударили Разбойника. Урон = " << i << endl;
                i = rand() % damage_max + 1;
                if (i <= damage_min)
                {
                    i = damage_min;
                }
                player.health -= i;
                cout << "Разбойник ударяет вас. Урон = " << i << endl;
                choise2 = 0;
                break;
            }
            case 2:
            {
                cout << "Вы убежали. Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
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

            if (player.health > 0 && bandit.health > 0)
            {
                cout << "Здоровье Разбойника: " << bandit.health << "| Ваше здоровье: " << player.health << endl << endl;
            }
            if (player.health <= 0)
            {
                cout << "Вы проиграли. Ваши характеристики: Здоровье: 0" << ", Золото: " << player.gold << endl << endl;
                system("pause");
                exit(0);
                break;
            }
            if (bandit.health <= 0)
            {
                player.gold += 20;
                cout << "Вы победили Разбойника! +20 золота\n";
                addXp(20);
                cout << "Вы победили Разбойника! Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
                if (quest1 == true)
                {
                    //quest1 = false;
                    cout << "Квест выполнен!\n";
					cout << "+20 золота и Меч.\n";
                    player.gold += 20;
                    addtoinv("Меч");
                    cout << "Вернитесь к Старейшине, чтобы получить второй квест.\n";
                    quest2 = true;
                }
                break;
            }

            if (choise2 == 2)
            {
                break;
            }
        }
	}

    Enemy dragon;
    dragon.health = 300;

    if (enemy_name == "Дракон")
    {
        cout << "ВЫ ВСТРЕТИЛИ ДРАКОНА!\n" << endl << endl;
        cout << "Здоровье Дракона: " << dragon.health << "| Ваше здоровье: " << player.health << endl << endl;

        while (player.health > 0 && dragon.health > 0 && choise2 != 2)
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
                dragon.health -= i;
                cout << "Вы ударили Дракона. Урон = " << i << endl;
                i = rand() % damage_max + 1;
                if (i <= damage_min)
                {
                    i = damage_min;
                }
                player.health -= i;
                cout << "Дракон ударяет вас. Урон = " << i << endl;
                choise2 = 0;
                break;
            }
            case 2:
            {
                cout << "Вы убежали. Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
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

            if (player.health > 0 && dragon.health > 0)
            {
                cout << "Здоровье Дракона: " << dragon.health << "| Ваше здоровье: " << player.health << endl << endl;
            }
            if (player.health <= 0)
            {
                cout << "Вы проиграли. Ваши характеристики: Здоровье: 0" << ", Золото: " << player.gold << endl << endl;
                system("pause");
                exit(0);
                break;
            }
            if (dragon.health <= 0)
            {
                player.gold += 200;
                cout << "Вы победили Дракона! +200 золота\n";
                addXp(200);
                cout << "Вы победили Дракона! Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
                break;
            }

            if (choise2 == 2)
            {
                break;
            }
        }
    }
    

    
}
void goForest()
{
    int i = rand() % 2;
    if (i == 0)
    {
        if (quest2 == true)
        {
            fightEnemy(enemy[2]);
        }
        if(quest1 == true)
        {
            //int r = rand() % 2;
            fightEnemy(enemy[1]);
        }
        if(quest1 != true && quest2 != true)
        {
            fightEnemy(enemy[0]);
        }
            
    }
    else
    {
        player.gold += 5;
        cout << "Вы вошли в лес. +5 золота\n";
        addXp(5);
        cout << "Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp  << endl << endl;
        
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
            cin >> player.name;
            cout << " " << endl;
            cout << "Куда отправимся, " << player.name << "?" << endl;
            cout << "Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Урон(min-max): " << damage_min << "-" << damage_max << endl << endl;

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
                    cout << "Ваши характеристики: Здоровье: " << player.health << ", Золото: " << player.gold << ", Уровень: " << player.level << ", Опыт: " << player.xp << endl << endl;
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
            if (player.name != "")
            {
                cout << "--- Характеристики героя ---" << endl;
                cout << "Имя: " << player.name << endl;
                cout << "Здоровье: " << player.health << endl;
                cout << "Золото: " << player.gold << endl;
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
