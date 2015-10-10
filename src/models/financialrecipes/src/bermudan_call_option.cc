#include <cmath> 
#include <vector>   
using namespace std;
    
double option_price_call_bermudan_binomial( const double& S, 
					    const double& K,   
					    const double& r,   
					    const double& q,   
					    const double& sigma,
					    const double& time, 
					    const vector<double>& potential_exercise_times,
					    const int& steps) { 
    double delta_t = time/steps;
    double R = exp(r*delta_t);            
    double Rinv = 1.0/R;                  
    double u = exp(sigma*sqrt(delta_t));  
    double uu = u*u;
    double d = 1.0/u;
    double p_up = (exp((r-q)*(delta_t))-d)/(u-d);
    double p_down = 1.0-p_up;
    vector<double> prices(steps+1);       
    vector<double> call_values(steps+1);  

    vector<int> potential_exercise_steps; // create list of steps at which exercise may happen
    for (int i=0;i<potential_exercise_times.size();++i){
	double t = potential_exercise_times[i];
	if ( (t>0.0)&&(t<time) ) {
	    potential_exercise_steps.push_back(int(t/delta_t));
	};
    };
    prices[0] = S*pow(d, steps);  // fill in the endnodes.
    for (int i=1; i<=steps; ++i) prices[i] = uu*prices[i-1];
    for (int i=0; i<=steps; ++i) call_values[i] = max(0.0, (prices[i]-K));
    for (int step=steps-1; step>=0; --step) {
	bool check_exercise_this_step=false;
	for (int j=0;j<potential_exercise_steps.size();++j){
	    if (step==potential_exercise_steps[j]) { check_exercise_this_step=true; };
	};
	for (int i=0; i<=step; ++i) {
	    call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
	    prices[i] = d*prices[i+1];
	    if (check_exercise_this_step) call_values[i] = max(call_values[i],prices[i]-K); 
	};
    };
    return call_values[0];
};
