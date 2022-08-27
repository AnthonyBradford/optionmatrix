/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_misc.cpp of optionmatrix                                    */
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
#include "license.h"
#include "curses_include.h"

void quit(int x)
{
    echo();
    endwin();
  
    printf("\n\n\n\n\n%s\n\n\n\n\n\n\n\n\n", license);
    
    exit(EXIT_SUCCESS);

} // void quit(int x)

void choose_options(void)
{
         clear();

         printw("Choose a option\n");
         printw("+-----------------------------------------------------------------------------+\n");
         printw("| d - Options Demo        o - Options on Futures Demo        f - Futures Demo |\n");
         printw("|                                                                             |\n");         
         printw("| ");
         attron(A_STANDOUT);
         printw("OPTIONS");
         attroff(A_STANDOUT);

         printw("                                                                     |\n");
         printw("| 0 - Date entry or decimal dated put/call with greeks, tickers               |\n");
         printw("| 1 - Date entry or decimal dated matrix with tickers                         |\n");
         printw("| 2 - Calendar dated strike to months matrix                                  |\n");
         printw("| 3 - Calendar dated strike to months matrix with days to expiration, tickers |\n");
         printw("| 4 - Calendar dated strikes to month matrix                                  |\n");
         printw("| 5 - Calendar dated strikes to month matrix with days to expiration, tickers |\n");             
         printw("| 6 - Calendar dated strikes to months matrix                                 |\n");
         printw("| 7 - Calendar dated custom strikes with days to expiration, tickers          |\n");
         printw("|                                                                             |\n");                  
         printw("| ");
         attron(A_STANDOUT);
         printw("FUTURES");
         attroff(A_STANDOUT);

         printw("                                                                     |\n");
         printw("| 8 - Date entry or decimal dated - single future with ticker, days to expr.  |\n");
         printw("| 9 - Calendar dated futures matrix with tickers, days to expiration          |\n");
         printw("|                                                                             |\n");                  
         printw("| a - AdvProperties (use to adjust calendar expirations)                      |\n");
         printw("| c - Options calendar (use to confirm expirations)          l - GNU License  |\n");
         printw("| C - Futures calendar (use to confirm expirations)          q - Quit         |\n");
         printw("+-----------------------------------------------------------------------------+\n");

         printw("Feel free to resize the termial screen larger. Program scales to size.\n");
         printw("Choose option [0-9,dofacClq]: ");

} // void choose_options(void)

void welcome_screen()
{
    int height,width;
    
    /* get screen size */
    getmaxyx(stdscr, height, width);

    // height balance adjuster, adjust all text up or down...
    int x = 1;

    const char *author = "Anthony Bradford's";

    char program[256] = { 0 };
    snprintf(program,sizeof(program),"| Options & Futures Matrix Modeler V%s", PACKAGE_VERSION);

#if defined(ENVIRONMENT32)
    strncat(program," 32-bit", (sizeof(program)-1) - strnlen(program,sizeof(program)));
#elif defined(ENVIRONMENT64)
    strncat(program," 64-bit", (sizeof(program)-1) - strnlen(program,sizeof(program)));
#endif

    strncat(program," |", (sizeof(program)-1) - strnlen(program,sizeof(program)));

    move(((height/2))-9+x,(width/2)-strlen(author)/2);
    attron(A_BOLD);
    printw("%s", author);
    attroff(A_BOLD);

    move(((height/2)-7+x),(width/2)- strlen(program)/2);
    printw("+");
    unsigned int index = 0;
    for( index = 0; index < strlen(program) - 2; index++)
      printw("-");
    printw("+");

    move(((height/2)-6+x),(width/2)- strlen(program)/2);
    printw("%s", program);

    move(((height/2)-5+x),(width/2)- strlen(program)/2);
    printw("+");
    for( index = 0; index < strlen(program) - 2; index++ )
      printw("-");
    printw("+");

    move(((height/2)-4+x),(width/2)- 17/2);
    printw("+---------------+");
    move(((height/2)-3+x),(width/2)- 17/2);
    printw("| Press any key |");
    move(((height/2)-2+x),(width/2)- 17/2);
    printw("+---------------+");

    move(((height/2))+0+x,(width/2)-62/2);
    printw("This program is distributed in the hope that it will be useful,");
    move(((height/2))+1+x,(width/2)-62/2);
    printw("but WITHOUT ANY WARRANTY; without even the implied warranty of");
    move(((height/2))+2+x,(width/2)-62/2);    
    printw("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
    move(((height/2))+3+x,(width/2)-62/2);        
    printw("GNU General Public License for more details.");

    attron(A_BOLD);
    move(((height/2))+5+x,(width/2)-strlen(PACKAGE_BUGREPORT)/2);
    printw(PACKAGE_BUGREPORT);

    move(((height/2))+6+x,(width/2)-strlen(PACKAGE_URL)/2);
    printw(PACKAGE_URL);
    attroff(A_BOLD);

    refresh();

    noecho();
    getch();
    echo();

} // void welcome_screen()

void simple_help(const struct _properties *properties)
{
  clear();

  move(0,0);

  printw("Press <TAB> or 1,2,3,4,5,6,7,8,9 to change display formats.\n");
  printw("m, M - to cycle models, ESC - Go to model select screen\n");
  printw("Lowercase letter is always decrement, uppercase increment\n");
  printw("+,- changes size of increments or decrements of all vars\n");
  printw("z,Z,b,B,j,J,p,P - Exotic var controls, # - State change\n");
  printw("w-walk months backward.\t\tW-walk months forward.\n");
  printw("x-decreases %s prices.", option_algorithms[properties->modeltype].strike);
  printw("\tX-increases %s prices.\n", option_algorithms[properties->modeltype].strike);
  printw("s-decreases stock price.\tS-increases stock price.\n");
  printw("d-decreases dividend.\t\tD-increases dividend.\n");             
  printw("r-decreases interest rates.\tR-increases interest rates.\n");
  printw("t-decreases expiration time.\tT-increases expiration time.\n");
  printw("e-decreases time 2.\t\tE-increases time 2.\n");
  printw("v-decreases standard deviation.\tV-increases standard deviation.\n");
  printw("u-decreases distribution mean.\tU-increases distribution mean.\n");
  printw("y-dec distribution variance.\tY-inc distribution variance.\n");
  printw("g-dec integration or step res.\tG-inc integration or step resolution.\n");
  printw("f-dec floating point precision.\tF-inc floating point precision.\n");
  printw("c - option calendar.\t\tC - Futures Calendar\n");
  printw("a - go to properties page.\to - toggle options cycle\n");
  printw("m - toggle option/fut model\tn - change distribution\n");
  printw("k - toggle strikes increments\t$ - highlight in/on money\n");
  printw("i-toggle CND() generation via Poly Approx, Simpson's Rule, Trapezoid.\n");
  printw("q-quit.  @ - toggle realtime updating  l - GNU License\n");
  
  printw("\t\t\t");
  attron(A_STANDOUT);
  printw("<<< Press any key to return >>>");
  attroff(A_STANDOUT);

  refresh();

  noecho();
  getch();
  echo();

} // void simple_help(const struct _properties *properties)

void calendar_date_message(void)
{
  move(4,0);
  printw("Expirations set to calendar dates");
  clrtoeol();

} // void calendar_date_message(void)

void decimal_date_message(void)
{
  move(4,0);
  printw("Expirations set to decimal date");
  clrtoeol();

} // void decimal_date_message(void)

void one_time_banner_message(void)
{
  static int counter = 0;

  if( counter++ == 0 )
  {
    move(4,0);

    printw("Press ");
    attron(A_STANDOUT);
    printw("M");
    attroff(A_STANDOUT);
    printw(" to cycle models. Press ");
    attron(A_STANDOUT);
    printw("TAB");
    attroff(A_STANDOUT);
    printw(" to cycle screen formats");

    clrtoeol();

  } // if( counter++ == 0 )

} // void one_time_banner_message(void)

int SetToFuture(struct _properties *properties)
{
    int optiontype;

    for( optiontype = 0; optiontype < (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm)); optiontype++)
    {
      if( option_algorithms[optiontype].assetClass == FUTURES_CLASS )
         return optiontype;
    }

    // no future we default to the zero enum model...
    return 0;

} // int SetToFuture(struct _properties *properties)

int SetToOption(struct _properties *properties)
{
    int optiontype;

    for( optiontype = 0; optiontype < (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm)); optiontype++ )
    {
      if( option_algorithms[optiontype].assetClass == OPTION_CLASS )
         return optiontype;
    }

    // no future we default to the zero enum model...
    return 0;

} // int SetToOption(struct _properties *properties)

int DoWeHaveFutures(const struct _properties *properties)
{
    int optiontype;

    for( optiontype = 0; optiontype < (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm)); optiontype++ )
    {
      if( option_algorithms[optiontype].assetClass == FUTURES_CLASS )
         return 1;
    }

    return 0;

} // int DoWeHaveFutures(const struct _properties *properties)

int DoWeHaveOptions(const struct _properties *properties)
{
    int optiontype;

    for( optiontype = 0; optiontype < (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm)); optiontype++ )
    {
      if( option_algorithms[optiontype].assetClass == OPTION_CLASS )
         return 1;
    }

    return 0;

} // int DoWeHaveOptions(const struct _properties *properties)
