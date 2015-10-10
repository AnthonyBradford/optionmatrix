#include <vector>
#include <cmath>
using namespace std;

double interest_rate_trees_gbm_value_of_callable_bond(const vector<double>& cflows,
						      const vector< vector<double> >& r_tree,
						      const double& q,
						      const int& first_call_time,
						      const double& call_price){
    int n=cflows.size();
    vector< vector<double> > values(n);
    vector<double> value(n);
    for (int i=0;i<n;i++){ value[i]=cflows[n-1]; };
    values[n-1]=value; 
    for (int t=n-1;t>0;--t){
	vector<double> value(t,0.0);
	for (int i=0;i<t;++i){
	    value[i]=cflows[t-1]+exp(-r_tree[t-1][i])*(q*values[t][i]+(1-q)*values[t][i+1]);
	    if (t>=first_call_time){ value[i]=min(value[i],call_price); };
	};
	values[t-1]=value;
    };
    return values[0][0];
};
