#include <cmath>
#include <cstdlib>
using namespace std;

double random_uniform_0_1(void);

double random_normal(void){
    double U1, U2, V1, V2;
    double S=2;
    while (S>=1) {
	U1 = random_uniform_0_1();
	U2 = random_uniform_0_1();
	V1 = 2.0*U1-1.0;
	V2 = 2.0*U2-1.0;
	S = pow(V1,2)+pow(V2,2);
    };
    double X1=V1*sqrt((-2.0*log(S))/S);
    return X1;
};
