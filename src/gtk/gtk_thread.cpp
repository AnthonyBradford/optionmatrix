/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_thread.cpp of optionmatrix                                     */
/*                                                                          */
/* Copyright (c) Anthony Bradford. 2012.                                    */
/* http://anthonybradford.com                                               */
/* info@anthonybradford.com                                                 */
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

gboolean calculate_options(struct _properties *properties)
{
  //g_print("calculate_options()\n");
  //g_print("properties->format = %d\n", properties->format );
  //g_print("properties->decimalorcalendar = %d\n",properties->decimalorcalendar);

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
  gchar textMonth[200] = { 0 };

  double callLeg2[200] = { 0 };
  double putLeg2[200] = { 0 };
  char textMonthLeg2[100][200] = { { 0 } };
  char textStrikeLeg2[100][200] = { { 0 } };
  char textLegacyCall[200] = { 0 };
  char textLegacyPut[200] = { 0 };

  int totalCounter = 0;

  char dataExport[20000] = { 0 };
  char lineData[5000] = { 0 };

  double cumStrikeLeg1 = 0.0;
  double cumStrikeLeg2 = 0.0;

  char statusMessage[80 * 3]  = { 0 };
  if( sanity_check(properties, &statusMessage[0]) )
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
    sprintf(dateTime2,"%s Date: %s  ",option_algorithms[properties->modeltype].supportTime2des,decimal_date_to_real_date(decimalTime2));
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
    sprintf(dateTime3,"%s Date: %s  ",option_algorithms[properties->modeltype].supportTime3des,decimal_date_to_real_date(decimalTime3));
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
    //sprintf(dateTime,"Expiration Date: %s",decimal_date_to_real_date(decimalTime));
    sprintf(dateTime,"%s Date: %s", option_algorithms[properties->modeltype].supportTime1des, decimal_date_to_real_date(decimalTime));
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
      sprintf(description,"Discount Factor T1");
      sprintf(timeDecimal,"%.*f", properties->precision,decimalTime2);
      sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime2));
      sprintf(value,"%.*f", properties->precision,properties->data.discount_t2);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      sprintf(lineData,"Discount Factor T1   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
      strcat(dataExport,lineData);

      sprintf(description,"Discount Factor T2");
      sprintf(timeDecimal,"%.*f", properties->precision,decimalTime);
      sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime));
      sprintf(value,"%.*f", properties->precision,properties->data.discount_t1);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      sprintf(lineData,"Discount Factor T2   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
      strcat(dataExport,lineData);

      sprintf(description,"Spot Rate T1");
      sprintf(timeDecimal,"%.*f", properties->precision,decimalTime2);
      sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime2));
      sprintf(value,"%.*f", properties->precision,properties->data.spot_t2);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      sprintf(lineData,"Spot Rate T1   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
      strcat(dataExport,lineData);

      sprintf(description,"Spot Rate T2");
      sprintf(timeDecimal,"%.*f", properties->precision,decimalTime);
      sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime));
      sprintf(value,"%.*f", properties->precision,properties->data.spot_t1);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      sprintf(lineData,"Spot Rate T2   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
      strcat(dataExport,lineData);
      
      sprintf(description,"Forward T1 : T2");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.forward);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

      sprintf(lineData,"Forward T1 : T2   %.*f\n", properties->precision,properties->data.forward);
      strcat(dataExport,lineData);

      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "", X2, "", X3, "", X4, "", -1);

    }

    if( properties->data.bond_price )
    {
      sprintf(description,"Bond Price");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.bond_price);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Bond Price   %.*f\n",properties->precision,properties->data.bond_price);
      strcat(dataExport,lineData);
    }

    if( properties->data.pv_continous )
    {
      sprintf(description,"Present Value");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.pv_continous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Present Value %.*f\n",properties->precision,properties->data.pv_continous);
      strcat(dataExport,lineData);
    }

    if( properties->data.pv_discrete )
    {
      sprintf(description,"Present Value Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.pv_discrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Present Value Discrete   %.*f\n",properties->precision,properties->data.pv_discrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.YTMContinous )
    {
      sprintf(description,"YTM");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.YTMContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"YTM   %.*f\n",properties->precision,properties->data.YTMContinous);
      strcat(dataExport,lineData);
    }

    if( properties->data.YTMDiscrete )
    {
      sprintf(description,"YTM Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.YTMDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"YTM Discrete   %.*f\n",properties->precision,properties->data.YTMDiscrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.durationContinous )
    {
      sprintf(description,"Duration");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.durationContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Duration   %.*f\n",properties->precision,properties->data.durationContinous);
      strcat(dataExport,lineData);
    }

    if( properties->data.durationDiscrete )
    {
      sprintf(description,"Duration Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.durationDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Duration Discrete   %.*f\n",properties->precision,properties->data.durationDiscrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.durationModifiedDiscrete )
    {
      sprintf(description,"Duration Modified Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.durationModifiedDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Duration Modified Discrete   %.*f\n",properties->precision,properties->data.durationModifiedDiscrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.durationMacaulayDiscrete )
    {
      sprintf(description,"Duration Macaulay Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.durationMacaulayDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Duration Macaulay Discrete   %.*f\n",properties->precision,properties->data.durationMacaulayDiscrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.convexityContinous )
    {
      sprintf(description,"Convexity");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.convexityContinous);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Convexity %.*f\n",properties->precision,properties->data.convexityContinous);
      strcat(dataExport,lineData);
    }

    if( properties->data.convexityDiscrete )
    {
      sprintf(description,"Convexity Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.convexityDiscrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Convexity Discrete %.*f\n",properties->precision,properties->data.convexityDiscrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.call )
    {
      sprintf(description,"Call");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.call);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"Call   %.*f\n",properties->precision,properties->data.call);
      strcat(dataExport,lineData);
    }

    if( properties->data.irr )
    {
      sprintf(description,"IRR");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.irr);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"IRR   %.*f\n",properties->precision,properties->data.irr);
      strcat(dataExport,lineData);
    }

    if( properties->data.irr_discrete )
    {
      sprintf(description,"IRR Discrete");
      timeDecimal[0] = dateTime[0] = 0; 
      sprintf(value,"%.*f", properties->precision,properties->data.irr_discrete);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"IRR Discrete   %.*f\n",properties->precision,properties->data.irr_discrete);
      strcat(dataExport,lineData);
    }

    if( properties->data.uirr )
    {
      sprintf(description,"UIRR");
      timeDecimal[0] = dateTime[0] = 0; 
      strcpy(value,"True");
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, dateTime, -1);

      sprintf(lineData,"UIRR   True\n");
      strcat(dataExport,lineData);
    }

    if( properties->textExport == true )
      text_export(properties, dataExport);

    return TRUE;
  }

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

    sprintf(description,"Discount Factor T1");
    sprintf(timeDecimal,"%.*f", properties->precision,decimalTime2);
    sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime2));
    sprintf(value,"%.*f", properties->precision,properties->data.discount_t2);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    sprintf(lineData,"Discount Factor T1   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
    strcat(dataExport,lineData);

    sprintf(description,"Discount Factor T2");
    sprintf(timeDecimal,"%.*f", properties->precision,decimalTime);
    sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime));
    sprintf(value,"%.*f", properties->precision,properties->data.discount_t1);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);
    sprintf(lineData,"Discount Factor T2   %.*f   %s   %.*f\n",properties->precision,properties->data.discount_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
    strcat(dataExport,lineData);

    sprintf(description,"Spot Rate T1");
    sprintf(timeDecimal,"%.*f", properties->precision,decimalTime2);
    sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime2));
    sprintf(value,"%.*f", properties->precision,properties->data.spot_t2);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    sprintf(lineData,"Spot Rate T1   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t2,decimal_date_to_real_date(decimalTime2),properties->precision,decimalTime2);
    strcat(dataExport,lineData);

    sprintf(description,"Spot Rate T2");
    sprintf(timeDecimal,"%.*f", properties->precision,decimalTime);
    sprintf(dateTime,"%s", decimal_date_to_real_date(decimalTime));
    sprintf(value,"%.*f", properties->precision,properties->data.spot_t1);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    sprintf(lineData,"Spot Rate T2   %.*f   %s   %.*f\n",properties->precision,properties->data.spot_t1,decimal_date_to_real_date(decimalTime),properties->precision,decimalTime);
    strcat(dataExport,lineData);

    sprintf(description,"Forward T1 : T2");
    timeDecimal[0] = dateTime[0] = 0; 
    sprintf(value,"%.*f", properties->precision,properties->data.forward);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, description, X2, value, X3, dateTime, X4, timeDecimal, -1);

    sprintf(lineData,"Forward T1 : T2   %.*f\n", properties->precision,properties->data.forward);
    strcat(dataExport,lineData);

    if( properties->data.term )
      delete properties->data.term;

    if( properties->textExport == true )
      text_export(properties, dataExport);

    return TRUE;
  }

#endif

  if( properties->format == DECIMAL_FUTURE )
  {
    g_print("DECIMAL_FUTURE\n");
    g_print("properties->decimalorcalendar = %d\n", properties->decimalorcalendar);

    struct _data futuredata;
    futuredata = future(&properties->data);

    char textSpot[200] = { 0 };
    sprintf(textSpot,"%.*f",properties->precision,properties->data.price);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Spot Price", X2, textSpot, -1);

    sprintf(lineData," %s, %s\n", "Spot Price",textSpot);
    strcat(dataExport,lineData);

    char textFuturesPrice[200] = { 0 };
    sprintf(textFuturesPrice,"%.*f (%s)",properties->precision,properties->data.future,(properties->data.future > properties->data.price ? "Cotango" : "Backwardation") );
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Futures Price", X2, textFuturesPrice, -1);

    sprintf(lineData," %s, %s\n", "Futures Price",textFuturesPrice);
    strcat(dataExport,lineData);

    char textRate[200] = { 0 };
    sprintf(textRate,"%.*f%%",properties->precision,properties->data.rate*100);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Interest Rate", X2, textRate, -1);

    sprintf(lineData," %s, %s\n", "Interest Rate", textRate);
    strcat(dataExport,lineData);

    char textBasis[200] = { 0 };
    sprintf(textBasis,"%.*f", properties->precision,properties->data.price-properties->data.future);
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Basis", X2, textBasis, -1);

    sprintf(lineData," %s, %s\n", "Basis", textBasis);
    strcat(dataExport,lineData);

    if( option_algorithms[properties->modeltype].supportDividend )
    {
      char textDiv[200] = { 0 };
      sprintf(textDiv,"%.*f", properties->precision,properties->data.dividend);
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
      gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Div yield underlying", X2, textDiv, -1);

      sprintf(lineData," %s, %s\n", "Div yield underlying", textDiv);
      strcat(dataExport,lineData);
    }

    char textExpr[200] = { 0 };
    sprintf(textExpr,"%s",decimal_date_to_real_date(properties->data.t[0]-properties->data.te));
    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Expiration Date", X2, textExpr, -1);

    sprintf(lineData," %s, %s\n", "Expiration Date",textExpr);
    strcat(dataExport,lineData);
    
    char textTicker[200] = { 0 };
    sprintf(textTicker,"%s%02d",future_codes[decimal_date_to_int_month(adjust_to_current_time(properties->data.t[0]-properties->data.te,0))],decimal_date_to_int_year(adjust_to_current_time(properties->data.t[0]-properties->data.te,0)));

    gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
    gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, "Ticker", X2, textTicker, -1);

    sprintf(lineData," %s, %s\n", "Ticker", textTicker);
    strcat(dataExport,lineData);
  }

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
    char textSpreadTicker[200] = { 0 };

    double leg1;
    double leg2;

    while( (*properties->expiration_month!=-1) && (*properties->days_to_expiration!=-1) && (*properties->expiration_year!=-1) )
    {
      properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
      //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

      futuredata = future(&properties->data);
      leg1 = properties->data.future;
      
      sprintf(textPrice,"%.*f",properties->precision,properties->data.future);
      //sprintf(textTicker,"%s",future_codes[*properties->expiration_month]);
      sprintf(textTicker,"%s%02d",future_codes[*properties->expiration_month],*properties->expiration_year);
      sprintf(textMonthDayYear,"%s%2d %02.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);
      sprintf(textDecimalDate,"%.*f",properties->precision,properties->data.t[0]);
      //g_print("textDecimalDate %.*f\n",properties->precision,properties->data.t[0]);
      sprintf(textDaysToExpr,"%.*f",properties->precision,(365*properties->data.t[0]));
      //g_print("textDaysToExpr = %.*f\n",properties->precision,(365*properties->data.t[0]));

      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

      if( properties->spreads == 0 )
      {
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textMonthDayYear, X2, textPrice, X3, textDaysToExpr, X4, textDecimalDate, X5, textTicker, -1);

        if( properties->textExport == true )
        {
          sprintf(lineData,"%s, %s, %s, %s, %s\n", 
                textMonthDayYear, textPrice, textDaysToExpr, textDecimalDate, textTicker);
          strcat(dataExport,lineData);
        }

      } else if( properties->spreads == 1 )
      {
        properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration2,properties->expiration_time,0);
        //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));

        futuredata2 = future(&properties->data);
        leg2 = properties->data.future;

        sprintf(textPrice2,"%.*f",properties->precision,properties->data.future);
        //sprintf(textTicker2,"%s",future_codes[*properties->expiration_month2]);
        sprintf(textTicker2,"%s%02d",future_codes[*properties->expiration_month2],*properties->expiration_year2);
        sprintf(textMonthDayYear2,"%s%2d %02.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);
        sprintf(textDecimalDate2,"%.*f",properties->precision,properties->data.t[0]);
        //g_print("textDecimalDate %.*f\n",properties->precision,properties->data.t[0]);
        sprintf(textDaysToExpr2,"%.*f",properties->precision,(365*properties->data.t[0]));
        //g_print("textDaysToExpr = %.*f\n",properties->precision,(365*properties->data.t[0]));
        sprintf(textSpread,"%.*f",properties->precision, (double) leg1 - (double) leg2);
        sprintf(textSpreadTicker,"%s - %s",textTicker, textTicker2);

        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textMonthDayYear, X2, textPrice, X3, textDaysToExpr, X4, textDecimalDate, X5, textTicker, X6, textMonthDayYear2, X7, textPrice2, X8, textDaysToExpr2, X9, textDecimalDate2, X10, textTicker2, X11, textSpread, X12, textSpreadTicker, -1);

        if( properties->textExport == true )
        {
          sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n", 
              textMonthDayYear, textPrice, textDaysToExpr, textDecimalDate, textTicker, textMonthDayYear2, textPrice2, textDaysToExpr2, textDecimalDate2, textTicker2, textSpread, textSpreadTicker);
          strcat(dataExport,lineData);
        }

      }

      properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;
      properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

      if(index++ >= 17)
        break;
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
  }

  if( properties->format == DECIMAL_GREEKS )
  {
      g_print("DECIMAL_GREEKS\n");
      double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
      double i;
      index = 0;
      for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
      {

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
           sprintf(textPrice,"%.*f", properties->precision,price);

         if( strike_control[properties->strikestoogle].incrementor == 0 )
           properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
         else
           properties->data.strike = i;

         if ( option_algorithms[properties->modeltype].supportStrikes )
         {
           if( modf(i,&properties->discard) == .5 )
           {
             sprintf(textStrike,"%.*f", 1,properties->data.strike);
           } else
           {
             sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
           }
         }

         //g_print("price = %f, strike = %f, rate = %f, v = %f, div = %f, z = %f, b = %f, j = %f, p = %f", price, i, rate, volatility, dividend,properties->data.UseZ, properties->data.UseB, properties->data.UseJ, properties->data.UseP);
        
         struct _data optiondata;

         if( option_algorithms[properties->modeltype].supportCalls )
         {
           optiondata = option_call(&properties->data);
           sprintf(&textCall[0][0],"%.*f",properties->precision,optiondata.call);
         }

         if( option_algorithms[properties->modeltype].supportPuts )
         {
           optiondata = option_put(&properties->data);
           sprintf(&textPut[0][0], "%.*f",properties->precision,optiondata.put);
         }

         process_greeks(properties, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0]);

         gtk_list_store_append(properties->GtkInfo.liststore1, &iter);
         gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textStrike, X3, textCall[0], X4, textPut[0], X5, textCallDelta, X6, textPutDelta, X7, textGamma, X8, textVega, X9, textCallTheta, X10, textPutTheta, X11, textCallRho, X12, textPutRho, -1);

         if( properties->textExport == true )
         {
           sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n", textPrice, textStrike, textCall[0], textPut[0], textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho);
           strcat(dataExport,lineData);
         }

         if( index++ >= 17 )
          break;

         if( !option_algorithms[properties->modeltype].supportStrikes )
          break;

         }
      }
  }
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
          sprintf(textStrikeLeg2[totalCounter],"%.*f",properties->precision,i);
        }
        //sprintf(textPrice,"%.*f",properties->precision,price);

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

        sprintf(&textMonthLeg2[totalCounter][0],"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

        sprintf(&textMonthLeg2[totalCounter][0],"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

        properties->time_to_expiration2++;  properties->days_to_expiration2++;  properties->expiration_month2++;  properties->expiration_year2++;

        totalCounter++;

        if( index++ >= 18 )
        {
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
        sprintf(textStrike,"%.*f", properties->precision,properties->data.strike);

      if ( option_algorithms[properties->modeltype].supportPrice )
          sprintf(textPrice,"%.*f",properties->precision,price);

      properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
      //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
      struct _data optiondata;
          
      if( option_algorithms[properties->modeltype].supportCalls )
      {
        optiondata = option_call(&properties->data);
        sprintf(&textCall[0][0],"%.*f",properties->precision,optiondata.call);
      }

      if( option_algorithms[properties->modeltype].supportPuts )
      {
        optiondata = option_put(&properties->data);
        sprintf(&textPut[0][0], "%.*f",properties->precision,optiondata.put);
      }

      sprintf(textMonth,"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

      char textDecimalDate[200]  = { 0 };
      sprintf(textDecimalDate,"%.*f",properties->precision,properties->data.t[0]);

      char textDaysToExpr[200] = { 0 };
      sprintf(textDaysToExpr,"%.*f",properties->precision,(365*properties->data.t[0]));

      process_greeks(properties, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0]);

      if ( option_algorithms[properties->modeltype].supportStrikes )
        sprintf(textLegacyCall,"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
      else
        sprintf(textLegacyCall,"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]);

      if ( option_algorithms[properties->modeltype].supportStrikes )
        sprintf(textLegacyPut,"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
      else
        sprintf(textLegacyPut,"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
      gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

      if( properties->spreads == 0 )
      {
        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

        if( properties->textExport == true )
        {
          sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut);
          strcat(dataExport,lineData);
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
          sprintf(textCallLeg2,"%.*f",properties->precision,callLeg2[totalCounter]);
          sprintf(textCallCallSpread,"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
        }

        if( option_algorithms[properties->modeltype].supportPuts )
        {
          sprintf(textPutLeg2, "%.*f",properties->precision,putLeg2[totalCounter]);
          sprintf(textPutPutSpread,"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
        }

        if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
        {
          sprintf(textCallPutSpread,"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
          sprintf(textPutCallSpread,"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
        }

        gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

        if( properties->textExport == true )
        {
          sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread);
          strcat(dataExport,lineData);
        }

      }

      properties->time_to_expiration++;  properties->days_to_expiration++;  properties->expiration_month++;  properties->expiration_year++;

      totalCounter++;

      if( index++ >= 18 )
      {
        break;
      }
    }

    /* reset pointers */
    properties->expiration_month=properties->start_expiration_month;
    properties->days_to_expiration=properties->start_days_to_expiration;
    properties->expiration_year=properties->start_expiration_year;
    properties->time_to_expiration=properties->start_time_to_expiration;

    g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);
    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );
    g_print("properties->verticalSpread = %d\n",properties->verticalSpread);

  }
  else if( properties->format == CALENDAR_OPTIONS6 )
  {
    g_print("CALENDAR_OPTIONS6\n");

    int counter = 0;

    double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
    double i;
    index = 0;
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
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
          sprintf(textPrice,"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
         properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( modf(i,&properties->discard) == .5 )
          {
            sprintf(textStrike,"%.*f", 1,properties->data.strike);
          } else
          {
            sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
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
            sprintf(&textCall[counter][0],"%.*f",properties->precision,optiondata.call);
          }
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            sprintf(&textPut[counter][0], "%.*f",properties->precision,optiondata.put);
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
          sprintf(lineData," %s, %s, %s, %s, %s, %s, %s, %s\n",
                textPrice, textStrike, textCall[0], textCall[1], textCall[2], textPut[0], textPut[1], textPut[2]);
          strcat(dataExport,lineData);
        }

        if( index++ >= 17 )
          break;

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }
  } else if( properties->format == CALENDAR_OPTIONS5 )
  {
    g_print("CALENDAR_OPTIONS5\n");
    int counter = 0;

    double epsilon = (double) 1 / pow(10.0,(double)strike_control[properties->strikestoogle].precision+1);
    double i;
    index = 0;
    if( option_algorithms[properties->modeltype].supportCalls )
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
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
          sprintf(textPrice,"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
         properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )        
        {
          if( modf(i,&properties->discard) == .5 )
          {
            sprintf(textStrike,"%.*f", 1,properties->data.strike);
          } else
          {
            sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
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
            sprintf(&textCall[counter][0],"%c %.*f",tolower(option_algorithms[properties->modeltype].call[0]),properties->precision,optiondata.call);
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
          sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n", 
                textPrice, textStrike, textCall[0], textCall[1], textCall[2], textCall[3], textCall[4], textCall[5], textCall[6], textCall[7]);
          strcat(dataExport,lineData);
        }

        if( index++ >= 8 )
          break;

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    index = 0;
    if( option_algorithms[properties->modeltype].supportPuts )
    for(i=(properties->strike_offset+(int)price-35/(strike_control[properties->strikestoogle].precision+1));i<(properties->strike_offset+(int)price+160);i+=strike_control[properties->strikestoogle].incrementor)
    {
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
          sprintf(textPrice,"%.*f",properties->precision,price);

        if( strike_control[properties->strikestoogle].incrementor == 0 )
          properties->data.strike = gtk_spin_button_get_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2));
        else
         properties->data.strike = i;

        if ( option_algorithms[properties->modeltype].supportStrikes )
        {
          if( modf(i,&properties->discard) == .5 )
          {
            sprintf(textStrike,"%.*f", 1,properties->data.strike);
          } else
          {
            sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
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
            sprintf(&textPut[counter][0],"%c %.*f",tolower(option_algorithms[properties->modeltype].put[0]),properties->precision,optiondata.put);
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
          sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                textPrice, textStrike, textPut[0], textPut[1], textPut[2], textPut[3], textPut[4], textPut[5], textPut[6], textPut[7]);
          strcat(dataExport,lineData);
        }

        if( index++ >= 8 )
          break;

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;

        //g_print("index = %d\n",index);
      }
    }
  } else if( properties->format == CALENDAR_OPTIONS4 )
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
                sprintf(textStrikeLeg2[totalCounter],"%.*f", 1,properties->data.strike);
              } else
              {
                sprintf(textStrikeLeg2[totalCounter],"%.*f",strike_control[properties->strikestoogle].precision,properties->data.strike);
              }

              g_print("textStrikeLeg2[totalCounter] = %s\n",textStrikeLeg2[totalCounter]);
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

            //sprintf(textMonth,"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

            sprintf(&textMonthLeg2[totalCounter][0],"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

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

          if(index++ >= 4)
            break;

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
          sprintf(textPrice,"%.*f",properties->precision,price);

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
            sprintf(textStrike,"%.*f", 1,properties->data.strike);
          } else
          {
            sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
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
            sprintf(&textCall[0][0],"%.*f",properties->precision,optiondata.call);
          }
          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            sprintf(&textPut[0][0], "%.*f",properties->precision,optiondata.put);
          }

          sprintf(textMonth,"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

          char textDecimalDate[200] = { 0 };
          sprintf(textDecimalDate,"%.*f",properties->precision,properties->data.t[0]);

          char textDaysToExpr[200] = { 0 };
          sprintf(textDaysToExpr,"%.*f",properties->precision,(365*properties->data.t[0]));

          process_greeks(properties, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            sprintf(textLegacyCall,"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            sprintf(textLegacyCall,"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]); 

          if ( option_algorithms[properties->modeltype].supportStrikes )
            sprintf(textLegacyPut,"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            sprintf(textLegacyPut,"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
          gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

          if( properties->spreads == 0 )
          {
            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

            if( properties->textExport == true )
            {
              sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                    textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut);
              strcat(dataExport,lineData);
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
              sprintf(textCallLeg2,"%.*f",properties->precision,callLeg2[totalCounter]);
              sprintf(textCallCallSpread,"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              sprintf(textPutLeg2, "%.*f",properties->precision,putLeg2[totalCounter]);
              sprintf(textPutPutSpread,"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
            {
              sprintf(textCallPutSpread,"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
              sprintf(textPutCallSpread,"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
            }

            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

            if( properties->textExport == true )
            {
              sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                    textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread);

              strcat(dataExport,lineData);
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

        if( index++ >= 4 )
          break;

        if( !option_algorithms[properties->modeltype].supportStrikes )
          break;
      }
    }

    g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);
    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );
    g_print("properties->verticalSpread = %d\n",properties->verticalSpread);

  } else if( properties->format == CALENDAR_OPTIONS3 )
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
            //sprintf(textPrice,"%.*f",properties->precision,price);

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
                sprintf(textStrikeLeg2[totalCounter],"%.*f", 1,properties->data.strike);
              } else
              {
                sprintf(textStrikeLeg2[totalCounter],"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
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

            //sprintf(textMonth,"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

            sprintf(&textMonthLeg2[totalCounter][0],"%s%2d %04.0f",mon[*properties->expiration_month2],*properties->days_to_expiration2,(double)*properties->expiration_year2 + 2000);

            totalCounter++;

            if( index++ >= 4 )
            {
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
            sprintf(textPrice,"%.*f",properties->precision,price);

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
              sprintf(textStrike,"%.*f", 1,properties->data.strike);
            } else
            {
              sprintf(textStrike,"%.*f", strike_control[properties->strikestoogle].precision,properties->data.strike);
            }
          }

          properties->data.t[0] = adjust_to_current_time_and_expr(properties->time_to_expiration,properties->expiration_time,0);
          //g_print("t = %.*f\t%s\n",15,(double)properties->data.t[0],decimal_date_to_real_date(properties->data.t[0]));
      
          struct _data optiondata;
          
          if( option_algorithms[properties->modeltype].supportCalls )
          {
            optiondata = option_call(&properties->data);
            sprintf(&textCall[0][0],"%.*f",properties->precision,optiondata.call);
          }

          if( option_algorithms[properties->modeltype].supportPuts )
          {
            optiondata = option_put(&properties->data);
            sprintf(&textPut[0][0], "%.*f",properties->precision,optiondata.put);
          }

          sprintf(textMonth,"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);

          char textDecimalDate[200] = { 0 };
          sprintf(textDecimalDate,"%.*f",properties->precision,properties->data.t[0]);

          char textDaysToExpr[200] = { 0 };
          sprintf(textDaysToExpr,"%.*f",properties->precision,(365*properties->data.t[0]));

          process_greeks(properties, &textCallDelta[0], &textPutDelta[0], &textGamma[0], &textVega[0], &textCallTheta[0], &textPutTheta[0], &textCallRho[0], &textPutRho[0]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            sprintf(textLegacyCall,"%s%c",option_calls[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            sprintf(textLegacyCall,"%s",option_calls[decimal_date_to_int_month(properties->data.t[0])]);

          if ( option_algorithms[properties->modeltype].supportStrikes )
            sprintf(textLegacyPut,"%s%c",option_puts[decimal_date_to_int_month(properties->data.t[0])],(char) strike_price_codes(i));
          else
            sprintf(textLegacyPut,"%s",option_puts[decimal_date_to_int_month(properties->data.t[0])]);
 
          gtk_list_store_append(properties->GtkInfo.liststore1, &iter);

          if( properties->spreads == 0 )
          {
            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textDaysToExpr, X7, textDecimalDate, X8, textCallDelta, X9, textPutDelta, X10, textGamma, X11, textVega, X12, textCallTheta, X13, textPutTheta, X14, textCallRho, X15, textPutRho, X16, textLegacyCall, X17, textLegacyPut, -1);

            if( properties->textExport == true )
            {            
              sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                      textPrice, textMonth, textStrike, textCall[0], textPut[0], textDaysToExpr, textDecimalDate, textCallDelta, textPutDelta, textGamma, textVega, textCallTheta, textPutTheta, textCallRho, textPutRho, textLegacyCall, textLegacyPut);
              strcat(dataExport,lineData);
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
              sprintf(textCallLeg2,"%.*f",properties->precision,callLeg2[totalCounter]);
              sprintf(textCallCallSpread,"%.*f",properties->precision,optiondata.call - callLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportPuts )
            {
              sprintf(textPutLeg2, "%.*f",properties->precision,putLeg2[totalCounter]);
              sprintf(textPutPutSpread,"%.*f",properties->precision,optiondata.put - putLeg2[totalCounter]);
            }

            if( option_algorithms[properties->modeltype].supportCalls && option_algorithms[properties->modeltype].supportPuts )
            {
              sprintf(textCallPutSpread,"%.*f", properties->precision, optiondata.call - putLeg2[totalCounter]);
              sprintf(textPutCallSpread,"%.*f", properties->precision, optiondata.put  - callLeg2[totalCounter]);
            }

            gtk_list_store_set(properties->GtkInfo.liststore1, &iter, X1, textPrice, X2, textMonth, X3, textStrike, X4, textCall[0], X5, textPut[0], X6, textMonthLeg2[totalCounter], X7, textStrikeLeg2[totalCounter], X8, textCallLeg2, X9, textPutLeg2, X10, textCallCallSpread, X11, textPutPutSpread, X12, textCallPutSpread, X13, textPutCallSpread, -1);

            if( properties->textExport == true )
            {            
              sprintf(lineData,"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
                      textPrice, textMonth, textStrike, textCall[0], textPut[0], textMonthLeg2[totalCounter], textStrikeLeg2[totalCounter], textCallLeg2, textPutLeg2, textCallCallSpread, textPutPutSpread, textCallPutSpread, textPutCallSpread);
              strcat(dataExport,lineData);
            }

            totalCounter++;
          }

          if( index++ >= 4 )
          {
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

    g_print("cumStrikeLeg1 = %f, cumStrikeLeg2 = %f\n",cumStrikeLeg1,cumStrikeLeg2);

    properties->verticalSpread = ( cumStrikeLeg1 != cumStrikeLeg2 );

    g_print("properties->verticalSpread = %d\n",properties->verticalSpread);
  }

  if( properties->textExport == true )
    text_export(properties, dataExport);

  if ( properties->spreads == 1 )
    spreadName(properties);

  return TRUE;
}

void process_greeks(struct _properties *properties, char *textCallDelta, char *textPutDelta, char *textGamma, char *textVega, char *textCallTheta, char *textPutTheta, char *textCallRho, char *textPutRho)
{
  struct _data optiondata;

  if( option_algorithms[properties->modeltype].produceCallDelta )
  {
    optiondata = option_call_delta(&properties->data);
    sprintf(textCallDelta,"%.*f", properties->precision,optiondata.calldelta);
  }
        
  if( option_algorithms[properties->modeltype].producePutDelta )
  {
    optiondata = option_put_delta(&properties->data);
    sprintf(textPutDelta,"%.*f", properties->precision,optiondata.putdelta);
  }

  if( option_algorithms[properties->modeltype].produceGamma )
  {
    optiondata = option_gamma(&properties->data);
    sprintf(textGamma,"%.*f", properties->precision,optiondata.gamma);
  }

  if( option_algorithms[properties->modeltype].produceVega )
  {
    optiondata = option_vega(&properties->data);
    sprintf(textVega,"%.*f", properties->precision,optiondata.vega);
  }

  if( option_algorithms[properties->modeltype].produceCallTheta )
  {
    optiondata = option_call_theta(&properties->data);
    sprintf(textCallTheta,"%.*f", properties->precision,optiondata.calltheta);
  }

  if( option_algorithms[properties->modeltype].producePutTheta )
  {
    optiondata = option_put_theta(&properties->data);
    sprintf(textPutTheta,"%.*f", properties->precision,optiondata.puttheta);
  }

  if( option_algorithms[properties->modeltype].produceCallRho )
  {
    optiondata = option_call_rho(&properties->data);
    sprintf(textCallRho,"%.*f", properties->precision,optiondata.callrho);
  }

  if( option_algorithms[properties->modeltype].producePutRho )
  {
    optiondata = option_put_rho(&properties->data);
    sprintf(textPutRho,"%.*f", properties->precision,optiondata.putrho);
  }
}
