#ifndef __GAME_H__
#define __GAME_H__
#include <iostream> 
#include <vector>
#include "Card.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

class Game {
    std::vector<Player> allPlayers;
    std::vector <int> playerScores;
    std::vector<Card> deck;
    std::vector<Card> spades;  
    std::vector<Card> hearts; 
    std::vector<Card> clubs; 
    std::vector<Card> diamonds; 
    int seed;
public:
Game (std::vector<Player> allPlayers, std::vector<int> playerScores, std::vector<Card> deck, std::vector<Card> spades,std::vector<Card> hearts, std::vector<Card> clubs,std::vector<Card> diamonds, int seed);
void invitePlayers();
void dealDeck();
void shuffleDeck();
int firstPlayerId();
std::vector<Card> legalPlays(bool firstTurn);
bool isPileEmpty(std::vector <Card> pile);
bool allHandEmpty();
void roundOver();
bool above80();
int lowestScore();
void printWinners(int lowestScore);
void playerTurnPrint(int turn, bool firstTurn);
void newRound();
void print(std::vector<Card> const & v);
int calculatePlayerDiscard(std::vector<Card> discardCards);
std::vector<Player> getAllPlayers() const;
std::vector<int> getPlayerScores() const;
std::vector<Card> getDeck() const;
std::vector<Card> getSpades() const;
std::vector<Card> getHearts() const;
std::vector<Card> getClubs() const;
std::vector<Card> getDiamonds() const;
void setSpades(std::vector<Card> spades);
void setHearts(std::vector<Card> hearts);
void setClubs(std::vector<Card> clubs);
void setDiamonds(std::vector<Card> diamonds);
void setAllPlayers(std::vector<Player> allNewPlayers);
void setAllPlayerScores(std::vector<int> allPlayerScores);
void setDeck(std::vector<Card> newDeck);
};

#endif

