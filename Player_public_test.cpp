#include "Player.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
  Player * human = Player_factory("NotRobot", "Human");
  cout << * human << endl;
  Player * alice = Player_factory("Alice", "Simple");
  cout << *alice << endl;
  assert(alice->get_name() == "Alice");

  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(two_spades);
  bob->add_card(two_spades);
  bob->add_card(two_spades);
  bob->add_card(two_spades);
  bob->add_card(two_spades);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  assert(orderup == false);
  assert(trump == Card::SUIT_SPADES);

  bob->add_and_discard(nine_spades);

  Card card_led = bob->lead_card(trump);
  assert(card_led == nine_spades); //check led card

  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  assert(card_played == two_spades);

  delete human;
  delete alice;
  delete bob;

  cout << "PASS" << endl;

  return 0;
}
