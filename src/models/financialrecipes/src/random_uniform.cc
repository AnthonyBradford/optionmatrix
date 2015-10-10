#include <cstdlib>
using namespace std;

double random_uniform_0_1(void){
    return double(rand())/double(RAND_MAX); // this uses the C library random number generator. 
};
