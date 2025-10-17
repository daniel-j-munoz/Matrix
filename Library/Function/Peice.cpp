#include "Peice.h"


Peice::Peice(){

}

Matrix Peice::sample(float left, float right, float delta){
    int N = (right - left) / delta;
    Matrix output(N, 2, 0.0f);

    int index = 0;
    for(float x = left; x <= right; x += delta){
        // jth spline
        int j = 0;
        for(int k = 0; k < bounds.size(); k++){  
            if(x >= bounds[k][0] && x < bounds[k][1]){ 
                j = k;
                break;
            }
        }

        if(x < bounds[0][0]){
            j = 0;
        } else if(x >= bounds.back()[1]){
            j = bounds.size() - 1;
        };

        float y = peices[j].at({x});

        // Set Data
        output.set(index, 0, x); 
        output.set(index, 1, y);
        index++;
    }

    return output;
}

void Peice::append(vector<float> coe, float center, float a, float b){
    peices.push_back(Function(coe, center));
    bounds.push_back({a, b});
}

// float Peice::integrate(float a, float b){
//     int left = -1; 
//     int right = -1;
//     for(int i = 0; i < bounds.size(); i++){
//         if(a >= bounds[i][0] && a <= bounds[i][1]){
//             left = i;
//         }
        
//         if(b >= bounds[i][0] && b <= bounds[i][1]){
//             right = i;
//         }
        
//         if(!(left == -1) && !(right == -1)){
//             break;
//         }
//     }

//     float sum = 0.0f;
//     for(int i = left; i <= right; i++){
//         if(i == left){
//             sum += peices.at(i).integrate(a, bounds[i][1]);
//         } else if(i == right){
//             sum += peices.at(i).integrate(bounds[i][0], b);
//         } else {
//             sum += peices.at(i).integrate(bounds[i][0], bounds[i][1]);
//         }
//     }
//     return sum;
// }