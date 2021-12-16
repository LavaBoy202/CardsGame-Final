straights: main.o Player.o Computer.o Human.o Game.o Card.o
	g++ main.o Player.o Computer.o Human.o Game.o Card.o -o straights
main.o: main.cc Game.h Human.h Computer.h Player.h Card.h
	g++ -std=c++14 -c main.cc
Card.o: Card.cc Card.h
	g++ -std=c++14 -c Card.cc
Player.o: Player.cc Player.h Card.h
	g++ -std=c++14 -c Player.cc
Computer.o: Computer.cc Computer.h Player.h Card.h
	g++ -std=c++14 -c Computer.cc
Human.o: Human.cc Human.h Player.h Computer.h Card.h
	g++ -std=c++14 -c Human.cc
Game.o: Game.cc Game.h Player.h Computer.h Human.h Card.h
	g++ -std=c++14 -c Game.cc
