#include <vector>
#include <cmath>
using namespace std;

vector< vector<double> > binomial_tree(const double& S0, 
				       const double& u, 
				       const double& d, 
				       const int& no_steps){
    vector< vector<double> > tree;
    for (int i=1;i<=no_steps;++i){
	vector<double> S(i);
	for (int j=0;j<i;++j){
	    S[j] = S0*pow(u,j)*pow(d,i-j-1);
	};
	tree.push_back(S);
    };
    return tree;
};
