/* FILE NAME: project4_kumar_szk0187.cpp
 * AUTHOR: Samarth Kumar
 * AU Username: szk0187
 * VERSION: 11/11/2021
 * COMPILE: g++ project4_kumar_szk0187.cpp 
 * RUN: ./a.out
 * 
 * Sarah Hardin helped me with the Ask/Add Question methods.
 * Parker Thompson helped me with formatting.
 */


//Libary imports.
# include <iostream>
# include <cstring>
# include <assert.h>
# include <cstdlib>
using namespace std;

// parameters
int num_of_questions;
int point_total = 0;


//Structure for creating a linked list that holds a trivia question,answer and point amount.
struct trivia_node {
    string question;
    string answer;
    int point;
    trivia_node *next;
};

//creates a pointer to trivia_node.
typedef trivia_node* ptr_node;


// Creating the linked list
class trivia_list
{
public:
	int count;
	trivia_node *head, *root;
	trivia_list()
	{
		count = 0;
		head = NULL;
		root = NULL;
	}
};
//initializes the quiz to have these three questions inputted into the linked list.
void init_question_list(ptr_node& q_list) {

    ptr_node cur_ptr = new trivia_node;

    // Question 1
    cur_ptr->question = "How long was the shortest war on record?";
    cur_ptr->answer = "38";
    cur_ptr->point = 100;
    cur_ptr->next = new trivia_node;
    q_list = cur_ptr;
    // Question 2
    cur_ptr = cur_ptr->next;
    cur_ptr->question = "What was Bank of America’s original name? (Hint: Bank of Italy or Bank of Germany)";
    cur_ptr->answer = "Bank of Italy";
    cur_ptr->point = 50;
    cur_ptr->next = new trivia_node;
    // Question 3
    cur_ptr = cur_ptr->next;
    cur_ptr->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
    cur_ptr->answer = "Wii Sports";
    cur_ptr->point = 20;
    cur_ptr->next = NULL;

    num_of_questions = 3;
}

//gives user the option to add a question to the linked list.
//question is added to the front of the linked list.
void add_question(ptr_node& q_list) {
    string answer;
    ptr_node new_ptr = new trivia_node;
    new_ptr->next = q_list;

    //gets question
    cout << "Enter a question: ";
    getline(cin, new_ptr->question);
    
    // gets answer
    cout << "Enter the answer: ";
    getline(cin, new_ptr->answer);

    // gets point value
    cout << "Enter the points: ";
    cin >> new_ptr->point;

    // adds question to front of linked list
    new_ptr->next = q_list;
    q_list = new_ptr;
    num_of_questions++;

}

//Checks for null value
//Ask the user trivia questions and starts the game
int ask_question(ptr_node q_list, int num_ask) {
    
    ptr_node cur_ptr = q_list;
    string user_answer;
    point_total = 0;
    
    // null list
    if (q_list == NULL) {
        return 0;
    } 
    // if there's no questions
    else if (num_ask < 1) {
        cout << "Warning - the number of trivia to be asked must equal to or be larger than 1.";
        return 1;
    }
    // if number of questions asked is greater than actual number 
    else if (num_of_questions < num_ask) {
        cout << "Warning - There is only " << num_of_questions << " trivia in the list.";
        return 1;
    }
    // if number of questions asked is less than or equal to actual number
    else {
        for(int x = 0; x < num_ask; x++) {
            cout << "Question: " << cur_ptr->question << endl;
            cout << "Answer: ";
            getline(cin, user_answer);
            // correct answer
            if (user_answer.compare(cur_ptr->answer) == 0) { 
                point_total += cur_ptr->point;
                cout << "Your answer is correct. You receive " << cur_ptr->point << " points." << endl;
                cout << "Your total points: " << point_total << "\n" << endl;
                cur_ptr = cur_ptr->next;
            }
            // wrong answer
            else {
                cout << "Your answer is wrong. The correct answer is: " << cur_ptr->answer << endl;
                cout << "Your total points: " << point_total << "\n" << endl;
                cur_ptr = cur_ptr->next;
            }
        }
    }
    return 0;
}
//Test cases to check whether the methods work.
void Unit_test() {
        ptr_node node_list = new trivia_node;
        init_question_list(node_list);

        cout << "***This is a Debugging Version ***" << endl;
        
        // Test Case 1
        cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
        int x = ask_question(node_list, 0);
        assert(x == 1);
        cout << "\nCase 1 Passed\n\n";
        
        // Test Case 2.1
        cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
        ask_question(node_list, 1);
        assert(point_total == 0);
        cout << "Case 2.1 passed\n\n";

        // Test Case 2.2
        cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters the correct answer." << endl;
        ask_question(node_list, 1);
        assert(point_total > 0);
        cout << "Case 2.2 passed\n\n";

        // Test Case 3 
        cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
        int asked = ask_question(node_list, 3);
        assert(asked == 0);
        cout << "Case 3 passed\n\n";

        // Test Case 4
        cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
        int y = ask_question(node_list, 5);
        assert(y == 1);
        cout << "\nCase 4 passed\n\n" ;

        cout << "*** End of the Debugging Version ***" << endl;
}

//creates two versions.

#define UNIT_TESTING
//#define trivia_quiz

int main() {
    // Unit_test();
    ptr_node node_list = new trivia_node;
    //Creates a new trivia game /
    //Sets up three original questions/
    //Sets up loop for user to input his or her own questions.
    //Quiz questions are stored in linked list.
    #ifdef trivia_quiz
        init_question_list(node_list);
    
        cout << "*** Welcome to Samarth's trivia quiz game ***\n";
        bool add_more = false;
        do {
            add_question(node_list);
            string response = "";
            cout << "Continue? (Yes/No): ";
            while (response == "") {
                getline(cin, response);
                if (response.compare("Yes") == 0 || response.compare("yes") == 0) {
                    add_more = true; 
                    cout << "\n";
                } else if (response.compare("No") == 0 || response.compare("no") == 0) {
                    add_more = false;
                    cout << "\n";
                } else {
                    cout << "";
                }
            }   
        } while (add_more);

        ask_question(node_list, num_of_questions);

        cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
        return 0;
    #endif

    //Method for testing
    #ifdef UNIT_TESTING
        Unit_test();
        return 0;

#endif
}



