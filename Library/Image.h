// #include "Matrix.h"

// class Image {
//     // birghtness and contrast method.
//     // really just scale and add
//     // but convenint name methods

//     public: 

//         static bool valid_path(string path);

//         static Matrix get_grayscale_channel(string& path);


//         // coefficents argument for rgb? 
//         static Matrix gray_scale(vector<Matrix*> channels);

//         // goes BGR ? 0, 1, 2?
//         static vector<Matrix*> get_channels(string& path);

//         static Mat merge_channels(vector<Matrix*>& channels);

//         /**
//          * @param size Reduces the quality of image and template to increase speed of conovlution. at the expense of a less accurate answer. 10 is usually a good size
//          */
//         static vector<int> find_template(Matrix image, Matrix temp, int value);


//         static void display_gradients(Matrix* image, int space, int length);
//         /**
//          * near mult to left 
//          */
//         static int near_mult(int value, int n);
//         static int near_pow(int value, int base);
// };

// // implemenet FFT2D now that we can pixalte/meanpool the image basically. 
