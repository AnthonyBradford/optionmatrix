/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: distributions.cpp of optionmatrix                                  */
/*                                                                          */
/* Copyright (c) Anthony Bradford. 2012.                                    */
/* anthony_bradford@yahoo.com                                               */
/*                                                                          */
/* optionmatrix may be freely redistributed.                                */
/* See file COPYING included with this distribution for license information */

/* 
   optionmatrix is free software; you can redistribute it and/or modify
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

#include "defs.h"
#include "extern.h"

double inverse_normal_dist_constant(const double dummy)
{
  return (double)-1;
}

double inverse_normal_dist_integrate(const double x, const double mean, const double standarddeviation)
{
  return (((double)1/
            (((double) sqrt(standarddeviation) *
              sqrt((double)2*(double)M_PI))))

              * exp( -( pow(((double)x-(double)mean),2) /
                   (double)((double)2*((double)standarddeviation*(double)standarddeviation) ) )
              ));

}

double normal_dist_constant(const double standarddeviation)
{
     return (((double)1/
            (((double) sqrt(standarddeviation) *
              sqrt((double)2*(double)M_PI)))));
}

/*
 * the only part of the normal distribution equation that has to be
 * integrated...the other part of the equation can be considered a
 * constant (1 divided by the square root of 2pi).
 */
double normal_dist_integrate(const double x, const double mean, const double standarddeviation)
{
    return  exp( -( pow(((double)x-(double)mean),2) /
            (double)((double)2*((double)standarddeviation*(double)standarddeviation) ) )
            );
}
