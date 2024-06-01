#include "Player.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

// a few cards for testing
const Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
const Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
const Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
const Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
const Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
const Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
const Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
const Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
const Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
const Card ten_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
const Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
const Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
const Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
const Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
const Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
const Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
const Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
const Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);




void test_play_card();
void test_get_name();
void test_make_trump();
void test_lead_card();
void test_print_player();
void test_add_and_discard();

int main() {
  test_play_card();
  test_add_and_discard();
  test_get_name();
  test_make_trump();
  test_lead_card();
  test_print_player();

  cout << "Player_tests passed" << endl;
  return 0;
}

void test_add_and_discard(){
    // create a hand of just ten of spades
    Player* simple1 = Player_factory("simple1", "Simple");
    simple1->add_card(ten_spades);
    simple1->add_card(ten_spades);
    simple1->add_card(ten_spades);
    simple1->add_card(ten_spades);
    simple1->add_card(ten_spades);
    // the added card must replace a ten of spades
    simple1->add_and_discard(king_diamonds);
    // the king of diamonds will (hopefully) be played
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == king_diamonds);
    // the added card must replace a ten of spades,
    simple1->add_and_discard(queen_hearts);
    // the queen of hearts must be playeed
    assert(simple1->play_card(ten_hearts, Card::SUIT_SPADES) == queen_hearts);
    // etc.
    simple1->add_and_discard(jack_spades);
    assert(simple1->play_card(king_clubs, Card::SUIT_CLUBS) == jack_spades);

    simple1->add_and_discard(king_clubs);
    assert(simple1->play_card(queen_clubs, Card::SUIT_CLUBS) == king_clubs);

    simple1->add_and_discard(jack_diamonds);
    assert(simple1->play_card(king_hearts, Card::SUIT_HEARTS) == jack_diamonds);
    // hand should be empty now (played five cards)
    // add all five highest cards to see if add_and_discard() still works
    simple1->add_card(jack_diamonds);
    simple1->add_card(ace_diamonds);
    simple1->add_card(king_diamonds);
    simple1->add_card(queen_diamonds);
    simple1->add_card(jack_hearts);
    // player should not keep ten_diamonds in hand
    simple1->add_and_discard(ten_diamonds);
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == jack_diamonds);
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == jack_hearts);
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == ace_diamonds);
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == king_diamonds);
    assert(simple1->play_card(nine_diamonds, Card::SUIT_DIAMONDS) == queen_diamonds);

    delete simple1;
    cout << "test_add_and_discard() PASS" << endl;
}

void test_play_card(){
  //testing add card
  Player* simple1 = Player_factory("simple1", "Simple");
  simple1->add_card(jack_spades);
  simple1->add_card(ten_spades);
  simple1->add_card(queen_hearts);
  simple1->add_card(nine_hearts);
  simple1->add_card(jack_clubs);
  // testing add and discard
  // should replace ten_spades and nine_hearts
  simple1->add_and_discard(king_diamonds);
  simple1->add_and_discard(nine_diamonds);
  // using led card as same card in hand for simplicity
  //testing play card
  assert(simple1->play_card(jack_spades, Card::SUIT_SPADES) == jack_spades);
  assert(simple1->play_card(king_diamonds, Card::SUIT_SPADES) == king_diamonds);
  assert(simple1->play_card(queen_hearts, Card::SUIT_SPADES) == queen_hearts);
  assert(simple1->play_card(nine_diamonds, Card::SUIT_SPADES) == nine_diamonds);
  assert(simple1->play_card(jack_clubs, Card::SUIT_SPADES) == jack_clubs);
 // More of the same, but this time using different inputs to see if the expected
 // card is played
  simple1->add_card(jack_spades);
  simple1->add_card(ten_spades);
  simple1->add_card(queen_hearts);
  simple1->add_card(nine_hearts);
  simple1->add_card(jack_diamonds);

  assert(simple1->play_card(ace_hearts, Card::SUIT_HEARTS) == jack_diamonds);
  assert(simple1->play_card(king_clubs, Card::SUIT_DIAMONDS) == nine_hearts);
  assert(simple1->play_card(jack_clubs, Card::SUIT_CLUBS) == jack_spades);
  assert(simple1->play_card(ten_hearts, Card::SUIT_SPADES) == queen_hearts);
  assert(simple1->play_card(nine_diamonds, Card::SUIT_SPADES) == ten_spades);

  simple1->add_card(jack_spades);
  simple1->add_card(jack_diamonds);
  simple1->add_card(queen_hearts);
  simple1->add_card(jack_clubs);
  simple1->add_card(king_clubs);

  assert(simple1->play_card(king_clubs, Card::SUIT_CLUBS) == jack_clubs);
  assert(simple1->play_card(jack_clubs, Card::SUIT_SPADES) == jack_spades);
  assert(simple1->play_card(jack_spades, Card::SUIT_CLUBS) == king_clubs);
  assert(simple1->play_card(ace_hearts, Card::SUIT_HEARTS) == jack_diamonds);
  assert(simple1->play_card(king_clubs, Card::SUIT_CLUBS) == queen_hearts);

  simple1->add_card(ace_hearts);
  simple1->add_card(king_hearts);
  simple1->add_card(queen_hearts);
  simple1->add_card(jack_diamonds);
  simple1->add_card(jack_hearts);

  assert(simple1->play_card(queen_spades, Card::SUIT_DIAMONDS) == queen_hearts);
  assert(simple1->play_card(ten_hearts, Card::SUIT_SPADES) == ace_hearts);
  assert(simple1->play_card(queen_spades, Card::SUIT_SPADES) == jack_hearts);
  assert(simple1->play_card(king_clubs, Card::SUIT_SPADES) == jack_diamonds);
  assert(simple1->play_card(king_clubs, Card::SUIT_CLUBS) == king_hearts);

  delete simple1;
  cout << "test_play_card() PASS" << endl;
}

void test_get_name() {
    // ensure that the players are initialized correctly
    Player *simple1 = Player_factory("Kevin1", "Simple");
    assert(simple1->get_name() == "Kevin1");
    Player *human1 = Player_factory("Kevin2", "Human");
    assert(human1->get_name() == "Kevin2");
    delete simple1;
    cout << "test_get_name() PASS" << endl;
}
// A test function that asserts that make_trump() is working correctly.
// Checks for appropriate behavior when the player should pick up, and when the
// player should not pick up
void test_make_trump(){
  // round 1
  Player *simple1 = Player_factory("Kevin1", "Simple");
  simple1->add_card(jack_spades);
  simple1->add_card(queen_spades);
  simple1->add_card(jack_clubs);
  simple1->add_card(ace_hearts);
  simple1->add_card(ten_hearts);
  string upcard = "test";
  // test pick up
  assert(simple1->make_trump(ten_spades, false, 1, upcard));
  assert(upcard == Card::SUIT_SPADES);
  assert(simple1->make_trump(queen_spades, false, 1, upcard));
  assert(upcard == Card::SUIT_SPADES);
  assert(simple1->make_trump(ten_spades, true, 1, upcard));
  assert(upcard == Card::SUIT_SPADES);
  assert(simple1->make_trump(queen_spades, true, 1, upcard));
  assert(upcard == Card::SUIT_SPADES);
  upcard = "test";
  assert(!simple1->make_trump(ace_diamonds, true, 1, upcard));
  assert(upcard == "test");


  Player *simple2 = Player_factory("Henry1", "Simple");
  simple2->add_card(jack_diamonds);
  simple2->add_card(nine_diamonds);
  simple2->add_card(king_diamonds);
  simple2->add_card(jack_hearts);
  simple2->add_card(queen_spades);
  // pick up with different hand
  assert(simple2->make_trump(nine_diamonds, false, 1, upcard));
  assert(upcard == Card::SUIT_DIAMONDS);

  // test don't pick up
  upcard = "test";
  assert(!simple1->make_trump(ace_hearts, false, 1, upcard));
  assert(upcard == "test");

  assert(!simple1->make_trump(nine_diamonds, false, 1, upcard));
  assert(upcard == "test");
  // if the player is the dealer (should be same as non-dealer for round 1)
  assert(!simple1->make_trump(ace_hearts, true, 1, upcard));
  assert(upcard == "test");

  assert(simple1->make_trump(ten_spades, true, 1, upcard));
  assert(upcard == Card::SUIT_SPADES);

  // round 2
  upcard = "test";
  // pick it up
  assert(simple1->make_trump(ten_spades, false, 2, upcard));
  assert(upcard == Card::SUIT_CLUBS);

  assert(simple1->make_trump(king_clubs, false, 2, upcard));
  assert(upcard == Card::SUIT_SPADES);

  // don't pick it up
  upcard = "test";
  assert(!simple1->make_trump(queen_hearts, false, 2, upcard));
  assert(upcard == "test");

  // if the player is the dealer (pick up everything)
  assert(simple1->make_trump(ten_spades, true, 2, upcard));
  assert(upcard == Card::SUIT_CLUBS);
  assert(simple1->make_trump(jack_diamonds, true, 2, upcard));
  assert(upcard == Card::SUIT_HEARTS);
  assert(simple1->make_trump(nine_hearts, true, 2, upcard));
  assert(upcard == Card::SUIT_DIAMONDS);
  assert(simple1->make_trump(king_clubs, true, 2, upcard));
  assert(upcard == Card::SUIT_SPADES);

  Player *simple3 = Player_factory("Henry2", "Simple");
  simple3->add_card(jack_diamonds);
  simple3->add_card(ace_hearts);
  simple3->add_card(queen_spades);
  simple3->add_card(king_clubs);
  simple3->add_card(ten_hearts);
  upcard = "test";

  assert(simple3->make_trump(jack_hearts, false, 1, upcard));
  assert(upcard == Card::SUIT_HEARTS);
  upcard = "test";
  assert(simple3->make_trump(jack_hearts, true, 1, upcard));
  assert(upcard == Card::SUIT_HEARTS);
  upcard = "test";
  /*
  assert(simple3->make_trump(jack_hearts, false, 2, upcard));
  assert(upcard == Card::SUIT_DIAMONDS);
  upcard = "test";
  assert(simple3->make_trump(jack_hearts, true, 2, upcard));
  assert(upcard == Card::SUIT_DIAMONDS);
  */
  delete simple1;
  delete simple2;
  delete simple3;
  cout << "test_make_trump() PASS" << endl;
}

// a test function which asserts that lead_card() is working correctly. Uses
// numerous cards to assert that the correct card is lead when trump is of all
// different suits
void test_lead_card(){
  Player *simple1 = Player_factory("Kevin1", "Simple");
  simple1->add_card(jack_spades);
  simple1->add_card(queen_spades);
  simple1->add_card(jack_clubs);
  simple1->add_card(ace_hearts);
  simple1->add_card(ten_hearts);

  assert(simple1->lead_card(Card::SUIT_SPADES) == ace_hearts);
  assert(simple1->lead_card(Card::SUIT_DIAMONDS) == queen_spades);
  assert(simple1->lead_card(Card::SUIT_CLUBS) == ten_hearts);
  assert(simple1->lead_card(Card::SUIT_SPADES) == jack_spades);
  assert(simple1->lead_card(Card::SUIT_HEARTS) == jack_clubs);

  simple1->add_card(king_clubs);
  simple1->add_card(queen_spades);
  simple1->add_card(jack_spades);
  simple1->add_card(nine_hearts);
  simple1->add_card(queen_hearts);

  assert(simple1->lead_card(Card::SUIT_SPADES) == king_clubs);
  assert(simple1->lead_card(Card::SUIT_SPADES) == queen_hearts);
  assert(simple1->lead_card(Card::SUIT_SPADES) == nine_hearts);
  assert(simple1->lead_card(Card::SUIT_SPADES) == jack_spades);
  assert(simple1->lead_card(Card::SUIT_DIAMONDS) == queen_spades);

  simple1->add_card(jack_spades);
  simple1->add_card(jack_clubs);
  simple1->add_card(jack_hearts);
  simple1->add_card(jack_diamonds);
  simple1->add_card(ace_hearts);

  assert(simple1->lead_card(Card::SUIT_SPADES) == ace_hearts);
  assert(simple1->lead_card(Card::SUIT_DIAMONDS) == jack_clubs);
  assert(simple1->lead_card(Card::SUIT_CLUBS) == jack_diamonds);
  assert(simple1->lead_card(Card::SUIT_SPADES) == jack_hearts);
  assert(simple1->lead_card(Card::SUIT_HEARTS) == jack_spades);

  simple1->add_card(nine_hearts);
  simple1->add_card(nine_diamonds);
  simple1->add_card(ten_hearts);
  simple1->add_card(ten_spades);
  simple1->add_card(jack_spades);

  assert(simple1->lead_card(Card::SUIT_SPADES) == ten_hearts);
  assert(simple1->lead_card(Card::SUIT_DIAMONDS) == jack_spades);
  assert(simple1->lead_card(Card::SUIT_CLUBS) == ten_spades);
  assert(simple1->lead_card(Card::SUIT_HEARTS) == nine_diamonds);
  assert(simple1->lead_card(Card::SUIT_DIAMONDS) == nine_hearts);

  delete simple1;
  cout << "test_lead_card() PASS" << endl;
}

// test function which asserts that the printing operator works correctly for
// different types of players
void test_print_player(){
  Player *Kevin = Player_factory("Kevin", "Human");
  Player *Henry = Player_factory("Henry", "Human");
  Player *Robot = Player_factory("Robot", "Simple");
  stringstream s;
  s << *Kevin << " " << *Henry << " " << *Robot;
  stringstream correct;
  correct << "Kevin Henry Robot";
  assert(s.str() == correct.str());
  delete Kevin;
  delete Henry;
  delete Robot;
  cout << "test_print_player() PASS" << endl;
}
