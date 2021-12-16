#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream> 
#include <vector>
#include "Card.h"


class Player {
    protected:
    int playerScore;
    std::vector<Card> playerHand;
    std::vector<Card> playerDiscard;
    char playerType;
    int playerId;
public:  
Player (std::vector<Card> playerHand, std::vector<Card> playerDiscard, int playerScore = 0, char playerType = 'n', int playerId = 10);
int getScore() const;
void setScore(int score);
int getPlayerId() const;
void setPlayerId(int id);
char getPlayerType() const;
void setPlayerType(char type);
std::vector<Card> getPlayerHand() const;
std::vector<Card> getPlayerDiscard() const;
void setPlayerHand(std::vector<Card> Hand);
void setPlayerDiscard(std::vector<Card> Discard);
bool isHandEmpty(std::vector<Card>);
bool isWinner(int scoreToBeat);
bool legalPlayExists(std::vector<Card> allLegalPlays);
std::vector<Card> showLegalPlays(std::vector<Card> allLegalPlays);
int calcScoreFromDiscard();
};

#endif

