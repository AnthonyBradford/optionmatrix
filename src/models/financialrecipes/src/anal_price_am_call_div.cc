#include <cmath>
#include "normdist.h"  // define the normal distribution functions
#include "fin_recipes.h"  // the regular black sholes formula

double option_price_american_call_one_dividend(const double& S,
					       const double& K,
					       const double& r,
					       const double& sigma,
					       const double& tau,
					       const double& D1, 
					       const double& tau1){
   if (D1 <= K* (1.0-exp(-r*(tau-tau1)))) // check for no exercise
      return option_price_call_black_scholes(S-exp(-r*tau1)*D1,K,r,sigma,tau);
   const double ACCURACY = 1e-6;              // decrease this for more accuracy
   double sigma_sqr = sigma*sigma;
   double tau_sqrt = sqrt(tau);
   double tau1_sqrt = sqrt(tau1);
   double rho = - sqrt(tau1/tau);

   double S_bar = 0;  // first find the S_bar that solves c=S_bar+D1-K 
   double S_low=0;    // the simplest: binomial search
   double S_high=S;  // start by finding a very high S above S_bar
   double c = option_price_call_black_scholes(S_high,K,r,sigma,tau-tau1);
   double test = c-S_high-D1+K;
   while ( (test>0.0) && (S_high<=1e10) ) {
      S_high *= 2.0;
      c = option_price_call_black_scholes(S_high,K,r,sigma,tau-tau1);
      test = c-S_high-D1+K;
   };
   if (S_high>1e10) { // early exercise never optimal, find BS value
      return option_price_call_black_scholes(S-D1*exp(-r*tau1),K,r,sigma,tau);
   };
   S_bar = 0.5 * S_high;  // now find S_bar that solves c=S_bar-D+K
   c = option_price_call_black_scholes(S_bar,K,r,sigma,tau-tau1);
   test = c-S_bar-D1+K;
   while ( (fabs(test)>ACCURACY) && ((S_high-S_low)>ACCURACY) ) {
      if (test<0.0) { S_high = S_bar; }
      else { S_low = S_bar; };
      S_bar = 0.5 * (S_high + S_low);
      c = option_price_call_black_scholes(S_bar,K,r,sigma,tau-tau1);
      test = c-S_bar-D1+K;
   };
   double a1 =  (log((S-D1*exp(-r*tau1))/K) +( r+0.5*sigma_sqr)*tau) / (sigma*tau_sqrt);
   double a2 = a1 - sigma*tau_sqrt;
   double b1 = (log((S-D1*exp(-r*tau1))/S_bar)+(r+0.5*sigma_sqr)*tau1)/(sigma*tau1_sqrt);
   double b2 = b1 - sigma * tau1_sqrt;
   double C = (S-D1*exp(-r*tau1)) * N(b1) + (S-D1*exp(-r*tau1)) * N(a1,-b1,rho)
      - (K*exp(-r*tau))*N(a2,-b2,rho) - (K-D1)*exp(-r*tau1)*N(b2);
   return C;
};
