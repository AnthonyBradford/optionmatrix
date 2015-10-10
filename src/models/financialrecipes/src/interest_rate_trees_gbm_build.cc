#include <vector>
#include <cmath>
using namespace std;

vector<vector<double> > interest_rate_trees_gbm_build(const double& r0,
						      const double& u,
						      const double& d,
						      const int& n){
    vector< vector<double> > tree;
    vector<double> r(1); r[0]=r0; 
    tree.push_back(r);
    for (int i=1;i<=n;++i) {
	double rtop=r[r.size()-1]*u;
	for (int j=0;j<i;++j){
	    r[j] = d*r[j];
	};
	r.push_back(rtop);
	tree.push_back(r);
    };
    return tree;
};
