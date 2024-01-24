//! \file       game.cpp
//! \brief      Game class
//! \author     Stephen Pasch, November 2023

#include "game.h"

//! \brief Begin Gameplay
Player Game::StartGame(Player player) {
	//must be overriden by children
	return player;
}

//! \brief End Gameplay: display winnings and say tailor goodbye to performance
void Game::EndGame(Player player) {
	std::cout << "\n************************************" << std::endl;
	std::cout << "\nThank you for playing with us at Stephen's casino!" << std::endl;

	int result = player.calculateWinnings();

	if (result > 10) {
		std::cout << "\nCongratulations on winning $" << result
			<< "we hope you ~never~ forget this feeling!";
	}
	else if (result > 0) {
		std::cout << "\nYou left with an extra $" << result
			<< ". Not bad, I mean...at least you didn't lose anything." << std::endl;
	}
	else if (result == 0) {
		std::cout << "\nYou broke even. Can't say the same for some of the others..." << std::endl;
	}
	else {
		std::cout << "\nToday you lost $" << -result
			<< ".\n \nBut remember what Thomas Edison once said... \n"
			<< "\"Many of life's failures are people who did not realize \n"
			<< "how close they were to sucess when they gave up.\"" << std::endl;
	}
}
