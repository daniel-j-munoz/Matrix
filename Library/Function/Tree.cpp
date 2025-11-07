#include "Tree.h"

#include <vector>
#include <map>
#include <string>

#include "Token.h"

#include <deque>

Tree::Tree(){
    

}



// change partial name to wrt?....w
// e..g wrt()?...
Tree Tree::partial(Tree output, char letter){
    if(node[0] == letter){
        Tree tree;
        tree.node = "1";
        return tree;
    } else if(node[0] == '^'){
        Tree one;
        one.node = "1";

        Tree* a = trees[0];
        Tree* b = trees[1];

        Tree list;
        list.node = "+";

        Tree* left = new Tree;
        left->node = "*";
        left->trees.push_back(new Tree(*b)); // b
        left->trees.push_back(new Tree(a->partial(*a, letter))); // a'
        left->trees.push_back(new Tree(*a ^ (*b - one))); // a^(b - 1)
        
        Tree* right = new Tree;
        right->node = "*";
        right->trees.push_back(new Tree(b->partial(*b, letter))); // b'
        right->trees.push_back(new Tree(a->ln())); // ln(a)
        right->trees.push_back(new Tree(*a^*b)); // a^b

        list.trees.push_back(left);
        list.trees.push_back(right);
        
        return list;
    } else if(node[0] == '+'){ 
        Tree list;
        list.node = "+";
        for(Tree* tree : trees){
            list.trees.push_back(new Tree(tree->partial(*tree, letter)));
        }
        return list;
    } else if(node[0] == '-'){
        Tree list;
        list.node = "-";
        for(Tree* tree : trees){
            list.trees.push_back(new Tree(tree->partial(*tree, letter)));
        }
        return list;
    } else if(node[0] == '*'){
        // e.g. (abcd...)' = a'bcd + ab'cd + abc'd + abcd' ...
        Tree list;
        list.node = "+";
        for(int i = 0; i < trees.size(); i++){
            Tree product;
            product.node = "*";
            for(int j = 0; j < trees.size(); j++){
                if(i == j){
                    product.trees.push_back(new Tree(trees[j]->partial(*trees[j], letter)));
                } else {
                    product.trees.push_back(new Tree(*trees[j]));
                }
            }
            list.trees.push_back(new Tree(product));
        }
        return list;
    } else {
        Tree tree;
        tree.node = "0";
        return tree;
    } 
}

void Tree::simplfy(){

    simplfy_arithmetic();
    times_zero();
    identities();
    power_one();



    
}

void Tree::simplfy_arithmetic(){
    if(trees.size() == 0){
        return;
    } else {

        bool numbers = true;
        for(Tree* tree : trees){
            tree->simplfy_arithmetic();
            if(!is_number(tree->node)){
                numbers = false;
            }
        }

        // + - * / ^
        if(numbers && (node == "+" || node == "-" || node == "*" || node == "/" || node == "^")){
            int value = stoi(trees[0]->node);
            for(int i = 1; i < trees.size(); i++){
                if(node == "+"){
                    value += stoi(trees[i]->node);
                } else if(node == "-"){
                    value -= stoi(trees[i]->node);
                } else if(node == "*"){
                    value *= stoi(trees[i]->node);
                } else if(node == "/"){
                    value /= stoi(trees[i]->node);
                } else {
                    value = pow(value, stoi(trees[i]->node));
                }
            }

            node = to_string(value);
            trees = {};
        } 


    }
}

void Tree::power_one(){
    if(trees.size() == 0){
        return;
    } else {
        for(Tree* tree : trees){
            tree->power_one();
        }

        if(node == "^" && trees[1]->node == "1"){
            node = trees[0]->node;
            trees = trees[0]->trees;
        }
    }
}



void Tree::identities(){
    if(trees.size() == 0){
        return;
    } else {
        for(Tree* tree : trees){
            tree->identities();
        }

        if(node == "+" || node == "*"){
            for(int i = 0; i < trees.size();){
                if(
                    (node == "+" && trees[i]->node == "0") || 
                    (node == "*" && trees[i]->node == "1")
                    // || (node == "^" && trees[i]->node == "1") // but i belive 1 has to be on right hand side...
                ){
                    trees.erase(trees.begin() + i);
                } else {
                    i++;
                }
            }

            if(trees.size() == 1){
                node = trees.back()->node;
                trees = trees.back()->trees;
            }
        }
    }
}

void Tree::times_zero(){
    if(trees.size() == 0){
        return;
    } else {
        if(node == "*"){
            for(int i = 0; i < trees.size(); i++){
                if(trees[i]->node == "0"){
                    node = "0";
                    trees = {};
                    return;
                }
            }
        }

        for(Tree* tree : trees){
            tree->times_zero();
        }
    }
}



Tree Tree::unary_operator(string s){
    Tree tree;
    tree.node = s;
    tree.trees.push_back(new Tree(*this));
    return tree;
}


Tree Tree::ln(){
   return unary_operator("ln");
}

Tree Tree::cos(){
   return unary_operator("cos");
}






vector<Tree*> Tree::sub_trees(vector<Tree*> list){
    if(trees.size() == 0){
        list.push_back(new Tree(*this));
        return list;
    } else {
        for(Tree* tree : trees){
            vector<Tree*> subtrees = tree->sub_trees(trees);
            while(subtrees.size() > 0){
                list.push_back(subtrees.back());
                subtrees.pop_back();
            }
        }

        list.push_back(new Tree(*this));
        return list;
    }
}


bool Tree::contains(Tree tree){
    vector<Tree*> list = {};
    list = sub_trees(list);
    for(Tree* x : list){
        if(tree == *x){
            return true;
        }
    }
    return false;
}





bool Tree::operator==(Tree other){

    // how to compare?...
    // simply traverse tree?...
    // and compare?...
}









Tree Tree::combine(Tree other, string s){
    Tree output;    
    output.node = s;
    output.trees.push_back(new Tree(*this));
    output.trees.push_back(new Tree(other));
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
Tree Tree::operator^(Tree other){
    return combine(other, "^");
}

void Tree::operator+=(Tree other){
    *this = *this + other;
}
void Tree::operator-=(Tree other){
    *this = *this - other;
}
void Tree::operator*=(Tree other){
    *this = *this * other;
}
void Tree::operator/=(Tree other){
    *this = *this / other;
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
                output[i]->trees.size() == 0
            ){
                Tree* tree = new Tree();
                tree->node = output[i]->node; // Operator
                tree->trees.push_back(output[i - 2]); // alpha
                tree->trees.push_back(output[i - 1]); // beta

                output.erase(output.begin() + i - 2);
                output.erase(output.begin() + i - 2);
                output[i - 2] = tree;
                break; 
            }
        }
    }

    *this = *output[0];
}




// int Tree::at(vector<int> shell, vector<int> point){
//     if(alpha == nullptr && beta == nullptr){
//         if(isnumber(node[0])){
//             return stoi(node);
//         } else {
//             for(int i = 0; i < shell.size(); i++){
//                 if(Token::axis[node[0]] == shell[i]){
//                     return point[i];
//                 }
//             }
//         }
//     } else {
//         int a = alpha->at(shell, point);
//         int b = beta->at(shell, point);
//         return Token::binary_operator(node[0], a, b); 
//     }
// }
// // other way w/ out just recursion?... idk...




// int get_precedence(char op){
//     if(op == '+' || op == '-') return 1;
//     if(op == '*' || op == '/') return 2;
//     if(op == '^') return 3;
//     return -1;  // Not an operator
// }

// // Helper function to check operator precedence
// bool has_lower_precedence(char op, char reference){
//     int prec_op = get_precedence(op);
//     int prec_ref = get_precedence(reference);
//     return prec_op < prec_ref && prec_op != -1;  // -1 means not an operator
// }

// bool has_lower_or_equal_precedence(char op, char reference){
//     int prec_op = get_precedence(op);
//     int prec_ref = get_precedence(reference);
//     return prec_op <= prec_ref && prec_op != -1;
// }

// string Tree::get_string(string s){
//     if(alpha == nullptr && beta == nullptr){
//         s += node;
//         return s;
//     } else {
//         string a = alpha->get_string("");
//         string b = beta->get_string("");

//         if(Token::is_operator(node[0])){
//             if(node[0] == '+'){
//                 s += a + " + " + b;
//             } else if(node[0] == '-'){
//                 s += a + " - ";
//                 // Only add parentheses if right side has lower precedence (+ or -)
//                 if(has_lower_precedence(beta->node[0], '-')){
//                     s += "(" + b + ")";
//                 } else {
//                     s += b;
//                 }
//             } else if(node[0] == '*'){
//                 // Add parentheses around left if it contains + or -
//                 if(has_lower_precedence(alpha->node[0], '*')){
//                     a = "(" + a + ")";
//                 }
//                 // Add parentheses around right if it contains + or -
//                 if(has_lower_precedence(beta->node[0], '*')){
//                     b = "(" + b + ")";
//                 }
//                 s += a + b;  // Implicit multiplication (no * symbol)
//             } else if(node[0] == '/'){
//                 // Add parentheses around left if it contains + or -
//                 if(has_lower_precedence(alpha->node[0], '/')){
//                     a = "(" + a + ")";
//                 }
//                 // Add parentheses around right if it contains +, -, *, or /
//                 if(has_lower_or_equal_precedence(beta->node[0], '/')){
//                     b = "(" + b + ")";
//                 }
//                 s += a + " / " + b;
//             } else if(node[0] == '^'){
//                 // Add parentheses around left if it's not a leaf or simple term
//                 if(alpha->alpha != nullptr || alpha->beta != nullptr){
//                     a = "(" + a + ")";
//                 }
//                 // Add parentheses around right if it contains operators
//                 if(beta->alpha != nullptr || beta->beta != nullptr){
//                     b = "(" + b + ")";
//                 }
//                 s += a + "^" + b;
//             }
//         }

//         return s;
//     }
// }


// void Tree::print(){
//     cout << get_string("") << "\n\n";
// }


















// Tree one;
//         one.node = "1";

//         Tree* a = trees[0];
//         Tree* b = trees[1];

//         // Create (b - 1) as a tree
//         Tree b_minus_one;
//         b_minus_one.node = "-";
//         b_minus_one.trees.push_back(new Tree(*b));
//         b_minus_one.trees.push_back(new Tree(one));

//         // Derivative: b * a^(b-1) * a' + b' * a^b * ln(a)
//         Tree list;
//         list.node = "+";
        
//         // First term: b * a^(b-1) * a'
//         Tree term1;
//         term1.node = "*";
//         term1.trees.push_back(new Tree(*b));
        
//         Tree a_power;
//         a_power.node = "^";
//         a_power.trees.push_back(new Tree(*a));
//         a_power.trees.push_back(new Tree(b_minus_one));
//         term1.trees.push_back(new Tree(a_power));
        
//         term1.trees.push_back(new Tree(a->partial(*a, letter)));
        
//         list.trees.push_back(new Tree(term1));
        
//         // Second term: b' * a^b * ln(a)
//         Tree term2;
//         term2.node = "*";
//         term2.trees.push_back(new Tree(b->partial(*b, letter)));
        
//         Tree a_power_b;
//         a_power_b.node = "^";
//         a_power_b.trees.push_back(new Tree(*a));
//         a_power_b.trees.push_back(new Tree(*b));
//         term2.trees.push_back(new Tree(a_power_b));
        
//         term2.trees.push_back(new Tree(a->ln()));
        
//         list.trees.push_back(new Tree(term2));
        
//         return list;




bool Tree::is_number(string s){
    if (s.empty()) return false;

    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }

    return true;

}