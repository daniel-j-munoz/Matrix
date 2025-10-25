// handle complex as well?...
// store complex #'s?.

class Q {

    public: 
        int alpha;
        int beta;

        // eta


        Q(int alpha, int beta);

        Q operator+(Q other);
        Q operator-(Q other);
        Q operator*(Q other);
        Q operator/(Q other);

        void operator+=(Q other);
        void operator-=(Q other);
        void operator*=(Q other);



        Q operator^(Q other);
        Q operator^(int z);

        Q operator*(int other);
        Q operator/(int other);


        void flip();
        
        static int lcm(int a, int b);
        static int gcd(int a, int b);

        // print?...

        void print();

};