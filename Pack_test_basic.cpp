#include "Pack.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

void test_init();
void test_deal_one();
void test_reset();
void test_shuffle();
void test_empty();
void test_pack_input();

int main() {
  test_init();
  test_deal_one();
  test_reset();
  test_shuffle();
  test_empty();
  test_pack_input();
  cout << "Pack_test_basic PASS :-)";
}

// tests to see if the constructor for packs actually works by asserting that each
// element of the pack is at the location that corresponds to its spot in
// RANK_NAMES_BY_WEIGHT[] and SUIT_NAMES_BY_WEIGHT[].
void test_init() {
  Pack pack;
  for (int suit = 0; suit < 4; suit++) {
    for (int rank = 7; rank < 13; rank++) {
      Card card = pack.deal_one();
      assert(card.get_rank() == RANK_NAMES_BY_WEIGHT[rank] &&
      card.get_suit() == SUIT_NAMES_BY_WEIGHT[suit]);
    }
  }
  cout << "test_init() PASSED" << endl;
}

void test_deal_one() {
  Pack pack;
  // for every card in pack, assert that deal_one() returns the expected element
  for (int suit = 0; suit < 4; suit++) {
    for (int rank = 7; rank < 13; rank++) {
      Card card = pack.deal_one();
      assert(card.get_rank() == RANK_NAMES_BY_WEIGHT[rank] &&
      card.get_suit() == SUIT_NAMES_BY_WEIGHT[suit]);
    }
  }
  cout << "test_reset() PASS" << endl;
}


// test function that tests if resetting the pack actually sets next back to zero
void test_reset() {
  Pack pack;
  pack.reset();
  Card deal = pack.deal_one();
  // the first card should be Nine of Spades
  assert(deal.get_rank() == "Nine"
          && deal.get_suit() == "Spades");
  cout << "test_reset() PASS" << endl;
}

// test function to assert that shuffling behaves as expected
void test_shuffle(){
  array<Card, 24> temp_arr;
  Pack test_pack;
  Pack comp_pack;
  test_pack.shuffle();
  // copy the elements of the pack into an array and compare it to a comparison
  // pack by finding the element (index + 21) % 24, which should be the corresponding
  // index in the temp after shuffling
  for(int i = 0; i < 24; i++){
    temp_arr[i] = test_pack.deal_one();
  }
  for(int i = 0; i < 24; i++){
    assert(comp_pack.deal_one() == temp_arr[(i + 21) % 24]);
  }
  cout << "test_shuffle() PASSED" << endl;
}

// tests to see if empty() actually empties the pack
void test_empty(){
  Pack pack;
  for (int i = 0; i < 24; i++) {
    pack.deal_one();
  }
  assert(pack.empty());
  cout << "test_empty() PASSED" << endl;
}

// a function which asserts that reading into the pack behaves as expected
void test_pack_input(){
  Pack pack;
  stringstream in;
  for (int i = 0; i < 24; i++) {
    in << pack.deal_one();
  }
  Pack pack2(in);
  for (int suit = 0; suit < 4; suit++) {
    for (int rank = 7; rank < 13; rank++) {
      Card card = pack2.deal_one();
      assert(card.get_rank() == RANK_NAMES_BY_WEIGHT[rank] &&
                   card.get_suit() == SUIT_NAMES_BY_WEIGHT[suit]);
    }
  }
  cout << "test_pack_input() PASSED" << endl;
}
