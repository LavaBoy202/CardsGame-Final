#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <iostream> 
#include <vector>
#include "Card.h"
#include "Player.h"
#include "Computer.h"

class Human : public Player{   
public:
Human(std::vector<Card> playerHand, std::vector<Card> playerDiscard, int playerScore = 0, char playerType = 'h', int PlayerId = 10);
Card playCard(std::vector<Card> legalPlays, Card play);
Card discardCard(Card discard);
Computer rageQuit();
};

#endif

