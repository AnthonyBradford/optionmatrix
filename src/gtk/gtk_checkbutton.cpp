/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_checkbutton.cpp of optionmatrix                                */
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

void on_checkbuttonFilterNegativePrice_toggled(GtkButton *button, struct _properties *properties)
{
  g_print("on_checkbuttonFilterNegativePrice_toggled()\n");

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button)) )
  {
    g_print("button set\n");
    option_algorithms[properties->modeltype].filterNegativePrices = true;
  } else
  {
    g_print("button not set\n");
    option_algorithms[properties->modeltype].filterNegativePrices = false;    
  }

} // void on_checkbuttonFilterNegativePrice_toggled(GtkButton *button, struct _properties *properties)

void on_checkbuttonDateEngine_toggled(GtkButton *button, struct _properties *properties)
{
  g_print("on_checkbuttonDateEngine_toggled()\n");

  if( properties->GtkInfo.checkbuttonDateEngineIgnore == true )
  {
    g_print("checkbuttonDateEngineIgnored\n");
    properties->GtkInfo.checkbuttonDateEngineIgnore = false;
    return;
  }

  if( option_algorithms[properties->modeltype].supportTime2 == 1 )
  {
    return;
  }

  if( option_algorithms[properties->modeltype].perpetual )
  {
    return;
  }

  if( properties->decimalorcalendar == DECIMALS )
  {
    // switch to calendar dated...
    //g_print("Calendar Dated\n");
    properties->decimalorcalendar = CALENDAR;

    if( option_algorithms[properties->modeltype].assetClass )
    {
      properties->format = CALENDAR_FUTURE;
    } else
    {
      properties->format = CALENDAR_OPTIONS3;
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton1),true);  // CALENDAR_OPTIONS3

      if( option_algorithms[properties->modeltype].supportStrikes )
      {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton2),false);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton3),false);
      }

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton4),false);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton5),false);

      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);
      gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);

      if( option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
      {
        gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");
        gtk_widget_show(properties->GtkInfo.scaleStrikes);

      } else
      {
        gtk_widget_hide(properties->GtkInfo.scaleStrikes);
      }

      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adjuster");
      gtk_widget_show(properties->GtkInfo.scaleMonths);
    }
    //properties->format = CALENDAR_OPTIONS4;
    //properties->format = CALENDAR_OPTIONS5;
    //properties->format = CALENDAR_OPTIONS6;
    //properties->format = CALENDAR_CUSTOM;

    gtk_widget_hide(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime);
    gtk_widget_hide(properties->GtkInfo.label1);
    gtk_widget_hide(properties->GtkInfo.labelDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.labelTime1);

    if( !option_algorithms[properties->modeltype].assetClass )
    {
      gtk_widget_show(properties->GtkInfo.labelCycle);
      gtk_widget_show(properties->GtkInfo.comboboxCycle);
      gtk_widget_show(properties->GtkInfo.radiobutton1);

      if( option_algorithms[properties->modeltype].supportStrikes )
      {
        gtk_widget_show(properties->GtkInfo.radiobutton2);
        gtk_widget_show(properties->GtkInfo.radiobutton3);
      }

      gtk_widget_show(properties->GtkInfo.radiobutton4);
      gtk_widget_show(properties->GtkInfo.radiobutton5);
      gtk_widget_show(properties->GtkInfo.labelDisplayFormats);
    }

    show_label_expirations(properties);
    gtk_widget_show(properties->GtkInfo.scaleMonths);
    gtk_widget_show(properties->GtkInfo.buttonProperties);
    gtk_widget_show(properties->GtkInfo.checkbuttonSpreads);

  } else 
  {
    // switch to decimal dated...
    //g_print("Decimal Dated\n");
    properties->decimalorcalendar = DECIMALS;

    if( option_algorithms[properties->modeltype].assetClass )
    {
      properties->format = DECIMAL_FUTURE;
    } else
    {
      properties->format = DECIMAL_GREEKS;
      if( option_algorithms[properties->modeltype].supportStrikes )
      {
        gtk_widget_show(properties->GtkInfo.comboboxStrikes);
        gtk_widget_show(properties->GtkInfo.scaleStrikes);

        gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
        gtk_widget_show(properties->GtkInfo.labelStrikes);

      } else
      {
        gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
        gtk_widget_hide(properties->GtkInfo.scaleStrikes);
        gtk_widget_hide(properties->GtkInfo.labelStrikes);
      }
    }

    gtk_widget_show(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_show(properties->GtkInfo.buttonCalendar);
    gtk_widget_show(properties->GtkInfo.spinbuttonTime);
    gtk_widget_show(properties->GtkInfo.label1);
    gtk_widget_show(properties->GtkInfo.labelDaysToExpr);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToExpr);
    gtk_widget_show(properties->GtkInfo.labelTime1);

    gtk_widget_hide(properties->GtkInfo.labelCycle);
    gtk_widget_hide(properties->GtkInfo.comboboxCycle);
    gtk_widget_hide(properties->GtkInfo.labelExpirations);
    gtk_widget_hide(properties->GtkInfo.scaleMonths);
    gtk_widget_hide(properties->GtkInfo.buttonProperties);

    gtk_widget_hide(properties->GtkInfo.radiobutton1);
    gtk_widget_hide(properties->GtkInfo.radiobutton2);
    gtk_widget_hide(properties->GtkInfo.radiobutton3);
    gtk_widget_hide(properties->GtkInfo.radiobutton4);
    gtk_widget_hide(properties->GtkInfo.radiobutton5);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats);
    gtk_widget_hide(properties->GtkInfo.labelStrikes2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
    gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);

    properties->data.t[0] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime));

    if( strike_control[properties->strikestoogle].incrementor == 0 )
    {
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }
    else
    {
     gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
     gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
     gtk_widget_hide(properties->GtkInfo.labelStrikes2);
     gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

  }

  setup_tree_view(properties);
  show_title(properties);
  
} // void on_checkbuttonDateEngine_toggled(GtkButton *button, struct _properties *properties)

void on_checkbuttonRealTime_toggled(GtkButton *button, struct _properties *properties)
{
  g_print("on_checkbuttonRealTime_toggled()\n");
  
  //gtk_toggle_button_get_active()
  
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button)) )
  {
    //g_print("Realtime set\n");
    properties->realTimeBleeding = 1;

    time(&properties->starttime);
    time(&properties->starttime2);
    time(&properties->starttime3);

  } else
  {
    //g_print("Leaving realtime\n");
    properties->realTimeBleeding = 0;

    properties->data.t[0] = properties->data.t[0] - properties->data.te;
    properties->data.t[1] = properties->data.t[1] - properties->data.te2;
    properties->data.t[2] = properties->data.t[2] - properties->data.te3;

    //
    pthread_mutex_lock(&properties->data.mutexCashflow);

    for( std::vector<double>::iterator it = properties->data.times.begin(); it != properties->data.times.end(); ++it)
    {
      *it -= properties->data.te;
    }

    for( std::vector<double>::iterator it = properties->data.coupon_times.begin(); it != properties->data.coupon_times.end(); ++it)
    {
      *it -= properties->data.te;
    }

    for( std::vector<double>::iterator it = properties->data.principal_times.begin(); it != properties->data.principal_times.end(); ++it)
    {
      *it -= properties->data.te;
    }
    
    pthread_mutex_unlock(&properties->data.mutexCashflow);

    properties->data.te  = 0;
    properties->data.te2 = 0;
    properties->data.te3 = 0;
  }

} // void on_checkbuttonRealTime_toggled(GtkButton *button, struct _properties *properties)

void on_checkbuttonSpreads_toggled(GtkButton *button, struct _properties *properties)
{
  g_print("on_checkbuttonSpreads_toggled()\n");
  
  if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button)) )
  {
    g_print("Use Spreads\n");
    properties->spreads = 1;

    calc_strike_scale(properties);

    if( properties->format != CALENDAR_CUSTOM && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
    {
      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adj Leg1");
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
      gtk_widget_show(properties->GtkInfo.scaleStrikes2);
    }

    if( properties->format == CALENDAR_CUSTOM && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
    }

    if( strike_control[properties->strikestoogle].incrementor == 0 && properties->format != CALENDAR_CUSTOM )
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);

      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
    }

    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adj Leg1");
    gtk_widget_show(properties->GtkInfo.scaleMonths);
    gtk_widget_show(properties->GtkInfo.scaleMonths2);

  } else
  {
    g_print("No Spreads\n");
    properties->spreads = 0;

    calc_strike_scale(properties);

    gtk_widget_hide(properties->GtkInfo.labelSpread);

    if( properties->format != CALENDAR_CUSTOM && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
    {
      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

    if( properties->format == CALENDAR_CUSTOM && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes )
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
    }

    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adjuster");
    gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

    if( properties->decimalorcalendar == CALENDAR )
      gtk_widget_show(properties->GtkInfo.scaleMonths);

    gtk_widget_hide(properties->GtkInfo.scaleMonths2);

    if( strike_control[properties->strikestoogle].incrementor == 0 && properties->format != CALENDAR_CUSTOM )
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
      gtk_widget_show(properties->GtkInfo.labelStrikes);

      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");

      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);
    }
  }

  setup_tree_view(properties);

} // void on_checkbuttonSpreads_toggled(GtkButton *button, struct _properties *properties)

void spreadName(struct _properties *properties)
{
  static char spreadName[512];
  spreadName[0] = 0;

  if( properties->spreads == 0 )
    return;

  if( properties->format == CALENDAR_OPTIONS5 ||  properties->format == CALENDAR_OPTIONS6 )
    return;

  if( properties->verticalSpread && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes )
    strncat(spreadName,"Vertical ",sizeof(spreadName)-1);

  if( properties->skipmonth != properties->skipmonth2 )
    strncat(spreadName,"Calendar ",sizeof(spreadName)-1);
  
  if( (properties->verticalSpread && !option_algorithms[properties->modeltype].assetClass && option_algorithms[properties->modeltype].supportStrikes) || properties->skipmonth != properties->skipmonth2)
    strncat(spreadName,"Spreads",sizeof(spreadName)-1);

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelSpread),spreadName);
  gtk_widget_show(properties->GtkInfo.labelSpread);

  //g_print("properties->skipmonth = %d properties->skipmonth2 = %d\n",properties->skipmonth,properties->skipmonth2);
  //g_print("spread strike %f, %f\n",properties->strike_offset,properties->strike_offset2);
  
} // void spreadName(struct _properties *properties)
