#include <iostream> 
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Computer.h"
using namespace std;


Computer::Computer(vector<Card> playerHand, vector<Card> playerDiscard, int playerScore, char playerType, int playerId) 
: Player{ playerHand, playerDiscard, playerScore, playerType, playerId} 
{}

Card Computer::playFirstLegalCard(std::vector<Card> legalPlays){
    Card blankCard(0, '0');
    for(int j = 0; j <= playerHand.capacity() - 1; j++){
        for (int i = 0; i <= legalPlays.capacity() - 1; i++){
            if (legalPlays[i] == playerHand[j]){
                Card found(playerHand[j]);
                auto it = find(playerHand.begin(), playerHand.end(), found);
                if (it == playerHand.end()){
                    cout << "Not Found";
                    return blankCard;
                } 
                else{
                    playerHand.erase(it);
                }
                
                return legalPlays[i];
            }
        }
    }  
}

Card Computer::discardfirCard(){
    Card discard(playerHand[0]);
    int rank;
    char suit;
    suit = playerHand[0].getSuit();
    rank = playerHand[0].getRank();
    playerHand.erase(playerHand.begin());
    /*auto it = find(playerHand.begin(), playerHand.end(), playerHand[0]);
    if (it == playerHand.end()){
        cout << "Not Found";
    } 
    else{
        playerHand.erase(it);
    }*/
    playerDiscard.emplace_back(rank, suit);
    return discard;
}





