//Name: Leonardo Cebrero, Aziel Buenrostro, Darryl Racoma
//Date: 1/21/2025

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//creating constant arry values to initialize our cards
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

//initializing the deck array to have 0 to 51 cards in a deck
int DECK[52];
int currentCardIndex = 0;

//int variables to track wins, losses, and draws
int wins = 0;
int losses = 0;
int draws = 0;

//initialize deck
void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
}

//function to shuffle the deck every time program is run
void shuffleDeck() {
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}

//function to recieve card from deck
int dealCard() {
    return DECK[currentCardIndex++] % 13;
}
//function to determine the value of the cards, this returns a value
int cardValue(int card) {

    return card < 9 ? card + 2 : 10;

    if (card < 9){
        return card + 2;
    }
    else{
        if (card == 12){
            //return 1 or 11
        }
        else{
            return 10;
        }
    }
}

//function to deal the first two cards for player
int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);
}

//function to produce dealer's first card
int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1);
}

//function to add total amount of points from cards obtained
int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[newCard / 13] << endl;
            if (playerTotal >= 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

//function for dealer to play their turn; stops when dealer's total is 17 or above
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}
//function to check if the player total card value if its greater or less than the dealer value
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
        wins++;
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
        draws++;
    } else {
        cout << "Dealer wins!" << endl;
        losses++;
    }
}

int main() {
    
    string continueGame = "yes";
    while (continueGame != "no"){
        initializeDeck();
        shuffleDeck();
  
        int playerTotal = dealInitialPlayerCards();
        int dealerTotal = dealInitialDealerCards();
  
        playerTotal = playerTurn(playerTotal);
        if (playerTotal > 21) {
        cout << "You busted! Dealer wins." << endl;
        }
        dealerTotal = dealerTurn(dealerTotal);
        determineWinner(playerTotal, dealerTotal);

        //Asks user if they'd like to continue playing, modifies continueGame variable to check if game should be repeated
        cout << "Would you like to continue playing?" << endl;
        //cin >> continueGame;
        getline(cin, continueGame);
        while (continueGame != "yes" && continueGame != "no"){
             cout << "Please enter a valid input. (yes/no)" << endl;
             //cin >> continueGame;
             getline(cin, continueGame);

        }
    }
    
    //Print out final stats
    cout << "Here are your final stats. You had: " << endl << endl;
    cout << wins << " win(s), " << losses << " loss(es), " << "and " << draws << " draw(s)!" << endl;
    return 0;
}
