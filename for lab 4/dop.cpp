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
