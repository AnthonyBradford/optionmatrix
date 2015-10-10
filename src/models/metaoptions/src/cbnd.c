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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "metaoptions.h"

static double sign(double d)
{
	assert(is_sane(d));

	if(d < +0.0)
		return -1.0;
	else
		return 1.0;
}


static const double y[] = {
	0.10024215,
	0.48281397,
	1.0609498,
	1.7797294,
	2.6697604
};

/* We keep multiplying y with 2.0, so here is a precomputed version */
static const double y2[] = {
	0.2004843000,
	0.9656279400,
	2.1218996000,
	3.5594588000,
	5.3395208000
};

static const double XX[5][5] = {
	{
		0.06170561535782249917847508414,
		0.09745745062408049663726927747,
		0.05251757861786850167806761647,
		0.00825867481095899844123486844,
		0.00020489864250404100768677973,
	},
	{
		0.09745745062408049663726927747,
		0.15392366848734490014649622935,
		0.08294592470016330654214442575,
		0.01304369769172619882013908210,
		0.00032361559347527383201023610,
	},
	{
		0.05251757861786850167806761647,
		0.08294592470016330654214442575,
		0.04469765106287610506585750159,
		0.00702894868074539942714995533,
		0.00017438900015825459450038992,
	},
	{
		0.00825867481095899844123486844,
		0.01304369769172619882013908210,
		0.00702894868074539942714995533,
		0.00110534040115559985262283504,
		0.00002742361854484439765474585,
	},
	{
		0.00020489864250404100768677973,
		0.00032361559347527383201023610,
		0.00017438900015825459450038992,
		0.00002742361854484439765474585,
		0.00000068038303250915557643890,
	},
};

/* The cumulative bivariate normal distribution function */
double cbnd(double a, double b, double Rho) 
{
	double result, t, a1, b1;

	if(isinf(b))
	  b = 10;

	assert(is_sane(a));
	assert(is_sane(b));
	assert(is_sane(Rho));

	t = sqrt(2.0 * (1.0 - pow2(Rho)));
	a1 = a / t;
	b1 = b / t;

	if(a <= 0.0 && b <= 0.0 && Rho <= 0.0) {
		double sum = 0.0;
		const double rho20 = Rho * 2.0;
		int i;

		for(i = 0; i < 5; i++) {
			sum += XX[i][0] * exp(a1 * (y2[i] - a1) + (b1 * (y2[0] - b1) ) + (rho20 * (y[i] - a1) * (y[0] - b1)));
			sum += XX[i][1] * exp(a1 * (y2[i] - a1) + (b1 * (y2[1] - b1) ) + (rho20 * (y[i] - a1) * (y[1] - b1)));
			sum += XX[i][2] * exp(a1 * (y2[i] - a1) + (b1 * (y2[2] - b1) ) + (rho20 * (y[i] - a1) * (y[2] - b1)));
			sum += XX[i][3] * exp(a1 * (y2[i] - a1) + (b1 * (y2[3] - b1) ) + (rho20 * (y[i] - a1) * (y[3] - b1)));
			sum += XX[i][4] * exp(a1 * (y2[i] - a1) + (b1 * (y2[4] - b1) ) + (rho20 * (y[i] - a1) * (y[4] - b1)));
		}

		result = sqrt(1.0 - pow2(Rho)) / pi * sum;
	}
	else if(a <= 0.0 && b >= 0.0 && Rho >= 0.0) {
		result = cnd(a) - cbnd(a, -b, -Rho);
	}
	else if(a >= 0.0 && b <= 0.0 && Rho >= 0.0) {
		result = cnd(b) - cbnd(-a, b, -Rho);
	}
	else if(a >= 0.0 && b >= 0.0 && Rho <= 0.0) {
		result = cnd(a) + cnd(b) - 1.0 + cbnd(-a, -b, Rho);
	}
	else if( (a * b * Rho) > 0.0) {
		double rho1, rho2, Delta;
		const double sp2a = sqrt(pow2(a) - (Rho * 2.0 * a * b) + pow2(b));
#if 0
		/*assert(is_sane(sp2a));*/
		if(!is_sane(sp2a) || sp2a == 0.0) {
			fprintf(stderr, "This shouldn't happen :-(\n");
			fprintf(stderr, "----------------------------\n");
			fprintf(stderr, "sp2a == %f\n", sp2a);
			fprintf(stderr, "pow2(a) == %.10g, Rho == %.10g a==%.10g b==%.10g pow2(b) == %.10g\n", pow2(a), Rho, a, b, pow2(b));
			fprintf(stderr, "The arg is %.10f\n", pow2(a) - (Rho * 2.0 * a * b) + pow2(b));
			fprintf(stderr, "The middle part is %.10g\n", (Rho * 2.0 * a * b) );
			fprintf(stderr, "----------------------------\n");
abort();
		}
#endif

		rho1 = (Rho * a - b) * sign(a) / sp2a;
#if 0
		if(!is_sane(rho1)) {
			fprintf(stderr, "Rho==%g a == %g b == %g sign(a) == %g sp2a==%g\n", Rho, a, b, sign(a), sp2a);
		}
		assert(is_sane(rho1));
#endif

		rho2 = (Rho * b - a) * sign(b) / sp2a;
		assert(is_sane(rho2));

		Delta = (1.0 - sign(a) * sign(b)) / 4.0;
		assert(is_sane(Delta));

		result = cbnd(a, 0.0, rho1) + cbnd(b, 0.0, rho2) - Delta;
	}
	else {
		/* Hmm, illegal input? Abort to be on the safe side */
		assert(0);
		abort();
	}

	return result;
}

#ifdef CBND_CHECK

int main(void)
{

	/* Testing cbnd() */
	assert_equal(cbnd( 0.0,  0.0,  0.0), 0.250000);
	assert_equal(cbnd( 0.0,  0.0, -0.5), 0.1666667);
	assert_equal(cbnd( 0.0,  0.0,  0.5), 0.333333);
	assert_equal(cbnd( 0.0, -0.5,  0.0), 0.154269);
	assert_equal(cbnd( 0.0, -0.5, -0.5), 0.081660);
	assert_equal(cbnd( 0.0, -0.5,  0.5), 0.226878);
	assert_equal(cbnd( 0.0,  0.5,  0.0), 0.345731);
	assert_equal(cbnd( 0.0,  0.5, -0.5), 0.273122);
	assert_equal(cbnd( 0.0,  0.5,  0.5), 0.418340);

	assert_equal(cbnd(-0.5,  0.0,  0.0), 0.154269);
	assert_equal(cbnd(-0.5,  0.0, -0.5), 0.081660);
	assert_equal(cbnd(-0.5,  0.0,  0.5), 0.226878);
	assert_equal(cbnd(-0.5, -0.5,  0.0), 0.095195);
	assert_equal(cbnd(-0.5, -0.5, -0.5), 0.036298);
	assert_equal(cbnd(-0.5, -0.5,  0.5), 0.163319);
	assert_equal(cbnd(-0.5,  0.5,  0.0), 0.213342);
	assert_equal(cbnd(-0.5,  0.5, -0.5), 0.145218);
	assert_equal(cbnd(-0.5,  0.5,  0.5), 0.272239);

	assert_equal(cbnd( 0.5,  0.0,  0.0), 0.345731);
	assert_equal(cbnd( 0.5,  0.0, -0.5), 0.273122);
	assert_equal(cbnd( 0.5,  0.0,  0.5), 0.418340);
	assert_equal(cbnd( 0.5, -0.5,  0.0), 0.213342);
	assert_equal(cbnd( 0.5, -0.5, -0.5), 0.145218);
	assert_equal(cbnd( 0.5, -0.5,  0.5), 0.272239);
	assert_equal(cbnd( 0.5,  0.5,  0.0), 0.478120);
	assert_equal(cbnd( 0.5,  0.5, -0.5), 0.419223);
	assert_equal(cbnd( 0.5,  0.5,  0.5), 0.546244);
	return 0;
}
#endif

#ifdef CBND_SPEED
#include <stdio.h>
#include <time.h>

int main(void)
{
	size_t i, niter = 300*1000;

	clock_t start, stop;
	double sum = 0.0;


	start = clock();
	for(i = 0; i < niter; i++) {
		sum += cbnd((double)i, 0.1, 0.0);
	}
	stop = clock();
	printf("%'lu clocks for %zu calls\n", (unsigned long)(stop - start), niter);
	return 0;
}
#endif


