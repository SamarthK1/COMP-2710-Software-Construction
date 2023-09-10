/* FILE NAME: project3_kumar_szk0187.cpp
 * AUTHOR: Samarth Kumar
 * AU Username: szk0187
 * VERSION: 10/15/2021
 * COMPILE: g++ -std=c++11 project3_kumar_szk0187.cpp 
 * RUN: ./a.out
 * 
 * Discussed with Caleb Johnson on sorting concepts.
 * Parker Thompson helped me with the merge and sort.
 * I based my code outline off of the hints file provided by TA's.
 * 
 */


#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

/* global variables. */
const int MAX_SIZE = 100;

/* declare your user-defined functions */
bool check_file(string);

/* do not forget to describe each function */
vector<int> read_file(string);

/*
 * Using sorted vector values and putting them in a new file.
 *
 * Param: v1 Vector containing values to display. (vector<int>)
 * Param: v Vector containing values to display. (vector<int>)
 */
void write_file(string, vector<int>);

/*
 * Combining and sorting values of both vectors.
 *
 * Param: file Name of file to write. (string)
 * Param: v2 Vector containing values to display. (vector<int>)
 */
vector<int> merge(vector<int>, vector<int>);

/*
 * Merge the numbers in two specified files and write all the numbers
 * to a specified third file sorted in ascending order.
 *  
 * Return: 1 Program completed successfully. (int)
 */
int main() {
    /* Declare variables. */
    string file1;
    string file2;
    string file3;
    vector<int> numbers1(MAX_SIZE);
    vector<int> numbers2(MAX_SIZE);
    vector<int> numbers3(MAX_SIZE);


    cout << "*** Welcome to Samarth's sorting program *** \n";
    
    /* Get name of first input file. */
    do {
        cout << "Enter the first input file name: ";
        cin >> file1;
    } while (cin.fail() || !check_file(file1));

    /* Reading file1. */
    numbers1 = read_file(file1);
    
    /* Outputting vector from file1. */
    cout << "The list of " << numbers1.size() << " numbers "
         << "in file " << file1 << " is:\n";
    for (int i = 0; i < numbers1.size(); i++) {
        cout << numbers1.at(i) << "\n";
    }
    cout << endl;

    /* Get name of second output file. */
    do {
        cout << "Enter the second input file name: ";
        cin >> file2;
    } while (cin.fail() || !check_file(file2));

    /* Reading file2. */
    numbers2 = read_file(file2);
    
    /* Outputting vector from file2. */
    cout << "The list of " << numbers2.size() << " numbers "
         << "in file " << file2 << " is:\n";
    for (int i = 0; i < numbers2.size(); i++) {
        cout << numbers2.at(i) << "\n";
    }
    cout << endl;

    /* Merging file1 and file2. */
    numbers3 = merge(numbers1, numbers2);
    
    /* Outputting sorted array from both file1 and file2. */
    cout << "The sorted list of " << numbers3.size() << " numbers is: ";
    for (int i = 0; i < numbers3.size(); i++) {
        cout << numbers3.at(i) << " ";
    }
    cout << endl;

    /* Get name of output file. */
    do {
        cout << "Enter the output file name: ";
        cin >> file3;
    } while (cin.fail());


    /* Write output file. */
    write_file(file3, numbers3);

    cout << "*** Goodbye. ***";
    return 0;
}

bool check_file(string file) {
    /* Input file stream. (ifstream) */
    ifstream stream;

    /* Check whether file exists. */
    stream.open(file.c_str());
    if(stream.fail()) {
        cout << "File does not exist.";
        return false;
    }
    stream.close();
    return true;
}

vector<int> read_file(string file) {
    /* Input file stream. (ifstream) */
    ifstream stream;
    
    /* Vector containing numbers from file. (vector<int>) */
    vector<int> v;
    
    /* Integer read from file. (int) */
    int i;

    /* Add each number in the file to a vector. */
    stream.open(file);
    while(!stream.eof()){
        stream >> i;
        v.push_back(i);
    }
    stream.close();
    return v; 
}

void write_file(string file, vector<int> v) {
    /* Output file stream. (ofstream) */
    ofstream stream;

    /* Putting values into the output file. */
    stream.open((char*)file.c_str());
    for (int i = 0; i < v.size(); i++) {
        stream << v.at(i) << "\n";
    }
    stream.close();

    cout << "*** Please check the new file - " << file << " ***\n";
}

vector<int> merge(vector<int> v1, vector<int> v2) {
    //variables 
    vector<int> merged_vector;
    unsigned short a, b;

    /* Comparing both vectors. */
    while (v1.size() > 0 && v2.size() > 0) {
        if (v1.at(0) < v2.at(0)) {
            merged_vector.push_back(v1.at(0));
            v1.erase(v1.begin());
        } else {
            merged_vector.push_back(v2.at(0));
            v2.erase(v2.begin());
        }
    }

    /* Adding remaining numbers from vector 1. */
    if (v1.size() > 0) {
        a = v1.size();
        for (int i = 0; i < a; i++) {
            merged_vector.push_back(v1.at(0));
            v1.erase(v1.begin());
        }
    }

    /* Adding remaining numbers from vector 2. */
    if (v2.size() > 0) {
        b = v2.size();
        for (int i = 0; i < b; i++) {
            merged_vector.push_back(v2.at(0));
            v2.erase(v2.begin());
        }
    }
    /* Return the new vector. */
    return merged_vector;
}

