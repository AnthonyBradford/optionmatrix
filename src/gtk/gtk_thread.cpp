/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_thread.cpp of optionmatrix                                     */
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
#include "../common/prototypes.h"

#include <sys/time.h>

static void fill_line(char *lineData, int line_len, const std::vector<string> &fields)
{
  string data;
  for (std::vector<string>::const_iterator it = fields.cbegin(); it != fields.cend(); it++)
  {
    if (*it != "")
      data += *it + ", ";
  }
  data += "\n";
  strncpy(lineData, data.c_str(), line_len - 1);
}

gboolean calculate_options(struct _properties *properties)
{
  g_print("calculate_options()\n");
  //g_print("properties->format = %d\n", properties->format );
  //g_print("properties->decimalorcalendar = %d\n",properties->decimalorcalendar);

  clock_t c0, c1;
  struct timeval start, end;

  c0 = clock();
  gettimeofday(&start, NULL);
  
  gint width;
  gint height;
  gtk_window_get_size(GTK_WINDOW(properties->GtkInfo.window),&width,&height);
  g_print("Window width = %d, height = %d\n", width,height);
  
  // OptionMatrix gets a window size of about 704 pixels...
  // When the user enlarges the window display more option rows
  double rowMultiplier = ((double) height - (double) 704) / (double) 704;
  rowMultiplier = (double) rowMultiplier * (double) 1.50;
  g_print("Height multiplier = %f\n", rowMultiplier);

  static int messageClear;

  gtk_list_store_clear(properties->GtkInfo.liststore1);

  guint index = 0;
  GtkTreeIter iter;

  properties->data.price = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonPrice));
  properties->data.rate  = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonRate));
  properties->data.volatility = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonStandardDeviation));
  properties->data.dividend = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDividend));
  properties->data.steps = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSteps));
  properties->distribution_mean = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistMean));
  properties->distribution_variance = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistVariance));
  properties->data.modeltype = properties->modeltype;

  properties->data.UseZ = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseZ) );
  properties->data.UseB = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseB) );
  properties->data.UseJ = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseJ) );
  properties->data.UseP = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseP) );

  properties->data.UseQ = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseQ) );
  properties->data.UseR = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseR) );
  properties->data.UseS = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseS) );
  properties->data.UseT = gtk_spin_button_get_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseT) );
  properties->data.filterNegativePrices = option_algorithms[properties->modeltype].filterNegativePrices;

  double price = properties->data.price;
 
  gchar textPrice[200] = { 0 };
  gchar textPrice2[200] = { 0 };
  gchar textStrike[200] = { 0 };
  gchar textCall[8][200] = { { 0 } };
  gchar textPut[8][200] = { { 0 } };
  gchar textCallDelta[200]  = { 0 };
  gchar textPutDelta[200] = { 0 };
  gchar textGamma[200] = { 0 };
  gchar textVega[200] = { 0 };
  gchar textCallTheta[200] = { 0 };
  gchar textPutTheta[200] = { 0 };
  gchar textCallRho[200] = { 0 };
  gchar textPutRho[200] = { 0 };
  gchar textCallElasticity[200] = { 0 };
  gchar textPutElasticity[200] = { 0 };
  gchar textMonth[200] = { 0 };

  double callLeg2[200] = { 0 };
  double putLeg2[200] = { 0 };
  char textMonthLeg2[100][200] = { { 0 } };
  char textStrikeLeg2[100][200] = { { 0 } };
  char textLegacyCall[200] = { 0 };
  char textLegacyPut[200] = { 0 };

  int totalCounter = 0;

  char dataExport[100000] = { 0 };
  char lineData[50000] = { 0 };

  double cumStrikeLeg1 = 0.0;
  double cumStrikeLeg2 = 0.0;

  char statusMessage[80 * 3]  = { 0 };
  if( sanity_check(properties, &statusMessage[0], sizeof(statusMessage)) )
  {
    g_print("%s\n",statusMessage);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelInfo),statusMessage);
    gtk_widget_show(properties->GtkInfo.labelInfo);
    messageClear = 1;
  }
  
  if( (messageClear++ % 20) == 0 )
  {
    gtk_widget_hide(properties->GtkInfo.labelInfo);
  }

  time_t mytime;
  struct tm *my_tm;
    
  time(&mytime);
  my_tm=localtime(&mytime);

  char tstring[200]  = { 0 };
  strftime(tstring,sizeof(tstring),"%a %b %d %Y %H:%M:%S",my_tm);
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDisplayTime),tstring);

  gchar dateTime[400] = { 0 };
  gchar dateTime2[400] = { 0 };
  gchar dateTime3[400] = { 0 };

  gdouble decimalTime  = (gdouble) properties->data.t[0] - (gdouble) properties->data.te;
  gdouble decimalTime2 = (gdouble) properties->data.t[1] - (gdouble) properties->data.te2;
  gdouble decimalTime3 = (gdouble) properties->data.t[2] - (gdouble) properties->data.te3;

  pthread_mutex_lock(&properties->data.mutexCashflow);

  properties->data.times_adjusted.erase( properties->data.times_adjusted.begin(), properties->data.times_adjusted.end() );

  for( std::vector<double>::iterator it = properties->data.times.begin(); it != properties->data.times.end(); ++it)
  {
    properties->data.times_adjusted.push_back( *it - (properties->realTimeBleeding ? (gdouble) properties->data.te4 : (gdouble) 0 ) );

    //g_print("%s ", decimal_date_to_real_date(*it - (properties->realTimeBleeding ? (gdouble) properties->data.te : (gdouble) 0) ));
  }
    
  pthread_mutex_unlock(&properties->data.mutexCashflow);

  //

  pthread_mutex_lock(&properties->data.mutexCashflow);

  properties->data.coupon_times_adjusted.erase( properties->data.coupon_times_adjusted.begin(), properties->data.coupon_times_adjusted.end() );

  for( std::vector<double>::iterator it = properties->data.coupon_times.begin(); it != properties->data.coupon_times.end(); ++it)
  {
    properties->data.coupon_times_adjusted.push_back( *it - (properties->realTimeBleeding ? (gdouble) properties->data.te4 : (gdouble) 0 ) );

    //g_print("%s ", decimal_date_to_real_date(*it - (properties->realTimeBleeding ? (gdouble) properties->data.te : (gdouble) 0) ));
  }

  properties->data.principal_times_adjusted.erase( properties->data.principal_times_adjusted.begin(), properties->data.principal_times_adjusted.end() );

  for( std::vector<double>::iterator it = properties->data.principal_times.begin(); it != properties->data.principal_times.end(); ++it)
  {
    properties->data.principal_times_adjusted.push_back( *it - (properties->realTimeBleeding ? (gdouble) properties->data.te4 : (gdouble) 0 ) );

    //g_print("%s ", decimal_date_to_real_date(*it - (properties->realTimeBleeding ? (gdouble) properties->data.te : (gdouble) 0) ));
  }
    
  pthread_mutex_unlock(&properties->data.mutexCashflow);

  if(option_algorithms[properties->modeltype].supportTime2 &&
     option_algorithms[properties->modeltype].perpetual == 0 &&
     properties->GtkInfo.spinbuttonTime2InFocusflag == FALSE)
  {
    snprintf(dateTime2,sizeof(dateTime2),"%s Date: %s  ",option_algorithms[properties->modeltype].supportTime2des,decimal_date_to_real_date(decimalTime2));
    //g_print("%.*f = %s\n",15,decimalTime2,dateTime2);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTime2),dateTime2);

    properties->GtkInfo.spinbuttonTime2Flag = FALSE;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime2),decimalTime2);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToDividend),(365 * decimalTime2));
    properties->GtkInfo.spinbuttonTime2Flag = TRUE;
    gtk_widget_show(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToDividend);
    gtk_widget_show(properties->GtkInfo.labelTime2);
    gtk_widget_show(properties->GtkInfo.buttonCalendar2);
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend);
    //g_print("show spinbuttonTime2, labelTime2\n");

    if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonTime2) )
      g_signal_emit_by_name (properties->GtkInfo.comboboxModel, "grab-focus");

    if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonDaysToDividend) )
      g_signal_emit_by_name (properties->GtkInfo.comboboxModel, "grab-focus");
  }

  //

  if(option_algorithms[properties->modeltype].supportTime3 &&
     properties->GtkInfo.spinbuttonTime3InFocusflag == FALSE)
  {
    snprintf(dateTime3,sizeof(dateTime3),"%s Date: %s  ",option_algorithms[properties->modeltype].supportTime3des,decimal_date_to_real_date(decimalTime3));
    //g_print("%.*f = %s\n",15,decimalTime2,dateTime2);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTime3),dateTime3);

    properties->GtkInfo.spinbuttonTime3Flag = FALSE;
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime3),decimalTime3);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToDividend2),(365 * decimalTime3));
    properties->GtkInfo.spinbuttonTime3Flag = TRUE;
    gtk_widget_show(properties->GtkInfo.spinbuttonTime3);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToDividend2);
    gtk_widget_show(properties->GtkInfo.labelTime3);
    gtk_widget_show(properties->GtkInfo.buttonCalendar3);
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend2);
    //g_print("show spinbuttonTime2, labelTime2\n");

    if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonTime3) )
      g_signal_emit_by_name (properties->GtkInfo.comboboxModel, "grab-focus");

    if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonDaysToDividend2) )
      g_signal_emit_by_name (properties->GtkInfo.comboboxModel, "grab-focus");
  }

  //

  if( properties->decimalorcalendar == DECIMALS && !option_algorithms[properties->modeltype].perpetual )
  {
    snprintf(dateTime,sizeof(dateTime),"%s Date: %s", option_algorithms[properties->modeltype].supportTime1des, decimal_date_to_real_date(decimalTime));
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelTime1),dateTime);
    gtk_widget_show(properties->GtkInfo.labelTime1);

    if( (properties->GtkInfo.spinbuttonTimeInFocusflag) == FALSE)
    {
      //g_print("properties->GtkInfo.spinbuttonTimeInFocusflag == FALSE\t%d\n",properties->GtkInfo.spinbuttonTimeInFocusflag);
      properties->GtkInfo.spinbuttonTimeFlag = FALSE;
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime),decimalTime);
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToExpr),(365 * decimalTime));
      properties->GtkInfo.spinbuttonTimeFlag = TRUE;

      if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonTime) )
        g_signal_emit_by_name(properties->GtkInfo.comboboxModel, "grab-focus");

      if( gtk_widget_is_focus(properties->GtkInfo.spinbuttonDaysToExpr) )
        g_signal_emit_by_name(properties->GtkInfo.comboboxModel, "grab-focus");
    }
  }

  if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
  {
    g_print("Bond Calculate\n");

    char description[250]  = { 0 };
    char timeDecimal[250] = { 0 };
    char dateTime[250] = { 0 };
    char value[250] = { 0 };

    struct _data bonddata;
    bonddata = bonddispatch(properties);

    if( !option_algorithms[properties->modeltype].perpetual )
    {
      snprintf(description,sizeof(description),"Discount Factor T1");
      snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime2);
      snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime2));
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.discount_t2);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      snprintf(lineData,sizeof(lineData),"Discount Factor T1   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

      snprintf(description,sizeof(description),"Discount Factor T2");
      snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime);
      snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime));
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.discount_t1);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      snprintf(lineData,sizeof(lineData),"Discount Factor T2   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

      snprintf(description,sizeof(description),"Spot Rate T1");
      snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime2);
      snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime2));
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.spot_t2);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      snprintf(lineData,sizeof(lineData),"Spot Rate T1   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

      snprintf(description,sizeof(description),"Spot Rate T2");
      snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime);
      snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime));
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.spot_t1);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      snprintf(lineData,sizeof(lineData),"Spot Rate T2   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
      
      snprintf(description,sizeof(description),"Forward T1 : T2");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.forward);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      snprintf(lineData,sizeof(lineData),"Forward T1 : T2   %.*f\n", properties->precision,properties->data.forward);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "", X2, "", X3, "", X4, "", -1);

    }

    if( properties->data.bond_price )
    {
      snprintf(description,sizeof(description),"Bond Price");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.bond_price);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Bond Price   %.*f\n",properties->precision,properties->data.bond_price);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.pv_continous )
    {
      snprintf(description,sizeof(description),"Present Value");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.pv_continous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Present Value %.*f\n",properties->precision,properties->data.pv_continous);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.pv_discrete )
    {
      snprintf(description,sizeof(description),"Present Value Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.pv_discrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Present Value Discrete   %.*f\n",properties->precision,properties->data.pv_discrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.YTMContinous )
    {
      snprintf(description,sizeof(description),"YTM");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.YTMContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"YTM   %.*f\n",properties->precision,properties->data.YTMContinous);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.YTMDiscrete )
    {
      snprintf(description,sizeof(description),"YTM Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.YTMDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"YTM Discrete   %.*f\n",properties->precision,properties->data.YTMDiscrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.durationContinous )
    {
      snprintf(description,sizeof(description),"Duration");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.durationContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Duration   %.*f\n",properties->precision,properties->data.durationContinous);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.durationDiscrete )
    {
      snprintf(description,sizeof(description),"Duration Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.durationDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Duration Discrete   %.*f\n",properties->precision,properties->data.durationDiscrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.durationModifiedDiscrete )
    {
      snprintf(description,sizeof(description),"Duration Modified Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.durationModifiedDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Duration Modified Discrete   %.*f\n",properties->precision,properties->data.durationModifiedDiscrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.durationMacaulayDiscrete )
    {
      snprintf(description,sizeof(description),"Duration Macaulay Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.durationMacaulayDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Duration Macaulay Discrete   %.*f\n",properties->precision,properties->data.durationMacaulayDiscrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.convexityContinous )
    {
      snprintf(description,sizeof(description),"Convexity");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.convexityContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Convexity %.*f\n",properties->precision,properties->data.convexityContinous);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.convexityDiscrete )
    {
      snprintf(description,sizeof(description),"Convexity Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.convexityDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Convexity Discrete %.*f\n",properties->precision,properties->data.convexityDiscrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.call )
    {
      snprintf(description,sizeof(description),"Call");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.call);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"Call   %.*f\n",properties->precision,properties->data.call);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.irr )
    {
      snprintf(description,sizeof(description),"IRR");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.irr);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"IRR   %.*f\n",properties->precision,properties->data.irr);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.irr_discrete )
    {
      snprintf(description,sizeof(description),"IRR Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.irr_discrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"IRR Discrete   %.*f\n",properties->precision,properties->data.irr_discrete);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->data.uirr )
    {
      snprintf(description,sizeof(description),"UIRR");
      timeDecimal[0] = dateTime[0] = 0; 
      strncpy(value, "True", sizeof(value));
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      snprintf(lineData,sizeof(lineData),"UIRR   True\n");
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    if( properties->textExport == true && properties->fileExport == false)
    {
      text_export(properties, dataExport);
    } else if( properties->textExport == true && properties->fileExport == true)
    {
      file_export(properties, dataExport);
    }

    gettimeofday(&end, NULL);
    c1 = clock();

    g_print("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000) - (start.tv_sec + (double) start.tv_usec / 1000000)));
    g_print("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);    

    return TRUE;

  } // if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )

#ifdef FINRECIPES

  if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )
  {
    g_print("Termstructure Calculate\n");

    properties->data.term = 0;

    struct _data termstructuredata;
    properties->data.term_model = properties->data.modeltype;
    termstructuredata = termstructure(&properties->data);

    char description[250] = { 0 };
    char timeDecimal[250] = { 0 };
    char dateTime[250] = { 0 };
    char value[250] = { 0 };

    g_print("*discount factor t1 = %.*f:%.*f\n", properties->precision,decimalTime,properties->precision,properties->data.discount_t1);
    g_print("*discount factor t2 = %.*f:%.*f\n", properties->precision,decimalTime2,properties->precision,properties->data.discount_t2);
    g_print("*spot rate t1 = %.*f:%.*f\n", properties->precision,decimalTime,properties->precision,properties->data.spot_t1);
    g_print("*spot rate t2 = %.*f:%.*f\n", properties->precision,decimalTime2,properties->precision,properties->data.spot_t2);
    g_print("*forward rate from t1= %.*f to t2 %.*f:%.*f\n",properties->precision,decimalTime,properties->precision,decimalTime2,properties->precision,properties->data.forward);

    snprintf(description,sizeof(description),"Discount Factor T1");
    snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime2);
    snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime2));
    snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.discount_t2);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    snprintf(lineData,sizeof(lineData),"Discount Factor T1   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    snprintf(description,sizeof(description),"Discount Factor T2");
    snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime);
    snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime));
    snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.discount_t1);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);
    snprintf(lineData,sizeof(lineData),"Discount Factor T2   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    snprintf(description,sizeof(description),"Spot Rate T1");
    snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime2);
    snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime2));
    snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.spot_t2);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    snprintf(lineData,sizeof(lineData),"Spot Rate T1   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    snprintf(description,sizeof(description),"Spot Rate T2");
    snprintf(timeDecimal,sizeof(timeDecimal),"%.*f", properties->precision,decimalTime);
    snprintf(dateTime,sizeof(dateTime),"%s", decimal_date_to_real_date(decimalTime));
    snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.spot_t1);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    snprintf(lineData,sizeof(lineData),"Spot Rate T2   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    snprintf(description,sizeof(description),"Forward T1 : T2");
    timeDecimal[0] = dateTime[0] = 0; 
    snprintf(value,sizeof(value),"%.*f", properties->precision,properties->data.forward);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    snprintf(lineData,sizeof(lineData),"Forward T1 : T2   %.*f\n", properties->precision,properties->data.forward);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    if( properties->data.term )
      delete properties->data.term;

    if( properties->textExport == true && properties->fileExport == false)
    {
      text_export(properties, dataExport);
    } else if( properties->textExport == true && properties->fileExport == true)
    {
      file_export(properties, dataExport);
    }

    gettimeofday(&end, NULL);
    c1 = clock();

    g_print("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000) - (start.tv_sec + (double) start.tv_usec / 1000000)));
    g_print("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);        
    
    return TRUE;

  } // if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )

#endif // FINRECIPES

  if( properties->format == DECIMAL_FUTURE )
  {
    g_print("DECIMAL_FUTURE\n");
    //g_print("properties->decimalorcalendar = %d\n", properties->decimalorcalendar);

    struct _data futuredata;
    futuredata = future(&properties->data);

    char textSpot[200] = { 0 };
    snprintf(textSpot,sizeof(textSpot),"%.*f",properties->precision,properties->data.price);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Spot Price", X2, textSpot, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Spot Price",textSpot);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    char textFuturesPrice[200] = { 0 };
    snprintf(textFuturesPrice,sizeof(textFuturesPrice),"%.*f (%s)",properties->precision,properties->data.future,(properties->data.future > properties->data.price ? "Cotango" : "Backwardation") );
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Futures Price", X2, textFuturesPrice, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Futures Price",textFuturesPrice);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    char textRate[200] = { 0 };
    snprintf(textRate,sizeof(textRate),"%.*f%%",properties->precision,properties->data.rate*100);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Interest Rate", X2, textRate, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Interest Rate", textRate);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    char textBasis[200] = { 0 };
    snprintf(textBasis,sizeof(textBasis),"%.*f", properties->precision,properties->data.price-properties->data.future);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Basis", X2, textBasis, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Basis", textBasis);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

    if( option_algorithms[properties->modeltype].supportDividend )
    {
      char textDiv[200] = { 0 };
      snprintf(textDiv,sizeof(textDiv),"%.*f", properties->precision,properties->data.dividend);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Div yield underlying", X2, textDiv, -1);

      snprintf(lineData,sizeof(lineData)," %s, %s\n", "Div yield underlying", textDiv);
      strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    }

    char textExpr[200] = { 0 };
    snprintf(textExpr,sizeof(textExpr),"%s",decimal_date_to_real_date(properties->data.t[0]-properties->data.te));
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Expiration Date", X2, textExpr, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Expiration Date",textExpr);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
    
    char textTicker[200] = { 0 };
    snprintf(textTicker,sizeof(textTicker),"%s%02d",future_codes[decimal_date_to_int_month(adjust_to_current_time(properties->data.t[0]-properties->data.te,0))],decimal_date_to_int_year(adjust_to_current_time(properties->data.t[0]-properties->data.te,0)));

    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Ticker", X2, textTicker, -1);

    snprintf(lineData,sizeof(lineData)," %s, %s\n", "Ticker", textTicker);
    strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);

  } // if( properties->format == DECIMAL_FUTURE )

  if( properties->format == CALENDAR_FUTURE )
  {
    g_print("CALENDAR_FUTURE\n");
    //g_print("properties->decimalorcalendar = %d\n",properties->decimalorcalendar);

    int index = 0;

    struct _data futuredata;
    struct _data futuredata2;

    char textTicker[200] = { 0 };
    char textTicker2[200] = { 0 };
    char textMonthDayYear[200] = { 0 };
    char textMonthDayYear2[200] = { 0 };
    char textDecimalDate[200] = { 0 };
    char textDecimalDate2[200] = { 0 };
    char textDaysToExpr[200] = { 0 };
    char textDaysToExpr2[200] = { 0 };
    char textSpread[200] = { 0 };
    char textSpreadTicker[600] = { 0 };

    double leg1;
    double leg2;

    while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
    {
      properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
      //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

      futuredata = future(&properties->data);
      leg1 = properties->data.future;
      
      snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,properties->data.future);
      snprintf(textTicker,sizeof(textTicker),"%s%02d",future_codes[*properties->expiration_month],*properties->expiration_year);
      snprintf(textMonthDayYear,sizeof(textMonthDayYear),"%s%2d %02.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);
      snprintf(textDecimalDate,sizeof(textDecimalDate),"%.*f",properties->precision,properties->data.t[0]);
      //g_print("textDecimalDate %.*f\n",properties->precision,properties->data.t[0]);
      snprintf(textDaysToExpr,sizeof(textDaysToExpr),"%.*f",properties->precision,(365*properties->data.t[0]));
      //g_print("textDaysToExpr = %.*f\n",properties->precision,(365*properties->data.t[0]));

      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

      if( properties->spreads == 0 )
      {
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textMonthDayYear, X2, textPrice, X3, textDaysToExpr, X4, textDecimalDate, X5, textTicker, -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textMonthDayYear, textPrice, textDaysToExpr, textDecimalDate, textTicker});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

      } else if( properties->spreads == 1 )
      {
        properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration2,properties->expiration_time,0);
        //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

        futuredata2 = future(&properties->data);
        leg2 = properties->data.future;

        snprintf(textPrice2,sizeof(textPrice2),"%.*f",properties->precision,properties->data.future);
        snprintf(textTicker2,sizeof(textTicker2),"%s%02d",future_codes[*properties->expiration_month2],*properties->expiration_year2);
        snprintf(textMonthDayYear2,sizeof(textMonthDayYear2),"%s%2d %02.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);
        snprintf(textDecimalDate2,sizeof(textDecimalDate2),"%.*f",properties->precision,properties->data.t[0]);
        //g_print("textDecimalDate %.*f\n",properties->precision,properties->data.t[0]);
        snprintf(textDaysToExpr2,sizeof(textDaysToExpr2),"%.*f",properties->precision,(365*properties->data.t[0]));
        //g_print("textDaysToExpr = %.*f\n",properties->precision,(365*properties->data.t[0]));
        snprintf(textSpread,sizeof(textSpread),"%.*f",properties->precision, (double) leg1 - (double) leg2);
        snprintf(textSpreadTicker,sizeof(textSpreadTicker),"%s - %s",textTicker, textTicker2);

        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textMonthDayYear, X2, textPrice, X3, textDaysToExpr, X4, textDecimalDate, X5, textTicker, X6, textMonthDayYear2, X7, textPrice2, X8, textDaysToExpr2, X9, textDecimalDate2, X10, textTicker2, X11, textSpread, X12, textSpreadTicker, -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textMonthDayYear, textPrice, textDaysToExpr, textDecimalDate, textTicker, textMonthDayYear2, textPrice2, textDaysToExpr2, textDecimalDate2, textTicker2, textSpread, textSpreadTicker});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

      }

      properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
      properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

      if( index++ >= 17 + (int) ((double) 17 * (double) rowMultiplier ))
      {
        g_print("%d rows of options and analytics created\n", index);
        break;
      }
      
    }

    /* reset pointers */
    properties->expiration_month=properties->start_expiration_month;
    properties->days_to_expiration=properties->start_days_to_expiration;
    properties->expiration_year=properties->start_expiration_year;
    properties->time_to_expiration=properties->start_time_to_expiration;

    /* reset pointers */
    properties->expiration_month2=properties->start_expiration_month2;
    properties->days_to_expiration2=properties->start_days_to_expiration2;
    properties->expiration_year2=properties->start_expiration_year2;
    properties->time_to_expiration2=properties->start_time_to_expiration2;

  } // if( properties->format == CALENDAR_FUTURE )

  if( properties->format == DECIMAL_GREEKS )
  {
      g_print("DECIMAL_GREEKS\n");
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      double i;
      index = 0;
      for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
      {
         properties->data.calldelta = NAN;
         properties->data.putdelta = NAN;
         properties->data.callElasticity = NAN;
         properties->data.putElasticity = NAN;
         properties->data.gamma = NAN;
         properties->data.vega = NAN;
         properties->data.calltheta = NAN;
         properties->data.puttheta = NAN;
         properties->data.callrho = NAN;
         properties->data.putrho = NAN;

         if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
           )
         {

         if( i <= 0 || fabs(i-0.0) < epsilon )
         {
           i = 0;
        
           if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
           {
             properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
           } else
           {
             properties->strike_offset = properties->strike_offset + 2.5;
           }
           continue;
         }

         if ( option_algorithms[properties->modeltype].supportPrice )
           snprintf(textPrice,sizeof(textPrice),"%.*f", properties->precision,price);

         if( strike_control[properties->strikestoogle].incrementor == 0 )
           properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
         else
           properties->data.strike = i;

         if ( option_algorithms[properties->modeltype].supportStrikes )
         {
           if( modf(i,&properties->discard) == .5 )
           {
             snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
           } else
           {
             snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
           }
         }

         //g_print("price = %f, strike = %f, rate = %f, v = %f, div = %f, z = %f, b = %f, j = %f, p = %f", price, i, rate, volatility, dividend,properties->data.UseZ, properties->data.UseB, properties->data.UseJ, properties->data.UseP);
        
         struct _data optiondata;

         if( option_algorithms[properties->modeltype].supportCalls )
         {
           optiondata = option_call(&properties->data);
           snprintf(&textCall[0][0],sizeof(textCall[0]),"%.*f",properties->precision,optiondata.call);
         }

         if( option_algorithms[properties->modeltype].supportPuts )
         {
           optiondata = option_put(&properties->data);
           snprintf(&textPut[0][0],sizeof(textPut[0]),"%.*f",properties->precision,optiondata.put);
         }

         process_greeks(properties, &properties->data, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0], &textCallElasticity[0], &textPutElasticity[0]);

         gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
         gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textStrike, X3, textCall[0], X4, textPut[0], X5, textCallDelta, X6, textPutDelta, X7, textGamma, X8, textVega, X9, textCallTheta, X10, textPutTheta, X11, textCallRho, X12, textPutRho, X13, textCallElasticity, X14, textPutElasticity, -1);

         if( properties->textExport == true )
         {
           fill_line(lineData, sizeof(lineData),
                std::vector<string>{textPrice, textStrike, textCall[0], textPut[0], textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textCallElasticity, textPutElasticity});
           strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
         }

         if( index++ >= 17 + (int) ((double) 17 * (double) rowMultiplier ))
         {
           g_print("%d rows of options and analytics created\n", index);
           break;
         }

         if( !option_algorithms[properties->modeltype].supportStrikes )
          break;

         }
      }

  } // if( properties->format == DECIMAL_GREEKS )

  else if( properties->format == CALENDAR_CUSTOM )
  {
    g_print("CALENDAR_CUSTOM\n");
    index = 0;

    if( properties->spreads == 1 )
    {
      totalCounter = 0;

      while( (*properties->expiration_month2!=-1) && (*properties->days_to_expiration2!=-1) && (*properties->expiration_year2!=-1) )
      {         
        double i = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        cumStrikeLeg2 += i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          snprintf(textStrikeLeg2[totalCounter],sizeof(textStrikeLeg2[totalCounter]),"%.*f",properties->precision,i);
        }

        if( strike_control[properties->strikestoogle].incrementor == 0 )
           properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
           properties->data.strike = i;

        properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration2,properties->expiration_time,0);
        //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
        struct _data optiondata;
          
        if( option_algorithms[properties->modeltype].supportCalls )
        {
          optiondata = option_call(&properties->data);
          callLeg2[totalCounter] = optiondata.call;
        }

        if( option_algorithms[properties->modeltype].supportPuts )
        {
          optiondata = option_put(&properties->data);
          putLeg2[totalCounter] = optiondata.put;
        }

        snprintf(&textMonthLeg2[totalCounter][0],sizeof(textMonthLeg2[totalCounter]),
                 "%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

        snprintf(&textMonthLeg2[totalCounter][0],sizeof(textMonthLeg2[totalCounter]),
                 "%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

        properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

        totalCounter++;

        if( index++ >= 18 + (int) ((double) 18 * (double) rowMultiplier ))
        {
          g_print("%d rows of options and analytics created\n", index);
          break;
        }
 
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /* reset pointers */
      properties->expiration_month2=properties->start_expiration_month2;
      properties->days_to_expiration2=properties->start_days_to_expiration2;
      properties->expiration_year2=properties->start_expiration_year2;
      properties->time_to_expiration2=properties->start_time_to_expiration2;

    }

    index = 0;
    totalCounter = 0;
    while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
    {
      double i = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike));
      cumStrikeLeg1 += i;

      if( strike_control[properties->strikestoogle].incrementor == 0 )
         properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
      else
         properties->data.strike = i;

      if ( option_algorithms[properties->modeltype].supportStrikes )
        snprintf(textStrike,sizeof(textStrike),"%.*f", properties->precision,properties->data.strike);

      if ( option_algorithms[properties->modeltype].supportPrice )
        snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

      properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
      //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
      struct _data optiondata;
          
      if( option_algorithms[properties->modeltype].supportCalls )
      {
        optiondata = option_call(&properties->data);
        snprintf(&textCall[0][0],sizeof(textCall[0]),"%.*f",properties->precision,optiondata.call);
      }

      if( option_algorithms[properties->modeltype].supportPuts )
      {
        optiondata = option_put(&properties->data);
        snprintf(&textPut[0][0],sizeof(textPut[0]),"%.*f",properties->precision,optiondata.put);
      }

      snprintf(textMonth,sizeof(textMonth),"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

      char textDecimalDate[200]  = { 0 };
      snprintf(textDecimalDate,sizeof(textDecimalDate),"%.*f",properties->precision,properties->data.t[0]);

      char textDaysToExpr[200] = { 0 };
      snprintf(textDaysToExpr,sizeof(textDaysToExpr),"%.*f",properties->precision,(365*properties->data.t[0]));

      process_greeks(properties, &properties->data, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0], &textCallElasticity[0], &textPutElasticity[0]);

      if ( option_algorithms[properties->modeltype].supportStrikes )
        snprintf(textLegacyCall,sizeof(textLegacyCall),"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
      else
        snprintf(textLegacyCall,sizeof(textLegacyCall),"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]);

      if ( option_algorithms[properties->modeltype].supportStrikes )
        snprintf(textLegacyPut,sizeof(textLegacyPut),"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
      else
        snprintf(textLegacyPut,sizeof(textLegacyPut),"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

      if( properties->spreads == 0 )
      {
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut});
          strncat(dataExport,lineData,strlen(dataExport) - sizeof(lineData)-1);
        }

      } else if( properties->spreads == 1 )
      {
        char textCallLeg2[200] = { 0 };
        char textPutLeg2[200] = { 0 };
        char textCallCallSpread[200] = { 0 };
        char textPutPutSpread[200] = { 0 };
        char textCallPutSpread[200] = { 0 };
        char textPutCallSpread[200] = { 0 };

        if( option_algorithms[properties->modeltype].supportCalls )
        {
          snprintf(textCallLeg2,sizeof(textCallLeg2),"%.*f",properties->precision,callLeg2[totalCounter]);
          snprintf(textCallCallSpread,sizeof(textCallCallSpread),"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
        }

        if( option_algorithms[properties->modeltype].supportPuts )
        {
          snprintf(textPutLeg2,sizeof(textPutLeg2),"%.*f",properties->precision,putLeg2[totalCounter]);
          snprintf(textPutPutSpread,sizeof(textPutPutSpread),"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
        }

        if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
        {
          snprintf(textCallPutSpread,sizeof(textCallPutSpread),"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
          snprintf(textPutCallSpread,sizeof(textPutCallSpread),"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
        }

        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

      }

      properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

      totalCounter++;

     if( index++ >= 18 + (int) ((double) 18 * (double) rowMultiplier ))
      {
        g_print("%d rows of options and analytics created\n", index);
        break;
      }

    }

    /* reset pointers */
    properties->expiration_month=properties->start_expiration_month;
    properties->days_to_expiration=properties->start_days_to_expiration;
    properties->expiration_year=properties->start_expiration_year;
    properties->time_to_expiration=properties->start_time_to_expiration;

    //g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);
    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );
    //g_print("properties->verticalSpread = %d\n",properties->verticalSpread);

  } // if( properties->format == CALENDAR_CUSTOM )

  else if( properties->format == CALENDAR_OPTIONS6 )
  {
    g_print("CALENDAR_OPTIONS6\n");

    int counter = 0;

    double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
    double i;
    index = 0;
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
      properties->data.calldelta = NAN;
      properties->data.putdelta = NAN;
      properties->data.callElasticity = NAN;
      properties->data.putElasticity = NAN;
      properties->data.gamma = NAN;
      properties->data.vega = NAN;
      properties->data.calltheta = NAN;
      properties->data.puttheta = NAN;
      properties->data.callrho = NAN;
      properties->data.putrho = NAN;

      if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
          ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
        )
      {
        if( i <= 0 || fabs(i-0.0) < epsilon )
        {
          i = 0;
        
          if ( option_algorithms[properties->modeltype].supportStrikes )
          {
            if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }
          }
          continue;
        }

        if ( option_algorithms[properties->modeltype].supportPrice )
          snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
         properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( modf(i,&properties->discard) == .5 )
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
          } else
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
          }
        }

        counter = 0;

        while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
        {
          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

          struct _data optiondata;

          if( option_algorithms[properties->modeltype].supportCalls )
          {
            optiondata = option_call(&properties->data);
            snprintf(&textCall[counter][0],sizeof(textCall[counter]),"%.*f",properties->precision,optiondata.call);
          }
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            snprintf(&textPut[counter][0],sizeof(textPut[counter]),"%.*f",properties->precision,optiondata.put);
          }

          properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

          if( ++counter >= 3 )
          {
            break;
          }
        }

        /* reset pointers */
        properties->expiration_month=properties->start_expiration_month;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_year=properties->start_expiration_year;
        properties->time_to_expiration=properties->start_time_to_expiration;
        
        gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textStrike, X3, textCall[0], X4, textCall[1], X5, textCall[2], X6, textPut[0], X7, textPut[1], X8, textPut[2], -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textPrice, textStrike, textCall[0], textCall[1], textCall[2], textPut[0], textPut[1], textPut[2]});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

        if( index++ >= 18 + (int) ((double) 18 * (double) rowMultiplier ))
        {
          g_print("%d rows of options and analytics created\n", index);
          break;
        }   

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }
    
  } // if( properties->format == CALENDAR_OPTIONS6 )

  else if( properties->format == CALENDAR_OPTIONS5 )
  {
    g_print("CALENDAR_OPTIONS5\n");
    int counter = 0;

    double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
    double i;
    index = 0;
    if( option_algorithms[properties->modeltype].supportCalls )
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
      properties->data.calldelta = NAN;
      properties->data.putdelta = NAN;
      properties->data.callElasticity = NAN;
      properties->data.putElasticity = NAN;
      properties->data.gamma = NAN;
      properties->data.vega = NAN;
      properties->data.calltheta = NAN;
      properties->data.puttheta = NAN;
      properties->data.callrho = NAN;
      properties->data.putrho = NAN;

      if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
          ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
        )
      {
        if( i <= 0 || fabs(i-0.0) < epsilon )
        {
          i = 0;

          if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
          {
            properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
          } else
          {
             properties->strike_offset = properties->strike_offset + 2.5;
          }
          continue;
        }

        if ( option_algorithms[properties->modeltype].supportPrice )
          snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
          properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )        
        {
          if( modf(i,&properties->discard) == .5 )
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
          } else
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
          }
        }

        counter = 0;
        while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
        {         
          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
          struct _data optiondata;
          
          if( option_algorithms[properties->modeltype].supportCalls )
          {
            optiondata = option_call(&properties->data);
            snprintf(&textCall[counter][0],sizeof(textCall[counter]),"%c %.*f",tolower(option_algorithms[properties->modeltype].call[0]),properties->precision,optiondata.call);
          }

          properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

          if( ++counter >= 8 )
          {
            break;
          }
        }
        /* reset pointers */
        properties->expiration_month=properties->start_expiration_month;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_year=properties->start_expiration_year;
        properties->time_to_expiration=properties->start_time_to_expiration;

        gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textStrike, X3, textCall[0], X4, textCall[1], X5, textCall[2], X6, textCall[3], X7, textCall[4], X8, textCall[5], X9, textCall[6], X10, textCall[7], -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textPrice, textStrike, textCall[0], textCall[1], textCall[2], textCall[3], textCall[4], textCall[5], textCall[6], textCall[7]});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

        if( index++ >= 8 + (int) ((double) 8 * (double) rowMultiplier ))
        {
          g_print("%d rows of call options and analytics created\n", index);
          break;
        }   

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    index = 0;
    if( option_algorithms[properties->modeltype].supportPuts )
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
      properties->data.calldelta = NAN;
      properties->data.putdelta = NAN;
      properties->data.callElasticity = NAN;
      properties->data.putElasticity = NAN;
      properties->data.gamma = NAN;
      properties->data.vega = NAN;
      properties->data.calltheta = NAN;
      properties->data.puttheta = NAN;
      properties->data.callrho = NAN;
      properties->data.putrho = NAN;

      if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
          ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
        )
      {
        if( i <= 0 || fabs(i-0.0) < epsilon )
        {
          i = 0;
        
          if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
          {
            properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
          } else
          {
            properties->strike_offset = properties->strike_offset + 2.5;
          }
          continue;
        }

        if ( option_algorithms[properties->modeltype].supportPrice )
          snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
         properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( modf(i,&properties->discard) == .5 )
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
          } else
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
          }
        }

        counter = 0;

        while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
        {         
          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
          struct _data optiondata;
          
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            snprintf(&textPut[counter][0],sizeof(textPut[counter]),"%c %.*f",tolower(option_algorithms[properties->modeltype].put[0]),properties->precision,optiondata.put);
          }

          properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

          if( ++counter >= 8 )
          {
            break;
          }
        }
        /* reset pointers */
        properties->expiration_month=properties->start_expiration_month;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_year=properties->start_expiration_year;
        properties->time_to_expiration=properties->start_time_to_expiration;

        gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textStrike, X3, textPut[0], X4, textPut[1], X5, textPut[2], X6, textPut[3], X7, textPut[4], X8, textPut[5], X9, textPut[6], X10, textPut[7], -1);

        if( properties->textExport == true )
        {
          fill_line(lineData,sizeof(lineData),
               std::vector<string>{textPrice, textStrike, textPut[0], textPut[1], textPut[2], textPut[3], textPut[4], textPut[5], textPut[6], textPut[7]});
          strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
        }

        if( index++ >= 8 + (int) ((double) 8 * (double) rowMultiplier ))
        {
          g_print("%d rows of put options and analytics created\n", index);
          break;
        }

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;

        //g_print("index = %d\n",index);
      }
    }
  } // if( properties->format == CALENDAR_OPTIONS5 )

  else if( properties->format == CALENDAR_OPTIONS4 )
  {
    g_print("CALENDAR_OPTIONS4\n");
    int counter = 0;

    if( properties->spreads == 1 )
    {
      totalCounter = 0;
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      double i;
      index = 0;

      for(i=(properties->strike_offset2+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset2+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
      {
        properties->data.calldelta = NAN;
        properties->data.putdelta = NAN;
        properties->data.callElasticity = NAN;
        properties->data.putElasticity = NAN;
        properties->data.gamma = NAN;
        properties->data.vega = NAN;
        properties->data.calltheta = NAN;
        properties->data.puttheta = NAN;
        properties->data.callrho = NAN;
        properties->data.putrho = NAN;

        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
            ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
            ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
          )
        {
          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;
        
            if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
            {
              properties->strike_offset2 = properties->strike_offset2 + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset2 = properties->strike_offset2 + 2.5;
            }
            continue;
          }

          cumStrikeLeg2 += i;
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

          counter = 0;
          while( (*properties->expiration_month2!=-1) && (*properties->days_to_expiration2!=-1) && (*properties->expiration_year2!=-1) )
          {

            if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
            {
               properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
               cumStrikeLeg2 = properties->data.strike;
            }
            else if( strike_control[properties->strikestoogle].incrementor == 0 )
            {
               properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike));
               cumStrikeLeg2 = properties->data.strike;
            }
            else
               properties->data.strike = i;

            if ( option_algorithms[properties->modeltype].supportStrikes )
            {
              if( modf(i,&properties->discard) == .5 )
              {
                snprintf(textStrikeLeg2[totalCounter],sizeof(textStrikeLeg2[totalCounter]),"%.*f", 1,properties->data.strike);
              } else
              {
                snprintf(textStrikeLeg2[totalCounter],sizeof(textStrikeLeg2[totalCounter]),"%.*f",strike_control[properties->strikestoogle].precision,properties->data.strike);
              }

              //g_print("textStrikeLeg2[totalCounter] = %s\n",textStrikeLeg2[totalCounter]);
            }

            properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration2,properties->expiration_time,0);

            struct _data optiondata;
          
            if( option_algorithms[properties->modeltype].supportCalls )
            {
              optiondata = option_call(&properties->data);
              callLeg2[totalCounter] = optiondata.call;
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              optiondata = option_put(&properties->data);
              putLeg2[totalCounter] = optiondata.put;
            }

            snprintf(&textMonthLeg2[totalCounter][0],sizeof(textMonthLeg2[totalCounter]),"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

            properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

            totalCounter++;

            if( ++counter >= 4 )
            {
              break;
            }            
          }

          /* reset pointers */
          properties->expiration_month2=properties->start_expiration_month2;
          properties->days_to_expiration2=properties->start_days_to_expiration2;
          properties->expiration_year2=properties->start_expiration_year2;
          properties->time_to_expiration2=properties->start_time_to_expiration2;

          if( index++ >= 4 + (int) ((double) 4 * (double) rowMultiplier ))
          {
            g_print("%d rows of options and analytics created\n", index * counter);
            break;
          }

          if( !option_algorithms[properties->modeltype].supportStrikes )
            break;
        }
      }
    }

    double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
    double i;
    index = 0;
    totalCounter = 0;
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
      properties->data.calldelta = NAN;
      properties->data.putdelta = NAN;
      properties->data.callElasticity = NAN;
      properties->data.putElasticity = NAN;
      properties->data.gamma = NAN;
      properties->data.vega = NAN;
      properties->data.calltheta = NAN;
      properties->data.puttheta = NAN;
      properties->data.callrho = NAN;
      properties->data.putrho = NAN;

      if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
          ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
        )
      {
        if( i <= 0 || fabs(i-0.0) < epsilon )
        {
          i = 0;
        
          if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
          {
            properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
          } else
          {
            properties->strike_offset = properties->strike_offset + 2.5;
          }
          continue;
        }

        if ( option_algorithms[properties->modeltype].supportPrice )
          snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

        cumStrikeLeg1 += i;

        if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
        {
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike));
          cumStrikeLeg1 = properties->data.strike;
        }
        else if( strike_control[properties->strikestoogle].incrementor == 0 )
        {
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
          cumStrikeLeg1 = properties->data.strike;
        }
        else
          properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( modf(i,&properties->discard) == .5 )
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
          } else
          {
            snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
          }
        }

        counter = 0;
        while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
        {         
          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
          struct _data optiondata;
          
          if( option_algorithms[properties->modeltype].supportCalls )
          {
            optiondata = option_call(&properties->data);
            snprintf(&textCall[0][0],sizeof(textCall[0]),"%.*f",properties->precision,optiondata.call);
          }
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            snprintf(&textPut[0][0],sizeof(textPut[0]),"%.*f",properties->precision,optiondata.put);
          }

          snprintf(textMonth,sizeof(textMonth),"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

          char textDecimalDate[200] = { 0 };
          snprintf(textDecimalDate,sizeof(textDecimalDate),"%.*f",properties->precision,properties->data.t[0]);

          char textDaysToExpr[200] = { 0 };
          snprintf(textDaysToExpr,sizeof(textDaysToExpr),"%.*f",properties->precision,(365*properties->data.t[0]));

          process_greeks(properties, &properties->data, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0], &textCallElasticity[0], &textPutElasticity[0]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            snprintf(textLegacyCall,sizeof(textLegacyCall),"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            snprintf(textLegacyCall,sizeof(textLegacyCall),"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]); 

          if ( option_algorithms[properties->modeltype].supportStrikes )
            snprintf(textLegacyPut,sizeof(textLegacyPut),"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            snprintf(textLegacyPut,sizeof(textLegacyPut),"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
          gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

          if( properties->spreads == 0 )
          {
            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

            if( properties->textExport == true )
            {
              fill_line(lineData,sizeof(lineData),
                   std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut});
              strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
            }

          } else if( properties->spreads == 1 )
          {
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            char textCallLeg2[200] = { 0 };
            char textPutLeg2[200] = { 0 };
            char textCallCallSpread[200] = { 0 };
            char textPutPutSpread[200] = { 0 };
            char textCallPutSpread[200] = { 0 };
            char textPutCallSpread[200] = { 0 };

            if( option_algorithms[properties->modeltype].supportCalls )
            {
              snprintf(textCallLeg2,sizeof(textCallLeg2),"%.*f",properties->precision,callLeg2[totalCounter]);
              snprintf(textCallCallSpread,sizeof(textCallCallSpread),"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              snprintf(textPutLeg2,sizeof(textPutLeg2),"%.*f",properties->precision,putLeg2[totalCounter]);
              snprintf(textPutPutSpread,sizeof(textPutPutSpread),"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
            {
              snprintf(textCallPutSpread,sizeof(textCallPutSpread),"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
              snprintf(textPutCallSpread,sizeof(textPutCallSpread),"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
            }

            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

            if( properties->textExport == true )
            {
              fill_line(lineData,sizeof(lineData),
                   std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread});
              strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
            }

            totalCounter++;
          }
          
          properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

          if( ++counter >= 4 )
          {
            break;
          }
        }
        /* reset pointers */
        properties->expiration_month=properties->start_expiration_month;
        properties->days_to_expiration=properties->start_days_to_expiration;
        properties->expiration_year=properties->start_expiration_year;
        properties->time_to_expiration=properties->start_time_to_expiration;

        if( index++ >= 4 + (int) ((double) 4 * (double) rowMultiplier ))       
        {
          g_print("%d rows of options and analytics created\n", index * counter);
          break;
        }

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }

    //g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);
    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );
    //g_print("properties->verticalSpread = %d\n",properties->verticalSpread);

  } // if( properties->format == CALENDAR_OPTIONS4 )

  else if( properties->format == CALENDAR_OPTIONS3 )
  {

    g_print("CALENDAR_OPTIONS3\n");
    int counter = 0;
    double i;

    if( properties->spreads == 1 )
    {
      totalCounter = 0;

      while( (*properties->expiration_month2!=-1) && (*properties->days_to_expiration2!=-1) && (*properties->expiration_year2!=-1) )
      {         
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
        index = 0;

        for(i=(properties->strike_offset2+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset2+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
        {
          properties->data.calldelta = NAN;
          properties->data.putdelta = NAN;
          properties->data.callElasticity = NAN;
          properties->data.putElasticity = NAN;
          properties->data.gamma = NAN;
          properties->data.vega = NAN;
          properties->data.calltheta = NAN;
          properties->data.puttheta = NAN;
          properties->data.callrho = NAN;
          properties->data.putrho = NAN;

          if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
              ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
              ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
            )
          {
            if( i <= 0 || fabs(i-0.0) < epsilon )
            {
              i = 0;
        
              if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
              {
                properties->strike_offset2 = properties->strike_offset2 + strike_control[properties->strikestoogle].xcontrol;
              } else
              {
                properties->strike_offset2 = properties->strike_offset2 + 2.5;
              }
              continue;
            }

            cumStrikeLeg2 += i;

            if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
            {
               properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
               cumStrikeLeg2 = properties->data.strike;
            }
            else if( strike_control[properties->strikestoogle].incrementor == 0 )
            {
               properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike));
               cumStrikeLeg2 = properties->data.strike;
            }
            else
               properties->data.strike = i;

            if ( option_algorithms[properties->modeltype].supportStrikes )
            {
              if( modf(i,&properties->discard) == .5 )
              {
                snprintf(textStrikeLeg2[totalCounter],sizeof(textStrikeLeg2[totalCounter]),"%.*f", 1,properties->data.strike);
              } else
              {
                snprintf(textStrikeLeg2[totalCounter],sizeof(textStrikeLeg2[totalCounter]),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
              }
            }

            properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration2,properties->expiration_time,0);
            //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
            struct _data optiondata;
          
            if( option_algorithms[properties->modeltype].supportCalls )
            {
              optiondata = option_call(&properties->data);
              callLeg2[totalCounter] = optiondata.call;
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              optiondata = option_put(&properties->data);
              putLeg2[totalCounter] = optiondata.put;
            }

            snprintf(&textMonthLeg2[totalCounter][0],sizeof(textMonthLeg2[totalCounter]),"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

            totalCounter++;

            if( index++ >= 4 + (int) ((double) 4 * (double) rowMultiplier ))
            {
              g_print("%d rows of options and analytics created\n", index);
              break;
            }

            if( !option_algorithms[properties->modeltype].supportStrikes )
              break;
          }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

        if( ++counter >= (option_algorithms[properties->modeltype].supportStrikes ? 4 : 20) )
        {
          break;
        }
      }

      /* reset pointers */
      properties->expiration_month2=properties->start_expiration_month2;
      properties->days_to_expiration2=properties->start_days_to_expiration2;
      properties->expiration_year2=properties->start_expiration_year2;
      properties->time_to_expiration2=properties->start_time_to_expiration2;
    }

    counter = 0;
    totalCounter = 0;

    while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
    {         
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      double i;
      index = 0;

      for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
      {
        properties->data.calldelta = NAN;
        properties->data.putdelta = NAN;
        properties->data.callElasticity = NAN;
        properties->data.putElasticity = NAN;
        properties->data.gamma = NAN;
        properties->data.vega = NAN;
        properties->data.calltheta = NAN;
        properties->data.puttheta = NAN;
        properties->data.callrho = NAN;
        properties->data.putrho = NAN;

        if( (((int)i%strike_control[properties->strikestoogle].strikes5or1==0) && (modf(i,&properties->discard)!=strike_control[properties->strikestoogle].retdiscard)) ||
          ((i== 2.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i== 7.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==12.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==17.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==22.5) && strike_control[properties->strikestoogle].strikes5or1==5) ||
          ((i==27.5) && strike_control[properties->strikestoogle].strikes5or1==5)
        )
        {
          if( i <= 0 || fabs(i-0.0) < epsilon )
          {
            i = 0;
        
            if( strike_control[properties->strikestoogle].strikes5or1 != 5 )
            {
              properties->strike_offset = properties->strike_offset + strike_control[properties->strikestoogle].xcontrol;
            } else
            {
              properties->strike_offset = properties->strike_offset + 2.5;
            }
            continue;
          }

          if ( option_algorithms[properties->modeltype].supportPrice )
            snprintf(textPrice,sizeof(textPrice),"%.*f",properties->precision,price);

          cumStrikeLeg1 += i;

          if( strike_control[properties->strikestoogle].incrementor == 0 && properties->spreads == 1 )
          {
             properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike));
             cumStrikeLeg1 = properties->data.strike;
          }
          else if( strike_control[properties->strikestoogle].incrementor == 0 )
          {
             properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
             cumStrikeLeg1 = properties->data.strike;
          }
          else
             properties->data.strike = i;

          if ( option_algorithms[properties->modeltype].supportStrikes )
          {
            if( modf(i,&properties->discard) == .5 )
            {
              snprintf(textStrike,sizeof(textStrike),"%.*f", 1,properties->data.strike);
            } else
            {
              snprintf(textStrike,sizeof(textStrike),"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
            }
          }

          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
          struct _data optiondata;
          
          if( option_algorithms[properties->modeltype].supportCalls )
          {
            optiondata = option_call(&properties->data);
            snprintf(&textCall[0][0],sizeof(textCall[0]),"%.*f",properties->precision,optiondata.call);
          }

          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            snprintf(&textPut[0][0],sizeof(textPut[0]),"%.*f",properties->precision,optiondata.put);
          }

          snprintf(textMonth,sizeof(textMonth),"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

          char textDecimalDate[200] = { 0 };
          snprintf(textDecimalDate,sizeof(textDecimalDate),"%.*f",properties->precision,properties->data.t[0]);

          char textDaysToExpr[200] = { 0 };
          snprintf(textDaysToExpr,sizeof(textDaysToExpr),"%.*f",properties->precision,(365*properties->data.t[0]));

          process_greeks(properties, &properties->data, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0], &textCallElasticity[0], &textPutElasticity[0]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            snprintf(textLegacyCall,sizeof(textLegacyCall),"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            snprintf(textLegacyCall,sizeof(textLegacyCall),"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            snprintf(textLegacyPut,sizeof(textLegacyPut),"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            snprintf(textLegacyPut,sizeof(textLegacyPut),"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
          gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

          if( properties->spreads == 0 )
          {
            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

            if( properties->textExport == true )
            {
              fill_line(lineData,sizeof(lineData),
                   std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut});
              strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
            }

          } else if( properties->spreads == 1 )
          {
            char textCallLeg2[200] = { 0 };
            char textPutLeg2[200] = { 0 };
            char textCallCallSpread[200] = { 0 };
            char textPutPutSpread[200] = { 0 };
            char textCallPutSpread[200] = { 0 };
            char textPutCallSpread[200] = { 0 };

            if( option_algorithms[properties->modeltype].supportCalls )
            {
              snprintf(textCallLeg2,sizeof(textCallLeg2),"%.*f",properties->precision,callLeg2[totalCounter]);
              snprintf(textCallCallSpread,sizeof(textCallCallSpread),"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              snprintf(textPutLeg2,sizeof(textPutLeg2),"%.*f",properties->precision,putLeg2[totalCounter]);
              snprintf(textPutPutSpread,sizeof(textPutPutSpread),"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
            {
              snprintf(textCallPutSpread,sizeof(textCallPutSpread),"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
              snprintf(textPutCallSpread,sizeof(textPutCallSpread),"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
            }

            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

            if( properties->textExport == true )
            {
              fill_line(lineData,sizeof(lineData),
                   std::vector<string>{textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread});
              strncat(dataExport,lineData,sizeof(dataExport)-strlen(dataExport)-1);
            }

            totalCounter++;
          }

          if( index++ >= 4 + (int) ((double) 4 * (double) rowMultiplier ))       
          {
            g_print("%d rows of options and analytics created\n", index);
            break;
          }

          if( !option_algorithms[properties->modeltype].supportStrikes )
            break;
        }
      }
      properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

      if( ++counter >= (option_algorithms[properties->modeltype].supportStrikes ? 4 : 20) )
      {
        break;
      }
    }
    /* reset pointers */
    properties->expiration_month=properties->start_expiration_month;
    properties->days_to_expiration=properties->start_days_to_expiration;
    properties->expiration_year=properties->start_expiration_year;
    properties->time_to_expiration=properties->start_time_to_expiration;

    //g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);

    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );

    //g_print("properties->verticalSpread = %d\n",properties->verticalSpread);

  } // if( properties->format == CALENDAR_OPTIONS3 )

  if( properties->textExport == true && properties->fileExport == false)
  {
    text_export(properties, dataExport);
  } else if( properties->textExport == true && properties->fileExport == true)
  {
    file_export(properties, dataExport);
  }

  if ( properties->spreads == 1 )
    spreadName(properties);

  gettimeofday(&end, NULL);
  c1 = clock();

  g_print("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000) - (start.tv_sec + (double) start.tv_usec / 1000000)));
  g_print("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);      

  return TRUE;

} // gboolean calculate_options(struct _properties *properties)

void process_greeks(struct _properties *properties, struct _data *dat, char *textCallDelta, char *textPutDelta, char *textGamma, char *textVega, char *textCallTheta, char *textPutTheta, char *textCallRho, char *textPutRho, char *textCallElasticity, char *textPutElasticity)
{
  struct _data optiondata;

  if( option_algorithms[properties->modeltype].produceCallDelta )
  {
    if( !isnan(dat->calldelta) )
    {
      optiondata.calldelta = dat->calldelta;
    }
    else
    {
      optiondata = option_call_delta(&properties->data);
    }
    if( !isnan(optiondata.calldelta))
      snprintf(textCallDelta,200,"%.*f", properties->precision,optiondata.calldelta);
  }
        
  if( option_algorithms[properties->modeltype].producePutDelta )
  {
    if( !isnan(dat->putdelta) )
    {
      optiondata.putdelta = dat->putdelta;
    } else
    {
      optiondata = option_put_delta(&properties->data);
    }
    if( !isnan(optiondata.putdelta))
      snprintf(textPutDelta,200,"%.*f", properties->precision,optiondata.putdelta);
  }

  if( option_algorithms[properties->modeltype].produceGamma )
  {
    if( !isnan(dat->gamma) )
    {
      optiondata.gamma = dat->gamma;
    } else
    {
      optiondata = option_gamma(&properties->data);
    }
    if( !isnan(optiondata.gamma))
      snprintf(textGamma,200,"%.*f", properties->precision,optiondata.gamma);
  }

  if( option_algorithms[properties->modeltype].produceVega )
  {
    if( !isnan(dat->vega) )
    {
      optiondata.vega = dat->vega;
    } else
    {
      optiondata = option_vega(&properties->data);
    }
    if( !isnan(optiondata.vega))
      snprintf(textVega,200,"%.*f", properties->precision,optiondata.vega);
  }

  if( option_algorithms[properties->modeltype].produceCallTheta )
  {
    if( !isnan(dat->calltheta) )
    {
      optiondata.calltheta = dat->calltheta;
    } else
    {
      optiondata = option_call_theta(&properties->data);
    }
    if( !isnan(optiondata.calltheta) )
      snprintf(textCallTheta,200,"%.*f", properties->precision,optiondata.calltheta);
  }

  if( option_algorithms[properties->modeltype].producePutTheta )
  {
    if( !isnan(dat->puttheta) )
    {
      optiondata.puttheta = dat->puttheta;
    } else
    {
      optiondata = option_put_theta(&properties->data);
    }
    if( !isnan(optiondata.puttheta) )    
      snprintf(textPutTheta,200,"%.*f", properties->precision,optiondata.puttheta);
  }

  if( option_algorithms[properties->modeltype].produceCallRho )
  {
    if( !isnan(dat->callrho) )
    {
      optiondata.callrho = dat->callrho;
    } else
    {
      optiondata = option_call_rho(&properties->data);
    }
    if( !isnan(optiondata.callrho) )    
      snprintf(textCallRho,200,"%.*f", properties->precision,optiondata.callrho);
  }

  if( option_algorithms[properties->modeltype].producePutRho )
  {
    if( !isnan(dat->putrho) )
    {
      optiondata.putrho = dat->putrho;
    } else {
      optiondata = option_put_rho(&properties->data);
    }
    if( !isnan(optiondata.putrho) )
    {
      snprintf(textPutRho,200,"%.*f", properties->precision,optiondata.putrho);
    }
  }

  if( option_algorithms[properties->modeltype].produceCallElasticity )
  {
    if( !isnan(dat->callElasticity) )
    {
      snprintf(textCallElasticity,200,"%.*f", properties->precision,dat->callElasticity);
    }
  }

  if( option_algorithms[properties->modeltype].producePutElasticity )
  {
    if( !isnan(dat->putElasticity) )
    {
      snprintf(textPutElasticity,200,"%.*f", properties->precision,dat->putElasticity);
    }
  }

} // void process_greeks()
