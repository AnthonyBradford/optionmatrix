double payoff_cash_or_nothing_call(const double& S, 
				   const double& K){
    if (S>=K) return 1;
    return 0;
};

double payoff_asset_or_nothing_call(const double& S, 
				    const double& K){
    if (S>=K) return S;
    return 0;
};
