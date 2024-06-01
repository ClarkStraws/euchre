#include "Player.h"
#include <cassert>
#include <algorithm>
using namespace std;

class Simple : public Player {
public:
  Simple(const string &name_){
    // give the player a name and empty hand
    name = name_;
    hand.empty();
  }
  virtual const string & get_name() const {
    return name;
  }

  virtual void add_card(const Card &c) {
    assert(hand.size() < MAX_HAND_SIZE);    
    hand.push_back(c);
  }

  virtual bool make_trump(const Card &upcard, bool is_dealer,
    int round, string &order_up_suit) const {
      assert(round == 1 || round == 2);
      if (round == 1) {
        // if round 1, and player has 2 or more face cards of same suit, order up
        // that suit. Otherwise, pass
        if (pick_up(upcard.get_suit())) {
          order_up_suit = upcard.get_suit();
          return true;
        }
        return false;
        }
      else {
        // if round 2, and you are the dealer, you must order up the suit of the
        // upcard
        if (is_dealer) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        // if round 2 and you are not the dealer, same behavior as round 1
        if (pick_up(Suit_next(upcard.get_suit()))) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        return false;
      }
  }

  virtual void add_and_discard(const Card &upcard) {
    assert(hand.size() > 0);
    // erase the minimum card in the hand and add the upcard to the hand
    hand.push_back(upcard);
    hand.erase(hand.begin() + min_card(upcard.get_suit()));
  }

  virtual Card lead_card(const string &trump){
    Card card(Card::RANK_TWO, Card::SUIT_SPADES);
    int card_index = -1;
    for(int i = 0; i < (int)hand.size(); i++){
      if(!hand[i].is_trump(trump) && hand[i] > card){
        card_index = i;
        card = hand[i];
      }
    }
    // if player has at least one card in hand that is not trump, play that card
    if(card_index + 1){
      hand.erase(hand.begin() + card_index);
      return card;
    }
    // otherwise, play the max trump card in hand
    card_index = max_in_suit(trump, trump);
    card = hand[card_index];
    hand.erase(hand.begin() + card_index);
    return card;
  }

  virtual Card play_card(const Card &led_card, const string &trump) {
    // find maximum trump card in hand
    int same_suit_index = max_in_suit(led_card.get_suit(trump), trump);
    // return the highest trump card in hand and erase in from the hand
    if (same_suit_index + 1) {
      Card card = hand[same_suit_index];
      hand.erase(hand.begin() + same_suit_index);
      return card;
    }
    // if no trump cards, return the minimum card in hand and erase it from hand
    int lowest_card_index = min_card(trump);
    Card card = hand[lowest_card_index];
    hand.erase(hand.begin() + lowest_card_index);
    return card;
  }

private:
  string name;
  vector<Card> hand;
  // return true if there are 2 or more trump cards in player's hand
  // else, return false
  bool pick_up(const string trump) const {
    int count = 0;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
      if (hand[i].is_face() && hand[i].is_trump(trump)) {
        count++;
      }
    }
    return count > 1;
  }
  // return the index of the maximum card of of a suit in the hand.
  // considers trump
  int max_in_suit(const string &suit, const string &trump) const {
    int max_card_index = -1;
    Card max_card(Card::RANK_TWO, suit);
    for (int i = 0; i < (int)hand.size(); i++) {
      Card temp(Card::RANK_TWO, suit);
      if (hand[i].get_suit(trump) == suit && Card_less(max_card, hand[i], temp, trump)) {
        max_card = hand[i];
        max_card_index = i;
      }
    }
    return max_card_index;
  }
  // returns the index of the minimum card in a hand
  // considers trump
  int min_card(const string trump) {
    int min_card_index = 0;
    Card min_card(Card::RANK_JACK, trump);
    for (int i = 0; i < (int)hand.size(); i++) {
      if (Card_less(hand[i], min_card, trump)) {
        min_card = hand[i];
        min_card_index = i;
      }
    }
    return min_card_index;
  }
};

class Human : public Player{
public:
  Human(const string &name_){
    // give the player a name and empty hand
    name = name_;
    hand.empty();
  }

 virtual const string & get_name() const{
   return name;
 }

 virtual void add_card(const Card &c){
   assert(hand.size() < MAX_HAND_SIZE);
   hand.push_back(c);
   sort(hand.begin(), hand.end());
 }

 virtual bool make_trump(const Card &upcard, bool is_dealer,
     int round, string &order_up_suit) const{
       // print hand and a prompt to ask the user to pass or to order up
       string choice;
       print_hand();
       cout << "Human player " << get_name()
            << ", please enter a suit, or \"pass\":" << endl;
       cin >> choice;

       assert(choice == "pass" || choice == upcard.get_suit() ||
             (choice == Suit_next(upcard.get_suit()) &&
              upcard.get_rank() == Card::RANK_JACK));
       // if round 2, and the player is the dealer, they must order up
       if(round == 2 && is_dealer){
         order_up_suit = upcard.get_suit();
         return true;
       }
       if(choice == "pass"){
         return false;
       }
       // otherwise, order up the choice of the player
       order_up_suit = choice;
       return true;
 }

 virtual void add_and_discard(const Card &upcard){
   // print hand and prompt user to discard a card
   print_hand();
   int choice = -2;
   cout << "Discard upcard: [-1]" << endl;
   cout << "Human player " << get_name();
   cout << ", please select a card to discard:" << endl;
   cin >> choice;
   // if player's choice is not -1, discard their selected card and add the upcard
   if(choice + 1){
     hand.erase(hand.begin() + choice);
     hand.push_back(upcard);
     sort(hand.begin(), hand.end());
   }
   cout << endl;
 }

 virtual Card lead_card(const string &trump){
     // print hand and a prompt asking player to select a card
     print_hand();
     int choice = -2;
     cout << "Human player " << get_name();
     cout << ", please select a card:" << endl;
     cin >> choice;
     // erase the card from the hand and return it
     Card temp = hand[choice];
     hand.erase(hand.begin() + choice);
     return temp;
 }

 virtual Card play_card(const Card &led_card, const string &trump){
     // print hand and a prompt asking the user to select a card
     print_hand();
     int choice = -2;
     cout << "Human player " << get_name();
     cout << ", please select a card:" << endl;
     cin >> choice;
     // erase the card from the hand and return it
     Card temp = hand[choice];
     hand.erase(hand.begin() + choice);
     return temp;
 }

private:
  string name;
  vector<Card> hand;
  // print hand with brackets around the element indices
  void print_hand() const{
    for(int i = 0; i < (int)hand.size(); i++){
      cout << "Human player " << get_name() << "'s hand: ";
      cout << "[" << i << "] " << hand[i] << endl;
    }
  }
};

Player * Player_factory(const string &name, const string &strategy){
  // create a Simple player if the choice is Simple, and a Human player if the
  // choice is Human
  if(strategy == "Simple"){
    return new Simple(name);
  }
  else if(strategy == "Human"){
    return new Human(name);
  }
  assert(false);
  exit(1);
}

ostream & operator<<(ostream &os, const Player &p){
  os << p.get_name();
  return os;
}
