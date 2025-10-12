#include <iostream> 
#include <vector>
#include "../Matrix/Matrix.h"
using namespace std;

#pragma once

// Function is now rational function. one polynomial over the other 
// alpha/beta, p/q 
// if regular polynomial beta is simply one;

// partial fraction decomp?

// now i belive we have to genralize methods given our beta now...

class Function {
    public: 
        float center;
        // scale as well for input?... scale and center?..
        vector<float> alpha = {}; 
        vector<float> beta = {1.0f};
        

        // limits? limit of infite?
        // e.g. 0, inf, or ratio of leading ceofficients


        Function(vector<float> alpha); 
        Function(vector<float> alpha, float center); 
        Function(vector<float> alpha, vector<float> beta); 
        Function(vector<float> alpha, vector<float> beta, float center); 
        float at(float input);
        Matrix sample(float left, float right, float delta);

        float deg();

        float integrate(float a, float b);
        Function derivative();

        Function operator*(Function f);
        vector<Function> operator/(Function f);
        Function operator+(Function f);
        Function operator-(Function f);
        Function& operator-=(Function f);


        Function operator*(float scale); // void or copy?
        Function operator/(float scale);
        Function& operator*=(float scale);
        Function& operator/=(float scale);
        
        // function that removes center by expanding out everything?...


        // factor things out method?.... like factor out a variable and stuf..
        // LCD? ... GCF?... factor out stuf?...

        // float nth_at(float nth, float value);
        // float synth_rem(float value);
        // Function synth_quot(float value);

        // integral function


        // composite function?...
        // power function?...

        void print(int n);


        // vector<vector<float>> sample(float a, float b, float delta);
        // void output_sample(float a, float b, float delta);
};



// multibariable integral & functions etc etc?....