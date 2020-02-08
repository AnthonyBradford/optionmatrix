/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: basicmodels.h of optionmatrix                                      */
/*                                                                          */
/* Copyright (c) Anthony Bradford. 2012.                                    */
/* anthony_bradford@yahoo.com                                               */
/*                                                                          */
/* optionmatrix may be freely redistributed.                                */
/* See file COPYING included with this distribution for license information */

/* 
   optionmatrix program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   optionmatrix program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../../../config.h"

#ifdef HAVE_MATH_H
# include <math.h>
#else
# error Sorry, this code requires <math.h>
#endif

extern "C"
{
  double cnd(double d1);
}

extern double cnd(const double d1);
extern double normd(const double z);
extern double black_scholes_call(const double, const double, const double, const double, const double, double *);
extern double black_scholes_put(const double, const double, const double, const double, const double, double *);
extern double futures_price(const double spot,const double rate,const double dividend, const double time);
extern double black76call(const double, const double, const double, const double, const double, double *);
extern double black76put(const double, const double, const double, const double, const double, double *);
extern double merton73_call(const double, const double, const double, const double, const double, const double, double *);
extern double merton73_put(const double, const double, const double, const double, const double, const double, double *);
extern double call_delta(double stockprice, const double strike, const double rate,const double t, const double d, const double dividend);
extern double put_delta(double stockprice, const double strike, const double rate,const double t, const double d, const double dividend);
double bachelier_call(const double stockprice, const double strike, const double t, const double d);
double bachelier_put(const double stockprice, const double strike, const double t, const double d);
double bachelier_modified_call(const double stockprice, const double strike, const double rate, const double t, const double d);
double bachelier_modified_put(const double stockprice, const double strike, const double rate, const double t, const double d);
double sprenkle_call(const double stockprice, const double strike, const double t, const double d, const double p, const double k);
double boness_call(const double stockprice, const double strike, const double t, const double d, const double p);
double samuelson_call(const double stockprice, const double strike, const double t, const double d, const double p, const double w);
