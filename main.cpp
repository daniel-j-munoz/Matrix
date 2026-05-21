#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


#include "Library/Function/Function.h"
#include "Library/Function/Tree.h"





int main(){


    
    Tree t;
    t.read("x^3 + 5 * x + x^2");
    Tree d = t.partial('x');
    d.simplfy();



    // vector<Tree*> trees = {};
    // trees = tree.sub_trees(trees);













    // doesnt read negative numbers. only reads subtracction.... 
    // as of now....
    // perhaps interpret negative numbers as subtraction operation?....
 

 














//    Function a({});
//     a += Monomial({21}, {5}, 1);
//     a += Monomial({21}, {4}, 1);
//     a += Monomial({21}, {3}, 10);
//     a += Monomial({21}, {2}, 12);
//     a += Monomial({21}, {1}, 25);
//     a += Monomial({21}, {0}, 35);

//     Function b({});
//     b += Monomial({21}, {3}, 1);
//     b += Monomial({21}, {2}, 1);
//     b += Monomial({21}, {1}, 5);
//     b += Monomial({21}, {0}, 7);

//     a.print();
//     b.print();

//     Function c = (a / b)[0];
//     cout << c.monomials.size();
//     // c.lexisort();
//     // c.print();


//     // x^2 + 5 no remainder....








    // Variable::create_map();


    // Sparse alpha;
    // alpha.add({0}, {0}, 5.0f); 
    // alpha.add({0}, {2}, -1.0f);
    // alpha.add({1}, {-1}, 1.0f);
    

    // vector<Function> beta;
    // Function f(alpha);

    // (f^3 * g^2).print(0);





    /**
     * 
     * Function alpha;
     * vector<Function> beta;
     * Function::PFD(alpha, beta)
     * 
     * PFD(){
     * 
     *      vector<Function> 
     *      
     * }
     * 
     * 
     */







    cout << "ahh";





    return 0;

}






    // polynomial w/ float as exponents?....
    // intersting...
// does foil handle negative exponents right?/...
