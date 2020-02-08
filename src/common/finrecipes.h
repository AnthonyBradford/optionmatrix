/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: finrecipes.h of optionmatrix                                       */
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

#ifdef FINRECIPES

const struct _int_to_function funlistcall[] = {
  { &payoff_call },
  { &payoff_cash_or_nothing_call },
  { &payoff_asset_or_nothing_call },
  { &payoff_binary_call },
 };

const struct _int_to_function funlistput[] = {
  { &payoff_put },
  { 0 },
  { 0 },
  { &payoff_binary_put },
};

const struct term_structure term_structure_list[] = {
  {  TERMFLAT,          },
  {  TERMCIR,           },
  {  TERMVASICEK,       },
  {  TERMNELSONSIEGEL   },
  {  TERMSVENSSON       },
  {  TERMCUBICSPLINE    },
  {  TERMINTERPOLATED   }
};

const int sizeofterm_structure_list = sizeof(term_structure_list);

const struct _int_to_name namefunlist[] = { 
                          { "callput" },
                          { "call_cash_or_nothing"},
                          { "call_asset_or_nothing" }, 
                          { "binary" }
                    };

const struct _int_to_name namefunlist2[] = { 
                          { "arithmetric_avg_call" },
                          { "geometric_avg_call"},
                          { "lookback_callput" }, 
                    };

#endif // FINRECIPES
