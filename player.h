//! \file       player.h
//! \brief      Player class
//! \author     Stephen Pasch, November 2023

#pragma once
#include <string>

//! \class Player
//! \brief Class describes a singular player at the casino.
class Player {

public:

	//! \brief Default constructor
	Player();

	//! \brief Constructor
	//! \param[in] name,  player name
	//! \param[in] cash, starting money
	Player(std::string name, int cash);

	//! \brief Get player funds
	//! \return player funds
	inline int getFunds() { return liquidity_; }

	//! \brief Get player name
	//! \return player name
	inline std::string getName() { return name_; }

	//! \brief Increase player money due to winning a wager
	inline void addWinnings(int winnings) { liquidity_ += winnings; }

	//! \brief Decrease player money due to losing a wager
	inline void loseBet(int wager) { liquidity_ -= wager; }

	//! \brief Buy in additional money for gambling credit
	//! \param[in] seed, amound of additional money player would like gamble with
	inline void buyIn(int seed) {
		initial_funds_ += seed;
		liquidity_ += seed;
	}

	//! \brief Get player winnings
	//! \return player profit (not includings buy-ins)
	inline int calculateWinnings() { return liquidity_ - initial_funds_; }

protected:
	std::string name_;
	int initial_funds_;
	int liquidity_;
};