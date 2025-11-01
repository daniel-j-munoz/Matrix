#include <iostream> 
#include <vector>
using namespace std;
#include <map>


// name something else?.... 
// idk.... 

// more tailored for reading math expressions and stuf...
class Token {
 

    public: 
        static vector<char> alphabet;
        static map<char, int> axis;


        static int digits(string number);

        static bool is_operator(char character);
        static int precedence(char character);
        static int binary_operator(char operation, int a, int b);



        static deque<string> tokens(string text);
        static deque<string> shunting_yard(deque<string> tokens);

};