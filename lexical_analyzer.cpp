
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

// Define token and character classes
enum CharClass { LETTER, DIGIT, UNKNOWN, END_OF_FILE = -1 };
enum TokenType {
    INT_LIT = 10, IDENT = 11,
    ASSIGN_OP = 20, ADD_OP = 21, SUB_OP = 22,
    MULT_OP = 23, DIV_OP = 24,
    LEFT_PAREN = 25, RIGHT_PAREN = 26
};

// Global variables
CharClass charClass;
string lexeme;
char nextChar;
int nextToken;
string input;
size_t inputIndex = 0;

// Function to add a character to the current lexeme
void addChar() {
    lexeme += nextChar;
}

// Function to get the next character from the input string and classify it
void getChar() {
    if (inputIndex < input.length()) {
        nextChar = input[inputIndex++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_FILE;
    }
}

// Function to skip whitespace
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

// Function to determine the token of symbols/operators
int lookup(char ch) {
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN;
    case ')': addChar(); return RIGHT_PAREN;
    case '+': addChar(); return ADD_OP;
    case '-': addChar(); return SUB_OP;
    case '*': addChar(); return MULT_OP;
    case '/': addChar(); return DIV_OP;
    default:  addChar(); return END_OF_FILE;
    }
}

// Function to convert token number to token name
string getTokenName(int token) {
    switch (token) {
    case INT_LIT: return "INT_LIT";
    case IDENT: return "IDENT";
    case ASSIGN_OP: return "ASSIGN_OP";
    case ADD_OP: return "ADD_OP";
    case SUB_OP: return "SUB_OP";
    case MULT_OP: return "MULT_OP";
    case DIV_OP: return "DIV_OP";
    case LEFT_PAREN: return "LEFT_PAREN";
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case END_OF_FILE: return "EOF";
    default: return "UNKNOWN";
    }
}

// The main lexical analyzer function
int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        nextToken = lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE:
        lexeme = "EOF";
        nextToken = END_OF_FILE;
        break;
    }
    cout << "Next token is: " << getTokenName(nextToken) << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

// Main program
int main() {
    cout << "Enter your input: ";
    getline(cin, input); // قراءة السطر بالكامل

    inputIndex = 0;
    getChar();
    do {
        lex();
    } while (nextToken != END_OF_FILE);

    return 0;
}
