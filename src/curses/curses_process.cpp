/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_process.cpp of optionmatrix                                 */
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

void curses_process(struct _properties *properties,struct _properties *future_properties)
{
  int c = -1;

  for(;;)
  {
    // Q for quit or ESC key
    if( c == 'q' || c == 'Q' || c == 27 )
    {
      return;
    }

    if( day_changed() && properties->decimalorcalendar == CALENDAR )
    {
      expires(LEG1,30,properties->skipmonth,future_properties);
    }

    matrix(properties,future_properties);

    /*********************************************************/
    if( properties->format == DEMO_FUTURES )
    {
      if( futures_demo(properties,future_properties,1) == 0 )
      {
        continue;

      } else
      {
        break;
      }
    }
    /*********************************************************/
    if( properties->format == DEMO_OPTIONS )
    {
      if( options_demo(properties,1) == 0 )
      {
        continue;

      } else
      {
        break;
      }
    }

    int timercounter = 0;
                
    for(;;)
    {
      noecho();
      if( properties->realTimeBleeding == 1 )
      {
        nodelay(stdscr,TRUE);
      }

      char lastc = c;

      noecho();
      c = getch();
      echo();

      if( properties->realTimeBleeding == 1 )
      {
        nodelay(stdscr,FALSE);
      }

      echo();

      if( c == ERR )
      {
        timespec sleepValue = { 0 };
        sleepValue.tv_nsec = 50000000;
        if( nanosleep(&sleepValue, NULL) < 0 )
        {
          printw("nanosleep() failed\n");
          refresh();
        }

        if(++timercounter == (20 * properties->updatedelayseconds))
        {
          timercounter = 0;

          break;
        }

      }
      
      // Q for quit or ESC key
      if( c == 'q' || c == 'Q' || c == 27 )
      {
        break;
      }

      int newformat = c - '0';
      int bChange = 0;

      if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS )
      {
        switch(newformat)
        {
        case 1:
          properties->format = DECIMAL_GREEKS;
          properties->decimalorcalendar = DECIMALS;
          
          if( option_algorithms[properties->modeltype].perpetual == 0 )
          {
            decimal_date_message();
          }

          bChange = 1;
          break;

        case 2:
          properties->format = DECIMAL_OPTIONS;
          properties->decimalorcalendar = DECIMALS;

          if( option_algorithms[properties->modeltype].perpetual == 0 )
          {
            decimal_date_message();
          }

          bChange = 1;
          break;

        case 3:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

          } else
          {
            properties->format = CALENDAR_OPTIONS1;
            properties->decimalorcalendar = CALENDAR;
            
            calendar_date_message();

            bChange = 1;
          }

          break;

        case 4:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

          } else
          {
            properties->format = CALENDAR_OPTIONS2;
            properties->decimalorcalendar = CALENDAR;

            calendar_date_message();

            bChange = 1;
          }

          break;

        case 5:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

          } else
          {
            properties->format = CALENDAR_OPTIONS3;
            properties->decimalorcalendar = CALENDAR;

            calendar_date_message();

            bChange = 1;
          }

          break;

        case 6:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

          } else
          {
            properties->format = CALENDAR_OPTIONS4;
            properties->decimalorcalendar = CALENDAR;

            calendar_date_message();
                      
            bChange = 1;
          }

          break;

        case 7:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();
                        
          } else
          {
            properties->format = CALENDAR_OPTIONS5;
            properties->decimalorcalendar = CALENDAR;

            calendar_date_message();
                        
            bChange = 1;
          }

          break;

        case 8:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();
                        
          } else
          {
            properties->format = CALENDAR_CUSTOM;
            properties->decimalorcalendar = CALENDAR;

            properties->customstrike = properties->data.price;
            bChange = 1;

            move(4,0);
            printw("Use 'x', 'X' to adjust strikes");
            clrtoeol();
          }

          break;

        case 9:

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

          } else
          {
            properties->format = CALENDAR_OPTIONS6;
            properties->decimalorcalendar = CALENDAR;

            calendar_date_message();

            bChange = 1;
          }

          break;
        }
      } else if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
      {
        switch(newformat)
        {
          case 1:
            properties->format = DECIMAL_FUTURE;
            properties->decimalorcalendar = DECIMALS;

            if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS )
            {
              properties->modeltype = SetToFuture(properties);
            }

            decimal_date_message();

            bChange = 1;
            break;

        case 2:
          properties->format = CALENDAR_FUTURE;
          properties->decimalorcalendar = CALENDAR;

          if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS )
            properties->modeltype = SetToFuture(properties);

          calendar_date_message();

          bChange = 1;
          break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0:

          move(4,0);
          printw("Key not supported for Futures models");
          clrtoeol();
          refresh();
          
          break;

        }
      }

      if( properties->realTimeBleeding == 0 && bChange == 1 )
      {
        break;
      }

      /* toogle through the options cycle */
      if( c == 'o' || c == 'O' )
      {
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          move(4,0);
          printw("No options cycle with futures");
          clrtoeol();

          continue;
        }

        if( properties->decimalorcalendar == DECIMALS )
        {
          move(4,0);
          printw("Options cycle only allowed in calendar expirations mode");
          clrtoeol();

          continue;
        }

        /* All Months 0, Jan cycle 1, Feb cycle 2, Mar cycle 3 */

        if( ++properties->optionscycle > 4 )
        {
            properties->optionscycle = 0;
        }

        move(4,0);
        printw("Options Cycle=%s", optionscycle[properties->optionscycle]);
        clrtoeol();

        expires(LEG1,30,properties->skipmonth,properties);

        time(&properties->starttime);
        
        break;
      }

      if( c == '-' )
      {
        if( properties->mode != 1 )
        {
          --properties->mode;
        }

        move(4,0);

        if( properties->mode == 1 )
        {
          printw("Increment size smallest");
          clrtoeol();
                        
        } else if( properties->mode == 2 )
        {
          printw("Increment size medium");
          clrtoeol();
        }
        /* don't end this with a break */
      }
      if( c == '+' || c == '=' )
      {
        if( properties->mode != 3 )
        {
            ++properties->mode;
        }

        move(4,0);

        if( properties->mode == 2 )
        {
          printw("Increment size medium");
          clrtoeol();
                        
        } else if( properties->mode == 3 )
        {
          printw("Increment size large"); 
          clrtoeol();
        }
        /* don't end this with a break */
      }
      if( ( c == 'x' || c == KEY_DOWN ) && option_algorithms[properties->modeltype].supportStrikes )
      {
        /* futures don't use strikes */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          move(4,0);
          printw("No strikes for futures");
          clrtoeol();

          continue;
        }

        if( properties->format == DECIMAL_GREEKS || properties->format == CALENDAR_CUSTOM )
        {
          if( properties->mode == 1 )
          {
            if( (properties->customstrike - .01) > 0 )
            {
              properties->customstrike -= .01;
            }
          } else if( properties->mode == 2 )
          {
            if( (properties->customstrike-.1) > 0 )
            {
              properties->customstrike -= .1;
            }
          } else if( properties->mode == 3 )
          {   
            if( (properties->customstrike - 1) > 0 )
            {
              properties->customstrike -= 1;
            }
          }

          move(4,0);
          printw("Decreasing strike");
          clrtoeol();

          break;
        }
                    
        if( strike_control[properties->strikestoogle].strikes5or1 == 5 )
        {
          if( (properties->strike_offset!=(15-properties->data.price)) && ((properties->strike_offset+properties->data.price-15)>=strike_control[properties->strikestoogle].strikes5or1))

          {
            properties->strike_offset = properties->strike_offset - strike_control[properties->strikestoogle].xcontrol;
            move(4,0);
            printw("Decreasing strikes");
            clrtoeol();

          } else
          {
            move(4,0);
            printw("Can't decrease strikes");
            clrtoeol();

            continue;
          }
        } else if( strike_control[properties->strikestoogle].strikes5or1 == 1 )
        {
          if((properties->data.price+properties->strike_offset-strike_control[properties->strikestoogle].xcontrol)>=strike_control[properties->strikestoogle].xcontrol)
          {
            properties->strike_offset = properties->strike_offset - strike_control[properties->strikestoogle].xcontrol;

            move(4,0);
            printw("Decreasing strikes");
            clrtoeol();

          } else
          {
            move(4,0);
            printw("Can't decrease strikes"); 
            clrtoeol();

            continue;
          }
        } else
        {
          move(4,0);
          printw("Can't decrease strikes");
          clrtoeol();

          continue;
        }
                       
        break;
      }
      if( ( c == 'X' || c == KEY_UP ) && option_algorithms[properties->modeltype].supportStrikes )
      {
        /* futures don't use strikes */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          move(4,0);
          printw("No strikes for futures");
          clrtoeol();

          continue;
        }

        if( properties->format == DECIMAL_GREEKS || properties->format == CALENDAR_CUSTOM )
        {
          if(  properties->mode == 1 )
            properties->customstrike += .01;
          else if( properties->mode == 2 )
            properties->customstrike += .1;
          else if( properties->mode == 3 )
            properties->customstrike += 1;

          move(4,0);
          printw("Increasing strike");
          clrtoeol();
                        
          break;
        }
                    
        properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
                    
        move(4,0);
        printw("Increasing strikes");
        clrtoeol();

        break;
      }
      /***********************************************************/
                
      if( c == 'd' )
      {
        if( !option_algorithms[properties->modeltype].supportDividend )
        {
          move(4,0);
          printw("Dividends not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].supportDividend == 3 ||
            option_algorithms[properties->modeltype].supportDividend == 4 )
        {
          move(4,0);
          printw("Mutliple dividend values at multiple times not supported in curses");
          clrtoeol();

          continue;
        }
               
        if( properties->mode == 3 )
        {
          properties->data.dividend += -.01;
        }
        if( properties->mode == 2 )
        {
          properties->data.dividend += -.001;
        }
        if( properties->mode == 1 )
        {
          properties->data.dividend += -.0001;
        }
        move(4,0);
        printw("Decreasing dividend %.*f", properties->precision, properties->data.dividend);
        clrtoeol();

        break;
      }
      if( c == 'D' )
      {
        if( !option_algorithms[properties->modeltype].supportDividend )
        {
          move(4,0);
          printw("Dividends not supported in this model");
          clrtoeol();
          continue;
        }

        if( option_algorithms[properties->modeltype].supportDividend == 3 ||
            option_algorithms[properties->modeltype].supportDividend == 4 )
        {
          move(4,0);
          printw("Mutliple dividend values at multiple times not supported in curses");
          clrtoeol();

          continue;
        }
                   
        if( properties->mode == 1 )
        {
          properties->data.dividend = properties->data.dividend + .0001;

        }
        else if( properties->mode == 2 )
        {
          properties->data.dividend = properties->data.dividend + .001;
        }
        else if( properties->mode == 3 )
        {
          properties->data.dividend = properties->data.dividend +.01;
        }
        move(4,0);
        printw("Increasing dividend %.*f", properties->precision, properties->data.dividend);
        clrtoeol();

        break;
      }                
                
      /***********************************************************/
                
      if( c == 's' && option_algorithms[properties->modeltype].supportPrice )
      {
        if( properties->mode == 3 )
        {
          if( (properties->data.price - 10) <= 0 )
          {
            properties->mode = 2;
                            
            move(4,0);
            printw("Increment size medium");
            clrtoeol();

          } else
          {
            properties->strike_offset = properties->strike_offset + 10;
            properties->data.price = properties->data.price - 10;
            move(4,0);

            /* if its a future */
            if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
            {
              printw("Decreasing spot price %.3f", properties->data.price);
              clrtoeol();
         
            } else
            {
              printw("Decreasing stock price %.3f", properties->data.price);
              clrtoeol();
            }

            break;
          }

        }
        if( properties->mode == 2 )
        {
          if( (properties->data.price - 1) <= 0 )
          {
            properties->mode = 1;

            move(4,0);
            printw("Increment size smallest");
            clrtoeol();
                            
          } else
          {
            properties->strike_offset = properties->strike_offset + 1;
            properties->data.price = properties->data.price - 1;
            move(4,0);

            /* if its a future */
            if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
            {
              printw("Decreasing spot price %.3f", properties->data.price);
              clrtoeol();

            } else
            {
              printw("Decreasing stock price %.3f", properties->data.price);
              clrtoeol();
            }

            break;
          }
        }
        if( properties->mode == 1 )
        {
          if( (properties->data.price - .125) <= 0 )
          {
            move(4,0);

            /* if its a future */
            if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
            {
              printw("Can't decrease spot price");
              clrtoeol();

            } else
            {
              printw("Can't decrease stock price");
              clrtoeol();
            }
            
          } else
          {
            properties->data.price = properties->data.price - .125;
            move(4,0);

            /* if its a future */
            if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
            {
              printw("Decreasing spot price %.3f", properties->data.price);
              clrtoeol();

            } else
            {
              printw("Decreasing stock price %.3f", properties->data.price);
              clrtoeol();
            }

            break;
          }
        }
      }
      if( c == 'S' && option_algorithms[properties->modeltype].supportPrice )
      {
        if( properties->mode == 1 )
        {
            properties->data.price = properties->data.price + .125;
        }
        else if( properties->mode == 2 )
        {
          properties->data.price = properties->data.price + 1;
          properties->strike_offset = properties->strike_offset - 1;
        }
        else if( properties->mode == 3 )
        {
          properties->data.price = properties->data.price + 10;
          properties->strike_offset = properties->strike_offset - 10;
        }
        move(4,0);

        /* if its a future */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          printw("Increasing spot price %.3f", properties->data.price);
          clrtoeol();

        } else
        {
          printw("Increasing stock price %.3f", properties->data.price);
          clrtoeol();
        }

        break;
      }                
      if( c == 'r' && option_algorithms[properties->modeltype].supportRate )
      {
        if( properties->mode == 1 )
          properties->data.rate = properties->data.rate - .0001;
        else if( properties->mode == 2 )
          properties->data.rate = properties->data.rate - .0010;
        else if( properties->mode == 3 )
          properties->data.rate = properties->data.rate - .0100;

        move(4,0);
        printw("Decreasing interest rate %.4f", properties->data.rate);
        clrtoeol();
                    
        break;
      }
      if( c == 'R' && option_algorithms[properties->modeltype].supportRate )
      {
        if( properties->mode == 1 )
          properties->data.rate = properties->data.rate + .0001;
        else if( properties->mode == 2 )
          properties->data.rate = properties->data.rate + .0010;
        else if( properties->mode == 3 )
          properties->data.rate = properties->data.rate + .0100;

        move(4,0);
        printw("Increasing interest rate %.4f", properties->data.rate);
        clrtoeol();

        break;
      }
      if( c == 't' )
      {
        move(4,0); clrtoeol();

        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          printw("Time not supported for this model");
          break;
        }

        if( properties->decimalorcalendar == DECIMALS )
        {
          if( properties->mode == 3 )
          {
            /* minus 1 day */
            if( properties->data.t[0] - 0.002739726027397260273972602739726 > 0 )
            {
              properties->data.t[0] = properties->data.t[0] - 0.002739726027397260273972602739726;
            } else
            properties->mode = 2;
          }

          if( properties->mode == 2 )
          {   
            /* minus 1 hour */
            if( properties->data.t[0] - 0.00011415525114155251141552511415525 > 0 )
            {
              properties->data.t[0] = properties->data.t[0] - 0.00011415525114155251141552511415525;
            } else
              properties->mode = 1;
          }

          if( properties->mode == 1 )
          {
            /* one minute */
            if( properties->data.t[0] - 0.0000019025875190258751902587519025875 > 0 )
            {
              properties->data.t[0] = properties->data.t[0] - 0.0000019025875190258751902587519025875;
            } else
            {
              printw("Can't decrease expiration time");
              clrtoeol();
                                
              continue;
            }
          }

          move(4,0);
          printw("Decreasing expiration time");
          clrtoeol();
        }
                        
        if( properties->decimalorcalendar == CALENDAR )
        {
          properties->day_offset = properties->day_offset+((double)1/(double)365);
          printw("Day offset is %d days", --properties->day_offset_counter);
          clrtoeol();
        }
        break;
      }
      if( c == 'T' )
      {
        move(4,0);

        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          printw("Time not supported for this model");
          break;
        }

        if( properties->decimalorcalendar == DECIMALS )
        {
          if( properties->mode == 3 )
          {
            /* add 1 day */
            properties->data.t[0] = properties->data.t[0] + 0.002739726027397260273972602739726;
          }

          if( properties->mode == 2 )
          {
            /* add 1 hour */
            properties->data.t[0] = properties->data.t[0] + 0.00011415525114155251141552511415525;
          }

          if( properties->mode == 1 )
          {
            /* add 1 minute */
            properties->data.t[0] = properties->data.t[0] + 0.0000019025875190258751902587519025875;
          }
                        
          printw("Increasing expiration time");
          clrtoeol();
        }
                    
        if( properties->decimalorcalendar == CALENDAR )
        {
          properties->day_offset = properties->day_offset-((double) 1/ (double) 365);
          printw("Day offset is %d days", ++properties->day_offset_counter);
          clrtoeol();
        }
        
        break;
      }
      /********************************************************************************/
      if( c == 'e' )
      {
        
        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          continue;
        }

        move(4,0);

        if( option_algorithms[properties->modeltype].supportTime2 == 0 )
        {
          printw("Change to model that supports two dates");
          clrtoeol();

          break;
        }

        if( properties->mode == 3 )
        {
          /* minus 1 day */
          if( properties->data.t[1] - 0.002739726027397260273972602739726 > 0 )
          {
            properties->data.t[1] = properties->data.t[1] - 0.002739726027397260273972602739726;
          } /*else
              properties->mode = 2;*/
        }

        if( properties->mode == 2 )
        {   
          /* minus 1 hour */
          if( properties->data.t[1] -0.00011415525114155251141552511415525 > 0 )
          {
            properties->data.t[1] = properties->data.t[1] - 0.00011415525114155251141552511415525;
          } /*else
              properties->mode = 1;*/
        }

        if( properties->mode == 1 )
        {
          /* one minute */
          if(properties->data.t[1] - 0.0000019025875190258751902587519025875 > 0 )
          {
            properties->data.t[1] = properties->data.t[1] - 0.0000019025875190258751902587519025875;
            
          } else
          {
            printw("Can't decrease %s date", option_algorithms[properties->modeltype].supportTime2des);
            clrtoeol();
                                
            continue;
          }
        }

        move(4,0);
        printw("Decreasing %s date", option_algorithms[properties->modeltype].supportTime2des);
        clrtoeol();

        break;
      }

      if( c == 'E' )
      {

        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          continue;
        }

        move(4,0);

        if( option_algorithms[properties->modeltype].supportTime2 == 0 )
        {
          printw("Change to model that supports two dates");
          clrtoeol();

          break;
        }

        if( properties->mode == 3 )
        {
          /* add 1 day */
          properties->data.t[1] = properties->data.t[1] + 0.002739726027397260273972602739726;
        }

        if( properties->mode == 2 )
        {
          /* add 1 hour */
          properties->data.t[1] = properties->data.t[1] + 0.00011415525114155251141552511415525;
        }

        if( properties->mode == 1 )
        {
          /* add 1 minute */
          properties->data.t[1] = properties->data.t[1] + 0.0000019025875190258751902587519025875;
        }

        printw("Increasing %s date", option_algorithms[properties->modeltype].supportTime2des);
        clrtoeol();
                    
        break;
      }
      if( c == 'v' )
      {
        if( option_algorithms[properties->modeltype].supportVolatility == 0 )
        {
          continue;
        }

        if( properties->mode == 3 )
        {
          if( (properties->data.volatility-.1) > 0 )
          {
            properties->data.volatility = properties->data.volatility -.1;
            move(4,0);
            
            printw("Decreasing standard deviation %.3f", properties->data.volatility);
            clrtoeol();

            break;
            
          } else
          {
            properties->mode = 2;
                            
            move(4,0);
            printw("Increment size medium");
            clrtoeol();
          }
        }
        if( properties->mode == 2 )
        {
          if( (properties->data.volatility - .01 ) > 0 )
          {
            properties->data.volatility = properties->data.volatility - .01;
            move(4,0);

            printw("Decreasing %s %.3f", option_algorithms[properties->modeltype].volatility,properties->data.volatility);
            clrtoeol();

            break;
          } else
          {
            properties->mode = 1;
            
            move(4,0);
            printw("Increment size small");
            clrtoeol();
          }
                            
        }
        if( properties->mode == 1 )
        {
          /*if( (d-.001)>0) does't seem to avoid zero */
          if( properties->data.volatility > 0.002 )                            
          {
            properties->data.volatility = properties->data.volatility - .001;
            move(4,0);

            printw("Decreasing %s %.3f", option_algorithms[properties->modeltype].volatility,properties->data.volatility);
            clrtoeol();

            break;

          } else {

            move(4,0);

            printw("Can't decrease %s %.3f", option_algorithms[properties->modeltype].volatility,properties->data.volatility);
            clrtoeol();

            continue;
          }
        }
      }
      if( c == 'V' )
      {
          if( option_algorithms[properties->modeltype].supportVolatility == 0 )
          {
            continue;
          }

          if( properties->mode == 1 )
            properties->data.volatility = properties->data.volatility +.001;
          else if( properties->mode == 2 )
            properties->data.volatility = properties->data.volatility +.01;
          else if( properties->mode == 3 )
            properties->data.volatility = properties->data.volatility +.1;

          move(4,0);

          printw("Increasing %s %.3f", option_algorithms[properties->modeltype].volatility,properties->data.volatility);

          clrtoeol();

          break;
      }

      if( c == 'y' )
      {
        /* futures don't use variance */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        if(option_algorithms[properties->modeltype].supportCND != 1 )
        {
          continue;
        }
                    
        if( properties->mode == 3 )
        {
          if( (properties->distribution_variance - .1 ) > 0 )
          {
            properties->distribution_variance = properties->distribution_variance -.1;

            move(4,0);
            printw("Decreasing distribution variance %.3f", properties->distribution_variance);
            clrtoeol();

            break;

          } else
          {
            properties->mode = 2;
                            
            move(5,50);
            printw("Increment size medium");
            clrtoeol();
          }
        }
        if( properties->mode == 2 )
        {
          if( (properties->distribution_variance - .01 ) > 0 )
          {
            properties->distribution_variance = properties->distribution_variance - .01;
            
            move(4,0);
            printw("Decreasing distribution variance %.3f", properties->distribution_variance);
            clrtoeol();
            
            break;

          } else
          {
            properties->mode = 1;

            move(5,50);
            printw("Increment size small");
            clrtoeol();
          }
          
        }
        if( properties->mode == 1 )
        {
          if( ( properties->distribution_variance - .001 ) > 0 )
          {
            properties->distribution_variance = properties->distribution_variance - .001;

            move(4,0);
            printw("Decreasing distribution variance %.3f", properties->distribution_variance);
            clrtoeol();

            break;

          } else {
            move(5,0);
            printw("Can't decrease distribution variance");
            clrtoeol();                      

            continue;
          }
        }

        break;
      }
      if( c == 'Y' )
      {
        /* futures don't use variance */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        if(option_algorithms[properties->modeltype].supportCND != 1 )
        {
          continue;
        }
                    
        if( properties->mode == 1 )
          properties->distribution_variance = properties->distribution_variance + .001;
        else if( properties->mode == 2 )
          properties->distribution_variance = properties->distribution_variance + .01;
        else if( properties->mode == 3 )
          properties->distribution_variance = properties->distribution_variance + .1;
        move(4,0);
        printw("Increasing distribution variance %.3f", properties->distribution_variance);
        clrtoeol();

        break;

      }
      if( c == 'G' )
      {
        /* futures don't use numerical integration */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        /* if not integratable it must use steps */
        if( option_algorithms[properties->modeltype].supportSteps == 1 )
        {
          option_algorithms[properties->modeltype].steps++;

          move(4,0);
          printw("Increasing steps %.d", option_algorithms[properties->modeltype].steps);
          clrtoeol();

          break;
        }

        if( integration_method[properties->integration_type].method != 0 )
        {
          if(integration_method[properties->integration_type].UpperLimit)
          {
            if( integration_method[properties->integration_type].resolution < integration_method[properties->integration_type].UpperLimit )
              {

                integration_method[properties->integration_type].resolution += 1;
                integration_method[properties->integration_type].resolution += integration_method[properties->integration_type].allowOnlyEven;
                
                move(4,0);
                printw("Increasing %s method resolution %.d",integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
                clrtoeol();

              } else
              {
                move(4,0);
                printw("%s method resolution maxed out: %.d",integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
                clrtoeol();
              }
          } else
          {
            integration_method[properties->integration_type].resolution += 1;
            integration_method[properties->integration_type].resolution += integration_method[properties->integration_type].allowOnlyEven;

            move(4,0);
            printw("Increasing %s method resolution %.d", integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
            clrtoeol();
          }
        }
        break;
      }
      if( c == 'g' )
      {
        /* futures don't use numerical integration */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        /* if not integratable it must use steps */
        if( option_algorithms[properties->modeltype].supportSteps == 1 )
        {
          if( option_algorithms[properties->modeltype].steps > 1 )
            option_algorithms[properties->modeltype].steps--;

          move(4,0);
          printw("Decreasing steps %.d", option_algorithms[properties->modeltype].steps);
          clrtoeol();

          break;
        }
        ///////////////////////////////////////////////////////////////////

        if( integration_method[properties->integration_type].method != 0 )
        {
          if( (integration_method[properties->integration_type].resolution - 1 - integration_method[properties->integration_type].allowOnlyEven) > 0 )
          {
            integration_method[properties->integration_type].resolution -= 1;
            integration_method[properties->integration_type].resolution -= integration_method[properties->integration_type].allowOnlyEven;

            move(4,0);
            printw("Decreasing %s method resolution %.d",integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
            clrtoeol();

          } else
          {
            move(4,0);
            printw("Can't decrease %s method resolution %.d",integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
            clrtoeol();

            continue;

          }
        }

        break;
      }
      if( c == 'u' )
      {
        /* futures don't use mean */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        if( option_algorithms[properties->modeltype].supportCND != 1 )
        {
          continue;
        }
                    
        if( properties->mode == 1 )
          properties->distribution_mean = properties->distribution_mean - .001;
        else if(properties->mode == 2)
          properties->distribution_mean = properties->distribution_mean - .01;
        else if(properties->mode == 3)
          properties->distribution_mean = properties->distribution_mean - .1;

        move(4,0);
        printw("Decreasing distribution mean %.3f", properties->distribution_mean);
        clrtoeol();

        break;
      }

      if( c == 'U' )
      {
        /* futures don't use mean */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        if( option_algorithms[properties->modeltype].supportCND != 1 )
        {
          continue;
        }
                    
        if( properties->mode == 1 )
          properties->distribution_mean = properties->distribution_mean +.001;
        else if( properties->mode == 2 )
          properties->distribution_mean = properties->distribution_mean + .01;
        else if( properties->mode == 3 )
          properties->distribution_mean = properties->distribution_mean + .1;

        move(4,0);
        printw("Increasing distribution mean %.3f",properties->distribution_mean);
        clrtoeol();
                    
        break;

      }

      if( c == 'h' || c == 'H' || c == '?' )
      {
        move(properties->start-2,0);
                    
        simple_help(properties);

        move(properties->start,0);
        clear();

        break;
      }
      if( c == 'a' || c == 'A' )
      {
        int ret = 0;
                    
        ret = props(properties,future_properties);

        /* if the user changed a date properties, re-run expires() */
        if( ret == 1 )
        {
          expires(LEG1,30,properties->skipmonth,properties);

          expires(LEG1,30,properties->skipmonth,future_properties);
          
        }
        clear();
                    
        break;
      }

      if( c == 'C' ) // capital 'C'
      {
        /* futures calendar properties->mode */
        calendar(future_properties);
        break;
      }

      if( c == 'c' ) // little 'c'
      {
        /* options calendar properties->mode */
        calendar(properties);
        break;
      }

      if( c == 'W' || c == KEY_RIGHT )
      {
        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          move(4,0);
          printw("Time not supported for this model");
          break;
        }

        /* these formats don't use months, they are decimal dates */
        if( properties->decimalorcalendar == DECIMALS )
        {
          move(4,0);
          printw("Change to Calendar Mode to walk months forward");
          clrtoeol();

          continue;
        }

        properties->skipmonth++;

        move(4,0);
        if( properties->optionscycle == 4 )
        {
          printw("Skip year forward %d", properties->skipmonth);
          clrtoeol();
        }
        else
        {
          printw("Skip month forward %d", properties->skipmonth);
          clrtoeol();
        }

        /* if calendar futures */
        if( properties->format == CALENDAR_FUTURE )
        {
          expires(LEG1,30,properties->skipmonth,future_properties);

        } else
        {
          expires(LEG1,30,properties->skipmonth,properties);
        }

        break;
      }
                
      if( c == 'w' || c == KEY_LEFT )
      {
        if( option_algorithms[properties->modeltype].perpetual == 1 )
        {
          move(4,0);
          printw("Time not supported for this model");
          break;
        }

        /* these formats don't use months, they are decimal dates */
        if( properties->decimalorcalendar == DECIMALS )
        {
          move(4,0);
          printw("Change to Calendar Mode to walk months backward");
          clrtoeol();

          continue;
        }

        if( properties->skipmonth > 0 )
        {
          properties->skipmonth--;

          move(4,0);
          if( properties->optionscycle == 4 )
          {
            printw("Skip year backward %d", properties->skipmonth);
            clrtoeol();
          }
          else
          {
            printw("Skip month backward %d", properties->skipmonth);
            clrtoeol();
          }

          /* if calendar futures */
          if( properties->format == CALENDAR_FUTURE )
          {
            expires(LEG1,30,properties->skipmonth,future_properties);

          } else
          {
            expires(LEG1,30,properties->skipmonth,properties);
          }

          break;

        } else
        {
          move(4,0);
          printw("Press capital 'W' for forward");
          clrtoeol();
        }

      }
      /* control-l to clear screen then redraw the screen */
      if( c == '' )
      {
        clear();
        break;
      }
      /* control-r to call refresh() to force paint */
      if( c == '' )
      {
        refresh();
        break;
      }
      /* space to refresh the time and redraw the screen */
      if( c == ' ' )
      {
        break;
      }
                
      if( c == 'f')
      {
        if( (properties->precision-1) >= 0 )
        {
          properties->precision--;
          move(4,0);
          printw("Decreasing floating point precision %d", properties->precision);
          clrtoeol();
                        
        } else
        {
          move(4,0);
          printw("Can't decrease floating point properties");
          clrtoeol();
          continue;
        }

        break;
      }

      if( c == 'F' )
      {
        move(4,0);

        /* DBL_DIG is defined in float.h */
        if( properties->precision >= DBL_DIG )
        {
          printw("Floating point precision maxed out: %d", properties->precision);
          clrtoeol();

        } else
        {
          properties->precision++;
          printw("Increasing floating point precision %d", properties->precision);
          clrtoeol();
        }

        break;
      }

      if( c == 'M')
      {
        if( --properties->modeltype < 0 )
        {
          properties->modeltype = (sizeofoption_algorithms/(signed)sizeof(struct option_algorithm)-1);
        }

        if( option_algorithms[properties->modeltype].supportDividend == 2 )
        {
          properties->data.dividend = option_algorithms[properties->modeltype].defaultDividend;
        }

        // just some defaults so the model doesnt NaN out
        // on its pricing...
        properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
        properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
        properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
        properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
        properties->data.UseQ = option_algorithms[properties->modeltype].Qdefault;
        properties->data.UseR = option_algorithms[properties->modeltype].Rdefault;
        properties->data.UseS = option_algorithms[properties->modeltype].Sdefault;
        properties->data.UseT = option_algorithms[properties->modeltype].Tdefault;
        properties->data.UsePound = option_algorithms[properties->modeltype].Pounddefault;
        properties->data.steps = option_algorithms[properties->modeltype].steps;

        break;
      }

      if( c == 'm' )
      {
        if(++properties->modeltype >= (sizeofoption_algorithms/(signed)sizeof(struct option_algorithm)))
        {
          properties->modeltype = 0;
        }

        if( option_algorithms[properties->modeltype].supportDividend == 2 )
        {
          properties->data.dividend = option_algorithms[properties->modeltype].defaultDividend;
        }

        // just some defaults so the model doesnt NaN out
        // on its pricing...
        properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
        properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
        properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
        properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
        properties->data.UseQ = option_algorithms[properties->modeltype].Qdefault;
        properties->data.UseR = option_algorithms[properties->modeltype].Rdefault;
        properties->data.UseS = option_algorithms[properties->modeltype].Sdefault;
        properties->data.UseT = option_algorithms[properties->modeltype].Tdefault;
        properties->data.UsePound = option_algorithms[properties->modeltype].Pounddefault;
        properties->data.steps = option_algorithms[properties->modeltype].steps;

        break;
      }

      /* change numerical integration type */
      if( c == 'i' || c == 'I' )
      {
        /* some options algo don't use my integration */
        if( option_algorithms[properties->modeltype].supportCND == 0 )
        {
          move(4,0);
          printw("Not supported for this model");
          clrtoeol();

          continue;
        }

        const int num_integration = sizeofintegration_method/sizeof(struct numerical_integration_method);

        if( ++properties->integration_type == num_integration )
        {
          properties->integration_type = 0;
        }

        /***************************************************************/

        if( integration_method[properties->integration_type].method == 0 )
        {
          move(4,0);
          printw("%s", integration_method[properties->integration_type].des);
          clrtoeol();
          
          refresh();

        } else
        {
          move(4,0);
          printw("%s resolution: %d", integration_method[properties->integration_type].des,integration_method[properties->integration_type].resolution);
          clrtoeol();
          refresh();
          
        }

        if( integration_method[properties->integration_type].method == 0 )
        {
          /* polynomial approximation doesn't allow for
             changes in mean or variance, you must use
             romberg's or simpson's rule */
          if( properties->distribution_mean != 0 && properties->distribution_variance != 1 )
          {
            properties->distribution_mean = 0;
            properties->distribution_variance = 1;

            move(4,0);
            printw("distribution mean forced to: 0 & ");
            printw("distribution variance forced to 1");
            clrtoeol();

            refresh();

          } 
          if( properties->distribution_mean != 0 )
          {
            properties->distribution_mean = 0;

            move(4,0);
            printw("distribution mean forced to: 0");
            clrtoeol();
            refresh();
          }
          if( properties->distribution_variance != 1 )
          {
            properties->distribution_variance = 1;

            move(4,0);
            printw("distribution variance forced to: 1");
            clrtoeol();
            refresh();
          }
          if( properties->distribution_type != NORMAL_DISTRIBUTION )
          {
            properties->distribution_type = NORMAL_DISTRIBUTION;

            move(4,0);
            printw("Normal Distribution");
            clrtoeol();
          }
        }

        break;
      }
                
      if( c == 'k' || c == 'K' )
      {
        /* futures have no strikes */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          move(4,0);
          printw("Futures have no strike increment adjustments");
          clrtoeol();
          continue;
        }

        if(++properties->strikestoogle >= (sizeofstrike_control/(signed)(sizeof(struct _strike_control)))-1)
         {
           properties->strikestoogle = 0;
         }

        properties->strike_offset = (int) properties->strike_offset;

        break;
      }

      if( c == 'n' || c == 'N' )
      {
        /* futures have no distribution */
        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          continue;
        }

        const int numberofdistributions = sizeofdistribution_list/sizeof(distribution_list[0]);
        properties->distribution_type++;

        if( properties->distribution_type != NORMAL_DISTRIBUTION )
        {
          if( integration_method[properties->integration_type].method == 0 )
          {
            //properties->integration_type=ROMBERGS_METHOD;
            properties->integration_type = SIMPSONS_RULE;
          }
        }

        if( properties->distribution_type >= numberofdistributions )
        {
          properties->distribution_type = 0;
        }
        
        break;
      }

      if( c == '@' )
      {
        if( properties->realTimeBleeding == 1 )
        {
          properties->realTimeBleeding = 0;

          move(4,0);
          printw("Realtime updating disabled");
          clrtoeol();

          //properties->data.te  = 0;
          //properties->data.te2 = 0;

          properties->data.t[0] = properties->data.t[0] - properties->data.te;
          properties->data.t[1] = properties->data.t[1] - properties->data.te2;

        }
        else 
        {
          properties->realTimeBleeding = 1;

          move(4,0);
          printw("Realtime updating enabled");
          clrtoeol();

          time(&properties->starttime);
          time(&properties->starttime2);

        }

        break;
      }

      if( c == '$' )
      {
        if( properties->highlightInTheMoney )
        {
          properties->highlightInTheMoney = 0;
                    
        } else
        {
          properties->highlightInTheMoney = 1;
        }

      }
      if( c == '\t' )
      {

        if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
          break;

        properties->customstrike = properties->data.price;
        ++properties->format;

        if( properties->format == FUTURES_FORMAT_END )
        {
          properties->format = DECIMAL_FUTURE;
        }

        if( properties->format == OPTIONS_FORMAT_END )
        {
          properties->format = DECIMAL_GREEKS;
        }

        switch( properties->format )
        {
        case DECIMAL_GREEKS:

          properties->decimalorcalendar = DECIMALS;

          if( option_algorithms[properties->modeltype].perpetual == 0 )
          {
            decimal_date_message();
          }

          break;

        case DECIMAL_OPTIONS:

          properties->decimalorcalendar = DECIMALS;

          if( option_algorithms[properties->modeltype].perpetual == 0 )
          {
            decimal_date_message();
          }

          break;

        case CALENDAR_OPTIONS1:
        case CALENDAR_OPTIONS2:
        case CALENDAR_OPTIONS3:
        case CALENDAR_OPTIONS4:
        case CALENDAR_OPTIONS5:
        case CALENDAR_OPTIONS6:
        case CALENDAR_CUSTOM: 

          if( option_algorithms[properties->modeltype].supportTime2 == 1 )
          {
            properties->format = DECIMAL_GREEKS;
            properties->decimalorcalendar = DECIMALS;

            if( option_algorithms[properties->modeltype].perpetual == 0 )
            {
              decimal_date_message();
            }

          } else
          {
            properties->decimalorcalendar=CALENDAR;
            calendar_date_message();
          }

          break;

        case DECIMAL_FUTURE:

          if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS )
          {
            properties->modeltype = SetToFuture(properties);
          }

          properties->decimalorcalendar = DECIMALS;

          decimal_date_message();

          break;

        case CALENDAR_FUTURE:

          properties->optionscycle = 0;

          if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS )
          {
            properties->modeltype = SetToFuture(properties);
          }

          properties->decimalorcalendar = CALENDAR;

          calendar_date_message();

          break;

        default:
                                    
          fprintf(stderr,"Error3: No format implementation for case %d\n", properties->format);

          break;

        }

        break;

      }

      if( c == 'z' )
      {
        if( !option_algorithms[properties->modeltype].iUseZ )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();
          continue;
        }
        if( option_algorithms[properties->modeltype].iUseZ == 2 )
          properties->data.UseZ = properties->data.UseZ - 1;
        else if( properties->mode == 1 )
          properties->data.UseZ = properties->data.UseZ - .01;
        else if( properties->mode == 2 )
          properties->data.UseZ=properties->data.UseZ - .1;
        else if( properties->mode == 3 )
          properties->data.UseZ = properties->data.UseZ - 1;

        if( option_algorithms[properties->modeltype].bZallow0Negative != 1 && properties->data.UseZ <= 0 )
        {
          move(4,0);

          printw("Can't decrease %s", option_algorithms[properties->modeltype].UseZdes);
          clrtoeol();

          properties->data.UseZ = 0;
          break;
        }

        move(4,0);
        printw("Decreasing %s %.2f", option_algorithms[properties->modeltype].UseZdes,properties->data.UseZ);
        clrtoeol();
        break;

      }
      if( c == 'Z' )
      {
        if( !option_algorithms[properties->modeltype].iUseZ )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].iUseZ == 2 )
          properties->data.UseZ = properties->data.UseZ + 1;
        else if( properties->mode == 1 )
          properties->data.UseZ = properties->data.UseZ + .01;
        else if( properties->mode == 2 )
          properties->data.UseZ = properties->data.UseZ + .1;
        else if( properties->mode == 3 )
          properties->data.UseZ = properties->data.UseZ + 1;

        move(4,0);
        printw("Increasing %s %.2f", option_algorithms[properties->modeltype].UseZdes,properties->data.UseZ);
        clrtoeol();

        break;

      }
      if( c == 'b' )
      {
        if( !option_algorithms[properties->modeltype].iUseB )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].iUseB == 2 )
          properties->data.UseB = properties->data.UseB - 1;
        else if( properties->mode == 1 )
          properties->data.UseB = properties->data.UseB -.01;
        else if( properties->mode == 2 )
          properties->data.UseB = properties->data.UseB -.1;
        else if( properties->mode == 3 )
          properties->data.UseB = properties->data.UseB -1;
        
        if( option_algorithms[properties->modeltype].bBallow0Negative != 1 && properties->data.UseB <= 0 )
        {
          move(4,0);

          printw("Can't decrease %s", option_algorithms[properties->modeltype].UseBdes);
          clrtoeol();

          properties->data.UseB = 0;
          break;
        }

        move(4,0);
        printw("Decreasing %s %.2f", option_algorithms[properties->modeltype].UseBdes,properties->data.UseB);
        clrtoeol();
                  
        break;

      }
      if( c == 'B' )
      {
        if( !option_algorithms[properties->modeltype].iUseB )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].iUseB == 2 )
          properties->data.UseB = properties->data.UseB + 1;
        else if( properties->mode == 1)
          properties->data.UseB = properties->data.UseB + .01;
        else if( properties->mode == 2)
          properties->data.UseB = properties->data.UseB + .1;
        else if( properties->mode == 3)
          properties->data.UseB = properties->data.UseB + 1;

        move(4,0);
        printw("Increasing %s %.2f", option_algorithms[properties->modeltype].UseBdes,properties->data.UseB);
        clrtoeol();

        break;

      }
      if( c == 'j' )
      {
        if( !option_algorithms[properties->modeltype].iUseJ )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].iUseJ == 2 )
          properties->data.UseJ = properties->data.UseJ - 1;
        else if( properties->mode == 1 )
          properties->data.UseJ = properties->data.UseJ - .01;
        else if( properties->mode == 2 )
          properties->data.UseJ = properties->data.UseJ - .1;
        else if( properties->mode == 3 )
          properties->data.UseJ = properties->data.UseJ - 1;

        if(option_algorithms[properties->modeltype].bJallow0Negative != 1 && properties->data.UseJ <= 0)
        {
          move(4,0);

          printw("Can't decrease %s", option_algorithms[properties->modeltype].UseJdes);
          clrtoeol();

          properties->data.UseJ = 0;

          break;
        }

        move(4,0);
        printw("Decreasing %s %.2f", option_algorithms[properties->modeltype].UseJdes,properties->data.UseJ);
        clrtoeol();

        break;

      }
      if( c == 'J' )
      {
        if( !option_algorithms[properties->modeltype].iUseJ )
        {
            move(4,0);
            printw("Not supported in this model");
            clrtoeol();

            continue;
        }

        if( option_algorithms[properties->modeltype].iUseJ == 2 )
          properties->data.UseJ = properties->data.UseJ + 1;
        else if( properties->mode == 1 )
          properties->data.UseJ = properties->data.UseJ + .01;
        else if( properties->mode == 2 )
          properties->data.UseJ = properties->data.UseJ + .1;
        else if( properties->mode == 3 )
          properties->data.UseJ = properties->data.UseJ + 1;

        move(4,0); clrtoeol();
        printw("Increasing %s %.2f", option_algorithms[properties->modeltype].UseJdes,properties->data.UseJ);
        clrtoeol();

        break;

      }

      if( c == 'p' )
      {
        if( !option_algorithms[properties->modeltype].iUseP )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();

          continue;
        }

        if( option_algorithms[properties->modeltype].iUseP == 2 )
          properties->data.UseP = properties->data.UseP - 1;
        else if( properties->mode == 1 )
          properties->data.UseP = properties->data.UseP - .01;
        else if( properties->mode == 2 )
          properties->data.UseP = properties->data.UseP - .1;
        else if( properties->mode == 3 )
          properties->data.UseP = properties->data.UseP - 1;

        if( option_algorithms[properties->modeltype].bPallow0Negative != 1 && properties->data.UseP <= 0 )
        {
          move(4,0);

          printw("Can't decrease %s", option_algorithms[properties->modeltype].UsePdes);
          clrtoeol();

          properties->data.UseP = 0;
          break;
        }

        move(4,0); clrtoeol();
        printw("Decreasing %s %.2f", option_algorithms[properties->modeltype].UsePdes,properties->data.UseP);
        clrtoeol();

        break;

      }
      if( c == 'P' )
      {
        if( !option_algorithms[properties->modeltype].iUseP )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();
          continue;
        }

        if( option_algorithms[properties->modeltype].iUseP == 2 )
          properties->data.UseP = properties->data.UseP + 1;
        else if( properties->mode == 1 )
          properties->data.UseP = properties->data.UseP + .01;
        else if( properties->mode == 2 )
          properties->data.UseP = properties->data.UseP + .1;
        else if( properties->mode == 3 )
          properties->data.UseP = properties->data.UseP + 1;
         
        move(4,0);
        printw("Increasing %s %.2f", option_algorithms[properties->modeltype].UsePdes,properties->data.UseP);
        clrtoeol();

        break;

      }
      /******************************************************/
      if( c == '#' )
      {
        if( !option_algorithms[properties->modeltype].bUsePound )
        {
          move(4,0);
          printw("Not supported in this model");
          clrtoeol();
          continue;
        }

        properties->data.UsePound = properties->data.UsePound + 1;

        move(4,0);

        if( option_algorithms[properties->modeltype].bUseStateNames == 0 )
        {
          printw("%s = %d", option_algorithms[properties->modeltype].UsePounddes,(properties->data.UsePound > option_algorithms[properties->modeltype].Poundmax ? 1 : properties->data.UsePound));
          clrtoeol();

        } else
        {
          printw("%s = %s", option_algorithms[properties->modeltype].UsePounddes,(char *) &(option_algorithms[properties->modeltype].StateNames[(properties->data.UsePound-1 >= option_algorithms[properties->modeltype].Poundmax ? 0 : properties->data.UsePound-1)]));
          clrtoeol();
        }

        refresh();
        break;

      }
      /******************************************************/
      if( c == '!' )
      {
        if( select_model(properties) == 1 )
        {
          // user changed model in select_model() lets setup the defaults...
          properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
          properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
          properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
          properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
          properties->data.UsePound = option_algorithms[properties->modeltype].Pounddefault;
          properties->data.steps = option_algorithms[properties->modeltype].steps;
                    
          if( option_algorithms[properties->modeltype].supportDividend == 2 )
          {
            properties->data.dividend = option_algorithms[properties->modeltype].defaultDividend;
          }

        }
        clear();
      }

      if( c == 'l' || c == 'L' )
      {
        if( lastc == 'l' || lastc == 'L' )
        {
          lastc = 0;
          c = 0;

          break;
        }

        clear();

        move(0,0);
                    
        printw("\n\n\n\n\n%s\n\n\n\n\n\n\n\n\n",license);
        printw("\t\t\t");
        attron(A_STANDOUT);
        printw("<<< Press any key to return >>>"); clrtoeol();
        attroff(A_STANDOUT);

        noecho();
        getch();
        echo();

        clear();
        refresh();
      }
    } /* for(;;) */
  } /* for(;;)*/

} // void curses_process(struct _properties *properties,struct _properties *future_properties)
