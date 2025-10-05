
#include "Function.h"
#include "Matrix.h"

#pragma once
class Peice {

    public: 

        vector<Function> peices;
        vector<vector<float>> bounds; // inclusive 
        Peice();

        // add/append a peice wise function. ?
        // x^0, x^1, ...
        void append(vector<float> coefficents, float center, float a, float b);

        Matrix sample(float left, float right, float delta); 
        Matrix graph();
};



// or perhaps do vector<vector<float>>.  so each peicewise func can have their own bounds 
// and doesnt nesseracily have to be connected and stuff.


// overlapping bounds?... what might happen then?....
// im not sure...