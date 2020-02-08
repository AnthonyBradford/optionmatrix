/*
   optionmatrix:

   Options & Futures Matrix Modeler
   View and Control Theoretical Option Chains

   File: black_76.c of optionmatrix

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

double black76call(const double stockprice, const double strike, const double rate, const double t, const double v, double *delta)
{
    double d1,d2,dd1,dd2,call;

    d1 = (log(stockprice/strike)+((v*v)/2)*t)/(v*sqrt(t));
    d2 = d1-(v*sqrt(t));

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
    
    call = ( exp(-rate*t) * ( (stockprice*dd1)-(strike*dd2) ) );

    return call;
}

double black76put(const double stockprice, const double strike, const double rate, const double t, const double v, double *delta)
{
    double put;

    double d1,d2,dd1,dd2;

    d1 = (log(stockprice/strike)+((v*v)/2)*t)/(v*sqrt(t));
    d2 = d1-(v*sqrt(t));

    /* dd1 is the hedge ratio or the option's delta */
    dd1 = cnd(-d1);
    dd2 = cnd(-d2);

    put = (exp(-rate*t)*((strike*dd2) - (stockprice*dd1)));

    if(dd1<0)
    {
      *delta=0.0;

    } else
    {
      if(dd1>=1)
      {
         *delta=-1;

      } else
      {
         *delta= (dd1 - (double) 1.0);
      }
    }

    return put;
}
