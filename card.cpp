//! \file       card.cpp
//! \brief      Card and Deck classes
//! \author     Stephen Pasch, November 2023

#include <random>
#include <algorithm> 
#include <iterator>
#include <iostream>
#include "card.h"



//Card Class
Card::Card(int rank, std::string suit, bool ace_high) :
	rank_{rank},
	suit_{suit},
	ace_high_{ace_high}
{}

std::string Card::toString() {
	std::string ranks[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", 
							"Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	return ranks[Card::getRank() - 1] + " of " + Card::getSuit();
}


//Deck Class

//! \brief Constructor
Deck::Deck(bool ace_high) {
	std::string suits[] = { "spades", "clubs", "diamonds", "hearts" };

	//create deck of 52 cards
	for (int suit = 0; suit < 4; suit++) {
		for (int rank = 1; rank <= 13; rank++) {
			cards_.push_back(Card{rank, suits[suit], ace_high});
		}
	}
}

//! \brief Default constructor
Deck::Deck() {
	std::string suits[] = { "spades", "clubs", "diamonds", "hearts" };

	//create deck of 52 cards
	for (int suit = 0; suit < 4; suit++) {
		for (int rank = 1; rank <= 13; rank++) {
			cards_.push_back(Card{ rank, suits[suit], true });
		}
	}
}

//! \brief Draw Card and add to discard
//! \return card off the top of the deck.
Card Deck::draw() {
	Card drawn = cards_.back();
	cards_.pop_back();

	discard_.push_back(drawn);

	return drawn;
}

//! \brief Shuffle Deck 
void Deck::fullShuffle() {
	for (int i = 0; i < discard_.size(); i++) {
		cards_.push_back(discard_[i]);
	}
	discard_.erase(discard_.begin(),discard_.end());
	
	std::random_device rd;
	std::mt19937 g(rd());

	std::cout << "Shuffling deck..." << std::endl;
	std::shuffle(cards_.begin(), cards_.end(), g);
	std::cout << "Done shuffling deck." << std::endl;

}

//! \brief Shuffle only card in draw pile (not discard)
void Deck::drawShuffle() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards_.begin(), cards_.end(), g);
}
