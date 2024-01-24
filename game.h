//! \file       game.h
//! \brief      Game class
//! \author     Stephen Pasch, November 2023

#pragma once
#include <iostream>
#include "player.h"

class Game {

public:
	//! \brief Default Constructor
	explicit Game() = default;

	//! \brief Begin Gameplay: must be overriden by children
	virtual Player StartGame(Player player);

	//! \brief End Gameplay: display winnings and say goodbye
	void EndGame(Player player);

	//! \brief print out current profit to player
	void statusUpdate(Player player) {
		std::cout << "\nCurrent Winnings: $" << player.calculateWinnings() 
				  << "  Current liquidity: $" << player.getFunds() << std::endl;
	}

};
