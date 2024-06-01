#include "Card.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

void test_card_init();
void test_card_default();
void test_card_get_rank();
void test_card_get_suit();
void test_card_is_face();
void test_card_is_right_bower();
void test_card_is_left_bower();
void test_card_is_trump();
void test_card_less_than();
void test_card_greater_than();
void test_card_equal();
void test_card_not_equal();
void test_card_suit_next();
void test_card_print();
void test_card_less();
void test_card_less_led();
void in_depth_test_card_less();


int main() {

  test_card_init();
  test_card_default();
  test_card_get_rank();
  test_card_get_suit();
  test_card_is_face();
  test_card_is_right_bower();
  test_card_is_left_bower();
  test_card_is_trump();
  test_card_less_than();
  test_card_greater_than();
  test_card_equal();
  test_card_not_equal();
  test_card_suit_next();
  test_card_print();
  test_card_less();
  test_card_less_led();
  in_depth_test_card_less();

  cout << "Card_tests passed" << endl;
  return 0;
}

// test function which ensures that the initialization of different types of cards
// behaves as expected
void test_card_init(){
  Card test1(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
  assert(test1.get_rank() == Card::RANK_FOUR && test1.get_suit() == Card::SUIT_DIAMONDS);
  Card test2(Card::RANK_ACE, Card::SUIT_CLUBS);
  assert(test2.get_rank() == Card::RANK_ACE && test2.get_suit() == Card::SUIT_CLUBS);
  test1 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(test1.get_rank() == Card::RANK_JACK && test1.get_suit() == Card::SUIT_SPADES);
  test2 = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  assert(test2.get_rank() == Card::RANK_KING && test2.get_suit() == Card::SUIT_HEARTS);

  cout << "test_card_init() PASSED" << endl;
}

void test_card_default(){
  // the default card is the Two of Spades
  // assert that this default constructor works correctly
  Card test;
  assert(test.get_rank() == Card::RANK_TWO && test.get_suit() == Card::SUIT_SPADES);
  cout << "test_card_default() PASSED" << endl;
}

// test function which uses every type of card of Clubs to see if the correct
// rank is returned
void test_card_get_rank(){
  Card test = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_ACE);

  test = Card(Card::RANK_TWO, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_TWO);

  test = Card(Card::RANK_THREE, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_THREE);

  test = Card(Card::RANK_FOUR, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_FOUR);

  test = Card(Card::RANK_FIVE, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_FIVE);

  test = Card(Card::RANK_SIX, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_SIX);

  test = Card(Card::RANK_SEVEN, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_SEVEN);

  test = Card(Card::RANK_EIGHT, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_EIGHT);

  test = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_NINE);

  test = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_TEN);

  test = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_JACK);

  test = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_QUEEN);

  test = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  assert(test.get_rank() == Card::RANK_KING);

  cout << "test_card_get_rank() PASSED" << endl;
}

// test function which uses various types of cards -- namely the bowers --
// to assert that get_suit() works
void test_card_get_suit(){

  Card test(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  assert(test.get_suit() == Card::SUIT_DIAMONDS);
  assert(test.get_suit(Card::SUIT_HEARTS) == Card::SUIT_HEARTS);
  assert(test.get_suit(Card::SUIT_DIAMONDS) == Card::SUIT_DIAMONDS);
  assert(test.get_suit(Card::SUIT_SPADES) == Card::SUIT_DIAMONDS);

  test = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(test.get_suit() == Card::SUIT_CLUBS);
  assert(test.get_suit(Card::SUIT_CLUBS) == Card::SUIT_CLUBS);

  test = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(test.get_suit() == Card::SUIT_HEARTS);
  assert(test.get_suit(Card::SUIT_CLUBS) == Card::SUIT_HEARTS);
  assert(test.get_suit(Card::SUIT_DIAMONDS) == Card::SUIT_DIAMONDS);

  test = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
  assert(test.get_suit() == Card::SUIT_SPADES);
  assert(test.get_suit(Card::SUIT_HEARTS) == Card::SUIT_SPADES);

  test = Card(Card::RANK_TEN, Card::SUIT_SPADES);
  assert(test.get_suit() == Card::SUIT_SPADES);
  assert(test.get_suit(Card::SUIT_CLUBS) == Card::SUIT_SPADES);
  assert(test.get_suit(Card::SUIT_DIAMONDS) == Card::SUIT_SPADES);

  cout << "test_card_get_suit() PASSED" << endl;
}
// tests whether a face card will return true from is_face()
// also tests whether a noface card will return true (this would be bad)
void test_card_is_face(){
  Card test(Card::RANK_ACE, Card::SUIT_CLUBS);
  assert(test.is_face());

  test = Card(Card::RANK_SIX, Card::SUIT_DIAMONDS);
  assert(!test.is_face());

  test = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(test.is_face());

  test = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  assert(test.is_face());

  test = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
  assert(!test.is_face());

  test = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  assert(test.is_face());

  cout << "test_card_is_face() PASSED" << endl;
}

// tests cards to ensure is_right_bower() is working correctly.
void test_card_is_right_bower(){
  Card test = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(test.is_right_bower(Card::SUIT_SPADES));

  test = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!test.is_right_bower(Card::SUIT_SPADES));

  test = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(!test.is_right_bower(Card::SUIT_CLUBS));

  test = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!test.is_right_bower(Card::SUIT_DIAMONDS));

  test = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
  assert(!test.is_right_bower(Card::SUIT_DIAMONDS));
  assert(!test.is_right_bower(Card::SUIT_HEARTS));

  test = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  assert(test.is_right_bower(Card::SUIT_DIAMONDS));

  test = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(test.is_right_bower(Card::SUIT_CLUBS));
  cout << "test_card_is_right_bower() PASSED" << endl;
}

// tests cards to ensure is_left_bower() is working correctly.
void test_card_is_left_bower(){
  Card test1(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(!test1.is_left_bower(Card::SUIT_SPADES));

  Card test2(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(test2.is_left_bower(Card::SUIT_SPADES));

  Card test3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(!test3.is_left_bower(Card::SUIT_CLUBS));

  Card test4(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!test4.is_left_bower(Card::SUIT_DIAMONDS));

  Card test5 = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
  assert(!test5.is_left_bower(Card::SUIT_DIAMONDS));
  assert(!test5.is_left_bower(Card::SUIT_HEARTS));

  test5 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  assert(test5.is_left_bower(Card::SUIT_HEARTS));

  test5 = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(test5.is_left_bower(Card::SUIT_SPADES));
  cout << "test_card_is_left_bower() PASSED" << endl;
}

// asserts whether a card of any type will be a trump card
void test_card_is_trump(){
  Card test1(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(test1.is_trump(Card::SUIT_CLUBS));

  Card test2(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(!test2.is_trump(Card::SUIT_CLUBS));

  Card test3(Card::RANK_NINE, Card::SUIT_SPADES);
  assert(!test3.is_trump(Card::SUIT_DIAMONDS));

  Card test4(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(test4.is_trump(Card::SUIT_HEARTS));

  Card test5(Card::RANK_TEN, Card::SUIT_HEARTS);
  assert(test5.is_trump(Card::SUIT_HEARTS));

  test5 = Card(Card::RANK_TWO, Card::SUIT_DIAMONDS);
  assert(test5.is_trump(Card::SUIT_DIAMONDS));
  assert(!test5.is_trump(Card::SUIT_HEARTS));

  test5 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
  assert(test5.is_trump(Card::SUIT_DIAMONDS));
  assert(!test5.is_trump(Card::SUIT_HEARTS));
  assert(!test5.is_trump(Card::SUIT_CLUBS));
  cout << "test_card_is_trump() PASSED" << endl;
}

// tests < operator on cards of different types. Ensures that lhs is less than
// rhs, by convention. (left hand and right hand sides)
void test_card_less_than(){
  Card lhs(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  Card rhs(Card::RANK_KING, Card::SUIT_HEARTS);
  assert(lhs < rhs);
  assert(!(rhs < lhs));
  lhs = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  rhs = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
  assert(lhs < rhs);
  assert(!(rhs < lhs));
  lhs = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  rhs = Card(Card::RANK_TWO, Card::SUIT_CLUBS);
  assert(lhs < rhs);
  assert(!(rhs < lhs));
  lhs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  rhs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!(lhs < rhs));
  rhs = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(!(lhs < rhs));
  lhs = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  rhs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  assert(!(lhs < rhs));
  assert(rhs < lhs);
  lhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  rhs = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  assert(lhs < rhs);
  assert(!(rhs < lhs));
  lhs = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  rhs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(lhs < rhs);
  assert(!(rhs < lhs));

  cout << "test_card_less_than() PASSED" << endl;
}

// tests > operator on cards of different types. Ensures that lhs is greater than
// rhs, by convention. (left hand and right hand sides)
void test_card_greater_than(){
  Card lhs(Card::RANK_NINE, Card::SUIT_HEARTS);
  Card rhs(Card::RANK_FIVE, Card::SUIT_CLUBS);
  assert(lhs > rhs);
  assert(!(rhs > lhs));
  lhs = Card(Card::RANK_TWO, Card::SUIT_CLUBS);
  rhs = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  assert(lhs > rhs);
  assert(!(rhs > lhs));
  lhs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
  rhs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(lhs > rhs);
  assert(!(rhs > lhs));
  lhs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  rhs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!(lhs < rhs));
  lhs = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  rhs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  assert(lhs > rhs);
  assert(!(rhs > lhs));
  lhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  rhs = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  assert(!(lhs > rhs));
  assert(rhs > lhs);
  lhs = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  rhs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  assert(!(lhs > rhs));
  assert(rhs > lhs);
  cout << "test_card_greater_than() PASSED" << endl;
}

// tests == operator on cards of different types. Ensures that lhs is equal to
// rhs, by convention. (left hand and right hand sides)
void test_card_equal(){
  Card equal_lhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  Card equal_rhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  assert(equal_lhs == equal_rhs);
  assert(equal_rhs == equal_lhs);

  Card not_equal_lhs(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card not_equal_rhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  assert(!(not_equal_lhs == not_equal_rhs));
  assert(!(not_equal_rhs == not_equal_lhs));

  Card not_equal_lhs2(Card::RANK_SEVEN, Card::SUIT_SPADES);
  Card not_equal_rhs2(Card::RANK_SEVEN, Card::SUIT_HEARTS);
  assert(!(not_equal_lhs2 == not_equal_rhs2));
  assert(!(not_equal_rhs2 == not_equal_lhs2));

  Card not_equal_lhs3(Card::RANK_SEVEN, Card::SUIT_SPADES);
  Card not_equal_rhs3(Card::RANK_EIGHT, Card::SUIT_HEARTS);
  assert(!(not_equal_lhs3 == not_equal_rhs3));
  assert(!(not_equal_rhs3 == not_equal_lhs3));

  equal_lhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  equal_rhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  assert(equal_lhs == equal_rhs);
  assert(equal_rhs == equal_lhs);
  cout << "test_card_equal() PASSED" << endl;
}

// tests != operator on cards of different types. Ensures that lhs is not equal
// to rhs, by convention. (left hand and right hand sides)
void test_card_not_equal(){
  Card not_equal_lhs(Card::RANK_FIVE, Card::SUIT_CLUBS);
  Card not_equal_rhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  assert(not_equal_lhs != not_equal_rhs);
  assert(not_equal_rhs != not_equal_lhs);

  Card not_equal_lhs2(Card::RANK_FIVE, Card::SUIT_CLUBS);
  Card not_equal_rhs2(Card::RANK_ACE, Card::SUIT_CLUBS);
  assert(not_equal_lhs2 != not_equal_rhs2);
  assert(not_equal_rhs2 != not_equal_lhs2);

  Card not_equal_lhs3(Card::RANK_FIVE, Card::SUIT_SPADES);
  Card not_equal_rhs3(Card::RANK_ACE, Card::SUIT_CLUBS);
  assert(not_equal_lhs3 != not_equal_rhs3);
  assert(not_equal_rhs3 != not_equal_lhs3);

  Card equal_lhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  Card equal_rhs(Card::RANK_FIVE, Card::SUIT_HEARTS);
  assert(!(equal_lhs != equal_rhs));

  equal_lhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  equal_rhs = Card(Card::RANK_KING, Card::SUIT_SPADES);
  assert(!(equal_lhs != equal_rhs));
  assert(!(equal_rhs != equal_lhs));

  not_equal_lhs = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  not_equal_rhs = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
  assert(not_equal_lhs != not_equal_rhs);
  assert(not_equal_rhs != not_equal_lhs);

  cout << "test_card_not_equal() PASSED" << endl;
}

// ensures suit_next() works. (eg next suit of Spades would be clubs)
void test_card_suit_next(){
  assert(Suit_next(Card::SUIT_CLUBS) == Card::SUIT_SPADES);
  assert(Suit_next(Card::SUIT_SPADES) == Card::SUIT_CLUBS);
  assert(Suit_next(Card::SUIT_HEARTS) == Card::SUIT_DIAMONDS);
  assert(Suit_next(Card::SUIT_DIAMONDS) == Card::SUIT_HEARTS);
  cout << "test_card_suit_next() PASSED" << endl;
}

// asserts that teh printing operator works with cards as expected.
// cout << jack_of_spades_card; for example, should print "Jack of Spades"
void test_card_print(){
  Card printed(Card::RANK_FOUR, Card::SUIT_HEARTS);
  // Capture our output
  stringstream s;
  s << printed;
  // Correct output
  stringstream correct;
  correct << "Four of Hearts";
  assert(s.str() == correct.str());

  printed = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  // Capture our output
  s << printed;
  // Correct output
  correct << "Jack of Spades";
  assert(s.str() == correct.str());

  printed = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  // Capture our output
  s << printed;
  // Correct output
  correct << "Queen of Diamonds";
  assert(s.str() == correct.str());

  cout << "test_card_print() PASSED" << endl;
}

// tests Card_less(), not considering the led card. Asserts cards of any suit and
// rank will behave as expected (Card_less() should return true for a < b, considering
// trump)
void test_card_less(){
  Card a1(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card b1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  assert(Card_less(a1, b1, Card::SUIT_HEARTS));
  assert(!Card_less(b1, a1, Card::SUIT_HEARTS));
  assert(Card_less(a1, b1, Card::SUIT_DIAMONDS));
  assert(!Card_less(b1, a1, Card::SUIT_DIAMONDS));
  assert(!Card_less(a1, a1, Card::SUIT_DIAMONDS));
  assert(!Card_less(b1, b1, Card::SUIT_SPADES));

  Card a2(Card::RANK_FIVE, Card::SUIT_SPADES);
  Card b2(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
  assert(Card_less(a2, b2, Card::SUIT_HEARTS));
  assert(Card_less(a2, b2, Card::SUIT_DIAMONDS));
  assert(!Card_less(a2, b2, Card::SUIT_SPADES));

  Card a3(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card b3(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(Card_less(a3, b3, Card::SUIT_SPADES));
  assert(!Card_less(a3, b3, Card::SUIT_CLUBS));
  assert(!Card_less(a3, b3, Card::SUIT_DIAMONDS));

  Card a4(Card::RANK_FIVE, Card::SUIT_SPADES);
  Card b4(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(Card_less(a4, b4, Card::SUIT_DIAMONDS));
  assert(!Card_less(a4, b4, Card::SUIT_SPADES));

  a4 = Card(Card::RANK_KING, Card::SUIT_SPADES);
  b4 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(!Card_less(a4, b4, Card::SUIT_DIAMONDS));
  assert(Card_less(a4, b4, Card::SUIT_SPADES));
  assert(Card_less(a4, b4, Card::SUIT_CLUBS));

  cout << "test_card_less() PASSED" << endl;
}

// tests Card_less(), and considers the led card. Asserts cards of any suit and
// rank will behave as expected (Card_less() should return true for a < b, considering
// trump and led_card)
void test_card_less_led(){
  Card led0(Card::RANK_NINE, Card::SUIT_CLUBS);
  Card led1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  Card led2(Card::RANK_THREE, Card::SUIT_CLUBS);
  Card led3(Card::RANK_KING, Card::SUIT_HEARTS);
  Card led4(Card::RANK_JACK, Card::SUIT_SPADES);

  Card a(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card b(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  assert(Card_less(a, b, led1, Card::SUIT_HEARTS));
  assert(Card_less(a, b, led1, Card::SUIT_DIAMONDS));
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));
  assert(Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(a, a, led0, Card::SUIT_CLUBS));

  a = Card(Card::RANK_FIVE, Card::SUIT_SPADES);
  b = Card(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
  assert(Card_less(a, b, led2, Card::SUIT_HEARTS));
  assert(!Card_less(a, b, led2, Card::SUIT_SPADES));
  assert(Card_less(a, b, led2, Card::SUIT_DIAMONDS));
  assert(!Card_less(a, b, led4, Card::SUIT_HEARTS));
  assert(Card_less(a, b, led1, Card::SUIT_HEARTS));
  led0 = Card(Card::RANK_KING, Card::SUIT_SPADES);
  assert(!Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(a, a, led1, Card::SUIT_CLUBS));

  a = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  b = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  assert(Card_less(a, b, led1, Card::SUIT_SPADES));
  assert(!Card_less(a, b, led3, Card::SUIT_CLUBS));
  assert(!Card_less(a, b, led1, Card::SUIT_HEARTS));
  assert(!Card_less(a, b, led2, Card::SUIT_HEARTS));
  assert(!Card_less(b, b, led2, Card::SUIT_CLUBS));

  a = Card(Card::RANK_FIVE, Card::SUIT_SPADES);
  b = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(Card_less(a, b, led1, Card::SUIT_DIAMONDS));
  assert(Card_less(a, b, led3, Card::SUIT_CLUBS));
  assert(!Card_less(b, b, led3, Card::SUIT_DIAMONDS));

  led0 = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  a = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  b = Card(Card::RANK_SIX, Card::SUIT_DIAMONDS);
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));
  assert(!Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(b, b, led4, Card::SUIT_SPADES));

  led0 = Card(Card::RANK_NINE, Card::SUIT_SPADES);
  a = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  b = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  assert(Card_less(a, b, led0, Card::SUIT_HEARTS));
  assert(!Card_less(a, b, led0, Card::SUIT_SPADES));
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));
  assert(!Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(a, a, led4, Card::SUIT_CLUBS));


  led0 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  a = Card(Card::RANK_KING, Card::SUIT_SPADES);
  b = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
  assert(Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(a, b, led0, Card::SUIT_SPADES));
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));
  assert(Card_less(a, b, led2, Card::SUIT_CLUBS));
  led0 = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  assert(!Card_less(a, b, led0, Card::SUIT_SPADES));
  led0 = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));
  assert(!Card_less(b, b, led4, Card::SUIT_HEARTS));

  a = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  b = Card(Card::RANK_KING, Card::SUIT_SPADES);
  led0 = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  assert(Card_less(a, b, led0, Card::SUIT_HEARTS));
  assert(!Card_less(a, b, led0, Card::SUIT_CLUBS));
  assert(!Card_less(a, b, led0, Card::SUIT_SPADES));
  assert(Card_less(a, b, led0, Card::SUIT_DIAMONDS));

  cout << "test_card_less_led() PASSED" << endl;
}

// tests every possible suit and rank for Card_less(), not considering trump
void in_depth_test_card_less() {
  for (int suit1 = 0; suit1 < 4; suit1++)
    for (int suit2 = 0; suit2 < 4; suit2++)
      for (int rank1 = 7; rank1 < 13; rank1++)
        for (int rank2 = 7; rank2 < 13; rank2++) {
          // first
          if (suit1 == suit2) {
              // if suit and rank are equal, make two cards that are identical and assert that they are not the same
              if (rank1 == rank2) {
                Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                for (int suit = 0; suit < 4; suit++)
                  assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
              }
              // if the rank is different but suits are the same, assert
              // a < b
              else if (rank1 < rank2) {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      // consider trump and assert a < b
                      if (!((suit1 == suit || suit1 + 2 == suit || suit1 - 2 == suit) && rank1 == 9)) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      // otherwise, assert a is not less than b
                      else {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
              // if ranks are still different, but rank1 not less than rank2,
              // and suits are still the same, assert that a is not less than b
              else {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      // consider trump and assert a is not less than b
                      if (!((suit2 == suit || suit2 + 2 == suit || suit2 - 2 == suit) && rank2 == 9)) {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          // otherwise, assert a < b
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
          }

          //second
          // if suit1 is less than suit1, make two cards (a has suit 1 and
          // b has suit 2)
          if (suit1 < suit2) {
              if (rank1 == rank2) {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      if (suit == suit1) {
                          // consider trump and assert a is not less than b when
                          // a is trump
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit1 || suit - 2 == suit1) && rank1 == 9 && suit != suit2) {
                          // else, consider the ranks and figure out if a < b
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
              // if a is less than b and suit a is less than suit b
              else if (rank1 < rank2) {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      // consider trump and assert a must not be less than b
                      // unless b and a are not trump
                      if (suit == suit1 && !((suit + 2 == suit2 || suit - 2 == suit2) && rank2 == 9 && rank1 != 9)) {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit1 || suit - 2 == suit1) && rank1 == 9 && (suit != suit2 || (suit == suit2 && rank2 != 9))) {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
              else {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      // in all other cases, a must be less than b unless they are
                      // the same card
                      if (suit == suit2 && !((suit + 2 == suit1 || suit - 2 == suit1) && rank1 == 9 && rank2 != 9)) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit2 || suit - 2 == suit2) && rank2 == 9 && (suit != suit1 || (suit == suit1 && rank1 != 9))) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }

          }

          //third
          if (suit1 > suit2) {
              // if a's suit is greater than b's suit, and ranks are the same
              // Card_less() is only true if b's suit is left of a's in the order
              // Diamonds > Clubs > Hearts > Spades
              if (rank1 == rank2) {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      if (suit == suit2) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit2 || suit - 2 == suit2) && rank2 == 9 && suit != suit1) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
              else if (rank1 < rank2) {
                  // if suit a > suit b, and rank a < rank b, Card_less() can't
                  // be true unless a is trump and b is not (a is face)
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      if (suit == suit1 && !((suit + 2 == suit2 || suit - 2 == suit2) && rank2 == 9 && rank1 != 9)) {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit1 || suit - 2 == suit1) && rank1 == 9 && (suit != suit2 || (suit == suit2 && rank2 != 9))) {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
              else {
                  Card a(RANK_NAMES_BY_WEIGHT[rank1], SUIT_NAMES_BY_WEIGHT[suit1]);
                  Card b(RANK_NAMES_BY_WEIGHT[rank2], SUIT_NAMES_BY_WEIGHT[suit2]);
                  for (int suit = 0; suit < 4; suit++) {
                      if (suit == suit2 && !((suit + 2 == suit1 || suit - 2 == suit1) && rank1 == 9 && rank2 != 9)) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else if ((suit + 2 == suit2 || suit - 2 == suit2) && rank2 == 9 && (suit != suit1 || (suit == suit1 && rank1 != 9))) {
                          assert(Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                      else {
                          assert(!Card_less(a, b, SUIT_NAMES_BY_WEIGHT[suit]));
                      }
                  }
              }
          }

        } // end of loop
    cout << "in_depth_test_card_less() PASS" << endl;
}
