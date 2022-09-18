/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: options_calls.cpp of optionmatrix                                  */
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

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)
# include <ql/quantlib.hpp>
# include <QuantLib.h>
#endif

#include "extern.h"
#include "prototypes.h"

struct _data option_call(struct _data *dat)
{
  double callprice;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t  = dat->t[0] - dat->te;
  const double t2 = dat->t[1] - dat->te2;
  const double t3 = dat->t[2] - dat->te3;
  const double volatility = dat->volatility;
  const double dividend = dat->dividend;

  double calldelta = 0;  /* this is a dummy variable */

  //g_print("t3 = %f\n", t3);

  time_t currentTime;
  struct tm *currentTime_tm;;
  time(&currentTime);
  currentTime_tm = localtime(&currentTime);

  if(t <= 0.0)
  {
    dat->call = 0.0;

    return *dat;
  }

  try {

  switch(dat->modeltype)
  {

#ifdef ABRADFORD

    case BLACKSCHOLES:

      if(dat->debug)
        logger( (char *)"black_scholes_call", 5,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility);

      callprice = black_scholes_call(price,strike,rate,t,volatility,&calldelta);

      break;

    case MERTON73:

      if(dat->debug)
        logger( (char *)"merton73_call", 6,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility,(double)dividend,&calldelta);

      callprice = merton73_call(price,strike,rate,t,volatility,dividend,&calldelta);

      break;

    case BLACK76:

      if(dat->debug)
        logger( (char *)"black76call", 6,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility);
      
      callprice = black76call(price,strike,rate,t,volatility,&calldelta);

      break;

  case BACHELIER:

      if(dat->debug)
        logger( (char *)"bachelier_call", 4,
                (double)price,(double)strike,(double)t,(double)volatility);

      callprice = bachelier_call(price, strike, t, volatility);

      break;

  case BACHELIERMODIFIED:

      if(dat->debug)
        logger( (char *)"bachelier_modified_call", 5,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility);

      callprice = bachelier_modified_call(price, strike, rate, t, volatility);

      break;

  case SPRENKLE:

      if(dat->debug)
        logger( (char *)"sprenkle_call", 6,
                (double)price,(double)strike,(double)t,(double)volatility,(double)dat->UseZ,(double)dat->UseB);

      callprice = sprenkle_call(price, strike, t, volatility, dat->UseZ, dat->UseB);

      break;

  case BONESS:

      if(dat->debug)
        logger( (char *)"boness_call", 5,
                (double)price,(double)strike,(double)t,(double)volatility,(double)dat->UseZ);

      callprice = boness_call(price, strike, t, volatility, dat->UseZ);

      break;

  case SAMUELSON:

      if(dat->debug)
        logger( (char *)"samuelson_call", 6,
                (double)price,(double)strike,(double)t,(double)volatility,(double)dat->UseZ,(double)dat->UseB);

      callprice = samuelson_call(price, strike, t, volatility, dat->UseZ, dat->UseB);

      break;

#endif //  ABRADFORD

#ifdef SPINSKY

    case AMERICAN_CRR:
      {

        Ivar data;
        data.S = data.X = data.T = data.sigma = data.mu = 0;

        data.S = price;
        data.X = strike;
        data.T = t;
        data.sigma = volatility;
        data.mu = rate;

        callprice = (double) option_price(data,dat->steps,AMERCALL,CRR);

      }

      break;

    case AMERICAN_EQUIPROB:
      {

        Ivar data;
        data.S = data.X = data.T = data.sigma = data.mu = 0;
        
        data.S = price;
        data.X = strike;
        data.T = t;
        data.sigma = volatility;
        data.mu = rate;
        
        callprice = (double) option_price(data,dat->steps,AMERCALL,EQUIPROB);
      }

      break;

    case EURO_CRR:
      {

        Ivar data;
        data.S = data.X = data.T = data.sigma = data.mu = 0;
        
        data.S = price;
        data.X = strike;
        data.T = t;
        data.sigma = volatility;
        data.mu = rate;

        callprice = (double) option_price(data,dat->steps,EUROCALL,CRR);
      }

      break;

    case EURO_EQUIPROB:
      {

        Ivar data;
        data.S = data.X = data.T = data.sigma = data.mu = 0;

        data.S = price;
        data.X = strike;
        data.T = t;
        data.sigma = volatility;
        data.mu = rate;

        callprice = (double) option_price(data,dat->steps,EUROCALL,EQUIPROB);

      }

      break;

#endif // SPINSKY

#ifdef METAOPTIONS

    case BLACKSCHOLES2:

      if(dat->debug)
        logger( (char *)"blackscholes", 6,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)volatility);

       callprice = blackscholes(1,price,strike,t,rate,volatility);

      break;

    case GBS:

      if(dat->debug)
        logger( (char *)"gbs", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = gbs(1,price,strike,t,rate,dividend,volatility);

      break;

    case MERTON73B:

      if(dat->debug)
        logger( (char *)"merton73", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = merton73(1,price,strike,t,rate,dividend,volatility);

      break;

    case GFRENCH:

      if(dat->debug)
        logger( (char *)"french", 8,
                (double)1,(double)price,(double)strike,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = french(1,price,strike,t2,t,rate,dividend,volatility);

      break;

    case GCARRY:

      if(dat->debug)
        logger( (char *)"carry call", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = carry(1,price,strike,t,rate,dividend,volatility);

      break;

    case BAWAMERICAN:

      if(dat->debug)
        logger( (char *)"BAWAmericanApprox", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = BAWAmericanApprox(1,price,strike,t,rate,dividend,volatility);

      break;

    case BSAMERICAN:

      if(dat->debug)
        logger( (char *)"BSAmericanApprox", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = BSAmericanApprox(1,price,strike,t,rate,dividend,volatility);
 
      break;

    case BLACK76B:

      if(dat->debug)
        logger( (char *)"black76", 6,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)volatility);

      callprice = black76(1,price,strike,t,rate,volatility);

      break;

    case ASSETORNOTHING:

      if(dat->debug)
        logger( (char *)"AssetOrNothing", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = AssetOrNothing(1,price,strike,t,rate,dividend,volatility);

      break;

    case CASHORNOTHING:

      if(dat->debug)
        logger( (char *)"CashOrNothing", 8,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = CashOrNothing(1,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case EXTENDIBLEWRITER:
      {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"ExtendibleWriter", 9,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = ExtendibleWriter(1,price,strike,dat->UseZ,t2,t,rate,dividend,volatility);

      }

      break;

    case CALLSONOPTIONS:
      {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"OptionsOnOptions", 9,
                (double)OOO_CALL_ON_CALL,(double)price,(double)strike,(double)dat->UseZ,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = OptionsOnOptions(OOO_CALL_ON_CALL,price,strike,dat->UseZ,t2,t,rate,dividend,volatility);

      }

      break;

    case PUTSONOPTIONS:

      if(dat->debug)
        logger( (char *)"OptionsOnOptions", 9,
                (double)OOO_PUT_ON_CALL,(double)price,(double)strike,(double)dat->UseZ,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = OptionsOnOptions(OOO_PUT_ON_CALL,price,strike,dat->UseZ,t2,t,rate,dividend,volatility);

      break;

    case ROLLGESKEWHALEY:

      if(dat->debug)
        logger( (char *)"RollGeskeWhaley", 7,
                price,strike,(t2>t?(double)0:(double)t2),t,rate,(t2>t?(double)0:(double)dividend),volatility);

      callprice = RollGeskeWhaley(price,strike,(t2 > t ? 0 : t2 ),t,rate,(t2 > t ? 0 : dividend ),volatility);

      break;

    case EXTREMESPREADOPTION:

      if(dat->debug)
        logger( (char *)"ExtremeSpreadOption", 9,
                (double)transextremeoptioncall[dat->UsePound-1],(double)price,(double)strike,(double)dat->UseB,(t2 > t ? (double)0 : (double)t2 ),(double)t,(double)rate,(t2 > t ? (double)0 : (double)dividend ),(double)volatility);
      
      callprice =  ExtremeSpreadOption(transextremeoptioncall[dat->UsePound-1],price,strike,dat->UseB,(t2 > t ? 0 : t2 ),t,rate,(t2 > t ? 0 : dividend ),volatility);

      break;

    case EXTREMESPREADOPTION2:

      if(dat->debug)
        logger( (char *)"ExtremeSpreadOption", 9,
                (double)transextremeoptioncall[dat->UsePound-1],(double)price,(double)dat->UseB,(double)strike,(t2 > t ? (double)0 : (double)t2 ),(double)t,(double)rate,(t2 > t ? (double)0 : (double)dividend ),(double)volatility);

      callprice =  ExtremeSpreadOption(transextremeoptioncall[dat->UsePound-1],price,dat->UseB,strike,(t2 > t ? 0 : t2 ),t,rate,(t2 > t ? 0 : dividend ),volatility);

      break;

    case SIMPLECHOOSER:

      if(dat->debug)
        logger( (char *)"SimpleChooser", 7,
                (double)price,(double)strike,(double)t2,(double)t,(double)rate,(double)dat->UseZ,(double)volatility);

      callprice = SimpleChooser(price,strike,t2,t,rate,dat->UseZ,volatility);

      break;

    case PARTIALFIXEDLB:
      {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"PartialFixedLB", 8,
                (double)1,(double)price,(double)strike,(t2 > t ? (double)0 : (double)t2),(double)t,(double)rate,(t2 > t ? (double)0 : (double)dividend),(double)volatility);

      callprice = PartialFixedLB(1,price,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      }

      break;

    case EXECUTIVE:

      if(dat->debug)
        logger( (char *)"Executive", 8,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseZ);

      callprice = Executive(1,price,strike,t,rate,dividend,volatility,dat->UseZ);

      break;

    case GARMANKOHLHAGEN:

      if(dat->debug)
        logger( (char *)"GarmanKohlhagen", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dat->UseZ,(double)volatility);

      callprice = GarmanKohlhagen(1,price,strike,t,rate,dat->UseZ,volatility);

      break;

    case LOOKBARRIER:
     {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"LookBarrier", 9,
                (double)dat->UsePound+2,(double)price,(double)strike,(double)dat->UseZ,(t2 > t ? (double)0 : (double)t2),(double)t,(double)rate,(double)(t2 > t ? (double)0 : (double)dividend),(double)volatility);

      callprice = LookBarrier(dat->UsePound+2,price,strike,dat->UseZ,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

     }

     break;

    case PARTIALTIMEBARRIER:
     {
      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"PartialTimeBarrier", 9,
                (double)(dat->UsePound-1),
                (double)price,
                (double)strike,
                (double)dat->UseZ,
                (t2 > t ? (double)0 : (double)t2),
                (double)t,
                (double)rate,
                (t2 > t ? (double)0 : (double)dividend),
                (double)volatility);

      callprice = PartialTimeBarrier((const char*)&namelistpartialtimebarrier[dat->UsePound-1],price,strike,dat->UseZ,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

     }

     break;

    case GAPOPTION:

      if(dat->debug)
        logger( (char *)"GapOption", 8,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t,(double)rate,(double)dividend,(double)volatility);
 
      callprice = GapOption(1,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case JUMPDIFFUSION:
      
      if(dat->debug)
        logger( (char *)"JumpDiffusion", 8,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)volatility,(double)dat->UseZ,(double)dat->UseB);

      callprice = JumpDiffusion(1,price,strike,t,rate,volatility,dat->UseZ,dat->UseB);

      break;

    case BISECTION:
      {

      double cprice;

      if(dat->debug)
        logger( (char *)"bisection", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      if( bisection(1,price,strike,t,rate,dividend,volatility,&cprice) == 1 )
        callprice = cprice;
      else
        callprice = 0;

      }

      break;


    case NEWTONRAPHSON:
      {

      double cprice;

      if(dat->debug)
        logger( (char *)"NewtonRaphson", 6,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)volatility);

      if( NewtonRaphson(1,price,strike,t,rate,volatility,&cprice) == 1 )
        callprice = cprice;
      else
        callprice = 0;

      }

      break;

    case BAWBISECTION:

      if(dat->debug)
        logger( (char *)"BAWbisection", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = BAWbisection(1,price,strike,t,rate,dividend,volatility);

      break;

    case BSBISECTION:

      if(dat->debug)
        logger( (char *)"BSbisection", 7,
                (double)1,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = BSbisection(1,price,strike,t,rate,dividend,volatility);

      break;

    case SWAPOPTION:

      if(dat->debug)
        logger( (char *)"Swapoption", 8,
                (double)1,(double)t,(double)dat->UseZ,(double)price,(double)strike,(double)t2,(double)rate,(double)volatility);
      
      callprice = Swapoption(1,t,dat->UseZ,price,strike,t2,rate,volatility);

      break;

    case TURNBULLWAKEMANASIAN:
      {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"TurnbullWakemanAsian", 10,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(double)t,(double)t2,(double)dat->UseB,(double)rate,(double)dividend,(double)volatility);

      callprice = TurnbullWakemanAsian(1,price,dat->UseZ,strike,t,t2,dat->UseB,rate,dividend,volatility);

      }

      break;

    case COMPLEXCHOOSER:
      {

      if( t2 < 0 || t3 < 0 )
      {
        callprice = 0;
        break;
      }

      if(dat->debug)
           logger( (char *)"ComplexChooser", 9,
                                 (double)price,
                                (double)strike,    // Strike Call
                             (double)dat->UseZ,    // Strike Put
                                    (double)t2,    // Time
                                     (double)t,    // Time to Call
                                    (double)t3,    // Time to Put
                                  (double)rate,    // Rate
                             (double)dat->UseJ,    // Cost of carry
                            (double)volatility);

       callprice = ComplexChooser(   price,
                                     strike,    // Strike Call
                                  dat->UseZ,    // Strike Put
                                         t2,    // Time
                                          t,    // Time to Call
                                         t3,    // Time to Put
                                      rate,     // Rate
                                  dat->UseJ,    // Cost of carry
                                  volatility);
       }

      break;

    case SUPERSHARE:

      if(dat->debug)
        logger( (char *)"SuperShare", 7,
                (double)price,(double)strike,(double)dat->UseZ,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = SuperShare(price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case SUPERSHARE2:

      if(dat->debug)
        logger( (char *)"SuperShare", 7,
                (double)price,(double)dat->UseZ,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = SuperShare(price,dat->UseZ,strike,t,rate,dividend,volatility);

      break;

    case VASICEKBONDOPTION:
      
      if(dat->debug)
        logger( (char *)"VasicekBondOption", 9,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t,(double)rate,(double)dat->UseB,(double)dat->UseJ,(double)volatility);

      callprice = VasicekBondOption(1,price,strike,dat->UseZ,t,rate,dat->UseB,dat->UseJ,volatility);

      break;

    case TIMESWITCHOPTION:
      
      if(dat->debug)
        logger( (char *)"TimeSwitchOption", 10,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t,(double)dat->UseB,(double)t2,(double)rate,(double)dividend,(double)volatility);

      callprice = TimeSwitchOption(1,price,strike,dat->UseZ,t,(int)dat->UseB,t2,rate,dividend,volatility);

      break;

    case FOREQUOPTINDOMCUR:

      if(dat->debug)
        logger( (char *)"ForEquOptInDomCur", 10,
                (double)1,(double)dat->UseZ,(double)price,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseB,(double)dat->UseJ);
 
      callprice = ForEquOptInDomCur(1,dat->UseZ,price,strike,t,rate,dividend,volatility,dat->UseB,dat->UseJ);

      break;

    case QUANTO:
        
        if(dat->debug)
          logger( (char *)"Quanto", 11,
                (double)1,(double)dat->UseZ,(double)price,(double)strike,(double)t,(double)rate,(double)dat->UseB,dividend,
                (double)volatility,(double)dat->UseJ,(double)dat->UseP);

        callprice = Quanto(1,dat->UseZ,price,strike,t,rate,dat->UseB,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case EQUITYLINKEDFXO:

      if(dat->debug)
        logger( (char *)"EquityLinkedFXO", 11,
                (double)1,(double)dat->UseZ,(double)price,(double)strike,(double)t,(double)rate,(double)dat->UseB,(double)dividend,(double)volatility,(double)dat->UseJ,(double)dat->UseP);

      callprice = EquityLinkedFXO(1,dat->UseZ,price,strike,t,rate,dat->UseB,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case SPREADAPPROXIMATION:

      if(dat->debug)
        logger( (char *)"SpreadApproximation", 9,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(double)t,(double)rate,(double)volatility,(double)dat->UseB,(double)dat->UseJ);

      callprice = SpreadApproximation(1,price,dat->UseZ,strike,t,rate,volatility,dat->UseB,dat->UseJ);

      break;

    case BINARYBARRIER:

      if(dat->UsePound >= 13)
      {
        if(dat->UseZ == strike)
        {
          // force NaN price
          callprice = NAN;
          break;
        }
      }

      if(dat->debug)
        logger( (char *)"BinaryBarrier", 11,
                (double)dat->UsePound,(double)price,(double)strike,(double)dat->UseZ,(double)dat->UseB,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseJ,(double)dat->UseP);

      callprice = BinaryBarrier(dat->UsePound,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility,(int)dat->UseJ,(int)dat->UseP);

      break;

    case TAKEOVERFXOPTION:

      if(dat->debug)
        logger( (char *)"TakeoverFXoption", 10,
                                   (double)price,
                                   (double)dat->UseZ,
                                   (double)dat->UseB,
                                   (double)strike,
                                   (double)t,
                                   (double)rate,
                                   (double)dat->UseJ,
                                   (double)volatility,
                                   (double)dat->UseQ,
                                   (double)dat->UseR);

      callprice = TakeoverFXoption(
                                   price,
                                   dat->UseZ,
                                   dat->UseB,
                                   strike,
                                   t,
                                   rate,
                                   dat->UseJ,
                                   volatility,
                                   dat->UseQ,
                                   dat->UseR);

      break;

    case AMERICANEXCHANGEOPTION:

      if(dat->debug)
        logger( (char *)"AmericanExchangeOption", 12,
                                           (double)1,
                                           (double)price,      // price
                                           (double)strike,     // strike
                                           (double)dat->UseB,  // B
                                           (double)dat->UseJ,  // J
                                           (double)t,          // time
                                           (double)rate,       // rate
                                           (double)dat->UseP,  // P
                                           (double)dat->UseQ,  // Q
                                           (double)volatility, // standard deviation
                                           (double)dat->UseR,  // R
                                           (double)dat->UseS   // S
                                           );

      callprice = AmericanExchangeOption(
                                           1,
                                           price,      // price
                                           strike,     // strike
                                           dat->UseB,  // B
                                           dat->UseJ,  // J
                                           t,          // time
                                           rate,       // rate
                                           dat->UseP,  // P
                                           dat->UseQ,  // Q
                                           volatility, // standard deviation
                                           dat->UseR,  // R
                                           dat->UseS   // T
                                           );

        break;

    case DISCRETEADJUSTEDBARRIER:

      if(dat->debug)
        logger( (char *)"DiscreteAdjustedBarrier", 4,
                (double)price, (double)strike, (double)volatility, (double)t );

      if(price == strike)
      {
        // force NaN price
        callprice = NAN;
      } else
      {
        callprice = DiscreteAdjustedBarrier(price, strike, volatility, t);
      }

      break;

    case BARRIERBINOMINAL:
      {
        int state;
        
        if ( dat->UsePound == 1 )
        {
          state = SB_CALL_UP_OUT;

        } else if( dat->UsePound == 2 )
        {
          state = SB_CALL_DOWN_OUT;
        } else
        {
          printf("Error unknown state UsePound = %d\n", dat->UsePound);
        }

        int optionType = (int) dat->UseZ;

        if( optionType != 0 && optionType != 1 )
        {
          printf("Error optionType = %d\n", optionType);
        }

        if(dat->debug)
          logger( (char *)"BarrierBinomial", 10,
                                  (double)optionType,         // Z     -> EuropeanOption
                                  (double)state,              // #     -> type
                                  (double)price,
                                  (double)strike,
                                  (double)dat->UseB,          // B     -> H
                                  (double)t,
                                  (double)rate,
                                  (double)dividend,           //
                                  (double)volatility,
                                  (double)dat->steps);        // steps -> n

        callprice = BarrierBinomial(
                                  optionType,         // Z     -> EuropeanOption
                                  state,              // #     -> type
                                  price,
                                  strike,
                                  dat->UseB,          // B     -> H
                                  t,
                                  rate,
                                  dividend,           //
                                  volatility,
                                  dat->steps);        // steps -> n
      }

      break;

    case CONVERTIBLEBOND:

      if(dat->debug)
        logger( (char *)"ConvertibleBond", 12,
                                  (double)dat->UsePound-1,
                                  (double)price,
                                  (double)strike,
                                  (double)t,
                                  (double)t2,
                                  (double)rate,
                                  (double)dat->UseZ,       // Z
                                  (double)dividend,
                                  (double)volatility,
                                  (double)dat->UseB,       // B
                                  (double)dat->UseJ,       // J
                                  (double)dat->steps);

      callprice = ConvertibleBond(
                                  dat->UsePound-1,
                                  price,
                                  strike,
                                  t,
                                  t2,
                                  rate,
                                  dat->UseZ,       // Z
                                  dividend,
                                  volatility,
                                  dat->UseB,       // B
                                  dat->UseJ,       // J
                                  dat->steps);

      break;

    case CRRBINOMINAL:

      if(dat->debug)
        logger( (char *)"CRRBinomial", 9,
                              (double)dat->UsePound-1,
                              (double)1,
                              (double)price,
                              (double)strike,
                              (double)t,
                              (double)rate,
                              (double)dividend,
                              (double)volatility,
                              (double)dat->steps);

      callprice = CRRBinomial(
                              dat->UsePound-1,
                              1,
                              price,
                              strike,
                              t,
                              rate,
                              dividend,
                              volatility,
                              dat->steps);

      break;

/*
    case IMPLIEDTRINOMINALTREE:

      callprice = ImpliedTrinomialTree(
                      const char* ReturnFlag,
                      int STEPn,
                      int STATEi,
                      double S,
                      double X,
                      double T,
                      double r,
                      double b,
                      double v,
                      double Skew,
                      int nSteps)

      callprice = ImpliedTrinomialTree(
                      (const char*)&namelistimpliedtrinominaltree[dat->UsePound-1],
                      dat->UseZ,            // int STEPn,
                      dat->UseB,            // int STATEi,
                      price,
                      strike,
                      t,
                      rate,
                      dividend,
                      volatility,
                      dat->UseJ,           // double Skew,
                      dat->steps);

      break;
*/

    case THREEDIMENSIONALBINOMINAL:

      if(dat->debug)
        logger( (char *)"ThreeDimensionalBinomial", 17,
                (double)dat->UsePound,
                (double)dat->UseZ,
                (double)1,
                (double)price,
                (double)dat->UseB,
                (double)dat->UseR,
                (double)dat->UseS,
                (double)strike,
                (double)dat->UseQ,
                (double)t,
                (double)rate,
                (double)dividend,
                (double)dat->UseP,
                (double)volatility,
                (double)dat->UseJ,
                (double)dat->UseT,
                (double)dat->steps);

      callprice = ThreeDimensionalBinomial(
                                           dat->UsePound,          // #             -> type
                                           dat->UseZ,              // Z             -> EuropeanOption
                                           1,                      // 1 for Call
                                           price,                  // P             -> S1
                                           dat->UseB,              // B             -> S2
                                           dat->UseR,              // R             -> Q1
                                           dat->UseS,              // S             -> Q2
                                           strike,                 // strike
                                           dat->UseQ,              // Q             -> X2
                                           t,                      // t     
                                           rate,                   // rate 
                                           dividend,               // dividend      -> b1
                                           dat->UseP,              // P             -> b2
                                           volatility,             // volatility
                                           dat->UseJ,              // J             -> v2
                                           dat->UseT,              // T             -> rho
                                           dat->steps);            // steps
      break;

    case TRINOMINALTREE:

      if(dat->debug)
        logger( (char *)"TrinomialTree", 9,
                                (double)dat->UsePound-1,
                                (double)1,
                                (double)price,
                                (double)strike,
                                (double)t,
                                (double)rate,
                                (double)dividend,
                                (double)volatility,
                                (double)dat->steps);

      callprice = TrinomialTree(
                                dat->UsePound-1,
                                1,
                                price,
                                strike,
                                t,
                                rate,
                                dividend,
                                volatility,
                                dat->steps);
      break;

    case EUROPEANEXCHANGEOPTION:

      if(dat->debug)
        logger( (char *)"EuropeanExchangeOption", 11,
                                         (double)price,      // price
                                         (double)strike,     // strike
                                         (double)dat->UseB,  // B
                                         (double)dat->UseJ,  // J
                                         (double)t,          // time
                                         (double)rate,       // rate
                                         (double)dat->UseP,  // P
                                         (double)dat->UseQ,  // Q 
                                         (double)dat->UseR,  // R 
                                         (double)dat->UseS,  // S
                                         (double)dat->UseT); // T

      callprice = EuropeanExchangeOption(
                                         price,      // price
                                         strike,     // strike
                                         dat->UseB,  // B
                                         dat->UseJ,  // J
                                         t,          // time
                                         rate,       // rate
                                         dat->UseP,  // P
                                         dat->UseQ,  // Q 
                                         dat->UseR,  // R 
                                         dat->UseS,  // S
                                         dat->UseT); // T

        break;

    case MILTERSENSWARTZ:

      if(dat->debug)
        logger( (char *)"MiltersenSchwartz", 14,
                (double)1,
                (double)dat->UseZ,     // Z 
                (double)price,         // price
                (double)strike,
                (double)t,
                (double)t2,
                (double)volatility,    // volatility
                (double)dat->UseB,     // B
                (double)dat->UseJ,     // J
                (double)dat->UseP,     // P
                (double)dat->UseQ,     // Q
                (double)dat->UseR,     // R
                (double)dat->UseS,     // S
                (double)dat->UseT);    // T 

        callprice = MiltersenSchwartz(
                1,
                dat->UseZ,     // Z 
                price,         // price
                strike,
                t,
                t2,
                volatility,    // volatility
                dat->UseB,     // B
                dat->UseJ,     // J
                dat->UseP,     // P
                dat->UseQ,     // Q
                dat->UseR,     // R
                dat->UseS,     // S
                dat->UseT);    // T 

        break;

    case PARTIALTIMETWOASSETBARRIER:
      {
        if( t2 <= 0.0 )
        {
          callprice = 0;
          break;
        }

        int state;
        if( dat->UsePound == 1 )
        {
          state = SB_CALL_UP_IN;

        } else if ( dat->UsePound == 2 )
        {
          state = SB_CALL_UP_OUT;
        }
        if( dat->UsePound == 3 )
        {
          state = SB_CALL_DOWN_OUT;

        } else if ( dat->UsePound == 4 )
        {
          state = SB_CALL_DOWN_IN;
        }

      if(dat->debug)
        logger( (char *)"PartialTimeTwoAssetBarrier", 13,
                (double)state,
                (double)price,          // price
                (double)dat->UseZ,      // Z
                (double)strike,         // strike
                (double)dat->UseB,      // B
                (double)t,              // t
                (double)t2,             // t2
                (double)rate,           // rate
                (double)dat->dividend,  // J
                (double)dat->UseP,      // P
                (double)dat->UseQ,      // Q
                (double)dat->UseR,      // R
                (double)dat->UseS);     // S

        callprice = PartialTimeTwoAssetBarrier(
                state,
                price,      // price
                dat->UseZ,  // Z
                strike,     // strike
                dat->UseB,  // B
                t,          // t
                t2,         // t2
                rate,       // rate
                dividend,   // J
                dat->UseP,  // P
                dat->UseQ,  // Q
                dat->UseR,  // R
                dat->UseS); // S
      }

      break;

    case TWOASSETBARRIER:
      {
        int state;
        if( dat->UsePound == 1 )
        {
          state = SB_CALL_UP_IN;

        } else if ( dat->UsePound == 2 )
        {
          state = SB_CALL_UP_OUT;
        }
        if( dat->UsePound == 3 )
        {
          state = SB_CALL_DOWN_OUT;

        } else if ( dat->UsePound == 4 )
        {
          state = SB_CALL_DOWN_IN;
        }

        if(dat->debug)
          logger( (char *)"TwoAssetBarrier", 12,
                  (double)state,
                  (double)price,         // standard deviation
                  (double)dat->UseZ,     // S2                        1
                  (double)strike,        // strike
                  (double)dat->UseB,     // H                         2
                  (double)t,             // t1
                  (double)rate,          // rate
                  (double)dat->UseJ,     // dividend
                  (double)dat->UseP,     // b2                        3
                  (double)volatility,    // standard deviation
                  (double)dat->UseQ,     // v2                        4
                  (double)dat->UseR);    // rho                       5

        callprice = TwoAssetBarrier(
                                    state,
                                    price,         // price
                                    dat->UseZ,     // S2                        1
                                    strike,        // strike
                                    dat->UseB,     // H                         2
                                    t,             // t1
                                    rate,          // rate
                                    dat->UseJ,     // dividend
                                    dat->UseP,     // b2                        3
                                    volatility,    // standard deviation
                                    dat->UseQ,     // v2                        4
                                    dat->UseR);    // rho                       5
      }

      break;

    case TWOASSETCASHORNOTHING:

      if(dat->debug)
        logger( (char *)"TwoAssetCashOrNothing", 13,
                                    (double)dat->UsePound,
                                    (double)price,         // price
                                    (double)dat->UseZ,     // S2                        1
                                    (double)strike,        // X1 strike
                                    (double)dat->UseB,     // X2
                                    (double)dat->UseJ,     // K                         2
                                    (double)t,             // t1
                                    (double)rate,          // rate
                                    (double)dat->UseP,     // dividend
                                    (double)dat->UseQ,     // b2                        3
                                    (double)volatility,    // standard deviation
                                    (double)dat->UseR,     // v2                        4
                                    (double)dat->UseS);    // rho                       5

        callprice =  TwoAssetCashOrNothing(
                                    dat->UsePound,
                                    price,         // price
                                    dat->UseZ,     // S2                        1
                                    strike,        // X1 strike
                                    dat->UseB,     // X2
                                    dat->UseJ,     // K                         2
                                    t,             // t1
                                    rate,          // rate
                                    dat->UseP,     // dividend
                                    dat->UseQ,     // b2                        3
                                    volatility,    // standard deviation
                                    dat->UseR,     // v2                        4
                                    dat->UseS);    // rho                       5
        break;

    case TWOASSETCORRELATION:

      if(dat->debug)
        logger( (char *)"TwoAssetCorrelation", 12,
                                    (double)1,
                                    (double)price,         // price
                                    (double)dat->UseZ,     // S2                        1
                                    (double)strike,        // X1 strike
                                    (double)dat->UseB,     // X2
                                    (double)t,             // t1
                                    (double)rate,          // rate
                                    (double)dat->UseJ,     // dividend
                                    (double)dat->UseP,     // b2                        3
                                    (double)volatility,    // standard deviation
                                    (double)dat->UseQ,     // v2                        4
                                    (double)dat->UseR);    // rho                       5

      callprice = TwoAssetCorrelation(
                                    1,
                                    price,         // price
                                    dat->UseZ,     // S2                        1
                                    strike,        // X1 strike
                                    dat->UseB,     // X2
                                    t,             // t1
                                    rate,          // rate
                                    dat->UseJ,     // dividend
                                    dat->UseP,     // b2                        3
                                    volatility,    // standard deviation
                                    dat->UseQ,     // v2                        4
                                    dat->UseR);    // rho                       5
        break;

    case VASICEKBONDPRICE:

      if(dat->debug)
        logger( (char *)"VasicekBondPrice", 6,
                                     (double)t2,
                                     (double)t,
                                     (double)rate,
                                     (double)dat->UseZ,
                                     (double)dat->UseB,
                                     (double)volatility);

        callprice = VasicekBondPrice(
                                     t2,
                                     t,
                                     rate,
                                     dat->UseZ,
                                     dat->UseB,
                                     volatility);

        break;

    case EXCHANGEEXCHANGEOPTION:

      if(dat->debug)
        logger( (char *)"ExchangeExchangeOption", 12,
                                            (double)dat->UsePound,
                                            (double)strike,
                                            (double)dat->UseZ,
                                            (double)dividend,
                                            (double)t2,
                                            (double)t,
                                            (double)rate,
                                            (double)dat->UseB,
                                            (double)dat->UseJ,
                                            (double)dat->UseP,
                                            (double)dat->UseQ,
                                            (double)dat->UseR);

      callprice =  ExchangeExchangeOption(
                                            dat->UsePound,
                                            strike,
                                            dat->UseZ,
                                            dividend,
                                            t2,
                                            t,
                                            rate,
                                            dat->UseB,
                                            dat->UseJ,
                                            dat->UseP,
                                            dat->UseQ,
                                            dat->UseR);

      break;

    case FLOATINGSTRIKELOOKBACK:

      if(dat->debug)
        logger( (char *)"FloatingStrikeLookback", 8,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = FloatingStrikeLookback(1,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case FLOATINGSTRIKELOOKBACK2:

      if(dat->debug)
        logger( (char *)"FloatingStrikeLookback", 8,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);
      
      callprice = FloatingStrikeLookback(1,price,dat->UseZ,strike,t,rate,dividend,volatility);

      break;

    case OPTIONSONTHEMAXMIN:

      if(dat->debug)
        logger( (char *)"OptionsOnTheMaxMin", 11,
                (double)(dat->UsePound-1),(double)price,(double)dat->UseZ,(double)strike,(double)t,(double)rate,(double)dividend,(double)dat->UseB,(double)volatility,(double)dat->UseJ,(double)dat->UseP);

      callprice = OptionsOnTheMaxMin((char *)&namelistoptionsontheminmax2[dat->UsePound-1],price,dat->UseZ,strike,t,rate,dividend,dat->UseB,volatility,dat->UseJ,dat->UseP);

      break;

    case PARTIALFLOATLB:
     {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"PartialFloatLB", 10,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseB);

      callprice = PartialFloatLB(1,price,dat->UseZ,strike,t2,t,rate,dividend,volatility,dat->UseB);

     }

     break;

    case PARTIALFLOATLB2:
     {

      if( t2 <= 0 )
      {
          callprice = 0;
          break;
      }

      if(dat->debug)
        logger( (char *)"PartialFloatLB", 10,
                (double)1,(double)price,(double)strike,(double)dat->UseZ,(double)t2,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseB);

      callprice = PartialFloatLB(1,price,strike,dat->UseZ,t2,t,rate,dividend,volatility,dat->UseB);

     }

     break;

    case FIXEDSTRIKELOOKBACK:

      if(dat->debug)
        logger( (char *)"FixedStrikeLookback", 9,
                (double)1,(double)price,(double)dat->UseZ,(double)dat->UseB,(double)strike,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = FixedStrikeLookback(1,price,dat->UseZ,dat->UseB,strike,t,rate,dividend,volatility);

      break;

    case DOUBLEBARRIER:

      if(dat->debug)
        logger( (char *)"DoubleBarrier", 11,
                (double)(dat->UsePound+2),(double)price,(double)strike,(double)dat->UseZ,(double)dat->UseB,(double)t,(double)rate,(double)dividend,(double)volatility,(double)dat->UseJ,(double)dat->UseP);

      callprice = DoubleBarrier(dat->UsePound+2,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case STANDARDBARRIER:

      if(dat->debug)
        logger( (char *)"StandardBarrier", 9,
                (double)dat->UsePound,(double)price,(double)strike,(double)dat->UseZ,(double)dat->UseB,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = StandardBarrier(dat->UsePound,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility);

      break;

    case SOFTBARRIER:

      if(dat->debug)
        logger( (char *)"SoftBarrier", 9,
                (double)dat->UsePound,(double)price,(double)strike,(double)dat->UseZ,(double)dat->UseB,(double)t,(double)rate,(double)dividend,(double)volatility);

      callprice = SoftBarrier(dat->UsePound,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility);

      break;

    case LEVYASIAN:

      if(dat->debug)
        logger( (char *)"LevyAsian", 9,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(t2>t?(double)0:(double)t2),(double)t,(double)rate,(t2>t?(double)0:(double)dividend),(double)volatility);

      callprice = LevyAsian(1,price,dat->UseZ,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case GEOMETRICAVERAGERATEOPTION:

      if(dat->debug)
        logger( (char *)"GeometricAverageRateOption", 9,
                (double)1,(double)price,(double)dat->UseZ,(double)strike,(double)t,(t2>t?(double)0:(double)t2),(double)rate,(t2>t?(double)0:(double)dividend),(double)volatility);

      callprice = GeometricAverageRateOption(1,price,dat->UseZ,strike,t,(t2 > t ? 0 : t2),rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case FORWARDSTARTOPTION:

      if(dat->debug)
        logger( (char *)"ForwardStartOption", 8,
                (double)1,(double)price,(double)strike,(t2>t?(double)0:(double)t2),(double)t,(double)rate,(t2>t?(double)0:(double)dividend),(double)volatility);

      callprice = ForwardStartOption(1,price,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case PERPETUAL:

      if(dat->debug)
        logger( (char *)"option_price_american_perpetual_call", 5,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility);

       callprice = option_price_american_perpetual_call(price,strike,rate,dividend,volatility);

      break;

    case AMERICANTRINOMIAL:

      if(dat->debug)
        logger( (char *)"option_price_call_american_trinomial", 7,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t,(double)dat->steps); 
       callprice = option_price_call_american_trinomial(price,strike,rate,dividend,volatility,t,dat->steps); 

      break;

    case FUTOPTEURBLACK:

     if(dat->debug)
        logger( (char *)"futures_option_price_call_european_black", 5,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t); 

      callprice  = futures_option_price_call_european_black(price,strike,rate,volatility,t); 

      break;

    case FUTOPTAMBINOMIAL:
      
      if(dat->debug)
        logger( (char *)"futures_option_price_call_american_binomial", 6,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps); 

      callprice = futures_option_price_call_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case EUROSIM:

      if(dat->debug)
        logger( (char *)"option_price_call_european_simulated", 6,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps); 

      callprice = option_price_call_european_simulated(price,strike,rate,volatility,t,dat->steps); 

      break;

     /*
    case AMERBJERKSUNDSTENSLAND:

      //callprice = option_price_american_call_approximated_bjerksund_stensland( const double& S, const double& X, const double& r, const double& q, const double& sigma, const double& time );

      //callprice = option_price_american_call_approximated_bjerksund_stensland(price,strike,rate,dividend,volatility,t); 

      break;
    */

    case AMERBINOMIAL:

      if(dat->debug)
        logger( (char *)"option_price_call_american_binomial", 6,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps); 

      callprice = option_price_call_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case AMERBAW:

      if(dat->debug)
        logger( (char *)"option_price_american_call_approximated_baw", 6,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t); 

      callprice = option_price_american_call_approximated_baw(price,strike,rate,dividend,volatility,t); 

      break;

    case BONDZEROBLACK:

      if(dat->debug)
        logger( (char *)"bond_option_price_call_zero_black_scholes", 5,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t); 

      callprice = bond_option_price_call_zero_black_scholes(price,strike,rate,volatility,t); 

      break;

    case AMERPUTAPPROXJOHNSON:

      callprice = 0;

      break;

#ifdef HAVE_LIBGSL

    case AMERPUTAPPROXGESKEJOHNSON:

      callprice = 0;

      break;

    case HESTON:

      if(dat->debug)
        logger( (char *)"heston_call_option_price", 10,
                (double)price, (double)strike, (double)rate, (double)volatility, (double)t, (double)dat->UseB, (double)dat->UseJ, (double)dat->UseP, (double)dat->UseQ, (double)dat->UseR);
 
      callprice = heston_call_option_price(price, strike, rate, volatility, t, dat->UseB, dat->UseJ, dat->UseP, dat->UseQ, dat->UseR);

      break;

#endif //  HAVE_LIBGSL

    case BONDAMERBINOMIAL:

      if(dat->debug)
        logger( (char *)"bond_option_price_call_american_binomial", 6,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps); 

      callprice = bond_option_price_call_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case BLACKSCHOLES3:

      if(dat->debug)
        logger( (char *)"option_price_call_black_scholes", 5,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t);

      callprice = option_price_call_black_scholes(price,strike,rate,volatility,t);

      break;

    case BSPAYOUT:

      if(dat->debug)
        logger( (char *)"option_price_european_call_payout", 6,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t);

      callprice = option_price_european_call_payout(price,strike,rate,dividend,volatility,t);

      break;

    case AMERBINOMIALDIV:

      if(dat->debug)
        logger( (char *)"option_price_call_american_binomial", 7,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t,(double)dat->steps); 
      callprice = option_price_call_american_binomial(price,strike,rate,dividend,volatility,t,dat->steps); 

      break;

    case EUROBIONMIAL:

      if(dat->debug)
        logger( (char *)"option_price_call_european_binomial", 6,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps); 

      callprice = option_price_call_european_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case ASIANGEOMETRICAVG:

     if(dat->debug)
        logger( (char *)"option_price_asian_geometric_average_price_call", 6,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t);

      callprice = option_price_asian_geometric_average_price_call(price,strike,rate,dividend,volatility,t);

      break;

    case EUROLOOKBACK:

      if(dat->debug)
        logger( (char *)"option_price_european_lookback_call", 6,
                (double)price,(double)dat->UseZ,(double)rate,(double)dividend,(double)volatility,(double)t);

      callprice = option_price_european_lookback_call(price,dat->UseZ,rate,dividend,volatility,t);

      break;

    case EUROLOOKBACK2:

      if(dat->debug)
        logger( (char *)"option_price_european_lookback_call", 6,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t);

      callprice = option_price_european_lookback_call(price,strike,rate,dividend,volatility,t);

      break;

    case MERTONJUMPDIFF:

      if(dat->debug)
        logger( (char *)"option_price_call_merton_jump_diffusion", 8,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UseZ,(double)dat->UseB,(double)dat->UseJ);

      callprice = option_price_call_merton_jump_diffusion(price,strike,rate,volatility,t,dat->UseZ,dat->UseB,dat->UseJ);

      break;

    case CURRAMBINOMIAL:

      if(dat->debug)
        logger( (char *)"currency_option_price_call_american_binomial", 7,
                (double)price,(double)strike,(double)rate,(double)dat->UseZ,(double)volatility,(double)t,(double)dat->steps);

      callprice = currency_option_price_call_american_binomial(price,strike,rate,dat->UseZ,volatility,t,dat->steps);

      break;

    case CURREURO:

      if(dat->debug)
        logger( (char *)"currency_option_price_call_european", 6,
                (double)price,(double)strike,(double)rate,(double)dat->UseZ,(double)volatility,(double)t);

      callprice = currency_option_price_call_european(price,strike,rate,dat->UseZ,volatility,t);

      break;

    case ROLLGESKEWHALEY2:

      if(dat->debug)
        logger( (char *)"option_price_american_call_one_dividend", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(t2 > t ? (double)0: (double)dividend),(t2 > t ? (double)0: (double)t2) );

      callprice = option_price_american_call_one_dividend(price,strike,rate,volatility,t,(t2 > t ? 0: dividend),(t2 > t ? 0: t2));

      break;

    case EUROBINOMIAL1P:

      if(dat->debug)
        logger( (char *)"option_price_call_european_binomial_single_period", 5,
                (double)price,(double)strike,(double)rate,(double)dat->UseZ,(double)dat->UseB);

      // no time, does not support any dividend at all...
      callprice = option_price_call_european_binomial_single_period(price,strike,rate,dat->UseZ,dat->UseB);

      break;

    case EUROBINOMIALMP:

      if(dat->debug)
        logger( (char *)"option_price_call_european_binomial_multi_period_given_ud", 6,
                (double)price,(double)strike,(double)rate,(double)dat->UseZ,(double)dat->UseB,(double)dat->steps);

      // no time, does not support any dividend at all...
      callprice = option_price_call_european_binomial_multi_period_given_ud(price,strike,rate,dat->UseZ,dat->UseB,dat->steps);

      break;

    case SIMEUROGENERIC:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_call;
        else if( dat->UsePound == 2 )
          fun = &payoff_cash_or_nothing_call;
        else if( dat->UsePound == 3 )
          fun = &payoff_asset_or_nothing_call;
        else if( dat->UsePound == 4 )
          fun = &payoff_binary_call;

      if(dat->debug)
        logger( (char *)"derivative_price_simulate_european_option_generic", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UsePound,(double)dat->steps); 

        callprice = derivative_price_simulate_european_option_generic(price,strike,rate,volatility,t,fun,dat->steps); 
      }

      break;

    case SIMEUROGENERICCV:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_call;
        else if( dat->UsePound == 2 )
          fun = &payoff_cash_or_nothing_call;
        else if( dat->UsePound == 3 )
          fun = &payoff_asset_or_nothing_call;
        else if( dat->UsePound == 4 )
          fun = &payoff_binary_call;

        if(dat->debug)
          logger( (char *)"derivative_price_simulate_european_option_generic_with_control_variate", 7,
                  (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UsePound,(double)dat->steps); 

        callprice = derivative_price_simulate_european_option_generic_with_control_variate(price,strike,rate,volatility,t,fun,dat->steps); 
      }

      break;

    case SIMEUROGENERICAV:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_call;
        else if(dat->UsePound == 2 )
          fun = &payoff_cash_or_nothing_call;
        else if(dat->UsePound == 3 )
          fun = &payoff_asset_or_nothing_call;
        else if(dat->UsePound == 4 )
          fun = &payoff_binary_call;

        if(dat->debug)
          logger( (char *)"derivative_price_simulate_european_option_generic_with_antithetic_variate", 7,
                  (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UsePound,(double)dat->steps);

        callprice = derivative_price_simulate_european_option_generic_with_antithetic_variate(price,strike,rate,volatility,t,fun,dat->steps);
      }

      break;

    case SIMPRICEPATH:
      {
        double (*fun2)(const vector<double>&, const double&);

        if( dat->UsePound == 1 )
          fun2 = &payoff_arithmetric_average_call;
        else if( dat->UsePound == 2 )
          fun2 = &payoff_geometric_average_call;
        else if( dat->UsePound == 3 )
          fun2 = &payoff_lookback_call;

        if(dat->debug)
          logger( (char *)"derivative_price_simulate_european_option_generic", 8,
                  (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UsePound,(double)dat->steps,(double)dat->UseZ);

        callprice = derivative_price_simulate_european_option_generic(price,strike,rate,volatility,t,fun2,dat->steps,(int)dat->UseZ);
      }

      break;

    case SIMPRICEPATHCONTROLVARIATE:
      {
        double (*fun2)(const vector<double>&, const double&);

        if( dat->UsePound == 1 )
          fun2 = &payoff_arithmetric_average_call;
        else if( dat->UsePound == 2 )
          fun2 = &payoff_geometric_average_call;
        else if( dat->UsePound == 3 )
          fun2 = &payoff_lookback_call;

        if(dat->debug)
          logger( (char *)"derivative_price_simulate_european_option_generic_with_control_variate", 8,
                  (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UsePound,(double)dat->steps,(double)dat->UseZ);

        callprice = derivative_price_simulate_european_option_generic_with_control_variate(price,strike,rate,volatility,t,fun2,dat->steps,(int)dat->UseZ);
      }

      break;

    case DISTLOGRAND:

      if(dat->debug)
        logger( (char *)"simulate_lognormal_random_variable", 4,
                (double)price,(double)rate,(double)volatility,(double)t);

      callprice = simulate_lognormal_random_variable(price,rate,volatility,t);

      break;

    case IMPLIEDNEWTON:

      if(dat->debug)
        logger( (char *)"option_price_implied_volatility_call_black_scholes_newton", 5,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility);

      callprice = option_price_implied_volatility_call_black_scholes_newton(price,strike,rate,t,volatility);

      break;

    case IMPLIEDBISECTIONS:

      if(dat->debug)
        logger( (char *)"option_price_implied_volatility_call_black_scholes_bisections", 5,
                (double)price,(double)strike,(double)rate,(double)t,(double)volatility);

      callprice = option_price_implied_volatility_call_black_scholes_bisections(price,strike,rate,t,volatility);

      break;

    case BONDZEROVASICEK:

      if(dat->debug)
        logger( (char *)"bond_option_price_call_zero_vasicek", 7,
                                           (double)strike,   // exercise price
                                             (double)rate,   // current interest rate
                                               (double)t2,
                                                (double)t,
                                        (double)dat->UseZ,   // a
                                        (double)dat->UseB,   // b, 
                                        (double)dat->UseJ);  // sigma

      callprice = bond_option_price_call_zero_vasicek(
                                           strike,   // exercise price
                                             rate,   // current interest rate
                                               t2,
                                                t,
                                        dat->UseZ,   // a
                                        dat->UseB,   // b, 
                                        dat->UseJ);  // sigma

      break;

    case EURODIVIDENDS:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      if(dat->debug)
      {
        //g_print("dividends = ");

        for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\ntimes = ");

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\n");
      }

      if(dat->debug)
        logger( (char *)"option_price_european_call_dividends", 5,
                                            (double)price,               
                                            (double)strike,
                                            (double)rate,
                                            (double)volatility,           
                                            (double)t);

      callprice = option_price_european_call_dividends( price,               
                                            strike,
                                            rate,
                                            volatility,           
                                            t,
                                            dat->times,
                                            dat->amounts);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case AMDISDIVSBINOMIAL:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      if(dat->debug)
      {
        //g_print("dividends = ");

        for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\ntimes = ");

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\n");
      }

      if(dat->debug)
        logger( (char *)"option_price_call_american_discrete_dividends_binomial", 6,
                                                                          (double)price,
                                                                          (double)strike,
                                                                          (double)rate,
                                                                          (double)volatility,
                                                                          (double)t,
                                                                          (double)dat->steps);

      // t should be > than last dividend...sanity.cpp forces this.
      callprice = option_price_call_american_discrete_dividends_binomial( price,
                                                                          strike,
                                                                          rate,
                                                                          volatility,
                                                                          t,
                                                                          dat->steps,
                                                                          dat->times, 
                                                                          dat->amounts);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case AMPROPORTDIVSBINOMIAL:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      if(dat->debug)
      {
        //g_print("dividends = ");

        for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\ntimes = ");

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          //g_print("%lf ", *it);
        }
        //g_print("\n");

      }

      if(dat->debug)
        logger( (char *)"option_price_call_american_proportional_dividends_binomial", 6,
                                                                             (double)price,
                                                                             (double)strike,
                                                                             (double)rate,
                                                                             (double)volatility,
                                                                             (double)t,
                                                                             (double)dat->steps);

      callprice = option_price_call_american_proportional_dividends_binomial( price,
                                                                              strike,
                                                                              rate,
                                                                              volatility,
                                                                              t,
                                                                              dat->steps, 
                                                                              dat->times, 
                                                                              //dat->dividend_yields);
                                                                              dat->amounts);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case BERMUDANBINOMIAL:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      if(dat->debug)
      {
        //g_print("times = ");

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\n");
      }

      if(dat->debug)
        logger( (char *)"option_price_call_bermudan_binomial", 6,
                                                      (double)price,
                                                      (double)strike,
                                                      (double)rate,
                                                      //dividend,
                                                      (double)dat->UseZ,
                                                      (double)volatility,
                                                      (double)t );

      callprice = option_price_call_bermudan_binomial( price,
                                                      strike,
                                                      rate,
                                                      //dividend,
                                                      dat->UseZ,
                                                      volatility,
                                                      t,
                                                      //potential_exercise_times,
                                                      dat->times,
                                                      dat->steps);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case BSCOUPONBOND:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      if(dat->debug)
      {
        //g_print("dividends = ");

        for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\ntimes = ");

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          //g_print("%lf ", *it);
        }

        //g_print("\n");
      }

      if(dat->debug)
        logger( (char *)"bond_option_price_call_coupon_bond_black_scholes", 5,
                                                                (double)price,
                                                                (double)strike,
                                                                (double)rate,
                                                                (double)volatility,
                                                                (double)t );

      callprice = bond_option_price_call_coupon_bond_black_scholes( price,
                                                                   strike,
                                                                     rate,
                                                               volatility,
                                                                        t,
                                                           //coupon_times,
                                                                //coupons);
                                                      dat->times, 
                                                     dat->amounts);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case AMFINITEDIFFEXP:

      if(dat->debug)
        logger( (char *)"option_price_call_american_finite_diff_explicit", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps,(double)dat->UseZ);

      callprice = option_price_call_american_finite_diff_explicit(price,strike,rate,volatility,t,dat->steps,dat->UseZ);

      break;
 
    case EUROFINITEDIFFEXP:

      if(dat->debug)
        logger( (char *)"option_price_call_european_finite_diff_explicit", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps,(double)dat->UseZ);

      callprice = option_price_call_european_finite_diff_explicit(price,strike,rate,volatility,t,dat->steps,dat->UseZ);

      break;

#ifdef HAVE_NEWMAT_NEWMAT_H

    case AMFINDIFFIMP:

      if(dat->debug)
        logger( (char *)"option_price_call_american_finite_diff_implicit", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps,(double)dat->UseZ);

      callprice = option_price_call_american_finite_diff_implicit(price,
                                                                 strike,
                                                                   rate, 
                                                             volatility,
                                                                      t, 
                                                             dat->steps,
                                                              dat->UseZ);

      break;

    case EURFINDDIFFIMP:

      if(dat->debug)
        logger( (char *)"option_price_call_european_finite_diff_implicit", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps,(double)dat->UseZ);

      callprice = option_price_call_european_finite_diff_implicit(price,
                                                                 strike,
                                                                   rate, 
                                                             volatility,
                                                                      t, 
                                                             dat->steps,
                                                              dat->UseZ);

      break;

#endif // HAVE_NEWMAT_NEWMAT_H

#ifdef HAVE_ITPP_ITBASE_H

    case AMFINDIFFIMPPUT:

      callprice = 0;

      break;

#endif //  HAVE_ITPP_ITBASE_H

    case WARRANT_NO_DIV:

      if(dat->debug)
        logger( (char *)"warrant_price_adjusted_black_scholes", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->UseZ,(double)dat->UseB);

      callprice = warrant_price_adjusted_black_scholes(price,strike,rate,volatility,t,dat->UseZ,dat->UseB);

      break;

    case WARRANT_DIV:

      if(dat->debug)
        logger( (char *)"warrant_price_adjusted_black_scholes", 8,
                (double)price,(double)strike,(double)rate,(double)dividend,(double)volatility,(double)t,(double)dat->UseZ,(double)dat->UseB);

      callprice = warrant_price_adjusted_black_scholes(price,strike,rate,dividend,volatility,t,dat->UseZ,dat->UseB);

      break;

    case AMBINOMIAL:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_call;
        else if( dat->UsePound == 2 )
          fun = &payoff_cash_or_nothing_call;
        else if( dat->UsePound == 3 )
          fun = &payoff_asset_or_nothing_call;
        else if( dat->UsePound == 4 )
          fun = &payoff_binary_call;

      if(dat->debug)
        logger( (char *)"option_price_generic_binomial", 7,
                (double)price,(double)strike,(double)dat->UsePound,(double)rate,(double)volatility,(double)t,(double)dat->steps);

        callprice = option_price_generic_binomial(price,strike,fun,rate,volatility,t,dat->steps);
      }

      break;

    case BOND_ZERO_AM_RENDLEMAN_BARTTER:

      if(dat->debug)
        logger( (char *)"bond_option_price_call_zero_american_rendleman_bartter", 8,
                      (double)strike,
                      (double)(t2 > t ? 0 : t2),
                      (double)dat->UseB,
                      (double)dat->UseZ,
                      (double)rate,
                      (double)t,
                      (double)price,
                      (double)dat->steps);


      callprice = bond_option_price_call_zero_american_rendleman_bartter(
                      strike,
                      (t2 > t ? 0 : t2),
                      dat->UseB,
                      dat->UseZ,
                      rate,
                      t,
                      price,
                      dat->steps);

      break;

#endif // FINRECIPES

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)

    case QUANTLIB_BLACKSCHOLES_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BLACKSCHOLES_EUROPEAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);
        
        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
                                         new QuantLib::EuropeanExercise(maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

        // Black-Scholes for European
        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(new QuantLib::AnalyticEuropeanEngine(bsmProcess)));
        
        callprice = europeanOption.NPV();

        try {
          dat->calldelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = europeanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = europeanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

   case QUANTLIB_HESTON_SEMI_ANALYTIC_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_HESTON_SEMI_ANALYTIC_EUR call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
                                         new QuantLib::EuropeanExercise(maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

        // semi-analytic Heston for European
        boost::shared_ptr<QuantLib::HestonProcess> hestonProcess(
            new QuantLib::HestonProcess(flatTermStructure, flatDividendTS,
                              underlyingH, volatility_*volatility_,
                              1.0, volatility_*volatility_, 0.001, 0.0));
        boost::shared_ptr<QuantLib::HestonModel> hestonModel(
                                              new QuantLib::HestonModel(hestonProcess));
        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
                                     new QuantLib::AnalyticHestonEngine(hestonModel)));

        callprice = europeanOption.NPV();

        try {
          dat->calldelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = europeanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = europeanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BARONE_ADESI_WHALEY_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BARONE_ADESI_WHALEY_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> americanExercise(
                                         new QuantLib::AmericanExercise(settlementDate,
                                         maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption americanOption(payoff, americanExercise);
        
        // Barone-Adesi and Whaley approximation for American
        americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
                  new QuantLib::BaroneAdesiWhaleyApproximationEngine(bsmProcess)));
        
        callprice = americanOption.NPV();

        try {
          dat->calldelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = americanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = americanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = americanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }
      
      break;

    case QUANTLIB_BJERKSUND_STENSLAND_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BJERKSUND_STENSLAND_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();
        boost::shared_ptr<QuantLib::Exercise> americanExercise(
                                         new QuantLib::AmericanExercise(settlementDate,
                                         maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption americanOption(payoff, americanExercise);

        americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
                      new QuantLib::BjerksundStenslandApproximationEngine(bsmProcess)));

        callprice = americanOption.NPV();

        try {
          dat->calldelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = americanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = americanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = americanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_EUROPEAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
                                         new QuantLib::EuropeanExercise(maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
               boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
                boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
                boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                        flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

        // Finite differences
        QuantLib::Size timeSteps = dat->steps;

        //europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
        //new QuantLib::FDEuropeanEngine<QuantLib::CrankNicolson>(bsmProcess,
        //timeSteps,timeSteps-1)));

        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::FdBlackScholesVanillaEngine(bsmProcess,dat->steps,dat->steps-1)));

        callprice = europeanOption.NPV();

        try {
          dat->calldelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = europeanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = europeanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }
        
      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_AMERICAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_AMERICAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> americanExercise(
                                         new QuantLib::AmericanExercise(settlementDate,
                                         maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
               boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                        flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption americanOption(payoff, americanExercise);
        
        // Finite differences
        QuantLib::Size timeSteps = dat->steps;
        
        //americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
        //       new QuantLib::FDAmericanEngine<QuantLib::CrankNicolson>(bsmProcess,
        
        americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::FdBlackScholesVanillaEngine(bsmProcess,dat->steps,dat->steps-1)));
        
        callprice = americanOption.NPV();

        try {
          dat->calldelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = americanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = americanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = americanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_MC_CRUDE_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_MC_CRUDE_EUR call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // options
       QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

       boost::shared_ptr<QuantLib::PricingEngine> mcengine1;
       mcengine1 = QuantLib::MakeMCEuropeanEngine<QuantLib::PseudoRandom>(bsmProcess)
            .withSteps(dat->steps)
            .withAbsoluteTolerance(dat->UseB)
            .withSeed(dat->UseZ);
       europeanOption.setPricingEngine(mcengine1);
       
       callprice =  europeanOption.NPV();
       
       try {
         dat->calldelta = europeanOption.delta();
       }
       catch (exception& e)
       {
         dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->callElasticity = europeanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->gamma = europeanOption.gamma();
       }
       catch (exception& e)
       {
         dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->vega = europeanOption.vega();
       }
       catch (exception& e)
       {
         dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->calltheta = europeanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->callrho = europeanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }
 
      }

      break;

    case QUANTLIB_QMC_SOBOL_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_QMC_SOBOL_EUR call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // options
       QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

       boost::shared_ptr<QuantLib::PricingEngine> mcengine2;
       mcengine2 = QuantLib::MakeMCEuropeanEngine<QuantLib::LowDiscrepancy>(bsmProcess)
            .withSteps(dat->steps)
            .withSamples(dat->UseZ);
       europeanOption.setPricingEngine(mcengine2);

       callprice =  europeanOption.NPV();

       try {
         dat->calldelta = europeanOption.delta();
       }
       catch (exception& e)
       {
         dat->calldelta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->callElasticity = europeanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->callElasticity = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->gamma = europeanOption.gamma();
       }
       catch (exception& e)
       {
         dat->gamma = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->vega = europeanOption.vega();
       }
       catch (exception& e)
       {
         dat->vega = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->calltheta = europeanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->calltheta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->callrho = europeanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->callrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }
       
      }

      break;

   case QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

        boost::shared_ptr<QuantLib::Exercise> americanExercise(
                                         new QuantLib::AmericanExercise(settlementDate,
                                         maturity));
       // options
       QuantLib::VanillaOption americanOption(payoff, americanExercise);

       // Monte Carlo Method: MC (Longstaff Schwartz)
       boost::shared_ptr<QuantLib::PricingEngine> mcengine3;
       mcengine3 = QuantLib::MakeMCAmericanEngine<QuantLib::PseudoRandom>(bsmProcess)
           .withSteps(dat->steps)
           .withAntitheticVariate()
           .withCalibrationSamples(dat->UseJ)
           .withAbsoluteTolerance(dat->UseB)
           .withSeed(dat->UseZ);
       americanOption.setPricingEngine(mcengine3);

       callprice = americanOption.NPV();

       try {
         dat->calldelta = americanOption.delta();
       }
       catch (exception& e)
       {
         dat->calldelta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->callElasticity = americanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->callElasticity = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->gamma = americanOption.gamma();
       }
       catch (exception& e)
       {
         dat->gamma = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->vega = americanOption.vega();
       }
       catch (exception& e)
       {
         dat->vega = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->calltheta = americanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->calltheta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->callrho = americanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->callrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

      }

      break;

   case QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Jarrow-Rudd
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
             new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);
         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
             new QuantLib::BinomialVanillaEngine<QuantLib::JarrowRudd>(bsmProcess,dat->steps)));

         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);
         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
             new QuantLib::BinomialVanillaEngine<QuantLib::JarrowRudd>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

    case QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Cox-Ross-Rubinstein
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
             new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);
         
         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::CoxRossRubinstein>(bsmProcess,dat->steps)));

         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);
         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::CoxRossRubinstein>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

   case QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Additive EQP
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
             new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);

         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::AdditiveEQPBinomialTree>(bsmProcess,dat->steps)));

         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::AdditiveEQPBinomialTree>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Cox-Ross-Rubinstein
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
            new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);

         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Trigeorgis>(bsmProcess,dat->steps)));

         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Trigeorgis>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_TIAN_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TIAN_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Tian
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
            new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);

         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Tian>(bsmProcess,dat->steps)));
 
         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Tian>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: LeisenReimer
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
             new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);

         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::LeisenReimer>(bsmProcess,dat->steps)));
 
         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::LeisenReimer>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_JOSHI_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JOSHI_EUR_AM call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(%f, %d, %d, %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::Handle<QuantLib::Quote> underlyingH(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
            new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
            new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                flatTermStructure, flatVolTS));

       // Binomial method: Joshi
       if( dat->UsePound == 1 )
       {
         //g_print("American\n");
         boost::shared_ptr<QuantLib::Exercise> americanExercise(
            new QuantLib::AmericanExercise(settlementDate,maturity));
         QuantLib::VanillaOption americanOption(payoff, americanExercise);

         americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Joshi4>(bsmProcess,dat->steps)));
 
         callprice = americanOption.NPV();

         try {
           dat->calldelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = americanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = americanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Joshi4>(bsmProcess,dat->steps)));

         callprice = europeanOption.NPV();

         try {
           dat->calldelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->calldelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->callElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->gamma = europeanOption.gamma();
         }
         catch (exception& e)
         {
           dat->gamma = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->vega = europeanOption.vega();
         }
         catch (exception& e)
         {
           dat->vega = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->calltheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->calltheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->callrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->callrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         callprice = 0;
       }

      }

      break;

     case QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
                                         new QuantLib::EuropeanExercise(maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));

        boost::shared_ptr<QuantLib::BatesProcess> batesProcess(
                new QuantLib::BatesProcess(flatTermStructure, flatDividendTS,
                             underlyingH, volatility*volatility,
                             1.0, volatility*volatility, 0.001, 0.0,
                             1e-14, 1e-14, 1e-14));

        // options
        QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

        boost::shared_ptr<QuantLib::BatesModel> batesModel(new QuantLib::BatesModel(batesProcess));
        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
              new QuantLib::BatesEngine(batesModel)));

        callprice = europeanOption.NPV();

        try {
          dat->calldelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = europeanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = europeanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_INTEGRAL_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_INTEGRAL_EUROPEAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
                                         new QuantLib::EuropeanExercise(maturity));
        
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        // options
        QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::IntegralEngine(bsmProcess)));

        callprice = europeanOption.NPV();

        try {
          dat->calldelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = europeanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = europeanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          
          if(dat->debug)
            logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_BERMUDAN call exercises", 3,
                    (double) day, (double) month, (double) year);

          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        //bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
        //   new QuantLib::FDBermudanEngine<QuantLib::CrankNicolson>(bsmProcess,dat->steps,dat->steps-1)));

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::FdBlackScholesVanillaEngine(bsmProcess,dat->steps,dat->steps-1)));
        
        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::JarrowRudd>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::CoxRossRubinstein>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::BinomialVanillaEngine<QuantLib::AdditiveEQPBinomialTree>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::BinomialVanillaEngine<QuantLib::Trigeorgis>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_TIAN_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TIAN_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::BinomialVanillaEngine<QuantLib::Tian>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::BinomialVanillaEngine<QuantLib::LeisenReimer>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_JOSHI_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JOSHI_BERMUDAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Call);
        QuantLib::Real underlying = price;
        QuantLib::Real strike_ = strike;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
                new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
            boost::shared_ptr<QuantLib::BlackVolTermStructure>(
                new QuantLib::BlackConstantVol(settlementDate, calendar, volatility_, dayCounter)));
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
                                        new QuantLib::PlainVanillaPayoff(type, strike_));
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
                 new QuantLib::BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                               flatTermStructure, flatVolTS));

        pthread_mutex_lock(&dat->mutexCashflow);

        std::vector<QuantLib::Date> exerciseDates;
        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          exerciseDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        boost::shared_ptr<QuantLib::Exercise> bermudanExercise(
            new QuantLib::BermudanExercise(exerciseDates));

        // options
        QuantLib::VanillaOption bermudanOption(payoff, bermudanExercise);

        bermudanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
           new QuantLib::BinomialVanillaEngine<QuantLib::Joshi4>(bsmProcess,dat->steps)));

        callprice = bermudanOption.NPV();

        try {
          dat->calldelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = bermudanOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = bermudanOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }
      }

      break;

    case QUANTLIB_DISCRETE_AVERAGE_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_DISCRETE_AVERAGE_ASIAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        try {

        // Calendar set up
        QuantLib::Calendar calendar = QuantLib::TARGET();

        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date todaysDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
 
        // Option parameters
        QuantLib::Option::Type optionType(QuantLib::Option::Call);
        QuantLib::Average::Type averageType = QuantLib::Average::Geometric;
        QuantLib::Real strike_ = strike;
        QuantLib::Real underlying = price;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Spread dividendYield = dat->UseJ;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();
        QuantLib::Real runningSum = dat->UseZ;
        QuantLib::Size pastFixings = dat->UseB;
        std::vector<QuantLib::Date> fixingDates;

        pthread_mutex_lock(&dat->mutexCashflow);

        static int oneTime_QUANTLIB_DISCRETE_AVERAGE_ASIAN = 0;

        if( oneTime_QUANTLIB_DISCRETE_AVERAGE_ASIAN++ == 0 )
        {
          dat->times.erase( dat->times.begin(), dat->times.end() );
          dat->amounts.erase( dat->amounts.begin(), dat->amounts.end() );
          //dat->times_adjusted.erase( dat->times_adjusted.begin(), dat->times_adjusted.end() );

          for( QuantLib::Date incrementedDate = todaysDate+7; incrementedDate <= maturity; incrementedDate += 7 )
          {
            //std::cout << "incrementedDate = " << incrementedDate << std::endl;

            g_print("%d %d %d\n", incrementedDate.dayOfMonth(),incrementedDate.month(),incrementedDate.year() );
            int daysaway = date_to_days_away( incrementedDate.dayOfMonth(),incrementedDate.month(),incrementedDate.year() - 2000 );
            //std::cout << "daysaway = " << daysaway << std::endl;
            //std::cout << "dat->generic_times->push_back( " << adjust_to_current_time_and_expr(&daysaway,0,0) << " )" << std::endl;
            dat->times.push_back( adjust_to_current_time_and_expr(&daysaway,0,0) );
            dat->amounts.push_back( 1 );
            //dat->times_adjusted.push_back( adjust_to_current_time_and_expr(&daysaway,0,0) );

          } // for( QuantLib::Date incrementedDate = todaysDate+7; incrementedDate <= maturity; incrementedDate += 7 )

          //std::cout << "dat->times.size() = " << dat->times.size() << std::endl;
          dat->generic_times_adjusted = &dat->times;
          dat->generic_amounts = &dat->amounts;
 
        } // if( oneTime_QUANTLIB_DISCRETE_AVERAGE_ASIAN++ == 0 )

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          //std::cout << "ExDate( " << day << " " << month << " " << year << ")" << std::endl;
          //std::cout << "options_calls():fixingDates.push_back( " << ExDate << " )" << std::endl;
          fixingDates.push_back(ExDate);
        }

        //std::cout << "options_calls:fixingDates.size() = " << fixingDates.size() << std::endl;
        pthread_mutex_unlock(&dat->mutexCashflow);
     
        //std::cout << "maturity = " << maturity << std::endl;
        //std::cout << "todaysDate = " << todaysDate << std::endl;
        //std::cout << "runningSum = " << runningSum << std::endl;
        //std::cout << "pastFixings = " << pastFixings << std::endl;      

        // Option exercise type
        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
               new QuantLib::EuropeanExercise(maturity));
 
        // Quote handling
        QuantLib::Handle<QuantLib::Quote> underlyingH(
               boost::shared_ptr<QuantLib::Quote>(
               new QuantLib::SimpleQuote(underlying)));
 
        // Yield term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
               boost::shared_ptr<QuantLib::YieldTermStructure>(
               new QuantLib::FlatForward(todaysDate,riskFreeRate,dayCounter)));
 
        // Dividend term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTermStructure(
               boost::shared_ptr<QuantLib::YieldTermStructure>(
               new QuantLib::FlatForward(todaysDate,dividendYield,dayCounter)));
 
        // Volatility structure handling
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTermStructure(
               boost::shared_ptr<QuantLib::BlackVolTermStructure>(
               new QuantLib::BlackConstantVol(todaysDate,calendar,volatility_,dayCounter)));
 
        // the BS equation behind
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
               new QuantLib::BlackScholesMertonProcess(underlyingH,flatDividendTermStructure,flatTermStructure,flatVolTermStructure));
 
        // Payoff
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoffAsianOption (
               new QuantLib::PlainVanillaPayoff(QuantLib::Option::Type(optionType),strike_));

        /*
        unsigned int ii;
        for(ii=0; ii < fixingDates.size(); ii++)
        {
          std::cout << ii << ' ' << fixingDates[ii] << ' ';
        }
        std::cout << std::endl;
        */

        // Discretely-averaged Asian option
        QuantLib::DiscreteAveragingAsianOption discreteAsianAverageOption(
                  averageType,
                  runningSum,
                  pastFixings,
                  fixingDates,
                  payoffAsianOption,
                  europeanExercise);
 
        // Pricing engine
        discreteAsianAverageOption.setPricingEngine(
               boost::shared_ptr<QuantLib::PricingEngine>(
               new QuantLib::AnalyticDiscreteGeometricAveragePriceAsianEngine(bsmProcess)));

        callprice = discreteAsianAverageOption.NPV();

        try {
          dat->calldelta = discreteAsianAverageOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = discreteAsianAverageOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = discreteAsianAverageOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = discreteAsianAverageOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = discreteAsianAverageOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = discreteAsianAverageOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      } catch(exception& e)
      {
          if(dat->debug)
            logger(e.what(), 0);
      }
        
      }

      break;

    case QUANTLIB_CONTINUOUS_AVERAGING_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_CONTINUOUS_AVERAGING_ASIAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // Calendar set up
        QuantLib::Calendar calendar = QuantLib::TARGET();

        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date todaysDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
 
        // Option parameters
        QuantLib::Option::Type optionType(QuantLib::Option::Call);
        QuantLib::Average::Type averageType = QuantLib::Average::Geometric;
        QuantLib::Real strike_ = strike;
        QuantLib::Real underlying = price;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        // Option exercise type
        boost::shared_ptr<QuantLib::Exercise> europeanExercise(
             new QuantLib::EuropeanExercise(maturity));
 
        // Quote handling
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(
            new QuantLib::SimpleQuote(underlying)));
 
        // Yield term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(todaysDate,riskFreeRate,dayCounter)));
 
        // Dividend term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTermStructure(
             boost::shared_ptr<QuantLib::YieldTermStructure>(
             new QuantLib::FlatForward(todaysDate,dividendYield,dayCounter)));
 
        // Volatility structure handling
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTermStructure(
             boost::shared_ptr<QuantLib::BlackVolTermStructure>(
             new QuantLib::BlackConstantVol(todaysDate,calendar,volatility,dayCounter)));
 
        // the BS equation behind
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
             new QuantLib::BlackScholesMertonProcess(underlyingH,flatDividendTermStructure,flatTermStructure,flatVolTermStructure));
 
        // Payoff
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoffAsianOption (
             new QuantLib::PlainVanillaPayoff(QuantLib::Option::Type(optionType),strike_));
 
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
             new QuantLib::PlainVanillaPayoff(optionType, strike_));

        boost::shared_ptr<QuantLib::Exercise> exercise(new QuantLib::EuropeanExercise(maturity));

        QuantLib::ContinuousAveragingAsianOption continuousAveragingAsianOption(averageType, payoff, exercise);

        // Pricing engine
        continuousAveragingAsianOption.setPricingEngine(
        boost::shared_ptr<QuantLib::PricingEngine>(
                new QuantLib::AnalyticContinuousGeometricAveragePriceAsianEngine(bsmProcess)));

        callprice = continuousAveragingAsianOption.NPV();

        try {
          dat->calldelta = continuousAveragingAsianOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = continuousAveragingAsianOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = continuousAveragingAsianOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = continuousAveragingAsianOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = continuousAveragingAsianOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = continuousAveragingAsianOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_CONTINUOUS_LEVY_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_CONTINUOUS_LEVY_ASIAN call", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // Calendar set up
        QuantLib::Calendar calendar = QuantLib::TARGET();

        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date todaysDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
 
        // Option parameters
        QuantLib::Option::Type optionType(QuantLib::Option::Call);
        QuantLib::Average::Type averageType = QuantLib::Average::Arithmetic;
        QuantLib::Real strike_ = strike;
        QuantLib::Real underlying = price;
        QuantLib::Real underlying_average = dat->UseZ;
        QuantLib::Rate riskFreeRate = rate;
        QuantLib::Volatility volatility_ = volatility;
        QuantLib::Spread dividendYield = dividend;
        QuantLib::Date maturity(day, QuantLibMonths[month], year);
        QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();

        boost::shared_ptr<QuantLib::Quote> average(
              new QuantLib::SimpleQuote(underlying_average));
  
        // Quote handling
        QuantLib::Handle<QuantLib::Quote> underlyingH(
            boost::shared_ptr<QuantLib::Quote>(
            new QuantLib::SimpleQuote(underlying)));
 
        // Yield term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(todaysDate,riskFreeRate,dayCounter)));
 
        // Dividend term structure handling
        QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTermStructure(
            boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(todaysDate,dividendYield,dayCounter)));
 
        // Volatility structure handling
        QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTermStructure(
           boost::shared_ptr<QuantLib::BlackVolTermStructure>(
           new QuantLib::BlackConstantVol(todaysDate,calendar,volatility,dayCounter)));
 
        // the BS equation behind
        boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
           new QuantLib::BlackScholesMertonProcess(underlyingH,flatDividendTermStructure,flatTermStructure,flatVolTermStructure));
 
        // Payoff
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
           new QuantLib::PlainVanillaPayoff(QuantLib::Option::Type(optionType),strike_));

        boost::shared_ptr<QuantLib::Exercise> exercise(new QuantLib::EuropeanExercise(maturity));

        boost::shared_ptr<QuantLib::PricingEngine> engine(
           new QuantLib::ContinuousArithmeticAsianLevyEngine(
           bsmProcess, QuantLib::Handle<QuantLib::Quote>(average), todaysDate));

        QuantLib::ContinuousAveragingAsianOption levyAsianOption(averageType,payoff, exercise);

        levyAsianOption.setPricingEngine(engine);

        callprice = levyAsianOption.NPV();

        try {
          dat->calldelta = levyAsianOption.delta();
        }
        catch (exception& e)
        {
          dat->calldelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callElasticity = levyAsianOption.elasticity();
        }
        catch (exception& e)
        {
          dat->callElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->gamma = levyAsianOption.gamma();
        }
        catch (exception& e)
        {
          dat->gamma = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->vega = levyAsianOption.vega();
        }
        catch (exception& e)
        {
          dat->vega = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->calltheta = levyAsianOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->calltheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->callrho = levyAsianOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->callrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

#endif // #if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)      

#ifdef DUMMYTESTMODELS

    case TESTOPTION1:
    case TESTOPTION2:
    case TESTOPTION3:
    case TESTOPTION4:
    case TESTOPTION5:
    case TESTOPTIONONEDIVIDEND1:
    case TESTOPTIONONEDIVIDEND2:

      callprice = 0;
      dat->callElasticity = 0;

      break;
      
#endif // DUMMYTESTMODELS
   
    default:

      fprintf(stderr,"option_call(): No implementation for case %d\n", dat->modeltype);

      break;

    }

  dat->call = callprice;

  if(isnan(dat->call))
  {
    dat->isnan = 1;
  }

  if(dat->filterNegativePrices == true && dat->call < 0.0 &&
     properties.distribution_type==NORMAL_DISTRIBUTION)
  {
    dat->call = 0.0;
  }

  }

  catch (exception& e)
  {
    fprintf(stderr,"option_call(): Exception caught: %s\n", e.what() );
    fprintf(stderr,"Model = %d, P = %f, X = %f, R = %f, V = %f, t = %f, Div = %f\n", dat->modeltype, price,strike,rate,volatility,t,dividend);

  } catch (...)
  {
    fprintf(stderr,"option_call(): unknown error\n");
    fprintf(stderr,"Model = %d, P = %f, X = %f, R = %f, V = %f, t = %f, Div = %f\n", dat->modeltype, price,strike,rate,volatility,t,dividend);
  }

  return *dat;
}
