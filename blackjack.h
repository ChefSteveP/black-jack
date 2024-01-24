//! \file       blackjack.h
//! \brief      Blackjack Card Game class
//! \author     Stephen Pasch, November 2023

#pragma once
#include "card.h"
#include "game.h"
#include "player.h"


class Blackjack : public Game {
public:

	//! \brief Constructor 
	Blackjack();

	//! \brief Game loop for blackjack
	//! \param[in] player player to use for gambling calulations
	Player StartGame(Player player) override;

	//! \brief flop first two cards into player or house hand
	//! param[in] isPlayer whether or not the user is the player or house
	void initialDraw(bool isPlayer);

	//! \brief print out current hand.
	//! param[in] hand the current set of cards in the hand
	//! param[in] isPlayer whether or not the user is the player or house
	//! \return total value of hand
	int checkHand(std::vector<Card> hand, bool isPlayer);

	//! \brief player/house may choose to flop another card to their hand
	//! param[in] hand the current set of cards in the hand
	//! param[in] isPlayer whether or not the user is the player or house
	void hitMe(std::vector<Card> hand, bool isPlayer);

	//! \brief will hit/hold dependent on house rules
	void housePlay();

	//! \brief evalautes house vs. player and decides winner
	//! return the positive/negative winnings of the player
	int evaluate();

	//! \brief get values for cards in accordance with Blackjack rules (ace high/low)
	//! \param[in] rank the rank of the card
	//! \param[in] ace_high whether or not ace is high or low
	int getValueFromRank(int rank, bool ace_high);

	//! \brief totals up card value in hand
	//! \param[in] hand the users hand of cards
	int sumHand(std::vector<Card> hand);

protected:
	Deck deck_;
	std::vector<Card> player_hand_;
	std::vector<Card> house_hand_;
	bool player_first_ace_ = false;
	bool house_first_ace_ = false;

};
