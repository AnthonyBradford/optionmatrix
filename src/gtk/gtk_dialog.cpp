/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_dialog.cpp of optionmatrix                                     */
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

void on_dialogProperties_ok( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_dialogProperties_ok():\n");;
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTimeError),"");
  gtk_widget_hide(properties->GtkInfo.labelTimeError);
  properties->occurence_day = gtk_combo_box_get_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxWeekday));

  if( properties->occurence_day == 0 )
  {
    properties->occurence_day = 7;
  }

  properties->occurence_in_month = gtk_combo_box_get_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxOccurance)) + 1;
  properties->occurence_plus_offset  = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDayOffset));
  //g_print("entry_get_text = %s\n",gtk_entry_get_text (GTK_ENTRY (entryExpirationTime)));

  const gchar *enteredTime = gtk_entry_get_text (GTK_ENTRY (properties->GtkInfo.entryExpirationTime));

  int expiration_time = 0;
  int expiration_hour = -1;
  int expiration_minute = -1;
  int expiration_second = -1;
  bool timeIsGood = false;
  int ret = sscanf(enteredTime,"%d:%d:%d",&expiration_hour,&expiration_minute,&expiration_second);

  /* User entered hour, minute, seconds */
  if( ret == 3 && expiration_hour != -1 && expiration_minute != -1 && expiration_second != -1 )
  {
    if( validate_time(expiration_hour,expiration_minute,expiration_second) == 0 )
    {
      //g_print("Time is valid\n");
      timeIsGood = true;
    } else
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTimeError),"Invalid Time Entered");
      gtk_widget_show(properties->GtkInfo.labelTimeError);
      //g_print("BAD Time entered 1\n");
    }
  }
  /* User entered hour, minute, we will default seconds to zero  */
  if( ret == 2 && expiration_hour != -1 && expiration_minute != -1 && expiration_second == -1 )
  {
    expiration_second = 0;

    if( validate_time(expiration_hour,expiration_minute,expiration_second) == 0 )
    {
      //g_print("Time is valid\n");
      timeIsGood = true;
    } else
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTimeError),"Invalid Time Entered");
      gtk_widget_show(properties->GtkInfo.labelTimeError);
      //g_print("BAD Time entered 2\n");
    }
  }

  if( timeIsGood == true )
  {
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

    gtk_widget_hide(properties->GtkInfo.dialogProperties);

    expires(LEG1,30,properties->skipmonth,properties);
    expires(LEG2,30,properties->skipmonth2,properties);

    setup_tree_view(properties);

    show_label_expirations(properties);

  } // if( timeIsGood == true )

} // void on_dialogProperties_ok( GtkWidget *widget, struct _properties *properties )

void on_dialogProperties_cancel( GtkWidget *widget, const struct _properties *properties )
{
  g_print("on_dialogProperties_cancel():\n");
  gtk_widget_hide(properties->GtkInfo.dialogProperties);
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTimeError),"");

} // void on_dialogProperties_cancel( GtkWidget *widget, const struct _properties *properties )

int on_dialogProperties_delete_event( GtkWidget *widget, const struct _properties *data )
{
  g_print("on_dialogProperties_delete_event()\n");
  gtk_widget_hide(properties.GtkInfo.dialogProperties);

  return TRUE;

} // int on_dialogProperties_delete_event( GtkWidget *widget, const struct _properties *data )

void on_buttonProperties_clicked( GtkWidget *widget, const struct _properties *properties )
{
  g_print("on_buttonProperties_clicked():\n");

  int index;
  struct elementList listWeekdays[7];

  int occurence_day = (properties->occurence_day == 7 ? 0 :  properties->occurence_day);

  const char *const weekDays[]= { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
  for(index = 0; index < 7; index++)
  {
    snprintf(listWeekdays[index].elementName,sizeof(listWeekdays[index].elementName),"%s", weekDays[index]);
    //g_print("%s\n",listWeekdays[index].elementName);
  }
  set_up_combobox_with_array2(properties->GtkInfo.comboboxWeekday, listWeekdays, 7);
  gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxWeekday), occurence_day);
  
  struct elementList listOccurance[4];

  for(index = 0; index < 4; index++)
  {
    snprintf(listOccurance[index].elementName,sizeof(listOccurance[index].elementName),"%d%s %s", index+1, order[index], weekDays[occurence_day] );
    //g_print("%s\n",listOccurance[index].elementName);
  }

  set_up_combobox_with_array2(properties->GtkInfo.comboboxOccurance, listOccurance, sizeof(listOccurance) / sizeof(listOccurance[0]));
  gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxOccurance), properties->occurence_in_month-1);
  gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxWeekday), occurence_day);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDayOffset), properties->occurence_plus_offset);
  g_print("properties->occurence_plus_offset = %d\n", properties->occurence_plus_offset);

  g_signal_connect(G_OBJECT (properties->GtkInfo.spinbuttonDayOffset), "value-changed", G_CALLBACK(on_spinbuttonDayOffset_value_changed), &properties);

  gtk_widget_show_all(properties->GtkInfo.dialogProperties);

  int value = gtk_combo_box_get_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxOccurance));

  if( value >= 3 )
  {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDayOffset),0);
    gtk_widget_hide(properties->GtkInfo.labelDayOffset);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDayOffset);
  } else
  {
    //g_print("value = %d\n",value);
    gtk_widget_show(properties->GtkInfo.labelDayOffset);
    gtk_widget_show(properties->GtkInfo.spinbuttonDayOffset);
  }

  char expirationTime[400] = { 0 };
  snprintf(expirationTime,sizeof(expirationTime),"%02d:%02d:%02d",properties->expiration_hour,properties->expiration_minute,properties->expiration_second);
  gtk_entry_set_text(GTK_ENTRY(properties->GtkInfo.entryExpirationTime), expirationTime);

  gtk_dialog_run(GTK_DIALOG(properties->GtkInfo.dialogProperties));

} // void on_buttonProperties_clicked( GtkWidget *widget, const struct _properties *properties )

void on_dialogSettings_ok(GtkWidget *widget, gpointer *data)
{
  g_print("on_dialogSettings_ok()\n");

  ::properties.updatedelayseconds = (int) gtk_spin_button_get_value(GTK_SPIN_BUTTON(::properties.GtkInfo.spinbuttonSleepDelay));

  g_print("on_dialogSettings_ok(): spinbuttonSleepDelay = %d\n", ::properties.updatedelayseconds);

  gtk_widget_hide(::properties.GtkInfo.dialogSettings);

  if( ::properties.GtkInfo.gcalculate_options )
  {
    g_source_remove(::properties.GtkInfo.gcalculate_options);
    ::properties.GtkInfo.gcalculate_options = 0;
  }

  ::properties.GtkInfo.gcalculate_options = g_timeout_add(1000 * ::properties.updatedelayseconds, (GSourceFunc) calculate_options, &properties);

} // void on_dialogSettings_ok(GtkWidget *widget, gpointer *data)

void on_dialogSettings_cancel(GtkWidget *widget, const struct _properties *properties)
{
  g_print("on_dialogSettings_cancel()\n");
  gtk_widget_hide(properties->GtkInfo.dialogSettings);

} // void on_dialogSettings_cancel(GtkWidget *widget, const struct _properties *properties)

int on_dialogSettings_delete_event(GtkWidget *widget, const struct _properties *properties)
{
  g_print("on_dialogSettings_delete_event()\n");
  gtk_widget_hide(::properties.GtkInfo.dialogSettings);

  return TRUE;

} // int on_dialogSettings_delete_event(GtkWidget *widget, const struct _properties *properties)
