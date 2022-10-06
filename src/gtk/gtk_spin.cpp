/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_spin.cpp of optionmatrix                                       */
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

void on_spinbuttonDayOffset_value_changed(GtkSpinButton *spinButton, const struct _properties *properties)
{
  g_print("on_spinbuttonDayOffset_value_changed()\n");
}

void on_spinbuttonUseZ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseZ_value_changed\n");
  g_print("properties->data.UseZ = %f\n",properties->data.UseZ);
}

void on_spinbuttonUseB_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseB_value_changed\n");
  g_print("properties->data.UseB = %f\n",properties->data.UseB);
}

void on_spinbuttonUseJ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseJ_value_changed\n");
  g_print("properties->data.UseJ = %f\n",properties->data.UseJ);
}

void on_spinbuttonUseP_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseP_value_changed\n");
  g_print("properties->data.UseP = %f\n",properties->data.UseP);
}

void on_spinbuttonUseQ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseQ_value_changed\n");
  g_print("properties->data.UseQ = %f\n",properties->data.UseQ);
}

void on_spinbuttonUseR_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseR_value_changed\n");
  g_print("properties->data.UseR = %f\n",properties->data.UseR);
}

void on_spinbuttonUseS_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseS_value_changed\n");
  g_print("properties->data.UseS = %f\n",properties->data.UseS);
}

void on_spinbuttonUseT_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonUseT_value_changed\n");
  g_print("properties->data.UseT = %f\n",properties->data.UseT);
}

void on_spinbuttonPrice_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonPrice_value_changed()\n");
  properties->data.price = gtk_spin_button_get_value(spinbutton);
  calc_strike_scale(properties);
}

int on_spinbuttonTime_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTimeInFocusflag = FALSE;
  return false;
}

int on_spinbuttonTime_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTimeInFocusflag = TRUE;
  return false;
}

int on_spinbuttonTime2_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime2_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTime2InFocusflag = FALSE;
  return false;
}

int on_spinbuttonTime3_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime3_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTime3InFocusflag = FALSE;
  return false;
}

int on_spinbuttonTime2_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime2_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTime2InFocusflag = TRUE;
  return false;
}

int on_spinbuttonTime3_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonTime3_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTime3InFocusflag = TRUE;
  return false;
}

void on_spinbuttonDaysToExpr_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToExpr_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTimeInFocusflag = FALSE;
}

void on_spinbuttonDaysToExpr_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToExpr_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTimeInFocusflag = TRUE;
}

void on_spinbuttonDaysToDividend_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToDividend_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTime2InFocusflag = FALSE;
}

void on_spinbuttonDaysToDividend2_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToDividend2_focus_out_event()\n");
  properties->GtkInfo.spinbuttonTime3InFocusflag = FALSE;
}

void on_spinbuttonDaysToDividend_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  //g_print("on_spinbuttonDaysToDividend_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTime2InFocusflag = TRUE;
}

void on_spinbuttonDaysToDividend2_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToDividend2_focus_in_event()\n");
  properties->GtkInfo.spinbuttonTime3InFocusflag = TRUE;
}

void on_spinbuttonTime_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonTime_value_changed()\n");
  //g_print("TimeFlag = %s\n",spinbuttonTimeFlag ? "TRUE": "FALSE");

  if(properties->GtkInfo.spinbuttonTimeFlag == TRUE)
  {
    properties->data.t[0] = gtk_spin_button_get_value(spinbutton);
    properties->data.t[0] += properties->data.te;
    properties->GtkInfo.spinbuttonTimeInFocusflag = FALSE;
  }
}

void on_spinbuttonTime2_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonTime2_value_changed()\n");

  if(properties->GtkInfo.spinbuttonTime2Flag == true)
  {
    properties->data.t[1] = gtk_spin_button_get_value(spinbutton);
    properties->data.t[1] += properties->data.te2;
    properties->GtkInfo.spinbuttonTime2InFocusflag = FALSE;
  }
}

void on_spinbuttonTime3_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonTime3_value_changed()\n");

  if(properties->GtkInfo.spinbuttonTime3Flag == true)
  {
    properties->data.t[2] = gtk_spin_button_get_value(spinbutton);
    properties->data.t[2] += properties->data.te3;
    properties->GtkInfo.spinbuttonTime3InFocusflag = FALSE;
  }
}

void on_spinbuttonDaysToExpr_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToExpr_value_changed_value_changed()\n");
  
  if(properties->GtkInfo.spinbuttonTimeFlag == true)
  {
    properties->data.t[0] = gtk_spin_button_get_value(spinbutton) / 365;
    properties->data.t[0] += properties->data.te;
    properties->GtkInfo.spinbuttonTimeInFocusflag = FALSE;
  }
}

void on_spinbuttonDaysToDividend_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToDividend_value_changed_value_changed()\n");
  
  if(properties->GtkInfo.spinbuttonTime2Flag == true)
  {
    properties->data.t[1] = gtk_spin_button_get_value(spinbutton) / 365;
    properties->data.t[1] += properties->data.te2;
    properties->GtkInfo.spinbuttonTime2InFocusflag = FALSE;
  }
}

void on_spinbuttonDaysToDividend2_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDaysToDividend2_value_changed_value_changed()\n");
  
  if(properties->GtkInfo.spinbuttonTime3Flag == true)
  {
    properties->data.t[2] = gtk_spin_button_get_value(spinbutton) / 365;
    properties->data.t[2] += properties->data.te3;
    properties->GtkInfo.spinbuttonTime3InFocusflag = FALSE;
  }
}

void on_spinbuttonRate_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonRate_value_changed()\n");
  properties->data.rate = gtk_spin_button_get_value(spinbutton);
}

void on_spinbuttonStandardDeviation_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonStandardDeviation_value_changed()\n");
  properties->data.volatility = gtk_spin_button_get_value(spinbutton);
}

void on_spinbuttonDividend_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDividend_value_changed()\n");
  properties->data.dividend = gtk_spin_button_get_value(spinbutton);
}

void on_spinbuttonSteps_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonSteps_value_changed()\n");

  if(option_algorithms[properties->modeltype].supportSteps)
  {
    option_algorithms[properties->modeltype].steps = gtk_spin_button_get_value(spinbutton);
  }
  if(integration_method[properties->integration_type].method)
  {
    integration_method[properties->integration_type].resolution = gtk_spin_button_get_value(spinbutton);
  }
}

void on_spinbuttonPrecision_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonPrecision_value_changed()\n");
  properties->precision = gtk_spin_button_get_value(spinbutton);
  updatePrecision(properties->modeltype,properties);
}

void on_spinbuttonDistMean_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDistMean_value_changed()\n");
}

void on_spinbuttonDistVariance_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDistVariance_value_changed()\n");
}

void on_spinbuttonCustomStrike_value_changed(GtkSpinButton *spinbutton, struct _properties *properties)
{
  g_print("on_spinbuttonDistVariance_value_changed()\n");
}

void on_spinbuttonSleepDelay_value_changed(GtkSpinButton *spinButton, struct _properties *properties)
{
  g_print("on_spinbuttonSleepDelay_value_changed(): %d\n", (int) gtk_spin_button_get_value(spinButton));
}
