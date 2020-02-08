/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_demo.cpp of optionmatrix                                    */
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

#include "../common/defs.h"
#include "../common/extern.h"
#include "curses_include.h"

int init_demo(struct _properties *properties)
{
  int x;
  int height, width;

  /* get screen size */
  getmaxyx(stdscr, height, width);

  properties->demotype = DECIMAL_GREEKS;

  properties->customstrike = 100;
  properties->data.t[0] = .25;

  clear();
  refresh();

  if( !DoWeHaveOptions(properties) )
  {
    printw("No Options Models implemented\nPress any key\n");
    refresh();

    noecho();
    getch();
    echo();

    return -1;
  }

  properties->modeltype = SetToOption(properties);

  if( option_algorithms[properties->modeltype].supportDividend == 2 )
  {
    properties->data.dividend = option_algorithms[properties->modeltype].defaultDividend;
  }

  /* set the seed as the time */
  srand( time(0) );

  /* give a random fireworks display */
  for(x = 1; x < 50; ++x)
  {
    /* 0 to row-1, 0 to col-1 */
    move((int)(height * (rand() / (RAND_MAX + 1.0))),(int)(width * (rand() / (RAND_MAX + 1.0))));

    printw("OPTIONS");
      
    refresh();
    
    myusleep(8500);

  } // for(x = 1; x < 50; ++x)

  if( myusleep(1000000) == -1 )
  {
    return -1;
  }

  clear();

  ///////////////////////////////////////////////////////////////////

  properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
  properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
  properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
  properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
  properties->data.UsePound = option_algorithms[properties->modeltype].Pounddefault;
  properties->data.steps = option_algorithms[properties->modeltype].steps;

  //////////////////////////////////////////////////////////////////

  move(0,0);

  printw("Enter stock price                    : ");

  myusleep(500000);
  refresh();

  /* make it look like someone is typing */
  printw("1"); myusleep(200000); refresh();
  printw("0"); myusleep(300000); refresh();
  printw("0"); myusleep(200000); refresh();
  properties->data.price = 100;
            
  move(1,0);
  printw("Enter strike price                   : ");
  printw("9"); myusleep(200000); refresh();
  printw("0"); myusleep(300000); refresh();
  properties->customstrike = 90;

  move(2,0);
  printw("Enter interest rate     (%s06 = 6%%)   : ", properties->lc->mon_decimal_point);

  /* make it look like someone is typing */
  printw("%s", properties->lc->mon_decimal_point); 
  myusleep(200000); refresh();
  printw("0"); myusleep(300000); refresh();
  printw("6"); myusleep(200000); refresh();
  properties->data.rate = .06;

  move(3,0);
  printw("Time to expiration    (%s25=1/4 year) : ", properties->lc->mon_decimal_point);

  /* make it look like someone is typing */
  printw("%s", properties->lc->mon_decimal_point); 
  myusleep(200000); refresh();
  printw("2"); myusleep(300000); refresh();
  printw("5"); myusleep(200000); refresh();
  move(3,0);
  printw("Time to expiration    (%s25=1/4 year) : %.6f, %.3f days, %s", properties->lc->mon_decimal_point,0.25,(365*(properties->data.t[0])),decimal_date_to_real_date(0.25));
  properties->data.t[0] = .25;

  time(&properties->starttime);
  time(&properties->starttime2);
            
  move(4,0);
  printw("Enter standard deviation             : ");
  /* make it look like someone is typing */
  printw("%s", properties->lc->mon_decimal_point); 
  myusleep(200000); refresh();
  printw("3"); myusleep(300000); refresh();
  printw("5"); myusleep(200000); refresh();
  properties->data.volatility = .35;

  expires(LEG1,30,properties->skipmonth,properties);

  if( myusleep(500000) == -1 )
  {
    return -1;
  }

  clear();
  refresh();

  properties->format = DECIMAL_GREEKS;
  properties->decimalorcalendar = DECIMALS;

  matrix(properties,properties);
  move(4,0);
  printw("%s supports date entry and decimal dates", PACKAGE_NAME);
  clrtoeol();
  refresh();

  if( myusleep(2000000) == -1 )
  {
    return -1;
  }

  properties->format = DECIMAL_OPTIONS;
  properties->decimalorcalendar = DECIMALS;

  matrix(properties,properties);
  refresh();
  
  if( myusleep(2000000) == -1 )
  {
    return -1;
  }

  if( option_algorithms[properties->modeltype].supportTime2 != 1 )
  {
    properties->format = CALENDAR_OPTIONS3;
    properties->decimalorcalendar = CALENDAR;

    matrix(properties,properties);
    move(4,0);
    printw("%s supports calendar dates", PACKAGE_NAME);
    clrtoeol();
    refresh();
    
    if( myusleep(2000000) == -1 )
    {
      return -1;
    }
    
    properties->format = CALENDAR_OPTIONS5;
    properties->decimalorcalendar = CALENDAR;

    matrix(properties,properties);
    refresh();
    
    if( myusleep(2000000) == -1 )
    {
      return -1;
    }

    properties->format = CALENDAR_OPTIONS6;
    properties->decimalorcalendar = CALENDAR;

    matrix(properties,properties);
    move(4,0);
    printw("%s supports many formats", PACKAGE_NAME);
    clrtoeol();
    refresh();
    
    if( myusleep(2000000) == -1 )
    {
      return -1;
    }
  }
  
  properties->format = DEMO_OPTIONS;
  properties->decimalorcalendar = DECIMALS;

  clear();
  refresh();

  return 0;

} // int init_demo(struct _properties *properties)

int init_futures_demo(struct _properties *properties, struct _properties *future_properties)
{
  int height, width;

  /* get screen size */
  getmaxyx(stdscr, height, width);

  int x;

  clear();
  refresh();

  if( !DoWeHaveFutures(properties) )
  {
    printw("No Futures Models implemented\nPress any key\n");
    refresh();

    noecho();
    getch();
    echo();

    return -1;
  }

  /* set the seed as the time */
  srand( time(0) );

  /* give a random fireworks display */
  for(x = 1; x < 50; ++x)
  {
    /* 0 to row-1, 0 to col-1 */
    move((int)(height * (rand() / (RAND_MAX + 1.0))),(int)(width * (rand() / (RAND_MAX + 1.0))));
    printw("FUTURES");
    
    refresh();

    myusleep(8500);
  }

  if( myusleep(1000000) == -1 )
  {
    return -1;
  }

  clear();

  move(0,0);
  printw("Enter spot price                     : ");
  myusleep(500000);
  refresh();

  /* make it look like someone is typing */
  printw("1"); myusleep(200000); refresh();
  printw("0"); myusleep(300000); refresh();
  printw("0"); myusleep(200000); refresh();
  properties->data.price = 100;

  myusleep(200000);
            
  move(1,0);
  printw("Enter interest rate     (%s05 = 6%%)   : ", properties->lc->mon_decimal_point);

  /* make it look like someone is typing */
  printw("%s", properties->lc->mon_decimal_point);
  myusleep(200000); refresh();
  printw("0"); myusleep(300000); refresh();
  printw("6"); myusleep(200000); refresh();
  properties->data.rate = .06;

  move(2,0);
  printw("Time to expiration    (%s25=1/4 year) : ", properties->lc->mon_decimal_point);

  /* make it look like someone is typing */
  printw("%s", properties->lc->mon_decimal_point);
  myusleep(200000); refresh();
  printw("2"); myusleep(300000); refresh();
  printw("5"); myusleep(200000); refresh();

  myusleep(500000);

  move(2,0);
  printw("Time to expiration    (%s25=1/4 year) : %.6f, %.3f days, %s\n", properties->lc->mon_decimal_point,0.25,(365*(properties->data.t[0])),decimal_date_to_real_date(0.25));
  properties->data.t[0] = .25;

  expires(LEG1,30,properties->skipmonth,future_properties);

  if( myusleep(2000000) == -1 )
  {
    return -1;
  }

  clear();
  refresh();

  properties->format = DECIMAL_FUTURE;
  properties->decimalorcalendar = DECIMALS;

  properties->modeltype = SetToFuture(properties);

  matrix(properties,future_properties);
  move(4,0);
  printw("%s supports date entry and decimal dates", PACKAGE_NAME);
  clrtoeol();
  refresh();

  if( myusleep(6000000) == -1 )
  {
    return -1;
  }

  properties->format = CALENDAR_FUTURE;
  properties->decimalorcalendar = CALENDAR;

  matrix(properties,future_properties);
  move(4,0);
  printw("%s supports calendar dates", PACKAGE_NAME);
  clrtoeol();
  refresh();

  if( myusleep(4000000) == -1 )
  {
    return -1;
  }

  properties->demotype = CALENDAR_FUTURE;
  properties->format = DEMO_FUTURES;

  clear();
  refresh();

  return 0;

} // int init_futures_demo(struct _properties *properties, struct _properties *future_properties)

int futures_demo(struct _properties *properties,struct _properties *future_properties, const int bPerpetual)
{
  static int numberofdemos = 0;

  if( numberofdemos++ == 0 )
  {
    if( init_futures_demo(properties,future_properties) == 0 )
    {
      return 0;

    } else
    {
      numberofdemos = 0;
      properties->day_offset = 0;
      properties->day_offset_counter = 0;
      properties->demotype = -1;
      properties->skipmonth = 0;
      properties->format = -1;

      return -1;
    }
  }

  if( numberofdemos < 10 )
  {
    properties->data.price = properties->data.price + .50;
    move(4,0); clrtoeol();
    printw("Increasing spot price %.2f", properties->data.price);
                    
  } else if( numberofdemos >= 10 && numberofdemos < 20 )
  {
    properties->data.rate = properties->data.rate - .0010;
    move(4,0); clrtoeol();
    printw("Decreasing interest rate %.4f", properties->data.rate);                        

  } else if( numberofdemos >= 20 && numberofdemos < 32)
  {
    properties->skipmonth++;

    move(4,0);
    printw("Skip month forward %d", properties->skipmonth); clrtoeol();

    expires(LEG1,30,properties->skipmonth,future_properties);
    
  } else if( numberofdemos >= 32 && numberofdemos < 38 )
  {
    move(4,0);

    clrtoeol();
                    
    properties->day_offset = properties->day_offset-((double)1/(double)365);
    printw("Day offset is %d days", ++properties->day_offset_counter); clrtoeol();
  }

  if( numberofdemos >= 38 )
  {
    if( bPerpetual )
    {
      numberofdemos = 0;
      properties->day_offset = 0;
      properties->day_offset_counter = 0;
      properties->skipmonth = 0;
      properties->demotype = DEMO_FUTURES;
      properties->format = DEMO_FUTURES;
      properties->decimalorcalendar = DECIMALS;

      return 0;

    } else
    {
      numberofdemos = 0;
      properties->day_offset = 0;
      properties->day_offset_counter = 0;
      properties->demotype = -1;
      properties->skipmonth = 0;
      properties->format = -1;

      myusleep(3000000);
    }
    
    return -1;
  }

  refresh();

  if( myusleep(500000) == -1 )
  {
    numberofdemos = 0;
    properties->day_offset = 0;
    properties->day_offset_counter = 0;
    properties->demotype = -1;
    properties->skipmonth = 0;
    properties->format = -1;

    props_defaults_futures(future_properties,0);

    return -1;

  } else
  {
    return 0;
  }

} // int futures_demo(struct _properties *properties,struct _properties *future_properties, const int bPerpetual)

int options_demo(struct _properties *properties, const int bPerpetual)
{
  static int numberofdemos = 0;

  if( numberofdemos++ == 0 )
  {
    if( init_demo(properties) == 0 )
    {
      return 0;

    } else
    {
      properties->demotype = -1;
      properties->format = -1;
      properties->skipmonth = 0;
      numberofdemos = 0;

      return -1;
    }
  }

  if ( option_algorithms[properties->modeltype].supportTime2 == 1 )
  {
    properties->decimalorcalendar = DECIMALS;
  }

  if( numberofdemos < 4 )
  {
    if( properties->demotype == DECIMAL_GREEKS )
    {
      properties->customstrike += 10;

      move(4,0);
      printw("Increasing strike %.2f", properties->customstrike); clrtoeol();

    } else
    {
      properties->strike_offset = properties->strike_offset + 5;
      
      move(4,0);
      printw("Increasing strikes"); clrtoeol();
    }
                    
  } else if( numberofdemos >= 4 && numberofdemos < 8 )
  {
    properties->data.price = properties->data.price + .50;
    move(4,0); clrtoeol();

    printw("Increasing stock price %.2f", properties->data.price);
    
  } else if( numberofdemos >= 8 && numberofdemos < 12 )
  {
    properties->data.rate = properties->data.rate - .0010;
    
    move(4,0); clrtoeol();
    printw("Decreasing interest rate %.4f", properties->data.rate);

  } else if( numberofdemos >= 12 && numberofdemos < 16 )
  {
    move(4,0);

    properties->data.volatility = properties->data.volatility + .01;
    printw("Increasing standard deviation %.4f", properties->data.volatility);
    clrtoeol();
                        
  } else if( numberofdemos >= 16 && numberofdemos < 20 )
  {
    move(4,0);
    clrtoeol();
                    
    if( properties->demotype == 1 || properties->demotype == DECIMAL_GREEKS )
    {
      if( (properties->data.t[0]-.01) > 0 )
      {
        properties->data.t[0] = properties->data.t[0] - .01;
        printw("Decreasing expiration time");

      } else
      {
        printw("Can't decrease expiration time");
        return 0;
      }
    }
                        
    if( properties->demotype > 1 && properties->demotype < 8 )
    {
      properties->day_offset = properties->day_offset+((double)1/(double)365);
      move(4,0);
      printw("Day offset is %d days", --properties->day_offset_counter);
    }
  } else if( numberofdemos >= 20 && numberofdemos < 30 )
  {
    /*
     * month walking looks best in formas 3,5,6 so lets
     * skip the other formats
     */
    if( properties->demotype != 3 && properties->demotype != 5 && properties->demotype != 6 )
    {
      numberofdemos = 30;
      return 0;
    }

    properties->skipmonth++;
    
    move(4,0);
    printw("Skip month forward %d", properties->skipmonth); clrtoeol();
    
    expires(LEG1,30,properties->skipmonth,properties);
    
  }                  

  if( numberofdemos >= 30 )
  {
    numberofdemos = 1;
    properties->strike_offset = 0.0;
    properties->day_offset = 0;
    properties->day_offset_counter = 0;
    properties->skipmonth = 0;

    expires(LEG1,30,properties->skipmonth,properties);
    
    move(4,0); clrtoeol();
    printw("Day offset is 0 days");
      
    ++properties->demotype;

    if(properties->demotype == 8 ||
       ( option_algorithms[properties->modeltype].supportTime2 == 1 &&
         properties->demotype == 2))
    {
      if( bPerpetual )
      {
        properties->demotype = 0;
        properties->skipmonth = 0;
        numberofdemos = 0;

        ///////////////////////////////////////////////////////////////////

        properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
        properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
        properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
        properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
        properties->data.UsePound = option_algorithms[properties->modeltype].Pounddefault;
        properties->data.steps = option_algorithms[properties->modeltype].steps;

        //////////////////////////////////////////////////////////////////

        return 0;
      } else
      {
        properties->demotype = -1;
        properties->format = -1;
        properties->skipmonth = 0;
        numberofdemos = 0;

        props_defaults_options(properties,0);

        return -1;
      }

    }
    if( properties->demotype != 0 &&
       option_algorithms[properties->modeltype].supportTime2 != 1 )
    {
      properties->decimalorcalendar = CALENDAR;
    }

    /* skip the next following formats */
    if( properties->demotype == 1 && 
       option_algorithms[properties->modeltype].supportTime2 != 1 )
    {
      properties->demotype = 2;
    }
    
  }

  refresh();

  if( myusleep(600000) == -1 )
  {
    properties->demotype = -1;
    properties->format = -1;
    properties->skipmonth = 0;
    numberofdemos = 0;
    
    return -1;

  } else
  {
    return 0;
  }

} // int options_demo(struct _properties *properties, const int bPerpetual)

int myusleep(const int useconds)
{
  char c;
  int i;

  nodelay(stdscr,TRUE);

  for( i = 0; i < 40; i++ )
  {
    noecho();
    c = getch();
    echo();

    if( c == 'q' || c == 'Q' || c == 27 )
    {
      nodelay(stdscr,FALSE);

      return -1;

    } // if( c == 'q' || c == 'Q' || c == 27 )

    timespec sleepValue = { 0 };
    sleepValue.tv_nsec = ( useconds / 40 ) * 1000;
    if( nanosleep(&sleepValue, NULL) < 0 )
    {
      printw("nanosleep() failed\n");
      refresh();
    }

  } // for( i = 0; i < 40; i++ )

  nodelay(stdscr,FALSE);

  return 0;

} // int myusleep(const int useconds)
