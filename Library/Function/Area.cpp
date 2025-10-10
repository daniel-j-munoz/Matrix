#include "Area.h"
#include "Interpolate.h"
#include "../Matrix/Data.h"

float Area::newton_cote(Matrix data, int n){
    Matrix x = data.get_column(0);
    Peice peice = Interpolate::peice_wise_lagrange(data, n);
    return peice.integrate(Data::min(x)[0], Data::max(x)[0]);
}