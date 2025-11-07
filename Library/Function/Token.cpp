#include "Token.h"
#include <algorithm>
#include <deque>


vector<char> Token::alphabet;
map<char, int> Token::axis;

vector<char> alphabet = { 
    'a', 'b', 'c', 'd', 'f', 
    'g', 'h', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'q',
    'r', 's', 't', 'u', 'v', 
    'w', 'x', 'y', 'z', 'A', 
    'B', 'C', 'D', 'E', 'F', 
    'G', 'H', 'I', 'J', 'K', 
    'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 
    'V', 'W', 'X', 'Y', 'Z'
};

map<char, int> axis = {
    {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'f', 4},
    {'g', 5}, {'h', 6}, {'j', 7}, {'k', 8}, {'l', 9},
    {'m', 10}, {'n', 11}, {'o', 12}, {'p', 13}, {'q', 14},
    {'r', 15}, {'s', 16}, {'t', 17}, {'u', 18}, {'v', 19},
    {'w', 20}, {'x', 21}, {'y', 22}, {'z', 23}, {'A', 24},
    {'B', 25}, {'C', 26}, {'D', 27}, {'E', 28}, {'F', 29},
    {'G', 30}, {'H', 31}, {'I', 32}, {'J', 33}, {'K', 34},
    {'L', 35}, {'M', 36}, {'N', 37}, {'O', 38}, {'P', 39},
    {'Q', 40}, {'R', 41}, {'S', 42}, {'T', 43}, {'U', 44},
    {'V', 45}, {'W', 46}, {'X', 47}, {'Y', 48}, {'Z', 49}
};

int Token::digits(string text){
    int count = 0;
    for (char c : text) {
        if (isdigit(static_cast<unsigned char>(c))) {
            count++;
        } else {
            return 0;
        }
    }
    return count;
}

bool Token::is_operator(char character){
    if(
        character == '*' || character == '/' || 
        character == '+' || character == '-' || 
        character == '^' || character == '(' ||
        character == ')'
    ){
        return true;
    } else {
        return false; 
    }
}

int Token::precedence(char character){
    switch(character){
        case '(': 
            return 5; 
            break; 
        case ')': 
            return 5; 
            break; 
        case '^': 
            return 4; 
            break; 
        case '*':
            return 3;
            break; 
        case '/': 
            return 2; 
            break; 
        case '+': 
            return 1; 
            break; 
        case '-': 
            return 0; 
            break;
    }

    return -1;
}


int Token::binary_operator(char operation, int a, int b){
    switch(operation){
        case '*':
            return a * b;
            break; 
        case '/': 
            return a / b; 
            break; 
        case '+': 
            return a + b; 
            break; 
        case '-': 
            return a - b; 
            break;
        case '^': 
            return pow(a, b);
            break;
    }
    throw invalid_argument("Invalid operator");
}

deque<string> Token::tokens(string text){
    deque<string> tokens = {};
    string number = ""; 
    for(char x : text){
        if(isnumber(x)){
            number += x; 
        } else if(isalpha(x) || Token::is_operator(x)){
            if(number.size() > 0){
                tokens.push_back(number);
            }
            tokens.push_back(string(1, x));
            number = "";
        }
    }

    if(number.size() > 0){
        tokens.push_back(number); 
    }

    return tokens;
}

deque<string> Token::shunting_yard(deque<string> tokens){
    deque<string> hold; 
    deque<string> output; 

    // Distribute into Hold & Output 
    for(string token : tokens){
        if(isnumber(token[0]) || isalpha(token[0])){
            output.push_back(token);
        } else if(is_operator(token[0])){
            if(token[0] == ')'){
                int x = hold.size() - 1;
                while(!(hold[x][0] == '(')){
                    output.push_back(hold.back()); 
                    hold.pop_back(); 
                    x--;
                }
                hold.pop_back(); 
            } else {
                while(hold.size() > 0 && precedence(token[0]) <= precedence(hold.back()[0])){
                    if(hold.back()[0] == '('){
                        break;
                    } else {
                        output.push_back(hold.back());
                        hold.pop_back(); 
                    }
                }
                hold.push_back(token);    
            }
        }
    }

    // Drain hold into output 
    while(hold.size() > 0){
        output.push_back(hold.back()); 
        hold.pop_back(); 
    }

    return output;
}