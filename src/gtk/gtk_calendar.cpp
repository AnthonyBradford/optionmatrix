/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_calendar.cpp of optionmatrix                                   */
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
#include <gtk/gtk.h>

#include "gtk_main.h"

void on_calendar1_day_selected( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_calendar1_day_selected()\n");

  guint day, month, year;
  gtk_calendar_get_date (GTK_CALENDAR(properties->GtkInfo.calendar1), &year, &month, &day);

  int daysaway = date_to_days_away(day,month+1,year-2000);

  g_print("daysaway = %d, day = %d, month = %d, year = %d\n", daysaway, day, month, year);

  if(daysaway < 0)
  {
    properties->data.t[properties->calendarSelected] = 0;
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelCalendar),"Please select date greater than current");

  } else
  {
    time(&properties->starttime);

    int dummy;
    int hour;
    int minute;
    int seconds;

    switch(properties->calendarSelected)
    {
    case 0:
      decimal_date_to_real_dates(properties->data.t[properties->calendarSelected] - properties->data.te, &dummy, &dummy, &dummy, &hour, &minute, &seconds);
      break;

    case 1:
      decimal_date_to_real_dates(properties->data.t[properties->calendarSelected] - properties->data.te2, &dummy, &dummy, &dummy, &hour, &minute, &seconds);
      break;

    case 2:
      decimal_date_to_real_dates(properties->data.t[properties->calendarSelected] - properties->data.te3, &dummy, &dummy, &dummy, &hour, &minute, &seconds);
      break;

    default:
      g_print("on_calendar1_day_selected(): Bad calendarSelected switch\n");
      break;
    }

    properties->data.t[properties->calendarSelected] = adjust_to_current_time_forward( (double) --daysaway / (double) 365, 0.0 );

    double k = (double) (
                 ( (double)(hour)*(double)60*(double)60) +
                 (double)(minute*60) + (double)seconds);

    properties->data.t[properties->calendarSelected] += (double) ( (k) /(double)86400)/(double)365;
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelCalendar),"");
  }

} // void on_calendar1_day_selected( GtkWidget *widget, struct _properties *properties )

int on_dialogCalendar_delete_event( GtkWidget *widget, GdkEvent *event, const struct _properties *properties )
{
  g_print("on_dialogCalendar_delete_event()\n");
  gtk_widget_hide(properties->GtkInfo.dialogCalendar);

  return TRUE;
}

void on_buttonCalendar_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_buttonCalendar_clicked():\n");

  gtk_window_set_title(GTK_WINDOW(properties->GtkInfo.dialogCalendar), "Select Date for Expr");
  gtk_window_set_icon(GTK_WINDOW(properties->GtkInfo.dialogCalendar), create_pixbuf("images/2.png"));

  int year;
  int month;
  int day;
  int hour;
  int minute;
  int seconds;

  properties->calendarSelected = 0;

  decimal_date_to_real_dates(properties->data.t[properties->calendarSelected], &year, &month, &day, &hour, &minute, &seconds);

  gtk_calendar_select_month(GTK_CALENDAR(properties->GtkInfo.calendar1), month, year);
  gtk_calendar_select_day(GTK_CALENDAR(properties->GtkInfo.calendar1), day);

  gtk_dialog_run(GTK_DIALOG(properties->GtkInfo.dialogCalendar));

} // void on_buttonCalendar_clicked( GtkWidget *widget, struct _properties *properties )

void on_buttonCalendar2_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_buttonCalendar2_clicked():\n");

  gtk_window_set_title(GTK_WINDOW(properties->GtkInfo.dialogCalendar), "Select Date");
  gtk_window_set_icon(GTK_WINDOW(properties->GtkInfo.dialogCalendar), create_pixbuf("images/2.png"));

  int year;
  int month;
  int day;
  int hour;
  int minute;
  int seconds;

  properties->calendarSelected = 1;

  decimal_date_to_real_dates(properties->data.t[1], &year, &month, &day, &hour, &minute, &seconds);

  gtk_calendar_select_month(GTK_CALENDAR(properties->GtkInfo.calendar1), month, year);
  gtk_calendar_select_day(GTK_CALENDAR(properties->GtkInfo.calendar1), day);

  gtk_dialog_run(GTK_DIALOG(properties->GtkInfo.dialogCalendar));

} // void on_buttonCalendar2_clicked( GtkWidget *widget, struct _properties *properties )

void on_buttonCalendar3_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_buttonCalendar3_clicked():\n");

  gtk_window_set_title(GTK_WINDOW(properties->GtkInfo.dialogCalendar), "Select Date for Expr");
  gtk_window_set_icon(GTK_WINDOW(properties->GtkInfo.dialogCalendar), create_pixbuf("images/2.png"));

  int year;
  int month;
  int day;
  int hour;
  int minute;
  int seconds;

  properties->calendarSelected = 2;

  decimal_date_to_real_dates(properties->data.t[2], &year, &month, &day, &hour, &minute, &seconds);

  gtk_calendar_select_month(GTK_CALENDAR(properties->GtkInfo.calendar1), month, year);
  gtk_calendar_select_day(GTK_CALENDAR(properties->GtkInfo.calendar1), day);

  gtk_dialog_run(GTK_DIALOG(properties->GtkInfo.dialogCalendar));

} // void on_buttonCalendar3_clicked( GtkWidget *widget, struct _properties *properties )
