
#include "../Matrix/Matrix.h"
#include <iostream>

class Graph {

    public: 
        float HEIGHT; 
        float WIDTH;
        Mat image;


        vector<float> point_size = {};
        vector<float> point_color = {};
        vector<float> curve_size = {};

        vector<Matrix> layers; 
        // vector<Matrix> layers_spatial;

        Graph(float WIDTH, float HEIGHT);


        // { N x 1, N x 1 }
        void graph(Matrix data); // or call add?...
        void show();
        



    // image 

    // other graph functions append stuff to this graph 
    // then you can call Graph::show() or Graph::display();
    // or Graph::write()// stroing graph image or something


    // maybe make graph objects
    // and you can add stuff to differnt graph objects?....




    // keep original data that is inputed into graph. 
    // then actually transform so that it fits onto graph.

    // every time new data is added to graph.
    // you find max left and right and transform everything to fit into graph
    // remmber to keep orgiinal data and spatial data 



    

};