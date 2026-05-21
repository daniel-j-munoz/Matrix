#include <iostream> 
using namespace std;
#include <vector>
class Tree {

    // ln, exp 
    // cos, sin
    // ... ?...

    public: 
        string node; // variable, operators or number.    apex?.... other names?...
        vector<Tree*> trees; 
        Tree();

        vector<Tree*> sub_trees(vector<Tree*> trees);
        Tree partial(char letter);
        bool contains(Tree tree);



        void simplfy(); // simplfy emthod?....
        void identities(); // void or copy?...
        void times_one();
        void times_zero();
        void simplfy_arithmetic();
        void power_one();


        Tree combine(Tree other, string s);
        Tree operator+(Tree other);
        Tree operator-(Tree other);
        Tree operator*(Tree other);
        Tree operator/(Tree other);
        Tree operator^(Tree other);

        void operator+=(Tree other);
        void operator-=(Tree other);
        void operator*=(Tree other);
        void operator/=(Tree other);


        // ??....
        Tree unary_operator(string s);
        Tree cos();
        Tree sin();
        Tree tan();  
        Tree sec(); 
        Tree csc();
        Tree arccos();
        Tree arcsin(); 



        Tree ln();
        Tree exp();


        bool operator==(Tree other);
        


        void read(string text);
        int at(vector<int> shell, vector<int> point); 



        void print();
        string get_string(string s);

        bool is_number(string s);

};