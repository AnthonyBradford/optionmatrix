#include "fin_recipes.h"

class time_contingent_cash_flows{
public:
    vector<double> times;
    vector<double> cash_flows;
    time_contingent_cash_flows(const vector<double>& in_times, const vector<double>& in_cflows){
	times=in_times;	cash_flows=in_cflows;
    };
    int no_cflows(){ return times.size(); };
};

vector<time_contingent_cash_flows> 
build_time_series_of_bond_time_contingent_cash_flows(const vector<double>& initial_times,
						     const vector<double>& initial_cflows){
    vector<time_contingent_cash_flows> vec_cf;
    vector<double> times  = initial_times;
    vector<double> cflows = initial_cflows;
    while (times.size()>0){
	vec_cf.push_back(time_contingent_cash_flows(times,cflows));
	vector<double> tmp_times;
	vector<double> tmp_cflows;
	for (int i=0;i<times.size();++i){
	    if (times[i]-1.0>=0.0) {
		tmp_times.push_back(times[i]-1);  
		tmp_cflows.push_back(cflows[i]);
	    };
	};
	times  = tmp_times;  cflows = tmp_cflows;
    };
    return vec_cf;
};
						
double price_european_call_option_on_bond_using_ho_lee(term_structure_class* initial, const double& delta, const double& pi,
						       const vector<double>& underlying_bond_cflow_times,
						       const vector<double>& underlying_bond_cflows,
						       const double& K, const double& time_to_maturity){
    int T = int(time_to_maturity+0.0001);
    vector<vector<term_structure_class_ho_lee> > hl_tree 
	= term_structure_ho_lee_build_term_structure_tree(initial,T+1,delta,pi);
    vector<time_contingent_cash_flows> vec_cf 
	= build_time_series_of_bond_time_contingent_cash_flows(underlying_bond_cflow_times, underlying_bond_cflows);

    vector<double> values(T+1);
    for (int i=0;i<=T;++i){
	values[i]=max(0.0,bonds_price(vec_cf[T+1].times, vec_cf[T+1].cash_flows, hl_tree[T+1][i]) - K);
    };
    for (int t=T;t>=0;--t){
	vector<double> values_this(t+1);
	for (int i=0;i<=t;++i){ values_this[i]=(pi*values[i+1]+(1.0-pi)*values[i])*hl_tree[t][i].d(1); };
	values=values_this;
    };
    return values[0];
};
