#include <iostream> 
#include <vector>
using namespace std;

#pragma once
class Function {
    public: 
        float center;
        vector<float> values = {}; 
        Function(vector<float> values, float center); 
        float at(float input);



        // float nth_at(float nth, float value);
        // float synth_rem(float value);
        // Function synth_quot(float value);
        // Function derivative();





        // vector<vector<float>> sample(float a, float b, float delta);
        // void output_sample(float a, float b, float delta);
};