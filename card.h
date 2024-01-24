//! \file       card.h
//! \brief      Card and Deck classes
//! \author     Stephen Pasch, November 2023

#pragma once
#include <string>
#include <vector>

//! \class Card
//! \brief Class describes a singular playing card of a standard 52-card deck.
class Card {

public: 

	//! \brief Default constructor
	Card() = default;

	//! \brief Constructor
	//! \param[in] rank,  card rank (ace-king)
	//! \param[in] suit, card suit
	//! \param[in] ace_high, context for ace high/low valuation
	Card(int rank, std::string suit, bool ace_high);

	//! \brief Get card rank
	//! \return card rank
	inline int getRank() { return rank_; }

	//! \brief Get card value
	//! \return card value
	inline int getValue() { return value_; }

	//! \brief Set card value
	inline void setValue(int val) { value_ = val; }

	//! \brief Get card suit
	//! \return card suit
	inline std::string getSuit() { return suit_; }

	//! \brief Get card suit
	//! \return card suit
	inline bool getAceHigh() { return ace_high_; }

	//! \brief Get card suit
	//! \return card suit
	inline void setAceHigh(bool ace_high) { ace_high_ = ace_high; }

	//! \brief Card to string
	//! \return output string decribing the card in english
	std::string toString();

protected:
	int rank_;
	int value_;        //
	std::string suit_; // spade,club,diamond, or heart
	bool ace_high_;    // determines if ace value is high or low for gameplay

};


//! \class Deck
//! \brief Deck class is used during play to refer to a full collection(52 cards, no jokers)
//! of standard 52-card deck.
class Deck {
public:
	//! \brief Constructor
	Deck(bool ace_high);

	//! \brief Default constructor
	Deck();

	//! \brief Draw Card
	//! \return card off the top of the deck.
	Card draw();

	//! \brief Shuffle discard back into deck 
	void fullShuffle();

	//! \brief Shuffle only card in draw pile (not discard)
	void drawShuffle();

	//! \brief Get Deck of Cards
	//! \return Deck
	inline std::vector<Card> getDeck() { return cards_; }
protected:
	std::vector<Card> cards_;
	std::vector<Card> discard_;
};