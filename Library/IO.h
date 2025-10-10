// // input output




// void Matrix::load(string path){
//     ifstream in(path);
//     string text = string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
//     string number = "";

//     int m; 
//     int n; 
//     vector<float> imported_data = {}; 

//     // Read Data
//     int count = 0; 
//     for(char character : text){
//         if(character == ','){
//             if(count == 0){
//                 m = stoi(number); 
//                 number = "";
//                 count++;
//             } else if(count == 1){
//                 n = stoi(number); 
//                 number = "";
//                 count++;
//             } else {
//                 imported_data.push_back(stof(number));
//                 number = "";
//             }
//         } else {
//             number += character;
//         }
//     }

//     data = imported_data; 
//     M = m; 
//     N = n;
// }


// void Matrix::save(string path){
//     string csv; 
//     csv += to_string(M) + "," + to_string(N) + ","; 
//     for(int ith = 0; ith < data.size(); ith++){
//         csv += to_string(data[ith]) + ",";
//     }
//     ofstream out(path); 
//     if (out.is_open()) {
//         out << csv; 
//         out.close(); 
//     } else {
//         std::cerr << "Failed to open file for writing.\n";
//     }
// }


// void Matrix::save_as_image(string path, bool grayscale){
//     Matrix output = *this;
//     output.range(0.0f, 255.0f);
//     if(grayscale){
//         imwrite(path, output.to_mat());
//     }
// }

// Mat Matrix::to_mat() {
//     Mat mat(M, N, CV_32F, data.data());
//     mat.convertTo(mat, CV_8U);
//     return mat;
// }