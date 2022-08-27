/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_inputs.cpp of optionmatrix                                  */
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
#include "curses_include.h"

int nonblockscan(int *control)
{
  static char buf[128];
  static char *inputstring;
  static int iZeroOneTwo = 0; /* 0, 1, 2 */

  inputstring = &buf[0];

  int c = 0;
  int ret;

  nodelay(stdscr,TRUE);
  noecho();
  c = getch();
  echo();
  nodelay(stdscr,FALSE);
    
  if( isdigit(c) )
  {
    printw("%c",c);
    refresh();

    if( iZeroOneTwo == 3 )
    {
      iZeroOneTwo = 0;

      inputstring[0] = inputstring[1] = inputstring[2] = 0;
    }

    inputstring[iZeroOneTwo] = c;
    iZeroOneTwo++;
  }

  if( c == '\n' )
  {
    ret = 0;
    int retscan = sscanf(inputstring,"%d",&ret);

    if( retscan == 0 || retscan == -1 )
      ret = 0;

    inputstring[0] = inputstring[1] = inputstring[2] = 0;
    iZeroOneTwo = 0; /* 0, 1, 2 */

    return ret;
  }

  // reset input buffer on all action keys...
  if( c == KEY_RIGHT || c == KEY_LEFT || c == KEY_DOWN || c == KEY_UP || 
      c == '\t' || c == ' ' || c == 'j' || c == 'k' || c == 'h' || c == 'l' )
  {
    inputstring[0] = inputstring[1] = inputstring[2] = 0;

    iZeroOneTwo = 0; /* 0, 1, 2 */

    *control = c;

    return -1;
  }

  // User hit ESC key or Quit
  if( c == 27 || c == 'q' || c == 'Q' )
  {
    quit(0);
  }

  return -1;

} // int nonblockscan(int *control)

int select_model(struct _properties *properties)
{
  clear();

  /* curses stuff */
  int height,width;
   
  /* curses, get screen size */
  getmaxyx(stdscr, height, width);

  int row = 1;
  bool redraw = 0;
  int start = 0;
  int optiontype;
  bool modelChanged = 0;
 
  int type = -1;

  while( type == -1 )
  {
    row = 2;

    move(0,0);
    attron(A_STANDOUT);
    printw("Select financial model or press enter:");
    attroff(A_STANDOUT);
    printw(" %d\n",properties->modeltype+1);

    move(0,53);
    attron(A_BOLD);
    printw("Arrow Down For More Models");
    attroff(A_BOLD);
    refresh();

    int x = 1;
    for( x = 1; x <= (height-1); x++ )
    {
       move(x,0); clrtoeol();
    }

    const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
    
    for( optiontype=start; optiontype<((numberofmodels-start>((height-3)*3))?((height-3)*3)+start:numberofmodels); optiontype++ )
    {
      
      if( optiontype==((height-3)+start) || optiontype==((height-3)*2+start) )
        row = 2;

      if( optiontype<((height-3)+start) )
        move(row,0);

      if( optiontype>=((height-3)+start) && optiontype < ((height-3)*2+start) )
        move(row,23);

      if( optiontype>=((height-3)*2+start) )
        move(row,50);

      if( properties->modeltype == optiontype )
      {
        attron(A_STANDOUT);
        printw("--->");
        attroff(A_STANDOUT);

      } else
      {
        printw("    ");
      }

      printw("%d=%.20s\n",optiontype+1,option_algorithms[optiontype].des);
      row++;
    
    }

    refresh();

    for(;;)
    {
      row = 0;
      move(row,39);

      int control = 0;
      type = -1;

      while( type == -1 )
      {
        type = nonblockscan(&control);

        timespec sleepValue = { 0 };
        sleepValue.tv_nsec = 1000;
        if( nanosleep(&sleepValue, NULL) < 0 )
        {
          printw("nanosleep() failed\n");
          refresh();
        }

        if( control == KEY_LEFT || control == KEY_UP || control == 'k' ||
            control == 'h' )
        {
          if( --start < 0 )
          {
            start = 0;
          }

          redraw = 1;
          break;
        }

        if( control == KEY_RIGHT || control == KEY_DOWN || control == '\t' || 
            control == ' ' || control == 'j' || control == 'l' )
        {
          start++;
          redraw = 1;
          break;
        }
      }
      
      if( redraw == 1 )
      {
        redraw = 0;
        type = -1;
        break;
      }

      if( type >= 1 && type<(1+(signed)sizeofoption_algorithms/(signed)sizeof(struct option_algorithm)) )
      {
        move(row,39);
        printw("%d\n",type);
        properties->modeltype = type - 1;
            
        move(row++,0);

        attron(A_STANDOUT);
        printw("Select financial model or press enter:");
        attroff(A_STANDOUT);
        printw(" %d\n",properties->modeltype+1);

        row = 2;
                  
        const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));

        for( optiontype = start; optiontype<((numberofmodels-start>((height-3)*3))?((height-3)*3)+start:numberofmodels); optiontype++ )
        {
          if( optiontype==((height-3)+start) || optiontype==((height-3)*2+start) )
            row = 2;

          if( optiontype<((height-3)+start) )
            move(row,0);
                  
          if( optiontype>=((height-3)+start) && optiontype < ((height-3)*2+start) )
            move(row,23);

          if( optiontype>=((height-3)*2+start) )
            move(row,50);

          if( properties->modeltype == optiontype )
          {
            attron(A_STANDOUT);
            printw("--->");
            attroff(A_STANDOUT);
          } else
          {
            printw("    ");
          }

          printw("%d=%.20s\n",optiontype+1,option_algorithms[optiontype].des);

          row++;
        }

        refresh();

        timespec sleepValue = { 0 };
        sleepValue.tv_nsec = 500000000;
        if( nanosleep(&sleepValue, NULL) < 0 )
        {
          printw("nanosleep() failed\n");
          refresh();
        }

        modelChanged = 1;

        break;
            
      } else if( type == 0 || type == -1 )
      {
        /* the user just entered a <ENTER>
           so just use previous value no change */
        break;
      }
    }
  }

  return modelChanged;

} // int select_model(struct _properties *properties)

int get_user_inputs(struct _properties *properties,struct _properties *future_properties)
{
        int ret = 0;
        int c;
        char inputstring[100]  = { 0 };
        int row = 1;

        properties->data.price = 100;
        properties->data.UseZ = 0;
        properties->data.UseB = 0;
        properties->data.UseJ = 0;
        properties->data.UseP = 0;
        properties->data.UseQ = 0;
        properties->data.UseR = 0;
        properties->data.UseS = 0;
        properties->data.UseT = 0;
        properties->data.UsePound = 0;
        properties->data.t[0] = 1.0;
        properties->data.t[1] = 0.25;
        properties->data.t[2] = 0.25;

        time_t mytime;
        struct tm *my_tm;

        time(&mytime);
        my_tm=localtime(&mytime);

        select_model(properties);

        row = -1;
        clear();

        for(;;)
        {
          clear();

          printw("Model = ");
          attron(A_STANDOUT);
          printw("%s",option_algorithms[properties->modeltype].des);
          attroff(A_STANDOUT);
          printw("  Source = %s\n\n",option_algorithms[properties->modeltype].source);

          if( strcmp(option_algorithms[properties->modeltype].curses_des,"") != 0 )
          {
            printw("%s\n\n",option_algorithms[properties->modeltype].curses_des);
          }
           
          if( option_algorithms[properties->modeltype].assetClass != BOND_CLASS &&
              option_algorithms[properties->modeltype].assetClass != TERMSTRUCTURE_CLASS )
          {
            attron(A_STANDOUT);
            printw("Select a screen/date style format:\n");
            attroff(A_STANDOUT);
          }

          if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
          {
            printw("\t\t\t");
            attron(A_STANDOUT);
            printw("Press <ENTER> to begin.\n");
            attroff(A_STANDOUT);
          }

          if( option_algorithms[properties->modeltype].assetClass == OPTION_CLASS )
          {
            printw("1 - Custom stike, greeks, tickers            (decimal/date entry dated)\n");
            printw("2 - Matrix strikes, tickers                  (decimal/date entry dated)\n");
          }

          if( option_algorithms[properties->modeltype].assetClass == OPTION_CLASS && option_algorithms[properties->modeltype].supportTime2 != 1 )
          {
            printw("3 - Strike to months matrix                  (calendar dated)\n");
            printw("4 - Strike to months matrix w/ days to expr  (calendar dated)\n");
            printw("5 - Strikes to month matrix                  (calendar dated)\n");
            printw("6 - Strikes to month matrix w/ days to expr  (calendar dated)\n");            
            printw("7 - Months across column style               (calendar dated)\n");
            printw("8 - Custom strike matrix                     (calendar dated)\n");
            printw("9 - Three Column style                       (calendar dated)\n");
          }

          if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
          {
            printw("1 - Single future                  (decimal/date entry dated)\n");
            printw("2 - Calendar dated futures matrix  (calendar dated)\n");
            printw("\n");
          }

          if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
          {
            printw("Use arrow keys to change to another model or type ESC.\n\n");
          }

          printw("\n");        
          printw("Or select:\n");        
          printw("a - AdvProperties (use to adjust calendar expirations)   ESC - Back 1 screen\n");
          printw("c - Options calendar (use to confirm expirations)          l - GNU License\n");
          printw("C - Futures calendar (use to confirm expirations)          h - Help\n");
          printw("m - Cycle financial models (or use TAB, arrow keys)        q - Quit\n");

          if( DoWeHaveOptions(properties) )
            printw("d - Options Demo                                   ");

          if( DoWeHaveFutures(properties) )
            printw("        f - Futures Demo\n\n");
          else
            printw("\n\n");

          printw("Feel free to resize the termial screen larger. Program scales to size.\n");
          refresh();

          noecho();
          c = getch();
          echo();

          if( c == 'h' || c == 'H' )
          {
            clear();

            simple_help(properties);

            c = 0;
             
          } else if( c == 'm' || c == ' ' || c == KEY_RIGHT || c == KEY_DOWN || c == '\t' ||
                     c == 'j' )
          {
            clear();
            move(0,0);
            refresh();
              
            if(++properties->modeltype >= (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm)))
            {
              properties->modeltype = 0;
            }

            c = 0;

            continue;

          } else if( c == 'M' || c == ' ' || c == KEY_LEFT || c == KEY_UP ||
                     c == 'k' )
          {
            clear();
            move(0,0);
            refresh();

            if( --properties->modeltype < 0 )
            {
              properties->modeltype = (sizeofoption_algorithms/(signed)sizeof(struct option_algorithm)-1);
            }

            c = 0;

            continue;

          } else if( c == 'l' || c == 'L' )
          {
            clear();
            move(0,0);

            printw("\n\n\n\n\n%s\n\n\n\n\n\n\n\n\n",license);
            printw("\t\t\t");
            attron(A_STANDOUT);
            printw("<<< Press any key to return >>>"); 
            attroff(A_STANDOUT);

            clrtoeol();
              
            refresh();

            noecho();
            getch();
            echo();
              
            c = 0;

            continue;

          } else if( c == 'f' || c == 'F' )
          {
            if( DoWeHaveFutures(properties) )
            {
              /* do a futures demo */
              properties->format = DEMO_FUTURES;
              properties->decimalorcalendar = CALENDAR;

              clear();
              refresh();

              return 0;
            }
              
          } else if( c == 'd' || c == 'D' )
          {
            /* do a demo options demo */
            properties->format = DEMO_OPTIONS;
            properties->decimalorcalendar = DECIMALS;

            clear();
            refresh();
            
            return 0;
              
          } else if( c == 'a' || c == 'A' )
          {
            /*
               if the user changes the expiration information
               the expires() functions are run at the end
               of inputs()
            */
            props(properties,future_properties);

            continue;
              
          } else if( c == 'c' )
          {
            calendar(properties);

            continue;

          } else if( c == 'C' )
          {
            calendar(future_properties);

            continue;

          } else if( c == 'b' || c == 'B' || c == '!' || c == 27 ) // B for back or ! or ESC key
          {
            return -1;

          } else if ( c == 'q' || c == 'Q' )
          {
            /* quit */
            quit(0);
              
          } else
          {
            char buf[128] = { 0 };
            snprintf(buf,sizeof(buf),"%c",c);

            int x = -1;
            sscanf(buf,"%d",&x);

            if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS &&
               option_algorithms[properties->modeltype].supportTime2 == 1 &&
               ( x == 1 || x == 2 ) )
              break;
          
            if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS &&
               option_algorithms[properties->modeltype].supportTime2 == 0 &&
               ( x >= 1 && x <= 9 ) )
              break;

            if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS &&
               option_algorithms[properties->modeltype].supportTime2 == 2 &&
               ( x >= 1 && x <= 9 ) )
              break;

            if(option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS &&
               (x == 1 || x == 2 ) )
              break;

          }

          if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
            break;

        }

        if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
        {
          return -1;
        }

        if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
        {
          switch(c)
          {
             case '1':

               properties->optionscycle = 0;

               properties->format = DECIMAL_FUTURE;
               properties->decimalorcalendar = DECIMALS;

               break;

             case '2':
             
               properties->optionscycle = 0;

               properties->format = CALENDAR_FUTURE;
               properties->decimalorcalendar = CALENDAR;

               break;

          }

        } else if( option_algorithms[properties->modeltype].assetClass == OPTION_CLASS )
        {

          switch(c)
          {
             case '1':

               properties->format = DECIMAL_GREEKS;
               properties->decimalorcalendar = DECIMALS;

               break;

             case '2':

               properties->format= DECIMAL_OPTIONS;
               properties->decimalorcalendar = DECIMALS;

               break;

             case '3':

               properties->format = CALENDAR_OPTIONS1;
               properties->decimalorcalendar = CALENDAR;

               break;

             case '4':

               properties->format= CALENDAR_OPTIONS2;
               properties->decimalorcalendar=CALENDAR;

               break;

             case '5':
              
               properties->format = CALENDAR_OPTIONS3;
               properties->decimalorcalendar = CALENDAR;

               break;

             case '6':

               properties->format = CALENDAR_OPTIONS4;
               properties->decimalorcalendar = CALENDAR;
                  
               break;

             case '7':

               properties->format = CALENDAR_OPTIONS5;
               properties->decimalorcalendar = CALENDAR;

               break;

             case '8':

               properties->format = CALENDAR_CUSTOM;
               properties->decimalorcalendar = CALENDAR;

               break;

             case '9':

               properties->format = CALENDAR_OPTIONS6;
               properties->decimalorcalendar = CALENDAR;

               break;
    
          }

        }

        clear();
        row = -1;

        if( option_algorithms[properties->modeltype].supportPrice )
        {
          properties->data.price = 0;

          ++row;
          for(;;)
          {
            move(row,0);                   
            printw("Enter %-31s    : ", option_algorithms[properties->modeltype].price);
            clrtoeol();

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);
            ret = sscanf(inputstring,"%lf",&properties->data.price);

            /* don't let the user enter a zero or negative */
            if( properties->data.price > 0 && ret == 1 && inputstring[0] != ' ' )
            {
              ret = 0;
              break;
            }
          }
        }

        /*****************************************************************/

        if( option_algorithms[properties->modeltype].supportDividend &&
            option_algorithms[properties->modeltype].supportDividend != 3 &&
            option_algorithms[properties->modeltype].supportDividend != 4 )
        {
          properties->data.dividend = 0;

          ++row;
          for(;;)
          {
            move(row,0);

            if( option_algorithms[properties->modeltype].supportDividend == 1 )
            {
              printw("Enter %-31s    : ", option_algorithms[properties->modeltype].dividend);
            }
            else if( option_algorithms[properties->modeltype].supportDividend == 2 )
            {
              printw("Enter %-31s    : %.2f", option_algorithms[properties->modeltype].dividend,option_algorithms[properties->modeltype].defaultDividend);
            }

            clrtoeol();
            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);
            properties->data.dividend = 0;
            ret = sscanf(inputstring,"%lf",&properties->data.dividend);

            if( option_algorithms[properties->modeltype].supportDividend == 1 )
            {
              /* allow zero and just enter */
              if( properties->data.dividend >= 0 || ret == 0 || ret == 1 )
              {
                if( inputstring[0] == ' ' )
                   properties->data.dividend = 0;

                move(row,43);
                printw("%.2f",properties->data.dividend);

                ret = 0;
                break;
              }
            } else
            if( option_algorithms[properties->modeltype].supportDividend == 2 )
            {
              /* allow the user to just hit enter and take the defaults */
              if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
              {
                move(row,0);
                properties->data.dividend = option_algorithms[properties->modeltype].defaultDividend;
                printw("Enter %-31s    : %.2f", option_algorithms[properties->modeltype].dividend,option_algorithms[properties->modeltype].defaultDividend);

                refresh();
                break;
              }

              // take the entered dividend...
              if( ret == 1 )
              {
                move(row,43);
                printw("%.2f",properties->data.dividend);

                ret = 0;
                break;
              }
            }
          }
        }

        if( ( properties->format == DECIMAL_GREEKS || properties->format == CALENDAR_CUSTOM ) &&
            option_algorithms[properties->modeltype].supportStrikes )
        {
          properties->customstrike = 0;

          ++row;
          for(;;)
          {
            move(row,0);

            /* next line generally %s="Strike" */
            printw("Enter %-31s    : ",option_algorithms[properties->modeltype].strike);
            clrtoeol();

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);
            ret = sscanf(inputstring,"%lf",&properties->customstrike);

            /* don't let the user enter a zero, negative or just hit enter */
            if( properties->customstrike > 0 && ret == 1 && inputstring[0] != ' ' )
            {
              ret = 0;
              break;
            }
          }
        }

        if ( option_algorithms[properties->modeltype].supportRate )
        {
          properties->data.rate = 0;
          ++row;
          for(;;)
          {
            move(row,0);
            printw("Enter interest rate          (%s05 = 5%%)  : ", properties->lc->mon_decimal_point );
            clrtoeol();

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);
            ret = sscanf(inputstring,"%lf",&properties->data.rate);

            /* allow positive, negative and zero interest rate */
            if( ret == 1 && inputstring[0] != ' ' )
            {
              ret = 0;
              move(row,43);
              printw("%.2f%%",properties->data.rate*100);
              break;
            }
          }
        }

        if( (properties->format==DECIMAL_OPTIONS || properties->format==DECIMAL_FUTURE || properties->format==DECIMAL_GREEKS || option_algorithms[properties->modeltype].supportTime2) && option_algorithms[properties->modeltype].perpetual == 0 )

        {
          int rollgeskewhaley_counter = 0;

          for(;;)
          {
            ++row;
            int expiration_day = -1, expiration_month =-1, expiration_year =-1;
            int expiration_hour = -1, expiration_minute = -1,expiration_second =-1;
            int daysaway;
            int decimaldateentered = 0;
            int ret2 = -1;
            int timecursesrow;

            char buf[128] = { 0 };
            const char *const mmddyy = "date MM/DD/YY";

            for(;;)
            {
              timecursesrow = row;
              move(row,0);

              if( option_algorithms[properties->modeltype].supportTime2 == 2 &&
                 properties->decimalorcalendar == CALENDAR )
              {
                rollgeskewhaley_counter = 1;
              }

              if( option_algorithms[properties->modeltype].supportTime2 && rollgeskewhaley_counter == 1 )
              {
                printw("Time to %-17s(%s25=1/4 year)\n",option_algorithms[properties->modeltype].supportTime2des,properties->lc->mon_decimal_point);
                snprintf(buf,sizeof(buf),"%s %s",option_algorithms[properties->modeltype].supportTime2des,mmddyy);
                printw("or %-*s: ",34 + (int) sizeof(mmddyy),buf);

              } else
              {
                if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
                {
                  printw("Time to %-17s(%s25=1/4 year)\n",option_algorithms[properties->modeltype].supportTime1des,properties->lc->mon_decimal_point);
                  snprintf(buf,sizeof(buf),"%s %s",option_algorithms[properties->modeltype].supportTime1des,mmddyy);
                  printw("or %-*s: ",34 + (int) sizeof(mmddyy),buf);

                } else
                {
                  printw("Time to expiration       (%s25=1/4 year)\n",properties->lc->mon_decimal_point);
                  printw("or expiration date MM/DD/YY              : ");
                }
              }

              memset(inputstring,(int) ' ',sizeof(inputstring));
              scanw("%10s",inputstring);
 
              if( option_algorithms[properties->modeltype].supportTime2 && rollgeskewhaley_counter == 1 )
              {
                ret2 = sscanf(inputstring,"%lf/%d/%d",&properties->data.t[rollgeskewhaley_counter],&expiration_day,&expiration_year);
              } else
              {
                ret2 = sscanf(inputstring,"%lf/%d/%d",&properties->data.t[0],&expiration_day,&expiration_year);
              }

              /* don't let the user enter a zero or negative */
              if( properties->data.t[rollgeskewhaley_counter] > 0.0 && ret2 == 1 )
              {
                move(row,0);

                if( option_algorithms[properties->modeltype].supportTime2 && rollgeskewhaley_counter == 1 )
                {
                  printw("Time to %-17s(%s25=1/4 year)  : %.*f %.*f days %s",option_algorithms[properties->modeltype].supportTime2des,properties->lc->mon_decimal_point,properties->precision+2,properties->data.t[rollgeskewhaley_counter],((properties->precision<=2)?2:properties->precision-4),(365*properties->data.t[rollgeskewhaley_counter]),decimal_date_to_real_date(properties->data.t[rollgeskewhaley_counter]));

                } else
                {
                  printw("Time to %-17s(%s25=1/4 year)  : %.*f %.*f days %s",option_algorithms[properties->modeltype].supportTime1des,properties->lc->mon_decimal_point,properties->precision+2,properties->data.t[rollgeskewhaley_counter],((properties->precision<=2)?2:properties->precision-4),(365*properties->data.t[rollgeskewhaley_counter]),decimal_date_to_real_date(properties->data.t[rollgeskewhaley_counter]));
                }

                move(row+1,0); clrtoeol();

                decimaldateentered = 1;

                break;
              }

              /* User entered MM/DD/YY */
              if( ret2 == 3 && properties->data.t[rollgeskewhaley_counter] != -1 && expiration_day != -1 && expiration_year != -1 )
              {

                if( validate_date( expiration_day,(int) properties->data.t[rollgeskewhaley_counter],expiration_year) == 0 )
                {
                  expiration_month= (int) properties->data.t[rollgeskewhaley_counter];

                  daysaway = date_to_days_away(expiration_day,expiration_month,expiration_year);

                  break;
                  
                } else 
                {
                  continue;
                }

              }
              /* User entered MM/DD let get and use this year */
              if( ret2 == 2  && properties->data.t[rollgeskewhaley_counter] != -1 && expiration_day != -1 )
              {
                expiration_year = my_tm->tm_year-100;

                if( validate_date( expiration_day,(int) properties->data.t[rollgeskewhaley_counter],expiration_year) == 0 )
                {
                  expiration_month = (int) properties->data.t[rollgeskewhaley_counter];

                  daysaway = date_to_days_away(expiration_day,expiration_month,expiration_year);

                  break;

                } else 
                {
                  continue;
                }
              }
            }

            int ret = 0;
            ret2 = 0;
            if( expiration_day != -1 && decimaldateentered == 0 )
            {
              row += 2;

              for(;;)
              {
                move(row,0);
                printw("Enter expiration time HH:MM:SS           : ");

                memset(inputstring,(int) ' ',sizeof(inputstring));
                ret = scanw("%10s",inputstring);

                if(ret != -1 )
                {
                  ret2 = sscanf(inputstring,"%d:%d:%d",&expiration_hour,&expiration_minute,&expiration_second);
                }

                /* if they just hit enter set the defaults for HH:MM:SS */
                /*if( ret2 == 0 )
                {
                    expiration_hour = 23;
                    expiration_minute = 59;
                    expiration_second = 0;
                      
                    move(row,0); clrtoeol();

                    break;

                 }*/

                /* User entered hour, minute, seconds */
                if( ret2 == 3 && expiration_hour != -1 && expiration_minute != -1 && expiration_second != -1 )
                {
                  if( validate_time(expiration_hour,expiration_minute,expiration_second) == 0 )
                  {
                    move(row-1,0);
                    clrtoeol();

                    move(row,0);
                    clrtoeol();

                    break;

                  } else
                  {
                    continue;
                  }
                }

                /* User entered hour, minute, we will default seconds to zero  */
                if( ret2 == 2 && expiration_hour != -1 && expiration_minute != -1 && expiration_second == -1 )
                {
                      expiration_second = 0;

                      if( validate_time(expiration_hour,expiration_minute,expiration_second) == 0 )
                      {
                        move(row-1,0);
                        clrtoeol();

                        move(row,0);
                        clrtoeol();

                        break;

                      } else
                      {
                        expiration_hour = expiration_minute = expiration_second = -1;
                        continue;
                      }
                }
              } /* for(;;) */
            } /* if( expiration_day != -1 ) */

            if( decimaldateentered == 0 )
            {
              unsigned int expirationtimeseconds = (unsigned int)(expiration_hour)*
                (unsigned int)60*(unsigned int)60 +
                (unsigned int)(expiration_minute*60) +        
                (unsigned int) expiration_second;

              if( option_algorithms[properties->modeltype].supportTime2 && rollgeskewhaley_counter == 1 )
              {
                properties->data.t[rollgeskewhaley_counter] = adjust_to_current_time_and_expr(&daysaway,expirationtimeseconds,0);
                move(timecursesrow,0);

                printw("Time to %-17s(%s25=1/4 year)  : %.*f %.*f days %s", option_algorithms[properties->modeltype].supportTime2des,properties->lc->mon_decimal_point,properties->precision+2,properties->data.t[rollgeskewhaley_counter],((properties->precision<=2)?2:properties->precision-4),(365*properties->data.t[rollgeskewhaley_counter]),decimal_date_to_real_date(properties->data.t[rollgeskewhaley_counter]));

              } else
              {
                properties->data.t[rollgeskewhaley_counter] = adjust_to_current_time_and_expr(&daysaway,expirationtimeseconds,0);

                move(timecursesrow,0);

                printw("Time to expiration    (%s25=1/4 year)     : %.*f %.*f days %s %02d %02d %02d:%02d", properties->lc->mon_decimal_point,properties->precision+2,properties->data.t[0],((properties->precision<=2)?2:properties->precision-4),(365*properties->data.t[0]),mon[expiration_month-1],expiration_day,expiration_year+2000,expiration_hour,expiration_minute);
              }

              row -= 2;
            }

            if( option_algorithms[properties->modeltype].supportTime2 == 0 )
            {
              break;
            }

            if( ++rollgeskewhaley_counter == 2 )
            {
              break;
            }

            decimaldateentered = 0;
          }

        } else
        {
          if( option_algorithms[properties->modeltype].perpetual == 0 )
            properties->decimalorcalendar = CALENDAR;
        }

        if( option_algorithms[properties->modeltype].supportVolatility == 1 )
        {
          properties->data.volatility = 0;
          ++row;
          for(;;)
          {
            move(row,0);
            printw("Enter %-31s    : ", option_algorithms[properties->modeltype].volatility);
            clrtoeol();

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);
            ret = sscanf(inputstring,"%lf",&properties->data.volatility);

            /* do not let the user enter negative standard deviation */
            if( properties->data.volatility >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
              ret = 0;
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseZ )
        {
          properties->data.UseZ = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseZ == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);

            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseZdes,decimal,option_algorithms[properties->modeltype].Zdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseZ == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseZ);
            } else if( option_algorithms[properties->modeltype].iUseZ == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseZ);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseZ = i;
              properties->data.UseZ = (i < option_algorithms[properties->modeltype].Zmax ? i : option_algorithms[properties->modeltype].Zmax);
            }

            /* do not let the user enter negative standard deviation */
            if( properties->data.UseZ >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseZdes,decimal,properties->data.UseZ); clrtoeol();
                refresh();
                break;
            }
            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseZ = option_algorithms[properties->modeltype].Zdefault;
              //printw("Enter %-31s    : %.2f",option_algorithms[properties->modeltype].UseZdes,properties->data.UseZ); clrtoeol();
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseZdes,decimal,properties->data.UseZ); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseB )
        {
          properties->data.UseB = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseB == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseBdes,decimal,option_algorithms[properties->modeltype].Bdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseB == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseB);
            } else if( option_algorithms[properties->modeltype].iUseB == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseB);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseB = i;
              properties->data.UseB = (i < option_algorithms[properties->modeltype].Bmax ? i : option_algorithms[properties->modeltype].Bmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseB >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseBdes,decimal,properties->data.UseB); clrtoeol();

                refresh();
                break;
            }
            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseB = option_algorithms[properties->modeltype].Bdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseBdes,decimal,properties->data.UseB); clrtoeol();

              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseJ )
        {
          properties->data.UseJ = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseJ == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseJdes,decimal,option_algorithms[properties->modeltype].Jdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseJ == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseJ);
            } else if( option_algorithms[properties->modeltype].iUseJ == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseJ);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseJ = i;
              properties->data.UseJ = (i < option_algorithms[properties->modeltype].Jmax ? i : option_algorithms[properties->modeltype].Jmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseJ >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseJdes,decimal,properties->data.UseJ); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseJ = option_algorithms[properties->modeltype].Jdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseJdes,decimal,properties->data.UseJ); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseP )
        {
          properties->data.UseP = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseP == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UsePdes,decimal,option_algorithms[properties->modeltype].Pdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseP == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseP);
            } else if( option_algorithms[properties->modeltype].iUseP == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseP);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseP = i;
              properties->data.UseP = (i < option_algorithms[properties->modeltype].Pmax ? i : option_algorithms[properties->modeltype].Pmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseP >= 0  && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UsePdes,decimal,properties->data.UseP); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseP = option_algorithms[properties->modeltype].Pdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UsePdes,decimal,properties->data.UseP); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseQ )
        {
          properties->data.UseQ = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseQ == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseQdes,decimal,option_algorithms[properties->modeltype].Qdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseQ == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseQ);
            } else if( option_algorithms[properties->modeltype].iUseQ == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseQ);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseQ = i;
              properties->data.UseQ = (i < option_algorithms[properties->modeltype].Qmax ? i : option_algorithms[properties->modeltype].Qmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseQ >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseQdes,decimal,properties->data.UseQ); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseQ = option_algorithms[properties->modeltype].Qdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseQdes,decimal,properties->data.UseQ); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseR )
        {
          properties->data.UseR = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseR == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseRdes,decimal,option_algorithms[properties->modeltype].Rdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseR == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseR);
            } else if( option_algorithms[properties->modeltype].iUseR == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseR);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseR = i;
              properties->data.UseR = (i < option_algorithms[properties->modeltype].Rmax ? i : option_algorithms[properties->modeltype].Rmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseR >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseRdes,decimal,properties->data.UseR); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseR = option_algorithms[properties->modeltype].Rdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseRdes,decimal,properties->data.UseR); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseS )
        {
          properties->data.UseS = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseS == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseSdes,decimal,option_algorithms[properties->modeltype].Sdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseS == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseS);
            } else if( option_algorithms[properties->modeltype].iUseS == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseS);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseS = i;
              properties->data.UseS = (i < option_algorithms[properties->modeltype].Smax ? i : option_algorithms[properties->modeltype].Smax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseS >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseSdes,decimal,properties->data.UseS); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseS = option_algorithms[properties->modeltype].Sdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseSdes,decimal,properties->data.UseS); clrtoeol();
              refresh();
              break;
            }
          }
        }

        if( option_algorithms[properties->modeltype].iUseT )
        {
          properties->data.UseT = 0;
          ++row;
          int decimal = 2;

          if( option_algorithms[properties->modeltype].iUseT == 2 )
            decimal = 0;

          for(;;)
          {
            move(row,0);
            
            printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseTdes,decimal,option_algorithms[properties->modeltype].Tdefault);

            clrtoeol();

            move(row,43);

            memset(inputstring,(int) ' ',sizeof(inputstring));
            scanw("%10s",inputstring);

            if( option_algorithms[properties->modeltype].iUseT == 1 )
            {
              ret = sscanf(inputstring,"%lf",&properties->data.UseT);
            } else if( option_algorithms[properties->modeltype].iUseT == 2 )
            {
              int i;
              //ret = sscanf(inputstring,"%d",(int *)&properties->data.UseT);
              ret = sscanf(inputstring,"%d",&i);
              //properties->data.UseT = i;
              properties->data.UseT = (i < option_algorithms[properties->modeltype].Tmax ? i : option_algorithms[properties->modeltype].Tmax);
            }
            
            /* do not let the user enter negative standard deviation */
            if( properties->data.UseT >= 0 && ret == 1 && inputstring[0] != ' ' )
            {
                ret = 0;
                move(row,0);
                printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseTdes,decimal,properties->data.UseT); clrtoeol();
                refresh();

                break;
            }

            /* allow the user to just hit enter and take the defaults */
            if( ret == -1 || ret == 0 || inputstring[0] == ' ' )
            {
              move(row,0);
              properties->data.UseT = option_algorithms[properties->modeltype].Tdefault;
              printw("Enter %-31s    : %.*f",option_algorithms[properties->modeltype].UseTdes,decimal,properties->data.UseT); clrtoeol();
              refresh();
              break;
            }
          }
        }

        expires(LEG1,30,properties->skipmonth,future_properties);
        expires(LEG1,30,properties->skipmonth,properties);

        timespec sleepValue = { 0 };
        sleepValue.tv_nsec = 100000000;
        if( nanosleep(&sleepValue, NULL) < 0 )
        {
          printw("nanosleep() failed\n");
          refresh();
        }

        clear();
        refresh();

        return 0;

} // int get_user_inputs(struct _properties *properties,struct _properties *future_properties)
