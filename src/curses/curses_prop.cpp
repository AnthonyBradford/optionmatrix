/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_prop.cpp of optionmatrix                                    */
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

int props(struct _properties *properties,struct _properties *future_properties)
{
    int ret;
    int row = 2;
    char inputstring[200]  = { 0 };
    int precision;
    int occurance_in_month;
    int occurence_plus_offset;
    int occurence_day;
    int expiration_time,expiration_hour,expiration_minute,expiration_second;

    /* if the user changed expiration times we have to recalc expiration dates */
    bool changedExpiration = 0;

    clear();

    attron(A_STANDOUT);
    printw("AdvProperties Page / ENTER makes no change / Press ENTER to continue\n\n");
    attroff(A_STANDOUT);

    /******************************************************************/
    move(row,0);
    printw("CALENDAR OPTIONS EXPIRATIONS\n");
    row += 2;
    move(row,0);
    printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[properties->occurence_day-1]);

    if( properties->occurence_day == 7 )
    {
         printw("0\n");
    } else
    {
         printw("%d\n", properties->occurence_day);
    }

    for(;;)
    {
         ret = -1;
         occurence_day = -1;
    
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &occurence_day);
             
         if( occurence_day >= 0 && occurence_day <= 7 && ret == 1 && inputstring[0] != ' ' )
         {
             ret = 0;
             if( occurence_day == 0 )
             {
                  properties->occurence_day = 7;
             }
             else
             {
                  properties->occurence_day = occurence_day;
             }
             
             move(row,0);
             printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[properties->occurence_day-1]);

             if( properties->occurence_day == 7 )
             {
                  printw("0\n");
             } else
             {
                  printw("%d\n", properties->occurence_day);
             }             
             refresh();

             changedExpiration = 1;
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[properties->occurence_day-1]);

             if( properties->occurence_day == 7 )
             {
                  printw("0\n");
             } else
             {
                  printw("%d\n", properties->occurence_day);
             }             
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
        
    /******************************************************************/
    move(++row,0);
    printw("1st, 2nd, 3rd or 4th occurance of the month : %d", properties->occurence_in_month);

    for(;;)
    {
         ret = -1;
         occurance_in_month = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &occurance_in_month);
         
         if( occurance_in_month > 0 && occurance_in_month <= 4 && ret == 1 && inputstring[0] != ' ' )
         {
             ret = 0;
             properties->occurence_in_month = occurance_in_month;
             
             move(row,0);
             printw("1st, 2nd, 3rd or 4th occurance of the month : %d\n", properties->occurence_in_month);
             refresh();

             changedExpiration = 1;
             
             break;

         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("1st, 2nd, 3rd or 4th occurance of the month : %d\n", properties->occurence_in_month);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    
    /******************************************************************/
    if( properties->occurence_in_month != 4 )
    {
      move(++row,0);
      printw("Occurence plus offset                       : %d\n", properties->occurence_plus_offset);

      for(;;)
      {
         ret = -1;
         occurence_plus_offset = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &occurence_plus_offset);
         
         if( occurence_plus_offset >= 0 && occurence_plus_offset <= 6 && ret == 1 && inputstring[0] != ' ' )
        {
             ret = 0;
             properties->occurence_plus_offset = occurence_plus_offset;

             move(row,0);
             printw("Occurence plus offset                       : %d\n", properties->occurence_plus_offset);
             refresh();

             changedExpiration = 1;
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);             
             printw("Occurence plus offset                       : %d\n", properties->occurence_plus_offset);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
      }
    } else
    {
      properties->occurence_plus_offset = 0;
    }

    /******************************************************************/
    move(++row,0);
    printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", properties->expiration_hour,properties->expiration_minute,properties->expiration_second);

    for(;;)
    {
         ret = -1;
         expiration_hour = -1;
         expiration_minute = -1;
         expiration_second = -1;
         expiration_time = 0;
         
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d:%d:%d", &expiration_hour,&expiration_minute,&expiration_second);

         if( ret == 2 && inputstring[0] != ' ' )
         {
           move(row,55);
           printw("Must enter seconds");
           continue;
         }

         if( expiration_hour != -1 && expiration_minute != -1 && expiration_second != -1 && ret == 3 && inputstring[0] != ' ' )
         {
             if( validate_time(expiration_hour,expiration_minute,expiration_second) != 0 )
             {
               continue;
             }

             if( expiration_hour >= 0 )
             {
                  properties->expiration_hour = expiration_hour;
                  expiration_time += ((expiration_hour * 60) * 60);
             }
             if( expiration_minute >= 0 )
             {
                  properties->expiration_minute = expiration_minute;
                  expiration_time += (expiration_minute * 60);
             }
             if( expiration_second >= 0 )
             {
                  properties->expiration_second = expiration_second;
                  expiration_time += expiration_second;
             }
             
             properties->expiration_time = expiration_time;

             /*move(row,55);
             printw(" = %d seconds in the day\n", properties->expiration_time);*/

             move(row,0);
             printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", properties->expiration_hour,properties->expiration_minute,properties->expiration_second);
             refresh();

             changedExpiration = 1;

             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", properties->expiration_hour,properties->expiration_minute,properties->expiration_second);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    /******************************************************************/
    /* char *optionscycle[] = { "All", "Jan", "Feb", "Mar", "LEAPS" }; */

    move(++row,0);

    printw("Options month cycle                         : %d\n\n", properties->optionscycle);
    printw("            %s %d=All", (properties->optionscycle == 0 ? "-->" : "   "),0);
    printw("     %s %d=LEAPS\n", (properties->optionscycle == 4 ? "-->" : "   "),4);
    printw("            %s %d=Jan\n", (properties->optionscycle == 1 ? "-->" : "   "),1);
    printw("            %s %d=Feb\n", (properties->optionscycle == 2 ? "-->" : "   "),2);
    printw("            %s %d=Mar\n", (properties->optionscycle == 3 ? "-->" : "   "),3);

    for(;;)
    {
         ret = -1;
         int type = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &type);

         if( type >= 0 && type <= 4 && inputstring[0] != ' ' )
         {
             move(row,41);
             printw("%d\n", type);
             properties->optionscycle = type;

             move(row,0);

             printw("Options month cycle                         : %d\n\n", properties->optionscycle);
             printw("            %s %d=All", (properties->optionscycle == 0 ? "-->" : "   "),0);
             printw("     %s %d=LEAPS\n", (properties->optionscycle == 4 ? "-->" : "   "),4);
             printw("            %s %d=Jan\n", (properties->optionscycle == 1 ? "-->" : "   "),1);
             printw("            %s %d=Feb\n", (properties->optionscycle == 2 ? "-->" : "   "),2);
             printw("            %s %d=Mar\n", (properties->optionscycle == 3 ? "-->" : "   "),3);
             refresh();

             changedExpiration = 1;
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Options month cycle                         : %d\n\n", properties->optionscycle);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    /******************************************************************/
    /* Futures stuff */
    row += 7;

    move(row,0);
    printw("CALENDAR FUTURES EXPIRATIONS\n");
    row += 2;
    move(row,0);
    printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[future_properties->occurence_day-1]);

    if( future_properties->occurence_day == 7 )
    {
         printw("0\n");
    } else
    {
         printw("%d\n", future_properties->occurence_day);
    }

    for(;;)
    {
         ret = -1;
         occurence_day = -1;
    
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &occurence_day);
             
         if( occurence_day >= 0 && occurence_day <= 7 && ret == 1 && inputstring[0] != ' ' )
         {
             ret = 0;
             if( occurence_day == 0 )
             {
                  future_properties->occurence_day = 7;
             }
             else
             {
                  future_properties->occurence_day = occurence_day;
             }
             
             move(row,0);
             printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[future_properties->occurence_day-1]);

             if( future_properties->occurence_day == 7 )
             {
                  printw("0\n");
             } else
             {
                  printw("%d\n", future_properties->occurence_day);
             }             
             refresh();

             changedExpiration = 1;
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Expiration weekday = %s [Sun-Sat,0-6]      : ", weekdays[future_properties->occurence_day-1]);

             if( future_properties->occurence_day == 7 )
             {
                  printw("0\n");
             } else
             {
                  printw("%d\n", future_properties->occurence_day);
             }             
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    /******************************************************************/

    move(++row,0);
    printw("1st, 2nd, 3rd or 4th occurance of the month : %d", future_properties->occurence_in_month);

    for(;;)
    {
         ret = -1;
         occurance_in_month = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &occurance_in_month);
         
         if( occurance_in_month > 0 && occurance_in_month <= 4 && ret == 1 && inputstring[0] != ' ' )
         {
             ret = 0;
             future_properties->occurence_in_month = occurance_in_month;
             
             move(row,0);
             printw("1st, 2nd, 3rd or 4th occurance of the month : %d\n", future_properties->occurence_in_month);
             refresh();

             changedExpiration = 1;
             
             break;

         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("1st, 2nd, 3rd or 4th occurance of the month : %d\n", future_properties->occurence_in_month);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    
    /******************************************************************/
    if( future_properties->occurence_in_month != 4 )
    {
      move(++row,0);
      printw("Occurence plus offset                       : %d\n", future_properties->occurence_plus_offset);

      for(;;)
      {
         ret = -1;
         occurence_plus_offset = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &occurence_plus_offset);
         
         if( occurence_plus_offset >= 0 && occurence_plus_offset <= 6 && ret == 1 && inputstring[0] != ' ' )
         {
             ret = 0;
             future_properties->occurence_plus_offset = occurence_plus_offset;

             move(row,0);
             printw("Occurence plus offset                       : %d\n", future_properties->occurence_plus_offset);
             refresh();

             changedExpiration = 1;
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);             
             printw("Occurence plus offset                       : %d\n", future_properties->occurence_plus_offset);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
      }
    } else
    {
      future_properties->occurence_plus_offset = 0;
    }

    /******************************************************************/
    move(++row,0);
    printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", future_properties->expiration_hour,future_properties->expiration_minute,future_properties->expiration_second);

    for(;;)
    {
         ret = -1;
         expiration_hour = -1;
         expiration_minute = -1;
         expiration_second = -1;
         expiration_time = 0;
         
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d:%d:%d", &expiration_hour,&expiration_minute,&expiration_second);

         if( ret == 2 && inputstring[0] != ' ' )
         {
           move(row,55);
           printw("Must enter seconds");
           continue;
         }

         if( expiration_hour != -1 && expiration_minute != -1 && expiration_second != -1 && ret == 3 && inputstring[0] != ' ' )
         {
             if( validate_time(expiration_hour,expiration_minute,expiration_second) != 0 )
             {
               continue;
             }

             if( expiration_hour >= 0 )
             {
                  future_properties->expiration_hour = expiration_hour;
                  expiration_time += ((expiration_hour * 60) * 60);
             }
             if(expiration_minute >= 0)
             {
                  future_properties->expiration_minute = expiration_minute;
                  expiration_time += (expiration_minute * 60);
             }
             if( expiration_second >= 0 )
             {
                  future_properties->expiration_second = expiration_second;
                  expiration_time += expiration_second;
             }
             
             future_properties->expiration_time = expiration_time;

             move(row,0);
             printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", future_properties->expiration_hour,future_properties->expiration_minute,future_properties->expiration_second);
             refresh();

             changedExpiration = 1;

             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Expiration time on expiration day [HH:MM:SS]: %02d:%02d:%02d\n", future_properties->expiration_hour,future_properties->expiration_minute,future_properties->expiration_second);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    /* End Futures stuff */
    /******************************************************************/

    /* clear screen top of screen */
    clear();
    row = -1;
    
    move(++row,0);
    printw("Floating point precision                    : %d\n", properties->precision);

    for(;;)
    {
         ret = -1;
         precision = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &precision);

         if( precision >= 0 && ret == 1 && inputstring[0] != ' ' )
         {
             properties->precision = precision;

             move(row,0);
             printw("Floating point precision                    : %d\n", properties->precision);
             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Floating point precision                    : %d\n", properties->precision);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    printw("\n");

    /******************************************************************/

    move(++row,0);
    
    printw("Real time bleeding / updating  [1=On,0=Off] : %d\n", properties->realTimeBleeding);

    for(;;)
    {
         ret = -1;
         int realTimeBleeding = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &realTimeBleeding);

         if( realTimeBleeding >= 0 && realTimeBleeding <= 1 && ret == 1 && inputstring[0] != ' ' )
         {
             properties->realTimeBleeding = realTimeBleeding;

             move(row,0);

             printw("Real time bleeding / updating  [1=On,0=Off] : %d\n", properties->realTimeBleeding);
             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("Real time bleeding / updating  [1=On,0=Off] : %d\n", properties->realTimeBleeding);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    /******************************************************************/
    move(++row,0);
    
    printw("Updating delay in seconds                   : %d\n", properties->updatedelayseconds);

    for(;;)
    {
         ret = -1;
         int updatedelayseconds = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &updatedelayseconds);

         if( updatedelayseconds > 0 && ret == 1 && inputstring[0] != ' ' )
         {
             properties->updatedelayseconds = updatedelayseconds;

             move(row,0);

             printw("Updating delay in seconds                   : %d\n", properties->updatedelayseconds);

             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("Updating delay in seconds                   : %d\n", properties->updatedelayseconds);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    /******************************************************************/

    char stringtemp2[200];
    memset(stringtemp2,(int) 0,sizeof(stringtemp2));
    
    int scounter;
    for( scounter=0; scounter < (sizeofstrike_control/(signed)(sizeof(struct _strike_control))); scounter++ )
    {
      strncat(stringtemp2,strike_control[scounter].des,sizeof(stringtemp2)-1);
      strncat(stringtemp2," ",sizeof(stringtemp2)-1);
    }

    move(++row,0);
    printw("Strike increments %19s [0-%d] : %d\n", stringtemp2,
            (int) (sizeofstrike_control/(sizeof(struct _strike_control))-1),
            properties->strikestoogle);

    for(;;)
    {
         ret = -1;
         int strikestyle = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &strikestyle);

         if( strikestyle >= 0 && 
            (strikestyle<=(sizeofstrike_control/(signed)(sizeof(struct _strike_control))-1)) && 
            ret == 1 && inputstring[0] != ' ' )
         {
             properties->strikestoogle = strikestyle;

             move(row,0);

             printw("Strike increments %19s [0-%d] : %d\n", stringtemp2,
                     (int) (sizeofstrike_control/(sizeof(struct _strike_control))-1),
                     properties->strikestoogle);

             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("Strike increments %19s [0-%d] : %d\n", stringtemp2,
                     (int) (sizeofstrike_control/(sizeof(struct _strike_control))-1),
                     properties->strikestoogle);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    /******************************************************************/

    move(++row,0);

    printw("Highlight in the money options [1=On,0=Off] : %d\n", properties->highlightInTheMoney);

    for(;;)
    {
         ret = -1;
         int highlightInTheMoney = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &highlightInTheMoney);

         if( highlightInTheMoney >= 0 && highlightInTheMoney <= 1 && ret == 1 && inputstring[0] != ' ' )
         {
             properties->highlightInTheMoney = highlightInTheMoney;

             move(row,0);
             
             printw("Highlight in the money options [1=On,0=Off] : %d\n", properties->highlightInTheMoney);

             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("Highlight in the money options [1=On,0=Off] : %d\n", properties->highlightInTheMoney);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    /******************************************************************/
    clear();
    row = -1;

    move(++row,0);
    printw("BEGIN - ONLY FOR NON-STEP METHODS\n\n");
    row += 2;
    
    const int num_integration = sizeofintegration_method/sizeof(struct numerical_integration_method);

    printw("Cumulative Norm Distribution calculation 0-%d: %d\n", num_integration-1,properties->integration_type);
    
    int x;
    for( x = 0; x < num_integration; x++ )
    {
      printw("            %s %d=%s\n", (properties->integration_type==x?"-->":"   "),x,integration_method[x].des);
    }

    for(;;)
    {
         ret = -1;
         int type = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s",inputstring);
         ret = sscanf(inputstring,"%d", &type);

         if( (type >= 0 || type < num_integration) && ret == 1 && inputstring[0] != ' ' )
         {
             move(row,41);
             printw("%d\n", type);
             properties->integration_type = type;

             move(row,0);
             printw("Cumulative Norm Distribution calculation 0-%d: %d\n", num_integration-1,properties->integration_type);

             for( x = 0; x < num_integration; x++ )
             {

               printw("            %s %d=%s\n", (properties->integration_type == x ? "-->" : "   "),x,integration_method[x].des);

             }

             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Cumulative Norm Distribution calculation 0-%d: %d\n", num_integration-1,properties->integration_type);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    row += num_integration+1;

    /******************************************************************/

    for( x = 0; x < num_integration; x++ )
    {
      if( integration_method[x].method == 0 )
         continue;

      move(++row,0);
      printw("%s rule/method integration resolution: %d\n", integration_method[x].des,integration_method[x].resolution);

      for(;;)
      {
         ret = -1;
         int resolution = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &resolution);

         if( resolution > 0 && ret == 1 && inputstring[0] != ' ' )
         {
             if( integration_method[x].UpperLimit != 0 )
             {
               if( resolution>integration_method[x].UpperLimit )
                  continue;
             }

             if( (resolution % 2) != 0 && integration_method[x].allowOnlyEven == 1) 
             {
                  resolution += 1;
                  move(row,41);
                  printw("%d", resolution);
             }

             integration_method[x].resolution = resolution;

             move(row,0);
             printw("%s rule/method integration resolution: %d\n", integration_method[x].des,integration_method[x].resolution);

             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("%s rule/method integration resolution: %d\n", integration_method[x].des,integration_method[x].resolution);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
      }
    }
    row++;
    /******************************************************************/

    move(++row,0);
    printw("Distribution variance                       : %f\n", properties->distribution_variance);

    for(;;)
    {
         ret = -1;
         double variance = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%lf", &variance);

         if( ret == 1 && inputstring[0] != ' ' )
         {
             properties->distribution_variance = variance;

             move(row,0);
             printw("Distribution variance                       : %f\n", properties->distribution_variance);
             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Distribution variance                       : %f\n", properties->distribution_variance);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }

    /******************************************************************/

    move(++row,0);
    printw("Distribution mean                           : %f\n", properties->distribution_mean);

    for(;;)
    {
         ret = -1;
         double mean = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%lf", &mean);

         if( ret == 1 && inputstring[0] != ' ' )
         {
             properties->distribution_mean = mean;

             move(row,0);
             printw("Distribution mean                           : %f\n", properties->distribution_mean);
             refresh();
             
             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);
             printw("Distribution mean                           : %f\n", properties->distribution_mean);
             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    row += 2;

    /******************************************************************/

    move(row,0);
    printw("Distribution type                           : %d\n\n", properties->distribution_type);

    const int numberofdistributions = sizeofdistribution_list/sizeof(distribution_list[0]);
    int counter;

    for( counter = 0; counter < numberofdistributions; counter++ )
    {
      printw("            %s %d=%s\n",(properties->distribution_type == counter ? "-->" : "   "),counter,distribution_list[counter].des);
    }

    for(;;)
    {
         ret = -1;
         int type = -1;
         memset(inputstring,(int) ' ',sizeof(inputstring));
         move(row,46);
         scanw("%10s", inputstring);
         ret = sscanf(inputstring,"%d", &type);

         if( type >= 0 && type < numberofdistributions && inputstring[0] != ' ' )
         {
             move(row,41);
             printw("%d\n",type);
             
             properties->distribution_type = type;
             
             move(row,0);
             
             printw("Distribution type                           : %d\n\n", properties->distribution_type);

             for( counter = 0; counter < numberofdistributions; counter++)
             {
                  printw("            %s %d=%s\n", (properties->distribution_type == counter ? "-->" : "   "),counter,distribution_list[counter].des);
             }

             refresh();

             timespec sleepValue = { 0 };
             sleepValue.tv_sec = 1;
             if( nanosleep(&sleepValue, NULL) < 0 )
             {
               printw("nanosleep() failed\n");
               refresh();
             }

             break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row,0);

             printw("Distribution type                           : %d\n\n", properties->distribution_type);

             refresh();
             
             /* the user just entered ENTER
                so just use previous value no change */
             break;
         }
    }
    row += 5;
    move(row,0);
    printw("END - ONLY FOR NON-STEP METHODS\n");
    
    /*
    clear();
    row = 0;
    move(row,0);

    // ******************************************************************
    printw("BEGIN - ONLY FOR STEPPING METHODS\n\n");

    row += 2;

    int optiontype;
    for( optiontype = 0; optiontype<(sizeofoption_algorithms/(signed)sizeof(struct option_algorithm)); optiontype++ )
    {
      if( option_algorithms[optiontype].supportSteps == 1 )
      {
         printw("%-20s number of steps        : %d\n", option_algorithms[optiontype].des,option_algorithms[optiontype].steps); clrtoeol();

          for(;;)
          {
            ret = -1;
            int type =-1;
            memset(inputstring,(int) ' ',sizeof(inputstring));
            move(row,46);
            scanw("%10s",inputstring);
            ret = sscanf(inputstring,"%d",&type);

            if( type >= 0 && inputstring[0] != ' ' )
            {
              move(row,41);
              printw("%d\n", type);
             
              option_algorithms[optiontype].steps = type;
             
              move(row++,0);

              printw("%-20s number of steps        : %d\n", option_algorithms[optiontype].des,option_algorithms[optiontype].steps); clrtoeol();             

              refresh();
              
              break;
             
         } else if( ret == 0 || ret == -1 || inputstring[0] == ' ' )
         {
             move(row++,0);

             printw("%-20s number of steps        : %d\n", option_algorithms[optiontype].des,option_algorithms[optiontype].steps); clrtoeol();             

             refresh();
             
             // the user just entered ENTER
             // so just use previous value no change
             break;
         }
      }
     }
    }
    move(row++,0);
    printw("END - ONLY FOR STEPPING METHODS\n");
    // ******************************************************************

    */
    refresh();

    if( changedExpiration == 1 )
    {
         return 1;
         
    } else
    {
         return 0;
    }

} // int props(struct _properties *properties,struct _properties *future_properties)
