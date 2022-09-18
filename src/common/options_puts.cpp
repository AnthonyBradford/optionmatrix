/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: options_puts.cpp of optionmatrix                                   */
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

//using namespace QuantLib;

struct _data option_put(struct _data *dat)
{
  double putprice;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t  = dat->t[0] - dat->te;
  const double t2 = dat->t[1] - dat->te2;
  // no model using t3 for puts yet...
  //const double t3 = dat->t[2] - dat->te3;
  const double volatility = dat->volatility;
  const double dividend = dat->dividend;

  double putdelta; /* this is a dummy variable */
  putdelta = 0;

  if(t <= 0.0)
  {
    dat->put = 0.0;

    return *dat;
  }

  try {

  switch(dat->modeltype)
  {

#ifdef ABRADFORD

    case BLACKSCHOLES:

      putprice = black_scholes_put(price,strike,rate,t,volatility,&putdelta);

      break;

    case MERTON73:

      putprice = merton73_put(price,strike,rate,t,volatility,dividend,&putdelta);

      break;

    case BLACK76:
      
      putprice = black76put(price,strike,rate,t,volatility,&putdelta);

      break;

  case BACHELIER:

      putprice = bachelier_put(price, strike, t, volatility);

      break;

  case BACHELIERMODIFIED:

      putprice = bachelier_modified_put(price, strike, rate, t, volatility);

      break;

  case SPRENKLE:

      putprice = 0;

      break;

  case BONESS:

      putprice = 0;

      break;

  case SAMUELSON:

      putprice = 0;

      break;

#endif // ABRADFORD

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

        putprice = (double) option_price(data,dat->steps,AMERPUT,CRR);
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

        putprice = (double) option_price(data,dat->steps,AMERPUT,EQUIPROB);
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

        putprice = (double) option_price(data,dat->steps,EUROPUT,CRR);
      }

      break;

    case EURO_EQUIPROB :
      {
        Ivar data;
        data.S = data.X = data.T = data.sigma = data.mu = 0;
      
        data.S = price;
        data.X = strike;
        data.T = t;
        data.sigma = volatility;
        data.mu = rate;

        putprice = (double) option_price(data,dat->steps,EUROPUT,EQUIPROB);
      }

      break;

#endif // SPINSKY

#ifdef METAOPTIONS

    case BLACKSCHOLES2:

      putprice = blackscholes(0,price,strike,t,rate,volatility);

      break;

    case GBS:

      putprice = gbs(0,price,strike,t,rate,dividend,volatility);

      break;

    case MERTON73B:

      putprice = merton73(0,price,strike,t,rate,dividend,volatility);

      break;

    case GFRENCH:

      putprice = french(0,price,strike,t2,t,rate,dividend,volatility);

      break;

    case GCARRY:

      // carry puts have negative prices with this model.
      // Un-check Prefs -> Settings [ ] Filter negative prices to see
      // the negative prices...

      putprice = carry(0,price,strike,t,rate,dividend,volatility);

      break;

    case BAWAMERICAN:

      putprice = BAWAmericanApprox(0,price,strike,t,rate,dividend,volatility);

      break;

    case BSAMERICAN:

      putprice = BSAmericanApprox(0,price,strike,t,rate,dividend,volatility);

      break;

    case BLACK76B:

      putprice = black76(0,price,strike,t,rate,volatility);

      break;

    case ASSETORNOTHING:

      putprice = AssetOrNothing(0,price,strike,t,rate,dividend,volatility);

      break;

    case CASHORNOTHING:

      putprice = CashOrNothing(0,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case EXTENDIBLEWRITER:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = ExtendibleWriter(0,price,strike,dat->UseZ,t2,t,rate,dividend,volatility);
      
      }

      break;

    case CALLSONOPTIONS:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = OptionsOnOptions(OOO_CALL_ON_PUT,price,strike,dat->UseZ,t2,t,rate,0,volatility);

      }

      break;

    case PUTSONOPTIONS:

      putprice = OptionsOnOptions(OOO_PUT_ON_PUT,price,strike,dat->UseZ,t2,t,rate,dividend,volatility);

      break;

    case ROLLGESKEWHALEY:

      putprice = 0;

      break;

    case EXTREMESPREADOPTION:

      putprice =  ExtremeSpreadOption(transextremeoptionput[dat->UsePound-1],price,strike,dat->UseB,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case EXTREMESPREADOPTION2:

      putprice =  ExtremeSpreadOption(transextremeoptionput[dat->UsePound-1],price,dat->UseZ,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case SIMPLECHOOSER:

      putprice = 0;

      break;

    case PARTIALFIXEDLB:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = PartialFixedLB(0,price,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

      }

    case PARTIALTIMEBARRIER:

        //putprice = PartialTimeBarrier("pdoA",price,strike,dat->UseZ,t2,t,rate,dividend,volatility);

      break;

    case EXECUTIVE:

      putprice = Executive(0,price,strike,t,rate,dividend,volatility,dat->UseZ);

      break;

    case GARMANKOHLHAGEN:

      putprice = GarmanKohlhagen(0,price,strike,t,rate,dat->UseZ,volatility);

      break;

    case LOOKBARRIER:
     {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = LookBarrier(dat->UsePound+4,price,strike,dat->UseZ,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

     }

     break;

    case GAPOPTION:

      putprice = GapOption(0,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case JUMPDIFFUSION:

      putprice = JumpDiffusion(0,price,strike,t,rate,volatility,dat->UseZ,dat->UseB);

      break;

    case BISECTION:
      {

      double pprice;

      if( bisection(0,price,strike,t,rate,dividend,volatility,&pprice) == 1 )
        putprice = pprice;
      else
        putprice = 0;

      }

      break;

    case NEWTONRAPHSON:
      {

      double pprice;

      if( NewtonRaphson(0,price,strike,t,rate,volatility,&pprice) == 1 )
        putprice = pprice;
      else
        putprice = 0;
      }

      break;

    case BAWBISECTION:

      putprice = BAWbisection(0,price,strike,t,rate,dividend,volatility);

      break;

    case BSBISECTION:

      putprice = BSbisection(0,price,strike,t,rate,dividend,volatility);

      break;

    case SWAPOPTION:

      putprice = Swapoption(0,t,dat->UseZ,price,strike,t2,rate,volatility);

      break;

    case TURNBULLWAKEMANASIAN:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = TurnbullWakemanAsian(0,price,dat->UseZ,strike,t,t2,dat->UseB,rate,dividend,volatility);

      break;

      }

    case COMPLEXCHOOSER:

      putprice = 0;

      break;

    case SUPERSHARE:

      putprice = 0;

      break;

    case SUPERSHARE2:

      putprice = 0;

      break;

    case VASICEKBONDOPTION:

      putprice = VasicekBondOption(0,dat->UseB,strike,dat->UseZ,t,rate,dat->UseB,dat->UseJ,volatility);

      break;

    case TIMESWITCHOPTION:

      putprice = TimeSwitchOption(0,price,strike,dat->UseZ,t,(int)dat->UseB,t2,rate,dividend,volatility);

      break;

    case FOREQUOPTINDOMCUR:

      putprice = ForEquOptInDomCur(0,dat->UseZ,price,strike,t,rate,dividend,volatility,dat->UseB,dat->UseJ);

      break;

    case QUANTO:

      putprice = Quanto(0,dat->UseZ,price,strike,t,rate,dat->UseB,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case EQUITYLINKEDFXO:

      putprice = EquityLinkedFXO(0,dat->UseZ,price,strike,t,rate,dat->UseB,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case SPREADAPPROXIMATION:

      putprice = SpreadApproximation(0,price,dat->UseZ,strike,t,rate,volatility,dat->UseB,dat->UseJ);

      break;

    case BINARYBARRIER:

      putprice = 0;

      break;

    case TAKEOVERFXOPTION:

      putprice = 0;

      break;

    case AMERICANEXCHANGEOPTION:

        putprice = AmericanExchangeOption(
                                           0,
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
                                           dat->UseS   // S
                                           );
    
      break;

    case DISCRETEADJUSTEDBARRIER:

      putprice = 0;

      break;

    case BARRIERBINOMINAL:
      {
        int state;
        
        if ( dat->UsePound == 1 )
        {
          state = SB_PUT_UP_OUT;

        } else if( dat->UsePound == 2 )
        {
          state = SB_PUT_DOWN_OUT;
        } else
        {
          printf("Error unknown state UsePound = %d\n", dat->UsePound);
        }

        int optionType = (int) dat->UseZ;

        if( optionType != 0 && optionType != 1 )
        {
          printf("Error optionType = %d\n", optionType);
        }

        putprice = BarrierBinomial(
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

    case CONVERTIBLEBOND:            // ConvertibleBond.c

      putprice = 0;

      break;

    case CRRBINOMINAL:

      putprice = CRRBinomial(
                              dat->UsePound-1,
                              0,
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

      putprice = 0;

      break;
*/

    case THREEDIMENSIONALBINOMINAL:

      putprice = ThreeDimensionalBinomial(
                                          dat->UsePound,          // #             -> type
                                          dat->UseZ,              // Z             -> EuropeanOption
                                          0,                      // 0 for Put
                                          price,                  // P             -> S1
                                          dat->UseB,              // B             -> S2
                                          dat->UseQ,              // Q             -> X2
                                          dat->UseS,              // S             -> Q2
                                          strike,                 // strike
                                          dat->UseQ,              // R             -> X2
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

      putprice = TrinomialTree(
                                dat->UsePound-1,
                                0,
                                price,
                                strike,
                                t,
                                rate,
                                dividend,
                                volatility,
                                dat->steps);


      break;

    case EUROPEANEXCHANGEOPTION:

      putprice = 0;

      break;

    case MILTERSENSWARTZ:

      putprice = MiltersenSchwartz(
                0,
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
          putprice = 0;
          break;
       }

      int state;
      if( dat->UsePound == 1 )
      {
        state = SB_PUT_UP_IN;

      } else if ( dat->UsePound == 2 )
      {
        state = SB_PUT_UP_OUT;
      }
      if( dat->UsePound == 3 )
      {
        state = SB_PUT_DOWN_OUT;

      } else if ( dat->UsePound == 4 )
      {
        state = SB_PUT_DOWN_IN;
      }

      putprice = PartialTimeTwoAssetBarrier(
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
          state = SB_PUT_UP_IN;

        } else if ( dat->UsePound == 2 )
        {
          state = SB_PUT_UP_OUT;
        }
        if( dat->UsePound == 3 )
        {
          state = SB_PUT_DOWN_OUT;

        } else if ( dat->UsePound == 4 )
        {
          state = SB_PUT_DOWN_IN;
        }

        putprice = TwoAssetBarrier(
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

      putprice = 0;

      break;

    case TWOASSETCORRELATION:

      putprice = TwoAssetCorrelation(
                                    0,
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

      putprice = 0;

      break;

    case EXCHANGEEXCHANGEOPTION:

      putprice = 0;

      break;

    case FLOATINGSTRIKELOOKBACK:

      putprice = FloatingStrikeLookback(0,price,strike,dat->UseZ,t,rate,dividend,volatility);

      break;

    case FLOATINGSTRIKELOOKBACK2:

      putprice = FloatingStrikeLookback(0,price,dat->UseZ,strike,t,rate,dividend,volatility);

      break;

    case OPTIONSONTHEMAXMIN:

      putprice = OptionsOnTheMaxMin((char *)&namelistoptionsontheminmax2[dat->UsePound+1],price,dat->UseZ,strike,t,rate,dividend,dat->UseB,volatility,dat->UseJ,dat->UseP);

     break;

    case PARTIALFLOATLB:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = PartialFloatLB(0,price,dat->UseZ,strike,t2,t,rate,dividend,volatility,dat->UseB);

      }

      break;

    case PARTIALFLOATLB2:
      {

      if( t2 <= 0 )
      {
          putprice = 0;
          break;
      }

      putprice = PartialFloatLB(0,price,strike,dat->UseZ,t2,t,rate,dividend,volatility,dat->UseB);

      }

      break;

    case FIXEDSTRIKELOOKBACK:

      putprice = FixedStrikeLookback(0,price,dat->UseZ,dat->UseB,strike,t,rate,dividend,volatility);

      break;

    case DOUBLEBARRIER:

      putprice = DoubleBarrier(dat->UsePound,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility,dat->UseJ,dat->UseP);

      break;

    case STANDARDBARRIER:

      putprice = StandardBarrier(dat->UsePound+4,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility);

      break;

    case SOFTBARRIER:

      putprice = SoftBarrier(dat->UsePound+6,price,strike,dat->UseZ,dat->UseB,t,rate,dividend,volatility);

      break;

    case LEVYASIAN:

      putprice = LevyAsian(0,price,dat->UseZ,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case GEOMETRICAVERAGERATEOPTION:

      putprice = GeometricAverageRateOption(0,price,strike,strike,t,(t2 > t ? 0 : t2),rate,(t2 > t ? 0 : dividend),volatility);

      break;

    case FORWARDSTARTOPTION:

      putprice = ForwardStartOption(0,price,strike,(t2 > t ? 0 : t2),t,rate,(t2 > t ? 0 : dividend),volatility);

      break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case PERPETUAL:

      putprice = option_price_american_perpetual_put(price,strike,rate,dividend,volatility);

      break;

    case AMERICANTRINOMIAL:

       putprice = option_price_put_american_trinomial(price,strike,rate,dividend,volatility,t,dat->steps); 

      break;

    case FUTOPTEURBLACK:

      putprice  = futures_option_price_put_european_black(price,strike,rate,volatility,t); 

      break;

    case FUTOPTAMBINOMIAL:

      putprice = futures_option_price_put_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case EUROSIM:

      putprice = option_price_put_european_simulated(price,strike,rate,volatility,t,dat->steps); 

      break;

      /*
    case AMERBJERKSUNDSTENSLAND:

      putprice = 0;

      break;
      */

    case AMERBINOMIAL:

      putprice = option_price_put_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case AMERBAW:

      putprice =  option_price_american_put_approximated_baw(price,strike,rate,dividend,volatility,t); 

      break;

    case BONDZEROBLACK:

      putprice = bond_option_price_put_zero_black_scholes(price,strike,rate,volatility,t); 

      break;

    case AMERPUTAPPROXJOHNSON:

      if(dat->debug)
        logger( (char *)"option_price_american_put_approximated_johnson", 5,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t); 

      putprice = option_price_american_put_approximated_johnson(price,strike,rate,volatility,t); 

      break;

#ifdef HAVE_LIBGSL

    case AMERPUTAPPROXGESKEJOHNSON:

      if(dat->debug)
        logger( (char *)"option_price_american_put_approximated_geske_johnson", 5,
                (double)price,(double)strike,(double)(rate > 0 ? rate : 0 ) ,(double)volatility,(double)t); 

      // freezes on rate < 0...
      putprice = option_price_american_put_approximated_geske_johnson(price,strike,(rate > 0 ? rate : 0 ),volatility,t); 

      break;

    case HESTON:

      putprice = 0;

      break;

#endif // HAVE_LIBGSL

    case BONDAMERBINOMIAL:

      putprice = bond_option_price_put_american_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case BLACKSCHOLES3:

      putprice = option_price_put_black_scholes(price,strike,rate,volatility,t);

      break;

    case BSPAYOUT:

      putprice = option_price_european_put_payout(price,strike,rate,dividend,volatility,t);

      break;

    case AMERBINOMIALDIV:

      putprice = option_price_put_american_binomial(price,strike,rate,dividend,volatility,t,dat->steps); 

      break;

    case EUROBIONMIAL:

      putprice = option_price_put_european_binomial(price,strike,rate,volatility,t,dat->steps); 

      break;

    case ASIANGEOMETRICAVG:

      putprice = 0;

      break;

    case EUROLOOKBACK:

      putprice = option_price_european_lookback_put(price,strike,rate,dividend,volatility,t);

      break;

    case EUROLOOKBACK2:

      putprice = option_price_european_lookback_put(price,dat->UseZ,rate,dividend,volatility,t);

      break;

    case MERTONJUMPDIFF:

      putprice = 0;

      break;

    case CURRAMBINOMIAL:

      putprice = currency_option_price_put_american_binomial(price,strike,rate,dat->UseZ,volatility,t,dat->steps);

      break;

    case CURREURO:

      putprice = currency_option_price_put_european(price,strike,rate,dat->UseZ,volatility,t);

      break;

    case ROLLGESKEWHALEY2:

      putprice = 0;

      break;

    case EUROBINOMIAL1P:

      putprice = 0;

      break;

    case EUROBINOMIALMP:

      putprice = 0;

      break;

    case SIMEUROGENERIC:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1)
        {
          fun = &payoff_put;

        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 4 )
        {
          fun = &payoff_binary_put;
        }

        putprice = derivative_price_simulate_european_option_generic(price,strike,rate,volatility,t,fun,dat->steps); 
      }

      break;

    case SIMEUROGENERICCV:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
        {
          fun = &payoff_put;
          
        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 4 )
        {
          fun = &payoff_binary_put;
        }

        putprice = derivative_price_simulate_european_option_generic_with_control_variate(price,strike,rate,volatility,t,fun,dat->steps); 
      }

      break;

    case SIMEUROGENERICAV:
      {
        double (*fun)(const double&,const double&);
      
        if( dat->UsePound == 1 )
        {
          fun = &payoff_put;

        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 4 )
        {
          fun = &payoff_binary_put;
        }

        putprice = derivative_price_simulate_european_option_generic_with_antithetic_variate(price,strike,rate,volatility,t,fun,dat->steps); 
      }

      break;

    case SIMPRICEPATH:
      {
        double (*fun2)(const vector<double>&, const double&);

        if( dat->UsePound == 1 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          fun2 = &payoff_lookback_put;
        }

        putprice = derivative_price_simulate_european_option_generic(price,strike,rate,volatility,t,fun2,dat->steps,(int)dat->UseZ);
      }

      break;

    case SIMPRICEPATHCONTROLVARIATE:
      {
        double (*fun2)(const vector<double>&, const double&);

        if( dat->UsePound == 1 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          fun2 = &payoff_lookback_put;
        }

        putprice = derivative_price_simulate_european_option_generic_with_control_variate(price,strike,rate,volatility,t,fun2,dat->steps,(int)dat->UseZ);
      }

      break;

    case DISTLOGRAND:
      
      putprice = 0;

      break;

    case IMPLIEDNEWTON:

      // option_price_implied_volatility_put_black_scholes_newton() doesn't seem to
      // resolve in the library? but its prototyped in fin_recipes.h????
      // nm librecipes.a | fgrep newton 
      // yields no reference to puts

      //putprice = option_price_implied_volatility_put_black_scholes_newton(price,strike,rate,t,volatility);

      putprice = 0;

      break;

    case IMPLIEDBISECTIONS:

      // option_price_implied_volatility_put_black_scholes_bisections() doesn't seem to
      // resolve in the library? but its prototyped in fin_recipes.h????
      // nm librecipes.a | fgrep bisections
      // yields no reference to puts

      //putprice  = option_price_implied_volatility_put_black_scholes_bisections(price,strike,rate,t,volatility);

      putprice = 0;

      break;

    case BONDZEROVASICEK:

      putprice = bond_option_price_put_zero_vasicek(strike,  // exercise price
                                           rate, // current interest rate
                                           t2,
                                           t,
                                           dat->UseZ,  // a
                                           dat->UseB,  // b, 
                                           dat->UseJ); // sigma
 
      break;

    case EURODIVIDENDS:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      putprice = option_price_european_put_dividends( price,               
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

      putprice = option_price_put_american_discrete_dividends_binomial( price,
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

      putprice = option_price_put_american_proportional_dividends_binomial( price,
                                                                              strike,
                                                                              rate,
                                                                              volatility,
                                                                              t,
                                                                              dat->steps, 
                                                                              dat->times, 
                                                                              //dividend_yields);
                                                                              dat->amounts);

      pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case BERMUDANBINOMIAL:
      {

      pthread_mutex_lock(&dat->mutexCashflow);

      putprice = option_price_put_bermudan_binomial( price,
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

      putprice = bond_option_price_put_coupon_bond_black_scholes( price,
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

      putprice = option_price_put_american_finite_diff_explicit(price,strike,rate,volatility,t,dat->steps,dat->UseZ);

      break;

    case EUROFINITEDIFFEXP:

      putprice = option_price_put_european_finite_diff_explicit(price,strike,rate,volatility,t,dat->steps,dat->UseZ);

      break;

#ifdef HAVE_NEWMAT_NEWMAT_H

    case AMFINDIFFIMP:

      putprice = option_price_put_american_finite_diff_implicit(price,
                                                               strike,
                                                                 rate, 
                                                           volatility,
                                                                    t, 
                                                           dat->steps,
                                                            dat->UseZ);

      break;

    case EURFINDDIFFIMP:

      putprice = option_price_put_european_finite_diff_implicit(price,
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

      if(dat->debug)
        logger( (char *)"option_price_put_american_finite_diff_implicit_itpp", 7,
                (double)price,(double)strike,(double)rate,(double)volatility,(double)t,(double)dat->steps,(double)dat->UseZ);

      putprice = option_price_put_american_finite_diff_implicit_itpp(price,
                                                                    strike,
                                                                      rate, 
                                                                volatility,
                                                                         t, 
                                                                dat->steps,
                                                                 dat->UseZ);

      break;

#endif // HAVE_ITPP_ITBASE_H

    case WARRANT_NO_DIV:

      putprice = 0;

      break;

    case WARRANT_DIV:

      putprice = 0;

      break;

    case AMBINOMIAL:
      {
        double (*fun)(const double&,const double&);
        if( dat->UsePound == 1 )
        {
          fun = &payoff_put;

        } else if( dat->UsePound == 2 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 3 )
        {
          putprice = 0;
          break;

        } else if( dat->UsePound == 4 )
        {
          fun = &payoff_binary_put;
        }
      
        putprice = option_price_generic_binomial(price,strike,fun,rate,volatility,t,dat->steps);
      }

      break;

    case BOND_ZERO_AM_RENDLEMAN_BARTTER:

      putprice = 0;

      break;

#endif // FINRECIPES

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)      

    case QUANTLIB_BLACKSCHOLES_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BLACKSCHOLES_EUROPEAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        //decimal_date_to_real_dates( (double) 1 / (double) 365, &year, &month, &day, &hour, &min, &second);
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        decimal_date_to_real_dates(t, &year, &month, &day, &hour, &min, &second);
        //g_print("2 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

       putprice = europeanOption.NPV();

       try {
         dat->putdelta = europeanOption.delta();
       }
       catch (exception& e)
       {
         dat->putdelta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->putElasticity = europeanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->putElasticity = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->puttheta = europeanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->puttheta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->putrho = europeanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->putrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

      }

      break;

    case QUANTLIB_HESTON_SEMI_ANALYTIC_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_HESTON_SEMI_ANALYTIC_EUR put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = europeanOption.NPV();

        try {
          dat->putdelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }
       
        try {
          dat->putElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BARONE_ADESI_WHALEY_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BARONE_ADESI_WHALEY_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
        
        putprice = americanOption.NPV();

        try {
          dat->putdelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = americanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }
      
      break;

   case QUANTLIB_BJERKSUND_STENSLAND_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BJERKSUND_STENSLAND_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = americanOption.NPV();

        try {
          dat->putdelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = americanOption.thetaPerDay();
        } 
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_EUROPEAN put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
        QuantLib::Size timeSteps = 801;

        //europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
        //         new QuantLib::FDEuropeanEngine<QuantLib::CrankNicolson>(bsmProcess,
        //                                            timeSteps,timeSteps-1)));

        europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::FdBlackScholesVanillaEngine(bsmProcess,dat->steps,dat->steps-1)));    

        putprice = europeanOption.NPV();

        try {
          dat->putdelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_AMERICAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_AMERICAN put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
        //         new QuantLib::FDAmericanEngine<QuantLib::CrankNicolson>(bsmProcess,
        //                                             timeSteps,timeSteps-1)));

        americanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::FdBlackScholesVanillaEngine(bsmProcess,dat->steps,dat->steps-1)));    

        putprice = americanOption.NPV();

        try {
          dat->putdelta = americanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = americanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = americanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = americanOption.rho() / 100;
        }
        catch (exception& e)
        {
         dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

      }
      
      break;

    case QUANTLIB_MC_CRUDE_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_MC_CRUDE_EUR put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
       
       putprice =  europeanOption.NPV();

       try {
         dat->putdelta = europeanOption.delta();
       }
       catch (exception& e)
       {
         dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->putElasticity = europeanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->putElasticity = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->puttheta = europeanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->puttheta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->putrho = europeanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->putrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }
       
      }

      break;

    case QUANTLIB_QMC_SOBOL_EUR:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_QMC_SOBOL_EUR put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

       putprice =  europeanOption.NPV();

       try {
         dat->putdelta = europeanOption.delta();
       }
       catch (exception& e)
       {
         dat->putdelta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->putElasticity = europeanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->puttheta = europeanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
       }

       try {
         dat->putrho = europeanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->putrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }
       
      }

      break;

   case QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

       putprice = americanOption.NPV();

       try {
         dat->putdelta = americanOption.delta();
       }
       catch (exception& e)
       {
         dat->putdelta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }
       
       try {
         dat->putElasticity = americanOption.elasticity();
       }
       catch (exception& e)
       {
         dat->putElasticity = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->puttheta = americanOption.thetaPerDay();
       }
       catch (exception& e)
       {
         dat->puttheta = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }

       try {
         dat->putrho = americanOption.rho() / 100;
       }
       catch (exception& e)
       {
         dat->putrho = NAN;

         if(dat->debug)
           logger(e.what(), 0);
       }
       
      }

      break;

   case QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);
         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
             new QuantLib::BinomialVanillaEngine<QuantLib::JarrowRudd>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
            dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);
         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::CoxRossRubinstein>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
            new QuantLib::BinomialVanillaEngine<QuantLib::AdditiveEQPBinomialTree>(bsmProcess,dat->steps)));
                                                                                    
         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
            dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::AdditiveEQPBinomialTree>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
                                                                                    
         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Trigeorgis>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_TIAN_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TIAN_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
            new QuantLib::BinomialVanillaEngine<QuantLib::Tian>(bsmProcess,dat->steps)));
 
         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Tian>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
            new QuantLib::BinomialVanillaEngine<QuantLib::LeisenReimer>(bsmProcess,dat->steps)));
 
         putprice = americanOption.NPV();

         try {
           dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::LeisenReimer>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

   case QUANTLIB_BINOMIAL_JOSHI_EUR_AM:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JOSHI_EUR_AM put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
            new QuantLib::BinomialVanillaEngine<QuantLib::Joshi4>(bsmProcess,dat->steps)));
 
         putprice = americanOption.NPV();

         try {
            dat->putdelta = americanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = americanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = americanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putrho = americanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

       } else if( dat->UsePound == 2 )
       {
         //g_print("European\n");
         QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

         europeanOption.setPricingEngine(boost::shared_ptr<QuantLib::PricingEngine>(
            new QuantLib::BinomialVanillaEngine<QuantLib::Joshi4>(bsmProcess,dat->steps)));

         putprice = europeanOption.NPV();

         try {
           dat->putdelta = europeanOption.delta();
         }
         catch (exception& e)
         {
           dat->putdelta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->putElasticity = europeanOption.elasticity();
         }
         catch (exception& e)
         {
           dat->putElasticity = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }

         try {
           dat->puttheta = europeanOption.thetaPerDay();
         }
         catch (exception& e)
         {
           dat->puttheta = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
 
         try {
           dat->putrho = europeanOption.rho() / 100;
         }
         catch (exception& e)
         {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);
         }
         
       } else
       {
         fprintf(stderr,"Error: Invalid state for UsePound = %d\n", dat->UsePound);
         putprice = 0;
       }

      }

      break;

     case QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = europeanOption.NPV();

        try {
          dat->putdelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }
  
        try {
          dat->puttheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }
      }

      break;

    case QUANTLIB_INTEGRAL_EUROPEAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_INTEGRAL_EUROPEAN put", 6,
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
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = europeanOption.NPV();
 
        try {
          dat->putdelta = europeanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = europeanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = europeanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = europeanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_FINITE_DIFFERENCES_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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
            logger( (char *) "QUANTLIB_FINITE_DIFFERENCES_BERMUDAN put exercises", 3,
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);
        
        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_TIAN_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_TIAN_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);
        
        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);
        
        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_BINOMIAL_JOSHI_BERMUDAN:
      // Based on QuantLib-1.6.2/Examples/EquityOption.cpp
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_BINOMIAL_JOSHI_BERMUDAN put", 6,
                  (double) price, (double) strike, (double) dividend, (double) rate, (double) volatility, (double) t);

        // set up dates
        QuantLib::Calendar calendar = QuantLib::TARGET();
        int year; int month; int day; int hour; int min; int second;
        decimal_date_to_real_dates( 0, &year, &month, &day, &hour, &min, &second);
        //g_print("1 decimal_date_to_real_dates(t = %f, year = %d, month = %d, day = %d, hour, min, second)\n", t, year, month, day);
        QuantLib::Date settlementDate(day, QuantLibMonths[month], year);

        // our options
        QuantLib::Option::Type type(QuantLib::Option::Put);
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

        putprice = bermudanOption.NPV();

        try {
          dat->putdelta = bermudanOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = bermudanOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->puttheta = bermudanOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = bermudanOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_DISCRETE_AVERAGE_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_DISCRETE_AVERAGE_ASIAN put", 6,
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
        QuantLib::Option::Type optionType(QuantLib::Option::Put);
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

        for( std::vector<double>::iterator it = dat->times.begin(); it != dat->times.end(); ++it)
        {
          decimal_date_to_real_dates( *it, &year, &month, &day, &hour, &min, &second);
          //g_print("decimal_date_to_real_dates(it = %lf, year = %d, month = %d, day = %d, hour, min, second)\n", *it, year, month, day);
          QuantLib::Date ExDate(day, QuantLibMonths[month], year);
          fixingDates.push_back(ExDate);
        }

        pthread_mutex_unlock(&dat->mutexCashflow);

        //std::cout << "options_puts:fixingDates.size() = " << fixingDates.size() << std::endl;
        //std::cout << "maturity = " << maturity << std::endl;
        //std::cout << "todaysDate = " << todaysDate << std::endl;      

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

        putprice = discreteAsianAverageOption.NPV();

        try {
          dat->putdelta = discreteAsianAverageOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);  
        }

        try {
          dat->putElasticity = discreteAsianAverageOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

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
          dat->puttheta = discreteAsianAverageOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);  
        }

        try {
          dat->putrho = discreteAsianAverageOption.rho() / 100;
        }
        catch (exception& e)
        {
           dat->putrho = NAN;

           if(dat->debug)
             logger(e.what(), 0);  
        }
        
      }

      break;

    case QUANTLIB_CONTINUOUS_AVERAGING_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_CONTINUOUS_AVERAGING_ASIAN put", 6,
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
        QuantLib::Option::Type optionType(QuantLib::Option::Put);
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

        putprice = continuousAveragingAsianOption.NPV();

        try {
          dat->putdelta = continuousAveragingAsianOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = continuousAveragingAsianOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

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
          dat->puttheta = continuousAveragingAsianOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = continuousAveragingAsianOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

      }

      break;

    case QUANTLIB_CONTINUOUS_LEVY_ASIAN:
      {
        if(dat->debug)
          logger( (char *) "QUANTLIB_CONTINUOUS_LEVY_ASIAN put", 6,
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
        QuantLib::Option::Type optionType(QuantLib::Option::Put);
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

        putprice = levyAsianOption.NPV();

        try {
          dat->putdelta = levyAsianOption.delta();
        }
        catch (exception& e)
        {
          dat->putdelta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putElasticity = levyAsianOption.elasticity();
        }
        catch (exception& e)
        {
          dat->putElasticity = NAN;

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
          dat->puttheta = levyAsianOption.thetaPerDay();
        }
        catch (exception& e)
        {
          dat->puttheta = NAN;

          if(dat->debug)
            logger(e.what(), 0);
        }

        try {
          dat->putrho = levyAsianOption.rho() / 100;
        }
        catch (exception& e)
        {
          dat->putrho = NAN;

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

      putprice = 0;
      dat->putElasticity = 0;

      break;

#endif // DUMMYTESTMODELS

    default:

      fprintf(stderr,"option_put(): No implementation for case %d\n", dat->modeltype);

      break;

  }

  dat->put = putprice;

  if(isnan(dat->put))
  {
    dat->isnan = 1;
  }

  if(dat->filterNegativePrices == true && dat->put < 0.0 &&
     properties.distribution_type==NORMAL_DISTRIBUTION)
  {
    dat->put = 0.0;
  }

  }

  catch (exception& e)
  {
    fprintf(stderr,"option_put(): Exception caught: %s\n", e.what() );
    fprintf(stderr,"Model = %d, P = %f, X = %f, R = %f, V = %f, t = %f, Div = %f\n", dat->modeltype, price,strike,rate,volatility,t,dividend);

  } catch (...)
  {
    fprintf(stderr,"option_put(): unknown error\n");
    fprintf(stderr,"Model = %d, P = %f, X = %f, R = %f, V = %f, t = %f, Div = %f\n", dat->modeltype, price,strike,rate,volatility,t,dividend);
  }

  return *dat;
}
