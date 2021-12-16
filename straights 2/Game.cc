#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include "Card.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Game.h"
using namespace std;

Game::Game (std::vector<Player> allPlayers, std::vector<int> playerScores, std::vector<Card> deck, std::vector<Card> spades, std::vector<Card> hearts, std::vector<Card> clubs, std::vector<Card> diamonds, int seed): allPlayers{allPlayers}, playerScores{playerScores}, deck{deck}, spades{spades}, hearts{hearts}, clubs{clubs}, diamonds{diamonds}, seed{seed}
{}
void Game::invitePlayers(){
    char input;
    cout << "Is Player1 a human (h) or a computer (c)" << endl;
    cin >> input;
   if(input == 'h'){
        allPlayers[0].setPlayerType('h');
    } else{
        allPlayers[0].setPlayerType('c');
    }
    cout << "Is Player2 a human (h) or a computer (c)" << endl;
    cin >> input;
    if(input == 'h'){
        allPlayers[1].setPlayerType('h');
    } else{
        allPlayers[1].setPlayerType('c');
    }
    cout << "Is Player3 a human (h) or a computer (c)" << endl;
    cin >> input;
    if(input == 'h'){
        allPlayers[2].setPlayerType('h');
    } else{
        allPlayers[2].setPlayerType('c');
    }
    cout << "Is Player4 a human (h) or a computer (c)" << endl;
    cin >> input;
    if(input == 'h'){
        allPlayers[3].setPlayerType('h');
    } else{
        allPlayers[3].setPlayerType('c');
    }
}

void Game::dealDeck(){
    vector<Card> hand1;
    hand1.reserve(13);
    vector<Card> hand2;
    hand2.reserve(13);
    vector<Card> hand3;
    hand3.reserve(13);
    vector<Card> hand4;
    hand4.reserve(13);
    for (int i = 0; i < 13; i++){
        hand1.emplace_back(deck[i]);
        //allPlayers[0].playerHand.emplace_back(deck[i]);
    }
    allPlayers[0].setPlayerHand(hand1);
    for (int i = 13; i < 26; i++){
        hand2.emplace_back(deck[i]);
        //allPlayers[1].playerHand.emplace_back(deck[i]);
    }
    allPlayers[1].setPlayerHand(hand2);
    for (int i = 26; i < 39; i++){
        hand3.emplace_back(deck[i]);
        //allPlayers[2].playerHand.emplace_back(deck[i]);
    }
    allPlayers[2].setPlayerHand(hand3);
    for (int i = 39; i < 52; i++){
        hand4.emplace_back(deck[i]);
        //allPlayers[3].playerHand.emplace_back(deck[i]);
    }
    allPlayers[3].setPlayerHand(hand4);
}
void Game::shuffleDeck(){
    //unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};
	shuffle(deck.begin(), deck.end(), rng);
}
int Game::firstPlayerId(){
    bool found = false;
    int id = 0;
    Card spade7(7,'S');
    while (!found){
        for (int i = 0; i <= allPlayers[id].getPlayerHand().capacity() - 1; i++){
            if (allPlayers[id].getPlayerHand()[i] == spade7){
                found = true;
                return id;
            }
        }
        id++;
    }
    return 100;
}
vector<Card> Game::legalPlays(bool firstTurn){
    Card blankCard(0,'0');
    vector<Card> legalPlays;
    int i = 0;
    int minS = 0;
    int maxS = 14;
    int minH = 0;
    int maxH = 14;
    int minC = 0;
    int maxC = 14;
    int minD = 0;
    int maxD = 14;
    if (firstTurn){
        legalPlays.emplace_back(7, 'S');
    }else{
        if (isPileEmpty(spades)){
            legalPlays.emplace_back(7, 'S');
        }else{
            for (int i = 0; i <= spades.capacity() - 1; i++){
                if (!(blankCard == spades[i])){
                    minS = spades[i].getRank();
                    break;
                }
            }
            for (int i = 0; i <= spades.capacity() - 1; i++){
                if(!(blankCard == spades[i]) && blankCard == spades[i+1]){
                    maxS = spades[i].getRank();
                    break;
                }
            }
            if (maxS < 13){
                legalPlays.emplace_back(maxS + 1, 'S');  
            }
            if (minS > 1){
                legalPlays.emplace_back(minS - 1, 'S');
            }
        }
        if (isPileEmpty(hearts)){
            legalPlays.emplace_back(7, 'H');
        }else {
            for (int i = 0; i <= hearts.capacity() - 1; i++){
                if (!(blankCard == hearts[i])){
                    minH = hearts[i].getRank();
                    break;
                }
            }
            for (int i = 0; i <= hearts.capacity() - 1; i++){
                if(!(blankCard == hearts[i]) && blankCard == hearts[i+1]){
                    maxH = hearts[i].getRank();
                    break;
                }
            }
            if (maxH < 13){
                legalPlays.emplace_back(maxH + 1, 'H');
            }
            if (minH > 1){
                legalPlays.emplace_back(minH - 1, 'H');
            }
        }
        if (isPileEmpty(clubs)){
            legalPlays.emplace_back(7, 'C');  
        }else{
            for (int i = 0; i <= clubs.capacity() - 1; i++){
                if (!(blankCard == clubs[i])){
                    minC = clubs[i].getRank();
                    break;
                }
            }
            for (int i = 0; i <= clubs.capacity() - 1; i++){
                if(!(blankCard == clubs[i]) && blankCard == clubs[i+1]){
                    maxC = clubs[i].getRank();
                    break;
                }
            }
            if (maxC < 13){
                legalPlays.emplace_back(maxC + 1, 'C');
            }
            if (minC > 1){
                legalPlays.emplace_back(minC - 1, 'C');
            }
        }
        if (isPileEmpty(diamonds)){
            legalPlays.emplace_back(7, 'D');
        }else{
            for (int i = 0; i <= diamonds.capacity() - 1; i++){
                if (!(blankCard == diamonds[i])){
                    minD = diamonds[i].getRank();
                    break;
                }
            }
            for (int i = 0; i <= diamonds.capacity() - 1; i++){
                if(!(blankCard == diamonds[i]) && blankCard == diamonds[i+1]){
                    maxD = diamonds[i].getRank();
                    break;
                }
            }
            if (maxD < 13){
                legalPlays.emplace_back(maxD + 1, 'D');
            }
            if (minD > 1){
                legalPlays.emplace_back(minD - 1, 'D');
            }
        }
    }
    return legalPlays; 
}
bool Game::isPileEmpty(std::vector<Card> pile){
    Card blankCard(0,'0');
    for(int i = 0; i <= pile.capacity() - 1; i++){
        if(!(pile[i] == blankCard)){
            return false;
        }
    }
    return true;
}
bool Game::allHandEmpty(){
    for (int i = 0; i < allPlayers.capacity(); i++){
        if(!(allPlayers[i].isHandEmpty(allPlayers[i].getPlayerHand()))){
            return false;
        }
    }
    return true;
}
void Game::print(vector<Card> const & v){
  Card blankCard(0, '0');
	for ( Card i : v ) {
    if (!(i == blankCard)){
      cout << i << ' ';
    }
  }
	cout << endl;
}
void Game::roundOver(){
        int player1Score = allPlayers[0].getScore() + calculatePlayerDiscard(allPlayers[0].getPlayerDiscard());
        int player2Score = allPlayers[1].getScore() + calculatePlayerDiscard(allPlayers[1].getPlayerDiscard());
        int player3Score = allPlayers[2].getScore() + calculatePlayerDiscard(allPlayers[2].getPlayerDiscard());
        int player4Score = allPlayers[3].getScore() + calculatePlayerDiscard(allPlayers[3].getPlayerDiscard());
        cout << "Player1's discards: ";
        print(allPlayers[0].getPlayerDiscard());
        cout << "Player1's score: ";
        cout << allPlayers[0].getScore();
        cout << " + ";
        cout << calculatePlayerDiscard(allPlayers[0].getPlayerDiscard());
        cout << endl;
        allPlayers[0].setScore(player1Score);
        //playerScores[0] = allPlayers[0].getScore();
        cout << "Player2's discards: ";
        print(allPlayers[1].getPlayerDiscard());
        cout << "Player2's score: ";
        cout << allPlayers[1].getScore();
        cout << " + ";
        cout << calculatePlayerDiscard(allPlayers[1].getPlayerDiscard());
        cout << endl;
        allPlayers[1].setScore(player2Score);
        //playerScores[1] = allPlayers[1].getScore();
        cout << "Player3's discards: ";
        print(allPlayers[2].getPlayerDiscard());
        cout << "Player3's score: ";
        cout << allPlayers[2].getScore();
        cout << " + ";
        cout << calculatePlayerDiscard(allPlayers[2].getPlayerDiscard());
        cout << endl;
        allPlayers[2].setScore(player3Score);
        //playerScores[2] = allPlayers[2].getScore();
        cout << "Player4's discards: ";
        print(allPlayers[3].getPlayerDiscard());
        cout << "Player4's score: ";
        cout << allPlayers[3].getScore();
        cout << " + ";
        cout << calculatePlayerDiscard(allPlayers[3].getPlayerDiscard());
        cout << endl;
        allPlayers[3].setScore(player4Score);
        //playerScores[3] = allPlayers[3].getScore();
}

int Game::calculatePlayerDiscard(vector<Card> discardCards){
    int score = 0;
    if (!(discardCards.empty())){
        for (int i = 0; i <= discardCards.capacity() - 1; i++){
        score += discardCards[i].getRank();
        }
    }
    return score;
}
bool Game::above80(){
    for (int i = 0; i < allPlayers.capacity(); i++){
        if(allPlayers[i].getScore() >= 80){
            return true;
        }
    }
    return false;
}
int Game::lowestScore(){
    int lowestScore = allPlayers[0].getScore();
    for (int i = 0; i < allPlayers.capacity(); i++){
        if(lowestScore >= allPlayers[i].getScore()){
            lowestScore = allPlayers[i].getScore();
        }
    }
    return lowestScore;
}
void Game::printWinners(int lowestScore){
    if (allPlayers[0].isWinner(lowestScore)){
        cout << "Player1 wins!" << endl;
    }
    if (allPlayers[1].isWinner(lowestScore)){
        cout << "Player2 wins!" << endl;   
    }
    if (allPlayers[2].isWinner(lowestScore)){
        cout << "Player3 wins!" << endl;   
    }
    if (allPlayers[3].isWinner(lowestScore)){
        cout << "Player4 wins!" << endl; 
    }
}
void Game::playerTurnPrint(int turn, bool firstTurn){
    cout << "Cards on the table:" << endl;
    cout << "Clubs: ";
    print(getClubs());
    cout << "Diamonds: ";
    print(getDiamonds());
    cout << "Hearts: ";
    print(getHearts());
    cout << "Spades: ";
    print(getSpades());
    cout << "Your Hand: ";
    print(getAllPlayers()[turn].getPlayerHand());
    cout << "Legal plays: ";
    print(getAllPlayers()[turn].showLegalPlays(legalPlays(firstTurn)));

}
void Game::newRound(){
        vector<Card> spadePile;
        spadePile.reserve(13);
        vector<Card> heartPile;
        heartPile.reserve(13);
        vector<Card> clubsPile;
        clubsPile.reserve(13);
        vector<Card> diamondPile;
        diamondPile.reserve(13);
        for (int i = 0; i <= spadePile.capacity() - 1; i++){
          spadePile.emplace_back(0, '0');
        }
        for (int i = 0; i <= heartPile.capacity() - 1; i++){
          heartPile.emplace_back(0, '0');
        }
        for (int i = 0; i <= clubsPile.capacity() - 1; i++){
          clubsPile.emplace_back(0, '0');
        }
        for (int i = 0; i <= diamondPile.capacity() - 1; i++){
          diamondPile.emplace_back(0, '0');
        }
        spades = spadePile;
        hearts = heartPile;
        clubs = clubsPile;
        diamonds = diamondPile;
        vector<Card> emptyDiscard = {};
        emptyDiscard.reserve(13);
        allPlayers[0].setPlayerDiscard(emptyDiscard);
        allPlayers[1].setPlayerDiscard(emptyDiscard);
        allPlayers[2].setPlayerDiscard(emptyDiscard);
        allPlayers[3].setPlayerDiscard(emptyDiscard);
        shuffleDeck();
        dealDeck();
}
vector<Player> Game::getAllPlayers() const{
    return allPlayers;

}
vector<int> Game::getPlayerScores() const{
    return playerScores;

}
vector<Card> Game::getDeck() const{
    return deck;

}
std::vector<Card> Game::getSpades() const{
    return spades;
}
std::vector<Card> Game::getHearts() const{
    return hearts;
}
std::vector<Card> Game::getClubs() const{
    return clubs;
}
std::vector<Card> Game::getDiamonds() const{
    return diamonds;
}
void Game::setSpades(std::vector<Card> Spades){
    spades = Spades;
}
void Game::setHearts(std::vector<Card> Hearts){
    hearts = Hearts;
}
void Game::setClubs(std::vector<Card> Clubs){
    clubs = Clubs;
}
void Game::setDiamonds(std::vector<Card> Diamonds){
    diamonds = Diamonds;
}

void Game::setAllPlayers(std::vector<Player> allNewPlayers){
    allPlayers = allNewPlayers;

}
void Game::setAllPlayerScores(vector<int> allPlayerScores){
    playerScores = allPlayerScores;

}
void Game::setDeck(std::vector<Card> newDeck){
    deck = newDeck;

}



