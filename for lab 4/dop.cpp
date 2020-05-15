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
		if (rand() % 2 == 0) f.isUserTurn = true; //определение хода пользователя/бота
		else f.isUserTurn = false;
	f.status = PLAY;
	f.userChar = userChar;
	
		if (userChar == 'o') f.botChar = 'x'; //установка символов пользователя/бота
		else f.botChar = 'o';
	
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
	
	int kol = 0;
	//проверка по строчкам
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
	
	int diag = 0;
	//проверка по главной диагонали
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
	
	game->board[randR][randC] = game->botChar;//рандомный ход бота
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
	int user_rows[3] = {};
	int user_cols[3] = {};
	int user_diags[2] = {}; // 0 - главная, 1 - побочная

	int bot_rows[3] = {};
	int bot_cols[3] = {};
	int bot_diags[2] = {}; // 0 - главная, 1 - побочная

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == game->userChar) {
				user_rows[i]++;
				user_cols[j]++;
				if (i == j) user_diags[0]++;
				if (i == 2 - j) user_diags[1]++;

				if (user_rows[i] == 3 || user_cols[j] == 3 || user_diags[0] == 3 || user_diags[1] == 3) {
					game->status = USER_WIN;
					return true;
				}
			}
			else if (game->board[i][j] == game->botChar) {
				bot_rows[i]++;
				bot_cols[j]++;
				if (i == j) bot_diags[0]++;
				if (i == 2 - j) bot_diags[1]++;

				if (bot_rows[i] == 3 || bot_cols[j] == 3 || bot_diags[0] == 3 || bot_diags[1] == 3) {
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
			if (game->board[i][j] == ' ') return false;
		}
	}
	if (draw) return true;
	return false;
}
