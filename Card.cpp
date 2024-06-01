#include "Card.h"
#include <cassert>

using namespace std;
Card::Card(const string &rank_in, const string &suit_in) {
    assert(rank_in == RANK_TWO || rank_in == RANK_THREE || rank_in == RANK_FOUR ||
           rank_in == RANK_FIVE || rank_in == RANK_SIX || rank_in == RANK_SEVEN ||
           rank_in == RANK_EIGHT || rank_in == RANK_NINE || rank_in == RANK_TEN ||
           rank_in == RANK_JACK || rank_in == RANK_QUEEN || rank_in == RANK_KING ||
           rank_in == RANK_ACE);
    assert(suit_in == SUIT_SPADES || suit_in == SUIT_HEARTS ||
           suit_in == SUIT_CLUBS || suit_in == SUIT_DIAMONDS);
    rank = rank_in;
    suit = suit_in;
}
// default card is Two of Spades
Card::Card(): Card(RANK_TWO, SUIT_SPADES)
{}

string Card::get_rank() const {
    return rank;
}

string Card::get_suit() const {
    return suit;
}

string Card::get_suit(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS ||
           trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    // if the card is the left bower, it is still trump, so return its suit as
    // trump
    if (is_left_bower(trump)) {
        return trump;
    }
    // all other cards should just have their own suit as the returned suit
    return suit;
}

bool Card::is_face() const {
    // if rank is Jack, King, Queen, or Ace, it is a face card
    return (rank == RANK_JACK || rank == RANK_QUEEN ||
            rank == RANK_KING || rank == RANK_ACE);
}

bool Card::is_right_bower(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS ||
        trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    // Jack of trump suit is right bower
    return ((suit == trump) && (rank == RANK_JACK));
}
bool Card::is_left_bower(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS ||
           trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    // Jack of same colored suit as trump is left bower
    return (rank == RANK_JACK && suit == Suit_next(trump));
}

bool Card::is_trump(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS ||
           trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    // if the suit is trump, or it's the left bower, it's a trump card
    return ((trump == suit) || (is_left_bower(trump)));
}

bool operator<(const Card &lhs, const Card &rhs) {
    int left = 0, right = 0;
    // find which rank the left and right cards are
    while (RANK_NAMES_BY_WEIGHT[left] != lhs.get_rank()) {
        left++;
    }
    while (RANK_NAMES_BY_WEIGHT[right] != rhs.get_rank()) {
        right++;
    }
    // if they are not the same rank, we are done; the lowest card is whichever
    // is the lowest rank
    if (left != right) {
        return left < right;
    }
    // if they are the same rank, find which suit is highest according to the
    // specification Diamonds > Clubs > Hearts > Spades
    else {
        left = 0;
        right = 0;
        int left = 0, right = 0;
        while (SUIT_NAMES_BY_WEIGHT[left] != lhs.get_suit()) {
            left++;
        }
        while (SUIT_NAMES_BY_WEIGHT[right] != rhs.get_suit()) {
            right++;
        }
        return left < right;
    }
}

bool operator>(const Card &lhs, const Card &rhs) {
    int left = 0, right = 0;
    // find which rank the left and right cards are
    while (RANK_NAMES_BY_WEIGHT[left] != lhs.get_rank()) {
        left++;
    }
    while (RANK_NAMES_BY_WEIGHT[right] != rhs.get_rank()) {
        right++;
    }
    // if they are not the same rank, we are done; the highest card is whichever
    // is the highest rank
    if (left != right) {
        return left > right;
    }
    // if they are the same rank, find which suit is highest according to the
    // specification Diamonds > Clubs > Hearts > Spades
    else {
        left = 0;
        right = 0;
        int left = 0, right = 0;
        while (SUIT_NAMES_BY_WEIGHT[left] != lhs.get_suit()) {
            left++;
        }
        while (SUIT_NAMES_BY_WEIGHT[right] != rhs.get_suit()) {
            right++;
        }
        return left > right;
    }
}

bool operator==(const Card &lhs, const Card &rhs) {
    // if !(lhs < rhs) and !(lhs, > rhs), then lhs must be equal to rhs
    return !(operator<(lhs, rhs) || operator>(lhs, rhs));
}

bool operator!=(const Card &lhs, const Card &rhs) {
    // if the lhs does not equal the right hand side . . .
    return !operator==(lhs, rhs);
}

string Suit_next(const string &suit) {
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_HEARTS ||
           suit == Card::SUIT_CLUBS || suit == Card::SUIT_DIAMONDS);
    // If the suit is red, return the other red suit. If the suit is black,
    // return the other black suit.
    if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    return Card::SUIT_DIAMONDS;
}

ostream & operator<<(ostream &os, const Card &card) {
    // print out rank of suit. (eg "Jack of Spades")
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const string &trump) {
    assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_HEARTS ||
           trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS);

    if (b.is_trump(trump)) {
        if (a.is_trump(trump)) {
            // if a and b are both trump, if a is right bower, it trumps left
            // bower, and Card_less is false. If a is left bower, and b is not
            // the left bower, then a > b, and Card_less is false.
            if (a.is_right_bower(trump) ||
                (a.is_left_bower(trump) && !b.is_right_bower(trump))) {
                return false;
            }
            // if a and b are both trump, if b is right bower, it trumps left
            // bower, and Card_less is true. If b is left bower, and a is not
            // the left bower, then a < b, and Card_less is true.
            if (b.is_right_bower(trump) ||
                (b.is_left_bower(trump) && !a.is_right_bower(trump))) {
                return true;
            }
            // b is trump and a is trump, but neither are right/left bower,
            // just find if a < b.
            return a < b;
        }
        // if b is trump and a is not, b trumps a no matter what a is
        return true;
    }
    // if b is not trump, and a is not trump, find if a < b. If a is trump and b
    // is not trump, a trumps b, and Card_less is false
    else {
        if (!a.is_trump(trump)) {
            return a < b;
        }
        return false;
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, const string &trump) {

    if (b.is_trump(trump)) {
        if (a.is_trump(trump)) {
            // if b and a are both trump, just treat the scenario as was if
            // there is no led card (its suit doesn't matter here)
            return Card_less(a, b, trump);
        }
        // if b is trump and a is not, b > a, and Card_less is true
        return true;
    }

    else {
        // if a is trump and b is not, b < a, and Card_less is false
        if (a.is_trump(trump)) {
            return false;
        }

        if (led_card.get_suit(trump) == b.get_suit()) {
            // if led card is the same suit as both b and a, find if a < b
            if (led_card.get_suit() == a.get_suit()) {
                return a < b;
            }
            // if b suit is same as led suit, and a is not, a < b
            return true;
        }
        else {
            // if b is not the led suit and a is the led suit, a > b, Card_less
            // is false
            if (led_card.get_suit(trump) == a.get_suit()) {
                return false;
            }
            // if both are not the led suit, find a < b
            return a < b;
        }
    }
}
