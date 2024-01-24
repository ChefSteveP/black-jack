//! \file       player.cpp
//! \brief      Player class
//! \author     Stephen Pasch, November 2023

#include "player.h"

//! \brief Default constructor
Player::Player() :
	name_{ "Gambler" },
	initial_funds_{ 0 },
	liquidity_{ 0 }
{}

//! \brief Constructor
//! \param[in] name,  player name
//! \param[in] cash, starting money
Player::Player(std::string name, int cash) :
	name_{ name },
	initial_funds_{ cash },
	liquidity_{ cash }
{}