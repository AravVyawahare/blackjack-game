//Card

#ifndef cards_hpp
#define cards_hpp

#include <iostream>
#include <string>
using namespace std;

enum suit {
	clubs,
	diamonds,
	hearts,
	spades
};

struct Card {
    //functions
	/**************************************************************************
	 * Description:
	 * Prints the suit of the card
	 *
	 * Input:
	 * n/a
	 *
	 * Output:
	 * suit
	****************************************************************************/
    string print() {
        string suit = "";
        switch (m_suit) {
            case 0:
                suit = "clubs";
                break;
            case 1:
                suit = "diamonds";
                break;
            case 2:
                suit = "hearts";
                break;
            case 3:
                suit = "spades";
                break;
            default:
                break;
        }
        if (m_rank == 1) {
            return "ace of " + suit;
        }
        if (m_rank <= 10 && m_rank >= 2) {
            return to_string(m_rank) + " of " + suit;
        }
        if (m_rank == 11) {
            return "jack of " + suit;
        }
        if (m_rank == 12) {
            return "queen of " + suit;
        }
        if (m_rank == 13) {
            return "king of " + suit;
        }
        else {
            return "invalid";
        }
    }
    //variables
    enum suit m_suit;
    int m_rank;
};

#endif /* cards_hpp */

