#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

// THIS TEST CASE IS NOT VERY THOROUGH.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Pack_tests.cpp

static void check_pack(Pack& pack);

int main() {
  const string filename = "pack.in";
  ifstream ifs(filename);
  assert(ifs.is_open());
  Pack pack_from_stream(ifs);
  check_pack(pack_from_stream);

  Pack default_pack;
  check_pack(default_pack);

  cout << "PASS" << endl;

  return 0;
}

static void check_pack(Pack& pack)
{
  Card first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_NINE, Card::SUIT_SPADES));

  assert(!pack.empty());

  pack.reset();

  first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_NINE, Card::SUIT_SPADES));

  pack.shuffle();

  first_card = pack.deal_one();
  assert(first_card == Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
}
