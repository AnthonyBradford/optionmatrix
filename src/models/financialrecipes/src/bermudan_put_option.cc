#include <cmath>                 // standard C mathematical library
#include <algorithm>             // defines the max() operator
#include <vector>                // STL vector templates
using namespace std;
    
double option_price_put_bermudan_binomial( const double& S, 
					   const double& X, 
					   const double& r, 
					   const double& q, 
					   const double& sigma,
					   const double& time,
					   const vector<double>& potential_exercise_times,
					   const int& steps) {
    double delta_t=time/steps;
    double R = exp(r*delta_t);       
    double Rinv = 1.0/R;                
    double u = exp(sigma*sqrt(delta_t));
    double uu = u*u;
    double d = 1.0/u;
    double p_up = (exp((r-q)*delta_t)-d)/(u-d);
    double p_down = 1.0-p_up; 
    vector<double> prices(steps+1);     
    vector<double> put_values(steps+1); 

    vector<int> potential_exercise_steps; // create list of steps at which exercise may happen
    for (int i=0;i<potential_exercise_times.size();++i){
	double t = potential_exercise_times[i];
	if ( (t>0.0)&&(t<time) ) {
	    potential_exercise_steps.push_back(int(t/delta_t));
	};
    };

    prices[0] = S*pow(d, steps);  // fill in the endnodes.
    for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];
    for (int i=0; i<=steps; ++i) put_values[i] = max(0.0, (X-prices[i])); // put payoffs at maturity
    for (int step=steps-1; step>=0; --step) {
	bool check_exercise_this_step=false;
	for (int j=0;j<potential_exercise_steps.size();++j){
	    if (step==potential_exercise_steps[j]) { check_exercise_this_step=true; };
	};
	for (int i=0; i<=step; ++i) {
	    put_values[i] = (p_up*put_values[i+1]+p_down*put_values[i])*Rinv;
	    prices[i] = d*prices[i+1]; 
	    if (check_exercise_this_step) put_values[i] = max(put_values[i],X-prices[i]);
	};
    };
    return put_values[0];
};
