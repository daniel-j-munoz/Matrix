#include <iostream> 
#include <vector>
#include "../Matrix/Matrix.h"
using namespace std;

#pragma once
class Function {
    public: 
        float center;
        vector<float> values = {}; 


        Function(vector<float> values, float center); 
        float at(float input);
        Matrix sample(float left, float right, float delta);


        float integrate(float a, float b);
        // Function derivative();

        Function operator*(Function f);
        Function operator*(float scale); // void or copy?
        Function operator+(Function f);

        // function that removes center by expanding out everything?...


        // float nth_at(float nth, float value);
        // float synth_rem(float value);
        // Function synth_quot(float value);

        // integral function




        // vector<vector<float>> sample(float a, float b, float delta);
        // void output_sample(float a, float b, float delta);
};



// multibariable integral & functions etc etc?....