#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <time.h>

//инициализация строк
using namespace std;

string input_char;						//для ввода сток/символов
int input_int; 							//для вводачисел
string login;							//строка слогином
string password;						//строка с паролем
string save_file = "save_file.txt";		//путь с данными игры
string save_exp_tabl = "exp_file.txt";
//enum настройка
enum keyBoard { STOP = 0, LEFT, RIGHT, UP, DOWN, ENTER, NONE };
keyBoard dir;
enum pos { MAIN, AREA, SHOP, HERO };
pos Mapkey;

time_t sec;
int kolichestvo_dney;

const int width = 48;
const int height = 18;
bool chekEndgame;
int cursor_x, cursor_y;
//Инициализациянастройекигры

class mainhero {
public:
	double level;
	double exp;
	double upexp;
	double power;
	double strength;
	double agility;
	double intellect;
	double health;
	double healthMax;
	double attack;
	double defense;
	double mana;
	double manaMax;

	void match() {
		level = 1;
		exp = 0;
		upexp = 150 + (level + 5) * (5 * level);

		agility = level * 15;
		strength = level * 15;
		intellect = level * 15;

		health = strength * 18;
		healthMax = strength * 18;
		mana = intellect * 15;
		manaMax = intellect * 15;

		power = agility + strength + intellect;

		defense = agility * 0.4 + 1;
		attack = strength * 1.5 + 5;
	}

	void writeparam() {

		cout << endl;
		cout << "# Level: " << level << endl;
		cout << "# Exp: " << exp << "/" << upexp << endl;
		cout << "# Power: " << power << endl << endl;
		cout << "# Strength: " << strength << endl;
		cout << "# Agility: " << agility << endl;
		cout << "# intellect: " << intellect << endl << endl;
		cout << "# Attack: " << attack << endl;
		cout << "# Defense: " << defense << endl;
		cout << "# Health: " << health << "/" << healthMax << endl;
		cout << "# Mana: " << mana << "/" << manaMax << endl;
		cout << endl;
	}
};
mainhero hero;

void setup() {
	chekEndgame = false;
	dir = NONE;
	cursor_x = 2;
	cursor_y = 0;
	hero.match();
}

void Draw() {

	system("cls");
	cout << "DrawVersionv0.2" << endl;
	cout << "Cursor Pos X: " << cursor_x << endl;
	cout << "Cursor Pos Y: " << cursor_y << endl;
	cout << dir << endl << endl;
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1) // Рисует боковые грани поля
			{
				cout << "#";
			}
			if (j == cursor_x && i == cursor_y)
			{
				cout << "\b\b>>";
			}
			if (cursor_y >= 18)
			{
				--cursor_y;
			}
			if (j == 2 && i == 1)
			{
				hero.writeparam();
			}
			cout << " ";
		}
		cout << endl;
	}




	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
}



void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'e':
			dir = ENTER;
			break;
		case'x':
			chekEndgame = true;
			cout << endl << "RealiseX" << endl << endl;
			break;
		}
	}
}

void gamemenu() {
	switch (Mapkey) {
	case MAIN:
		cout << "1. AREA " << endl;
		cout << "2. SHOP " << endl;
		cout << "3. HERO " << endl;
		break;
	case AREA:
	case SHOP:
	case HERO:
		break;
	default:
		cout << "&ERROR: " << endl;
		break;
	}
}

void Logic() {
	switch (dir)
	{
	case LEFT:
		cursor_x -= 1;
		dir = NONE;
		break;
	case RIGHT:
		cursor_x += 1;
		dir = NONE;
		break;
	case UP:
		cursor_y--;
		dir = NONE;
		break;
	case DOWN:
		cursor_y++;
		dir = NONE;
		break;
	case ENTER:
		dir = NONE;
		break;
	case NONE:
		break;
	default:
		break;

	}
}

void ddd() {
	setlocale(LC_ALL, "rus");
	setup();
	while (!chekEndgame)
	{
		Draw();
		Input();
		Logic();
	}
}