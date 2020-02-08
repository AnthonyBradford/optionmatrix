/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: futures.cpp of optionmatrix                                        */
/*                                                                          */
/* Copyright (c) Anthony Bradford. 2012.                                    */
/* anthony_bradford@yahoo.com                                               */
/*                                                                          */
/* optionmatrix may be freely redistributed.                                */
/* See file COPYING included with this distribution for license information */

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

#include "defs.h"
#include "extern.h"
#include "prototypes.h"

struct _data future(struct _data *dat)
{
  double price;

  const double spot = dat->price;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double dividend = dat->dividend;

  switch(dat->modeltype)
  {

#ifdef FINRECIPES

    case FUTURES:

      if(dat->debug)
        logger( (char *)"futures_price", 3,
                (double)spot,(double)rate,(double)t);

      price = futures_price(spot,rate,t);

      break;

#endif // FINRECIPES

#ifdef ABRADFORD

    case FUTURES2:
    
      if(dat->debug)
        logger( (char *)"futures_price", 4,
                (double)spot,(double)rate,(double)dividend,(double)t);

      price = futures_price(spot,rate,dividend,t);

      break;

#endif // ABRADFORD

#ifdef DUMMYTESTMODELS

    case TESTFUTURES1:
    case TESTFUTURES2:

      price = 0;

      break;

#endif // DUMMYTESTMODELS

     default:

      fprintf(stderr,"future(): No implementation for case %d\n",dat->modeltype);

      break;

  } // switch(dat->modeltype)

  dat->future = price;

  return *dat;

} // struct _data future(struct _data *dat)
