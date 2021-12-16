#include <iostream> 
#include <sstream>
#include <string>
#include <vector>
#include "Player.h"
#include "Card.h"
using namespace std;


Player::Player(vector<Card> playerHand, vector<Card> playerDiscard, int playerScore, char playerType, int playerId) 
: playerHand{playerHand}, playerDiscard {playerDiscard}, playerScore{playerScore}, playerType{playerType}, playerId{playerId} 
{}

int Player::getScore() const {
    return playerScore;
}
void Player::setScore(int score){
    playerScore = score;
}
char Player::getPlayerType() const {
    return playerType;
}
void Player::setPlayerType(char type){
    playerType = type;
}
int Player::getPlayerId() const{
    return playerId;
}
void Player::setPlayerId(int id){
    playerId = id;
}
vector<Card> Player::getPlayerHand() const {
    return playerHand;

}
vector<Card> Player::getPlayerDiscard() const {
    return playerDiscard;  
}
void Player::setPlayerHand(vector<Card> Hand) {
    playerHand = Hand;
}
void Player::setPlayerDiscard(vector<Card> Discard) {
    playerDiscard = Discard;
}

bool Player::isHandEmpty(vector<Card> cardHand){
    if (cardHand.size() == 0){
        return true;
    }
    return false;
}
bool Player::isWinner(int scoreToBeat){
    if (playerScore <= scoreToBeat){
        return true;
    }
    return false;
}
bool Player::legalPlayExists(std::vector<Card> allLegalPlays){
    for (int i = 0; i <= allLegalPlays.capacity() - 1; i++){
        for(int j = 0; j <= playerHand.capacity() - 1; j++){
            if (playerHand[j] == allLegalPlays[i]){
                return true;
            }
        }
    }
    return false;
}

vector<Card> Player::showLegalPlays(std::vector<Card> allLegalPlays){
    vector<Card> legal;
    for (int j = 0; j <= playerHand.capacity() - 1; j++){
        for(int i = 0; i <= allLegalPlays.capacity() - 1; i++){
            if (playerHand[j] == allLegalPlays[i]){
                legal.emplace_back(playerHand[j]);
            }
        }
    }
    return legal;
}
int Player::calcScoreFromDiscard(){
    int score = 0;
    if (!(playerDiscard.empty())){
        for (int i = 0; i <= playerDiscard.capacity() - 1; i++){
        score += playerDiscard[i].getRank();
        }
    }
    return score;
}

