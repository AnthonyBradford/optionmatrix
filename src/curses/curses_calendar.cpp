/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_calendar.cpp of optionmatrix                                */
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

void calendar(const struct _properties *properties)
{
    int x = 0;
    int y,nextmonth,friday,monthsout;
    int counter1,n,day,year;
    int ret = 0;
    char inputstring[200] = { 0 };
    char character;

    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    if( my_tm->tm_wday == 0 )
    {
        x = 7;
    } else
    {
        x = my_tm->tm_wday;
    }

    year = my_tm->tm_year;

    monthsout = -1;
    
    for(;;)
    {
        clear();
        
        move(0,0);
        printw("Press lower case 'c' for Options Calendar, capital 'C' for Futures Calendar.\n\n");
        printw("Show calendar how many months out  : ");

        memset(inputstring,(int) ' ',sizeof(inputstring));
        scanw("%10s",inputstring);
        ret = sscanf(inputstring,"%d",&monthsout);

        /* don't allow user to enter zero or negative numbers */
        if( monthsout > 0 && ret == 1 )
        {
            ret = 0;
            clear();
            break;
        }
    }

    /* count back to the first of the month and keep
       day names in sync */
    counter1 = my_tm->tm_mday;
    day = x;
    while( counter1 != 1 )
    {
        counter1--;

        if( day-- == 1 )
            day = 7;
    }

    /* figure out if it is a leap year and adjust the month feb */
    if( ((year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
        months[1] = 29;
    else
        months[1] = 28;

    /* increment to the end of the month take option expiration
       date only it is greater than current date  */
    friday = 1;
    
    printw("%s expirations set to %d%s %s+%d @ %02d:%02d:%02d. ", (properties->modeltype!=_FUTURES)?"Options":"Futures",properties->occurence_in_month,order[properties->occurence_in_month-1],weekdays[properties->occurence_day-1],properties->occurence_plus_offset,properties->expiration_hour,properties->expiration_minute,properties->expiration_second);

    //printw("BIsAFuture = %d\n",option_algorithms[properties->modeltype].bIsAFuture);
    
    printw("Use AdvProperties to change.\nTime to expiration is accurate to the second from your current time.\n");
   
    printw("\n\t\t%s %d\n\n", mon[my_tm->tm_mon], year + 1900);
    printw("\t\tMon\tTue\tWens\tThur\tFri\tSat\tSun\n");
    printw("\t\t---------------------------------------------------\n\t\t");

    for( n = 1; n < day; n++ )
        printw("\t");

    int offset = properties->occurence_plus_offset;
    int found = 0;

    while( counter1 <= months[my_tm->tm_mon] )
    {
        if( day == properties->occurence_day ) /* this is a friday or user specified day */
        {        
            /* this is the 3rd friday of the month or user specified */
            if( friday++ == properties->occurence_in_month ) 
            {
                /*printw("x");*/
                found = 1;
                monthsout--;
            }
        }
        if( found == 1 )
        {
            if( offset-- == 0 )
            {
                printw("EXPR");
            }

        }
        printw("%d\t", counter1);

        if( day++ == 7 )
        {
            day = 1;
            printw("\n\t\t---------------------------------------------------\n\t\t");
        }
        counter1++;
    }

    printw("\n\n\t\t\t ");
    attron(A_STANDOUT);
    printw("<< Press any key or Q to quit >>\n");
    attroff(A_STANDOUT);

    character = getch();

    if( character == 'q' || character == 'Q' )
    {
        clear();
        
        return;
    }

    counter1 = my_tm->tm_mday;
    day = x;

    /* increment to the end of the month */
    while( counter1++ < months[my_tm->tm_mon] ) {
        if( day++ == 7 )
            day = 1;
    }
    nextmonth = my_tm->tm_mon;

    if( day++ == 7 )
        day = 1;

    while( monthsout-- != 0 )
    {
        clear();

        if( nextmonth++ == 11 ) /* months 0-11 */
        {        
            nextmonth = 0;        /* set to Jan */
            year++;
        }

        /* figure out if it is a leap year and adjust the month feb */
        if( ((year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
            months[1] = 29;
        else
            months[1] = 28;

        printw("%s expirations set to %d%s %s+%d @ %02d:%02d:%02d. ", (properties->modeltype!=_FUTURES)?"Options":"Futures",properties->occurence_in_month,order[properties->occurence_in_month-1],weekdays[properties->occurence_day-1],properties->occurence_plus_offset,properties->expiration_hour,properties->expiration_minute,properties->expiration_second);

        printw("Use AdvProperties to change.\nTime to expiration is accurate to the second from your current time.\n");

        /*printw("\n\n\n\n\n\t\t%s %d\n\n",mon[nextmonth],year+1900);*/
        printw("\n\t\t%s %d\n\n", mon[nextmonth], year+1900);
        printw("\t\tMon\tTue\tWens\tThur\tFri\tSat\tSun\n");
        printw("\t\t---------------------------------------------------\n\t\t");
        
        friday = 1;        /* reset friday counter */

        for( n = 1; n < day; n++ )
            printw("\t");

        offset = properties->occurence_plus_offset;
        found = 0;

        for( y = 1; y <= months[nextmonth]; y++ )
        {
            if( day == properties->occurence_day )        /* this is a friday or user specified day */
            {
                /* this is the 3rd firday of the month or user specified */
                if( friday++ == properties->occurence_in_month )
                {
                    found = 1;
                    /*printw("x");*/
                }
            }
            if( found == 1 )
            {
                if( offset-- == 0 )
                {
                    printw("EXPR");
                }

            }
            printw("%d\t",y);
            if( day++ == 7 )
            {
                day = 1;
                printw("\n\t\t---------------------------------------------------\n\t\t");
            }
        }

        printw("\n\n\t\t\t ");
        attron(A_STANDOUT);
        printw("<< Press any key or Q to quit >>\n");
        attroff(A_STANDOUT);

        character = getch();
       
        if( character == 'q' || character == 'Q' )
        {
          clear();
            
          return;
        }
    }
    
    clear();
    return;

} // void calendar(const struct _properties *properties)
