/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: tickers.cpp of optionmatrix                                        */
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

/* get the industry strike price code/ticker from the strike price */
char strike_price_codes(const double strike)
{
    /* 
     * superset of The Options Industry Council 
     * based on Option Tickers in http://investopedia.com
     */

    const char strike_codes[] = {
       'Z', 'A', 'U', 'B', 'V', 'C', /* 6  */
       'W', 'D', 'X', 'E', 'Y', 'F', /* 12 */
       'Z', 'G', 'U', 'H', 'V', 'I', /* 18 */
       'W', 'J', 'X', 'K', 'Y', 'L', /* 24 */
       'Z', 'M', 'U', 'N', 'V', 'O', /* 30 */
       'W', 'P', 'X', 'Q', 'Y', 'R', /* 36 */
       'Z', 'S', 'U', 'T', 'V', 'A', /* 42 */
       'W', 'B', 'X', 'C', 'Y', 'D', /* 48 */
       'Z', 'E', 'U', 'F', 'V', 'G', /* 54 */
       'W', 'H', 'X', 'I', 'Y', 'J', /* 60 */
       'Z', 'K', 'U', 'L', 'V', 'M', /* 64 */
       'W', 'N', 'X', 'O', 'Y', 'P', /* 68 */
       'Z', 'Q', 'U', 'R', 'V', 'S', /* 74 */
       'W', 'T', 'X', 'A', 'Y', 'B', /* 80 */
       'Z', 'C', 'U', 'D', 'V', 'E', /* 86 */
       'W', 'F', 'X', 'G', 'Y', 'H', /* 92 */
       'Z', 'I', 'J' }; 
     
    const double strikes[]= {
   /*Z*/   2.5, /*A*/  5,  /*U*/  7.5, /*B*/  10,  /*V*/ 12.5, /*C*/  15,  /*  6 */
   /*W*/  17.5, /*D*/ 20,  /*X*/ 22.5, /*E*/  25,  /*Y*/ 27.5, /*F*/  30,  /* 12 */
   /*Z*/  32.5, /*G*/ 35,  /*U*/ 37.5, /*H*/  40,  /*V*/ 42.5, /*I*/  45,  /* 18 */
   /*W*/  47.5, /*J*/ 50,  /*X*/ 52.5, /*K*/  55,  /*Y*/ 57.5, /*L*/  60,  /* 24 */
   /*Z*/  62.5, /*M*/ 65,  /*U*/ 67.5, /*N*/  70,  /*V*/ 72.5, /*O*/  75,  /* 30 */
   /*W*/  77.5, /*P*/ 80,  /*X*/ 82.5, /*Q*/  85,  /*Y*/ 87.5, /*R*/  90,  /* 36 */
   /*Z*/  92.5, /*S*/ 95,  /*U*/ 97.5, /*T*/ 100,  /*V*/102.5, /*A*/ 105,  /* 42 */
   /*W*/ 107.5, /*B*/110,  /*X*/112.5, /*C*/ 115,  /*Y*/117.5, /*D*/ 120,  /* 48 */
   /*Z*/ 122.5, /*E*/125,  /*U*/127.5, /*F*/ 130,  /*V*/132.5, /*G*/ 135,  /* 54 */
   /*W*/ 137.5, /*H*/140,  /*X*/142.5, /*I*/ 145,  /*Y*/147.5, /*J*/ 150,  /* 60 */
   /*Z*/ 152.5, /*K*/155,  /*U*/157.5, /*L*/ 160,  /*V*/162.5, /*M*/ 165,  /* 64 */
   /*W*/ 167.5, /*N*/170,  /*X*/172.5, /*O*/ 175,  /*Y*/177.5, /*P*/ 180,  /* 68 */
   /*Z*/ 182.5, /*Q*/185,  /*U*/187.5, /*R*/ 190,  /*V*/192.5, /*S*/ 195,  /* 74 */
   /*W*/ 197.5, /*T*/200,  /*X*/202.5, /*A*/ 205,  /*Y*/207.5, /*B*/ 210,  /* 80 */
   /*Z*/ 212.5, /*C*/215,  /*U*/217.5, /*D*/ 220,  /*V*/222.5, /*E*/ 225,  /* 86 */
   /*W*/ 227.5, /*F*/230,  /*X*/232.5, /*G*/ 235,  /*Y*/237.5, /*H*/ 240,  /* 92 */
   /*Z*/ 242.5, /*I*/245,  /*J*/250 };

    int y = 0;
    int x = 0;
    double discard;

    for(y = 0; y <= 5000; y += 200)
    {
       for(x = 0; x < (signed)sizeof(strike_codes); x++)
       {
        if( strike <= (strikes[x]+y) )
        {
          if( strikes[x]+y > 242.5 )
          {
            if( modf(strikes[x]+y,&discard) == .5 )
            {
               ++x;
               continue;
            }
          }

          /*printw("Strike Code = %d\n",x);*/

          return strike_codes[x];
        }
      }
    }

    return  ' ';

} // char strike_price_codes(const double strike)
