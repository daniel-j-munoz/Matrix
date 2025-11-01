#include "Tree.h"

#include <vector>
#include <map>
#include <string>

#include "Token.h"

#include <deque>

Tree::Tree(){
    

}

void Tree::read(string text){
    deque<string> list = Token::shunting_yard(Token::tokens(text)); 

    deque<Tree*> output;
    for(string token : list){
        Tree* tree = new Tree();
        tree->node = token;
        output.push_back(tree);
    }

    // Evaluate 
    while(output.size() > 1){
        for(int i = 0; i < output.size(); i++){
            if(
                Token::is_operator(output[i]->node[0]) && 
                output[i]->alpha == nullptr && output[i]->beta == nullptr
            ){
                Tree* tree = new Tree();
                tree->node = output[i]->node; // Operator
                tree->alpha = output[i - 2]; // alpha
                tree->beta = output[i - 1]; // beta

                output.erase(output.begin() + i - 2);
                output.erase(output.begin() + i - 2);
                output[i - 2] = tree;
                break; 
            }
        }
    }

    *this = *output[0];
}









int Tree::at(vector<int> shell, vector<int> point){
    if(alpha == nullptr && beta == nullptr){
        if(isnumber(node[0])){
            return stoi(node);
        } else {
            for(int i = 0; i < shell.size(); i++){
                if(Token::axis[node[0]] == shell[i]){
                    return point[i];
                }
            }
        }
    } else {
        int a = alpha->at(shell, point);
        int b = beta->at(shell, point);
        return Token::binary_operator(node[0], a, b); 
    }
}
// other way w/ out just recursion?... idk...


Tree Tree::combine(Tree other, string s){
    Tree output;    
    output.node = s;
    output.alpha = new Tree(*this);
    output.beta = new Tree(other);
    return output;
}

Tree Tree::operator+(Tree other){
    return combine(other, "+");
}
Tree Tree::operator-(Tree other){
    return combine(other, "-");
}
Tree Tree::operator*(Tree other){
    return combine(other, "*");
}
Tree Tree::operator/(Tree other){
    return combine(other, "/");
}

Tree Tree::operator+=(Tree other){
    *this = *this + other;
}
Tree Tree::operator-=(Tree other){
    *this = *this - other;
}
Tree Tree::operator*=(Tree other){
    *this = *this * other;
}
Tree Tree::operator/=(Tree other){
    *this = *this / other;
}

























string Tree::get_string(string s){
    if(alpha == nullptr && beta == nullptr){
        s += node;
        return s;
    } else {
        string a = alpha->get_string(s);
        string b = beta->get_string(s);

        if(Token::is_operator(node[0])){
            if(node[0] == '+'){
                s += a + " + " + b;
            } else {
                
                // Operand 'a'
                s += "(" + a + ")";

                // Operation Symbol
                if(node[0] == '^'){
                    s += "^";
                } else if(node[0] == '-' || node[0] == '/'){
                    s += " " + node + " ";
                }

                // Operand 'b'
                s += "(" + b + ")";

            }
        }

        return s;
    }
}

void Tree::print(){
    cout << get_string("") << "\n\n";
}
