/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: misc.h of optionmatrix                                             */
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

/* extend feb 1 day during leap year */
int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const char *const mon[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const char *const optionscycle[] = { "All", "Jan", "Feb", "Mar", "LEAPS" };

const char *const weekdays[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

/* industry futures codes from jan-dec */
const char *const future_codes[] = { "F", "G", "H", "J", "K", "M", "N", "Q", "U", "V", "X", "Z" };

/* 
 * Industry option month codes codes - The Options Industry Council
 * calls: A=Jan, B=Feb ... L=Dec
 * puts:  M=Jan, N=Feb ... X=Dec
 */
const char *const option_calls[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
const char *const option_puts[]  = { "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X" };

const char *const order[] = { "st","nd", "rd", "th" };

struct _properties properties;
struct _properties future_properties;

const struct integratable_distributions distribution_list[] = {

  { normal_dist_constant,         normal_dist_integrate,  "Normal Distribution "  },
  { inverse_normal_dist_constant, inverse_normal_dist_integrate,  "InvNormalDist" }

};

/* this is needed since sizeof(distribution_list) doesn't work via a extern */
const int sizeofdistribution_list = sizeof(distribution_list);
const int sizeofoptionscycle      = sizeof(optionscycle);

const struct numerical_integration_method integration_method[] = {

    /*
      double (*method) (const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3);
      char           des[256];
      mutable int    resolution;
      bool           allowOnlyEven;
      int            UpperLimit;
    */

    { 0,                "PolyApprox6",          0, 0,  0 },
    { 0,                "PolyApprox4",          0, 0,  0 },
    { 0,                "Rational1.0*E-7",      0, 0,  0 },
    { 0,                "Rational2.5*E-4",      0, 0,  0 },
    { 0,                "Hart",                 0, 0,  0 },
    { &rombergs_method, "Romberg's",            6, 0,  6 },
    { &simpsons_rule,   "Simpson's",           52, 1,  0 },
    { &trapezoid_rule,  "Trapezoid",           52, 1,  0 },
    { 0,                "erf()",                0, 0,  0 }

};

const struct _strike_control strike_control[] = {

  /*
    double xcontrol;
    double incrementor;
    int strikes5or1;
    double retdiscard;
    char des[256];
    int precision;
    double sliderScale;
  */

  {     5,      .5,    5,   .5,     "5",    0,    1, },
  {     1,       1,    1,   .5,     "1",    0,    1, },
  {    .5,      .5,    1,   -1,    ".5",    0,    1, },
  {    .1,      .1,    1,   -1,    ".1",    1,    1, },
  {   .01,     .01,    1,   -1,   ".01",    2,    2, },
  {  .001,    .001,    1,   -1,  ".001",    3,    2  },
  {     0,       0,    1,   -1,  "CUST",    5,    0  }

};
