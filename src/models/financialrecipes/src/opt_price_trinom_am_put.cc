#include <vector>
#include <cmath>
using namespace std;

double option_price_put_american_trinomial( const double& S,  
					    const double& K,  
					    const double& r,  
					    const double& q,
					    const double& sigma,
					    const double& t,    
					    const int& steps) { 
    double delta_t = t/steps;
    double Rinv = exp(-r*(delta_t));
    double sigma_sqr=pow(sigma,2);

    double u = exp(sigma*sqrt(3.0*delta_t)); 
    double d = 1.0/u;
    double p_u = 1.0/6.0 + sqrt(delta_t/(12.0*sigma_sqr)) * (r-q-0.5*sigma_sqr);
    double p_m = 2.0/3.0;
    double p_d = 1.0/6.0 - sqrt(delta_t/(12.0*sigma_sqr)) * (r-q-0.5*sigma_sqr);

    vector< vector<double> > Stree;       // price of underlying in a tree
    vector<double> Svec;
    Svec.push_back(S);
    for (int step=1;step<=steps;++step){ 
	Stree.push_back(Svec);
	Svec.insert(Svec.begin(),Svec[0]*d); // use the fact that only the extreme values change. 
	Svec.push_back(Svec[Svec.size()-1]*u);
    };
    int m = Svec.size();
    vector<double> values_next = vector<double>(m);       // value of option next step
    for (int i=0; i<m; ++i) values_next[i] = max(0.0, K-Svec[i]); // call payoffs at maturity
    vector<double> values;
    for (int step=steps-1; step>=0; --step) {
	m = Stree[step].size();	
	values = vector<double> (m);       // value of option
	for (int i=0; i<m; ++i) {
	    values[i] = (p_u*values_next[i+2]+p_m*values_next[i+1] + p_d*values_next[i])*Rinv;
	    values[i] = max(values[i],K-Stree[step][i]);       // check for exercise
	};
	values_next=values;
    };
    return values[0];
};
