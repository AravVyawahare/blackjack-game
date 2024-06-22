#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include <cctype>
#include <ctime>

#include "cards.hpp"
#include "deck.hpp"
#include "player.hpp"
using namespace std;

/**************************************************************************
 * Description:
 * A boolean function consisting of a range-based for loop meant to detect
 * non alphanumeric characters besides spaces
 *
 * Input:
 * name - player name inputted by the user
 *
 * Output:
 * True/False
****************************************************************************/
bool validName(string name) {
    for (char c : name) {
        if (isspace(c)) {
            continue;
        }
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

/**************************************************************************
 * Description:
 * Starting point of the program. Collects the player's name, and creates
 * the deck object. Collects the player's wager and prints out the content
 * of the game via loop structures and processing.
 *
 * Input:
 * N/A
 *
 * Output:
 * An integer that signals the exit code to the operating system (OS)
****************************************************************************/
int main() {

    srand((unsigned int)time(0));
    string name = "";
    
    cout << "What is your name? You may not enter special characters: ";
    while (name.empty() || !validName(name)) {
        getline(cin, name);
        if (name.empty() || !validName(name)) {
            cout << "Please enter a valid name. " << endl;
            cout << "What is your name? You may not enter special characters: ";
        }
    }
    
    // Generates two players. You (the user) and a cpu.
    Player you = {.money = 100, .points = 0, .name = name};
    Player cpu = {.money = 0, .points = 0, .name = "The computer"};

    // static var
    static Deck pile;
    pile.createDeck();
    int n = rand() % 100;
    pile.shuffleTimes(n);
    
    char play = ' ';
    
    while (you.money > 0 && play != 'n') {
        int wager = -999;
        cout << "You have $" << you.money << " right now, " << you.name << ". How much money do you want to wager? Must be less than or equal to " << you.money << " and greater than 0" << ": ";
        
        while (wager > you.money || wager <= 0) {
            cin >> wager;
            if (wager > you.money || wager <= 0) {
                cout << "Please enter a valid wager." << endl;
                cout << "How much money do you want to wager? Must be less than or equal to " << you.money << " and greater than 0" << ':';
            }
            else {
                break;
            }
        }
        
        cin.ignore(10000, '\n');
        cout << endl;
        
        you.addCard(pile.deal());
        you.addCard(pile.deal());
        cpu.addCard(pile.deal());
        cpu.addCard(pile.deal());
        
        cout << you.name << " currently has the "
                << you.hand[0].print() << " and the " << you.hand[1].print() << '.' << endl;
        cout << cpu.name << " currently has the " << cpu.hand[0].print()
                << " and an unflipped card." << endl;
//                << " and the " << cpu.hand[1].print() << '.' << endl;
        
        int scoreOfCompFirstCard = 0;
        if (cpu.hand[0].m_rank > 10) {
            scoreOfCompFirstCard = 10;
        }
        else if (cpu.hand[0].m_rank == 1) {
            scoreOfCompFirstCard = 11;
        }
        else {
            scoreOfCompFirstCard = cpu.hand[0].m_rank;
        }

        cout << you.name << " has " << you.points << " points" << '.' << endl;
        cout << cpu.name << " has " << scoreOfCompFirstCard << " points" << '.' << endl;
        
        char move = ' ';
        
        cout << "Do you want to hit or stand? Type 'H' for hit, 'S' for stand: ";
        cin >> move;
        
        while (toupper(move) != 'H' && toupper(move) != 'S') {
            cout << "Please enter a valid move." << endl;
            cout << "Do you want to hit or stand? Type 'H' for hit, 'S' for stand: ";
            cin >> move;
            if (toupper(move) == 'H' || toupper(move) == 'S') {
                break;
            }
        }
        
        if (toupper(move) == 'H') {
            while (toupper(move) == 'H') {
                you.addCard(pile.deal());
                cout << you.name << " drew the " << you.hand.back().print() << '.' << endl;
                cout << you.name << " now has " << you.points << " points." << endl;
                if (you.points > 21) {
                    cout << you.name << " busted." << endl;
                    break;
                }
                cout << "Do you want to hit or stand? Type 'H' for hit, 'S' for stand: ";
                cin >> move;
                while (toupper(move) != 'H' && toupper(move) != 'S') {
                    cout << "Please enter a valid move." << endl;
                    cout << "Do you want to hit or stand? Type 'H' for hit, 'S' for stand: ";
                    cin >> move;
                    if (toupper(move) == 'H' || toupper(move) == 'S') {
                        break;
                    }
                }
            }
        }
        
        if (toupper(move) == 'S') {
            cout << you.name << " chose to stand." << endl;
        }
        
        cout << endl << "It is now the computer's turn." << endl;
        cout << "The computer's unflipped card is revealed to be " << cpu.hand[1].print() << '.' << endl;
        cout << "The computer now has " << cpu.points << " points." << endl;
        
        while (cpu.points <= 21) {
            if (cpu.points > you.points) {
                you.lose(wager);
                cout << "The computer has more points than " << you.name << " without busting. " << you.name << " lost." << endl;
                break;
            }
            
            cpu.addCard(pile.deal());
            cout << cpu.name << " drew the " << cpu.hand.back().print() << '.' << endl;
            cout << cpu.name << " now has " << cpu.points << " points." << endl;
            if (cpu.points > you.points && cpu.points <= 21) {
                you.lose(wager);
                cout << cpu.name << " has more points than " << you.name << " without busting. " << you.name << " lost." << endl;
                break;
            }
            if (cpu.points > 21 && you.points <= 21) {
                you.win(wager);
                cout << cpu.name << " busted. " << you.name << " won." << endl;
                break;
            }
            if (cpu.points > 21 && you.points > 21) {
                you.lose(wager);
                cout << "Both players busted." << endl;
                break;
            }
            if (cpu.points == you.points && cpu.points <= 21 && you.points <= 21) {
                cout << "Push. No money is won or lost." << endl;
                break;
            }
        }
        
        cout << endl;
        cout << "You now have $" << you.money << '.' << endl;
        
        if (you.money == 0) {
            break;
        }
        
        cout << "Do you want to keep playing? Type 'Y' for yes, 'N' for no: ";
        cin >> play;
        play = tolower(play);
        while (tolower(play) != 'y' && tolower(play) != 'n') {
            cout << "Please enter a valid play." << endl;
            cout << "Do you want to keep playing? Type 'Y' for yes, 'N' for no: ";
            cin >> play;
            if (tolower(play) == 'y' || tolower(play) == 'n') {
                break;
            }
        }
        cin.ignore(10000, '\n');
        if (tolower(play) == 'y') {
            you.returnToPile(pile.deck);
            cpu.returnToPile(pile.deck);
            pile.shuffle();
            cout << endl;
            continue;
        }
        else {
            break;
        }
    }
    
    cout << "Game over!" << endl;
    if (you.money == 0) {
        cout << you.name << " lost everything." << endl;
    }
    else {
        cout << you.name << " ended with $" << you.money << "." << endl;
    }

    //OFSTREAM
	ofstream writer;
	writer.open("game-log.txt", ios::app);

	writer << you.name << " ended with $" << you.money << "." << endl;
    writer << setfill('-') << setw(25) << "" << endl;

    writer.close();

    //IFSTREAM
    int userChoice;
    cout << "Here are your options." << endl;
    cout << "\t1. See all the game logs" << endl;
    cout << "\t2. Exit" << endl << endl;

    cout << "Enter your choice: ";
    cin >> userChoice;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');

		cout << "Enter your choice: ";
		cin >> userChoice;
    }

    if (userChoice == 1) {
    	ifstream reader;
    	reader.open("game-log.txt");
    	string data;
    	while (!reader.eof()) {
    		getline(reader, data);
    		cout << data << endl;
    	}
    	reader.close();
    }
    else if (userChoice == 2) {
    	cout << "Goodbye!" << endl;
    }



    // terminate
    return 0;
}


