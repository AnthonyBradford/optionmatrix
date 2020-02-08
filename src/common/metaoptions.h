/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: metaoptions.h of optionmatrix                                      */
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

#ifdef METAOPTIONS

const struct _int_to_name nameliststandardbarrier[] = { { "DOWN_IN" }, { "DOWN_OUT" }, { "UP_IN" }, { "UP_OUT" } };
const struct _int_to_name namelistlookbarrier[] =   { { "IN" }, { "OUT" } };
const struct _int_to_name namelistdoublebarrier[] = { { "IN" }, { "OUT" } };
const struct _int_to_name namelistsoftbarrier[] =   { { "IN" }, { "OUT" } };
const struct _int_to_name namelistextremespread[] = { {"NORMAL" }, { "REVERSE" } };
const struct _int_to_name namelistbarrierbinominal[] = { { "UP_OUT" }, { "DOWN_OUT" } };
const struct _int_to_name namelistamericanoreuropean[] = { { "American" }, { "European" } };

const struct _int_to_name namelistthreedimensionalbinominal[] = {
  { "SPREAD_OPTION" },
  { "OPTION_ON_THE_MAX" },
  { "OPTION_ON_THE_MIN" },
  { "DUAL_STRIKE_OPTION" },
  { "REVERSE_DUAL_STRIKE_OPTION" },
  { "PORTFOLIO_OPTION" },
  { "EXCHANGE_OPTION" }
};

const struct _int_to_name namelistimpliedtrinominaltree[] = {
  { "DPM" },
  { "UPM" },
  { "DPni" },
  { "UPni" },
  { "ADM" },
  { "LVM" },
  { "LVni" },
  { "ADni" },
  { "c" },
  { "p" }
};

/* PARTIALTIMEBARRIER makes reference in its source to 10 states
   but only does not abort() on the first two */
/*const struct _int_to_name namelistpartialtimebarrier[]  = {
                                    "cdoA",
                                    "cuoA",
                                    "cdoB2",
                                    "coB1",
                                    "cuoB2",
                                    "pdoA",
                                    "pdoB2",
                                    "poB1",
                                    "puoA",
                                    "puoB2" };*/

/* PARTIALTIMEBARRIER lets keep to the first two states */
const struct _int_to_name namelistpartialtimebarrier[]  = {
                                    { "cdoA" },
                                    { "cuoA" } 
                                                    };

const struct _int_to_name namelistoptionsontheminmax[]  = {
                                    { "min" },
                                    { "max" }
                                                    };

const struct _int_to_name namelistoptionsontheminmax2[]  = {
                              { "cmin" },
                              { "cmax" },
                              { "pmin" },
                              { "pmax" }   };

const struct _int_to_name namelistTwoAssetBarrier[]  = {
                              { "SB_UP_IN"    },
                              { "SB_UP_OUT"   },
                              { "SB_DOWN_OUT" },
                              { "SB_DOWN_IN"  }   };

const int transextremeoptionput[] =  { 2, 4 };
const int transextremeoptioncall[] = { 1, 3 };

#endif // METAOPTIONS
