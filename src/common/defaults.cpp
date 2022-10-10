/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: defaults.cpp of optionmatrix                                       */
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

#include "defs.h"
#include "extern.h"

#include <signal.h>

void programInits(struct _properties *properties)
{

#ifdef HAVE_LIBGSL

    gsl_set_error_handler_off();

#endif

    properties->lc = localeconv();

    signal(SIGFPE,SIG_IGN);
    signal(SIGILL,SIG_IGN);
    signal(SIGSEGV,SIG_IGN);

#ifdef HAVE_ATEXIT

    atexit(programExit);

#endif

    if( pthread_mutex_init(&properties->data.mutexCashflow, NULL) != 0 )
    {
      fprintf(stderr,"programInits(): pthread_mutex_init() mutexCashflow failed.\n");
    }

    time(&properties->starttime);
    time(&properties->starttime2);
    time(&properties->starttime3);
    time(&properties->starttime4);

    properties->listModelsForGroups = NULL;

#ifdef FINRECIPES

    int index;
    const int count = sizeofterm_structure_list / (signed) sizeof(term_structure);
    properties->termstructure_name_list = ( _int_to_name_nonconst * ) malloc( count * sizeof(_int_to_name_nonconst) ); 

    for( index = 0 ; index < count ; index++ )
    {
      //g_print("index = %d\n", index);
      int term = term_structure_list[index].modeltype;
      snprintf(&properties->termstructure_name_list[index].string[0],sizeof(properties->termstructure_name_list[index].string),
               "%s", option_algorithms[term].des);
      //g_print("\"%s\"\n",&properties->termstructure_name_list[index].string[0]);
    }

    option_algorithms[BONDSTERM].StateNames = ( _int_to_name * ) properties->termstructure_name_list;
    option_algorithms[EURBOND_HO_LEE].StateNames = ( _int_to_name * ) properties->termstructure_name_list;

#endif

} // void programInits(struct _properties *properties)

void props_defaults_options(struct _properties *properties, const int clearcalendar)
{  
    /*
     * Set the default properties
     */
    properties->data.debug = false;
    properties->textExport = false;
    properties->fileExport = false;    

    properties->modeltype = 0;
    properties->decimalorcalendar = CALENDAR;
 
#if defined(HAVE_LIBGTK_3) || defined(HAVE_LIBGTK_X11_2_0)
    properties->GtkInfo.checkbuttonDateEngineIgnore = false;
#endif

    if( clearcalendar == 1 )
    {
      properties->occurence_day = 5; /* days since sunday (0,6) */
      properties->occurence_in_month = 3;
      properties->occurence_plus_offset = 1;
      properties->optionscycle = 0;
      properties->precision = 6;

      /*
       * 43140 is 11:59:00, 43200 would be noon exact, options expire
       * 3rd friday+1 (the saturday at 11:59:00)
       */
      properties->expiration_time = 43140;
    
      /*
       * set option expiration time to 11:59:00, these next variables
       * are used for display purposes and are translate into seconds
       * and stored into properties->expiration_time
       */
      properties->expiration_hour = 11;
      properties->expiration_minute = 59;
      properties->expiration_second = 0;

      properties->skipmonth  = 0;
      properties->skipmonth2 = 1;
      properties->day_offset_counter = 0;
      properties->day_offset = 0;
      properties->adjusttime = 0;
    }

    properties->format = -1;

    properties->start_time_to_expiration = properties->time_to_expiration = NULL;
    properties->start_days_to_expiration = properties->days_to_expiration = NULL;
    properties->start_expiration_month = properties->expiration_month = NULL;
    properties->start_expiration_year = properties->expiration_year = NULL;

    properties->start_time_to_expiration2 = properties->time_to_expiration2 = NULL;
    properties->start_days_to_expiration2 = properties->days_to_expiration2 = NULL;
    properties->start_expiration_month2 = properties->expiration_month2 = NULL;
    properties->start_expiration_year2 = properties->expiration_year2 = NULL;

    properties->realTimeBleeding = 1;
    properties->updatedelayseconds = 1;
    properties->highlightInTheMoney = 1;

    properties->distribution_type = NORMAL_DISTRIBUTION;

    /*
     * mean = 0 and variance = 1 for the standard normal
     * distribution
     */
    properties->distribution_mean = 0;
    properties->distribution_variance = 1;

    properties->integration_type = POLYNOMIAL_APPROX6;

    properties->strikestoogle = 0;
    properties->customstrike = 0;
    properties->strike_offset = 0;
    properties->discard = 0;
    properties->data.t[1] = 0.20;
    properties->data.t[2] = 0.25;

    /* curses specific */
    properties->start = 5;
    properties->mode = 1;
    properties->demotype = -1;

    srand(time(0));

    properties->listModelsForGroups = NULL;
    properties->data_dir[0] = 0;

    return;

} // void props_defaults_options(struct _properties *properties, const int clearcalendar)

// props_defaults_futures() is only used by the curses version of this 
// program...
void props_defaults_futures(struct _properties *properties, const int clearcalendar)
{

  void props_defaults_options(struct _properties *properties,const int clearcalendar);

  /* get the option properties then below change for futures */
  props_defaults_options(properties,clearcalendar);

  properties->modeltype = _FUTURES;

  /*
   * lets make our futures expire 3rd friday+0
   * at 16:30
   */

  properties->occurence_in_month = 3;
  properties->occurence_plus_offset = 0;
  properties->expiration_time = 59400;

  properties->expiration_hour = 16;
  properties->expiration_minute = 30;
  properties->expiration_second = 0;

  return;

} // void props_defaults_futures(struct _properties *properties, const int clearcalendar)

void programExit(void)
{

} // void programExit(void)
