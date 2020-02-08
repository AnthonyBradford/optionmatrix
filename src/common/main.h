/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: main.h of optionmatrix                                             */
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
 #include "../models/financialrecipes/src/fin_recipes.h"
#endif

#ifndef QUANTLIB
# undef HAVE_QL_QUANTLIB_HPP
#endif

#include "finrecipes.h"
#include "metaoptions.h"
#include "test.h"
#include "misc.h"

const struct option_algorithm option_algorithms[] = {

#ifdef ABRADFORD

  { BLACKSCHOLES,      "Black-Scholes", "Anthony Bradford, libabradford.a",  
    "",
    "models/abradford/black_scholes.cpp",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { MERTON73,          "Merton-73",  "Anthony Bradford, libabradford.a",  
    "Continuous dividends supported.",
    "models/abradford/merton_73.cpp",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BLACK76,           "Black-76",  "Anthony Bradford, libabradford.a",
    "",
    "models/abradford/black_76.cpp",
    "",
    "a;Futures",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 }, 
#endif

#ifdef SPINSKY

  { AMERICAN_CRR,      "AmericanCRR", "Seth Pinsky, libspinsky.a",
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/spinsky/binomial.cpp",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMERICAN_EQUIPROB, "AmericanEqui", "Seth Pinsky, libspinsky.a",
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/spinsky/binomial.cpp",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EURO_CRR,          "EuropeanCRR",  "Seth Pinsky, libspinsky.a",
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/spinsky/binomial.cpp",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0,  1,  25, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EURO_EQUIPROB,     "EuropeanEqui",  "Seth Pinsky, libspinsky.a",
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/spinsky/binomial.cpp",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef METAOPTIONS

  { BLACKSCHOLES2,     "Black-Scholes 2", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/blackscholes.c",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  
  { GBS,               "Generalized BS", "Bjorn Augestad, libmetaoptions.a",  
    "Continuous dividends supported.",
    "models/metaoptions/src/gbs.c",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { MERTON73B,         "Merton-73b", "Bjorn Augestad, libmetaoptions.a",      
    "Continuous dividends supported.",
    "models/metaoptions/src/merton73.c",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { GFRENCH,           "French", "Bjorn Augestad, libmetaoptions.a",         
    "Adjusted Black-Scholes for Trading Days.",
    "models/metaoptions/src/gfrench.c",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "trading days", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { GCARRY,            "Carry", "Bjorn Augestad, libmetaoptions.a",           
    "Carry for generalized Black-Scholes formula.",
    "models/metaoptions/src/gcarry.c",
    "",
    "0;BSM",
                                       1, // supportRealTime
                                       0, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BAWAMERICAN,       "AmericanBAW", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/BAWAmericanApprox.c",
    "",
    "1;American Options",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BSAMERICAN,        "BSAmerican", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/BSAmericanApprox.c",
    "",
    "1;American Options",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Exiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BLACK76B,          "Black-76b", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/black76.c",
    "",
    "a;Futures",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { ASSETORNOTHING,    "AssetOrNothing", "Bjorn Augestad, libmetaoptions.a",   
    "",
    "models/metaoptions/src/AssetOrNothing.c",
    "",
    "2;Single Asset;Binary",
                                       1, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EXECUTIVE,         "Executive", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust lambda. '+', '-' adjusts increment size.",
    "models/metaoptions/src/Executive.c",
    "",
    "2;Single Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "lambda", 1, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  
  { GARMANKOHLHAGEN,   "GarmanKohlHagen", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust rf. '+', '-' adjusts increment size.",
    "models/metaoptions/src/GarmanKohlhagen.c",
    "",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "rf", .08, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { CASHORNOTHING,     "CashOrNothing", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust cash. '+', '-' adjusts increment size.",
    "models/metaoptions/src/CashOrNothing.c",
    "",
    "2;Single Asset;Binary",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "cash", 30, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { GAPOPTION,         "GapOption", "Bjorn Augestad, libmetaoptions.a",       
    "Use 'z', 'Z' to adjust X2. '+', '-' adjusts increment size.",
    "models/metaoptions/src/GapOption.c",
    "",
    "2;Single Asset;Binary",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "X2", 40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SUPERSHARE,        "SuperShare", "Bjorn Augestad, libmetaoptions.a",       
    "Use 'z', 'Z' to adjust HigherStrike. '+', '-' adjusts increment size.",
    "models/metaoptions/src/SuperShare.c",
    "",
    "2;Single Asset;Binary",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "HigherStrike", 120, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SUPERSHARE2,        "SuperShare 2", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust LowerStrike. '+', '-' adjusts increment size.",
    "models/metaoptions/src/SuperShare.c",
    "",
    "2;Single Asset;Binary",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "LowerStrike", 40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { VASICEKBONDPRICE,  "VasicekBondPrice", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/VasicekBondPrice.c",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 0, 0, 0, 0, 0,
                                       0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "time2", 0, "",
                                       "", "", "Bond Price", "", "Strike", "v",
                                       1, 1, "theta",     .03,  0,  // Z
                                       1, 1, "kappa",     .05,  0,  // B
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { VASICEKBONDOPTION,  "VasicekBondOption", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z', 'b', 'B', 'j' and 'J' to adjust tau, theta, kappa.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/VasicekBondOption.c",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "tau",   1, 0,
                                       1, 1, "theta", .05, 0,
                                       1, 1, "kappa", .09, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TIMESWITCHOPTION,  "TimeSwitchOption", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z', 'b', 'B', 'j' and 'J' to adjust a, m, dt.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/TimeSwitchOption.c",
    "",
    "2;Single Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "Switch", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "a",  5, 0,            // Z
                                       2, 1, "m",  0, 0,            // B
                                       0, 0, "dt", 0.002739726, 0,  // disable
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FOREQUOPTINDOMCUR,  "ForEquOptInDomCur", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z', 'b', 'B', 'j' and 'J' to adjust E, VE, rho.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/ForEquOptInDomCur.c",
    "",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "q", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "E",   1.5,  0,
                                       1, 1, "VE",  0.12, 0,
                                       1, 1, "rho", 0.45, 0,
                                       0, 0, "", 0,    0,
                                       0, 0, "", 0,    0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { QUANTO,              "Quanto", "Bjorn Augestad, libmetaoptions.a",        
    "Use 'z', 'Z', 'b', 'B', 'j', 'J', 'p' and 'P' to adjust Ep, rf, vE, rho.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/Quanto.c",
    "",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "q", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "Ep",   1.5, 0,
                                       1, 1, "rf",  0.05, 0,
                                       1, 1, "vE",  0.10, 0,
                                       1, 1, "rho", 0.30, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EQUITYLINKEDFXO, "EquityLinkedFXO", "Bjorn Augestad, libmetaoptions.a",   
    "Use 'z', 'Z', 'b', 'B', 'j' , 'J', 'p' and 'P' to adjust E, rf, VE, rho.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/EquityLinkedFXO.c",
    "",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "q", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "E",   1.5,  0,
                                       1, 1, "rf",  0.05, 0,
                                       1, 1, "vE",  0.12, 0,
                                       1, 1, "rho", -0.4, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SPREADAPPROXIMATION, "SpreadApproximation", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z', 'b', 'B', 'j' and 'J' to adjust F2, V2, rho.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/SpreadApproximation.c",
    "",
    "3;Two Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "F2",     20, 0,
                                       1, 1, "V2",   0.36, 0,
                                       1, 1, "rho",  0.42, 0,
                                       0, 0, "",        0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { JUMPDIFFUSION,     "MertonJumpDiff", "Bjorn Augestad, libmetaoptions.a",   
    "Use 'z', 'Z', 'b', and 'B' to adjust lambda and gamma.\n '+', '-' adjusts increment size.",
    "models/metaoptions/src/JumpDiffusion.c",
    "",
    "4;Jump Diffusion",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "lambda",    1, 0,
                                       1, 1, "gamma",  0.25, 1,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BISECTION,     "Bisection",  "Bjorn Augestad, libmetaoptions.a",        
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/metaoptions/src/bisection.c",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Implied Vol Call", "Implied Vol Put", "Strike", "Call Price",
                                       0, 0, "", 100, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  { NEWTONRAPHSON,     "NewtonRaphson",  "Bjorn Augestad, libmetaoptions.a",        
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/metaoptions/src/NewtonRaphson.c",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Implied Vol Call", "Implied Vol Put", "Strike", "Call Price",
                                       0, 0, "", 100, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  
  { BAWBISECTION,     "BAWbisection",  "Bjorn Augestad, libmetaoptions.a",        
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/metaoptions/src/BAWbisection.c",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Implied Vol Call", "Implied Vol Put", "Strike", "Option Price",
                                       0, 0, "", 100, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BSBISECTION,     "BSbisection",  "Bjorn Augestad, libmetaoptions.a",        
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/metaoptions/src/BSbisection.c",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.07, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Implied Vol Call", "Implied Vol Put", "Strike", "Call Price",
                                       0, 0, "", 100, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMERICANEXCHANGEOPTION,  "AmerExchangeOpt", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/AmericanExchangeOption.c",
    "",
    "3;Two Asset;Exchange",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "Dividend", "Call", "Put", "S2", "v1",
                                       0, 1, "S2",   100,  0, // disable
                                       1, 1, "Q1",     1,  0, // B
                                       1, 1, "Q2",     1,  0, // J
                                       1, 1, "b1",   .04,  0, // P
                                       1, 1, "b2",   .06,  0, // Q
                                       1, 1, "v2",   .25,  0, // R
                                       1, 1, "rho",    0,  0, // S
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROPEANEXCHANGEOPTION,  "EurExchangeOpt", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/EuropeanExchangeOption.c",
    "",
    "3;Two Asset;Exchange",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "Dividend", "Call", "Put", "S2", "Standard Deviation",
                                       0, 1, "S2",   100,  0, // Z disable
                                       1, 1, "Q1",     1,  0, // B
                                       1, 1, "Q2",     1,  0, // J
                                       1, 1, "b1",   .04,  0, // P
                                       1, 1, "b2",   .05,  0, // Q
                                       1, 1, "v1",   .20,  0, // R
                                       1, 1, "v2",   .23,  0, // S
                                       1, 1, "rho",    1,  0, // T
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { MILTERSENSWARTZ,  "MiltersenSchwartz", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/MiltersenSwartz.c",
    "",
    "a;Futures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "Futures Exp", 0, "",
                                       "FT", "Dividend", "Call", "Put", "Strike", "vS",
                                       1, 1, "Pt",  0.987578,  0,
                                       1, 1, "vE",     0.249,  0,
                                       1, 1, "vf",    0.0096,  0,
                                       1, 1, "rhoSe",  0.805,  0,
                                       1, 1, "rhoSf", 0.0964,  0,
                                       1, 1, "rhoef", 0.1243,  0,
                                       1, 1, "kE",     1.045, 0,
                                       1, 1, "kF",        .2, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { PARTIALTIMETWOASSETBARRIER,  "PartialTimeTwoAsset", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/PartialTimeTwoAssetBarrier.c",
    "",
    "3;Two Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "time2", 0, "",
                                       "S1", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "S2",   80,  0,
                                       1, 1, "H",     1,  0,
                                       1, 1, "b1",  .06,  0,
                                       1, 1, "b2",  .03,  0,
                                       1, 1, "v1",  .30,  0,
                                       1, 1, "v2",  .25,  0,
                                       1, 1, "rho",   1,  0,
                                       0, 0, "",      0,  0,
                                       1, 0, "State", 1,  4,
                                       1, &namelistTwoAssetBarrier[0] },

  { TAKEOVERFXOPTION,  "TakeOverFXOption", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/TakeoverFXoption.c",
    "",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "v", "Dividend", "Call", "Put", "Strike", "vV",
                                       1, 0, "b",   100,  0,  // Z
                                       1, 1, "E",   100,  0,  // B
                                       1, 1, "rf",  .06,  0,  // J
                                       0, 1, "vV",  .25,  0,  // P - disable
                                       1, 1, "vE",  .30,  0,  // Q
                                       1, 1, "rho", .25,  0,  // R
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TWOASSETBARRIER,  "TwoAssetBarrier", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/TwoAssetBarrier.c",
    "",
    "3;Two Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "Dividend", "Call", "Put", "Strike", "v1",
                                       1, 0, "S2",    100, 0,  // Z
                                       1, 0, "H",     95,  0,  // B
                                       1, 1, "b1",   .08,  0,  // J
                                       1, 1, "b2",   .08,  0,  // P
                                       1, 1, "v2",   .20,  0,  // Q
                                       1, 1, "rho", -.50,  0,  // R
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 4,
                                       1, &namelistTwoAssetBarrier[0] },

  { TWOASSETCASHORNOTHING,  "TwoAssetCashOrNothing", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/TwoAssetCashOrNothing.c",
    "",
    "3;Two Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "Dividend", "Call", "Put", "Strike", "v1",
                                       1, 0, "S2",    100, 0,  // Z
                                       1, 0, "X2",    100, 0,  // B
                                       1, 1, "K",      30, 0,  // J
                                       1, 1, "b1",   .08,  0,  // P
                                       1, 1, "b2",   .08,  0,  // Q
                                       1, 1, "v2",   .20,  0,  // R
                                       1, 1, "rho", -.50,  0,  // S
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 4,
                                       0, 0 },

  { TWOASSETCORRELATION,  "TwoAssetCorrelation", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/TwoAssetCorrelation.c",
    "",
    "3;Two Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "Dividend", "Call", "Put", "Strike", "v1",
                                       1, 0, "S2",    100, 0,  // Z
                                       1, 0, "X2",    100, 0,  // B
                                       1, 1, "b1",   .08,  0,  // J
                                       1, 1, "b2",   .08,  0,  // P
                                       1, 1, "v2",   .20,  0,  // Q
                                       1, 1, "rho", -.50,  0,  // R
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FLOATINGSTRIKELOOKBACK, "FloatingXLookBack", "Bjorn Augestad, libmetaoptions.a",
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/FloatingStrikeLookback.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Min", "Standard Deviation",
                                       1, 0, "Max", 40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FLOATINGSTRIKELOOKBACK2, "FloatingXLookBack 2", "Bjorn Augestad, libmetaoptions.a",
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/FloatingStrikeLookback.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Max", "Standard Deviation",
                                       1, 0, "Min", 40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FIXEDSTRIKELOOKBACK, "FixedXLookback", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/FixedStrikeLookback.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "Max", 120, 0,
                                       1, 0, "Min",  40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { OPTIONSONTHEMAXMIN, "OptionsOnTheMaxMin", "Bjorn Augestad, libmetaoptions.a",  
    "Supports \"min\" and \"max\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/OptionsOnTheMaxMin.c",
    "",
    "3;Two Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "S1", "b1", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "S2", 90, 0,
                                       1, 1, "b2", .03, 0,
                                       1, 1, "v2", .15, 0,
                                       1, 1, "rho", .05, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 2,
                                       1, &namelistoptionsontheminmax[0] },

  { STANDARDBARRIER, "StandardBarrier", "Bjorn Augestad, libmetaoptions.a",   
    "Supports \"DOWN_IN\", \"DOWN_OUT\", \"UP_IN\" and \"UP_OUT\" states use '#' key to\ntoggle when displayed.",
    "models/metaoptions/src/StandardBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "H", 95, 0,
                                       1, 1, "K", 3, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 4,     
                                       1, &nameliststandardbarrier[0] },

  { DOUBLEBARRIER,   "DoubleBarrier", "Bjorn Augestad, libmetaoptions.a",     
    "Supports \"IN\" and \"OUT\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/DoubleBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "LowerBarrier", 50, 0,
                                       1, 0, "UpperBarrier", 150, 0,
                                       1, 1, "delta1", 0, 0,
                                       1, 1, "delta2", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 2,     
                                       1, &namelistdoublebarrier[0] },

  { SOFTBARRIER, "SoftBarrier", "Bjorn Augestad, libmetaoptions.a",            
    "Produces \"nan\", not a number, when dividend is equal to zero\nSupports \"IN\" and \"OUT\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/SoftBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "L", 50, 0,
                                       1, 0, "U", 95, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 2,     
                                       1, &namelistsoftbarrier[0] },

  { BINARYBARRIER,  "BinaryBarrier", "Bjorn Augestad, libmetaoptions.a",  
    "Supports 28 states. Use '#' key to change states when displayed.",
    "models/metaoptions/src/BinaryBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "H",      100,  0, // Z
                                       1, 0, "K",       15,  0, // B
                                       2, 1, "eta",      1,  0, // J
                                       2, 1, "phi",      1,  0, // P
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State",    1, 28,
                                       0, 0 },

  { DISCRETEADJUSTEDBARRIER,  "DiscreteAdjBarrier", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/DiscreteAdjustedBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 0, 0, 0, 0, 0,
                                       1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "dt", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "H", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BARRIERBINOMINAL,  "BarrierBinomial", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/BarrierBinominal.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 10, 0, 0,
                                       1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "EuropeanOption", 0, 1,      // Z
                                       1, 0, "H", 110, 0,                 // B
                                       0, 0, "", 0, 0,                    // J
                                       0, 0, "", 0, 0,                    // P
                                       0, 0, "", 0, 0,                    // Q
                                       0, 0, "", 0, 0,                    // R
                                       0, 0, "", 0, 0,                    // S
                                       0, 0, "", 0, 0,                    // T
                                       1, 0, "State", 1, 2,               // #
                                       1, &namelistbarrierbinominal[0] },

  { CONVERTIBLEBOND,  "ConvertibleBond", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/ConvertibleBond.c",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Maturity", 2, "Convert", 0, "",
                                       "Price", "q", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "k", 1.25,   0,         // Z
                                       1, 0, "F",  100,   0,         // B
                                       1, 1, "Coupon", .05, 0,       // J
                                       0, 0, "", 0, 0,               // P
                                       0, 0, "", 0, 0,               // Q
                                       0, 0, "", 0, 0,               // R
                                       0, 0, "", 0, 0,               // S
                                       0, 0, "", 0, 0,               // T
                                       1, 0, "Type", 1, 2,           // #
                                       1, &namelistamericanoreuropean[0] },

  { CRRBINOMINAL,  "CRRBinomial", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/CRRBinominal.c",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,          // Z
                                       0, 0, "", 0, 0,          // B
                                       0, 0, "", 0, 0,          // J
                                       0, 0, "", 0, 0,          // P
                                       0, 0, "", 0, 0,          // Q
                                       0, 0, "", 0, 0,          // R
                                       0, 0, "", 0, 0,          // S
                                       0, 0, "", 0, 0,          // T
                                       1, 0, "Type", 1, 2,      // #
                                       1, &namelistamericanoreuropean[0] },

 /*
  { IMPLIEDTRINOMINALTREE,  "ImpliedTriTree", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/ImpliedTrinominalTree.c",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Type", "Put", "Strike", "Standard Deviation",
                                       2, 0, "STEPn",    10, 0,    // Z
                                       2, 0, "STATEi",   10, 0,    // B
                                       1, 0, "Skew",    .25, 0,    // J
                                       0, 0, "", 0, 0,             // P
                                       0, 0, "", 0, 0,             // Q
                                       0, 0, "", 0, 0,             // R
                                       0, 0, "", 0, 0,             // S
                                       0, 0, "", 0, 0,             // T
                                       1, 0, "Type", 1, 10,        // #
                                       1, &namelistimpliedtrinominaltree[0] },
*/

  { THREEDIMENSIONALBINOMINAL,  "3D-Binominal", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/ThreeDimensionalBinominal.c",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.7, "Expiration", 0, "", 0, "",
                                       "S1", "b1", "Call", "Put", "X1", "v1",
                                       2, 0, "EuropeanOption", 0, 1,   // Z
                                       1, 0, "S2",  80, 0,             // B
                                       1, 0, "v2", .25, 0,             // J
                                       1, 1, "b2", .05, 0,             // P
                                       1, 0, "X2", .85, 0,             // Q
                                       1, 1, "Q1", .97, 0,             // R
                                       1, 1, "Q2", .05, 0,             // S
                                       1, 1, "rho",  1, 0,             // T
                                       1, 0, "Type", 1, 7,             // #
                                       1, &namelistthreedimensionalbinominal[0] },

  { TRINOMINALTREE,  "TrinomialTree", "Bjorn Augestad, libmetaoptions.a",  
    "",
    "models/metaoptions/src/TrinominalTree.c",
    "",
    "5;Trees & Finite Diff;Trinomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,          // Z
                                       0, 0, "", 0, 0,          // B
                                       0, 0, "", 0, 0,          // J
                                       0, 0, "", 0, 0,          // P
                                       0, 0, "", 0, 0,          // Q
                                       0, 0, "", 0, 0,          // R
                                       0, 0, "", 0, 0,          // S
                                       0, 0, "", 0, 0,          // T
                                       1, 0, "Type", 1, 2,      // #
                                       1, &namelistamericanoreuropean[0] },

  { LOOKBARRIER, "LookBarrier", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero\nSupports \"IN\" and \"OUT\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/LookBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 dont use 2
                                       2, 0.03, "Expiration", 1, "look time", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "H", 80, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       /*1, 0, "State", 3, 4,*/
                                       1, 0, "State", 1, 2,
                                       1, &namelistlookbarrier[0] },

  { PARTIALTIMEBARRIER, "PartialTimeBarrier", "Bjorn Augestad, libmetaoptions.a",  
    "Supports \"cdoA\" and \"cuoA\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/PartialTimeBarrier.c",
    "",
    "2;Single Asset;Barrier",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "partial time", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "H", 50, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       //1, 0, "State", 1, 10,
                                       1, 0, "State", 1, 2,
                                       1, &namelistpartialtimebarrier[0] },

  { ROLLGESKEWHALEY,   "RollGeskeWhaley 2", "Bjorn Augestad, libmetaoptions.a",  
    "Supports explicit dividend date. Enter dividend date as\ndecimal date such as .25 or enter as MM/DD/YY HH:MM:SS",
    "models/metaoptions/src/RollGeskeWhaley.c",
    "",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "dividend", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EXTREMESPREADOPTION, "ExtremeSpread", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero or div time is\ngreater than expiration. Supports \"NORMAL\" and \"REVERSE\" states use '#' key\nto toggle when displayed.",
    "models/metaoptions/src/ExtremeSpreadOption.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 2, "T1", 0, "",
                                       "Price", "b", "Call", "Put", "SMax", "Standard Deviation",
                                       0, 0, "SMax", 100, 0,  // disable
                                       1, 0, "SMin", 100, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 2,
                                       1, &namelistextremespread[0] },

  { EXTREMESPREADOPTION2, "ExtremeSpread 2", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero or div time is\ngreater than expiration. Supports \"NORMAL\" and \"REVERSE\" states use '#' key\nto toggle when displayed.",
    "models/metaoptions/src/ExtremeSpreadOption.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 2, "T1", 0, "",
                                       "Price", "b", "Call", "Put", "SMin", "Standard Deviation",
                                       1, 0, "SMax", 100, 0,
                                       0, 0, "SMin", 100, 0,   // disable
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "State", 1, 2,
                                       1, &namelistextremespread[0] },

  { PARTIALFIXEDLB,    "PartialFixedLB", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/PartialFixedLB.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 don't use 2
                                       2, 0.03, "Expiration", 1, "partial time", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { PARTIALFLOATLB,  "PartialFloatLB",   "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/PartialFloatLB.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 don't use 2
                                       2, 0.03, "Expiration", 1, "time to option", 0, "",
                                       "Price", "b", "Call", "Put", "Max", "Standard Deviation",
                                       1, 0, "Min",   40, 0,
                                       1, 0, "lambda", 1, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { PARTIALFLOATLB2,  "PartialFloatLB 2",   "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/PartialFloatLB.c",
    "",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 don't use 2
                                       2, 0.03, "Expiration", 1, "time to option", 0, "",
                                       "Price", "b", "Call", "Put", "Min", "Standard Deviation",
                                       1, 0, "Max",   40, 0,
                                       1, 0, "lambda", 1, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EXTENDIBLEWRITER, "ExtendibleWriter", "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust X2. '+', '-' adjusts increment size.",
    "models/metaoptions/src/ExtendibleWriter.c",
    "",
    "2;Single Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 dont use 2
                                       1, 0.0, "Expiration", 1, "extended maturity", 0, "",
                                       "Price", "b", "Call", "Put", "X1", "Standard Deviation",
                                       1, 0, "X2", 30, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { CALLSONOPTIONS, "CallsOnOptions",    "Bjorn Augestad, libmetaoptions.a",  
    "Use 'z', 'Z' to adjust X2. '+', '-' adjusts increment size.\nUse 'e', 'E' to adjust time to option.",
    "models/metaoptions/src/OptionsOnOptions.c",
    "",
    "2;Single Asset;Options on Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // iSupportTime2 don't use 2
                                       1, 0.0, "Expiration", 1, "time to option", 0, "",
                                       "Price", "b", "Call", "Put", "X2", "Standard Deviation",
                                       1, 0, "X1", 20, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

 { PUTSONOPTIONS,  "PutsOnOptions",   "Bjorn Augestad, libmetaoptions.a",  
   "",
   "models/metaoptions/src/OptionsOnOptions.c",
    "",
    "2;Single Asset;Options on Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 1, "time to option", 0, "",
                                       "Price", "b", "Call", "Put", "X2", "Standard Deviation",
                                       1, 0, "X1", 40, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { LEVYASIAN,      "LevyAsian",       "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/LevyAsian.c",
    "",
    "c;Asian",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 2, "dividend", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "SA", 10, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { GEOMETRICAVERAGERATEOPTION, "GeoMetricAvgRate", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend time is greater than expiration.\nUse 'E', 'e' to adjust div time. Use 'W', 'w' to adjust months.\nSupports \"NORMAL\" and \"REVERSE\" states use '#' key to toggle when displayed.",
    "models/metaoptions/src/GeometricAverageRateOption.c",
    "",
    "c;Asian",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "avg", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "SA", 10, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FORWARDSTARTOPTION, "ForwardStartOption", "Bjorn Augestad, libmetaoptions.a",  
    "Strikes have been replaced with alpha.",
    "models/metaoptions/src/ForwardStartOption.c",
    "",
    "2;Single Asset",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "time to start", 0, "",
                                       "Price", "b", "Call", "Put", "alpha", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SWAPOPTION,     "SwapOption",       "Bjorn Augestad, libmetaoptions.a",   
    "Use 'z', 'Z' to adjust m. '+', '-' adjusts increment size.\nUse 'e', 'E' to adjust time to swap.",
    "models/metaoptions/src/Swapoption.c",
    "",
    "b;Interest Rate Dx",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "time to swap", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "m", 2, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
 
  { TURNBULLWAKEMANASIAN, "TurnBullWakemanAsian", "Bjorn Augestad, libmetaoptions.a",  
    "Produces \"nan\", not a number, when dividend is equal to zero.",
    "models/metaoptions/src/TurnbullWakemanAsian.c",
    "",
    "c;Asian",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       2, 0.03, "Expiration", 2, "avg start", 0, "",
                                       "Price", "b", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "SA", 88, 0,
                                       1, 1, "tau", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EXCHANGEEXCHANGEOPTION, "ExchangeExchOption", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/ExchangeExchangeOption.c",
    "",
    "3;Two Asset;Exchange",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // Crashing on dividend, Disabled dividend
                                       //1, 0.0, "Expiration", 2, "exchange",
                                       0, 0.0, "Expiration", 2, "exchange", 0, "",
                                       "S1", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0,   "S2",  100, 0,
                                       1, 1,   "b1",  0.1, 0,
                                       1, 1,   "b2",  0.1, 0,
                                       1, 0,   "v1",  0.2, 0,
                                       1, 0,   "v2",  0.2, 0,
                                       1, 1,  "rho",  0.5, 0,
                                       0, 0,     "",    0, 0,
                                       0, 0,     "",    0, 0,
                                       1, 0, "State",   1, 4,
                                       0, 0 },

  { SIMPLECHOOSER,     "SimpleChooser", "Bjorn Augestad, libmetaoptions.a",    
    "Adjust Time to choose with 'E' and 'e' keys. Adjust size of decrement,\nincrements with '+', '-' keys. Produces \"nan\", not a number, when time to\nchoose is greater than expiration.",
    "models/metaoptions/src/SimpleChooser.c",
    "",
    "2;Single Asset;Chooser",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "choose", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "b", .03, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { COMPLEXCHOOSER, "ComplexChooser", "Bjorn Augestad, libmetaoptions.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/metaoptions/src/ComplexChooser.c",
    "",
    "2;Single Asset;Chooser",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,  
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Call", 1, "time", 1, "Put",
                                       "Price", "", "Call", "Put", "Xc", "Standard Deviation",
                                       1, 0, "Xp", 48, 0,            // Z - Strike Put
                                       0, 0, "T to Put", 0.25, 0,    // B - Disabled
                                       1, 1, "b", 0.03, 0,           // J - Cost of carry
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef FINRECIPES

  { BLACKSCHOLES3,      "Black-Scholes 3",  "Bernt Arne Oedegaard, librecipes.a",
    "",
    "models/financialrecipes/src/black_scholes_call.cc",
    "models/financialrecipes/src/black_scholes_put.cc",
    "0;BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { PERPETUAL,     "AmPerpetual", "Bernt Arne Oedegaard, librecipes.a",  
    "Calls price \"nan\", not a number, when dividend is equal to zero\nPuts have no pricing issues.",
    "models/financialrecipes/src/option_price_american_perpetual_call.cc",
    "models/financialrecipes/src/option_price_american_perpetual_put.cc",
    "1;American Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       1, 0, 0, 0, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // not a t2 model, but iSupportTime2 will not
                                       // allow calendar dates formats...
                                       2, 0.03, "Expiration", 1, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FUTOPTEURBLACK, "Black-76c", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/futures_opt_call_black.cc",
    "models/financialrecipes/src/futures_opt_put_black.cc",
    "a;Futures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FUTOPTAMBINOMIAL, "FutOptAmBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/futures_opt_call_bin.cc",
    "models/financialrecipes/src/futures_opt_put_bin.cc",
    "a;Futures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  /*
  { AMERBJERKSUNDSTENSLAND, "AmBjerksundStensland", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/approx_am_put_bjerksund_stensland.cc",
    "",
    "1;American Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
  */
  { AMERBINOMIAL, "AmericanBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/bin_am_call_payout.cc",
    "models/financialrecipes/src/bin_am_put_payout.cc",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  // American Binomial that supports a dividend
  { AMERBINOMIALDIV, "AmericanBinomialDiv", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/bin_am_call_payout.cc",
    "models/financialrecipes/src/bin_am_put_payout.cc",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMERICANTRINOMIAL, "AmericanTrinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease trinomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/opt_price_trinom_am_call.cc",
    "models/financialrecipes/src/opt_price_trinom_am_put.cc",
    "5;Trees & Finite Diff;Trinomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMERBAW, "AmericanBAW 2", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/approx_am_call.cc",
    "models/financialrecipes/src/approx_am_put.cc",
    "1;American Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMERPUTAPPROXJOHNSON, "AmPutApproxJohnson", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/approx_am_put_johnson.cc",
    "",
    "1;American Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#ifdef HAVE_LIBGSL

  { AMERPUTAPPROXGESKEJOHNSON, "AmPutApproxGeskeJohn", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/approx_am_put_geske_johnson.cc",
    "",
    "1;American Options",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { HESTON,      "Heston",  "Bernt Arne Oedegaard, librecipes.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/heston_price.cc",
    "",
    "5;Trees & Finite Diff;Heston",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "tau",      0.5, 0,   // disable
                                       1, 1, "rho",        0, 0,   // B
                                       1, 1, "kappa",      2, 0,   // J
                                       1, 1, "lambda",     0, 0,   // P
                                       1, 1, "theta",   0.01, 0,   // Q
                                       1, 1, "sigma",   0.01, 0,   // R
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

  { BONDZEROBLACK, "BondZeroBlack", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/bondopt_call_bs.cc",
    "models/financialrecipes/src/bondopt_put_bs.cc",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BONDAMERBINOMIAL, "BondAmerBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/bondopt_call_binom_am.cc",
    "models/financialrecipes/src/bondopt_put_binom_am.cc",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BOND_ZERO_AM_RENDLEMAN_BARTTER, "BondCallRendlemanB", "Bernt Arne Oedegaard, librecipes.a",  
    "Zero Bond Option Call American Rendleman Bartter. Use 'z', 'Z', 'b', and 'B'\nto adjust M and S. '+', '-' adjusts increment size.",
    "models/financialrecipes/src/bondopt_call_rend_bart.cc",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 0, 1, 100, 0, 0,
                                       1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "option maturity", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "M", 0.05, 0,
                                       1, 1, "S", 0.15, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BSPAYOUT,      "Merton-73c",  "Bernt Arne Oedegaard, librecipes.a",  
    "Continuous dividends supported.",
    "models/financialrecipes/src/black_scholes_price_payout_call.cc",
    "models/financialrecipes/src/black_scholes_price_payout_put.cc",
    "0;BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROBIONMIAL, "EuropeanBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Increase / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/bin_eur_call.cc",
    "models/financialrecipes/src/bin_eur_put.cc",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { ASIANGEOMETRICAVG,     "AsianGeometricAvg", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/exotics_asian_price_call.cc",
    "",
    "c;Asian",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROLOOKBACK, "EuroLookback", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z' to adjust Min. '+', '-' adjusts increment size.",
    "models/financialrecipes/src/exotics_lookback_call.cc",
    "models/financialrecipes/src/exotics_lookback_put.cc",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Smax", "Standard Deviation",
                                       1, 0, "Smin", 40, 0,
                                       0, 0, "",  0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROLOOKBACK2, "EuroLookback 2", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z' to adjust Min. '+', '-' adjusts increment size.",
    "models/financialrecipes/src/exotics_lookback_call.cc",
    "models/financialrecipes/src/exotics_lookback_put.cc",
    "2;Single Asset;Lookbacks",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Smin", "Standard Deviation",
                                       1, 0, "Smax", 100, 0,
                                       0, 0, "",  0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { MERTONJUMPDIFF, "MertonJumpDiff 2", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z', 'b', 'B', 'j' and 'J' to adjust lambda, gamma, delta.\n '+', '-' adjusts increment size.",
    "models/financialrecipes/src/merton_jump_diff_call.cc",
    "",
    "4;Jump Diffusion",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "lambda", 0.5, 0,
                                       1, 1, "kappa",  0.5, 0,
                                       1, 1, "delta",  0.5, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { CURRAMBINOMIAL, "CurrencyAmBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z' to adjust rf. '+', '-' adjusts increment size.\nIncrease / decrease binomial steps with 'G', 'g' keys when displayed.",
    "models/financialrecipes/src/currency_opt_bin_call.cc",
    "models/financialrecipes/src/currency_opt_bin_put.cc",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 25, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "rf", 0.05, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
       
  { CURREURO, "CurrencyEuro", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z' to adjust rf. '+', '-' adjusts increment size.",
    "models/financialrecipes/src/currency_opt_euro_call.cc",
    "models/financialrecipes/src/currency_opt_euro_put.cc",
    "8;Currency",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "rf", 0.05, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { ROLLGESKEWHALEY2, "RollGeskeWhaley", "Bernt Arne Oedegaard, librecipes.a",  
    "Supports explicit dividend date. Enter dividend date as\ndecimal date such as .25 or enter as MM/DD/YY HH:MM:SS",
    "models/financialrecipes/src/anal_price_am_call_div.cc",
    "",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "dividend", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROBINOMIAL1P, "EuroBinomial1Period", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z', 'b', and 'B' to adjust up and down.\n '+', '-' adjusts increment size.",
    "models/financialrecipes/src/bin_eur_call_ud_one.cc",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       // Perpetual no sensitivity to time
                                      -1, 0, 0, 0, 0, 1,
                                       1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // not a t2 model, but iSupportTime2 will not
                                       // allow calendar dates formats...
                                       0, 0.0, "Expiration", 1, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "up",   1.05, 0,
                                       1, 0, "down", 0.952380952, 0,   // = 1/1.05
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
    
  { EUROBINOMIALMP, "EuroBinomialMPeriod", "Bernt Arne Oedegaard, librecipes.a",  
    "Use 'z', 'Z', 'b', and 'B' to adjust up and down.\n '+', '-' adjusts increment size.",
    "models/financialrecipes/src/bin_eur_call_ud.cc",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       // Perpetual no sensitivity to time
                                      -1, 0, 1, 25, 0, 1,
                                       1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       // not a t2 model, but iSupportTime2 will not
                                       // allow calendar dates formats...
                                       0, 0.0, "Expiration", 1, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "up",   1.05, 0,
                                       1, 0, "down", 0.952380952, 0,   // = 1/1.05
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMBINOMIAL, "GenericBinomial", "Bernt Arne Oedegaard, librecipes.a",  
    "American Binomial Method. Use '#' to toggle payoffs between callput,\ncash_or_nothing, asset_or_nothing and binary when displayed.\nBinomial steps controlled by 'G', 'g' keys.",
    "models/financialrecipes/src/binomial_generic.cc",
    "models/financialrecipes/src/binomial_generic_delta.cc",
    "5;Trees & Finite Diff;Binomial",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 4,
                                       1, &namefunlist[0] },

  { EUROSIM, "SimEuro", "Bernt Arne Oedegaard, librecipes.a",  
    "This is a Monte Carlo Method. Monte Carlo simulations controlled by 'G', 'g'\nkeys.",
    "models/financialrecipes/src/simulated_call_euro.cc",
    "models/financialrecipes/src/simulated_put_euro.cc",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 500, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SIMEUROGENERIC, "SimEuroGeneric", "Bernt Arne Oedegaard, librecipes.a",  
    "Monte Carlo European Generic. Supports multiple payoffs. Use '#' to toggle\npayoffs between callput, cash_or_nothing, asset_or_nothing, binary when\ndisplayed. Monte Carlo simulations controlled by 'G', 'g' keys.",
    "models/financialrecipes/src/simulate_european_options_generic_routine.cc",
    "",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 500, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 4,
                                       1, &namefunlist[0] },

  { SIMEUROGENERICCV, "SimGControlVariate", "Bernt Arne Oedegaard, librecipes.a",  
    "Monte Carlo simulations controlled by 'G', 'g' keys. Use '#' to toggle payoffs\nbetween callput, cash_or_nothing, asset_or_nothing, binary when displayed.",
    "models/financialrecipes/src/simulate_european_options_generic_routine_control_variate.cc",
    "",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 0, 1, 500, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 4,
                                       1, &namefunlist[0] },

  { SIMEUROGENERICAV, "SimGAntiheticVariate", "Bernt Arne Oedegaard, librecipes.a",  
    "Monte Carlo simulations controlled by 'G', 'g' keys. Use '#' to toggle payoffs\nbetween callput, cash_or_nothing, asset_or_nothing, binary when displayed.",
    "models/financialrecipes/src/simulate_european_options_generic_routine_antithetic_variate.cc",
    "",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 500, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 4,
                                       1, &namefunlist[0] },

  { SIMPRICEPATH, "SimPricePath", "Bernt Arne Oedegaard, librecipes.a",  
    "Monte Carlo simulations controlled by 'G', 'g' keys. Binomial steps controlled\nby 'Z', 'z' keys. Use '#' to toggle payoffs between arithmetric_avg_call,\ngeometric_avg_call, lookback_callput when displayed.",
    "models/financialrecipes/src/simulate_european_options_generic_routine_price_sequence.cc",
    "",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "Sims", 10, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 3,
                                       1, &namefunlist2[0] },

  { SIMPRICEPATHCONTROLVARIATE, "SimPPControlVariate", "Bernt Arne Oedegaard, librecipes.a",  
    "Monte Carlo simulations controlled by 'G', 'g' keys. Binomial steps controlled\nby 'Z', 'z' keys. Use '#' to toggle payoffs between arithmetric_avg_call,\ngeometric_avg_call, lookback_callput when displayed.",
    "models/financialrecipes/src/simulate_european_options_generic_routine_control_variate.cc",
    "",
    "6;Monte Carlo",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "Sims", 10, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "payoff", 1, 3,
                                       1, &namefunlist2[0] },

  { DISTLOGRAND, "LogNormRandom", "Bernt Arne Oedegaard, librecipes.a",  
    "A Log Normal Random number at time",
    "models/financialrecipes/src/simulate_lognormal_variable.cc",
    "",
    "g;Misc",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 0, 0, 0, 0,
                                       1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Log-normal Random", "", "", "sigma",
                                       0, 0, "", 10, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMFINITEDIFFEXP, "AmFiniteDiffExpl", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/findiff_exp_am_call.cc",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 1, 50, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Steps 2", 250, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EUROFINITEDIFFEXP, "EuroFiniteDiffExpl", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/findiff_exp_eur_call.cc",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 1, 50, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Steps 2", 250, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#ifdef HAVE_NEWMAT_NEWMAT_H

  { AMFINDIFFIMP, "AmFiniteDiffImpl", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/findiff_imp_am_call_newmat.cc",
    "models/financialrecipes/src/findiff_imp_am_put_newmat.cc",
    "5;Trees & Finite Diff;Finite Diff",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 1, 50, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Steps 2", 250, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EURFINDDIFFIMP, "EurFiniteDiffImpl", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/findiff_imp_eur_call_newmat.cc",
    "models/financialrecipes/src/findiff_imp_eur_put_newmat.cc",
    "5;Trees & Finite Diff;Finite Diff",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 1, 50, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Steps 2", 250, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef HAVE_ITPP_ITBASE_H

  { AMFINDIFFIMPPUT, "AmFinDiffImpPut", "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/findiff_imp_am_put_itpp.cc",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       -1, 0, 1, 50, 0, 0,
                                       1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Steps 2", 250, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

  { IMPLIEDNEWTON,      "ImpliedVolBSNewton",  "Bernt Arne Oedegaard, librecipes.a",  
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/financialrecipes/src/black_scholes_imp_vol_newt.cc",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Implied Vol Call", "Implied Vol Put", "Strike", "Call Price",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { IMPLIEDBISECTIONS,      "ImpliedBisections",  "Bernt Arne Oedegaard, librecipes.a",
    "Volatility and option price are swapped in this model. Use 'v', 'V' to adjust\noption price. '+', '-' adjusts size.",
    "models/financialrecipes/src/black_scholes_imp_vol_bisect.cc",
    "",
    "d;Implied Volatility",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Implied Vol Call", "Implied Vol Put", "Strike", "Call Price",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BONDZEROVASICEK,      "BondZeroVasicek", "Bernt Arne Oedegaard, librecipes.a",
    "",
    "models/financialrecipes/src/bondopt_call_vasicek.cc",
    "models/financialrecipes/src/bondopt_put_vasicek.cc",
    "e;Bonds",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                      -1, 1, 0, 0, 0, 0,
                                       0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 2, "maturity", 0, "",
                                       "", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "a",      .03, 0,
                                       1, 1, "b",      .04, 0,
                                       1, 1, "sigma",  .02, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EURODIVIDENDS,      "BS Dividends", "Bernt Arne Oedegaard, librecipes.a",
    "Model not supported in curses version.\nDividends can not be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/black_scholes_call_div.cc",
    "models/financialrecipes/src/black_scholes_put_div.cc",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 1.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividends","Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMDISDIVSBINOMIAL,      "AmDisDivsBinomial", "Bernt Arne Oedegaard, librecipes.a",
    "Model not supported in curses version.\nDividends can not be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/bin_am_div_call.cc",
    "models/financialrecipes/src/bin_am_div_put.cc",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 10, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividends","Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { AMPROPORTDIVSBINOMIAL,    "AmProportDivsBinom", "Bernt Arne Oedegaard, librecipes.a",
    "Model not supported in curses version.\nDividends can not be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/bin_am_prop_div_call.cc",
    "models/financialrecipes/src/bin_am_prop_div_put.cc",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "Yields","Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BERMUDANBINOMIAL,    "Bermudan Binomial", "Bernt Arne Oedegaard, librecipes.a",
    "Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/bermudan_call_option.cc",
    "models/financialrecipes/src/bermudan_put_option.cc",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       1, // supportRealTime    
                                       0, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises","Call", "Put", "Strike", "sigma",
                                       1, 1, "q", 1.0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BSCOUPONBOND,    "BS Coupon Bond", "Bernt Arne Oedegaard, librecipes.a",
    "Model not supported in curses version.\nDividends can not be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/bondopt_call_coupon_bs.cc",
    "models/financialrecipes/src/bondopt_put_coupon_bs.cc",
    "7;Discrete Dividend",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 0.03, "Expiration", 0, "", 0, "",
                                       "Price", "Coupons","Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { WARRANT_NO_DIV,      "WarrantsBS",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/warrant_price_black_scholes.cc",
    "",
    "0;BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Warrants", 1000,  100000,
                                       2, 0, "Shares",   10000, 100000,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { WARRANT_DIV,      "WarrantsBS Div",  "Bernt Arne Oedegaard, librecipes.a",  
    "Continuous dividends supported.",
    "models/financialrecipes/src/warrant_price_black_scholes_dividends.cc",
    "",
    "0;BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "sigma",
                                       2, 0, "Warrants", 1000,  100000,
                                       2, 0, "Shares",   10000, 100000,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { EURBOND_HO_LEE,      "EuroBond Ho Le",  "Bernt Arne Oedegaard, librecipes.a",  
    "Not supported in curses version.\nPlease use GUI version of program.",
    "models/financialrecipes/src/term_structure_class_ho_lee_price_bond_option.cc",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, BOND_CLASS, 0,
                                       1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       5, 100, "T2", 1, "T1", 1, "Call",
                                       "K", "Coupons", "0Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0,          // Z
                                       0, 0, "", 0, 0,          // B
                                       0, 0, "", 0, 0,          // J
                                       0, 0, "", 0, 0,          // P
                                       0, 0, "", 0, 0,          // Q
                                       0, 0, "", 0, 0,          // R
                                       1, 0, "delta", 0.98, 0,  // S
                                       1, 0, "pi",    0.5,  0,  // T
                                       1, 0, " Term Structure ", 1, 7,
                                       1, 0 },

  { TERMFLAT,      "TermFlat",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/term_structure_class_flat.cc",
    "models/financialrecipes/src/term_structure_class_flat.h",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TERMCIR,      "TermCir",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/term_structure_class_cir.cc",
    "models/financialrecipes/src/termstru_discfact_cir.cc",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "kappa",   .01, 0,
                                       1, 1, "lambda",  0.0, 0,
                                       1, 1, "theta",  0.08, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TERMVASICEK,      "TermVasicek",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/term_structure_class_vasicek.cc",
    "models/financialrecipes/src/termstru_discfact_vasicek.cc",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "a",  .01, 0,
                                       1, 1, "b",  0.0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },
/* prototyped but not defined...

  { TERMDISESTCIR,      "TermDisfactCir",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/",
    "",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "a",   .01, 0,
                                       1, 1, "b",  0.0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

*/

/* prototyped but not defined...

  { TERMYIELDBLISS,      "TermYieldBliss",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/",
    "",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "a",   .01, 0,
                                       1, 1, "b",  0.0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

*/

  { TERMNELSONSIEGEL,      "TermNelsonSiegel",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/term_structure_class_nelson_siegel.cc",
    "models/financialrecipes/src/termstru_yield_nels_sie.cc",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "beta0",  .01, 0,  // Z
                                       1, 1, "beta1",  0.0, 0,  // B
                                       1, 1, "beta2",    0, 0,  // J
                                       1, 1, "lambda",   0, 0,  // P
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TERMSVENSSON,      "TermSvensson",  "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/term_structure_class_svensson.cc",
    "models/financialrecipes/src/termstru_yield_svensson.cc",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "T2", 1, "T1", 0, "",
                                       "", "Dividend", "Yield", "", "", "sigma",
                                       1, 1, "beta0",  .01, 0,   // Z
                                       1, 1, "beta1",  0.0, 0,   // B
                                       1, 1, "beta2",    0, 0,   // J
                                       1, 1, "beta3",    0, 0,   // P
                                       1, 1, "tau1",     0, 0,   // Q
                                       1, 1, "tau2",     0, 0,   // R
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TERMCUBICSPLINE,    "TermCubicSpline",  "Bernt Arne Oedegaard, librecipes.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/term_structure_class_cubic_spline.cc",
    "models/financialrecipes/src/termstru_discfact_cubic_spline.cc",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 0.01, "T2", 1, "T1", 0, "",
                                       "", "Term Knots", "Yield", "", "", "sigma",
                                       1, 1, "b",   .1, 0,    // Z
                                       1, 1, "c",   0.1, 0,   // B
                                       1, 1, "d",  -0.1, 0,   // J
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TERMINTERPOLATED,    "TermInterpolated",  "Bernt Arne Oedegaard, librecipes.a",  
    "Model not supported in curses version.\nNot all variables can be controlled. Please use GUI version of program.",
    "models/financialrecipes/src/term_structure_class_interpolated.cc",
    "models/financialrecipes/src/term_structure_class_interpolated.h",
    "f;Term Structures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, TERMSTRUCTURE_CLASS, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       3, 0.01, "T2", 1, "T1", 0, "",
                                       "", "Term Yields", "Yield", "", "", "sigma",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { FUTURES,           "Futures",      "Bernt Arne Oedegaard, librecipes.a",  
    "",
    "models/financialrecipes/src/futures_price.cc",
    "",
    "a;Futures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, FUTURES_CLASS, 0,
                                       1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Spot", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef ABRADFORD

  { FUTURES2,          "Futures Div",     "Anthony Bradford, libabradford.a",
    "Continuous dividends supported.",
    "models/abradford/future.cpp",
    "",
    "a;Futures",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, FUTURES_CLASS, 0,
                                       1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Spot", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BACHELIER,      "Bachelier-1900", "Anthony Bradford, libabradford.a",  
    "Louis Bachelier, French Mathematician",
    "models/abradford/pre-BSM.cpp",
    "",
    "i;Pre-BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BACHELIERMODIFIED,      "BachelierMod", "Anthony Bradford, libabradford.a",  
    "Bachelier Model modified to adjust for time value of money",
    "models/abradford/pre-BSM.cpp",
    "",
    "i;Pre-BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SPRENKLE,      "Sprenkle-64", "Anthony Bradford, libabradford.a",  
    "",
    "models/abradford/pre-BSM.cpp",
    "",
    "i;Pre-BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "Avg Growth", .04, 0,
                                       1, 1, "Market Risk Adverse", .02, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BONESS,      "Boness-64", "Anthony Bradford, libabradford.a",  
    "",
    "models/abradford/pre-BSM.cpp",
    "",
    "i;Pre-BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "Exp Rate of Ret", .04, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { SAMUELSON,      "Samuelson-65", "Anthony Bradford, libabradford.a",  
    "",
    "models/abradford/pre-BSM.cpp",
    "",
    "i;Pre-BSM",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 1, "Positive Drift", .04, 0,
                                       1, 1, "Avg Growth Call", .06, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef FINRECIPES

  { BONDS,           "Bond Flat",      "Bernt Arne Oedegaard, librecipes.a",  
    "Not supported in curses version.\nPlease use GUI version of program.",
    // currently only we can display two source files...hope to include all the functions of the
    // analytics in the future...source path should have a separator ';' to include multiple files in 1 reference...
    "models/financialrecipes/src/bonds_price.cc",
    "models/financialrecipes/src/bonds_duration.cc",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, BOND_CLASS, 1,
                                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       5, 1.25, "Expiration", 0, "", 0, "",
                                       "Face", "Coupons & Final Payment", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,                       // Z
                                       0, 0, "", 0, 0,                       // B
                                       0, 0, "", 0, 0,                       // J
                                       0, 0, "", 0, 0,                       // P
                                       2, 0, "Periodicity", 2, 12,           // Q
                                       1, 0, "Time to First Coupon", .25, 0, // R
                                       2, 0, "# of Coupons", 5, 0,           // S
                                       1, 1, "Coupon", 1.25, 0,              // T
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { BONDSTERM,       "Bond w/Term",      "Bernt Arne Oedegaard, librecipes.a",  
    "Not supported in curses version.\nPlease use GUI version of program.",
    // currently only we can display two source files...hope to include all the functions of the
    // analytics in the future...
    "models/financialrecipes/src/bonds_price_termstru.cc",
    "models/financialrecipes/src/bonds_duration_termstru.cc",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, BOND_CLASS, 0,
                                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       5, 1.25, "T2", 1, "T1", 0, "",
                                       "", "Coupons & Final Payment", "Call", "Put", "Strike", "sigma",
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // Reserved by a Term Structure model...
                                       0, 0, "", 0, 0, // S
                                       0, 0, "", 0, 0, // T
                                       1, 0, " Term Structure ", 1, 7,
                                       1, 0 },

  { BONDSPRINCIPAL,       "Bond w/Principal",      "Bernt Arne Oedegaard, librecipes.a",  
    "Not supported in curses version.\nPlease use GUI version of program.",
    "models/financialrecipes/src/bonds_price_both.cc",
    "",
    "e;Bonds",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 1, BOND_CLASS, 1,
                                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       6, 20, "Expiration", 0, "", 0, "",
                                       "Face", "Coupons", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "P Periodicity", 2, 12,         // Z
                                       1, 0, "Time to First Prin", .25, 0,   // B
                                       2, 0, "# of Principal", 5, 0,         // J
                                       1, 1, "Principal", 20, 0,             // P
                                       2, 0, "C Periodicity", 2, 12,         // Q
                                       1, 0, "Time to First Coupon", .25, 0, // R
                                       2, 0, "# of Coupons", 5, 0,           // S
                                       1, 1, "Coupon", 1.25, 0,              // T
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { IRR,           "PV / IRR",      "Bernt Arne Oedegaard, librecipes.a",  
    "Not supported in curses version.\nPlease use GUI version of program.",
    // currently only we can display two source files...hope to include all the functions of the
    // analytics in the future...
    "models/financialrecipes/src/cflow_irr.cc",
    "models/financialrecipes/src/cflow_pv.cc",
    "g;Misc",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 2, BOND_CLASS, 1,
                                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       5, 1.25, "Expiration", 0, "", 0, "",
                                       "Face", "Cash Flows", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

#ifdef HAVE_QL_QUANTLIB_HPP

    { QUANTLIB_BLACKSCHOLES_EUROPEAN,  "Black-Scholes 4", "QuantLib, QuantLib.a",  
    "Black-Scholes European QuantLib. Model is only accurate to the day.",
    "",
    "",
    "0;BSM",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_HESTON_SEMI_ANALYTIC_EUR,  "Heston Semi-Analytic", "QuantLib, QuantLib.a",  
    "Heston Semi-Analytic European. Model is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Heston",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BARONE_ADESI_WHALEY_AM,  "Barone-Adesi Whaley", "QuantLib, QuantLib.a",  
    "Barone-Adesi and Whaley approximation for American. Model is only accurate to the day.",
    "",
    "",
    "1;American Options",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BJERKSUND_STENSLAND_AM,  "Bjerksund Stensland", "QuantLib, QuantLib.a",  
    "Bjerksund/Stensland approximation for American. Model is only accurate to the day.",
    "",
    "",
    "1;American Options",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_FINITE_DIFFERENCES_EUROPEAN,  "Finite Diff Euro", "QuantLib, QuantLib.a",  
    "Finite Differences European. Model is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 801, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_FINITE_DIFFERENCES_AMERICAN,  "Finite Diff American", "QuantLib, QuantLib.a",  
    "Finite Differences American. Model is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_MC_CRUDE_EUR,  "MC (Crude)", "QuantLib, QuantLib.a",  
    "Monte Carlo (Crude) European. Model is only accurate to the day.",
    "",
    "",
    "6;Monte Carlo",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 1, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "mcSeed",      42, 0,
                                       1, 0, "Tolerance", 0.15, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_QMC_SOBOL_EUR,  "QMC (Sobol)", "QuantLib, QuantLib.a",  
    "QMC (Sobol) European. Model is only accurate to the day.",
    "",
    "",
    "6;Monte Carlo",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "nSamples", 1000, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM,  "MC (Longstaff Schwartz)", "QuantLib, QuantLib.a",  
    "Monte Carlo (Longstaff Schwartz). American option. Model is only accurate to the day.",
    "",
    "",
    "6;Monte Carlo",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 3, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "mcSeed",      42, 0,
                                       1, 0, "Tolerance", 0.15, 0,
                                       2, 0, "nSamples", 1000, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM,  "Jarrow-Rudd", "QuantLib, QuantLib.a",  
    "Binomial Jarrow-Rudd with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM, "Cox-Ross-Rubinstein", "QuantLib, QuantLib.a",  
    "Binomial Cox-Ross-Rubinstein with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM, "Additive Equiprob", "QuantLib, QuantLib.a",  
    "Binomial Additive Equiprobabilities with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM, "Trigeorgis", "QuantLib, QuantLib.a",  
    "Binomial Trigeorgis with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },
  
    { QUANTLIB_BINOMIAL_TIAN_EUR_AM, "Tian", "QuantLib, QuantLib.a",  
    "Binomial Tian with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM, "Leisen-Reimer", "QuantLib, QuantLib.a",  
    "Leisen-Reimer with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_BINOMIAL_JOSHI_EUR_AM, "Joshi", "QuantLib, QuantLib.a",  
    "Joshi with European and American options.\nModel is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       1, 0, "Type", 1, 2,
                                       1, &QuantLibnamelistamericanoreuropean[0] },

    { QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN,  "Bates Semi-Analytic", "QuantLib, QuantLib.a",  
    "Bates Semi-Analytic for European. Model is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_INTEGRAL_EUROPEAN,  "Integral", "QuantLib, QuantLib.a",  
    "Integral for European. Model is only accurate to the day.",
    "",
    "",
    "5;Trees & Finite Diff;Finite Diff",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_FINITE_DIFFERENCES_BERMUDAN,  "Finite Diff Bermudan", "QuantLib, QuantLib.a",  
    "Finite Differences Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Finite Diff;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN,  "Jarrow Rudd", "QuantLib, QuantLib.a",  
    "Jarrow Rudd Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN,  "Cox-Ross-Rubinstein", "QuantLib, QuantLib.a",  
    "Cox-Ross-Rubinstein Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN,  "Additive Equiprob", "QuantLib, QuantLib.a",  
    "Additive Equiprobabilities Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN,  "Trigeorgis", "QuantLib, QuantLib.a",  
    "Trigeorgis Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_TIAN_BERMUDAN,  "Tian", "QuantLib, QuantLib.a",  
    "Tian Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN,  "Leisen-Reimer", "QuantLib, QuantLib.a",  
    "Leisen-Reimer Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_BINOMIAL_JOSHI_BERMUDAN,  "Joshi", "QuantLib, QuantLib.a",  
    "Joshi Bermudan. Model not supported in curses version.\nExercise times can not be controlled. Please use GUI version of program.",
    "",
    "",
    "5;Trees & Finite Diff;Binomial;Bermudan",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 1, 5, 0, 1,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Exercises", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_DISCRETE_AVERAGE_ASIAN,  "Discrete Avg Asian", "QuantLib, QuantLib.a",  
    "Discrete Average Asian. Model not supported in curses version.\nFixing dates can not be controlled. Please use GUI version of program.",
    "",
    "",
    "c;Asian",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       4, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Fixings", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "runningSum", 1, 0,
                                       2, 0, "pastFixings", 0, 0,
                                       1, 1, "Dividend", 0.03, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_CONTINUOUS_AVERAGING_ASIAN,  "Continuous Avg Asian", "QuantLib, QuantLib.a",  
    "",
    "",
    "",
    "c;Asian",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

    { QUANTLIB_CONTINUOUS_LEVY_ASIAN,  "LevyAsian Cont", "QuantLib, QuantLib.a",  
    "",
    "",
    "",
    "c;Asian",
                                       0, // supportRealTime
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       // Supports dividend
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "Average", 80, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif
  
#ifdef DUMMYTESTMODELS

  { TESTOPTION1,  "Testing Option1", "Test",  
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TESTOPTION2,  "Testing Option2", "Test",  
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "1", 1, 0,
                                       1, 0, "2", 1, 0,
                                       1, 0, "3", 1, 0,
                                       1, 0, "4", 1, 0,
                                       1, 0, "5", 1, 0,
                                       1, 0, "6", 1, 0,
                                       1, 0, "7", 1, 0,
                                       1, 0, "8", 1, 0,
                                       1, 0, "Test State", 1, 4,
                                       1, &nametestlist[0] },

  { TESTOPTION3,  "Testing Option3", "Test",
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 1, "Dividend", 1, "t3",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       1, 0, "1", 1, 0,
                                       1, 0, "2", 1, 0,
                                       1, 0, "3", 1, 0,
                                       1, 0, "4", 1, 0,
                                       1, 0, "5", 1, 0,
                                       1, 0, "6", 1, 0,
                                       1, 0, "7", 1, 0,
                                       1, 0, "8", 1, 0,
                                       1, 0, "Test State", 1, 100,
                                       0, 0 },

  { TESTOPTION4,  "Testing Option4", "Test",
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 1, "Dividend", 1, "t3",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       1, 0, "Test State", 1, 100,
                                       0, 0 },

     { TESTOPTION5,  "Testing Option5", "Test",
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 1, 100, 0, 0,
                                       1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
                                       1, 0.0, "Expiration", 1, "Dividend", 1, "t3",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       2, 0, "int", 1, 0,
                                       1, 0, "Test State", 1, 11,
                                       1, &nametestlist2[0] },

  { TESTOPTIONONEDIVIDEND1, "Testing Option6", "Test",  
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 1, "dividend", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TESTOPTIONONEDIVIDEND2, "Testing Option7", "Test",
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 1, 0, 0, 0, 0,
                                       1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 2, "dividend", 0, "",
                                       "Price", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TESTFUTURES1,    "Testing Future1",      "Test",
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 1, 0,
                                       1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0.0, "Expiration", 0, "", 0, "",
                                       "Spot", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

  { TESTFUTURES2,    "Testing Future2",      "Test",  
    "",
    "",
    "",
    "g;Misc;Test",
                                       1, // supportRealTime    
                                       1, // filterNegativePrices
                                       0, 0, 0, 0, 1, 0,
                                       1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       1, 0.0, "Expiration", 0, "", 0, "",
                                       "Spot", "Dividend", "Call", "Put", "Strike", "Standard Deviation",
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0, "", 0, 0,
                                       0, 0 },

#endif

};

const int sizeofstrike_control = sizeof(strike_control);
const int sizeofoption_algorithms = sizeof(option_algorithms);
const int sizeofintegration_method = sizeof(integration_method);
