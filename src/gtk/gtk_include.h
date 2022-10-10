/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk.h of optionmatrix                                              */
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

#include "config.h"

#if defined(HAVE_LIBGTK_3) || defined(HAVE_LIBGTK_X11_2_0)
# include <gtk/gtk.h>
#else
# error Sorry, this code requires <gtk/gtk.h>
#endif

struct gtkinfo {

  bool checkbuttonDateEngineIgnore;

  GtkBuilder *builder;
  GtkWidget  *window;
  GtkWidget  *vpanel1;
  GtkWidget  *tableTop;
  GtkWidget  *calendar1;
  GtkWidget  *calendar2;

  GtkWidget *labelTime1;
  GtkWidget *labelTime2;
  GtkWidget *labelTime3;
  GtkWidget *labelDisplayTime;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *labelDaysToExpr;
  GtkWidget *labelDaysToDividend;
  GtkWidget *labelDaysToDividend2;
  GtkWidget *labelPrice;
  GtkWidget *labelSpread;
  GtkWidget *spinbuttonPrice;
  GtkWidget *spinbuttonCustomStrike;
  GtkWidget *spinbuttonCustomStrike2;
  GtkWidget *spinbuttonTime;
  GtkWidget *spinbuttonTime2;
  GtkWidget *spinbuttonTime3;
  GtkWidget *spinbuttonSleepDelay;
  GtkWidget *labelRate;
  GtkWidget *spinbuttonRate;
  GtkWidget *labelExpirations;
  GtkWidget *labelModel;
  GtkWidget *comboboxModel;
  GtkWidget *labelCND;
  GtkWidget *comboboxCND;
  GtkWidget *labelState;
  GtkWidget *comboboxState;
  GtkWidget *labelStandardDeviation;
  GtkWidget *spinbuttonStandardDeviation;
  GtkWidget *labelDividend;
  GtkWidget *spinbuttonDividend;
  GtkWidget *labelCycle;
  GtkWidget *comboboxCycle;
  GtkWidget *spinbuttonSteps;
  GtkWidget *labelSteps;
  GtkWidget *labelPrecision;
  GtkWidget *buttonProperties;
  GtkWidget *buttonDividends;
  GtkWidget *buttonCalendar;
  GtkWidget *buttonCalendar2;
  GtkWidget *buttonCalendar3;
  GtkWidget *buttonCoupons;
  GtkWidget *buttonPrincipal;
  GtkWidget *labelCalendar;
  GtkWidget *labelCalendar2;
  GtkWidget *spinbuttonPrecision;
  GtkWidget *spinbuttonDaysToExpr;
  GtkWidget *spinbuttonDaysToDividend;
  GtkWidget *spinbuttonDaysToDividend2;
  GtkWidget *checkbuttonRealTime;
  GtkWidget *checkbuttonDateEngine;
  GtkWidget *checkbuttonSpreads;
  GtkWidget *checkbuttonFilterNegativePrice;
  GtkWidget *labelStrikes;
  GtkWidget *labelStrikes2;
  GtkWidget *comboboxStrikes;
  GtkListStore *liststore1;
  GtkWidget *scrolledwindow1;
  GtkWidget *radiobutton1;
  GtkWidget *radiobutton2;
  GtkWidget *radiobutton3;
  GtkWidget *radiobutton4;
  GtkWidget *radiobutton5;
  GtkWidget *labelDisplayFormats;
  GtkWidget *labelDisplayFormats2;
  GtkWidget *menu_quit;
  GtkWidget *menu_about;
  GtkWidget *menu_website;
  GtkWidget *menu_feedback;
  GtkWidget *menu_debug_log;
  GtkWidget *menu_text_export;
  GtkWidget *menu_file_export;
  GtkWidget *menu_source_export;
  GtkWidget *menu_ListCategory;
  GtkWidget *menu_ListAuthor;
  GtkWidget *menu_List;
  GtkWidget *menu_settings;
  GtkWidget *dialogAbout;
  GtkWidget *dialogProperties;
  GtkWidget *dialogCalendar;
  GtkWidget *dialogSettings;
  GtkWidget *labelInfo;
  
  GtkWidget *labelWeekday;
  GtkWidget *comboboxWeekday;
  GtkWidget *labelOccurance;
  GtkWidget *comboboxOccurance;
  GtkWidget *labelDayOffset;
  GtkWidget *spinbuttonDayOffset;
  GtkWidget *labelExpirationTime;
  GtkWidget *entryExpirationTime;
  GtkWidget *labelTimeError;

  GtkWidget *labelDistMean;
  GtkWidget *spinbuttonDistMean;
  GtkWidget *labelDistVariance;
  GtkWidget *spinbuttonDistVariance;
  
  GtkAdjustment *spin_int_precision;
  GtkAdjustment *spin_float_price;
  GtkAdjustment *spin_float_rate;
  GtkAdjustment *spin_float_dist_mean;
  GtkAdjustment *spin_float_dist_var;
  GtkAdjustment *spin_int_steps;
  GtkAdjustment *spin_int_sleep_delay;
  GtkAdjustment *spin_float_sd;
  GtkAdjustment *spin_float_dividend;
  GtkAdjustment *spin_float_time;
  GtkAdjustment *spin_float_time2;
  GtkAdjustment *spin_float_time3;
  GtkAdjustment *spin_float_days_to_expr;
  GtkAdjustment *spin_float_days_to_dividend;
  GtkAdjustment *spin_float_days_to_dividend2;
  GtkAdjustment *spin_float_custom_strike;
  GtkAdjustment *spin_float_custom_strike2;
  GtkAdjustment *spin_z;
  GtkAdjustment *spin_b;
  GtkAdjustment *spin_j;
  GtkAdjustment *spin_p;
  GtkAdjustment *spin_q;
  GtkAdjustment *spin_r;
  GtkAdjustment *spin_s;
  GtkAdjustment *spin_t;
  GtkAdjustment *spin_pound;
  GtkAdjustment *scale_int_strikes;
  GtkAdjustment *scale_int_strikes2;
  GtkAdjustment *scale_int_months;
  GtkAdjustment *scale_int_months2;

  gboolean spinbuttonTimeFlag;
  gboolean spinbuttonTimeInFocusflag;

  gboolean spinbuttonTime2Flag;
  gboolean spinbuttonTime2InFocusflag;

  gboolean spinbuttonTime3Flag;
  gboolean spinbuttonTime3InFocusflag;

  GtkWidget *treeview;
  GtkWidget *labelUseZ;
  GtkWidget *labelUseB;
  GtkWidget *labelUseJ;
  GtkWidget *labelUseP;
  GtkWidget *labelUseQ;
  GtkWidget *labelUseR;
  GtkWidget *labelUseS;
  GtkWidget *labelUseT;
  GtkWidget *spinbuttonUseZ;
  GtkWidget *spinbuttonUseB;
  GtkWidget *spinbuttonUseJ;
  GtkWidget *spinbuttonUseP;
  GtkWidget *spinbuttonUseQ;
  GtkWidget *spinbuttonUseR;
  GtkWidget *spinbuttonUseS;
  GtkWidget *spinbuttonUseT;
  GtkWidget *scaleStrikes;
  GtkWidget *scaleMonths;
  GtkWidget *scaleStrikes2;
  GtkWidget *scaleMonths2;

  gint gcalculate_options;

  GtkWidget *dialog;
  GtkTreeStore *store;
  GtkWidget *treeview2;
  GtkTreeModel *model;
  GdkPixbuf *optionmatrix_icon;
  gint gListTimer;
};
