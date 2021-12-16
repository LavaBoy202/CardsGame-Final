#include <iostream> 
#include <sstream>
#include <string>
#include "Card.h"

Card::Card(int ranks, char suits) { 
rank = ranks;
suit = suits;
}
int Card::getRank() const{
    return rank;
}
char Card::getSuit() const{
    return suit;
}
void Card::setRank(int Rank){
    rank = Rank;
}
void Card::setSuit(char Suit){
    suit = Suit;
}

bool Card::operator==(const Card card1){
    return ((card1.getSuit() == suit) && (card1.getRank() == rank));
}

std::istream &operator>>(std::istream &in, Card &car){
    char rank;
    char discard;
    char suit;
    in >> rank;
    if (rank == 'K'){
        car.setRank(13);
    }else if (rank == 'Q'){
        car.setRank(12);
    }else if (rank == 'J'){
        car.setRank(11);
    }else if (rank == 'A'){
        car.setRank(1);
    }else if (rank == '2'){
        car.setRank(2);
    }else if (rank == '3'){
        car.setRank(3);
    }else if (rank == '4'){
        car.setRank(4);
    }else if (rank == '5'){
        car.setRank(5);
    }else if (rank == '6'){
        car.setRank(6);
    }else if (rank == '7'){
        car.setRank(7);
    }else if (rank == '8'){
        car.setRank(8);
    }else if (rank == '9'){
        car.setRank(9);
    }else if (rank == 'T'){
        car.setRank(10);
    }
    in >> suit;
    car.setSuit(suit);
    return in;
}
std::ostream &operator<<(std::ostream &out, const Card &car){
    if(car.getRank() == 0 && car.getSuit() == '0'){
        return out;
    }
    if (car.getRank() == 13){
        out << 'K';
    }else if(car.getRank() == 12){
        out << 'Q';

    }else if (car.getRank() == 11){
        out << 'J';
    }else if (car.getRank() == 1){
        out << 'A';
    }else if(car.getRank() == 10){
        out << 'T';

    }else {
        out << car.getRank();
    }
    out << car.getSuit();

    return out;
}

