//! \file       blackjack.cpp
//! \brief      Blackjack Card Game class
//! \author     Stephen Pasch, November 2023

#include <algorithm>
#include <numeric>
#include "blackjack.h"


//! \brief Constructor 
Blackjack::Blackjack() 
{
	deck_= Deck{};
}

//! \brief Game loop for blackjack
Player Blackjack::StartGame(Player player) {

    std::cout << "\n************************************" << std::endl;
	std::cout << "Welcome to Blackjack!" << std::endl;
    std::cout << "************************************" << std::endl;

	bool play_again = true;

	//keep playing rounds till player quits or goes broke
	while (play_again) {

		std::string choice;
		int wager;
		int buy_in;
		bool invalid_wager = true;

		//shuffle deck for new round
		deck_.fullShuffle();
         
		//if player starts with no money have them buy in.
		if (player.getFunds() == 0) {
			std::cout << "\nYou have no money. Would you like to buy back in? (y/n): ";
			std::cin >> choice;
			if (choice == "y") {
				std::cout << "How much are you spending? (integer values only): ";
				std::cin >> buy_in;
				player.buyIn(buy_in);
			}
			else {
				break;
			}
		}

		//have player make a wager.
		std::cout << "\nYou have $" << player.getFunds() << "." << std::endl;
		while (invalid_wager) {
			std::cout << "How much would you like to wager? (integer values only): $";
			std::cin >> wager;

			if (wager > player.getFunds()) {
				std::cout << "You may only bet as much as you have" << std::endl;
			} else if (wager <= 0) {
                std::cout << "You must bet at least $1" << std::endl;
            }
            else {
                invalid_wager = false;
            }
		}
		
		//first flop for player and dealer
		Blackjack::initialDraw(true);
		Blackjack::initialDraw(false);

		//show dealer first card
		std::cout << "\n[Dealer] First Card: " << house_hand_[0].Card::toString() << std::endl;
		std::cout <<  "[Dealer] Value of Hand(first card): " << house_hand_[0].getValue() << std::endl;

        //show players current hand
		Blackjack::checkHand(player_hand_, true);

        //player hits till they stay or bust
        bool early_bust = false;
		while (choice != "stay" && !early_bust) {

			std::cout << "\nWould you like to hit or stay? (hit/stay): ";
			std::cin >> choice;

            //convert to lower case
			std::transform(choice.begin(), choice.end(), choice.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (choice == "hit") {

				Blackjack::hitMe(player_hand_, true);
                int hand_value = Blackjack::checkHand(player_hand_, true);

				if (hand_value > 21) { // player busts
                    early_bust = true;
				} 
                else if (hand_value == 21) { // player has blackjack
                    choice = "stay";
                }
			}
		}
		
        //Dealer shows hand
        std::cout << "\nDealer reveals second card " << std::endl;
		while (Blackjack::checkHand(house_hand_, false) <= 16 && !early_bust) {
			Blackjack::housePlay();
		}
		
		//compare deal against player
		int result = Blackjack::evaluate();
		if (result < 0) {
			player.loseBet(wager);
		}
		else if (result == 1) {
			player.addWinnings(wager);
		}

		Game::statusUpdate(player);

		if (player.getFunds() > 0) {
			std::cout << "\nWould you like to play another round? (y/n): ";
			std::cin >> choice;
			if (choice == "y") {
				continue;
			}
			else {
				play_again = false;
			}
		}
		else {
			//player has run out of money and can buy more chips
			std::cout << "Would you like to buy back in? (y/n): ";
			std::cin >> choice;
			if (choice == "y") {
				std::cout << "How much are you spending? (integer values only): ";
				std::cin >> buy_in;
				player.buyIn(buy_in);
			}
			else {
				play_again = false;
			}
		}
	}
    return player;
	//Player leaves the table
}

//! \brief flop first two cards into player or house hand
void Blackjack::initialDraw(bool isPlayer) {

    std::vector<Card> hand;
	hand.push_back(deck_.draw());

	hand.push_back(deck_.draw());

	hand[0].setValue(Blackjack::getValueFromRank(hand[0].getRank(), hand[0].getAceHigh()));

	//If either is an ace track as the first recieved
	if (hand[0].getRank() == 1 || hand[1].getRank() == 1) {
		if (isPlayer) { player_first_ace_ = true;}
		else { house_first_ace_ = true;}
	}
	
	//If two aces then set the second to value 1.
	if (hand[0].getRank() == 1 && hand[1].getRank() == 1) {
		hand[1].setAceHigh(false);
	}
    // std::cout << "previous" << hand[1].getValue() << std::endl;
	hand[1].setValue(Blackjack::getValueFromRank(hand[1].getRank(), hand[1].getAceHigh()));

    if (isPlayer) {
        player_hand_ = hand;
    } 
    else {
        house_hand_ = hand;
    }
}

//! \brief print out current hand.
int Blackjack::checkHand(std::vector<Card> hand, bool isPlayer) {

	int sum = Blackjack::sumHand(hand);
    std::string user = isPlayer ? "[Player]" : "[Dealer]";

    std::cout << "\n" << user << " Hand contains: " << std::endl;

    //print out hand and value
	for (Card card : hand)
	{
        std::cout << user << " " << card.Card::toString() << std::endl;
	}

	if (sum < 21) { //under bust
		std::cout << user << " Total Value of Hand: " << sum << std::endl;
	}
	else if (sum == 21){ //blackjack
		std::cout << user << " Blackjack! Total Value of Hand: 21" << std::endl;
	}
	else { //bust
		std::cout << user << " Bust :( Total Value of Hand: " << sum << std::endl;
	}
	return sum;
	
}

//! \brief player/ house may choose to flop another card to their hand
void Blackjack::hitMe(std::vector<Card> hand, bool isPlayer) {

	//get new card and card value
	Card new_card = deck_.draw();

    /////// DEBUG
    // std::cout << "new card is: " << new_card.Card::toString() << std::endl;

	//if ace already present make new card ace low.
	if (isPlayer && player_first_ace_) {
		new_card.setAceHigh(false);
	}
	if (!isPlayer && house_first_ace_) {
		new_card.setAceHigh(false);
	}
	new_card.setValue(Blackjack::getValueFromRank(new_card.getRank(), new_card.getAceHigh()));

	int new_val = new_card.getValue();

	//calculate current sum
	int current_total = Blackjack::sumHand(hand);

	//handle new total that tentitivley busts
	if (current_total + new_val > 21) {
	
		//look for ace to demote
		for (Card card : hand) {
			//demote first ace
			if (card.getValue() == 11) {
				card.setValue(1);
				card.setAceHigh(false);
				new_val = 1;
			}
		}		
	}

	//add card to hand
	hand.push_back(new_card);

    if(isPlayer) {
        player_hand_ = hand;
    }
    else {
        house_hand_ = hand;
    }
}

//! \brief totals up card value in hand
//! \param[in] hand the users hand of cards
int Blackjack::sumHand(std::vector<Card> hand) {
	int sum = 0;
	for (Card card : hand)
	{
		card.Card::toString();
		sum += card.Card::getValue();
	}
	return sum;
}

//! \brief will hit/hold dependent on house rules
void Blackjack::housePlay() {
	
	int current_total = Blackjack::sumHand(house_hand_);

	if (current_total <= 16) {
		std::cout << "\nDealaer must draw" << std::endl;
		Blackjack::hitMe(house_hand_, false);
	}
	else {
		std::cout << "\nDealaer must stand" << std::endl;
	}
}

//! \brief evalautes house vs. player and decides winner
//! return if player wins or not (1 win, 0 tie, -1 loss)
int Blackjack::evaluate() {
	
	int dealer_total = Blackjack::sumHand(house_hand_);
    // std::cout << "\n[Dealer] evaluate: " << dealer_total << std::endl;

	int player_total = Blackjack::sumHand(player_hand_);
    // std::cout << "\n[Player] evaluate: " << player_total << std::endl;

	if (player_total > 21) {
		return -1;
	}
	if (player_total > dealer_total) {
		std::cout << "\nPlayer Wins" << std::endl;
		return 1;
	}
	else if (player_total == dealer_total) {
		std::cout << "\nTie. No payout" << std::endl;
		return 0;
	}
	else {		
		std::cout << "\nPlayer loses" << std::endl;
		return -1;
	}

}

//! \brief Sets values for cards in accordance with Blackjack rules
int Blackjack::getValueFromRank(int rank, bool ace_high) {

	if (rank == 1) {
		return ace_high ? 11 : 1;
	}
	else if (rank > 10) {
		return 10;
	}
	else {
		return rank;
	}
}
