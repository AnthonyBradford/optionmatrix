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
#include <assert.h>

#include "metaoptions.h"

static const double fact_lookup[11] = {
	1,
	1,
	2,
	6,
	24,
	120,
	720,
	5040,
	40320,
	362880,
	3628800
};

/* Merton (1976) jump diffusion model */
double JumpDiffusion(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double v,
	double lambda,
	double gamma_val) 
{

	int i;
	double p2v, result, vi, p2Z, p2delta;
	double elT = exp(-lambda * T);
	double bs;

	p2v = pow2(v);
    p2delta = pow2(sqrt(gamma_val * p2v / lambda));
    p2Z = pow2(sqrt(p2v - lambda * p2delta));

    result = 0.0;
	for(i = 0; i < 11; i++) {
        vi = sqrt(p2Z + p2delta * ((double)i / T));
		if(fCall) 
			bs = gbs_call(S, X, T, r, r, vi);
		else
			bs = gbs_put(S, X, T, r, r, vi);

        result += elT * pow(lambda * T, (double)i) / fact_lookup[i] * bs;
    }
        
	return result;
}

#ifdef JUMPDIFFUSION_CHECK

void check_JumpDiffusion(void)
{
	/* Jump Diffusion, page 8-9 */
	double S = 45.0, X = 55.0, T = 0.25, r = 0.10, v = 0.25;
	double lambda = 3.0;
	double _Gamma = 0.40;

	double computed = JumpDiffusion(1, S, X, T, r, v, lambda, _Gamma);
	assert_equal(computed, 0.2417);

	S = 100.0; X = 80.0; T = 0.25; r = 0.08; v = 0.25;
	lambda = 1.0;
	_Gamma = 0.25;
	computed = JumpDiffusion(1, S, X, T, r, v, lambda, _Gamma);
	assert_equal(computed, 21.735476);
}


int main(void)
{
	check_JumpDiffusion();
	return 0;
}
#endif

