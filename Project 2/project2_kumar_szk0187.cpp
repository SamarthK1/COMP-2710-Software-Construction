/* FILE NAME: project2_kumar_szk0187.cpp
 * AUTHOR: Samarth Kumar
 * AU Username: szk0187
 * VERSION: 9/24/2021
 * COMPILE: g++ project2_kumar_szk0187.cpp 
 * RUN: ./a.out
 * 
 * Worked with Cole Rasmussen, Will McCrite, and Jake Creason to understand the overall objectives and requirements.
 * Parker Thompson helped me figure out how to use assert() for test drivers.
 * Caleb Johnson helped me compile and run in the AU Server as well as fix calculation errors.
 */


#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

// Constants: Aaron's, Bob's, Charlie's % Accuracy, and total number of duels
const double a_accuracy = 33.333;
const double b_accuracy = 50;
const double c_accuracy = 100;
const int TOTAL_RUNS = 10000;

// If the players are alive
bool aaron_a;
bool bob_a;
bool charlie_a;

// # Wins of Aaron, Bob, Charlie
int aaron_wins1 = 0;
int aaron_wins2 = 0;
int bob_wins = 0;
int charlie_wins = 0;

// Functions
bool at_least_two_alive(bool aaron_a, bool bob_a, bool charlie_a);
void Aaron_shoots1(bool& bob_a, bool& charlie_a);
void Bob_shoots(bool& aaron_a, bool& charlie_a);
void Charlie_shoots(bool& aaron_a, bool& bob_a);
void Aaron_shoots2(bool& bob_a, bool& charlie_a);
void Strategy_1(bool& aaron_a, bool& bob_a, bool& charlie_a);
void Strategy_2(bool& aaron_a, bool& bob_a, bool& charlie_a);
void Press_any_key(void);

// Test drivers
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

// Main Function - utilizing and testing the above functions
int main() {

    cout << "*** Welcome to Samarth's Duel Simulator ***\n";
    
    srand(time(0));

    test_at_least_two_alive();

    Press_any_key();
    test_Aaron_shoots1();

    Press_any_key();;
    test_Bob_shoots();
    
    Press_any_key();
    test_Charlie_shoots();
    
    Press_any_key();
    test_Aaron_shoots2();

    Press_any_key();

    //Starts Strategy 1 and runs 10,000 times
    cout << "\nReady to test strategy 1 (run 10000 times):\n";
    Press_any_key();

    for (int i = 0; i < TOTAL_RUNS; i++) {
        Strategy_1(aaron_a, bob_a, charlie_a);
        aaron_a = true;
        bob_a = true;
        charlie_a = true;
    }
    
    int strategy1;
    strategy1 = aaron_wins1;
    
    // Printing out Strategy 1 Results
    cout << "Aaron won " << strategy1 << "/" << TOTAL_RUNS 
         << " duels or " << (strategy1 / 100.0) << "%" 
         << endl;

    cout << "Bob won " << bob_wins << "/" << TOTAL_RUNS 
         << " duels or " << (bob_wins / 100.0) << "%" 
         << endl;
    
    cout << "Charlie won " << charlie_wins << "/" << TOTAL_RUNS 
         << " duels or " << (charlie_wins / 100.0) << "%" 
         << endl;
    
    // Resetting player wins
    aaron_wins1 = 0;
    bob_wins = 0;
    charlie_wins = 0;
    
    // Starts Strategy 2 and runs 10,000 times
    cout <<"\nReady to test strategy 2 (run 10000 times):\n";
    Press_any_key();
    
    for (int i = 0; i < TOTAL_RUNS; i++) {
        Strategy_2(aaron_a, bob_a, charlie_a);
        aaron_a = true;
        bob_a = true;
        charlie_a = true;
    }
    
    int strategy2;
    strategy2 = aaron_wins2;

    // Printing out Strategy 2 results
    cout << "Aaron won " << strategy2 << "/" << TOTAL_RUNS 
         << " duels or " << (strategy2 / 100.0) << "%" 
         << endl;

    cout << "Bob won " << bob_wins << "/" << TOTAL_RUNS 
         << " duels or " << (bob_wins / 100.0) << "%" 
         << endl;
    
    cout << "Charlie won " << charlie_wins << "/" << TOTAL_RUNS 
         << " duels or " << (charlie_wins / 100.0) << "%" 
         << endl;
    
    // Determining which of the two strategies is better based on Aaron's wins.
    if (strategy1 > strategy2) cout << "\nStrategy 1 is better than strategy 2.";
    else cout << "\nStrategy 2 is better than strategy 1.";
}

//press any key to continue
void Press_any_key(void) {
    cout << "Press any key to continue...\n";
    cin.get();
}

// -----------------Checks if at least two players are alive----------------------
bool at_least_two_alive(bool aaron_a, bool bob_a, bool charlie_a) {
    if ( (aaron_a && bob_a) || (aaron_a && charlie_a) || (bob_a && charlie_a) ) {
        return true;
    } else {
        return false;
    }
}

// -----------------Testing at least two alive-----------------------
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";
}

// -----------------Shoot methods-----------------------
// Aaron's shot in strategy 1
void Aaron_shoots1(bool& bob_a, bool& charlie_a) {
    int shootResult = rand() % 100;
    if (shootResult <= a_accuracy) {
        if (charlie_a) charlie_a = false;
        else bob_a = false;
    }
}

// Bob's shot
void Bob_shoots(bool& aaron_a, bool& charlie_a) {
    int shootResult = rand() % 100;
    if (shootResult <= b_accuracy) {
        if (charlie_a) charlie_a = false;
        else aaron_a = false;
    }
    
}

// Charlie's shot
void Charlie_shoots(bool& aaron_a, bool& bob_a) {
     if (bob_a) bob_a = false;
     else aaron_a = false;
}

// Aaron's shot in strategy 2
void Aaron_shoots2(bool& bob_a, bool& charlie_a) {
    if (!bob_a || !charlie_a) {
        int shootResult = rand() % 100;
        if (shootResult <= a_accuracy) {
            if (charlie_a) charlie_a = false;
            else bob_a = false;
        }
    }
}
// -----------------Testing the shoot methods -----------------------
// testing Aaron's shot in strategy 1
void test_Aaron_shoots1(void) {

    bool test_bob;
    bool test_charlie;

    cout << "Unit Testing 2: Function Aaron_shoots1(bob_a, charlie_a)\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    test_bob = true;
    test_charlie = true;
    Aaron_shoots1(test_bob, test_charlie);
    assert(true == test_bob);

    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    test_bob = false;
    test_charlie = true;
    Aaron_shoots1(test_bob, test_charlie);
    assert(false == test_bob);

    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    test_bob = true;
    test_charlie = false;
    Aaron_shoots1(test_bob, test_charlie);   
    assert(false == test_charlie);       
}


// testing Bob's shot
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(bob_a, charlie_a)\n";

    bool test_aaron;
    bool test_charlie;

    cout << "\tCase 1: Aaron alive, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
    test_aaron = true;
    test_charlie = true;
    assert(true == test_aaron);
    Bob_shoots(test_aaron, test_charlie);

    cout << "\tCase 2: Aaron dead, Charlie alive\n"
         << "\t\tBob is shooting at Charlie\n";
    test_aaron = false;
    test_charlie = true;
    assert(false == test_aaron);
    Bob_shoots(test_aaron, test_charlie);

    cout << "\tCase 3: Aaron alive, Charlie dead\n"
         << "\t\tBob is shooting at Aaron\n";
    test_aaron = true;
    test_charlie = false;
    assert(false == test_charlie);
    Bob_shoots(test_aaron, test_charlie);          
}


// testing Charlie's shot
void test_Charlie_shoots(void) {
    
    bool test_aaron;
    bool test_bob;
    
    cout << "Unit Testing 4: Function Charlie_shoots(aaron_a, bob_a)\n";

    cout << "\tCase 1: Aaron alive, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
    test_aaron = true;
    test_bob = true;
    assert(true == test_bob);
    Charlie_shoots(test_aaron, test_bob);

    aaron_a = false;
    bob_a = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n"
         << "\t\tCharlie is shooting at Bob\n";
    test_aaron = false;
    test_bob = true;
    assert(false == test_aaron);
    Charlie_shoots(test_aaron, test_bob);

    aaron_a = true;
    bob_a = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n"
         << "\t\tCharlie is shooting at Aaron\n";
    test_aaron = true;
    test_bob = false;
    assert(false == test_bob);
    Charlie_shoots(test_aaron, test_bob);          
}

// Testing Aaron's second shot
void test_Aaron_shoots2(void) {
    cout<< "Unit Testing 5: Function - Aaron_shoots2(bob_a, charlie_a)\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = false;
    charlie_a = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n"
         << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_a, charlie_a);

    bob_a = true;
    charlie_a = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n"
         << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots2(bob_a, charlie_a);
}
// -----------------Strategies 1 and 2-----------------------
// Strategy 1
void Strategy_1(bool& aaron_a, bool& bob_a, bool& charlie_a) {
    aaron_a = true;
    bob_a = true;
    charlie_a = true;
    while(at_least_two_alive(aaron_a, bob_a, charlie_a)) {
        if (aaron_a) Aaron_shoots1(bob_a, charlie_a);

        if (bob_a) Bob_shoots(aaron_a, charlie_a);

        if (charlie_a) Charlie_shoots(aaron_a, bob_a);
    }

    if (aaron_a) aaron_wins1++;
    if (bob_a) bob_wins++;
    if (charlie_a) charlie_wins++;

}

// Strategy 2
void Strategy_2(bool& aaron_a, bool& bob_a, bool& charlie_a) {
    aaron_a = true;
    bob_a = true;
    charlie_a = true;
    while(at_least_two_alive(aaron_a, bob_a, charlie_a)) {
        if (aaron_a) Aaron_shoots2(bob_a, charlie_a);

        if (bob_a) Bob_shoots(aaron_a, charlie_a);

        if (charlie_a) Charlie_shoots(aaron_a, bob_a);
    }

    if (aaron_a) aaron_wins2++;
    if (bob_a) bob_wins++;
    if (charlie_a) charlie_wins++;
}


