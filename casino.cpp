#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "player.h"
#include "blackjack.h"
#include "game.h"


//main function which runs all games

int main()
{
    int choice;
    int funds;
    std::string name;
    
    std::cout << "\n************************************" << std::endl;
    std::cout << "Welcome to Stephen's Casino!" << std::endl;
    std::cout << "************************************\n" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "How much are you betting with today, "<< name << "? (integer numbers only): $" ;
    std::cin  >> funds;

    while (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter valid funding amount" << std::endl;
        std::cout << "How much are you betting with today, "<< name << "? (integer numbers only): $" ;
        std::cin  >> funds;
    }


    //create player from info
    Player player(name, funds);

    std::cout << "\nWhich game would you like to play?" << std::endl;
    std::cout << "1. Blackjack" << std::endl;
    std::cout << "2. Exit" << std::endl;

    std::cout << "\nGames Coming Soon:" << std::endl;
    std::cout << "* Poker" << std::endl;
    std::cout << "* Roulette" << std::endl;

    std::cout << "\nChoice: ";
    
    std::cin >> choice;

    Game game{};
    //run game of choice
    while (choice != '2')
    {
        if (choice == 1) {
            Blackjack blackjack{};
            player = blackjack.Blackjack::StartGame(player);
            blackjack.EndGame(player);
        }
        else if (choice == 2)
        {
            std::cout << "Thanks for playing! (Please accept me...)" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << "\nWould you like to play another game?" << std::endl;
        std::cout << "1. Blackjack" << std::endl;
        std::cout << "2. Exit" << std::endl;

        std::cout << "Choice: ";
        std::cin >> choice;
    }
    //std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
