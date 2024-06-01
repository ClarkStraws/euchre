#include "Card.h"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;


int main()
{
    Card two_spades = Card();
    assert(two_spades.get_rank() == Card::RANK_TWO);
    assert(two_spades.get_suit() == Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    assert(three_spades.get_rank() == Card::RANK_THREE);
    assert(three_spades.get_suit() == Card::SUIT_SPADES);
    assert(three_spades.get_suit(Card::SUIT_CLUBS) == Card::SUIT_SPADES);

    assert(!three_spades.is_face());
    assert(!three_spades.is_right_bower(Card::SUIT_CLUBS));
    assert(!three_spades.is_left_bower(Card::SUIT_CLUBS));
    assert(!three_spades.is_trump(Card::SUIT_CLUBS));

    assert(!(three_spades < three_spades));
    assert(!(three_spades > three_spades));
    assert(three_spades == three_spades);
    assert(!(three_spades != three_spades));

    assert(Suit_next(Card::SUIT_CLUBS) == Card::SUIT_SPADES);

    cout << three_spades << endl;

    assert(!Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    assert(!Card_less(three_spades, three_spades, three_spades, Card::SUIT_CLUBS));

    ostringstream oss;
    oss << three_spades;
    assert(oss.str() == "Three of Spades");

    cout << "PASS" << endl;

    return 0;
}
