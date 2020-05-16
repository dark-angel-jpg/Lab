МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования<br>
<br/><br/>

### Отчёт по лабораторной работе №4<br/> по дисциплине "Программирование"
<br/>

студентки 1 курса группы ПИ-б-о-191(2)
Павловой Татьяны Викторовны
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
## Лабораторная работа №4
Иксики-нолики.<br>
**Цель:**<br>
1. Закрепить навыки работы с перечислениями;<br>
2. Закрепить навыки работы с структурами;<br>
3. Освоить методы составления многофайловых программ.

**Ход работы:**<br>
1. [Файл](https://github.com/dark-angel-jpg/Lab/blob/master/for%20lab%204/iksiki-noliki.cpp), реализующий саму игру "Иксики-нолики" с функциями из вспомогательного файла:
```cpp
#include <iostream>
#include"ikssiki.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    bool again;
    char sign;
    std::cout << "Приветствую, в игре. (раскладка должна быть английская)." << '\n';
    std::cout<< "Введите символ, которым будете играть (x, o):";
    std::cin >> sign;
    Game f = initGame(sign);

    while (true) {
        updateDisplay(f);
            if (f.isUserTurn) userTurn(&f);
            else botTurn(&f);
            if (updateGame(&f) == true) {
                updateDisplay(f);
                break;
            }
    }
    
    switch (f.status)
    {
    case USER_WIN: std::cout << "Pobeda-pobeda vmesto obeda";
        break;
    case BOT_WIN: std::cout << "Vo slavy Omnissii";
        break;
    default: std::cout << "No one";
        break;
    }
}
```
2. [Вспомогательный файл](https://github.com/dark-angel-jpg/Lab/blob/master/for%20lab%204/dop.cpp):
```cpp
#include<iostream>
#include"ikssiki.h"
#include<ctime>

Game initGame(char userChar) {
	srand(time(NULL));
	Game f; 
	for (int i = 0; i < 3; i++) { //очищает поле и заполняет пробелами
		for (int j = 0; j < 3; j++) {
			f.board[i][j] = ' ';
		}
	}
	
	if (userChar == 'o') f.botChar = 'x'; //установка символов пользователя/бота
	else f.botChar = 'o';

	if (rand() % 2 == 0) f.isUserTurn = true; //определение хода пользователя/бота
		else f.isUserTurn = false;
	f.status = PLAY;
	f.userChar = userChar;
	
	return f;
}

void updateDisplay(const Game game) {
	system("cls"); //очищает консоль
	std::cout << "  a  b  c\n"; //отображение игрового поля
	for (int i = 0; i < 3; i++) {
		std::cout << i << " ";
		for (int j = 0; j < 3; j++) {
			std::cout << game.board[i][j] << "| ";
		}
		std::cout << "\n";
	}

}

void botTurn(Game* game) {
	//проверка на пустое поле
	bool empty = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] != ' ') empty = false;
		}
	}
	if (empty) {
		game->board[1][1] = game->botChar;
		return;
	}
	
	//проверка по строчкам
	int kol = 0;
	for (int i = 0; i < 3; i++) {
		kol = 0;
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == game->userChar) {
				kol++;
				if (kol == 2) {
					for (int k = 0; k < 3; k++) {
						if (game->board[i][k] == ' ') {
							game->board[i][k] = game->botChar;
							return;
						}
					}
				}
			}
		}
	}

	//проверка по столбикам
	for (int j = 0; j < 3; j++) {
		kol = 0;
		for (int i = 0; i < 3; i++) {
			if (game->board[i][j] == game->userChar) {
				kol++;
				if (kol == 2) {
					for (int k = 0; k < 3; k++) {
						if (game->board[k][j] == ' ') {
							game->board[k][j] = game->botChar;
							return;
						}
					}
				}
			}
		}
	}
	
	//проверка по главной диагонали
	int diag = 0;
	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) diag++;
		if (diag == 2) {
			for (int k = 0; k < 3; k++) {
				if (game->board[k][k] == ' ') {
					game->board[k][k] = game->botChar;
					return;
				}
			}
		}
	}

	//Проверка по побочной диагонали //board[i][2-i]
	for (int i = 0; i < 3; i++) {
		if (game->board[i][2-i] == game->userChar) diag++;
		if (diag == 2) {
			for (int k = 0; k < 3; k++) {
				if (game->board[k][2 - k] == ' ') {
					game->board[k][2 - k] = game->botChar;
					return;
				}
			}
		}
	}
	
	int randR;
	int randC;
	do {
	 randR = rand() % 3;
	 randC = rand() % 3;
	} while (game->board[randR][randC] != ' ');
	
	game->board[randR][randC] = game->botChar; //рандомный ход бота
}


void userTurn(Game* game) {
	while (true) {
		std::cout << "Введите координаты (x, y):";
		char x; int y;
		std::cin >> x >> y;

		x -= 'a';
		if ((x < 0 || x>2) || (y < 0 || y>2) || game->board[y][x] != ' ') {
			std::cout << "Надругиваюсь ! Некорректный ввод.";
			continue;
		}
		game->board[y][x] = game->userChar;
		break;
	}
}

bool updateGame(Game* game) {
	game->isUserTurn = !game->isUserTurn;
	//проверка на выигрыш 
	int userline[3] = {};
	int usercolum[3] = {};
	int userdiags[2] = {}; 

	int botline[3] = {};
	int botcolum[3] = {};
	int botdiags[2] = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == game->userChar) {
				userline[i]++;
				usercolum[j]++;
				if (i == j) userdiags[0]++;
				if (i == 2 - j) userdiags[1]++;

				if (userline[i] == 3 || usercolum[j] == 3 || userdiags[0] == 3 || userdiags[1] == 3) {
					game->status = USER_WIN;
					return true;
				}
			}
			else if (game->board[i][j] == game->botChar) {
				botline[i]++;
				botcolum[j]++;
				if (i == j) botdiags[0]++;
				if (i == 2 - j) botdiags[1]++;

				if (botline[i] == 3 || botcolum[j] == 3 || botdiags[0] == 3 || botdiags[1] == 3) {
					game->status = BOT_WIN;
					return true;
				}
			}
		}
	}

	//Проверка на ничью
	bool draw = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == ' ') return false; //поиск пустой ячейки
		}
	}
	if (draw) return true;
	return false;
}
```

3. [Заголовочный файл](https://github.com/dark-angel-jpg/Lab/blob/master/for%20lab%204/ikssiki.h), который необходим для связи главного и вспомогательного файла:

```cpp
#pragma once
/* Состояния игры */
enum Status {
    PLAY,            // Игра продолжается
    USER_WIN,        // Игрок победил
    BOT_WIN,         // Бот победил
    NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};
struct Game {
    char board[3][3];  // Игровое поле
    bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
    char userChar;    // Символ которым играет пользователь
    char botChar;     // Символ которым играет бот
    Status status;
};
/**
* Выполняет следующие действия:
*  1. Очищает игровое поле заполняя его пробелами
*  2. Случайным образом определяет чей ход
*  3. Устанавливает символ для Игрока (Задаётся параметром userChar)
*  4. Устанавливает символ для бота
*  5. Возвращает заполненную структуру
*/
Game initGame(char userChar);
/**
* Выполняет следующие действия:
*  1. Очищает экран
*  2. Отображает содержимое игрового поля. Например так (можно по своему):
*        a   b   c
*      -------------
*     0  O | O | X |
*      -------------
*     1    |   |   |
*      -------------
*     2    |   | X |
*      -------------
*/
void updateDisplay(const Game game);
/**
* Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
* Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ. Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
*/
void botTurn(Game* game);
/**
* Функция отвечает за ход игрока. Если игрок вводит не допустимые
* значения, ругнуться и попросить ввести заново
*/
void userTurn(Game* game);
/**
* Функция определяет как изменилось состояние игры после последнего хода.
* Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
* игроку.
* Функция возвращает true, если есть победитель или ничья, иначе false.
*/
bool updateGame(Game* game);
```
**Вывод:** На данной лабораторной работе, я закрепила навыки работы с перечислениями и структурами и освоила методы составления многофайловых систем.
