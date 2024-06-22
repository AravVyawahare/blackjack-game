#ifndef deck_hpp
#define deck_hpp

#include "cards.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

/**************************************************************************
 * Description:
 * Swaps two variables packed into x and y
 *
 * Input:
 * x - a constant reference to a card object
 * y - a constant reference to a card object
 *
 * Output:
 * n/a
****************************************************************************/
void swap(Card& x, Card& y) {
    Card tmp = x;
    x = y;
    y = tmp;
}

struct Deck {
    //functions
	/**************************************************************************
	 * Description:
	 * Creation of a standard, 52 card deck
	 *
	 * Input:
	 * n/a
	 *
	 * Output:
	 * n/a
	****************************************************************************/
    void createDeck() {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= 13; j++) {
                switch(i) {
                    case 0:
                    {
                        Card c = {.m_suit = clubs, .m_rank = j};
                        deck.push_back(c);
                        break;
                    }
                    case 1:
                    {
                        Card c = {.m_suit = diamonds, .m_rank = j};
                        deck.push_back(c);
                        break;
                    }
                    case 2:
                    {
                        Card c = {.m_suit = hearts, .m_rank = j};
                        deck.push_back(c);
                        break;
                    }
                    case 3:
                    {
                        Card c = {.m_suit = spades, .m_rank = j};
                        deck.push_back(c);
                        break;
                    }
                    default:
                        continue;
                }
            }
        }
    }
    /**************************************************************************
     * Description:
     * Swaps two cards at random n amount of times until the deck has gone through
     * every card
     *
     * Input:
     * n/a
     *
     * Output:
     * n/a
    ****************************************************************************/
    void shuffle() {
        for (int i = 0; i < deck.size(); i++) {
            swap(deck[rand() % deck.size()], deck[rand() % deck.size()]);
        }
    }
    /**************************************************************************
     * Description:
     * Shuffles the deck n number of times
     *
     * Input:
     * n/a
     *
     * Output:
     * n/a
    ****************************************************************************/
    void shuffleTimes(int n) {
        for (int i = 0; i < n; i++) {
            shuffle();
        }
    }
    /**************************************************************************
     * Description:
     * Returns the card at the back of the deck and removes
     *
     * Input:
     * n/a
     *
     * Output:
     * c
    ****************************************************************************/
    Card deal() {
        Card c = deck.back();
        deck.pop_back();
        return c;
    }
    //variables
    vector<Card> deck;
};

#endif /* deck_hpp */
