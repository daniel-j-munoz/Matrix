#include <iostream> 
using namespace std;
class Tree {


    public: 

        // apex/top of tree
        string node; // variable, operators or number. 
        // e.g. +, -, *, /, x, y, z ..., 1, 2, 3 ...

        Tree* alpha;
        Tree* beta;

        Tree();
        void read(string text);


        Tree combine(Tree other, string s);
        Tree operator+(Tree other);
        Tree operator-(Tree other);
        Tree operator*(Tree other);
        Tree operator/(Tree other);

        Tree operator+=(Tree other);
        Tree operator-=(Tree other);
        Tree operator*=(Tree other);
        Tree operator/=(Tree other);


        int at(vector<int> shell, vector<int> point); 



        void print();
        string get_string(string s);
};