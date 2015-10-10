#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double bond_option_price_call_zero_american_rendleman_bartter(const double& X,  
							      const double& option_maturity, 
							      const double& S, 
							      const double& M,    // term structure paramters
							      const double& interest, // current short interest rate
							      const double& bond_maturity, // time to maturity for underlying bond
							      const double& maturity_payment,
							      const int& no_steps) {     
    double delta_t = bond_maturity/no_steps;
 
    double u=exp(S*sqrt(delta_t));
    double d=1/u;
    double p_up = (exp(M*delta_t)-d)/(u-d);
    double p_down = 1.0-p_up;

    vector<double> r(no_steps+1);
    r[0]=interest*pow(d,no_steps);
    double uu=u*u;
    for (int i=1;i<=no_steps;++i){ r[i]=r[i-1]*uu;};
    vector<double> P(no_steps+1);
    for (int i=0;i<=no_steps;++i){ P[i] = maturity_payment; };
    int no_call_steps=int(no_steps*option_maturity/bond_maturity);
    for (int curr_step=no_steps;curr_step>no_call_steps;--curr_step) {
	for (int i=0;i<curr_step;i++) {
	    r[i] = r[i]*u;
	    P[i] = exp(-r[i]*delta_t)*(p_down*P[i]+p_up*P[i+1]); 
 	};
    };
    vector<double> C(no_call_steps+1);
    for (int i=0;i<=no_call_steps;++i){ C[i]=max(0.0,P[i]-X); };
    for (int curr_step=no_call_steps;curr_step>=0;--curr_step) {
	for (int i=0;i<curr_step;i++) {
	    r[i]  = r[i]*u;
	    P[i] = exp(-r[i]*delta_t)*(p_down*P[i]+p_up*P[i+1]); 
	    C[i]=max(P[i]-X, exp(-r[i]*delta_t)*(p_up*C[i+1]+p_down*C[i]));
 	};
    };
    return C[0];
};
