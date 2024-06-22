#ifndef player_hpp
#define player_hpp

#include "deck.hpp"

struct Player {
    //functions
	/**************************************************************************
	 * Description:
	 * Adds the card to the players hand and adjusts the points accordingly
	 *
	 * Input:
	 * c - a pass by value to the Card object
	 *
	 * Output:
	 * n/a
	****************************************************************************/
    void addCard(Card c) {
        hand.push_back(c);
        if (c.m_rank == 1) {
            if (points + 11 > 21) {
                points++;
                return;
            }
            else {
                points += 11;
                return;
            }
        }
        if (c.m_rank > 10) {
            points += 10;
            return;
        }
        points += c.m_rank;
    }
    /**************************************************************************
     * Description:
     * Increases the player's money by the amount they wagered
     *
     * Input:
     * m - wagered money
     *
     * Output:
     * n/a
    ****************************************************************************/
    void win(int m) {
        money += m;
    }
    /**************************************************************************
     * Description:
     * Decreases the player's money by the amount they wagered
     *
     * Input:
     * m - wagered money
     *
     * Output:
     * n/a
    ****************************************************************************/
    void lose(int m) {
        money -= m;
    }/**************************************************************************
     * Description:
     * Returns a player's cards back to the deck
     *
     * Input:
     * d - a reference to the deck
     *
     * Output:
     * n/a
    ****************************************************************************/
    void returnToPile(vector<Card>& d) {
        while (hand.size() > 0) {
            Card c = hand.back();
            d.push_back(c);
            hand.pop_back();
        }
        points = 0;
    }
    //variables
    vector<Card> hand;
    int money;
    int points;
    string name;
};

#endif /* player_hpp */
