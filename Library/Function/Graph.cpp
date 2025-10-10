#include "Graph.h"
#include "../Matrix/Data.h"


// Graph Curve 
// Graph Points
// curve & points?
// color of curve and points?...

Graph::Graph(float WIDTH, float HEIGHT){
    this->WIDTH = WIDTH; 
    this->HEIGHT = HEIGHT;
    image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
}


void Graph::graph(Matrix data){
    layers.push_back(data);
}


void Graph::show(){
    float a = numeric_limits<float>::max();
    float b = numeric_limits<float>::min();
    float c = numeric_limits<float>::max();
    float d = numeric_limits<float>::min();

    for(Matrix layer : layers){
        Matrix x = layer.get_column(0);
        Matrix y = layer.get_column(1);

        a = min(a, Data::min(x)[0]);
        b = max(b, Data::max(x)[0]);
        c = min(c, Data::min(y)[0]);
        d = max(d, Data::max(y)[0]);
    }

    for(Matrix layer : layers){
        Matrix x = layer.get_column(0);
        Matrix y = layer.get_column(1);

        Data::range(a, b, 0, WIDTH, &x);
        Data::range(c, d, (3.0f / 4.0f) * HEIGHT, (1.0f / 4.0f) * HEIGHT, &y);

        // Plot Layer
        for(int i = 0; i < x.M; i++){
            circle(
                image, 
                Point(x.get(i, 0), y.get(i, 0)),
                5.0f, 
                Scalar(100, 100, 100),
                -1
            );

            // Line 
            if(!(i == x.M - 1)){
                line(
                    image, 
                    Point(x.get(i, 0), y.get(i, 0)), 
                    Point(x.get(i + 1, 0), y.get(i + 1, 0)), 
                    Scalar(100, 100, 100), 
                    1
                );
            }
        }
    }
    

    imshow("", image);
    waitKey(0);
}