#include <iostream>
#include <sstream>
#include "Card.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

void print( vector<Card> const & v ) {
  Card blankCard(0, '0');
	for ( Card i : v ) {
    if (!(i == blankCard)){
      cout << i << ' ';
    }
  }
	cout << endl;
}

int main( int argc, char * argv[] ){
    
vector<Card> deck;
deck.reserve(52);
vector<Player> allPlayers;
allPlayers.reserve(4);
vector<int> allPlayerScores;
vector<Card> spadePile;
spadePile.reserve(13);
vector<Card> heartPile;
heartPile.reserve(13);
vector<Card> clubsPile;
clubsPile.reserve(13);
vector<Card> diamondPile;
diamondPile.reserve(13);
vector<Card> discard;
vector<Card> hand;
hand.reserve(13);
discard.reserve(13);
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
Player player1(hand, discard, 0, 'n', 1);
Player player2(hand, discard, 0, 'n', 2);
Player player3(hand, discard, 0, 'n', 3);
Player player4(hand, discard, 0, 'n', 4);
allPlayers.emplace_back(player1);
allPlayers.emplace_back(player2);
allPlayers.emplace_back(player3);
allPlayers.emplace_back(player4);
//Initializing the Deck
for (int i = 1; i <= 13; i++){
    deck.emplace_back(i, 'C');
}
for (int i = 1; i <= 13; i++){
    deck.emplace_back(i, 'D');
}
for (int i = 1; i <= 13; i++){
    deck.emplace_back(i, 'H');
}
for (int i = 1; i <= 13; i++){
    deck.emplace_back(i, 'S');
}
//Setting Seed
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
if ( argc > 1 ) {
		try {
			seed = stoi( string{ argv[1] } );
		} catch( invalid_argument & e ) {
			cerr << e.what() << endl;
			return 1;
		} catch( out_of_range & e ) {
			cerr << e.what() << endl;
			return -1;
		} // catch
	} // if

	default_random_engine rng{seed};
	//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
	shuffle(deck.begin(), deck.end(), rng);

//Creating Game Object
Game game(allPlayers, allPlayerScores, deck, spadePile, heartPile, clubsPile, diamondPile, seed);
game.invitePlayers();
game.dealDeck();
bool done = false;
  while(!done){
    int firstPlayerIndex = game.firstPlayerId();
    int turn = firstPlayerIndex;
    bool firstTurn = true;
    bool nextRound = false;
    cout << "A new round begins. It's Player" << turn + 1 << "'s turn to play." << endl;
    while (!nextRound){
      game.playerTurnPrint(turn, firstTurn);
      if ((game.getAllPlayers()[turn].getPlayerType() == 'c')){
        if (game.getAllPlayers()[turn].legalPlayExists(game.legalPlays(firstTurn))){
            Player temp(game.getAllPlayers()[turn]);
            Computer computer (temp.getPlayerHand(), temp.getPlayerDiscard(), temp.getScore(), temp.getPlayerType(), temp.getPlayerId());
            Card card1(computer.playFirstLegalCard(game.legalPlays(firstTurn)));
            vector <Card> newPile;
            if (card1.getSuit() == 'S'){
              newPile = game.getSpades();
              newPile[card1.getRank() - 1] = card1;
              game.setSpades(newPile);
            }else if (card1.getSuit() == 'H'){
              newPile = game.getHearts();
              newPile[card1.getRank() - 1] = card1;
              game.setHearts(newPile);
            }else if (card1.getSuit() == 'C'){
              newPile = game.getClubs();
              newPile[card1.getRank() - 1] = card1;
              game.setClubs(newPile);
            }else{
              newPile = game.getDiamonds();
              newPile[card1.getRank() - 1] = card1;
              game.setDiamonds(newPile);
            }
            vector <Player> newAllPlayers = game.getAllPlayers();
            newAllPlayers[turn] = computer;
            game.setAllPlayers(newAllPlayers);
            cout << "Player " << turn + 1 << " plays " << card1 << "." << endl;
        } else {
          Player temp(game.getAllPlayers()[turn]);
          Computer computer (temp.getPlayerHand(), temp.getPlayerDiscard(), temp.getScore(), temp.getPlayerType(), temp.getPlayerId());
          vector <Player> newAllPlayers = game.getAllPlayers();
          Card discard(computer.discardfirCard());
          newAllPlayers[turn] = computer;
          game.setAllPlayers(newAllPlayers);
          cout << "Player " << turn + 1 << " discards " << discard << endl;
        }
      } else{
      string command;
      Card input;
      bool nextPlayer = false;
      if (cin.eof()) { 
        break;
      }
      while(!nextPlayer){
        cin >> command;
        if (cin.eof()) {
          nextRound = true;
          done = true; 
          nextPlayer = true;
          break;
        }
        if (command == "quit"){
          nextPlayer = true;
          done = true;      
        }
        else if(command == "deck"){
          print(game.getDeck());
        }
        else if(command == "play"){
            cin >> input;
            Player temp(game.getAllPlayers()[turn]);
            Human human (temp.getPlayerHand(), temp.getPlayerDiscard(), temp.getScore(), temp.getPlayerType(), temp.getPlayerId());
            Card card1 (human.playCard(game.legalPlays(firstTurn), input));
            Card blankCard (0,'0');
            if (!(card1 == blankCard)){
              if (temp.legalPlayExists(game.legalPlays(firstTurn))) {
                if (card1.getSuit() == 'S'){
                  vector <Card> newSpades = game.getSpades();
                  newSpades[card1.getRank() - 1] = card1;
                  game.setSpades(newSpades);
                } else if(card1.getSuit() == 'H'){
                  vector <Card> newHearts = game.getHearts();
                  newHearts[card1.getRank() - 1] = card1;
                  game.setHearts(newHearts);
                }else if (card1.getSuit() == 'C'){
                  vector <Card> newClubs = game.getClubs();
                  newClubs[card1.getRank() - 1] = card1;
                  game.setClubs(newClubs);
                }else{
                  vector <Card> newDiamonds = game.getDiamonds();
                  newDiamonds[card1.getRank() - 1] = card1;
                  game.setDiamonds(newDiamonds);
                }
                vector <Player> newAllPlayers = game.getAllPlayers();
                newAllPlayers[turn] = human;
                game.setAllPlayers(newAllPlayers);
                cout << "Player " << turn + 1 << " plays " << card1 << "." << endl;
                nextPlayer = true;
              }
            } 
            else{
              cout << "This is not a legal play." << endl;
            }  
        }
        else if (command == "discard"){
          if (game.getAllPlayers()[turn].getPlayerType() == 'h'){
            cin >> input;
            Player temp(game.getAllPlayers()[turn]);
            if (temp.legalPlayExists(game.legalPlays(firstTurn))){
              cout << "You have a legal play. You may not discard." << endl;
            }else{
              Human human (temp.getPlayerHand(), temp.getPlayerDiscard(), temp.getScore(), temp.getPlayerType(), temp.getPlayerId());
              vector<Player> newAllPlayers = game.getAllPlayers();
              newAllPlayers[turn] = human;
              Card card1 (human.discardCard(input));
              Card blankCard(0,'0');
              if(!(card1 == blankCard)){
                newAllPlayers[turn] = human;
                game.setAllPlayers(newAllPlayers);
                cout << "Player " << turn + 1 << " discards " << card1 << endl;
                nextPlayer = true;
              }
            }
          }
        }
        else if(command == "ragequit"){
          Player temp(game.getAllPlayers()[turn]);
          Human human (temp.getPlayerHand(), temp.getPlayerDiscard(), temp.getScore(), temp.getPlayerType(), temp.getPlayerId());
          vector <Player> newAllPlayers = game.getAllPlayers();
          newAllPlayers[turn] = human.rageQuit();
          game.setAllPlayers(newAllPlayers);
          turn--;
          nextPlayer = true;
        }
      }
      }
      if (turn == 3){
        turn = 0;
      }else if(turn == 2){
        turn = 3;
      }else if(turn == 1){
        turn = 2;
      }else if (turn == 0){
        turn = 1;
      }else {
        turn = 0;
      }
      firstTurn = false;
      if(game.allHandEmpty()){
        game.roundOver();
        if (game.above80()){
          int scoreToBeat = game.lowestScore();
          game.printWinners(scoreToBeat);
          done = true;
          break;
        }
        game.newRound();
        nextRound = true;
      }        
    }
  }
}


