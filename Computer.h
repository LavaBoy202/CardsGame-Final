#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <iostream> 
#include <vector>
#include "Card.h"
#include "Player.h"

class Computer : public Player{   
public:
Computer(std::vector<Card> playerHand, std::vector<Card> playerDiscard, int playerScore = 0, char playerType = 'c', int playerId = 10);
Card playFirstLegalCard(std::vector<Card> legalPlays);
Card discardfirCard();
};

#endif

