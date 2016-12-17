/*
    libmetaoptions - A collection of option-related functions. 
    Copyright (C) 2000-2004 B. Augestad, bjorn.augestad@gmail.com 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <math.h>

#include "metaoptions.h"

/* Vasicek: options on zero coupon bonds, page 151-152.*/
double VasicekBondOption(
	int fCall,
	double F,
	double X,
	double tau,
	double T,
	double r,
	double Theta,
	double kappa,
	double v) 
{
	double PtT, Pt_tau, vp, H, result;

	assert_valid_strike(X);
	assert_valid_time(T);
	assert_valid_interest_rate(r);
	assert_valid_volatility(v);

    X = X / F;
    PtT = VasicekBondPrice(0.0, T, r, Theta, kappa, v);
    Pt_tau = VasicekBondPrice(0.0, tau, r, Theta, kappa, v);
    vp	= sqrt(pow2(v) * (1.0 - exp(-2.0 * kappa * T)) / (2.0 * kappa)) 
		* (1.0 - exp(-kappa * (tau - T))) / kappa;
   
    H = 1.0 / vp * log(Pt_tau / (PtT * X)) + vp / 2.0;
    
    if(fCall)
        result = F * (Pt_tau * cnd(H) - X * PtT * cnd(H - vp));
    else
        result = F * (X * PtT * cnd(-H + vp) - Pt_tau * cnd(-H));
    
    return result;
}

#ifdef VASICEKBONDOPTION_CHECK
void check_VasicekBondOption(void)
{
	double F = 100, X = 92, T = 2, r = 0.08, v = 0.03;
	double mean_reverting_level = 0.09;
	double mean_reverting_rate = 0.05;
	double result;

	double tau = T * 1; /* Tror dette er feil, men jeg er så trøtt... */
	double kappa = mean_reverting_rate;
	double Theta = mean_reverting_level;

	result = VasicekBondOption(1, F, X, tau, T, r, Theta, kappa, v);
	assert_equal(result, 0.1394); /* See page 152 */
}

int main(void)
{

	check_VasicekBondOption();
	return 0;
}
#endif

