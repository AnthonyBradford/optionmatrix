/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_scale.cpp of optionmatrix                                      */
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

void calc_strike_scale(struct _properties *properties)
{
  double price;

  if( properties->data.price < 100 )
  {
    price = 100;
  }
  else
  {
    price = properties->data.price;
  }

  int middle;
  int high;
  double incrementor;

  if( properties->spreads == 0 )
  {
    middle = (int) (price/strike_control[properties->strikestoogle].xcontrol)/2;
    high =  (int) (price/strike_control[properties->strikestoogle].xcontrol);
    incrementor = strike_control[properties->strikestoogle].sliderScale;

  } else if( properties->spreads == 1 )
  {
    middle = (int) (price/strike_control[properties->strikestoogle].xcontrol);
    high =  (int) (price/strike_control[properties->strikestoogle].xcontrol) * 1.5;
    incrementor = 1;
  }

 if( properties->format == CALENDAR_OPTIONS4 )
   incrementor = 1;

  g_print("middle = %d, high = %d, incrementor = %f\n",middle,high,incrementor);
  properties->GtkInfo.scale_int_strikes  = GTK_ADJUSTMENT (gtk_adjustment_new ( middle, 1, high, incrementor, incrementor, 0));
  properties->GtkInfo.scale_int_strikes2 = GTK_ADJUSTMENT (gtk_adjustment_new ( middle, 1, high, incrementor, incrementor, 0));

  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties->GtkInfo.scaleStrikes),properties->GtkInfo.scale_int_strikes);
  gtk_button_set_relief(GTK_BUTTON(properties->GtkInfo.scaleStrikes), GTK_RELIEF_NORMAL);
  
  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties->GtkInfo.scaleStrikes2),properties->GtkInfo.scale_int_strikes2);
  gtk_button_set_relief(GTK_BUTTON(properties->GtkInfo.scaleStrikes2), GTK_RELIEF_NORMAL);

} // void calc_strike_scale(struct _properties *properties)

void on_scaleStrikes_value_changed(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties)
{
  g_print("on_scaleStrikes_value_changed()\n");

  double price = properties->data.price;
  double mult;

  int middle = (int) (price / strike_control[properties->strikestoogle].xcontrol) / 2;

  if( properties->spreads == 0 )
    mult = 2;
  else  if( properties->spreads == 1 )
    mult = 1;

  if( properties->format == CALENDAR_OPTIONS4 )
    mult = 1;

  properties->strike_offset = (int) (value - middle) * strike_control[properties->strikestoogle].xcontrol*mult;

  //g_print("strike_control[properties->strikestoogle].xcontrol = %f\n", strike_control[properties->strikestoogle].xcontrol);
  //g_print("price = %f, value = %f, strike_offset = %f\n", price, value, properties->strike_offset);
  g_print("strike_offset = %f\n",properties->strike_offset);

} // void on_scaleStrikes_value_changed(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties)

void on_scaleStrikes_value_changed2(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties)
{
  g_print("on_scaleStrikes_value_changed2()\n");

  double price = properties->data.price;
  double mult;

  int middle = (int) (price / strike_control[properties->strikestoogle].xcontrol) / 2;

  if( properties->spreads == 0 )
    mult = 2;
  else  if( properties->spreads == 1 )
    mult = 1;

  if( properties->format == CALENDAR_OPTIONS4 )
    mult = 1;

  properties->strike_offset2 = (int) (value - middle) * strike_control[properties->strikestoogle].xcontrol*mult;

  //g_print("strike_control[properties->strikestoogle].xcontrol = %f\n", strike_control[properties->strikestoogle].xcontrol);
  //g_print("price = %f, value = %f, strike_offset2 = %f\n", price, value, properties->strike_offset2);
  g_print("strike_offset2 = %f\n",properties->strike_offset2);

} // void on_scaleStrikes_value_changed2(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties)

void on_scaleMonths_value_changed(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties)
{
  g_print("on_scaleStrikes_value_changed()\n");
  properties->skipmonth = value;

  //g_print("value = %f\n",value);

  expires(LEG1,30,properties->skipmonth,properties);

  if( properties->format != CALENDAR_OPTIONS3 && properties->format != CALENDAR_OPTIONS4 && properties->format != CALENDAR_CUSTOM )
    setup_tree_view(properties);

} // void on_scaleMonths_value_changed(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties)

void on_scaleMonths_value_changed2(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties)
{
  g_print("on_scaleStrikes_value_changed2()\n");
  properties->skipmonth2 = value;

  //g_print("value = %f\n",value);

  expires(LEG2,30,properties->skipmonth2,properties);

  if( properties->format != CALENDAR_OPTIONS3 && properties->format != CALENDAR_OPTIONS4 && properties->format != CALENDAR_CUSTOM )
    setup_tree_view(properties);

} // void on_scaleMonths_value_changed2(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties)
