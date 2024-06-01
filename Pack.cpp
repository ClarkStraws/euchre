#include <cassert>
#include "Pack.h"
using namespace std;

Pack::Pack() {
    int index = 0;
    next = 0;
    // fill the pack with the 24 cards we need for a Euchre game
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 7; rank < 13; rank++) {
            Card temp(RANK_NAMES_BY_WEIGHT[rank], SUIT_NAMES_BY_WEIGHT[suit]);
            cards[index] = temp;
            index++;
        }
    }
}

Pack::Pack(istream& pack_input) {
    string rank, junk, suit;
    int index = 0;
    next = 0;
    // take in rank and suit, but discard the "of" between them. Then, set each
    // Card object in cards to the cards read in.
    while (pack_input >> rank) {
        pack_input >> junk;
        pack_input >> suit;
        Card temp(rank, suit);
        cards[index] = temp;
        index++;
    }
}

Card Pack::deal_one() {
    assert(next < PACK_SIZE);
    // increase next but return the card at next index irst
    int index = next;
    next++;
    return cards[index];
}

void Pack::reset() {
    // begin at the beginning of the pack again
    next = 0;
}

void Pack::shuffle() {
    array<Card, 17> temp_arr;
    // shuffle the deck three times as expained in the specification.
    // copy elements into a temporary array to store them temporarily while we
    // move the last few elements to the beginning. Then, put those elements at
    // the end of the original
    for (int times = 0; times < 3; times++) {

        for (int first = 0; first < 17; first++) {
            temp_arr[first] = cards[first];
        }
        for (int second = 17; second < PACK_SIZE; second++) {
            cards[second - 17] = cards[second];
        }
        for (int first = 0; first < 17; first++) {
            cards[first + 7] = temp_arr[first];
        }
    }
    reset();
}


bool Pack::empty() const {
    // if next reaches full size of the pack, return true.
    return next == PACK_SIZE;
}
