/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: prototypes.h of optionmatrix                                       */
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

#ifndef __PROTOTYPES__
#define __PROTOTYPES__

#ifdef ABRADFORD
 #include "../models/abradford/basicmodels.h"
#endif

#ifdef SPINSKY
 #include "../models/spinsky/binomial.h"
#endif

#if defined(__cplusplus) && defined(FINRECIPES)

 #include "../models/financialrecipes/src/fin_recipes.h"
 #include "../models/financialrecipes/src/fin_recipes_gsl.h"
 #include "../models/financialrecipes/src/fin_recipes_extra.h"

#ifdef HAVE_ITPP_ITBASE_H
 #include "../models/financialrecipes/src/fin_recipes_itpp.h"
#endif

#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef METAOPTIONS
  #include "../models/metaoptions/src/metaoptions.h"
#endif

#ifdef __cplusplus
}
#endif

#endif // __PROTOTYPES__
