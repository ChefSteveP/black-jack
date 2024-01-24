# Casino
Written 11/27/23-11/30/23

A commmand line casino game which supports playing blackjack.

I created this as a casino game and not soley as a blackjack game because I 
structured my classes in a way that can easily accept more games into the system.
Each new game must inherit from the Game class and then can be easily integrated into 
the casino (main) program as another four-line choice statment.

### Compile instructions
A makefile is include so as long as you have `make` installed on your system and GNU Compiler Collection, `gcc`, compliler then you sould be fine. 

#### In windows cmd run
``` 
$ make
$ casino
```
#### In a Linux terminal run
I haven't tested this since I have a windows system. But from my understanding this is the command.

``` 
$ make
$ ./casino
```

I will describe each file in order of its dependency on others (low to high).

## Card & Deck
The card class describes a singular card withing a standard 52-card deck.
It is comprised of:
* A miriade of getter and setters for (suit, rank, value,etc.)
* A toString() method for printing out the qualities of a card in words.

The desk class(no surprise) represents a set of all 52 kinds of cards. 

* A draw() method that returns the top card of the deck and takes it out of selection.

* Shuffle methods of shuffling the deck with the discard or without (blackjack only uses full shuffling).

## Player
This class keeps track of player information and how much money they came in with vs. earned/lost.
* Getters for money and name.

* Mutators for handling winning or losing a bet.

* A function buyIn() for buying back in after running out of money.

* calculateWinnings(): which returns net profit.


## Game
This class is the parent that all implemented games must inherit.

* StartGame(): handles the game loop for the particular game. It returns the player in the new financial state that they earned.
* EndGame(): Calulates the winnings and says farewell to the player in a manner appropriate to how much they won/lost,

## Blackjack
This class contains the game loop and all methods for guiding the player through one/multiple rounds of blackjack. 
* Overrides **StartGame**() and executes game loop appropriate with blackjack.

* **intialDraw()**: handles the intial dealing for both the dealer and player.

* **checkHand**(): gets a running soft total of a hand and prints the contents.

* **hitMe**(): handles the action of requesting another card on top of the initial flop.

* **housePlay**(): follow the rules of engagment for how a casino dealer must act (draw on 16 or under, stay on 17 or over.)

* **evaluate**(): compares hands and determines winner.

* some other helper functions associated with these.

## Casino
This is the main executable for the program. This handles getting user info at the beginning and directs player from game to game (just blackjack for now).


