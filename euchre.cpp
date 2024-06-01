#include "Pack.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

// REQUIRES: argv and pack are valid arguments
// MODIFIES: pack, cout
// EFFECTS: Runs the game for the players using pack and the arguments provided
//         in main. Also prints basic messages, keeps track of score, round, hand,
//         and deals
void game(char **argv, Pack &pack);
const int NUM_PLAYERS = 4;

int main(int argc, char **argv){
    // ensure that the input of the functions is correct. If not, print an Error
    // message and exit.
    if (argc != 12 || !(atoi(argv[3]) > 0 && atoi(argv[3]) < 101) ||
       !(strcmp(argv[2], "shuffle") == 0 || strcmp(argv[2], "noshuffle") == 0) ||
       !((strcmp(argv[5], "Simple") == 0 || strcmp(argv[5], "Human") == 0) &&
       (strcmp(argv[7], "Simple") == 0 || strcmp(argv[7], "Human") == 0) &&
       (strcmp(argv[9], "Simple") == 0 || strcmp(argv[9], "Human") == 0) &&
       (strcmp(argv[11], "Simple") == 0 || strcmp(argv[11], "Human") == 0))) {
           cout << "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_"
                << "TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4"
                << endl;
            exit(EXIT_FAILURE);
     }
    // use the second argument as the filename. If it cannot be opened, print an
    // error message and exit
    string pack_filename = argv[1];
    ifstream fin;
    fin.open(pack_filename);
    if(!fin.is_open()){
      cout << "Error opening " << pack_filename << endl;
      exit(EXIT_FAILURE);
    }
    Pack pack(fin);
    fin.close();
    // print out the command used in the beginning
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << ' ';
    }
    cout << endl;
    // run the game
    game(argv, pack);
    return 0;
}

void game(char **argv, Pack &pack){
    int hand = 0;
    int scoreA = 0, scoreB = 0;
    vector<Player*> player;
    player.empty();
    // add the players from the arguments using the given names and strategies
    for(int i = 0; i < 4; i++){
        player.push_back(Player_factory(argv[4 + i * 2], argv[5 + i * 2]));
    }
    // agrv[3] is the max number of points.
    while (scoreA < atoi(argv[3]) && scoreB < atoi(argv[3])) {
        // argv[2] is shuffle or not
        if (strcmp(argv[2], "shuffle") == 0) {
            pack.shuffle();
        }
        else {
            pack.reset();
        }
        // print out the hand at the beginning of the hand and the dealer's name
        cout << "Hand " << hand << endl;
        cout << *player[hand % 4] << " deals" << endl;
        // deal the cards 3-2-3-2
        for (int i = 0; i < NUM_PLAYERS; i++) {
                 for (int j = 0; j < 3 - i % 2; j++) {
                     // hand % 4 is the dealer, + 1 making it the first to be dealt,
                     // + i makes everyone get dealt
                     player[(hand % 4 + 1 + i) % 4]->add_card(pack.deal_one());
                 }
             }
             // then deal the remaining cards 2-3-2-3
             for (int i = 0; i < NUM_PLAYERS; i++) {
                 for (int j = 0; j < 2 + i % 2; j++) {
                     player[(hand % 4 + 1 + i) % 4]->add_card(pack.deal_one());
                 }
             }
        // deal the upcard out and print what it is
        Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        string trump = "passes";
        //hand % 4 is the dealer, + 1 is the first person to call
        int player_index = (hand % 4 + 1) % 4;
        int round = 1;
        // while no one orders up . . .
        while (trump == "passes") {
            // if they pass, print out the name and that they pass
             if (!player[player_index]->make_trump(upcard,
                 player_index == hand % 4, round, trump)) {
                     cout << *player[player_index] << ' ' << trump << endl;
                     // once the dealer passses, start over and set round to 2
                     if (player_index == hand % 4) {
                         round++;
                     }
                     player_index = (player_index + 1) % 4;
                 }
             // if they don't pass, print that hey order up, and set trump to the
             // choice
             else {
                 cout << *player[player_index] << " orders up "
                      << trump << endl;
                 if (round == 1) {
                     player[player_index]->add_and_discard(upcard);
                 }
             }
        }
        cout << endl;

        //play the game
        // 5 trick in a hand
        int lead = (hand % 4 + 1) % 4;
        int trickA = 0, trickB = 0;
        // for each trick, count through the players and play the cards they select
        for (int trick = 0; trick < 5; trick++) {
            Card led_card = player[lead]->lead_card(trump);
            // when a person leads, print out that they lead, and what card
            cout << led_card << " led by " << *player[lead] << endl;
            int winner = lead;
            Card winning_card = led_card;
            // keep track of the winning card, and print out the cards each player
            // plays
            for (int i = 1; i < 4; i++) {
                Card played_card = player[(lead + i) % 4]->play_card(led_card, trump);
                cout << played_card << " played by " << *player[(lead + i) % 4] << endl;
                if (Card_less(winning_card, played_card, led_card, trump)) {
                    winner = (lead + i) % 4;
                    winning_card = played_card;
                }
            }
            // print out the winner (determined by winner and winning_card)
            cout << *player[winner] << " takes the trick" << endl;
            cout << endl;
            // the next person to lead should be the winner of the previous trick
            lead = winner;
            // if the winner is an even numbered player (0 or 2), increase that
            // team's score
            if (winner % 2 == 0) {
                trickA++;
            }
            // if the winner is an odd numbered player (1 or 3), increase that
            // team's score
            else {
                trickB++;
            }
        }
        // if team A has (even players) has won the hand . . .
        if (trickA > trickB) {
            // print out the players of that team and that they win
            cout << *player[0] << " and " << *player[2] << " win the hand" << endl;
            // player_index is the one who ordered up
            if (player_index % 2 == 0) {
                // if the team who ordered up wins all hands, they march!
                if (trickA == 5) {
                    cout << "march!" << endl;
                    // increase the score of team A
                    scoreA++;
                }
                // increase score of team A (march grants 2 points if 5 tricks
                // were taken)
                scoreA++;
            }
            else {
                // if the team that ordered up was not the winning team, it is
                // called a euchre and they get 2 points for winning
                cout << "euchred!" << endl;
                scoreA += 2;
            }
        }
        // if team B has (odd players) has won the hand . . .
        else {
            // print out the players of that team and that they win
            cout << *player[1] << " and " << *player[3] << " win the hand" << endl;
            if (player_index % 2 == 1) {
                if (trickB == 5) {
                    cout << "march!" << endl;
                    // increase the score of team B
                    scoreB++;
                }
                // increase score of team B (march grants 2 points if 5 tricks
                // were taken)
                scoreB++;
            }
            else {
                cout << "euchred!" << endl;
                scoreB += 2;
            }
        }
        // print out the teams and their points, and increase the hand
        cout << *player[0] << " and " << *player[2] << " have "
             << scoreA << " points" << endl;
        cout << *player[1] << " and " << *player[3] << " have "
             << scoreB << " points" << endl << endl;
        hand++;
    }
    // if the score of team A is greater than or equal to the number of
    // hands to win, print that team A wins
    if (!(scoreA < atoi(argv[3]))) {
        cout << *player[0] << " and " << *player[2] << " win!" << endl;
    }
    else {
        // do the same for team B
        cout << *player[1] << " and " << *player[3] << " win!" << endl;
    }
    // delete the players
    for (int i = 0; i < int(player.size()); i++) {
        delete player[i];
        player[i] = nullptr;
    }

}
