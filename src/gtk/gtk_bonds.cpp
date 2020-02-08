/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_bonds.cpp of optionmatrix                                      */
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

#include "../common/defs.h"
#include "../common/extern.h"
#include "gtk_extern.h"
#include "../common/prototypes.h"

struct _data bonddispatch(struct _properties *p)
{
  struct _data *dat;
  dat = (struct _data *) &p->data;
  const double rate = dat->rate;

  const double t  = dat->t[0] - dat->te;
  const double t2 = dat->t[1] - dat->te2;
  const double t3 = dat->t[2] - dat->te3;

  //g_print("t = %f\n", t);
  //g_print("t2 = %f\n", t2);
  //g_print("t3 = %f\n", t3);

  //g_print("rate = %f\n", rate);

  dat->bond_price = 0;
  dat->pv_discrete = 0;
  dat->pv_continous = 0;
  dat->irr_discrete = 0;
  dat->irr = 0;
  dat->uirr = false;
  dat->YTMDiscrete = 0;
  dat->YTMContinous = 0;
  dat->durationDiscrete = 0;
  dat->durationContinous = 0;
  dat->durationMacaulayDiscrete = 0;
  dat->durationModifiedDiscrete = 0;
  dat->convexityDiscrete = 0;
  dat->convexityContinous = 0;
  dat->call = 0;

  try {

  switch(dat->modeltype)
  {

#ifdef FINRECIPES

  case BONDS:
    {

    //g_print("BOND Flat term\n");

    pthread_mutex_lock(&dat->mutexCashflow);

    static int numberOfCoupons = 5;
    int numberOfCouponsSelected = dat->UseS;

    static double couponValue = 1.25;
    double couponValueSelected = dat->UseT;

    static int periodicity = 2;
    int periodicitySelected = (int) dat->UseQ;

    static double firstCoupon = .25;
    double firstCouponSelected = dat->UseR;

    g_print("firstCoupon = %f, firstCouponSelected = %f\n", firstCoupon, firstCouponSelected);
    //g_print("dat->coupon.size() = %d\n", dat->coupon.size() );

    if( numberOfCoupons != numberOfCouponsSelected || couponValue != couponValueSelected ||
        periodicity != periodicitySelected || firstCoupon != firstCouponSelected )
    {
      numberOfCoupons = numberOfCouponsSelected;
      couponValue = couponValueSelected;
      periodicity = periodicitySelected;
      firstCoupon = firstCouponSelected;

      g_print("Number of Coupons Changed: %d\n", numberOfCoupons);

      dat->coupon.erase( dat->coupon.begin(), dat->coupon.end() );
      dat->coupon_times.erase( dat->coupon_times.begin(), dat->coupon_times.end() );

      int counter;
      for(counter = 0; counter < numberOfCoupons; counter++)
      {
        dat->coupon_times.push_back(firstCoupon);

        if( counter == (numberOfCoupons - 1) )
            dat->coupon.push_back(100 + dat->UseT); 
        else
          dat->coupon.push_back(dat->UseT); 
        
        if( periodicity )
          firstCoupon +=  (double) 1 / periodicity;
      }

    }

    if(dat->debug)
    {
      g_print("coupons = ");
      
      for( std::vector<double>::iterator it = dat->coupon.begin(); it != dat->coupon.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\ntimes = ");

      for( std::vector<double>::iterator it = dat->coupon_times_adjusted.begin(); it != dat->coupon_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");
 
    } // if(dat->debug)

    // cash_flow_pv_discrete() and bonds_price_discrete() should produce the
    // same result...
    dat->pv_discrete = cash_flow_pv_discrete(dat->coupon_times_adjusted,dat->coupon,rate);
    double pv_discrete2 = bonds_price_discrete(dat->coupon_times_adjusted,dat->coupon,rate);
    double epsilon = 0.00001;

    if ( fabs(dat->pv_discrete - pv_discrete2) > epsilon )
      g_print("ERROR: Mismatch dat->pv_discrete( %f ) != pv_discrete2 ( %f )\n", dat->pv_discrete,pv_discrete2);

    // cash_flow_pv() and bonds_price() should produce the
    // same result..
    dat->pv_continous = cash_flow_pv(dat->coupon_times_adjusted,dat->coupon,rate);
    double pv_continous2 = bonds_price(dat->coupon_times_adjusted,dat->coupon,rate);

    if ( fabs(dat->pv_continous - pv_continous2) > epsilon )
      g_print("ERROR: Mismatch dat->pv_continous( %f ) != pv_continous2 ( %f )\n", dat->pv_continous,pv_continous2);

    //

    dat->YTMDiscrete = bonds_yield_to_maturity_discrete(dat->coupon_times_adjusted,dat->coupon,dat->pv_discrete);
    dat->YTMContinous = bonds_yield_to_maturity(dat->coupon_times_adjusted,dat->coupon,dat->pv_continous);
    dat->durationContinous = bonds_duration(dat->coupon_times_adjusted,dat->coupon,rate);
    dat->durationDiscrete = bonds_duration_discrete(dat->coupon_times_adjusted,dat->coupon,rate);
    dat->durationMacaulayDiscrete = bonds_duration_macaulay_discrete(dat->coupon_times_adjusted,dat->coupon,dat->pv_discrete);
    dat->durationModifiedDiscrete = bonds_duration_modified_discrete(dat->coupon_times_adjusted,dat->coupon,dat->pv_discrete);
    dat->convexityContinous = bonds_convexity(dat->coupon_times_adjusted,dat->coupon,rate);
    dat->convexityDiscrete = bonds_convexity_discrete(dat->coupon_times_adjusted,dat->coupon,rate);

    pthread_mutex_unlock(&dat->mutexCashflow);

    }

    break;

  case BONDSTERM:
    {

    //g_print("term structure selected: %s\n", &option_algorithms[BONDSTERM].StateNames[dat->UsePound-1].string[0]);
    //g_print("term model number      : %d\n", term_structure_list[dat->UsePound-1].modeltype);

    // I would like to give BONDSTERM control over numberOfCoupons, couponValue, periodicity and
    // firstCoupon but I'm out of internal values to support this...

    static int term_struct_bondsterm = -1;
    int term_selected = dat->UsePound-1;

    if( term_selected != term_struct_bondsterm )
    {
      term_struct_bondsterm = term_selected;
      //g_print("BONDSTERM: term struct changed\n");

      on_comboboxModel_changed_hide(term_structure_list[dat->UsePound-1].modeltype,p);
      on_comboboxModel_changed_show(term_structure_list[dat->UsePound-1].modeltype,p);
      updateTime(term_structure_list[dat->UsePound-1].modeltype,p);
      updateVolatility(term_structure_list[dat->UsePound-1].modeltype,p);
      updatePrecision(term_structure_list[dat->UsePound-1].modeltype,p);
    }

    struct _data termstructuredata;
    p->data.term_model = term_structure_list[dat->UsePound-1].modeltype;
    termstructuredata = termstructure(&p->data);

    pthread_mutex_lock(&dat->mutexCashflow);

    if(dat->debug)
    {
      g_print("coupons = ");
      
      for( std::vector<double>::iterator it = dat->coupon.begin(); it != dat->coupon.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\ntimes = ");

      for( std::vector<double>::iterator it = dat->coupon_times_adjusted.begin(); it != dat->coupon_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");

    } // if(dat->debug)

    dat->bond_price = bonds_price(dat->coupon_times_adjusted,dat->coupon,*dat->term);
    dat->durationContinous = bonds_duration(dat->coupon_times_adjusted,dat->coupon,*dat->term);
    dat->convexityContinous = bonds_convexity(dat->coupon_times_adjusted,dat->coupon,*dat->term);

    delete dat->term;

    pthread_mutex_unlock(&dat->mutexCashflow);

    }

    break;

  case BONDSPRINCIPAL:
    {

    //g_print("BOND w/ Principal Payments\n");

    pthread_mutex_lock(&dat->mutexCashflow);

    static int numberOfCoupons = 5;
    int numberOfCouponsSelected = dat->UseS;

    static double couponValue = 1.25;
    double couponValueSelected = dat->UseT;

    static int periodicity = 2;
    int periodicitySelected = (int) dat->UseQ;

    static double firstCoupon = .25;
    double firstCouponSelected = dat->UseR;

    g_print("firstCoupon = %f, firstCouponSelected = %f\n", firstCoupon, firstCouponSelected);
    //g_print("dat->coupon.size() = %d\n", dat->coupon.size() );

    if( numberOfCoupons != numberOfCouponsSelected || couponValue != couponValueSelected ||
        periodicity != periodicitySelected || firstCoupon != firstCouponSelected )
    {
      numberOfCoupons = numberOfCouponsSelected;
      couponValue = couponValueSelected;
      periodicity = periodicitySelected;
      firstCoupon = firstCouponSelected;

      g_print("Number of Coupons Changed: %d\n", numberOfCoupons);

      dat->coupon.erase( dat->coupon.begin(), dat->coupon.end() );
      dat->coupon_times.erase( dat->coupon_times.begin(), dat->coupon_times.end() );

      int counter;
      for(counter = 0; counter < numberOfCoupons; counter++)
      {
        dat->coupon_times.push_back(firstCoupon);
        dat->coupon.push_back(dat->UseT); 
        
        if( periodicity )
          firstCoupon +=  (double) 1 / periodicity;

      } // for(counter = 0; counter < numberOfCoupons; counter++)

    }

    static int numberOfPrincipal = 5;
    int numberOfPrincipalSelected = dat->UseJ;

    static double principalValue = 20;
    double principalValueSelected = dat->UseP;

    static int pperiodicity = 2;
    int pperiodicitySelected = (int) dat->UseZ;

    static double firstPrincipal = .25;
    double firstPrincipalSelected = dat->UseB;

    //g_print("pperiodicity = %d, dat->UseZ = %f\n", pperiodicity, dat->UseZ );
    //g_print("dat->principal.size() = %d\n", dat->principal.size() );

    if( numberOfPrincipal != numberOfPrincipalSelected || principalValue != principalValueSelected ||
        pperiodicity != pperiodicitySelected ||  firstPrincipal != firstPrincipalSelected )
    {
      numberOfPrincipal = numberOfPrincipalSelected;
      principalValue = principalValueSelected;
      pperiodicity = pperiodicitySelected;
      firstPrincipal = firstPrincipalSelected;

      g_print("Number of Principal Changed: %d\n", numberOfPrincipal);

      dat->principal.erase( dat->principal.begin(), dat->principal.end() );
      dat->principal_times.erase( dat->principal_times.begin(), dat->principal_times.end() );

      int counter;
      for(counter = 0; counter < numberOfPrincipal; counter++)
      {
        dat->principal_times.push_back(firstPrincipal);
        dat->principal.push_back(dat->UseP); 

        if( pperiodicity )
          firstPrincipal +=  (double) 1 / pperiodicity;

      } // for(counter = 0; counter < numberOfPrincipal; counter++)

    }

    if(dat->debug)
    {
      g_print("coupon = ");
      
      for( std::vector<double>::iterator it = dat->coupon.begin(); it != dat->coupon.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\ncoupon times = ");

      for( std::vector<double>::iterator it = dat->coupon_times_adjusted.begin(); it != dat->coupon_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");
      g_print("principal = ");
      
      for( std::vector<double>::iterator it = dat->principal.begin(); it != dat->principal.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\nprincipal times = ");
      for( std::vector<double>::iterator it = dat->principal_times_adjusted.begin(); it != dat->principal_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");

    } // if(dat->debug)

    dat->bond_price = bonds_price(dat->coupon_times_adjusted, dat->coupon,dat->principal_times_adjusted, dat->principal, rate);

    pthread_mutex_unlock(&dat->mutexCashflow);
    
    }

    break;

  case IRR:

    //g_print("Internal Rate of Return\n");

    pthread_mutex_lock(&dat->mutexCashflow);

    if(dat->debug)
    {
      g_print("cash flows = ");
      
      for( std::vector<double>::iterator it = dat->coupon.begin(); it != dat->coupon.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\ntimes = ");

      for( std::vector<double>::iterator it = dat->coupon_times_adjusted.begin(); it != dat->coupon_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");

    } // if(dat->debug)

    dat->pv_continous = cash_flow_pv(dat->coupon_times_adjusted,dat->coupon,rate);
    dat->pv_discrete = cash_flow_pv_discrete(dat->coupon_times_adjusted,dat->coupon,rate);
    dat->irr_discrete = cash_flow_irr_discrete(dat->coupon_times_adjusted,dat->coupon);
    dat->irr = cash_flow_irr(dat->coupon_times_adjusted,dat->coupon);
    dat->uirr = cash_flow_unique_irr(dat->coupon_times_adjusted,dat->coupon);

    pthread_mutex_unlock(&dat->mutexCashflow);

    break;

  case EURBOND_HO_LEE:
    {

    static int term_struct_eurbond_ho_lee = -1;
    int term_selected = dat->UsePound-1;

    if( term_selected != term_struct_eurbond_ho_lee )
    {
      term_struct_eurbond_ho_lee = term_selected;
      //g_print("EURBOND_HO_LEE: term struct changed\n");

      on_comboboxModel_changed_hide(term_structure_list[dat->UsePound-1].modeltype,p);
      on_comboboxModel_changed_show(term_structure_list[dat->UsePound-1].modeltype,p);
      updateTime(term_structure_list[dat->UsePound-1].modeltype,p);
      updateVolatility(term_structure_list[dat->UsePound-1].modeltype,p);
      updatePrecision(term_structure_list[dat->UsePound-1].modeltype,p);

      gtk_widget_show(p->GtkInfo.spinbuttonUseS);
      gtk_widget_show(p->GtkInfo.labelUseS);
      gtk_widget_show(p->GtkInfo.spinbuttonUseT);
      gtk_widget_show(p->GtkInfo.labelUseT);
      gtk_widget_show(p->GtkInfo.label3);
      gtk_widget_show(p->GtkInfo.labelPrice);
      gtk_widget_show(p->GtkInfo.spinbuttonPrice);

    } // if( term_selected != term_struct_eurbond_ho_lee )

    struct _data termstructuredata;
    p->data.term_model = term_structure_list[dat->UsePound-1].modeltype;
    termstructuredata = termstructure(&p->data);

    pthread_mutex_lock(&dat->mutexCashflow);

    if(dat->debug)
    {
      g_print("coupons = ");
      
      for( std::vector<double>::iterator it = dat->coupon.begin(); it != dat->coupon.end(); ++it)
      {
        g_print("%lf ", *it);
      }
      g_print("\ntimes = ");

      for( std::vector<double>::iterator it = dat->coupon_times_adjusted.begin(); it != dat->coupon_times_adjusted.end(); ++it)
      {
        g_print("%lf ", *it);
      }

      g_print("\n");

    } // if(dat->debug)

    if(dat->debug)
        logger( (char *)"price_european_call_option_on_bond_using_ho_lee", 6,
                                                    (double) dat->UseS, 
                                                    (double) dat->UseT,
                                                    (double) 0,
                                                    (double) 0,
                                                    (double) dat->price, 
                                                    (double) t3);

    dat->call = price_european_call_option_on_bond_using_ho_lee(
                                                    dat->term,
                                                    dat->UseS,
                                                    dat->UseT,
                                                    dat->coupon_times_adjusted,
                                                    dat->coupon,
                                                    dat->price,
                                                    t3);

    delete dat->term;

    pthread_mutex_unlock(&dat->mutexCashflow);

    }

    break;

#endif // FINRECIPES

  default:

      fprintf(stderr,"bonddispatch(): No implementation for case %d\n",dat->modeltype);

      break;

  } // switch(dat->modeltype)

  }
  catch (exception& e)
  {
    fprintf(stderr,"bonddispatch(): Exception caught: %s\n", e.what() );
    fprintf(stderr,"Model = %d\n", dat->modeltype);

  } catch (...)
  {
    fprintf(stderr,"bonddispatch(): unknown error\n");
    fprintf(stderr,"Model = %d\n", dat->modeltype);
  }

  return *dat;

} // struct _data bonddispatch(struct _properties *p)
