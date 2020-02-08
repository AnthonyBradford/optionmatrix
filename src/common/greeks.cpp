/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: greeks.cpp of optionmatrix                                         */
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

struct _data option_call_delta(struct _data *dat)
{
  double calldelta;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  const double dividend = dat->dividend;

  switch(dat->modeltype)
  {

#ifdef ABRADFORD

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       calldelta = call_delta(price,strike,rate,t,volatility,dividend);

       break;

#endif // ABRADFORD

#if defined(ABRADFORD) && defined(METAOPTIONS)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       calldelta = call_delta(price,strike,rate,t,volatility,dividend);

       break;

#endif // #if defined(ABRADFORD) && defined(METAOPTIONS)

#ifdef METAOPTIONS

    case GBS:
    case GFRENCH:
    case GCARRY:

      calldelta = delta(1,price,strike,t,rate,dividend,volatility);

      break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

      calldelta = option_price_delta_call_black_scholes(price,strike,rate,volatility,t);

      break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

      calldelta = option_price_delta_american_call_binomial(price,strike,rate,volatility,t,dat->steps);

      break;

    case EUROSIM:

      calldelta  = option_price_delta_call_european_simulated(price,strike,rate,volatility,t,dat->steps);

      break;

    case AMBINOMIAL:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_call;
        else if( dat->UsePound == 2 )
          fun = &payoff_cash_or_nothing_call;
        else if(dat->UsePound == 3)
          fun = &payoff_asset_or_nothing_call;
        else if( dat->UsePound == 4 )
          fun = &payoff_binary_call;

        calldelta =  option_price_delta_generic_binomial(price,strike,fun,rate,volatility,t,dat->steps);

      }

      break;

#endif // FINRECIPES

  default:

    calldelta = NAN;

    break;

  } // switch(dat->modeltype)

  dat->calldelta = calldelta;

  return *dat;

} // struct _data option_call_delta(struct _data *dat)

struct _data option_put_delta(struct _data *dat)
{
  double putdelta;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  const double dividend = dat->dividend;

  switch(dat->modeltype)
  {

#ifdef ABRADFORD

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       putdelta = put_delta(price,strike,rate,t,volatility,dividend);

       break;

#endif // ABRADFORD

#if defined(ABRADFORD) && defined(METAOPTIONS)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       putdelta = put_delta(price,strike,rate,t,volatility,dividend);

       break;

#endif // #if defined(ABRADFORD) && defined(METAOPTIONS)

#ifdef METAOPTIONS

    case GBS:
    case GFRENCH:
    case GCARRY:

       putdelta = delta(0,price,strike,t,rate,dividend,volatility);

       break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       putdelta = option_price_delta_put_black_scholes(price,strike,rate,volatility,t);

       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       putdelta = option_price_delta_american_put_binomial(price,strike,rate,volatility,t,dat->steps);

       break;

    case EUROSIM:

       putdelta  = option_price_delta_put_european_simulated(price,strike,rate,volatility,t,dat->steps);

       break;

    case AMBINOMIAL:
      {
        double (*fun)(const double&,const double&);

        if( dat->UsePound == 1 )
          fun = &payoff_put;
        else if( dat->UsePound == 2 )
        {
          putdelta =  0;
          break;
        }
        else if( dat->UsePound == 3 )
        {
          putdelta =  0;
          break;
        }
        else if( dat->UsePound == 4 )
          fun = &payoff_binary_put;

        putdelta =  option_price_delta_generic_binomial(price,strike,fun,rate,volatility,t,dat->steps);

      }

      break;

#endif // FINRECIPES

    default:

      putdelta = NAN;

      break;

  } // switch(dat->modeltype)

  dat->putdelta = putdelta;

  return *dat;

} // struct _data option_put_delta(struct _data *dat)

struct _data option_gamma(struct _data *dat)
{
  double gamma_;

  double price = dat->price;
  double strike = dat->strike;
  double rate = dat->rate;
  double t = dat->t[0]-dat->te;
  double volatility = dat->volatility;
  double dividend = dat->dividend;
  double dummydelta,dummytheta,dummyvega,dummyrho;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,gamma_,dummytheta,dummyvega,dummyrho);
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

       gamma_ = Gamma(price,strike,t,rate,dividend,volatility);
      
       break;

#endif // METAOPTIONS

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,gamma_,dummytheta,dummyvega,dummyrho);
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,gamma_,dummytheta,dummyvega,dummyrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_call_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,gamma_,dummytheta,dummyvega,dummyrho);

       break;

#endif // FINRECIPES
       
    default:

      gamma_ = NAN;

      break;

  } // switch(dat->modeltype)

  dat->gamma = gamma_;

  return *dat;

} // struct _data option_gamma(struct _data *dat)

struct _data option_vega(struct _data *dat)
{
  double vega_;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  const double dividend = dat->dividend;
  double dummydelta,dummygamma,dummytheta,dummyrho;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,vega_,dummyrho);
       
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,vega_,dummyrho);
       
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

      vega_ = vega(price,strike,t,rate,dividend,volatility);

      break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,vega_,dummyrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_call_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,dummygamma,dummytheta,vega_,dummyrho);

      break;

#endif // FINRECIPES

    default:

      vega_ = NAN;

      break;

  } // switch(dat->modeltype)

  dat->vega = vega_;

  return *dat;

} // struct _data option_vega(struct _data *dat)

struct _data option_call_theta(struct _data *dat)
{
  double calltheta;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  double dividend = dat->dividend;
  double dummydelta,dummygamma,dummyvega,dummyrho;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,calltheta,dummyvega,dummyrho);
       
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,calltheta,dummyvega,dummyrho);
       
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

       calltheta = theta(1,price,strike,t,rate,dividend,volatility);

       break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,calltheta,dummyvega,dummyrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_call_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,dummygamma,calltheta,dummyvega,dummyrho);

      break;

#endif // FINRECIPES

    default:

      calltheta = NAN;

      break;

  } // switch(dat->modeltype)

  dat->calltheta = calltheta;

  return *dat;

} // struct _data option_call_theta(struct _data *dat)

struct _data option_put_theta(struct _data *dat)
{
  double puttheta;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  double dividend = dat->dividend;
  double dummydelta,dummygamma,dummyvega,dummyrho;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,puttheta,dummyvega,dummyrho);
       
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,puttheta,dummyvega,dummyrho);
       
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

       puttheta = theta(0,price,strike,t,rate,dividend,volatility);

       break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,puttheta,dummyvega,dummyrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_put_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,dummygamma,puttheta,dummyvega,dummyrho);

      break;

#endif // FINRECIPES

    default:

      puttheta = NAN;

      break;

  } // switch(dat->modeltype)

  dat->puttheta = puttheta;

  return *dat;

} // struct _data option_put_theta(struct _data *dat)

struct _data option_call_rho(struct _data *dat)
{
  double callrho;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  double dividend = dat->dividend;
  double dummydelta,dummygamma,dummytheta,dummyvega;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,callrho);
       
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,callrho);
       
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

       callrho = rho(1,price,strike,t,rate,dividend,volatility);

       break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_call_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,callrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_call_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,dummygamma,dummytheta,dummyvega,callrho);

      break;

#endif // FINRECIPES

     default:

      callrho = NAN;

      break;

  } // switch(dat->modeltype)

  dat->callrho = callrho;

  return *dat;

} // struct _data option_call_rho(struct _data *dat)

struct _data option_put_rho(struct _data *dat)
{
  double putrho;

  const double price = dat->price;
  const double strike = dat->strike;
  const double rate = dat->rate;
  const double t = dat->t[0]-dat->te;
  const double volatility = dat->volatility;
  double dividend = dat->dividend;
  double dummydelta,dummygamma,dummytheta,dummyvega;

  switch(dat->modeltype)
  {

#if defined(ABRADFORD) && defined(FINRECIPES)

    case BLACKSCHOLES:
    case MERTON73:
    case BLACK76:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,putrho);
       
       break;

#endif // #if defined(ABRADFORD) && defined(FINRECIPES)

#if defined(METAOPTIONS) && defined(FINRECIPES)

    case BLACKSCHOLES2:
    case MERTON73B:
    case BLACK76B:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,putrho);
       
       break;

#endif // #if defined(METAOPTIONS) && defined(FINRECIPES)

#ifdef METAOPTIONS

    case GBS:

       putrho = rho(0,price,strike,t,rate,dividend,volatility);

       break;

#endif // METAOPTIONS

#ifdef FINRECIPES

    case BLACKSCHOLES3:
    case FUTOPTEURBLACK:
    case BSPAYOUT:

       option_price_partials_put_black_scholes(price,strike,rate,volatility,t,dummydelta,dummygamma,dummytheta,dummyvega,putrho);
       
       break;

    case AMERBINOMIAL:
    case AMERBINOMIALDIV:

       option_price_partials_american_call_binomial(price,strike,rate,volatility,t,dat->steps,dummydelta,dummygamma,dummytheta,dummyvega,putrho);

      break;

#endif // FINRECIPES

    default:

      putrho = NAN;

      break;

  } // switch(dat->modeltype)

  dat->putrho = putrho;

  return *dat;

} // struct _data option_put_rho(struct _data *dat)
