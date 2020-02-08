/*
   optionmatrix:

   Options & Futures Matrix Modeler
   View and Control Theoretical Option Chains

   File: delta.c of optionmatrix

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

double call_delta(double stockprice, const double strike, const double rate, const double t, const double d, const double dividend)
{
    double d1,dd1;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    stockprice = stockprice - stockprice * dividend * exp(-t * rate);

    d1 = (log(stockprice/strike)+((rate+((d*d)/2))*t))/(d*sqrt(t));

    /* dd1 is the hedge ratio or the option's delta */
    dd1 = cnd(d1);

    if( dd1 < 0 )
    {
        return 0.0;
    } else
    {
        if( dd1 >= 1 )
        {
          return 1;
        } else
        {
          return dd1;
        }
    }

    return dd1;
}

double put_delta(double stockprice, const double strike, const double rate, const double t, const double d, const double dividend)
{
    double d1,dd1;

    /* no time left this thing is worth nothing */
    if( t <= 0 )
    {
        return 0.0;
    }

    stockprice = stockprice - stockprice * dividend * exp(-t * rate);

    d1 = (log(stockprice/strike)+((rate+((d*d)/2))*t))/(d*sqrt(t));

    /* dd1 is the hedge ratio or the option's delta */
    dd1 = cnd(d1);

    dd1 = dd1 - (double) 1;

    if( dd1 > 0 )
    {
        return 0.0;
    } else
    {
        if( dd1 <= -1 )
        {
          return -1;
        } else
        {
          return dd1;
        }
    }

    return dd1;
}
