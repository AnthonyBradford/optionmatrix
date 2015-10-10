#include <vector>
#include <cmath>
using namespace std;

double interest_rate_trees_gbm_value_of_cashflows(const vector<double>& cflow,
						  const vector< vector<double> >& r_tree,
						  const double& q){
    int n=cflow.size();
    vector< vector<double> > values(n);
    vector<double> value(n);
    for (int i=0;i<n;i++){ value[i]=cflow[n-1]; };
    values[n-1]=value; 
    for (int t=n-1;t>0;--t){
	vector<double> value(t,0.0);
	for (int i=0;i<t;++i){
	    value[i]=cflow[t-1]+exp(-r_tree[t-1][i])*(q*values[t][i]+(1-q)*values[t][i+1]);
	};
	values[t-1]=value;
    };
    return values[0][0];
};
