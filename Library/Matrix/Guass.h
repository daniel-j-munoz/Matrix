#include "Matrix.h"
class Guass{



    public: 
        static void swap_row(int a, int b, Matrix* A);

        static void swap_col(int a, int b, Matrix* A);
        static void scale_row(int m, float scale, Matrix* A);
        /** e.g. row_a + scale * row_b **/
        static void row_plus(int a, float scale, int b, Matrix* A);

};