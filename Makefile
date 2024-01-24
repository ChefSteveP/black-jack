casino: blackjack.o card.o casino.o game.o player.o 
	g++ blackjack.o card.o casino.o game.o player.o -o casino

blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp

card.o: card.cpp
	g++ -c card.cpp

casino.o: casino.cpp
	g++ -c casino.cpp

game.o: game.cpp
	g++ -c game.cpp

player.o: player.cpp
	g++ -c player.cpp

clean:
	-del *.o casino
