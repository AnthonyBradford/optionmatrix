/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_radio.cpp of optionmatrix                                      */
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

void on_radiobutton1_pressed( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_radiobutton1_pressed()\n");
  properties->format = CALENDAR_OPTIONS3;

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    // custom strikes...
    if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads != 1 )
    {
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }
    // custom strikes with spreads...
    else if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
    {
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);

      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_hide(properties->GtkInfo.comboboxStrikes);

    }
    else if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads == 1 )
    {
      gtk_widget_hide(properties->GtkInfo.labelStrikes);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);
    }
    else
    {
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

    if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads != 1 )
    {
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
    }

  } else
  {
    gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
    gtk_widget_hide(properties->GtkInfo.labelStrikes);
  }
  
  if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads != 1 )
  {
    gtk_widget_hide(properties->GtkInfo.labelStrikes2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
  }

  set_scale_button(properties);
  gtk_widget_show(properties->GtkInfo.checkbuttonSpreads);

  setup_tree_view(properties);
  show_title(properties);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton1),true);

} // void on_radiobutton1_pressed( GtkWidget *widget, struct _properties *properties )

void on_radiobutton2_pressed( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_radiobutton2_pressed()\n");
  properties->format = CALENDAR_OPTIONS4;

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    // custom strikes...
    if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads != 1 )
    {
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }
    // custom strikes with spreads...
    else if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
    {
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);

      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_hide(properties->GtkInfo.comboboxStrikes);

    }
    else if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads == 1 )
    {
      gtk_widget_hide(properties->GtkInfo.labelStrikes);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);
    }
    else
    {
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

    if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads != 1 )
    {
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
    }

  } else
  {
    gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
    gtk_widget_hide(properties->GtkInfo.labelStrikes);
  }

  if( strike_control[properties->strikestoogle].incrementor != 0 && properties->spreads != 1 )
  {
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
    gtk_widget_hide(properties->GtkInfo.labelStrikes2);
  }

  set_scale_button(properties);
  gtk_widget_show(properties->GtkInfo.checkbuttonSpreads);

  setup_tree_view(properties);
  show_title(properties);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton2),true);

} // void on_radiobutton2_pressed( GtkWidget *widget, struct _properties *properties )

void on_radiobutton3_pressed( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_radiobutton3_pressed()\n");
  properties->format = CALENDAR_CUSTOM;

  if( strike_control[properties->strikestoogle].incrementor == 0 )
  {
    properties->strikestoogle = 0;
    gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxStrikes), 0);
  }

  gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
  gtk_widget_hide(properties->GtkInfo.scaleStrikes);
  gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike);
    gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);

  } else
  {
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
  }

  if( properties->spreads == 1 )
  {
    gtk_widget_show(properties->GtkInfo.scaleMonths2);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");

    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adj Leg1");
    gtk_widget_show(properties->GtkInfo.scaleMonths);

    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);

    } else
    {
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
    }

    g_print("Strike Leg1\n");

  } else if( properties->spreads == 0 )
  {
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strike");

    gtk_widget_hide(properties->GtkInfo.labelStrikes2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);

    g_print("NO Strike Leg1\n");
  }

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    gtk_widget_show(properties->GtkInfo.labelStrikes);

  } else
  {
    gtk_widget_hide(properties->GtkInfo.labelStrikes);
  }

  gtk_widget_show(properties->GtkInfo.checkbuttonSpreads);

  setup_tree_view(properties);
  show_title(properties);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton3),true);

} // void on_radiobutton3_pressed( GtkWidget *widget, struct _properties *properties )

void on_radiobutton4_pressed( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_radiobutton4_pressed()\n");
  properties->format = CALENDAR_OPTIONS5;

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    // custom strikes...
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

    gtk_widget_show(properties->GtkInfo.comboboxStrikes);

    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
    gtk_widget_show(properties->GtkInfo.labelStrikes);

  } else
  {
    gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes);
  }

  gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
  gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");

  if( !option_algorithms[properties->modeltype].supportStrikes || strike_control[properties->strikestoogle].incrementor != 0 )
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);

  gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adjuster");
  gtk_widget_show(properties->GtkInfo.scaleMonths);

  gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);
  gtk_widget_hide(properties->GtkInfo.labelSpread);
  gtk_widget_hide(properties->GtkInfo.scaleMonths2);
  gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

  setup_tree_view(properties);
  show_title(properties);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton4),true);

} // void on_radiobutton4_pressed( GtkWidget *widget, struct _properties *properties )

void on_radiobutton5_pressed( GtkWidget *widget, struct _properties *properties )
{
  g_print ("on_radiobutton5_pressed()\n");
  properties->format = CALENDAR_OPTIONS6;

  if( option_algorithms[properties->modeltype].supportStrikes )
  {
    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");

    if( strike_control[properties->strikestoogle].incrementor == 0 )
    {
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    } else
    {
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

    gtk_widget_show(properties->GtkInfo.comboboxStrikes);

    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");
    gtk_widget_show(properties->GtkInfo.labelStrikes);

  } else
  {
    gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    gtk_widget_hide(properties->GtkInfo.labelStrikes);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes);
  }

  gtk_widget_hide(properties->GtkInfo.scaleStrikes2);
  gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);

  if( strike_control[properties->strikestoogle].incrementor != 0 )
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);

  gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adjuster");
  gtk_widget_show(properties->GtkInfo.scaleMonths);

  gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);
  gtk_widget_hide(properties->GtkInfo.labelSpread);
  gtk_widget_hide(properties->GtkInfo.scaleMonths2);
  gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

  setup_tree_view(properties);
  show_title(properties);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.radiobutton5),true);

} // void on_radiobutton5_pressed( GtkWidget *widget, struct _properties *properties )

void set_scale_button(struct _properties *properties )
{
  if( properties->spreads == 1 )
  {
    if( option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
    {
      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adj Leg1");
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
      gtk_widget_show(properties->GtkInfo.scaleStrikes2);

    } else
    {
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }

    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adj Leg1");
    gtk_widget_show(properties->GtkInfo.scaleMonths);

    gtk_widget_show(properties->GtkInfo.scaleMonths2);

  } else if ( properties->spreads == 0 )
  {
    if( option_algorithms[properties->modeltype].supportStrikes && strike_control[properties->strikestoogle].incrementor != 0 )
    {
      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");
      gtk_widget_show(properties->GtkInfo.scaleStrikes);

    } else
    {
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }

    if( strike_control[properties->strikestoogle].incrementor == 0 )
    {
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);

    } else
    {
      gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_hide(properties->GtkInfo.labelStrikes2);
      gtk_widget_show(properties->GtkInfo.scaleStrikes);
    }

    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleMonths),"Month Adjuster");
    gtk_widget_show(properties->GtkInfo.scaleMonths);

    gtk_widget_hide(properties->GtkInfo.scaleMonths2);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes2);
  }

} // void set_scale_button(struct _properties *properties )
