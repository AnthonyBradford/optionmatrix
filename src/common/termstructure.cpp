/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: termstructure.cpp of optionmatrix                                  */
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

struct _data termstructure(struct _data *dat)
{

  const double rate = dat->rate;
  const double t  = dat->t[0] - dat->te;
  const double t2 = dat->t[1] - dat->te2;
  const double sigma = dat->volatility;

  //g_print("rate = %f\n", rate);
  //g_print("modeltype = %d\n", dat->modeltype);

  try {

  switch(dat->term_model)
  {

#ifdef FINRECIPES

    case TERMFLAT:
      {
        //g_print("TERMFLAT\n");

        term_structure_class_flat *term;
        dat->term = (term_structure_class *) new term_structure_class_flat(rate);
        term = (term_structure_class_flat *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);

      }
      break;

    case TERMCIR:        // termstru_discfact_cir.c
      {
        //g_print("TERMCIR\n");

        term_structure_class_cir *term;
        dat->term = (term_structure_class *) new term_structure_class_cir(rate,dat->UseZ,dat->UseB,dat->UseJ,sigma);
        term = (term_structure_class_cir *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);

      }

      break;

    case TERMVASICEK:
      {
        //g_print("TERMVASICEK\n");

        term_structure_class_vasicek *term;
        dat->term = (term_structure_class *) new term_structure_class_vasicek(rate,dat->UseZ,dat->UseB,sigma);
        term = (term_structure_class_vasicek *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);

      }

      break;

    case TERMNELSONSIEGEL:
      {
        //g_print("TERMNELSONSIEGEL\n");

        term_structure_class_nelson_siegel *term;
        dat->term = (term_structure_class *) new term_structure_class_nelson_siegel(dat->UseZ,dat->UseB,dat->UseJ,dat->UseP);
        term = (term_structure_class_nelson_siegel *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);
 
      }

      break;

    case TERMSVENSSON:
      {
        //g_print("TERMSVENSSON\n");

        term_structure_class_svensson *term;
        dat->term = (term_structure_class *) new term_structure_class_svensson(dat->UseZ,dat->UseB,dat->UseJ,dat->UseP,dat->UseQ,dat->UseR);
        term = (term_structure_class_svensson *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);
      }

      break;

    case TERMCUBICSPLINE:
      {
        //g_print("TERMCUBICSPLINE\n");

        pthread_mutex_lock(&dat->mutexCashflow);

        if(dat->debug)
        {
          //g_print("dividends = ");

          for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
          {
            //g_print("%lf ", *it);
          }

          //g_print("\ntimes = ");

          for( std::vector<double>::iterator it = dat->times_adjusted.begin(); it != dat->times_adjusted.end(); ++it)
          {
            //g_print("%lf ", *it);
          }

          //g_print("\n");
        }

        term_structure_class_cubic_spline *term;
        dat->term = (term_structure_class *) new term_structure_class_cubic_spline(dat->UseZ,dat->UseB,dat->UseJ,dat->amounts,dat->times_adjusted);
        term = (term_structure_class_cubic_spline *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);
 
        pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

    case TERMINTERPOLATED:
      {
        //g_print("TERMINTERPOLATED\n");

        pthread_mutex_lock(&dat->mutexCashflow);

        if(dat->debug)
        {
          //g_print("dividends = ");

          for( std::vector<double>::iterator it = dat->amounts.begin(); it != dat->amounts.end(); ++it)
          {
            //g_print("%lf ", *it);
          }

          //g_print("\ntimes = ");

          for( std::vector<double>::iterator it = dat->times_adjusted.begin(); it != dat->times_adjusted.end(); ++it)
          {
            //g_print("%lf ", *it);
          }

          //g_print("\n");
        }

        term_structure_class_interpolated *term;
        dat->term = (term_structure_class *) new term_structure_class_interpolated(dat->times_adjusted,dat->amounts);
        term = (term_structure_class_interpolated *) dat->term;

        dat->discount_t1 = term->d(t);
        dat->discount_t2 = term->d(t2);
        dat->spot_t1 = term->r(t);
        dat->spot_t2 = term->r(t2);
        dat->forward = term->f(t,t2);

        pthread_mutex_unlock(&dat->mutexCashflow);

      }

      break;

#endif

     default:

      fprintf(stderr,"termstructure(): No implementation for case %d\n",dat->modeltype);

      break;
  }

  }
  catch (exception& e)
  {
    fprintf(stderr,"termstructure(): Exception caught: %s\n", e.what() );
    fprintf(stderr,"Model = %d\n", dat->modeltype);

  } catch (...)
  {
    fprintf(stderr,"termstructure(): unknown error\n");
    fprintf(stderr,"Model = %d\n", dat->modeltype);
  }

  return *dat;
}
