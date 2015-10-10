#include <vector>
using namespace std;
#include "fin_recipes.h"

double term_structure_yield_linearly_interpolated(const double& time, 
						  const vector<double>& obs_times, 
						  const vector<double>& obs_yields) {
    // assume the yields are in increasing time to maturity order.
    int no_obs = obs_times.size();
    if (no_obs<1) return 0;
    double t_min = obs_times[0];
    if (time <= t_min) return obs_yields[0];  // earlier than lowest obs.

    double t_max = obs_times[no_obs-1];  
    if (time >= t_max) return obs_yields[no_obs-1]; // later than latest obs

    int t=1;  // find which two observations we are between
    while ( (t<no_obs) && (time>obs_times[t])) 	{ ++t; }; 
    double lambda = (obs_times[t]-time)/(obs_times[t]-obs_times[t-1]);
    // by ordering assumption, time is  between t-1,t
    double r = obs_yields[t-1] * lambda + obs_yields[t] * (1.0-lambda); 
    return r;
};
