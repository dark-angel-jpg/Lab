#include <iostream>
#include"ikssiki.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    Game f = initGame('x');

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
    case NOT_WIN: std::cout << "No one";
        break;
    default: std::cout << "Something's wrong";
        break;
    }
}
