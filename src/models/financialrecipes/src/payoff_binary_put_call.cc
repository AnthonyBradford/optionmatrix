double payoff_binary_call(const double& S, const double& K){
    if (S>=K) return 1;
    return 0;
};

double payoff_binary_put(const double& S, const double& K){
    if (S<=K) return 1;
    return 0;
};
