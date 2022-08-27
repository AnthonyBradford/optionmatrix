/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_display.cpp of optionmatrix                                 */
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
#include "../common/prototypes.h"
#include "curses_include.h"

void matrix(struct _properties *properties, struct _properties *future_properties)
{
    static int messageClear;

    properties->data.calldelta = NAN;
    properties->data.putdelta = NAN;
    properties->data.callElasticity = NAN;
    properties->data.putElasticity = NAN;
    properties->data.gamma = NAN;
    properties->data.vega = NAN;
    properties->data.calltheta = NAN;
    properties->data.puttheta = NAN;
    properties->data.callrho = NAN;
    properties->data.putrho = NAN;

    int row;
    for( row = 0; row <= 3; row++ )
    {
        move(row,0);
        clrtoeol();
    }

    one_time_banner_message();

    char statusMessage[80 * 3] = { 0 };
    if( sanity_check(properties, &statusMessage[0], sizeof(statusMessage)) )
    {
      move(4,0);
      printw("%s",statusMessage);
      clrtoeol();
      messageClear = 1;
    }

    if( (messageClear++ % 20) == 0 )
    {
      move(4,0);
      clrtoeol();
    }

    parameter_display(properties,future_properties);

    refresh();

    /**********************************************************************/
    
    /* curses specific stuff */
    int height,width,cellrows=14,endingbarrier=22,ibdacross=8;

    /* get screen size */
    getmaxyx(stdscr, height, width);
          
    if( height > 24 )
    {
      cellrows = height-10;
      endingbarrier = height-3;
    }

    if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
    {
      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start,0); clrtoeol();
      move(properties->start+1,0); clrtoeol();

      printw("Bonds not supported in curses version of this program.\nPlease use GUI version of this program.\n");

      return;
    }

#ifdef FINRECIPES

    if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
    {

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start,0); clrtoeol();
      move(properties->start+1,0); clrtoeol();

      double decimalTime  = (double) properties->data.t[0] - (double) properties->data.te;
      double decimalTime2 = (double) properties->data.t[1] - (double) properties->data.te2;

      properties->data.term = 0;
      properties->data.modeltype = properties->modeltype;

      struct _data termstructuredata;
      properties->data.term_model = properties->data.modeltype;
      termstructuredata = termstructure(&properties->data);

      printw("                    Time\tTime\t\t\tValue\n");
      printw("                    ----\t----\t\t\t-----\n");

      printw("Discount Factor T1: %.*f\t%s\t%.*f\n", properties->precision,decimalTime2, decimal_date_to_real_date(decimalTime2),properties->precision,properties->data.discount_t2);

      printw("Discount Factor T2: %.*f\t%s\t%.*f\n", properties->precision,decimalTime,decimal_date_to_real_date(decimalTime),properties->precision,properties->data.discount_t1);

      printw("Spot Rate T1      : %.*f\t%s\t%.*f\n", properties->precision,decimalTime2,decimal_date_to_real_date(decimalTime2),properties->precision,properties->data.spot_t2);

      printw("Spot Rate T2      : %.*f\t%s\t%.*f\n", properties->precision,decimalTime, decimal_date_to_real_date(decimalTime),properties->precision,properties->data.spot_t1);

      printw("Forward T1 - T2   : %.*f\n", properties->precision,properties->data.forward);

      if( properties->data.term )
        delete properties->data.term;

      /* ending barrier for term structures */
      move(endingbarrier+1,0);
      printw("h-help or +-AEFLMRT@ for effects q-quit");
      clrtoeol();

      return;
    }

#endif

    if( properties->format == DECIMAL_GREEKS || properties->demotype == DECIMAL_GREEKS )
    {
      properties->data.isnan = 0;

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start,0); clrtoeol();
      move(properties->start+1,0); clrtoeol();

      if( option_algorithms[properties->modeltype].supportPrice )
      {
        printw("Stock  = %.*f\n",properties->precision,properties->data.price);
      }

      if( option_algorithms[properties->modeltype].supportStrikes )
      {
        printw("%s = %.*f\n\n",option_algorithms[properties->modeltype].strike,properties->precision,properties->customstrike);
      }
                       
      if( option_algorithms[properties->modeltype].supportRate )
      {
        printw("Int. rate  = %.2f%%\n",properties->data.rate*100);
      }
                
      if( option_algorithms[properties->modeltype].perpetual == 0 )
      {
        printw("Expiration =  %.*f, %.*f days, %s\n\n",properties->precision+3,properties->data.t[0]-properties->data.te,properties->precision,(365*(properties->data.t[0]-properties->data.te)),decimal_date_to_real_date(properties->data.t[0]-properties->data.te));
        clrtoeol();
      }

      if( option_algorithms[properties->modeltype].supportStrikes )
        printw("Highlighted prices are in/at the money\n");
      else
        printw("\n");

      properties->data.modeltype = properties->modeltype;
      properties->data.strike = properties->customstrike;
      properties->data.steps = option_algorithms[properties->modeltype].steps;

      struct _data optiondata;

      if( option_algorithms[properties->modeltype].supportCalls )
      {
        optiondata = option_call(&properties->data);

        //printw("Call    = ");
        printw("%s    = ", option_algorithms[properties->modeltype].call);
      
        if(properties->customstrike<=properties->data.price && properties->highlightInTheMoney)
        {
          attron(A_STANDOUT);
        }
        if( option_algorithms[properties->modeltype].supportCalls )
        {
          printw("%.*f",properties->precision,optiondata.call);

        } else
        {
          attroff(A_STANDOUT);
          printw("%*s",properties->precision," ");
        }
        attroff(A_STANDOUT);

        printw("\t");
      }

      if( option_algorithms[properties->modeltype].supportPuts )
      {
        optiondata = option_put(&properties->data);

        //printw("Put     = ");
        printw("%s    = ", option_algorithms[properties->modeltype].put);
      
        if( properties->customstrike>=properties->data.price && properties->highlightInTheMoney )
        {
          attron(A_STANDOUT);
        }

        printw("%.*f",properties->precision,optiondata.put);
        attroff(A_STANDOUT);
      }

      printw("\n");

      /* print the tickers */
      if( option_algorithms[properties->modeltype].supportStrikes )
      {
        if( option_algorithms[properties->modeltype].supportCalls )
          printw("CTicker = %s%c\t\t",option_calls[decimal_date_to_int_month(properties->data.t[0]-properties->data.te)],(char) strike_price_codes(properties->customstrike));

        if( option_algorithms[properties->modeltype].supportPuts )
          printw("PTicker = %s%c",option_puts[decimal_date_to_int_month(properties->data.t[0]-properties->data.te)],(char) strike_price_codes(properties->customstrike));
      }

      printw("\n\n");

      if( option_algorithms[properties->modeltype].produceCallDelta == 1 )
      {
        if( !isnan(properties->data.calldelta) )
          optiondata.calldelta = properties->data.calldelta;
        else
          optiondata = option_call_delta(&properties->data);

        printw("C Delta = %.*f\t",properties->precision,optiondata.calldelta); clrtoeol();
      } else
      {
        printw("C Delta not avail\t");
      }

      if( option_algorithms[properties->modeltype].producePutDelta == 1 )
      {
        if( !isnan(properties->data.putdelta) )
          optiondata.putdelta = properties->data.putdelta;
        else
          optiondata = option_put_delta(&properties->data);

        printw("P Delta = %.*f\n",properties->precision,optiondata.putdelta); clrtoeol();
      } else
      {
        printw("P Delta not avail\n");
      }

      if( option_algorithms[properties->modeltype].produceGamma == 1 )
      {
        if( !isnan(properties->data.gamma) )
          optiondata.gamma = properties->data.gamma;
        else
          optiondata = option_gamma(&properties->data);

        printw("Gamma   = %.*f\t",properties->precision,optiondata.gamma);

      } else
      {
        printw("Gamma not avail  \t");
      }

      if( option_algorithms[properties->modeltype].produceVega == 1 )
      {
        if( !isnan(properties->data.vega) )
          optiondata.vega = properties->data.vega;
        else
          optiondata = option_vega(&properties->data);

        printw("Vega    = %.*f\n\n",properties->precision,optiondata.vega);

      } else
      {
        printw("Vega not avail\n\n");
      }

      if( option_algorithms[properties->modeltype].produceCallTheta == 1 )
      {
        if( !isnan(properties->data.calltheta) )
          optiondata.calltheta = properties->data.calltheta;
        else
          optiondata = option_call_theta(&properties->data);

        printw("C Theta  = %.*f\t",properties->precision,optiondata.calltheta);

      } else
      {
        printw("C Theta not avail\t");
      }

      if( option_algorithms[properties->modeltype].producePutTheta == 1 )
      {
        if( !isnan(properties->data.puttheta) )
          optiondata.puttheta = properties->data.puttheta;
        else
          optiondata = option_put_theta(&properties->data);
 
        printw("P Theta  = %.*f\n",properties->precision,optiondata.puttheta);

      } else
      {
        printw("P Theta not avail\n");
      }

      if( option_algorithms[properties->modeltype].produceCallRho == 1 )
      {
        if( !isnan(properties->data.callrho) )
          optiondata.callrho = properties->data.callrho;
        else
          optiondata = option_call_rho(&properties->data);

        printw("C Rho    = %.*f\t",properties->precision,optiondata.callrho);

      } else
      {
        printw("C Rho not avail  \t");
      }

      if( option_algorithms[properties->modeltype].producePutRho == 1 )
      {
        if( !isnan(properties->data.putrho) )
          optiondata.putrho = properties->data.putrho;
        else
          optiondata = option_put_rho(&properties->data);

        printw("P Rho    = %.*f\n",properties->precision,optiondata.putrho);

      } else
      {
        printw("P Rho not avail");
      }


    }
    /*********************************************************/

    /* Tester */
    /*if( properties->format == DECIMAL_OPTIONS )
    {
      return;
    }*/

    if( properties->format == DECIMAL_OPTIONS || properties->demotype == DECIMAL_OPTIONS )
    {
      properties->data.isnan = 0;

      move(properties->start,0);
      printw("stock  %-6s %-*s %s  %-*s  %s%-*s     %-*s   %-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call,(properties->precision<3)?"":"    ",properties->precision,option_algorithms[properties->modeltype].put,(properties->precision==0)?"":"    ",properties->precision,"c delta",properties->precision,"p delta",properties->precision,"tickers");
      clrtoeol();
                
      move(properties->start+1,0);
      printw("-----  ------ %-*s %s  %-*s  %s%-*s     %-*s   %-*s",properties->precision,"----",(properties->precision<3)?"":"    ",properties->precision,"---",(properties->precision==0)?"":"    ",properties->precision,"-------",properties->precision,"-------",properties->precision,"-------");
      clrtoeol();

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }
                
      int counter = 0;

      move(properties->start+2,0);

      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      double i;

      for(i=(properties->strike_offset+(int)properties->data.price-15/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)properties->data.price+140);i+=strike_control[properties->strikestoogle].incrementor)
      {
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )
        {
            if( i <= 0 || fabs(i-0.0) < epsilon )
            {
              i = 0;

              if(strike_control[properties->strikestoogle].strikes5or1!=5)
              {
                properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
              } else
              {
                properties->strike_offset = properties->strike_offset + 2.5;
              }

              continue;
            }
          
            printw("%.3f ",properties->data.price);
            
            properties->data.modeltype = properties->modeltype;
            properties->data.strike = i;

            properties->data.steps = option_algorithms[properties->modeltype].steps;

            struct _data optiondata;

            optiondata = option_call(&properties->data);

            if(modf(i,&properties->discard)==.5)
            {
              printw("%-5.*f ",1,i);

            } else
            {
              printw("%-4.*f  ",strike_control[properties->strikestoogle].precision,i);
            }

            if(i<=properties->data.price && properties->highlightInTheMoney)
            {
                attron(A_STANDOUT);
            }
            if(option_algorithms[properties->modeltype].supportCalls)
            {
              printw("%.*f",properties->precision,optiondata.call);

            } else
            {
              attroff(A_STANDOUT);
              printw("%*s",properties->precision," ");
            }
            attroff(A_STANDOUT);
            
            printw("    ");

            optiondata = option_put(&properties->data);

            if(i>=properties->data.price && properties->highlightInTheMoney)
            {
                attron(A_STANDOUT);
            }
            if(option_algorithms[properties->modeltype].supportPuts)
            {
              printw("%-.*f",properties->precision,optiondata.put);

            } else
            {
              attroff(A_STANDOUT);
              printw("%*s",properties->precision+3," ");
            }

            attroff(A_STANDOUT);

            printw("   ");

            if( option_algorithms[properties->modeltype].produceCallDelta == 1 )
            {
              if( !isnan(properties->data.calldelta) )
                optiondata.calldelta = properties->data.calldelta;
              else
                optiondata = option_call_delta(&properties->data);

              printw(" %.*f   ", properties->precision,optiondata.calldelta);

            } else
            {
              printw("          ");
            }

            if( option_algorithms[properties->modeltype].producePutDelta == 1 )
             {
              if( !isnan(properties->data.putdelta) )
                optiondata.putdelta = properties->data.putdelta;
              else
                optiondata = option_put_delta(&properties->data);

              printw("%.*f",properties->precision,optiondata.putdelta);

            } else
            {
              printw("          ");
            }

            /* print the tickers */
            if( option_algorithms[properties->modeltype].supportStrikes )
            {
              if( option_algorithms[properties->modeltype].supportCalls )
                printw("   %s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));

              if( option_algorithms[properties->modeltype].supportPuts )
                printw("  %s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
            }

            printw("\n");

            if(counter++>=cellrows)
            {
              break;
            }                               
         }
      }

    }
    /*********************************************************/
    if( properties->format == CALENDAR_OPTIONS1 || properties->demotype == CALENDAR_OPTIONS1 )
    {
      properties->data.isnan = 0;

      move(properties->start,0); clrtoeol();
      printw("stock  %-6s   YY     ",option_algorithms[properties->modeltype].strike);
      move(properties->start,17+(properties->precision/2));                
      printw("%-*s%s%-*s",properties->precision,option_algorithms[properties->modeltype].call,(properties->precision<=1)?" ":"   ",properties->precision,option_algorithms[properties->modeltype].put);                
      move(properties->start+1,0); clrtoeol();
      printw("-----  ------   --     ");
      move(properties->start+1,17+(properties->precision/2));                
      printw("%-*s%s%-*s",properties->precision,"----",(properties->precision<=1)?" ":"   ",properties->precision,"---");

      move(properties->start,35+(2*(properties->precision-4)));
      printw("%-6s   YY %-*s%s%-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call,(properties->precision<2)?" ":"     ",properties->precision,option_algorithms[properties->modeltype].put); clrtoeol();
      move(properties->start+1,35+(2*(properties->precision-4)));
      printw("------   -- %-*s%s%-*s",properties->precision,"----",(properties->precision<2)?" ":"     ",properties->precision,"---"); clrtoeol();
                
      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start+2,0);
      int counter = 0;
      int counter2 = properties->start+2;
      
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      
      double i;
      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+40);i+=strike_control[properties->strikestoogle].incrementor)
      {
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )
         {
            if( i <= 0 || fabs(i-0.0) < epsilon)
            {
              i = 0;

              if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
              {
                properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
              } else
              {
                properties->strike_offset = properties->strike_offset + 2.5;
              }

              continue;
            }
                       
           int mcounter = 0;
           while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
           {
             properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                
            
             if( counter > cellrows )
             {
               if(counter>((cellrows*2)+1))
                {
                  break;
                }

               move(counter2++,36+(2*(properties->precision-4)));
             }

             if( counter <= cellrows )
             {
               printw("%.3f ",properties->data.price);
             }

             properties->data.modeltype = properties->modeltype;
             properties->data.strike = i;
             properties->data.t[0] = properties->adjusttime;
             properties->data.steps = option_algorithms[properties->modeltype].steps;
             
             struct _data optiondata;

             optiondata = option_call(&properties->data);
             optiondata = option_put(&properties->data);

             if(modf(i,&properties->discard)==.5)
             {
               printw("%-4.*f ",1,i);

             } else
             {
               printw("%-3.*f  ",strike_control[properties->strikestoogle].precision,i);
             }

             printw("%s%02.0f ",mon[*properties->expiration_month],(double) *properties->expiration_year);

             if( i <= properties->data.price && properties->highlightInTheMoney )
             {
               attron(A_STANDOUT);
             }
             if( option_algorithms[properties->modeltype].supportCalls )
             {
               printw("%.*f",properties->precision,optiondata.call);

             } else
             {
               attroff(A_STANDOUT);
               printw("%*s",properties->precision," ");
             }
             attroff(A_STANDOUT);

             printw(" ");

             if(i>=properties->data.price && properties->highlightInTheMoney)
             {
               attron(A_STANDOUT);
             }
             if( option_algorithms[properties->modeltype].supportPuts )
             {
               printw("%.*f\n",properties->precision,optiondata.put);

             } else
             {
               attroff(A_STANDOUT);
               printw("%*s\n",properties->precision," ");
             }

             attroff(A_STANDOUT);

             properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
             counter++;

             if( mcounter++ == 5 )
               break;

           }
         }
      }
    }
    /*********************************************************/
    if( properties->format == CALENDAR_OPTIONS2 || properties->demotype == CALENDAR_OPTIONS2 )
    {
      properties->data.isnan = 0;

      move(properties->start,0); clrtoeol();
      printw("stock  %-6s %-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call);
      move(properties->start,23+properties->precision-4);
      printw("%-*s",properties->precision,option_algorithms[properties->modeltype].put);
      printw("  days to exp. exp. date call delta  tickers");
                
      move(properties->start+1,0); clrtoeol();
      printw("-----  ------ %-*s ",properties->precision,"----");
      move(properties->start+1,23+properties->precision-4);
      printw("%-*s",properties->precision,"---");
      printw("  -----------  --------- ----------  -------");                

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }
                
      move(properties->start+2,0);

      int counter = 0;

      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      int mcounter = 0;
      double i;

      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+40);i+=strike_control[properties->strikestoogle].incrementor)
      {
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )
         {
            if( i <= 0 || fabs(i-0.0) < epsilon)
            {
              i = 0;

              if(strike_control[properties->strikestoogle].strikes5or1!=5)
              {
                properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
              } else
              {
                properties->strike_offset = properties->strike_offset + 2.5;
              }

              continue;
            }
                       
           while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
           {

             properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                
             
             if( counter > cellrows )
               break;

             printw("%.3f ",properties->data.price);
             
             properties->data.modeltype = properties->modeltype;
             properties->data.strike = i;
             properties->data.t[0] = properties->adjusttime;
             properties->data.steps = option_algorithms[properties->modeltype].steps;

             struct _data optiondata;

             optiondata = option_call(&properties->data);
             optiondata = option_put(&properties->data);

             if(modf(i,&properties->discard)==.5)
             {
               printw("%-4.*f ",1,i);

             } else
             {
               printw("%-3.*f  ",strike_control[properties->strikestoogle].precision,i);
             }

             if(i<=properties->data.price && properties->highlightInTheMoney)
             {
               attron(A_STANDOUT);
             }
             if(option_algorithms[properties->modeltype].supportCalls)
             {
               printw("%*.*f",properties->precision+3,properties->precision,optiondata.call);

             } else
             {
               attroff(A_STANDOUT);
               printw("%*s",properties->precision," ");
             }
             attroff(A_STANDOUT);

             printw("  ");

             if( i >= properties->data.price && properties->highlightInTheMoney )
             {
               attron(A_STANDOUT);
             }

             if(option_algorithms[properties->modeltype].supportPuts)
             {
               printw("%*.*f",properties->precision+3,properties->precision,optiondata.put);
             } else
             {
               attroff(A_STANDOUT);
               printw("%*s",properties->precision+3," ");
             }
                            
             attroff(A_STANDOUT);
                           
             printw("  %4d       %s%2d %02.0f  ",(*properties->time_to_expiration-properties->day_offset_counter),mon[*properties->expiration_month],*properties->days_to_expiration,(double) *properties->expiration_year);                            

             if( option_algorithms[properties->modeltype].produceCallDelta == 1 )
             {
              if( !isnan(properties->data.calldelta) )
                optiondata.calldelta = properties->data.calldelta;
              else
                optiondata = option_call_delta(&properties->data);

               printw("%.*f",properties->precision,optiondata.calldelta);
             } else
             {
               printw("        ");
             }

             /* print the tickers */
             if( option_algorithms[properties->modeltype].supportStrikes )
             {
               if( option_algorithms[properties->modeltype].supportCalls )
                 printw("   %s%c",option_calls[*properties->expiration_month],(char) strike_price_codes(i));

               if( option_algorithms[properties->modeltype].supportPuts )
                 printw("  %s%c",option_puts[*properties->expiration_month],(char) strike_price_codes(i));
             }

             printw("\n");
                                
             properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
             counter++;

             if( mcounter++ == 4 )
               break;
           }
         }
      }
                
      move(endingbarrier,0);
    }
    /*********************************************************/
    if( properties->format == CALENDAR_OPTIONS3 || properties->demotype == CALENDAR_OPTIONS3 )
    {
      properties->data.isnan = 0;

      move(properties->start,0); clrtoeol();
      printw("stock  %-6s    YY    ",option_algorithms[properties->modeltype].strike);
      move(properties->start,17+(properties->precision/2));                
      printw("%-*s%s%-*s",properties->precision,option_algorithms[properties->modeltype].call,(properties->precision<=1)?" ":"   ",properties->precision,option_algorithms[properties->modeltype].put);                
      move(properties->start+1,0); clrtoeol();
      printw("-----  ------    --    ");
      move(properties->start+1,17+(properties->precision/2));                
      printw("%-*s%s%-*s",properties->precision,"----",(properties->precision<=1)?" ":"   ",properties->precision,"---");
                
      move(properties->start,35+(2*(properties->precision-4)));
      printw("%-6s    YY %-*s%s%-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call,(properties->precision<2)?" ":"     ",properties->precision,option_algorithms[properties->modeltype].put); clrtoeol();
      move(properties->start+1,35+(2*(properties->precision-4)));
      printw("------    -- %-*s%s%-*s",properties->precision,"----",(properties->precision<2)?" ":"     ",properties->precision,"---"); clrtoeol();

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }
                
      int counter = 0;
      int counter2 = properties->start+2;
      move(properties->start+2,0);

      int offset = 3;
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      double i;
      while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
      {
        for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+5+(offset*5));i+=strike_control[properties->strikestoogle].incrementor)
        {
          if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
              ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
              )
          {
            if( i <= 0 || fabs(i-0.0) < epsilon )
            {
              i = 0;

              if(strike_control[properties->strikestoogle].strikes5or1!=5)
              {
                properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
              } else
              {
                properties->strike_offset = properties->strike_offset + 2.5;
              }

              continue;
            }

            properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                

            if( counter > cellrows )
              move(counter2++,36+(2*(properties->precision-4)));

            if(counter>((cellrows*2)+1))
              break;

            if(counter<=cellrows)
              printw("%.3f ",properties->data.price);

            properties->data.modeltype = properties->modeltype;
            properties->data.strike = i;
            properties->data.t[0] = properties->adjusttime;
            properties->data.steps = option_algorithms[properties->modeltype].steps;

            struct _data optiondata;
            
            optiondata = option_call(&properties->data);
            optiondata = option_put(&properties->data);

            if(modf(i,&properties->discard)==.5)
            {
              printw("%-4.*f ",1,i);

            } else
            {
              printw("%-3.*f  ",strike_control[properties->strikestoogle].precision,i);
            }

            printw(" %-s%02.0f ",mon[*properties->expiration_month],(double) *properties->expiration_year);
                            
            if(i<=properties->data.price && properties->highlightInTheMoney)
            {
              attron(A_STANDOUT);
            }
            if(option_algorithms[properties->modeltype].supportCalls)
            {
              printw("%-*.*f",properties->precision+3,properties->precision,optiondata.call);
            } else
            {
              attroff(A_STANDOUT);
              printw("%*s",properties->precision+3," ");
            }
            attroff(A_STANDOUT);

            printw(" ");
                            
            if(i>=properties->data.price && properties->highlightInTheMoney)
            {
              attron(A_STANDOUT);
            }
            if( option_algorithms[properties->modeltype].supportPuts )
            {
              printw("%-*.*f",properties->precision+3,properties->precision,optiondata.put);
            } else
            {
              attroff(A_STANDOUT);
              printw("%*s",properties->precision+3," ");
            }

            attroff(A_STANDOUT);
                            
            printw("\n");
                            
            counter++;
          }
        }

        properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
      }

    }
    /*********************************************************/

    if( properties->format == CALENDAR_OPTIONS4 || properties->demotype == CALENDAR_OPTIONS4 )
    {
      properties->data.isnan = 0;

      move(properties->start,0); clrtoeol();

      printw("stock  %-6s %-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call);
      move(properties->start,23+properties->precision-4);
      printw("%-*s",properties->precision,option_algorithms[properties->modeltype].put);
      printw("  days to exp. exp. date call delta  tickers");
                
      move(properties->start+1,0); clrtoeol();
      printw("-----  ------ %-*s ",properties->precision,"----");
      move(properties->start+1,23+properties->precision-4);
      printw("%-*s",properties->precision,"---");
      printw("  -----------  --------- ----------  -------");                

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }
                
      move(properties->start+2,0);
      int counter = 0;

      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
      {
        double i;
        for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+5);i+=strike_control[properties->strikestoogle].incrementor)
        {
          if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
              ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
              )
           {
             if( i <= 0 || fabs(i-0.0) < epsilon)
             {
               i = 0;

               if(strike_control[properties->strikestoogle].strikes5or1!=5)
                 {
                   properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
                 } else
                 {
                   properties->strike_offset = properties->strike_offset + 2.5;
                 }

               continue;
             }
                           
             properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                

             if( counter > cellrows )
               break;

             printw("%.3f ",properties->data.price);
             
             properties->data.modeltype = properties->modeltype;
             properties->data.strike = i;
             properties->data.t[0] = properties->adjusttime;
             properties->data.steps = option_algorithms[properties->modeltype].steps;

             struct _data optiondata;

             optiondata = option_call(&properties->data);

             if(modf(i,&properties->discard)==.5)
              {
                printw("%-4.*f ",1,i);

              } else
              {
                printw("%-3.*f  ",strike_control[properties->strikestoogle].precision,i);
              }

             if( i <= properties->data.price && properties->highlightInTheMoney )
              {
                attron(A_STANDOUT);
              }                                
             if( option_algorithms[properties->modeltype].supportCalls )
             {
               printw("%*.*f",properties->precision+3,properties->precision,optiondata.call);
             } else
             {
               attroff(A_STANDOUT);
               printw("%*s",properties->precision+3," ");
             }
             attroff(A_STANDOUT);
                            
             printw("  ");

             optiondata = option_put(&properties->data);

             if( i >= properties->data.price && properties->highlightInTheMoney )
             {
                 attron(A_STANDOUT);
             }

             if(option_algorithms[properties->modeltype].supportPuts)
             {
                printw("%*.*f",properties->precision+3,properties->precision,optiondata.put);
             } else
             {
               attroff(A_STANDOUT);
               printw("%*s",properties->precision+3," ");
             }

             attroff(A_STANDOUT);
                            
             printw("  %4d       %s%2d %02.0f  ",(*properties->time_to_expiration-properties->day_offset_counter),mon[*properties->expiration_month],*properties->days_to_expiration,(double) *properties->expiration_year);

             if( option_algorithms[properties->modeltype].produceCallDelta == 1 )
             {
               if( !isnan(properties->data.calldelta) )
                 optiondata.calldelta = properties->data.calldelta;
               else
                 optiondata = option_call_delta(&properties->data);
               
               printw("%.*f",properties->precision,optiondata.calldelta);
             } else
             {
               printw("        ");
             }

             /* print the tickers */
             if( option_algorithms[properties->modeltype].supportStrikes )
             {
               if( option_algorithms[properties->modeltype].supportCalls )
                 printw("   %s%c",option_calls[*properties->expiration_month],(char) strike_price_codes(i));

               if( option_algorithms[properties->modeltype].supportPuts )
                 printw("  %s%c",option_puts[*properties->expiration_month],(char) strike_price_codes(i));
             }

             printw("\n");
                            
             counter++;
                            
           }
        }
        if( counter > cellrows )
          break;

        properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
      }

    }
    /*********************************************************/
    if( properties->format == CALENDAR_OPTIONS5 || properties->demotype == CALENDAR_OPTIONS5 )
    {
      properties->data.isnan = 0;

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start,0); clrtoeol();
      printw("stock  %-6s\n",option_algorithms[properties->modeltype].strike); 
      printw("-----  ------\n");

      int counter = 0;
      int column = 15;
                
      ibdacross = 8;
      int flag2 = 0;

      if( properties->precision >= 8 )
       {
         /* default width on a normal screen is 80 */
         ibdacross = (int) ((double)width/80)*(6 - (2*properties->precision/8));
                    
       } else
       {
         /* default width on a normal screen is 80 */
         ibdacross = (int) (((double)width/80)*(ibdacross + 4 - ((double)8/8*properties->precision)));
                        
         if( properties->precision == 0 || properties->precision == 1 )
           ibdacross++;
       }

      while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
      {
        move(properties->start,column);
        printw(" %s%2d %02.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year);
        clrtoeol();
                    
        properties->expiration_month++; properties->days_to_expiration++; properties->expiration_year++;

        column = column + 8 + properties->precision - 4;
        
        if( ++counter == ibdacross )
          break;
      }

      column = 15;
      move(properties->start+1,15); clrtoeol();
      while( counter != 0 )
      {
        move(properties->start+1,column);
        printw(" --------");
        clrtoeol();

        column = column + 4 + properties->precision;
        counter--;
      }
                
      /* reset pointers */
      properties->expiration_month=properties->start_expiration_month;
      properties->days_to_expiration=properties->start_days_to_expiration;
      properties->expiration_year=properties->start_expiration_year;
      properties->time_to_expiration=properties->start_time_to_expiration;
      
      move(properties->start+2,0);

      int rowcounter = 0;
      column = 15;

      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      /* calc the call matrix */
      double i;
      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+200);i+=strike_control[properties->strikestoogle].incrementor)
      {
        flag2 = 0;
        counter = 0;
                    
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )                        
        {
          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;

            if(strike_control[properties->strikestoogle].strikes5or1!=5)
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }

            continue;
          }
                       
          while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
          {
            properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                
            if( flag2 == 0 )
            {
              flag2 = 1;

              if(modf(i,&properties->discard)!=.5)
              {
                move(rowcounter+properties->start+2,0);
                printw("%3.3f %.*f c  ",properties->data.price,strike_control[properties->strikestoogle].precision,i);
                                    
              } else
              {
                move(rowcounter+properties->start+2,0);
                printw("%3.3f %.1f c  ",properties->data.price,i);

              }
                                
              move(rowcounter+properties->start+2,column);
            }

            properties->data.modeltype = properties->modeltype;
            properties->data.strike = i;
            properties->data.t[0] = properties->adjusttime;
            properties->data.steps = option_algorithms[properties->modeltype].steps;

            if(option_algorithms[properties->modeltype].supportCalls)
            {
              struct _data optiondata;

              optiondata = option_call(&properties->data);

              if( optiondata.call >= 100 )
              {
                printw(" ");
                                
                if( i <= properties->data.price && properties->highlightInTheMoney )
                {
                  attron(A_STANDOUT);
                }
                                
                if( properties->precision != 0 )
                {
                  printw("%3.*f",properties->precision-1,optiondata.call);
                }
                else
                {
                  printw("%3.*f",properties->precision,optiondata.call);
                }
                attroff(A_STANDOUT);
              
              } else
              {                                
                printw(" ");

                if(i<=properties->data.price && properties->highlightInTheMoney)
                {
                  attron(A_STANDOUT);
                }
                printw("%3.*f",properties->precision,optiondata.call);
                attroff(A_STANDOUT);
              }
            }

            properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

            if( ++counter == ibdacross )
            {
              break;
            }
                            
            column = column + 4 + properties->precision;
            move(rowcounter+properties->start+2,column);
                            
          } /* while */

          clrtoeol();
                        
          rowcounter++;

          column = 15;
                        
        } /* if.. */

        properties->time_to_expiration=properties->start_time_to_expiration;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_month=properties->start_expiration_month;
        properties->expiration_year=properties->start_expiration_year;

        if( rowcounter >= (cellrows/2) )
        {
          break;
        }
      }
      
      printw("\n");
      column = 15;
                
      /* now calc the put matrix */
      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+200);i+=strike_control[properties->strikestoogle].incrementor)
      {
        flag2 = 0;
        counter = 0;
                    
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )
        {
          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;

            if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }

            continue;
          }
                       
          while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
          {
            properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                
                            
            if( flag2 == 0 )
            {
              flag2 = 1;

              if(modf(i,&properties->discard)!=.5)
              {
                printw("%3.3f %.*f p",properties->data.price,strike_control[properties->strikestoogle].precision,i);
                                    
              } else
              {
                printw("%3.3f %.1f p",properties->data.price,i);
              }
              move(rowcounter+properties->start+2,column);

            }

            properties->data.modeltype = properties->modeltype;
            properties->data.strike = i;
            properties->data.t[0] = properties->adjusttime;
            properties->data.steps = option_algorithms[properties->modeltype].steps;

            struct _data optiondata;

            optiondata = option_put(&properties->data);

            if( optiondata.put >= 100 )
            {
              printw(" ");

              if( i >= properties->data.price && properties->highlightInTheMoney )
              {
                attron(A_STANDOUT);
              }
              if( properties->precision != 0 )
              {
                if(option_algorithms[properties->modeltype].supportPuts)
                {
                  printw("%3.*f",properties->precision-1,optiondata.put);
                } else
                {
                  attroff(A_STANDOUT);
                  printw("%*s",properties->precision+3," ");
                }

              } else
              {
                if( option_algorithms[properties->modeltype].supportPuts )
                {
                  printw("%3.*f",properties->precision,optiondata.put);
                } else
                {
                  attroff(A_STANDOUT);
                  printw("%*s",properties->precision+3," ");
                }

              }
              attroff(A_STANDOUT);

            } else
            {
              printw(" ");
              
              if( i >= properties->data.price && properties->highlightInTheMoney )
              {
                attron(A_STANDOUT);
              }
              if( option_algorithms[properties->modeltype].supportPuts )
              {
                printw("%3.*f",properties->precision,optiondata.put);

              } else
              {
                attroff(A_STANDOUT);
                printw("%*s",properties->precision+3," ");
              }

              attroff(A_STANDOUT);
            }
                           
            properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
                            
            if( ++counter == ibdacross )
            {
              break;
            }

            column = column + 4 + properties->precision;
            move(rowcounter+properties->start+2,column);
                            
          } /* while */

          clrtoeol();

          rowcounter++;
          printw("\n");
          column = 15;

        } /* if(...) */

        properties->time_to_expiration=properties->start_time_to_expiration;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_month=properties->start_expiration_month;
        properties->expiration_year=properties->start_expiration_year;

        if( rowcounter > cellrows )
        {
          break;
        }
                        
      } /* for.. */

      move(endingbarrier,0);
    }
    
    /*********************************************************/
    if( properties->format == CALENDAR_CUSTOM )
    {
      properties->data.isnan = 0;

      /* clear the screen where the matrix other formats leave
         stuff behind */
      int row;
      for( row = properties->start+2; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start,0); clrtoeol();
      printw("stock  %-6s %-*s",option_algorithms[properties->modeltype].strike,properties->precision,option_algorithms[properties->modeltype].call);
      move(properties->start,23+properties->precision-4);
      printw("%-*s",properties->precision,option_algorithms[properties->modeltype].put);
      printw("  days to exp. exp. date call delta  tickers");
      
      move(properties->start+1,0); clrtoeol();
      printw("-----  ------ %-*s ",properties->precision,"----");
      move(properties->start+1,23+properties->precision-4);
      printw("%-*s",properties->precision,"---");
      printw("  -----------  --------- ----------  -------");                
      
      move(properties->start+2,0);
      int counter = 0;

      while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
      {
        
        properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                

        if( counter > cellrows )
          break;

        move(properties->start+2+counter,0);

        properties->data.modeltype = properties->modeltype;
        properties->data.strike = properties->customstrike;
        properties->data.t[0] = properties->adjusttime;
        properties->data.steps = option_algorithms[properties->modeltype].steps;
                    
        struct _data optiondata;

        optiondata = option_call(&properties->data);
        optiondata = option_put(&properties->data);
        
        printw("%.3f %.*f",properties->data.price,properties->precision-4,properties->customstrike);

        printw(" ");
                    
        if( properties->customstrike <= properties->data.price && properties->highlightInTheMoney )
        {
          attron(A_STANDOUT);
        }
        if( option_algorithms[properties->modeltype].supportCalls )
        {
          printw("%*.*f",properties->precision+3,properties->precision,optiondata.call);

        } else
        {
          attroff(A_STANDOUT);
          printw("%*s",properties->precision," ");
        }
        attroff(A_STANDOUT);
                    
        printw("  ");

        if( properties->customstrike >= properties->data.price && properties->highlightInTheMoney )
        {
          attron(A_STANDOUT);
        }
        if( option_algorithms[properties->modeltype].supportPuts )
        {
          printw("%*.*f",properties->precision+3,properties->precision,optiondata.put);
        } else
        {
          attroff(A_STANDOUT);
          printw("%*s",properties->precision+3," ");
        }

        attroff(A_STANDOUT);
                    
        printw("  %4d       %s%2d %02.0f  ",(*properties->time_to_expiration-properties->day_offset_counter),mon[*properties->expiration_month],*properties->days_to_expiration,(double) *properties->expiration_year);

        if( option_algorithms[properties->modeltype].produceCallDelta == 1 )
        {
          if( !isnan(properties->data.calldelta) )
            optiondata.calldelta = properties->data.calldelta;
          else
            optiondata = option_call_delta(&properties->data);

          printw("%.*f",properties->precision,optiondata.calldelta);

        } else
        {
          printw("        ");
        }

        /* print the tickers */
        if( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( option_algorithms[properties->modeltype].supportCalls )
            printw("   %s%c",option_calls[*properties->expiration_month],(char) strike_price_codes(properties->customstrike));

          if( option_algorithms[properties->modeltype].supportPuts )
            printw("  %s%c",option_puts[*properties->expiration_month],(char) strike_price_codes(properties->customstrike));
        }

        printw("\n");
                    
        counter++;

        properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
      }
    }
            
    if(properties->format == DECIMAL_FUTURE)
    {
      if(!DoWeHaveFutures(properties))
      {
        clear();
        printw("Futures decimal dated screen # 1 not implemented.\nFutures model not defined.\n\n\n");

        attron(A_STANDOUT);
        printw("Press TAB to continue");
        attroff(A_STANDOUT);
        refresh();

        return;
      }
      /* clear the screen where the matrix other formats leave
         stuff behind */
      int row;
      for( row = properties->start; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start+3,0);

      properties->data.modeltype = properties->modeltype;
      
      struct _data optiondata;

      optiondata = future(&properties->data);

      printw("Spot Price           = %.*f\n",properties->precision,properties->data.price); clrtoeol();
      printw("Futures Price        = %.*f (%s)\n",properties->precision,properties->data.future,(properties->data.future>properties->data.price?"Cotango":"Backwardation"));
      printw("Interest rate        = %.2f%%\n",properties->data.rate*100);
      printw("Basis                = %.*f\n",properties->precision,properties->data.price-properties->data.future); clrtoeol();
      printw("Days to expr         = %.*f\n",properties->precision,(365*(properties->data.t[0]-properties->data.te))); clrtoeol();
      printw("Time to expr         = %.*f\n",properties->precision+3,properties->data.t[0]-properties->data.te);

      printw("Expiration date      = %s\n",decimal_date_to_real_date(properties->data.t[0]-properties->data.te));
      printw("Ticker               = %s%02d",future_codes[decimal_date_to_int_month(adjust_to_current_time(properties->data.t[0]-properties->data.te,0))],decimal_date_to_int_year(adjust_to_current_time(properties->data.t[0]-properties->data.te,0)));

      printw("\n\n\n\t\t");
      attron(A_STANDOUT);
      printw("Press 2");
      attroff(A_STANDOUT);
      printw(" to switch to date by calendar");

      move(endingbarrier,0);

      printw("------------------------------------------------------------------------------\n");
      move(endingbarrier,82/2-strlen("Futures")/2);
      printw("Futures");

    }

    if( properties->format==CALENDAR_FUTURE || 
        properties->demotype==CALENDAR_FUTURE )
    {
      if(!DoWeHaveFutures(properties))
      {
        clear();
        printw("Futures calendar dated screen # 2 not implemented.\nFutures model not defined.\n\n\n");
        attron(A_STANDOUT);
        printw("Press TAB to continue");
        attroff(A_STANDOUT);

        refresh();

        return;
      }

      /* clear the screen where the matrix other formats leave
         stuff behind */
      int row;
      for( row = properties->start; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }
                
      move(properties->start,0);
      int counter = 0;
      int counter2 = properties->start+2;

      printw("  Expiration Days to Price               Expiration Days to Price\n");
      printw("  ---------- ------- -----               ---------- ------- -----\n");
      printw("  Spot           0   %.*f\n",properties->precision,properties->data.price); 

      while( (*future_properties->time_to_expiration!= -1) && (*future_properties->days_to_expiration!= -1) && (*future_properties->expiration_month!= -1) && (*future_properties->expiration_year!= -1) )
      {
        if(counter>cellrows-1)
        {
          if(counter>(cellrows*2))
          {
            break;
          }
          move(counter2++,39);
        }

        future_properties->adjusttime = adjust_to_current_time_and_expr(future_properties->time_to_expiration,future_properties->expiration_time,future_properties->day_offset);                                
        properties->data.modeltype = properties->modeltype;
        properties->data.t[0] = future_properties->adjusttime;
        struct _data optiondata;
        optiondata = future(&properties->data);

        printw("%s %s%2d %02.0f    %4d   %.*f\n",future_codes[*future_properties->expiration_month],mon[*future_properties->expiration_month],*future_properties->days_to_expiration,(double)*future_properties->expiration_year,(*future_properties->time_to_expiration-future_properties->day_offset_counter),properties->precision,properties->data.future);

        future_properties->time_to_expiration++;  future_properties->days_to_expiration++;  future_properties->expiration_month++;  future_properties->expiration_year++;

        counter++;
      }
      if( properties->demotype != CALENDAR_FUTURE )
      {
        move(21,39);
        attron(A_STANDOUT);
        printw("Press 1");
        attroff(A_STANDOUT);
        printw(" to switch to decimal dating");
      }

      move(endingbarrier,0);
      printw("------------------------------------------------------------------------------\n");
      move(endingbarrier,82/2-strlen("Futures")/2);
      printw("Futures");

    }

    if( properties->format == CALENDAR_OPTIONS6 || properties->demotype == CALENDAR_OPTIONS6 )
    {
      properties->data.isnan = 0;

      int columnbreak = 3;

      if( properties->precision >= 8 )
        columnbreak = 2;

      if( properties->precision >= 12 )
        columnbreak = 1;

      if( properties->precision <= 4 )
        columnbreak = 4;

      if( properties->precision <= 2 )
        columnbreak = 5;

      if( properties->precision <= 1 )
        columnbreak = 6;

      /* clear the screen where the matrix other properties->formats leave
         stuff behind */
      int row;
      for( row = properties->start; row <= endingbarrier; ++row )
      {
        move(row,0);  clrtoeol();
      }

      move(properties->start+1,0); clrtoeol();
      printw("stock  %-6s\n",option_algorithms[properties->modeltype].strike); 
      printw("-----  ------\n");

      int counter = 0;
      int column = 14;
      int flag2 = 0;

      while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
      {
        move(properties->start+1,column);
        printw(" %s%2d %02.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year);
        clrtoeol();
                    
        properties->expiration_month++; properties->days_to_expiration++; properties->expiration_year++;

        column = column + 8 + properties->precision - 4;
        
        if( ++counter == columnbreak )
          break;
      }

      column = 14;

      while( counter != 0 )
      {
        move(properties->start+2,column);
        printw(" --------");
        clrtoeol();

        column = column + 4 + properties->precision;
        counter--;
      }
                
      /* reset pointers */
      properties->expiration_month=properties->start_expiration_month;
      properties->days_to_expiration=properties->start_days_to_expiration;
      properties->expiration_year=properties->start_expiration_year;
      properties->time_to_expiration=properties->start_time_to_expiration;
      
      move(properties->start,0);
      //printw("                          Calls                           Puts");
      printw("                          %-5s                           %-4s",option_algorithms[properties->modeltype].call,option_algorithms[properties->modeltype].put);

      int rowcounter = 0;
      column = 14;

      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      double i;
      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+200);i+=strike_control[properties->strikestoogle].incrementor)
      {
        flag2 = 0;
        counter = 0;
                    
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )                        
        {

          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;

            if(strike_control[properties->strikestoogle].strikes5or1!=5)
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }

            continue;
          }

          /* calc the call matrix */
          while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
          {
            properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                

            if( flag2 == 0 )
            {
              flag2 = 1;

              if(modf(i,&properties->discard)!=.5)
              {
                move(rowcounter+properties->start+3,0);
                printw("%3.3f %.*f   ",properties->data.price,strike_control[properties->strikestoogle].precision,i);
                                    
              } else
              {
                move(rowcounter+properties->start+3,0);
                printw("%3.3f %.1f   ",properties->data.price,i);

              }
                                
              move(rowcounter+properties->start+3,column);
            }

            properties->data.modeltype = properties->modeltype;
            properties->data.strike = i;
            properties->data.t[0] = properties->adjusttime;
            properties->data.steps = option_algorithms[properties->modeltype].steps;

            if( option_algorithms[properties->modeltype].supportCalls )
            {
              struct _data optiondata;

              optiondata = option_call(&properties->data);

              if( optiondata.call >= 100 )
              {
                printw(" ");
                                
                if(i<=properties->data.price && properties->highlightInTheMoney)
                {
                  attron(A_STANDOUT);
                }
                                
                if( properties->precision != 0 )
                {
                  printw("%3.*f",properties->precision-1,optiondata.call);
                }
                else
                {
                  printw("%3.*f",properties->precision,optiondata.call);
                }
                attroff(A_STANDOUT);
              
              } else
              {                                
                printw(" ");

                if( i <= properties->data.price && properties->highlightInTheMoney )
                {
                  attron(A_STANDOUT);
                }

                printw("%3.*f",properties->precision,optiondata.call);
                attroff(A_STANDOUT);
              }
            }

            properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

            // columnbreak for call
            if( ++counter == columnbreak )
            {
              break;
            }
                            
            column = column + 4 + properties->precision;
            move(rowcounter+properties->start+3,column);
                            
          } /* while */

          clrtoeol();
                        
          rowcounter++;

          column = 14;
                        
        } /* if.. */

        if( rowcounter >= cellrows )
        {
          break;
        }

        properties->time_to_expiration=properties->start_time_to_expiration;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_month=properties->start_expiration_month;
        properties->expiration_year=properties->start_expiration_year;

      }
      /***********************************************************************/

      rowcounter = 0;
      column = 47;
      counter = 0;

      epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);

      /* reset pointers */
      properties->expiration_month=properties->start_expiration_month;
      properties->days_to_expiration=properties->start_days_to_expiration;
      properties->expiration_year=properties->start_expiration_year;
      properties->time_to_expiration=properties->start_time_to_expiration;

      /* calc the put matrix */
      while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
      {
        move(properties->start+1,column);
        printw("%s%2d %02.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year);
        clrtoeol();
                    
        properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

        column = column + 8 + properties->precision - 4;
        
        if( ++counter == columnbreak )
        {
          break;
        }
      }
      clrtoeol();

      column = 46;
      while( counter != 0 )
      {
        move(properties->start+2,column);
        printw(" --------");

        column = column + 4 + properties->precision;
        counter--;
      }
      clrtoeol();
                
      /* reset pointers */
      properties->expiration_month=properties->start_expiration_month;
      properties->days_to_expiration=properties->start_days_to_expiration;
      properties->expiration_year=properties->start_expiration_year;
      properties->time_to_expiration=properties->start_time_to_expiration;

      column = 46;

      /* calc the put matrix */
      for(i=(properties->strike_offset+(int)properties->data.price-15);i<(properties->strike_offset+(int)properties->data.price+200);i+=strike_control[properties->strikestoogle].incrementor)
      {
        flag2 = 0;
        counter = 0;
                    
        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )                        
        {

          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;

            if(strike_control[properties->strikestoogle].strikes5or1!=5)
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }

            continue;
          }
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            while( (*properties->time_to_expiration!= -1) && (*properties->days_to_expiration!= -1) && (*properties->expiration_month!= -1) && (*properties->expiration_year!= -1) )
            {
              properties->adjusttime = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,properties->day_offset);                                

              if( flag2 == 0 )
              {
                flag2 = 1;

                move(rowcounter+properties->start+3,column);
              }

              properties->data.modeltype = properties->modeltype;
              properties->data.strike = i;
              properties->data.t[0] = properties->adjusttime;
              properties->data.steps = option_algorithms[properties->modeltype].steps;

              struct _data optiondata;

              optiondata = option_put(&properties->data);

              if( optiondata.put >= 100 )
              {
                printw(" ");
                                
                if( i >= properties->data.price && properties->highlightInTheMoney )
                {
                  attron(A_STANDOUT);
                }
                                
                if( properties->precision != 0 )
                {
                  printw("%3.*f",properties->precision-1,optiondata.put);
                }
                else
                {
                  printw("%3.*f",properties->precision,optiondata.put);
                }
                attroff(A_STANDOUT);
              
              } else
              {                                
                printw(" ");

                if(i>=properties->data.price && properties->highlightInTheMoney)
                {
                  attron(A_STANDOUT);
                }
                printw("%3.*f",properties->precision,optiondata.put);
                attroff(A_STANDOUT);
              }

              properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

              // columnbreak for put
              if( ++counter == columnbreak )
              {
                break;
              }
                            
              column = column + 4 + properties->precision;
              move(rowcounter+properties->start+3,column);
                            
            } /* while */

            clrtoeol();
                        
            rowcounter++;

            column = 46;
                        
          } /* if.. */

          if(rowcounter>=cellrows)
          {
              break;
          }
        }

        properties->time_to_expiration=properties->start_time_to_expiration;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_month=properties->start_expiration_month;
        properties->expiration_year=properties->start_expiration_year;

      }

      /***********************************************************************/

    }
    /*********************************************************/

    if( properties->data.isnan == 1 )
    {
      // "nan" not a number detected, instructions should be given to the user to
      // adjust t2 forward to get rid of nans or give model divided...
      // probably have a "[ ] do not show again" popup with these instructions
      // in the gtk version of optionmatrix
    }

    properties->time_to_expiration=properties->start_time_to_expiration;
    properties->days_to_expiration=properties->start_days_to_expiration;
    properties->expiration_month=properties->start_expiration_month;
    properties->expiration_year=properties->start_expiration_year;
    
    future_properties->time_to_expiration=future_properties->start_time_to_expiration;
    future_properties->days_to_expiration=future_properties->start_days_to_expiration;
    future_properties->expiration_month=future_properties->start_expiration_month;
    future_properties->expiration_year=future_properties->start_expiration_year;

    if( properties->format == DEMO_OPTIONS ||
        properties->format == DEMO_FUTURES)
    {
      attron(A_STANDOUT);
      move(endingbarrier+1,82/2-strlen("PRESS 'q' TO QUIT DEMO")/2);
      printw("PRESS 'q' TO QUIT DEMO");
      attroff(A_STANDOUT);

      clrtoeol();

      return;
    }

    /* ending barrier for options */
    if( option_algorithms[properties->modeltype].assetClass == OPTION_CLASS )
    {
      /* ending barrier for options */
      move(endingbarrier+1,0);
      printw("h-help Type TAB or +-123456789ABCDEFGIJKLMNOPRSTUVWXYZ@ for effects q-quit");
      clrtoeol();
            
    } else
    if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
    {
      /* ending barrier for futures */
      move(endingbarrier+1,0);
      printw("h-help Type TAB or +-123456789ACDFLMRSTW@ for effects q-quit");
      clrtoeol();
    } else
    {
      move(endingbarrier+1,0);
      printw("h-help New asset class implemented? Ending banner not set");
      clrtoeol();
    }

} // void matrix(struct _properties *properties, struct _properties *future_properties)

// remove a set but un-used compiler warning...
inline void noop(int x)
{
    return;

} // inline void noop(int x)

void parameter_display(struct _properties *properties,struct _properties *future_properties)
{
  /**********************************************************************/

  move(0,0);

  if ( option_algorithms[properties->modeltype].supportPrice )
    printw("S=%.*f ",(2>properties->precision-4?2:properties->precision-4),properties->data.price);

  if( properties->format == CALENDAR_CUSTOM )
  {
    if ( option_algorithms[properties->modeltype].supportStrikes )
      printw("X=%.*f ",(2>properties->precision-4?2:properties->precision-4),properties->data.strike);
  }
  
  if( option_algorithms[properties->modeltype].supportRate )
    printw("R=%.*f ",(4>properties->precision-2?4:properties->precision-2),properties->data.rate);

  if( option_algorithms[properties->modeltype].supportVolatility )
  {
    printw("V=%.*f ",(3>properties->precision-3?3:properties->precision-3),properties->data.volatility);
  }

  if( option_algorithms[properties->modeltype].supportDividend )
  {
    printw("D=%.*f ",(3>properties->precision-3?3:properties->precision-3),properties->data.dividend);
  }

  printw("F=%d ",properties->precision);

  if( option_algorithms[properties->modeltype].assetClass != FUTURES_CLASS &&
      properties->format != CALENDAR_CUSTOM &&
      properties->format != DECIMAL_GREEKS)
  {
    printw("K=%s ",strike_control[properties->strikestoogle].des);
  }

  if( properties->decimalorcalendar == CALENDAR )
  {
    printw("W=%d ",properties->skipmonth);
  }
        
  clrtoeol();

  /* curses stuff */
  int height,width;
   
  /* curses, get screen size */
  getmaxyx(stdscr, height, width);

  noop(height);

  time_t mytime;
  struct tm *my_tm;
    
  time(&mytime);
  my_tm = localtime(&mytime);

  char tstring[200] = { 0 };
  strftime(tstring,sizeof(tstring),"%a %b %d %Y %H:%M:%S",my_tm);
  move(0,width-strlen(tstring));
  printw("%s\n",tstring);
    
  move(1,0);

  if( properties->decimalorcalendar == DECIMALS &&
      option_algorithms[properties->modeltype].perpetual == 0 )
  {
    printw("T=%.*f %.*f days Expiration %s\n",properties->precision+3,properties->data.t[0]-properties->data.te,((properties->precision<=2)?2:properties->precision-1),(365*(properties->data.t[0]-properties->data.te)),decimal_date_to_real_date(properties->data.t[0]-properties->data.te));
    clrtoeol();
        
  } else
  {
    if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
    {
      printw("Expirations %d%s %s+%d %02d:%02d:%02d\n",future_properties->occurence_in_month,order[future_properties->occurence_in_month-1],weekdays[future_properties->occurence_day-1],future_properties->occurence_plus_offset,future_properties->expiration_hour,future_properties->expiration_minute,future_properties->expiration_second);

    } else if( option_algorithms[properties->modeltype].assetClass == OPTION_CLASS &&
               option_algorithms[properties->modeltype].perpetual == 0 )
    {
      printw("Expirations %d%s %s+%d %02d:%02d:%02d OCycle:%s\n",properties->occurence_in_month,order[properties->occurence_in_month-1],weekdays[properties->occurence_day-1],properties->occurence_plus_offset,properties->expiration_hour,properties->expiration_minute,properties->expiration_second,optionscycle[properties->optionscycle]);
    }
  }

  if(option_algorithms[properties->modeltype].supportTime2 &&
     option_algorithms[properties->modeltype].perpetual == 0 )
  {
    printw("E%s=%.*f %.*f days %s\n",option_algorithms[properties->modeltype].supportTime2des,properties->precision+2,properties->data.t[1]-properties->data.te2,((properties->precision<=2)?2:properties->precision-1),(365*(properties->data.t[1]-properties->data.te2)),decimal_date_to_real_date(properties->data.t[1]-properties->data.te2));
    clrtoeol();
    
  }

  printw("M=");
  attron(A_BOLD);
  printw("%s ",option_algorithms[properties->modeltype].des);
  attroff(A_BOLD);

  if(option_algorithms[properties->modeltype].bUsePound)
  {
    if( option_algorithms[properties->modeltype].bUseStateNames == 0 )
    {
      printw("#%s=%d ",option_algorithms[properties->modeltype].UsePounddes,properties->data.UsePound);
    } else
    {
      printw("#%s=%s ",option_algorithms[properties->modeltype].UsePounddes, (char *) &(option_algorithms[properties->modeltype].StateNames[properties->data.UsePound-1]));

    }
  }

  if( option_algorithms[properties->modeltype].iUseZ )
  {
    printw("Z%s=%.*f ",option_algorithms[properties->modeltype].UseZdes,(2>properties->precision-4?2:properties->precision-4),properties->data.UseZ);
  }

  if( option_algorithms[properties->modeltype].iUseB )
  {
    printw("B%s=%.*f ",option_algorithms[properties->modeltype].UseBdes,(2>properties->precision-4?2:properties->precision-4),properties->data.UseB);
  }

  if( option_algorithms[properties->modeltype].iUseJ )
  {
    printw("J%s=%.*f ",option_algorithms[properties->modeltype].UseJdes,(2>properties->precision-4?2:properties->precision-4),properties->data.UseJ);
  }

  if( option_algorithms[properties->modeltype].iUseP )
  {
    printw("P%s=%.*f ",option_algorithms[properties->modeltype].UsePdes,(2>properties->precision-4?2:properties->precision-4),properties->data.UseP);
  }

  if( option_algorithms[properties->modeltype].supportCND == 1 )
  {
    printw("I=%s ",integration_method[properties->integration_type].des);
        
    if( integration_method[properties->integration_type].resolution )
      printw("GSteps=%d ",integration_method[properties->integration_type].resolution);

    if( properties->distribution_mean != 0 )
    {
      printw("U=%.*f ",properties->precision-3,properties->distribution_mean);
    }
    if( properties->distribution_variance != 1 )
    {
      printw("Y=%.*f ",properties->precision-3,properties->distribution_variance);
    }
     
  } else
  {
    if( option_algorithms[properties->modeltype].supportSteps == 1 )
    {
      printw("GSteps=%d ",option_algorithms[properties->modeltype].steps);
    }
  }

  if( properties->distribution_type != 0 && option_algorithms[properties->modeltype].supportCND == 1 )
  {
    printw("N=%s ",distribution_list[properties->distribution_type].des);
  }
    
  printw("H=Help A=AdvProperties "); 

  //printw("DORC = %d",properties->decimalorcalendar);
  //printw("Format=%d",properties->format);
  //printw("assetClass = %d",option_algorithms[properties->modeltype].assetClass);
  //printw("modeltype = %d",properties->modeltype);

  clrtoeol();
    
  refresh();
  
} // void parameter_display(struct _properties *properties,struct _properties *future_properties)
