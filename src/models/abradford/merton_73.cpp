/* 
   optionmatrix:

   Options & Futures Matrix Modeler
   View and Control Theoretical Option Chains

   File: merton_73.c of optionmatrix

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

double merton73_call(const double stockprice, const double strike, const double rate, const double t, const double d, const double dividend, double *delta)
{
    double d1,d2,dd1,dd2,call;

    /* no time left this thing is worth nothing */
    if(t<=0)
    {
        *delta=0.0;
        return 0.0;
    }

    d1= (log(stockprice/strike)+((rate-dividend+((d*d)/2))*t))/(d*sqrt(t));
    d2=d1-(d*sqrt(t));

    /* dd1 is the hedge ratio or the option's delta */
    dd1 = cnd(d1);
    dd2 = cnd(d2);

    if(dd1<0)
    {
        *delta=0.0;
    } else
    {
        if(dd1>=1)
        {
            *delta=1;
        } else
        {
            *delta=dd1;
        }
    }

    call=((stockprice*exp(-dividend*t)*(dd1))-((strike*exp(-rate*t))*(dd2)));

    return call;
}

double merton73_put(const double stockprice, const double strike, const double rate, const double t, const double d, const double dividend, double *delta)
{
    double call,put;

    /* no time left this thing is worth nothing */
    if(t<=0)
    {
        *delta=0.0;
        return 0.0;
    }

    call=black_scholes_call(stockprice,strike,rate,t,d,delta);
    put=(call+(strike*exp(-rate*t))-stockprice);

    *delta= (*delta - (double) 1.0);

    return put;
}
