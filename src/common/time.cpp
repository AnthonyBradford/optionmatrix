/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: time.cpp of optionmatrix                                           */
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

int day_changed()
{
  time_t mytime;
  struct tm *my_tm;

  time(&mytime);
  my_tm = localtime(&mytime);

  static int tm_mday = 0;

  if( tm_mday == 0 )
  {
    tm_mday = my_tm->tm_mday;

  } else
  {
    if( tm_mday != my_tm->tm_mday )
    {
      return 1;
    }
  }

  return 0;

} // int day_changed()

int date_to_days_away(const int day, int month, int year)
{
    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    int curr_year  = my_tm->tm_year+1900;
    int curr_month = my_tm->tm_mon;
    int curr_day   = my_tm->tm_mday;

    int year_counter  = curr_year;
    int month_counter = curr_month;
    int day_counter   = curr_day;

    year += 2000;

    int x;
    int timeindays = 0;

    /* make from 0-11 */
    month -= 1;

    /*printw("day %d %d\tmonth %d %d\tyear %d %d\n",day,day_counter,month,month_counter,year,year_counter);*/

    if( year < curr_year )
    {
      return -1;
    }

    if( year == curr_year && month < curr_month )
    {
      return -1;
    }

    if( year == curr_year && month == curr_month && day < curr_day )
    {
      return -1;
    }

    if( curr_year == year && curr_month == month && curr_day == day )
    {
      return 0;
    }

    for(;;)
    {
        for(x = curr_month; x < 12; x++)
        {
          /* figure out if it is a leap year and adjust the month feb */
          if( ( (year_counter)%4 == 0 && (year_counter)%100 != 0 ) || (year_counter)%400 == 0 )
            {
              months[1] = 29;
            
            } else
            {
              months[1] = 28;
            }
        
          /* increment through the month */
          while( day_counter <= months[x] )
          {
            if(day == day_counter && month == month_counter && 
               year == year_counter)
            {
              /*printw("%s month = %d timeindays = %d\n",mon[month_counter],day_counter,timeindays);*/

              return timeindays;
            }

            day_counter++;
            timeindays++;
            /*printw("day = %d\tday_counter = %d\n",day,day_counter);*/
          }

          /*printw("%s month = %d timeindays = %d\n",mon[month_counter],day_counter,timeindays);*/
          /*printw("day %d %d\tmonth %d %d\tyear %d %d\n",day,day_counter,month,month_counter,year,year_counter);*/

          day_counter = 1;

          if( month_counter++ == 11 ) /* months 0-11 */
          {
            month_counter = 0;        /* set to Jan */
            year_counter++;
          }
        }
        curr_month = 0;
    }

} // int date_to_days_away(const int day, int month, int year)

/*
 * the greatest date this allow to be entered is 99 which is
 * the year 2099
 */
int validate_date(const int day, const int month, int year)
{
  /* extend feb 1 day during leap year */
  int validate_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  time_t mytime;
  struct tm *my_tm;

  time(&mytime);
  my_tm = localtime(&mytime);

  if( day < 1 )
  {
    return -1;
  }

  if( month > 12 || month < 1 )
  {
      return -1;
  }

  if( year < 0 )
  {
      return -1;
  } 

  if( year > 99 || year < 7 )
  {
      return -1;
  } 

  year += 2000;

  if( (my_tm->tm_year+1900) > year )
  {
    return -1;
  }

  if( year == (my_tm->tm_year+1900) )
  {
    if(month < (my_tm->tm_mon+1))
    {
      return -1;
    }

    if( month == (my_tm->tm_mon+1) )
    {
      if( day < my_tm->tm_mday )
      {
        return -1;
      }
    }
  }

  /*
   * figure out if it is a leap year and adjust the month feb
   */
  if( ( (year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
  {
    validate_months[1] = 29;

  } else
  {
    validate_months[1] = 28;
  }
  
  if( day > validate_months[month-1] )
  {
    return -1;
  }

  return 0;

} // int validate_date(const int day, const int month, int year)

int validate_time(const int hours, const int minutes, const int seconds)
{
  if( hours < 0 || hours > 23 )
  {
    return -1;
  }

  if( minutes < 0 || minutes > 59 )
  {
    return -1;
  }

  if( seconds < 0 || seconds > 59 )
  {
    return -1;
  }

  return 0;

} // int validate_time(const int hours, const int minutes, const int seconds)

char *decimal_date_to_real_date(double decimaltime)
{
    static char string[400];
    int daysahead;
    int counter1 = 0, counter2 = 0;
    int yy, mm;

    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    // add 1 decimal second..
    decimaltime += 0.000000032;

    double secondsintotoday = (double) ( ( (double)(my_tm->tm_hour)*
                                           (double)60*(double)60) +
                                           (double)(my_tm->tm_min*60) +
                                           (double) my_tm->tm_sec);
    /* 
     * 86400 seconds in 24 hours
     * add to the decimal time how much decimal time we are already
     * into today
     */
     decimaltime = decimaltime + (double) (
                    ( (double)secondsintotoday/(double)86400)/ 365
                                         );
    /* if the decimal date indicates today just return */
    if( decimaltime < (double) ((double) 1 / (double) 365) )
    {

        double hoursoftoday = ((double) decimaltime * 365) * 24;
        double dummy;
        double percentminutesofhour = modf(hoursoftoday,&dummy);

        int minutes = (int) (percentminutesofhour * 60);

        if( minutes >= 30 )
        {
          hoursoftoday -= 1;

          if( hoursoftoday < 0 )
            hoursoftoday = 0;
        }

        snprintf(string,sizeof(string),"%s %02d %02d %02.0f:%02d",mon[my_tm->tm_mon],my_tm->tm_mday,my_tm->tm_year+1900,hoursoftoday,(minutes == 60 ? 0 : minutes));

        return &string[0];
    }

    counter1 = my_tm->tm_mday;
    counter2 = 1;

    daysahead = (int) (365*decimaltime);

    double daysaheaddouble = (double) 365 * decimaltime;
    double dummy;
    double decimallasthours = modf(daysaheaddouble,&dummy);
    double lasthours = ((double)decimallasthours * (double) 24);
    double lastminutes = modf(lasthours,&dummy);
    int minutes = (int) (lastminutes * 60);
       
    int year  = my_tm->tm_year;
    int month = my_tm->tm_mon;
    int found = 0;
    
    while( !found )
    {
        /* figure out if it is a leap year and adjust the month feb */
        if( ( (year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
        {
            months[1] = 29;
            
        } else
        {
            months[1] = 28;
        }
        
        /* increment through the month */
        while( counter1 < months[month] )
        {
            if( counter2++ >= daysahead )
            {
                yy = year-100;
                mm = month;
                found = 1;

                if( minutes >= 30 )
                {
                  lasthours -= 1;

                  if( lasthours < 0 )
                    lasthours = 0;
                }

                /*snprintf(string,sizeof(string),"%s %02d %02d %02.0f:%02d",mon[mm],counter1+1,yy,lasthours,(minutes == 60 ? 0: minutes));*/
                snprintf(string,sizeof(string),"%s %02d %d %02.0f:%02d",mon[mm],counter1+1,yy+2000,lasthours,(minutes == 60 ? 0: minutes));

                break;
            }
            counter1++;
            
        } /* while(counter1<months[month]) */
        counter1 = 0;

        if( month++ == 11 ) /* months 0-11 */
        {
            month = 0;        /* set to Jan */
            year++;
        }
        
    } /* while(!found) */
    
    return &string[0];

} // char *decimal_date_to_real_date(double decimaltime)

void decimal_date_to_real_dates(double decimaltime, int *y, int *m, int *d, int *h, int *min, int *sec)
{
    int daysahead;
    int counter1 = 0, counter2 = 0;
    int yy, mm;

    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    // add 1 decimal second..
    decimaltime += 0.000000032;

    double secondsintotoday = (double) ( ( (double)(my_tm->tm_hour)*
                                           (double)60*(double)60) +
                                           (double)(my_tm->tm_min*60) +
                                           (double) my_tm->tm_sec);
    /* 
     * 86400 seconds in 24 hours
     * add to the decimal time how much decimal time we are already
     * into today
     */
     decimaltime = decimaltime + (double) (
                    ( (double)secondsintotoday/(double)86400)/ 365
                                         );
    /* if the decimal date indicates today just return */
    if( decimaltime < (double) ((double) 1 / (double) 365) )
    {
        double hoursoftoday = ((double) decimaltime * 365) * 24;
        double dummy;
        double percentminutesofhour = modf(hoursoftoday,&dummy);

        int minutes = (int) (percentminutesofhour * 60);
        double percentminutes = (percentminutesofhour * 60);
        double seconds = modf(percentminutes, &dummy);
        seconds *= 60;
        int int_seconds = (int) seconds;
        int_seconds--;
        if( int_seconds == -1 )
          int_seconds = 59;

        //printf("Current     %d:%d:%d\n",my_tm->tm_hour,my_tm->tm_min,my_tm->tm_sec);
        //printf("%s %02d %02d %02.0f:%02d:%02d\n",mon[my_tm->tm_mon],my_tm->tm_mday,my_tm->tm_year+1900,hoursoftoday,(minutes == 60 ? 0 : minutes),int_seconds);
        *y = my_tm->tm_year+1900;
        *m = my_tm->tm_mon;
        *d = my_tm->tm_mday;
        *h = hoursoftoday;
        *min = (minutes == 60 ? 0: minutes);
        *sec = int_seconds;
        return;
    }

    counter1 = my_tm->tm_mday;
    counter2 = 1;

    daysahead = (int) (365*decimaltime);

    double daysaheaddouble = (double) 365 * decimaltime;
    double dummy;
    double decimallasthours = modf(daysaheaddouble,&dummy);
    double lasthours = ((double)decimallasthours * (double) 24);
    double lastminutes = modf(lasthours,&dummy);
    int minutes = (int) (lastminutes * 60);

    double seconds = modf(lastminutes * 60, &dummy);
    seconds *= 60;
    int int_seconds = (int) seconds;
    int_seconds--;
    if( int_seconds == -1 )
      int_seconds = 59;
       
    int year  = my_tm->tm_year;
    int month = my_tm->tm_mon;
    int found = 0;
    
    while( !found )
    {
        /* figure out if it is a leap year and adjust the month feb */
        if( ( (year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
        {
            months[1] = 29;
            
        } else
        {
            months[1] = 28;
        }
        
        /* increment through the month */
        while( counter1 < months[month] )
        {
            if( counter2++ >= daysahead )
            {
                yy = year-100;
                mm = month;
                found = 1;

                //snprintf(string,sizeof(string),"%s %02d %d %02.0f:%02d",mon[mm],counter1+1,yy+2000,lasthours,(minutes == 60 ? 0: minutes));

                *y = yy + 2000;
                *m = mm;
                *d = counter1+1;
                *h = lasthours;
                *min = (minutes == 60 ? 0: minutes);
                *sec = int_seconds;
                //printf("Current     %d:%d:%d\n",my_tm->tm_hour,my_tm->tm_min,my_tm->tm_sec);
                break;
            }
            counter1++;
            
        } /* while(counter1<months[month]) */
        counter1 = 0;

        if( month++ == 11 ) /* months 0-11 */
        {
            month = 0;        /* set to Jan */
            year++;
        }
        
    } /* while(!found) */
    
    return;

} // void decimal_date_to_real_dates(double decimaltime, int *y, int *m, int *d, int *h, int *min, int *sec)

int decimal_date_to_int_month(const double decimaltime)
{
    int daysahead;
    int counter1 = 0;
    int counter2 = 0;
    int mm;

    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    daysahead = (int) (365*decimaltime);

    counter1 = my_tm->tm_mday;
    counter2 = 0;
    
    int year  = my_tm->tm_year;
    int month = my_tm->tm_mon;

    int found = 0;
    
    while( !found )
    {
        /* figure out if it is a leap year and adjust the month feb */
        if( ( (year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
        {
            months[1] = 29;
            
        } else
        {
            months[1] = 28;
        }
        
        /* increment through the month */
        while( counter1 < months[month] )
        {
            if( counter2++ == daysahead )
            {
                mm = month;
                /* dd = day;*/
                found = 1;
                
                /*snprintf(string,sizeof(string),"%s %02d %02d",mon[mm],counter1+1,yy);*/
                break;
            }
            counter1++;
            
        } /* while(counter1<months[month]) */
        counter1 = 0;

        if( month++ == 11 ) /* months 0-11 */
        {
            month = 0;        /* set to Jan */
            year++;
        }
        
    } /* while(!found) */
    
    return mm;

} // int decimal_date_to_int_month(const double decimaltime)

int decimal_date_to_int_year(const double decimaltime)
{
    int daysahead;
    int counter1 = 0;
    int counter2 = 0;
    int yy;

    time_t mytime;
    struct tm *my_tm;

    time(&mytime);
    my_tm = localtime(&mytime);

    daysahead = (int) (365*decimaltime);

    counter1 = my_tm->tm_mday;
    counter2 = 0;
    
    int year  = my_tm->tm_year;
    int month = my_tm->tm_mon;

    int found = 0;
    
    while( !found )
    {
        /* figure out if it is a leap year and adjust the month feb */
        if( ( (year+1900)%4 == 0 && (year+1900)%100 != 0 ) || (year+1900)%400 == 0 )
        {
            months[1] = 29;
            
        } else
        {
            months[1] = 28;
        }
        
        /* increment through the month */
        while( counter1 < months[month] )
        {
            if( counter2++ == daysahead )
            {
                yy = year-100;
                /* dd = day;*/
                found = 1;
                
                /*snprintf(string,sizeof(string),"%s %02d %02d",mon[mm],counter1+1,yy);*/
                break;
            }
            counter1++;
            
        } /* while(counter1<months[month]) */
        counter1 = 0;

        if( month++ == 11 ) /* months 0-11 */
        {
            month = 0;        /* set to Jan */
            year++;
        }
        
    } /* while(!found) */
    
    return yy;

} // int decimal_date_to_int_year(const double decimaltime)

double adjust_to_current_time(double t, const double day_offset)
{
  time_t mytime;
  struct tm *my_tm;

  time(&mytime);
  my_tm = localtime(&mytime);

  double expiration_time = 86400; /* 23 * 60 * 60 + 59 * 60 + 60 */

  t = t + day_offset;

  /* 86400 seconds in 24 hours */
  double k = (double) (
                 ( (double)(my_tm->tm_hour)*(double)60*(double)60) +
                   (double)(my_tm->tm_min*60) +
                   (double) my_tm->tm_sec);

  t = t - (double) ( (expiration_time-k) /(double)86400)/(double)365;
  
  return t;

} // double adjust_to_current_time(double t, const double day_offset)

double adjust_to_current_time_forward(double t, const double day_offset)
{
  time_t mytime;
  struct tm *my_tm;

  time(&mytime);
  my_tm = localtime(&mytime);

  double expiration_time = 86400; /* 23 * 60 * 60 + 59 * 60 + 60 */

  t = t + day_offset;

  /* 86400 seconds in 24 hours */
  double k = (double) (
                 ( (double)(my_tm->tm_hour)*(double)60*(double)60) +
                   (double)(my_tm->tm_min*60) +
                   (double) my_tm->tm_sec);

  t = t + (double) ( (expiration_time-k) /(double)86400)/(double)365;
  
  return t;

} // double adjust_to_current_time_forward(double t, const double day_offset)

/*
 * add user adjustable expiration time HH:MM:SS
 * minus out time into the current day
 */
double adjust_to_current_time_and_expr(int *tte, unsigned int expiration_time, const double day_offset)
{
  double temp;

  time_t mytime;
  struct tm *my_tm;

  time(&mytime);
  my_tm = localtime(&mytime);

  temp = (double) (*tte)/365;
  temp = temp + day_offset;

  /*   86400 seconds in 24 hours */
  double k = expiration_time - (double) (
                 ( (double)(my_tm->tm_hour)*(double)60*(double)60) +
                   (double)(my_tm->tm_min*60) +
                   (double) my_tm->tm_sec);

  temp = temp +(double) (k /(double)86400)/(double)365;
  
  return temp;

} // double adjust_to_current_time_and_expr(int *tte, unsigned int expiration_time, const double day_offset)

int expires(const int leg, const int monthsahead, const int skip_, struct _properties *properties)
{
    /*
     * avoid using difftime() due to having a 
     * 2038 Jan 19 03:14:07 bug on 32 bit systems
     */

    int **tte, **d, **em, **ey;

    if( leg == LEG1 )
    {

      tte = &properties->time_to_expiration;
      d   = &properties->days_to_expiration;
      em  = &properties->expiration_month;
      ey  = &properties->expiration_year;

    } else if( leg == LEG2 )
    {

      tte = &properties->time_to_expiration2;
      d   = &properties->days_to_expiration2;
      em  = &properties->expiration_month2;
      ey  = &properties->expiration_year2;

    }

    int skip = skip_;
    int monthcounter = 0;
    int x = 0, y, nextmonth = 0, friday, monthsout, temp;
    int counter1, counter2, day, overflow, year;
    int *timetoexpire, *dates, *emonths, *exyear;
    int retvalue;

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

    if( monthsahead )
    {
        monthsout = monthsahead;
        retvalue = monthsahead;
    }

    year = my_tm->tm_year;

    if(*tte)
        free(*tte);

    if(*d)
        free(*d);

    if(*em)
        free(*em);

    if(*ey)
        free(*ey);

    *tte = timetoexpire = (int *) calloc(monthsout+1,sizeof(int *));
    *d   = dates = (int *) calloc(monthsout+1,sizeof(int *));
    *em  = emonths = (int *) calloc(monthsout+1,sizeof(int *));
    *ey  = exyear = (int *) calloc(monthsout+1,sizeof(int *));

    monthsout += skip;

    /* count back to the first of the month and keep
       day names in sync */
    counter1 = my_tm->tm_mday;
    counter2 = 0;
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

    *timetoexpire = 0;  *dates = 0;  *emonths = 0;  *exyear = 0;

    while( counter1 <= months[my_tm->tm_mon] )
    {
        if( day == properties->occurence_day ) /* this is a friday or user specified day */
        {        
            /* this is the 3rd firday of the month or user specified */
            if( friday++ == properties->occurence_in_month )
            {
                if( counter1 >= my_tm->tm_mday )
                {
                    if( skip <= 0 && properties->optionscycle != 4 )
                    {
                        *emonths = my_tm->tm_mon;
                        emonths++;
                        *timetoexpire = counter1-my_tm->tm_mday+properties->occurence_plus_offset;
                        timetoexpire++;
                        *dates = counter1+properties->occurence_plus_offset;
                        dates++;
                        *exyear = ((year>=100)?(year-100):year);
                        exyear++;
                    } else
                    {
                        if( properties->optionscycle == 4 )
                        {

                            if( ( skip>0 ) &&
                                nextmonth == 0 /*&& year>=my_tm->tm_year+2*/)
                            {
                              --skip;

                            } else
                            {
                              monthsout++;
                            }
                        } else
                        {
                          if( skip > 0 )
                            --skip;
                        }

                    }
                    
                    monthsout--;
                }
            }
        }
        if( day++ == 7 )
            day = 1;

        counter1++;
    }
    monthcounter++;
    counter1 = my_tm->tm_mday;
    counter2 = 0;
    day = x;

    /* increment to the end of the month */
    while( counter1++ < months[my_tm->tm_mon] )
    {
        counter2++;
        if( day++ == 7 )
            day = 1;
    }
    nextmonth = my_tm->tm_mon;

    if( day++ == 7 )
        day = 1;

    *timetoexpire = counter2 + 2;
    
    /* overflow is the distance in days between expirations */
    overflow = 0;

    while( monthsout-- != 0 )
    {
        monthcounter++;

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
        
        friday = 1;        /* reset friday counter */
        for( y = 1; y <= months[nextmonth]; y++ )
        {
            if( day == properties->occurence_day )        /* this is a friday or user specified day */
            {
                /* this is the 3rd firday of the month or user specified */
                if( friday++ == properties->occurence_in_month )
                {
                    if( ( skip <= 0 && properties->optionscycle == 0 ) ||

                        /*   0,   1,   2,   3,   4,   5,   6,    7,   8,   9,  10,  11 */
                        /* Jan, Feb, Mar, Apr, May, Jun, Jul,  Aug, Sep, Oct, Nov, Dec */

                        /* January cycle */
                        ( skip <= 0 && properties->optionscycle == 1       &&
                            /*       Jan             Apr */  
                         ( ( nextmonth == 0 || nextmonth == 3       ||
                            /*       Jul             Oct */
                            nextmonth == 6 || nextmonth == 9       ||
                            ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year)
                           ) 
                           )
                        ) ||

                        /* Febuary cycle */
                        ( skip <= 0 && properties->optionscycle == 2       &&
                            /*       Feb             May */   
                         ( ( nextmonth == 1 || nextmonth == 4      ||
                            /*       Aug             Nov */
                            nextmonth == 7 || nextmonth == 10     ||
                                ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year)
                           ) 
                         )
                        ) ||

                        /* March cycle */
                        ( skip <= 0 && properties->optionscycle == 3       &&
                            /*       Mar             Jun */
                         ( ( nextmonth == 2 || nextmonth == 5      ||
                            /*       Sep             Dec */
                            nextmonth == 8 || nextmonth == 11     ||
                                  ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year)
                           ) 
                         )
                        ) ||

                        /* LEAPS */
                        ( skip <= 0 && properties->optionscycle == 4       &&
                         nextmonth == 0 /*&& year>=my_tm->tm_year+2*/)
                     )
                    {
                        *exyear = ((year>=100)?(year-100):year);
                        exyear++;

                        *emonths = nextmonth;
                        emonths++;
                    
                        *timetoexpire =* timetoexpire+y+overflow-2+properties->occurence_plus_offset;

                        temp =* timetoexpire;
                        timetoexpire++;
                        *timetoexpire = temp;
                        *timetoexpire =* timetoexpire+1-properties->occurence_plus_offset;

                        overflow = 0;

                        *dates = y + properties->occurence_plus_offset;
                        dates++;
                    } else
                    {
                        *timetoexpire =* timetoexpire+y+overflow-1;
                        overflow = 0;

                        if( properties->optionscycle == 1 )
                        {
                            if( ( skip > 0 ) && /* Jan, Apr, Jul, Oct */
                                ( nextmonth == 0 || nextmonth == 3 ||
                                nextmonth == 6 || nextmonth == 9 ||
                                ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year) )
                              )
                            {
                                --skip;

                            } else
                            {
                                monthsout++;
                            }
                        } else if( properties->optionscycle == 2 )
                        {
                            if( ( skip>0 ) && /* Feb, May, Aug, Nov */
                                 ( nextmonth == 1 || nextmonth == 4      ||
                                 nextmonth == 7 || nextmonth == 10     ||
                                 ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year) )
                              )
                            {
                              --skip;

                            } else
                            {
                              monthsout++;
                            }

                        }  else if( properties->optionscycle == 3 )
                        {
                            if( ( skip>0 ) && /* Mar, Jun, Sep, Dec */
                                 ( nextmonth == 2 || nextmonth == 5      ||
                                 nextmonth == 8 || nextmonth == 11     ||
                                 ( my_tm->tm_mon+1 == nextmonth && year == my_tm->tm_year) )
                              )
                            {
                              --skip;

                            } else
                            {
                              monthsout++;
                            }

                        } else if( properties->optionscycle == 0 )
                        {
                            skip--;

                        } else if( properties->optionscycle == 4 )
                        {

                            if( ( skip > 0 ) &&
                                nextmonth == 0 /*&& year>=my_tm->tm_year+2*/)
                            {
                              --skip;

                            } else
                            {
                              monthsout++;
                            }
                        }
                    }
                }
            }
            
            if(day++ == 7)
                day = 1;
            
            if( friday > properties->occurence_in_month )
                overflow++;
        }
    }

    *timetoexpire = -1;
    *dates = -1;
    *emonths = -1;        /* can't use NULL because *emonths=0 equals Jan */
    *exyear = -1;

    if( leg == LEG1 )
    {
      /* preserve the head of the lists */
      properties->start_time_to_expiration = properties->time_to_expiration;
      properties->start_days_to_expiration = properties->days_to_expiration;
      properties->start_expiration_month = properties->expiration_month;
      properties->start_expiration_year = properties->expiration_year;

    } else if( leg == LEG2 )
    {
      /* preserve the head of the lists */
      properties->start_time_to_expiration2 = properties->time_to_expiration2;
      properties->start_days_to_expiration2 = properties->days_to_expiration2;
      properties->start_expiration_month2 = properties->expiration_month2;
      properties->start_expiration_year2 = properties->expiration_year2;

    }

    return retvalue;

} // int expires(const int leg, const int monthsahead, const int skip_, struct _properties *properties)
