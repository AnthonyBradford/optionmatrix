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


/* Miltersen Schwartz (1997) commodity option model 
 * Notes:
 * kE == Kappa E and kF == kappaF. We needed to shorten the names a bit
 * o make the formulas more readable.
 * nkF == (1/kF) and the same goes for E.
 */
double MiltersenSchwartz(
	int fCall,
	double Pt,
	double FT,
	double X,
	double t1,
	double T2,
	double vS,
	double vE,
	double vf,
	double rhoSe,
	double rhoSf,
	double rhoef,
	double kE,
	double kF) 
{
	double result;

	/* Removed redundant expressions from the vz and vxz formulas */
	const double ekEt1 = exp(kE * t1);
	const double ekFt1 = exp(kF * t1);
	const double emkET2 = exp(-kE * T2);  /* Read as: Exp Minus Kappa E T2 */
	const double emkFt1 = exp(-kF * t1); 
	const double emkFT2 = exp(-kF * T2); 
	const double nkF = 1.0 / kF;
	const double nkE = 1.0 / kE;
	const double nemkFt1 = 1.0 - emkFt1;
	const double kEF = kE + kF;
	const double ekEt1m1 = ekEt1 - 1.0;
	const double ekFt1m1 = ekFt1 - 1.0;
	const double nff = nkF * emkFT2 * ekFt1m1;
	const double tkF = 2.0 * kF;
	const double tkE = 2.0 * kE;

	const double vz 
		= pow2(vS) * t1 + 2.0 * vS 
		* ( vf * rhoSf * nkF * (t1 - nff) - vE * rhoSe * nkE * (t1 - nkE * emkET2 * ekEt1m1))
		+ pow2(vE) * 1.0 / pow2(kE) 
		* (t1 + 1.0 / (tkE) * exp(-tkE * T2) * (exp(tkE * t1) - 1.0) - 2.0 * nkE * emkET2 * ekEt1m1) 
		+ pow2(vf) * 1.0 / pow2(kF) 
		* (t1 + (1.0 / tkF) * exp(-tkF * T2) * (exp(tkF * t1) - 1.0) - 2.0 * nff) 
		- 2.0 * vE * vf * rhoef * nkE * nkF 
		* ( t1 - (nkE * emkET2 * ekEt1m1) - nff + ((1.0 / kEF) * exp(-kEF * T2) * (exp(kEF * t1) - 1.0)));

	const double vxz 
		= vf * nkF 
		* (vS * rhoSf * (t1 - nkF * nemkFt1) 
		+ vf * nkF * (t1 - nff - nkF * nemkFt1 + ((1.0 / tkF) * emkFT2 * (ekFt1 - emkFt1)))
		- vE * rhoef * nkE 
		* (t1 - nkE * emkET2 
		* ekEt1m1 - nkF * nemkFt1 
		+ 1.0 / kEF * emkET2 * (ekEt1 - emkFt1)));

	const double sqrtvz = sqrt(vz);
	const double logFTX = log(FT / X);
	const double vz2 = vz / 2.0;
	const double d1 = (logFTX - vxz + vz2) / sqrtvz;
	const double d2 = (logFTX - vxz - vz2) / sqrtvz;

	if(fCall)
		result = Pt * (FT * exp(-vxz) * cnd(d1) - X * cnd(d2));
	else 
		result = Pt * (X * cnd(-d2) - FT * exp(-vxz) * cnd(-d1));

	return result;

}

#ifdef MILTERSENSCHWARTZ_CHECK
void check_MiltersenSchwartz(void)
{
	/* Miltersen and Schwartz Futures Option prices, page 32-33.
	 * Here we need lots and lots of parameters.
	 */
	struct {
		double t, T, X, ms;
	} values[] = {
		{ 0.25, 0.25,  80.0, 15.1918 },
		{ 0.25, 0.25,  95.0,  4.5669 },
		{ 0.25, 0.25, 110.0,  0.6896 },
		{ 0.25, 0.30,  80.0, 15.1424 },
		{ 0.25, 0.30,  95.0,  4.4170 },
		{ 0.25, 0.30, 110.0,  0.6131 },
		{ 0.25, 0.50,  80.0, 15.0049 },
		{ 0.25, 0.50,  95.0,  3.9251 },
		{ 0.25, 0.50, 110.0,  0.3903 },
		{ 0.50, 1.00,  80.0, 15.0787 },
		{ 0.50, 1.00,  95.0,  4.7245 },
		{ 0.50, 1.00, 110.0,  0.7972 }
	};
	double Kappae = 1.045, Kappaf = 0.2, FT = 95.0, vS = 0.266;
	double vE = 0.249, vf = 0.0096, rhoSf = 0.0964, rhoSe = 0.805;
	double rhoef = 0.1243;

	size_t i = 0, nelem = sizeof(values) / sizeof(values[0]);
	for(i = 0; i < nelem; i++) {
		double Pt = exp(-0.05 * values[i].t);

		double computed = MiltersenSchwartz(1,
			Pt,
			FT,
			values[i].X,
			values[i].t,
			values[i].T,
			vS,
			vE,
			vf,
			rhoSe,
			rhoSf,
			rhoef,
			Kappae,
			Kappaf);

		assert_equal(computed, values[i].ms);
	}

}


int main(void)
{
	check_MiltersenSchwartz();
	return 0;
}
#endif


