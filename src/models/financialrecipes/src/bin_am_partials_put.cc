// file bin_am_partials_put.cc
// author: Bernt A Odegaard

#include <cmath>
#include <algorithm>
#include <vector> 
#include "fin_recipes.h"

void option_price_partials_american_put_binomial(const double& S,  // spot prices
						 const double& K,  // Exercise prices,
						 const double& r,     // interest rate
						 const double& sigma, // volatility
						 const double& time,  // time to maturity
						 const int& no_steps, // steps in binomial
						 double& delta, //  partial wrt S
						 double& gamma, //  second prt wrt S
						 double& theta, // partial wrt time
						 double& vega,  //  partial wrt sigma
						 double& rho){   // partial wrt r
   vector<double> prices(no_steps+1);
   vector<double> put_values(no_steps+1);
   double delta_t =(time/no_steps);
   double R = exp(r*delta_t);
   double Rinv = 1.0/R;
   double u = exp(sigma*sqrt(delta_t));
   double d = 1.0/u;
   double uu= u*u;
   double pUp   = (R-d)/(u-d);
   double pDown = 1.0 - pUp;
   prices[0] = S*pow(d, no_steps);
   int i;
   for (i=1; i<=no_steps; ++i) prices[i] = uu*prices[i-1];
   for (i=0; i<=no_steps; ++i) put_values[i] = max(0.0, (K-prices[i]));
   for (int CurrStep=no_steps-1 ; CurrStep>=2; --CurrStep){
      for (i=0; i<=CurrStep; ++i){
	 prices[i] = d*prices[i+1];
	 put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
	 put_values[i] = max(put_values[i], K-prices[i]); // check for exercise
      };
   }; 
   double f22 = put_values[2];
   double f21 = put_values[1];
   double f20 = put_values[0];
   for (i=0;i<=1;i++) {
      prices[i] = d*prices[i+1];
      put_values[i] = (pDown*put_values[i]+pUp*put_values[i+1])*Rinv;
      put_values[i] = max(put_values[i], K-prices[i]); // check for exercise
   };
   double f11 = put_values[1];
   double f10 = put_values[0];
   prices[0] = d*prices[1];
   put_values[0] = (pDown*put_values[0]+pUp*put_values[1])*Rinv;
   put_values[0] = max(put_values[0], K-prices[i]); // check for exercise
   double f00 = put_values[0];
   delta = (f11-f10)/(S*(u-d));
   double h = 0.5 * S *( uu - d*d);
   gamma = ( (f22-f21)/(S*(uu-1.0)) - (f21-f20)/(S*(1.0-d*d)) ) / h;
   theta = (f21-f00) / (2*delta_t);
   double diff = 0.02;
   double tmp_sigma = sigma+diff;
   double tmp_prices = option_price_put_american_binomial(S,K,r,tmp_sigma,time,no_steps);
   vega = (tmp_prices-f00)/diff; 
   diff = 0.05;
   double tmp_r = r+diff;
   tmp_prices = option_price_put_american_binomial(S,K,tmp_r,sigma,time,no_steps);
   rho = (tmp_prices-f00)/diff; 
};
