#include <iostream> 
#include <vector>
#include "../Matrix/Matrix.h"
#include "Tensor.h"
using namespace std;
#include "Map.h"


// remainder? that way you don't have to return a vecgor of function?... 
// idk though....

#pragma once
// gcf, lcd,  etc etc...


// Ratio of Multivariate Polynomials



// partial fraction decomp?

class Function {
    public: 
        float center;
        // scale as well for input?... scale and center?..
        Tensor alpha = Tensor({0}); 
        Tensor beta = Tensor({1}, 1.0f); 
        

        Map<string, int> map; // e.g. {a, b, c} -> {0, 1, 2}


        static Tensor to_tensor(vector<float> data);

        // Single Variable...
        Function(vector<float> alpha); 
        Function(vector<float> alpha, float center); 
        Function(vector<float> alpha, vector<float> beta); 
        Function(vector<float> alpha, vector<float> beta, float center); 

        Function(Tensor alpha); 
        Function(Tensor alpha, float center); 
        Function(Tensor alpha, Tensor beta); 
        Function(Tensor alpha, Tensor beta, float center); 

        // Multivariable 
        Function(string alpha);
        Function(string alpha, float center);
        Function(string alpha, string beta); 
        Function(string alpha, string beta, float center); 






   
        
        
        // Arithmetic ....................
        Function operator+(Function f);
        Function operator-(Function f);
        static Tensor FOIL(Tensor a, Tensor b); // make private?...
        Function operator*(Function f);
        vector<Function> operator/(Function f);

        Function operator*(float scale); // void or copy?
        Function operator/(float scale);





        Function plus(Function function);






// power method?...
 // negative power means recriprocal(beta / alpha) then multiply & stuf....


        static float at(Tensor tensor, vector<float> x);
        float at(vector<float> x); 

        float slice(vector<float> point, vector<float> free); // kind of like cross section...
        // eveulate at points skipping the free variables. essentially kind of like given you subspace or cross section something like that....



        vector<Matrix> sample(vector<float> a, vector<float> b, vector<float> delta);

        float deg();
        float deg(int dim);

        float integrate(float a, float b);
        Function derivative();


        void rerank(int rank);

        // order swap, swtich?... permut?...
        void transpose(vector<float> swap);

        //compound operators? ... 

        
        // function that removes center by expanding out everything?...


        // factor things out method?.... like factor out a variable and stuf..
        // LCD? ... GCF?... factor out stuf?...

        // float nth_at(float nth, float value);
        // float synth_rem(float value);
        // Function synth_quot(float value);

        // integral function

        // limits? limit of infite?
        // e.g. 0, inf, or ratio of leading ceofficients



        // GCf of polynomial...
        // PFD...
        // factor. rewrite multi var poly as if was 




        // composite function?...
        // power function?...

        void print(int n);



        // vector<vector<float>> sample(float a, float b, float delta);
        // void output_sample(float a, float b, float delta);
};



// multibariable integral & functions etc etc?....