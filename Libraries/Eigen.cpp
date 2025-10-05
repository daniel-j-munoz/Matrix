#include "Eigen.h"
#include "Factor.h"


Matrix gershgorin_radii(Matrix A){
    vector<float> radii = {};

    for(int j = 0; j < A.M; j++){
        // Radius
        float sum = 0.0f;
        for(int i = 0; i < A.N; i++){
            if(!(i == j)){
                sum += abs(A.get(j, i));   // is abs working here...?...
            }
        }
        radii.push_back(sum);
    }

    return Matrix(radii.size(), 1, radii);
}

// you get a new matrix every iteration of QR algo. 
// perhaps we could graph the Greshgoni circles each iteration?.....
// perhaps ew could see circles converge and stuff


// better stopping criteria?..... 
// or convergence criteria?....

// say if it doesnt converge...??...
Matrix Eigen::QR(Matrix A){

    float thresh = 1e-1;
    Matrix past_A = A;

    for(int i = 0; i < 100; i++){
        A.print(4);
        cout << "\n";

        save_gershgorin(A, to_string(i) + ".png");

        vector<Matrix> QR = Factor::QR(A); // Use QR or HHQR?....
        Matrix Q = QR.at(0);
        Matrix R = QR.at(1);
        past_A = A;
        A = R * Q;

        if(gershgorin_radii(A).max() < thresh){
            cout << "converged\n";
            break;
        }
    }

    A.print(4);
    cout << "\n";
    save_gershgorin(A, "final.png");

    return A;
}


// ocnverges to one w/ hgihest absoolute eigenvalue?....
// converges to spectral radius basically...

// b is col vector. 
// if row just transpose. not big deal. 
// really just a convention. it could be a row vector as 
// well if im not mistaken

/**
 * @param b Intial Eigenvector Guess
 * Might converge to eigenvector associated w/ spectral radius
 */
Matrix Eigen::power(Matrix A, Matrix b){

    float tol = 1e-6; // e.g. [0.999999, 1.000001]
    Matrix past_b = b;
    b.unit_mag();
    b.print(2);
    cout << "\n";

    Matrix b_t = b.T();
    Matrix temp = A * b; 
    float lambda = b.dot(temp) / b.dot(b);
    cout << "λ ≈ " << to_string(lambda) << "\n\n";

    for(int i = 0; i < 10; i++){
        past_b = b; 

        // Eigen Vector
        b = A * b;
        b.unit_mag();
        b.print(2);
        cout << "\n";

        // Eigen Value. Rayleigh Quotient
        Matrix b_t = b.T();
        Matrix temp = A * b; 
        float lambda = b.dot(temp) / b.dot(b);
        cout << "λ ≈ " << to_string(lambda) << "\n\n";

        if(b.dot(past_b) <= 1.0f + tol && b.dot(past_b) >= 1.0f - tol){
            cout << "converged\n";
            break; 
        }

    }

    
    


    
    return b; 
}













        // if(
        //     past_b.dot(b) <= 1.0f + tol && 
        //     past_b.dot(b) >= 1.0f - tol
        // ){
        //     cout << "converged\n";
        //     break;
        // }








// complex valued Matrix?.....
// use complex rather than float?....
// make another matrix class for complex... im not sure....


// also display gerhsorin?....

/**
 * @param name e.g. "image.png"
 */
void Eigen::save_gershgorin(Matrix A, string name){
    float min_radius = 2.0f;

    int WIDTH = 500; 
    int HEIGHT = 500; 
    Mat image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3); // i switched width wnd height

    Matrix centers(A.M, 1);
    vector<float> radii = {};

    for(int j = 0; j < A.M; j++){
        // Center at jth diagonal
        float center = A.get(j, j);

        // Radius
        float sum = 0.0f;
        for(int i = 0; i < A.N; i++){
            if(!(i == j)){
                sum += abs(A.get(j, i));   // is abs working here...?...
            }
        }

        centers.set(j, 0, center);
        radii.push_back(sum);
    }

    centers.range(
        0 + radii.at(0), 
        WIDTH - radii.at(radii.size() - 1)
    );

    // Real Axis
    line(image, Point(0, HEIGHT / 2), Point(WIDTH, HEIGHT/2), Scalar(255, 255, 255), 1);

    // Gershgorin Circles
    int scale = 10;

    // Circle
    for(int i = 0; i < A.M; i++){
        circle(
            image, 
            Point(centers.get(i, 0), HEIGHT / 2), // Center
            scale * radii.at(i) + min_radius, // Radius
            Scalar(0, 255, 0), // Color
            -1 // Fill
        );
    }

    // Center
    for(int i = 0; i < A.M; i++){
        circle(
            image, 
            Point(centers.get(i, 0), HEIGHT / 2), // Center
            min_radius,
            Scalar(0, 0, 255), // Color
            -1 // Fill
        ); 
    }

    imwrite("gershgorin/" + name, image);
}

