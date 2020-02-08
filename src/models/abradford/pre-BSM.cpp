/* 
   optionmatrix:

   Options & Futures Matrix Modeler
   View and Control Theoretical Option Chains

   File: pre-BSM.c of optionmatrix

   Copyright (c) Anthony Bradford. 2012.
   anthony_bradford@yahoo.com

   optionmatrix may be freely redistributed.
   See file COPYING included with this distribution for license information
*/

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

#include "basicmodels.h"

// Louis Bachelier 1870 – 1946...
double bachelier_call(const double stockprice, const double strike, const double t, const double d)
{
    double d1,call;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( stockprice - strike ) / ( stockprice * d * sqrt(t) );
    call = ( stockprice - strike ) * cnd(d1) + ( stockprice * d * sqrt(t) * normd(d1) );

    return call;
}

double bachelier_put(const double stockprice, const double strike, const double t, const double d)
{
    double d1,put;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( stockprice - strike ) / ( stockprice * d * sqrt(t) );
    put = ( strike - stockprice ) * cnd(-d1) + ( stockprice * d * sqrt(t) * normd(d1) );

    return put;
}

// Bachelier call model modified to adjust for time value of money...
double bachelier_modified_call(const double stockprice, const double strike, const double rate, const double t, const double d)
{
    double d1,call;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( stockprice - strike ) / ( stockprice * d * sqrt(t) );
    call = ( ( stockprice * exp( -rate * t)) * cnd(d1) - strike * cnd(d1) )  + ( stockprice * d * sqrt(t) * normd(d1) );

    return call;
}

// Bachelier put model modified to adjust for time value of money...
double bachelier_modified_put(const double stockprice, const double strike, const double rate, const double t, const double d)
{
    double d1,put;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( stockprice - strike ) / ( stockprice * d * sqrt(t) );
    put = ( ( strike * exp( -rate * t )) * cnd(-d1) - stockprice * cnd(-d1) ) + ( stockprice * d * sqrt(t) * normd(d1) );

    return put;
}

double sprenkle_call(const double stockprice, const double strike, const double t, const double d, const double p, const double k)
{
    //double d1,d2,call;
    double d1,call;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( log( stockprice - strike ) + ( p + ( (d * d) / 2 ) * t ) ) / ( d * sqrt(t) );
    call = ( exp( p * t ) * stockprice * cnd(d1) ) - ( 1 - k ) * strike * cnd(d1);

    return call;
}

double boness_call(const double stockprice, const double strike, const double t, const double d, const double p)
{
    double d1,call;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( log( stockprice - strike ) + ( p + ( (d * d) / 2 ) * t ) ) / ( d * sqrt(t) );
    call = stockprice * cnd(d1) - strike * exp( -p * t ) * cnd(d1);

    return call;
}

double samuelson_call(const double stockprice, const double strike, const double t, const double d, const double p, const double w)
{
    double d1,call;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    d1 = ( log( stockprice - strike ) + ( p + ( (d * d) / 2 ) * t ) ) / ( d * sqrt(t) );
    call = stockprice * exp( (p - w) * t ) * cnd(d1) - strike * exp( -w * t) * cnd(d1);

    return call;
}
