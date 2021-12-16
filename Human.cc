#include <iostream> 
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Computer.h"
#include "Player.h"
#include "Human.h"
using namespace std;


Human::Human(vector<Card> playerHand, vector<Card> playerDiscard, int playerScore, char playerType, int playerId) 
: Player{ playerHand, playerDiscard, playerScore, playerType, playerId} 
{}

Card Human::playCard(std::vector<Card> legalPlays, Card play){
    Card blankCard(0, '0');
    bool found;
    auto it = find(playerHand.begin(), playerHand.end(), play);
    for(int i = 0; i < legalPlays.capacity(); i++){
            if (play == legalPlays[i]){
                found = true;
            }
    }
    if (it == playerHand.end()){
        cout << "It seems like you do not have " << play << "in your hand. You can only play a card that belongs in your hand." << endl;
        return blankCard;
    } 
    else{
        if(found){
            playerHand.erase(it);
            return play;
        }
        else{
            return blankCard;
        }
    }
}

Card Human::discardCard(Card discard){
    Card blankCard(0, '0');
    for(int i = 0; i < playerHand.capacity(); i++){
            if (discard == playerHand[i]){
                int rank;
                char suit;
                suit = playerHand[i].getSuit();
                rank = playerHand[i].getRank();
                playerDiscard.emplace_back(rank, suit);
                playerHand.erase(playerHand.begin() + i);
                return discard;
            }
    }
    cout << "It seems like you do not have " << discard << "in your hand. You can only discard a card that exists in your hand." << endl;
    return blankCard;
}
Computer Human::rageQuit(){
    Computer comp(playerHand, playerDiscard, playerScore, 'c', playerId);
    cout << "Player" << comp.getPlayerId() << " ragequits. A computer will now take over." << endl;
    return comp;
}








