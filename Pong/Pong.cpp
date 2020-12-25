// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "GameSinglePlayer.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        char numPlayers;
        std::cout << "Enter Number of Players (1 or 2): ";
        std::cin >> numPlayers;
        std::cout << std::endl;
        
        while (numPlayers != '1' && numPlayers != '2') {
            std::cout << "Enter Number of Players (1 or 2): ";
            std::cin >> numPlayers;
            std::cout << std::endl;
        }

        if (numPlayers == '1') {
            GameSinglePlayer gameOnePlayer;

            while (gameOnePlayer.running()) {

                gameOnePlayer.update();

                gameOnePlayer.render();
            }
        }

        else if (numPlayers == '2') {
            Game gameTwoPlayer;

            while (gameTwoPlayer.running()) {

                gameTwoPlayer.update();

                gameTwoPlayer.render();
            }
        }
        std::cout << "Play Again? (Y/N) ";
        std::cin >> playAgain;
        std::cout << std::endl;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
