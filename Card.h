#ifndef __CARD_H__
#define __CARD_H__
#include <iostream> 

class Card {
int rank;
char suit;
public:
Card (int rank = 0, char suit = '0');
int getRank() const;
char getSuit() const;
void setRank(int Rank);
void setSuit(char Suit);
bool operator==(const Card card1);
};
std::istream &operator>>(std::istream &in, Card &car);
std::ostream &operator<<(std::ostream &out, const Card &car);

#endif

