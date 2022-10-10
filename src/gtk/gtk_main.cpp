/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_main.cpp of optionmatrix                                       */
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
#include "gtk_glade_xml.h"
#include "gtk_icon.h"
#include "../common/main.h"
#include "../common/license.h"

GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if(!pixbuf)
   {
      g_print("%s\n", error->message);
      g_error_free(error);
      return NULL;
   }

   return pixbuf;

} // GdkPixbuf *create_pixbuf(const gchar * filename)

void show_title(const struct _properties *properties)
{
  char title[1000] = { 0 };

  bool supportStrikes = option_algorithms[properties->modeltype].supportStrikes;

  struct fname { char format[5][100];  };

  const struct fname formatNames[] = {
    { { "Months Call / Put",        "Not used", "Months Across", "3 Call / 3 Put Columns",     "Not used"   } },
    { { "Month to Strikes", "Months to Strike", "Months Across", "3 Call / 3 Put Columns", "Custom Strike"  } }
  };

  if( properties->decimalorcalendar == DECIMALS )
  {
    snprintf(title,sizeof(title),"%s %s Decimal Dated, Model Source: %s", PACKAGE_NAME, PACKAGE_VERSION, option_algorithms[properties->modeltype].source);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats2);

  } else if( properties->decimalorcalendar == CALENDAR )
  {
    snprintf(title,sizeof(title),"%s %s Calendar Dated, Model Source: %s", PACKAGE_NAME, PACKAGE_VERSION, option_algorithms[properties->modeltype].source);

    if( !option_algorithms[properties->modeltype].assetClass )
    {
      char formatStyle[1000] = { 0 };
      snprintf(formatStyle,sizeof(formatStyle),"Format: %s",formatNames[supportStrikes].format[properties->format - CALENDAR_OPTIONS3]);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDisplayFormats2),formatStyle);
      gtk_widget_show(properties->GtkInfo.labelDisplayFormats2);
    }
  }

  g_print("%s\n",option_algorithms[properties->modeltype].source);
  gtk_window_set_title(GTK_WINDOW(properties->GtkInfo.window), title);

} // void show_title(const struct _properties *properties)

void show_label_expirations(const struct _properties *properties)
{
  char expiration[400] = { 0 };

  if( properties->occurence_plus_offset )
  {
    snprintf(expiration,sizeof(expiration),"Expirations set to %d%s %s + %d @ %02d:%02d:%02d",properties->occurence_in_month,order[properties->occurence_in_month-1],weekdays[properties->occurence_day-1],properties->occurence_plus_offset,properties->expiration_hour,properties->expiration_minute,properties->expiration_second);
  } else
  {
    snprintf(expiration,sizeof(expiration),"Expirations set to %d%s %s @ %02d:%02d:%02d",properties->occurence_in_month,order[properties->occurence_in_month-1],weekdays[properties->occurence_day-1],properties->expiration_hour,properties->expiration_minute,properties->expiration_second);
  }

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelExpirations),expiration);
  gtk_widget_show(properties->GtkInfo.labelExpirations);

} // void show_label_expirations(const struct _properties *properties)

void updateVolatility(int modeltype, const struct _properties *properties)
{
  g_print("updateVolatility()\n");
  
  if( option_algorithms[modeltype].supportVolatility )
  {
    gtk_widget_show(properties->GtkInfo.labelStandardDeviation);
    gtk_widget_show(properties->GtkInfo.spinbuttonStandardDeviation);
  } else
  {
    gtk_widget_hide(properties->GtkInfo.labelStandardDeviation);
    gtk_widget_hide(properties->GtkInfo.spinbuttonStandardDeviation);
  }

} // void updateVolatility(int modeltype, const struct _properties *properties)

void updateTime(int modeltype, struct _properties *properties)
{

  g_print("updateTime()\n");
  
  if( option_algorithms[modeltype].assetClass == FUTURES_CLASS ||
      option_algorithms[modeltype].assetClass == BOND_CLASS )
  {
    g_print("FUTURES_CLAS || BOND_CLASS hide\n");
    
    gtk_widget_hide(properties->GtkInfo.labelCycle);
    gtk_widget_hide(properties->GtkInfo.comboboxCycle);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime3);
    gtk_widget_hide(properties->GtkInfo.labelTime2);
    gtk_widget_hide(properties->GtkInfo.labelTime3);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar2);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar3);
    gtk_widget_hide(properties->GtkInfo.label2);
    gtk_widget_hide(properties->GtkInfo.label3);
    gtk_widget_hide(properties->GtkInfo.labelExpirations);
    gtk_widget_hide(properties->GtkInfo.scaleMonths);
  }

  if( option_algorithms[modeltype].perpetual )
  {
    g_print("perpetual hide\n");
    
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime);
    gtk_widget_hide(properties->GtkInfo.label1);
    gtk_widget_hide(properties->GtkInfo.labelDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.labelTime1);
    gtk_widget_hide(properties->GtkInfo.checkbuttonDateEngine);
    gtk_widget_hide(properties->GtkInfo.labelCycle);
    gtk_widget_hide(properties->GtkInfo.comboboxCycle);
    gtk_widget_hide(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_hide(properties->GtkInfo.buttonProperties);
    gtk_widget_hide(properties->GtkInfo.buttonDividends);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime3);
    gtk_widget_hide(properties->GtkInfo.labelTime2);
    gtk_widget_hide(properties->GtkInfo.labelTime3);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar2);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar3);
    gtk_widget_hide(properties->GtkInfo.label2);
    gtk_widget_hide(properties->GtkInfo.label3);
    gtk_widget_hide(properties->GtkInfo.labelDaysToDividend);
    gtk_widget_hide(properties->GtkInfo.labelDaysToDividend2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToDividend);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToDividend2);
    gtk_widget_hide(properties->GtkInfo.labelExpirations);
    gtk_widget_hide(properties->GtkInfo.scaleMonths);
    properties->decimalorcalendar = DECIMALS;
    properties->format = DECIMAL_GREEKS;
    
    return;
  }

  if( option_algorithms[modeltype].supportTime2 == 2 )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_show(properties->GtkInfo.labelTime2);
    gtk_widget_show(properties->GtkInfo.buttonCalendar2);
    gtk_widget_show(properties->GtkInfo.label2);
    //g_print("label2 show 1\n");
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToDividend);
    //g_print("show Time2\n");
  }

  if( !option_algorithms[modeltype].supportTime2 )
  {
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_hide(properties->GtkInfo.labelTime2);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar2);
    gtk_widget_hide(properties->GtkInfo.label2);
    //g_print("label2 hide\n");
    gtk_widget_hide(properties->GtkInfo.labelDaysToDividend);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToDividend);
    //g_print("dont show Time2\n");
  }

  if( option_algorithms[modeltype].supportTime3 == 1 )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonTime3);
    gtk_widget_show(properties->GtkInfo.labelTime3);
    gtk_widget_show(properties->GtkInfo.buttonCalendar3);
    gtk_widget_show(properties->GtkInfo.label3);
    //g_print("label3 show 1\n");
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend2);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToDividend2);
    //g_print("show Time3\n");
  } else
  {
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime3);
    gtk_widget_hide(properties->GtkInfo.labelTime3);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar3);
    gtk_widget_hide(properties->GtkInfo.label3);
    gtk_widget_hide(properties->GtkInfo.labelDaysToDividend2);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToDividend2);
    //g_print("dont show Time3\n");
  }

  if( !option_algorithms[modeltype].perpetual )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonTime);
    gtk_widget_show(properties->GtkInfo.label1);
    gtk_widget_show(properties->GtkInfo.labelDaysToExpr);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToExpr);
    gtk_widget_show(properties->GtkInfo.labelTime1);
    gtk_widget_show(properties->GtkInfo.checkbuttonDateEngine);
    gtk_widget_show(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_show(properties->GtkInfo.buttonCalendar);
    //g_print("show time1\n");
  }

  if( option_algorithms[modeltype].supportTime2 == 1 )
  {
    gtk_widget_hide(properties->GtkInfo.checkbuttonDateEngine);
    gtk_widget_hide(properties->GtkInfo.buttonProperties);
  }

  if( properties->decimalorcalendar == DECIMALS || option_algorithms[modeltype].supportTime2 == 1 )
  {
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
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats2);
  } else 
  {
    //
    gtk_widget_hide(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar);
    gtk_widget_hide(properties->GtkInfo.spinbuttonTime);
    gtk_widget_hide(properties->GtkInfo.label1);
    gtk_widget_hide(properties->GtkInfo.labelDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDaysToExpr);
    gtk_widget_hide(properties->GtkInfo.labelTime1);

    gtk_widget_show(properties->GtkInfo.labelCycle);
    gtk_widget_show(properties->GtkInfo.comboboxCycle);
    gtk_widget_show(properties->GtkInfo.scaleMonths);
    gtk_widget_show(properties->GtkInfo.buttonProperties);

    gtk_widget_show(properties->GtkInfo.radiobutton1);
    gtk_widget_show(properties->GtkInfo.radiobutton2);
    gtk_widget_show(properties->GtkInfo.radiobutton3);
    gtk_widget_show(properties->GtkInfo.radiobutton4);
    gtk_widget_show(properties->GtkInfo.radiobutton5);
    gtk_widget_show(properties->GtkInfo.labelDisplayFormats);
    gtk_widget_show(properties->GtkInfo.labelDisplayFormats2);

    show_label_expirations(properties);
  } 

  if( option_algorithms[modeltype].assetClass )
  {
    gtk_widget_hide(properties->GtkInfo.labelCycle);
    gtk_widget_hide(properties->GtkInfo.comboboxCycle);
    gtk_widget_hide(properties->GtkInfo.radiobutton1);
    gtk_widget_hide(properties->GtkInfo.radiobutton2);
    gtk_widget_hide(properties->GtkInfo.radiobutton3);
    gtk_widget_hide(properties->GtkInfo.radiobutton4);
    gtk_widget_hide(properties->GtkInfo.radiobutton5);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats2);
  }

} // void updateTime(int modeltype, struct _properties *properties)

void updatePrecision(int modeltype, struct _properties *properties)
{
  g_print("updatePrecision()\n");
  
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonPrice),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonRate),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonStandardDeviation),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDividend),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime2),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonTime3),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToExpr),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToDividend),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDaysToDividend2),properties->precision);

  if( option_algorithms[modeltype].iUseZ == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseZ),properties->precision);

  if( option_algorithms[modeltype].iUseB == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseB),properties->precision);

  if( option_algorithms[modeltype].iUseJ == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseJ),properties->precision);

  if( option_algorithms[modeltype].iUseP == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseP),properties->precision);

  if( option_algorithms[modeltype].iUseQ == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseQ),properties->precision);

  if( option_algorithms[modeltype].iUseR == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseR),properties->precision);

  if( option_algorithms[modeltype].iUseS == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseS),properties->precision);

  if( option_algorithms[modeltype].iUseT == 1 )
    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseT),properties->precision);

  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistMean),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistVariance),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike),properties->precision);
  gtk_spin_button_set_digits(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonCustomStrike2),properties->precision);

  setup_tree_view(properties);

} // void updatePrecision(int modeltype, struct _properties *properties)

void updateStepping(struct _properties *properties)
{
  g_print("updateStepping()\n");

  if( option_algorithms[properties->modeltype].supportSteps )
  {
    //g_print("supportSteps\n");
    properties->GtkInfo.spin_int_steps = GTK_ADJUSTMENT (gtk_adjustment_new (option_algorithms[properties->modeltype].steps,   1, 50000,     1,   10, 0));
    gtk_spin_button_set_adjustment (GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSteps),properties->GtkInfo.spin_int_steps);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSteps),option_algorithms[properties->modeltype].steps);
    gtk_widget_show(properties->GtkInfo.spinbuttonSteps);
    gtk_widget_show(properties->GtkInfo.labelSteps);
    gtk_widget_hide(properties->GtkInfo.comboboxCND);
    gtk_widget_hide(properties->GtkInfo.labelCND);
    gtk_widget_hide(properties->GtkInfo.labelDistMean);
    gtk_widget_hide(properties->GtkInfo.labelDistVariance);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDistMean);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDistVariance);

  } else if( integration_method[properties->integration_type].method )
  {
    properties->GtkInfo.spin_int_steps = GTK_ADJUSTMENT (gtk_adjustment_new (integration_method[properties->integration_type].resolution,
                                                         1 + integration_method[properties->integration_type].allowOnlyEven,
                                                         ((integration_method[properties->integration_type].UpperLimit == 0) ? 10000 : integration_method[properties->integration_type].UpperLimit),
                                                         1 + integration_method[properties->integration_type].allowOnlyEven,
                                                         1 + integration_method[properties->integration_type].allowOnlyEven,
                                                         0));

    gtk_spin_button_set_adjustment (GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSteps),properties->GtkInfo.spin_int_steps);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSteps),integration_method[properties->integration_type].resolution);
    
    gtk_widget_show(properties->GtkInfo.spinbuttonSteps);
    gtk_widget_show(properties->GtkInfo.labelSteps);

    if( option_algorithms[properties->modeltype].supportCND )
    {
        gtk_widget_show(properties->GtkInfo.comboboxCND);
        gtk_widget_show(properties->GtkInfo.labelCND);
    }

    if( !option_algorithms[properties->modeltype].failsOnMeanVarianceChanges )
    {
      gtk_widget_show(properties->GtkInfo.labelDistMean);
      gtk_widget_show(properties->GtkInfo.labelDistVariance);
      gtk_widget_show(properties->GtkInfo.spinbuttonDistMean);
      gtk_widget_show(properties->GtkInfo.spinbuttonDistVariance);
    }

  } else
  {
    //g_print("hide spinbuttonSteps labelSteps\n");
    //g_print("show comboboxCND labelCND\n");
    gtk_widget_hide(properties->GtkInfo.spinbuttonSteps);
    gtk_widget_hide(properties->GtkInfo.labelSteps);
    gtk_widget_hide(properties->GtkInfo.labelDistMean);
    gtk_widget_hide(properties->GtkInfo.labelDistVariance);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDistMean);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDistVariance);

    if( option_algorithms[properties->modeltype].supportCND )
    {
      g_print("show comboboxCND\n");
      gtk_widget_show(properties->GtkInfo.comboboxCND);
      gtk_widget_show(properties->GtkInfo.labelCND);
    }
  }

} // void updateStepping(struct _properties *properties)

void on_window_destroy( gpointer user_data )
{
  if( properties.GtkInfo.gcalculate_options )
  {
    g_source_remove(properties.GtkInfo.gcalculate_options);
    properties.GtkInfo.gcalculate_options = 0;
  }

  pthread_mutex_destroy(&properties.data.mutexCashflow);

  const char *const closeLogger="";
  logger(closeLogger, 0, 0);
 
  gtk_main_quit();

} // void on_window_destroy( gpointer user_data )

int main(int argc, char *argv[])
{
  GError *err = NULL;
    
  programInits(&properties);
  props_defaults_options(&properties,1);

#if defined(HAVE_GETOPT_H) && defined(HAVE_GETTIMEOFDAY)

  process_arguments(argc, (const char **) argv, &properties.data.debug);

#endif

  properties.GtkInfo.spinbuttonTimeInFocusflag = FALSE;

  properties.data.t[0] = 0.25;
  properties.format = DECIMAL_GREEKS;
  properties.decimalorcalendar = DECIMALS;
  properties.precision = 8;

  //char *envlang;
  //envlang = gtk_set_locale();
  //g_print("envlang = %s\n", envlang);

  gtk_init(&argc, &argv);

  properties.GtkInfo.builder = gtk_builder_new();
  properties.GtkInfo.optionmatrix_icon = NULL;

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED  
  properties.GtkInfo.optionmatrix_icon = gdk_pixbuf_new_from_inline(-1, icon_inline, FALSE, NULL);
#endif

#ifdef DATADIR
  char imageName[PATH_MAX];
  snprintf(imageName,sizeof(imageName), "%s/%s/images/6.png", DATADIR, PACKAGE);
  
  if( access(imageName, F_OK ) == 0 )
  {
    properties.GtkInfo.optionmatrix_icon = gdk_pixbuf_new_from_file(imageName, &err);
  } else
  {
    g_print("Can't access %s\n", imageName);
  }
#endif // DATADIR

  // First case is for Windows...
  if( access("images/6.png", F_OK ) == 0 )
  {
    gtk_window_set_default_icon(create_pixbuf("images/6.png"));
  } else
  {
    if(properties.GtkInfo.optionmatrix_icon)
      gtk_window_set_default_icon(properties.GtkInfo.optionmatrix_icon);
    else
      gtk_window_set_default_icon(NULL);
  }

  // 3 ways to load GTK Builder properties Glade file.
  // From file or from string - const char *const gtkBuilderString (defined in gtk_glade_xml.h)
  // or from DATADDIR/PACKAGE/gtk_glade_xml.glade

  gtk_builder_add_from_string(properties.GtkInfo.builder, gtkBuilderString, strlen(gtkBuilderString), &err);
  //gtk_builder_add_from_file(properties.GtkInfo.builder, "gtk_glade_xml.glade", &err);

#ifdef DATADIR
  //char gladeFile[PATH_MAX];
  //snprintf(gladeFile,sizeof(gladeFile),"%s/%s/gtk_glade_xml.glade", DATADIR, PACKAGE);
  //gtk_builder_add_from_file(properties.GtkInfo.builder, gladeFile, &err);
#endif

  if(err != NULL)
  {
    //g_print("strlen(gtkBuilderString) = %lu\n",strlen(gtkBuilderString));
    g_warning("%s", err->message);
    g_error_free(err);
  }

  properties.GtkInfo.window = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "window1"));

  properties.GtkInfo.labelTime1 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelTime1"));
  properties.GtkInfo.labelTime2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelTime2"));
  properties.GtkInfo.labelTime3 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelTime3"));
  properties.GtkInfo.labelDisplayTime = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelDisplayTime"));
  properties.GtkInfo.label1 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "label1"));
  properties.GtkInfo.label2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "label2"));
  properties.GtkInfo.label3 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "label3"));
  properties.GtkInfo.vpanel1  = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "vpanel1"));
  properties.GtkInfo.tableTop = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "tableTop"));
  properties.GtkInfo.labelPrice = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelPrice"));
  properties.GtkInfo.labelSpread = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelSpread"));
  properties.GtkInfo.buttonProperties = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonProperties"));
  properties.GtkInfo.buttonDividends = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonDividends"));
  properties.GtkInfo.buttonCalendar = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonCalendar"));
  properties.GtkInfo.buttonCalendar2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonCalendar2"));
  properties.GtkInfo.buttonCalendar3 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonCalendar3"));
  properties.GtkInfo.buttonCoupons = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonCoupons"));
  properties.GtkInfo.buttonPrincipal = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "buttonPrincipal"));
  properties.GtkInfo.labelCalendar = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelCalendar"));
  properties.GtkInfo.labelCalendar2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelCalendar2"));
  properties.GtkInfo.spinbuttonPrice = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonPrice"));
  properties.GtkInfo.spinbuttonTime = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonTime"));
  properties.GtkInfo.spinbuttonTime2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonTime2"));
  properties.GtkInfo.spinbuttonTime3 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonTime3"));
  properties.GtkInfo.spinbuttonSleepDelay = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonSleepDelay"));
  properties.GtkInfo.spinbuttonDaysToExpr = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonDaysToExpr"));
  properties.GtkInfo.spinbuttonDaysToDividend = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonDaysToDividend"));
  properties.GtkInfo.spinbuttonDaysToDividend2 = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonDaysToDividend2"));
  properties.GtkInfo.labelRate = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "labelRate"));
  properties.GtkInfo.spinbuttonRate = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonRate"));
  properties.GtkInfo.labelExpirations = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "labelExpirations"));
  properties.GtkInfo.labelModel = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "labelModel"));
  properties.GtkInfo.comboboxModel = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "comboboxModel"));
  properties.GtkInfo.labelCND = GTK_WIDGET (gtk_builder_get_object (properties.GtkInfo.builder, "labelCND"));
  properties.GtkInfo.comboboxCND = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "comboboxCND"));
  properties.GtkInfo.labelStandardDeviation = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "labelStandardDeviation"));
  properties.GtkInfo.spinbuttonStandardDeviation = GTK_WIDGET(gtk_builder_get_object (properties.GtkInfo.builder, "spinbuttonStandardDeviation"));
  properties.GtkInfo.labelState = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelState"));
  properties.GtkInfo.labelDividend = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelDividend"));
  properties.GtkInfo.labelDaysToExpr = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelDaysToExpr"));
  properties.GtkInfo.labelDaysToDividend = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelDaysToDividend"));
  properties.GtkInfo.labelDaysToDividend2 = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelDaysToDividend2"));
  properties.GtkInfo.spinbuttonDividend = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonDividend"));
  properties.GtkInfo.labelCycle = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelCycle"));
  properties.GtkInfo.comboboxCycle = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "comboboxCycle"));
  properties.GtkInfo.spinbuttonSteps = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonSteps"));
  properties.GtkInfo.labelSteps = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelSteps"));
  properties.GtkInfo.labelPrecision = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelPrecision"));
  properties.GtkInfo.spinbuttonPrecision = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonPrecision"));
  properties.GtkInfo.checkbuttonRealTime = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "checkbuttonRealTime"));
  properties.GtkInfo.checkbuttonDateEngine = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "checkbuttonDateEngine"));
  properties.GtkInfo.checkbuttonSpreads = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "checkbuttonSpreads"));
  properties.GtkInfo.checkbuttonFilterNegativePrice = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "checkbuttonFilterNegativePrice"));
  properties.GtkInfo.labelStrikes = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelStrikes"));
  properties.GtkInfo.labelStrikes2 = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "labelStrikes2"));
  properties.GtkInfo.comboboxStrikes = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "comboboxStrikes"));
  properties.GtkInfo.comboboxState = GTK_WIDGET (gtk_builder_get_object(properties.GtkInfo.builder, "comboboxState"));
  properties.GtkInfo.liststore1 = GTK_LIST_STORE(gtk_builder_get_object(properties.GtkInfo.builder, "liststore1"));
  properties.GtkInfo.scrolledwindow1 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "scrolledwindow1"));
  properties.GtkInfo.labelUseZ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseZ"));
  properties.GtkInfo.labelUseB = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseB"));
  properties.GtkInfo.labelUseJ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseJ"));
  properties.GtkInfo.labelUseP = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseP"));
  properties.GtkInfo.labelUseQ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseQ"));
  properties.GtkInfo.labelUseR = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseR"));
  properties.GtkInfo.labelUseS = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseS"));
  properties.GtkInfo.labelUseT = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelUseT"));
  properties.GtkInfo.spinbuttonUseZ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseZ"));
  properties.GtkInfo.spinbuttonUseB = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseB"));
  properties.GtkInfo.spinbuttonUseJ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseJ"));
  properties.GtkInfo.spinbuttonUseP = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseP"));
  properties.GtkInfo.spinbuttonUseQ = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseQ"));
  properties.GtkInfo.spinbuttonUseR = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseR"));
  properties.GtkInfo.spinbuttonUseS = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseS"));
  properties.GtkInfo.spinbuttonUseT = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonUseT"));
  properties.GtkInfo.scaleStrikes = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "scaleStrikes"));
  properties.GtkInfo.scaleStrikes2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "scaleStrikes2"));
  properties.GtkInfo.scaleMonths = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "scaleMonths"));
  properties.GtkInfo.scaleMonths2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "scaleMonths2"));
  properties.GtkInfo.radiobutton1 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "radiobutton1"));
  properties.GtkInfo.radiobutton2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "radiobutton2"));
  properties.GtkInfo.radiobutton3 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "radiobutton3"));
  properties.GtkInfo.radiobutton4 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "radiobutton4"));
  properties.GtkInfo.radiobutton5 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "radiobutton5"));
  properties.GtkInfo.labelDisplayFormats = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelDisplayFormats"));
  properties.GtkInfo.labelDisplayFormats2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelDisplayFormats2"));
  properties.GtkInfo.menu_quit  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_quit"));
  properties.GtkInfo.menu_about = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_about"));
  properties.GtkInfo.menu_website = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_website"));
  properties.GtkInfo.menu_feedback = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_feedback"));
  properties.GtkInfo.menu_debug_log = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_debug_log"));
  properties.GtkInfo.menu_text_export = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_text_export"));
  properties.GtkInfo.menu_file_export = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_file_export"));
  properties.GtkInfo.menu_source_export = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_source_export"));
  properties.GtkInfo.menu_ListCategory  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_ListCategory"));
  properties.GtkInfo.menu_ListAuthor  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_ListAuthor"));
  properties.GtkInfo.menu_List  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_List"));
  properties.GtkInfo.menu_settings  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "menu_settings"));

  properties.GtkInfo.dialogAbout = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "dialogAbout"));
  properties.GtkInfo.dialogProperties = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "dialogProperties"));
  properties.GtkInfo.dialogSettings = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "dialogSettings"));
  properties.GtkInfo.dialogCalendar = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "dialogCalendar"));
  properties.GtkInfo.labelInfo = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelInfo"));

  properties.GtkInfo.labelWeekday = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelWeekday"));
  properties.GtkInfo.comboboxWeekday = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "comboboxWeekday"));
  properties.GtkInfo.labelOccurance = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelOccurance"));
  properties.GtkInfo.comboboxOccurance = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "comboboxOccurance"));
  properties.GtkInfo.labelDayOffset = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelDayOffset"));
  properties.GtkInfo.spinbuttonDayOffset = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonDayOffset"));
  properties.GtkInfo.labelExpirationTime = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelExpirationTime"));
  properties.GtkInfo.entryExpirationTime = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "entryExpirationTime"));
  properties.GtkInfo.labelTimeError = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelTimeError"));

  properties.GtkInfo.labelDistMean = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelDistMean"));
  properties.GtkInfo.spinbuttonDistMean = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonDistMean"));

  properties.GtkInfo.labelDistVariance = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "labelDistVariance"));
  properties.GtkInfo.spinbuttonDistVariance = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonDistVariance"));
  properties.GtkInfo.spinbuttonCustomStrike  = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonCustomStrike"));
  properties.GtkInfo.spinbuttonCustomStrike2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "spinbuttonCustomStrike2"));

  properties.GtkInfo.calendar1 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "calendar1"));
  properties.GtkInfo.calendar2 = GTK_WIDGET(gtk_builder_get_object(properties.GtkInfo.builder, "calendar2"));

  g_signal_connect(G_OBJECT (properties.GtkInfo.window), "destroy", G_CALLBACK (on_window_destroy), NULL);

  g_signal_connect(G_OBJECT(properties.GtkInfo.checkbuttonRealTime), "toggled", G_CALLBACK(on_checkbuttonRealTime_toggled), (gpointer) &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.checkbuttonDateEngine), "toggled", G_CALLBACK (on_checkbuttonDateEngine_toggled), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.checkbuttonSpreads), "toggled", G_CALLBACK (on_checkbuttonSpreads_toggled), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.checkbuttonFilterNegativePrice), "toggled", G_CALLBACK (on_checkbuttonFilterNegativePrice_toggled), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonPrice), "value-changed", G_CALLBACK (on_spinbuttonPrice_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonRate), "value-changed", G_CALLBACK (on_spinbuttonRate_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonStandardDeviation), "value-changed", G_CALLBACK (on_spinbuttonStandardDeviation_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDividend), "value-changed", G_CALLBACK (on_spinbuttonDividend_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonSteps), "value-changed", G_CALLBACK (on_spinbuttonSteps_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonPrecision), "value-changed", G_CALLBACK (on_spinbuttonPrecision_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime), "value-changed", G_CALLBACK (on_spinbuttonTime_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime), "focus-in-event", G_CALLBACK (on_spinbuttonTime_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime), "focus-out-event", G_CALLBACK (on_spinbuttonTime_focus_out_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime2), "value-changed", G_CALLBACK (on_spinbuttonTime2_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime2), "focus-in-event", G_CALLBACK (on_spinbuttonTime2_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime2), "focus-out-event", G_CALLBACK (on_spinbuttonTime2_focus_out_event), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime3), "value-changed", G_CALLBACK (on_spinbuttonTime3_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime3), "focus-in-event", G_CALLBACK (on_spinbuttonTime3_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonTime3), "focus-out-event", G_CALLBACK (on_spinbuttonTime3_focus_out_event), &properties);

  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToExpr), "focus-in-event", G_CALLBACK (on_spinbuttonDaysToExpr_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToExpr), "focus-out-event", G_CALLBACK (on_spinbuttonDaysToExpr_focus_out_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend), "focus-in-event", G_CALLBACK (on_spinbuttonDaysToDividend_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend), "focus-out-event", G_CALLBACK (on_spinbuttonDaysToDividend_focus_out_event), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend2), "focus-in-event", G_CALLBACK (on_spinbuttonDaysToDividend2_focus_in_event), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend2), "focus-out-event", G_CALLBACK (on_spinbuttonDaysToDividend2_focus_out_event), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseZ), "value-changed", G_CALLBACK (on_spinbuttonUseZ_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseB), "value-changed", G_CALLBACK (on_spinbuttonUseB_value_changed), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseJ), "value-changed", G_CALLBACK (on_spinbuttonUseJ_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseP), "value-changed", G_CALLBACK (on_spinbuttonUseP_value_changed), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseQ), "value-changed", G_CALLBACK (on_spinbuttonUseQ_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseR), "value-changed", G_CALLBACK (on_spinbuttonUseR_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseS), "value-changed", G_CALLBACK (on_spinbuttonUseS_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonUseT), "value-changed", G_CALLBACK (on_spinbuttonUseT_value_changed), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.scaleStrikes), "value-changed", G_CALLBACK (on_scaleStrikes_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.scaleStrikes2), "value-changed", G_CALLBACK (on_scaleStrikes_value_changed2), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.scaleMonths), "value-changed", G_CALLBACK (on_scaleMonths_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.scaleMonths2), "value-changed", G_CALLBACK (on_scaleMonths_value_changed2), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToExpr), "value-changed", G_CALLBACK (on_spinbuttonDaysToExpr_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend), "value-changed", G_CALLBACK (on_spinbuttonDaysToDividend_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDaysToDividend2), "value-changed", G_CALLBACK (on_spinbuttonDaysToDividend2_value_changed), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDistMean), "value-changed", G_CALLBACK (on_spinbuttonDistMean_value_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonDistVariance), "value-changed", G_CALLBACK (on_spinbuttonDistVariance_value_changed), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.spinbuttonSleepDelay), "value-changed", G_CALLBACK (on_spinbuttonSleepDelay_value_changed), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxCycle), "changed", G_CALLBACK (on_comboboxCycle_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxCND), "changed", G_CALLBACK (on_comboboxCND_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxModel), "changed", G_CALLBACK (on_comboboxModel_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxStrikes), "changed", G_CALLBACK (on_comboboxStrikes_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxState), "changed", G_CALLBACK (on_comboboxState_changed), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxWeekday), "changed", G_CALLBACK (on_comboboxWeekday_changed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.comboboxOccurance), "changed", G_CALLBACK (on_comboboxOccurance_changed), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.radiobutton1), "pressed", G_CALLBACK(on_radiobutton1_pressed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.radiobutton2), "pressed", G_CALLBACK(on_radiobutton2_pressed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.radiobutton3), "pressed", G_CALLBACK(on_radiobutton3_pressed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.radiobutton4), "pressed", G_CALLBACK(on_radiobutton4_pressed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.radiobutton5), "pressed", G_CALLBACK(on_radiobutton5_pressed), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_quit), "activate", G_CALLBACK(on_menu_quit_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_about), "activate", G_CALLBACK(on_menu_about_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_website), "activate", G_CALLBACK(on_menu_website_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_feedback), "activate", G_CALLBACK(on_menu_feedback_activate), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_debug_log), "activate", G_CALLBACK(on_menu_debug_log_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_text_export), "activate", G_CALLBACK(on_menu_text_export_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_file_export), "activate", G_CALLBACK(on_menu_file_export_activate), &properties);  
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_source_export), "activate", G_CALLBACK(on_menu_source_export_activate), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_ListCategory), "activate", G_CALLBACK(on_menu_ListCategory_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_ListAuthor), "activate", G_CALLBACK(on_menu_ListAuthor_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_List), "activate", G_CALLBACK(on_menu_List_activate), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.menu_settings), "activate", G_CALLBACK(on_menu_settings_activate), &properties);
  //
  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonProperties), "clicked", G_CALLBACK(on_buttonProperties_clicked), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonDividends), "clicked", G_CALLBACK(on_buttonDividends_clicked), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonCoupons), "clicked", G_CALLBACK(on_buttonCoupons_clicked), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonPrincipal), "clicked", G_CALLBACK(on_buttonPrincipal_clicked), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonCalendar), "clicked", G_CALLBACK(on_buttonCalendar_clicked), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonCalendar2), "clicked", G_CALLBACK(on_buttonCalendar2_clicked), &properties);
  g_signal_connect(G_OBJECT (properties.GtkInfo.buttonCalendar3), "clicked", G_CALLBACK(on_buttonCalendar3_clicked), &properties);

  g_signal_connect(G_OBJECT (properties.GtkInfo.calendar1), "day-selected", G_CALLBACK(on_calendar1_day_selected), &properties);

  g_signal_connect(G_OBJECT(properties.GtkInfo.window), "configure-event", G_CALLBACK(window_configure_event), &properties);

  properties.GtkInfo.spin_int_precision   = GTK_ADJUSTMENT(gtk_adjustment_new (properties.precision, 0.0,  15.0,   1.0,  2.0, 0));
  properties.GtkInfo.spin_int_steps       = GTK_ADJUSTMENT(gtk_adjustment_new (100,   1,  50000,     1,   10, 0));
  properties.GtkInfo.spin_int_sleep_delay = GTK_ADJUSTMENT(gtk_adjustment_new (1  ,   1,  86400,     1,   10, 0));
  properties.GtkInfo.spin_float_price     = GTK_ADJUSTMENT(gtk_adjustment_new (100,   0,  50000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_rate      = GTK_ADJUSTMENT(gtk_adjustment_new (.05,  -1,  10000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_dist_mean = GTK_ADJUSTMENT(gtk_adjustment_new ( 0,  -100, 10000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_dist_var  = GTK_ADJUSTMENT(gtk_adjustment_new ( 1,  -100, 10000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_sd        = GTK_ADJUSTMENT(gtk_adjustment_new (.25,   0,  10000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_dividend  = GTK_ADJUSTMENT(gtk_adjustment_new (.00,   0,  99999,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_time      = GTK_ADJUSTMENT(gtk_adjustment_new (.25,   0,  99999, 0.000001902587519,
                                                            0.000114155251142, 0));
  properties.GtkInfo.spin_float_time2     = GTK_ADJUSTMENT(gtk_adjustment_new (.10,   0,  99999, 0.000001902587519,
                                                            0.000114155251142, 0));
  properties.GtkInfo.spin_float_time3     = GTK_ADJUSTMENT(gtk_adjustment_new (.10,   0,  99999, 0.000001902587519,
                                                            0.000114155251142, 0));
  properties.GtkInfo.spin_float_days_to_expr = GTK_ADJUSTMENT(gtk_adjustment_new (.00,   0,  99999,  1.00, 1.00, 0));
  properties.GtkInfo.spin_float_days_to_dividend  = GTK_ADJUSTMENT(gtk_adjustment_new (.00,   0,  99999,  1.00, 1.00, 0));
  properties.GtkInfo.spin_float_days_to_dividend2 = GTK_ADJUSTMENT(gtk_adjustment_new (.00,   0,  99999,  1.00, 1.00, 0));
  properties.GtkInfo.spin_float_custom_strike  = GTK_ADJUSTMENT(gtk_adjustment_new (100,   0,  50000,  0.01, 0.10, 0));
  properties.GtkInfo.spin_float_custom_strike2 = GTK_ADJUSTMENT(gtk_adjustment_new (100,   0,  50000,  0.01, 0.10, 0));

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties.GtkInfo.checkbuttonRealTime),properties.realTimeBleeding);

  properties.GtkInfo.scale_int_strikes = GTK_ADJUSTMENT(gtk_adjustment_new (50,   1,  100,  1, 2, 0));
  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties.GtkInfo.scaleStrikes),properties.GtkInfo.scale_int_strikes);

  properties.GtkInfo.scale_int_strikes2 = GTK_ADJUSTMENT(gtk_adjustment_new (50,  1,  100,  1, 2, 0));
  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties.GtkInfo.scaleStrikes2),properties.GtkInfo.scale_int_strikes2);

  properties.GtkInfo.scale_int_months = GTK_ADJUSTMENT (gtk_adjustment_new (0,   0,  120,  1, 1, 0));
  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties.GtkInfo.scaleMonths),properties.GtkInfo.scale_int_months);
  gtk_button_set_relief(GTK_BUTTON(properties.GtkInfo.scaleMonths), GTK_RELIEF_NORMAL);

  properties.GtkInfo.scale_int_months2 = GTK_ADJUSTMENT (gtk_adjustment_new (0,   0,  120,  1, 1, 0));
  gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(properties.GtkInfo.scaleMonths2),properties.GtkInfo.scale_int_months2);
  gtk_button_set_relief(GTK_BUTTON(properties.GtkInfo.scaleMonths2), GTK_RELIEF_NORMAL);

  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonPrice),properties.GtkInfo.spin_float_price);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonRate),properties.GtkInfo.spin_float_rate);

  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDistMean),properties.GtkInfo.spin_float_dist_mean);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDistVariance),properties.GtkInfo.spin_float_dist_var);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonStandardDeviation),properties.GtkInfo.spin_float_sd);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDividend),properties.GtkInfo.spin_float_dividend);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonPrecision),properties.GtkInfo.spin_int_precision);

  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonSteps),properties.GtkInfo.spin_int_steps);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonSleepDelay),properties.GtkInfo.spin_int_sleep_delay);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonTime),properties.GtkInfo.spin_float_time);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonTime2),properties.GtkInfo.spin_float_time2);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonTime3),properties.GtkInfo.spin_float_time3);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDaysToExpr),properties.GtkInfo.spin_float_days_to_expr);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDaysToDividend),properties.GtkInfo.spin_float_days_to_dividend);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDaysToDividend2),properties.GtkInfo.spin_float_days_to_dividend2);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonCustomStrike),properties.GtkInfo.spin_float_custom_strike);
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonCustomStrike2),properties.GtkInfo.spin_float_custom_strike2);

  gtk_window_set_icon(GTK_WINDOW(properties.GtkInfo.window), create_pixbuf("images/2.png"));

  GtkAdjustment *spin_int_DayOffset;
  spin_int_DayOffset = GTK_ADJUSTMENT(gtk_adjustment_new (1, 0, 6, 1, 1, 0));
  gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties.GtkInfo.spinbuttonDayOffset),spin_int_DayOffset);

  // These buttons are for Date Engine Properties button's dialog
  GtkWidget *okay;
  GtkWidget *cancel;

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  okay = gtk_button_new_from_stock(GTK_STOCK_OK);
  cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
  gtk_container_add( GTK_CONTAINER ( gtk_dialog_get_action_area(GTK_DIALOG(properties.GtkInfo.dialogProperties))), okay );
  gtk_container_add( GTK_CONTAINER ( gtk_dialog_get_action_area(GTK_DIALOG(properties.GtkInfo.dialogProperties))), cancel );
  g_signal_connect(G_OBJECT (okay), "clicked", G_CALLBACK (on_dialogProperties_ok), (gpointer) &properties);
  g_signal_connect(G_OBJECT (cancel), "clicked", G_CALLBACK (on_dialogProperties_cancel), (gpointer) &properties);
#endif
#ifdef HAVE_LIBGTK_3
  //okay = gtk_button_new_with_label("Ok");
  //cancel = gtk_button_new_with_label("Cancel");
  g_signal_connect(G_OBJECT (gtk_dialog_add_button(GTK_DIALOG(properties.GtkInfo.dialogProperties),"Ok",GTK_RESPONSE_OK)), "clicked", G_CALLBACK (on_dialogProperties_ok), (gpointer) &properties);
  g_signal_connect(G_OBJECT (gtk_dialog_add_button(GTK_DIALOG(properties.GtkInfo.dialogProperties),"Cancel",GTK_RESPONSE_CANCEL)), "clicked", G_CALLBACK (on_dialogProperties_cancel), (gpointer) &properties);
#endif

  g_signal_connect(G_OBJECT (properties.GtkInfo.dialogProperties), "delete-event", G_CALLBACK(on_dialogProperties_delete_event), &properties);

  gtk_window_set_title(GTK_WINDOW(properties.GtkInfo.dialogProperties), "Date Engine Properties");
  gtk_window_set_icon(GTK_WINDOW(properties.GtkInfo.dialogProperties), create_pixbuf("images/2.png"));

  // These buttons are for Menu -> Prefs -> Settings
  GtkWidget *okaySettings;
  GtkWidget *cancelSettings;

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  okaySettings = gtk_button_new_from_stock(GTK_STOCK_OK);
  cancelSettings = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
  gtk_container_add( GTK_CONTAINER ( gtk_dialog_get_action_area(GTK_DIALOG(properties.GtkInfo.dialogSettings))), okaySettings );
  gtk_container_add( GTK_CONTAINER ( gtk_dialog_get_action_area(GTK_DIALOG(properties.GtkInfo.dialogSettings))), cancelSettings );
  g_signal_connect(G_OBJECT (okaySettings), "clicked", G_CALLBACK (on_dialogSettings_ok), (gpointer) &properties);
  g_signal_connect(G_OBJECT (cancelSettings), "clicked", G_CALLBACK (on_dialogSettings_cancel), (gpointer) &properties);
#endif
#ifdef HAVE_LIBGTK_3
  okaySettings = gtk_button_new_with_label("Ok");
  cancelSettings = gtk_button_new_with_label("Cancel");
  g_signal_connect(G_OBJECT (gtk_dialog_add_button(GTK_DIALOG(properties.GtkInfo.dialogSettings),"Ok",GTK_RESPONSE_OK)), "clicked", G_CALLBACK (on_dialogSettings_ok), (gpointer) &properties);
  g_signal_connect(G_OBJECT (gtk_dialog_add_button(GTK_DIALOG(properties.GtkInfo.dialogSettings),"Cancel",GTK_RESPONSE_CANCEL)), "clicked", G_CALLBACK (on_dialogSettings_cancel), (gpointer) &properties);
#endif

  g_signal_connect(G_OBJECT (properties.GtkInfo.dialogSettings), "delete-event", G_CALLBACK(on_dialogSettings_delete_event), &properties);

  gtk_window_set_title(GTK_WINDOW(properties.GtkInfo.dialogSettings), "Settings");
  gtk_window_set_icon(GTK_WINDOW(properties.GtkInfo.dialogSettings), create_pixbuf("images/2.png"));

  g_signal_connect(G_OBJECT (properties.GtkInfo.dialogCalendar), "delete-event", G_CALLBACK(on_dialogCalendar_delete_event), &properties);

  ////////////////////////////////////////////////////////////////////////
  int index;

  const int num_cycles = sizeofoptionscycle/sizeof(optionscycle[0]);
  struct elementList listOptionCycles[num_cycles];
  for(index = 0; index < num_cycles; index++)
  {
    snprintf(listOptionCycles[index].elementName,sizeof(listOptionCycles[index].elementName),"%s",optionscycle[index]);
  }
  set_up_combobox_with_array2(properties.GtkInfo.comboboxCycle, listOptionCycles, num_cycles);

  ////////////////////////////////////////////////////////////////////////

  const int num_integration = sizeofintegration_method/sizeof(struct numerical_integration_method);

  struct elementList listCND[num_integration];
  for(index = 0; index < num_integration; index++)
  {
    strncpy(listCND[index].elementName,integration_method[index].des,sizeof(listCND[index].elementName));
  }
  set_up_combobox_with_array2(properties.GtkInfo.comboboxCND, listCND, num_integration);

  ////////////////////////////////////////////////////////////////////////
  const int num_strike_control = sizeofstrike_control/(sizeof(struct _strike_control));

  struct elementList listStrikeControl[num_strike_control];
  for(index = 0; index < num_strike_control; index++)
  {
    g_print("%d  des = %s\n", index, strike_control[index].des);
    strncpy(listStrikeControl[index].elementName,strike_control[index].des,sizeof(listStrikeControl[index].elementName));
  }
  set_up_combobox_with_array2(properties.GtkInfo.comboboxStrikes, listStrikeControl, num_strike_control);

  const int num_models = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  properties.listModelsForGroups = new elementListWithGroup[num_models];
  for(index = 0; index < num_models; index++)
  {
    snprintf(properties.listModelsForGroups[index].elementName,sizeof(properties.listModelsForGroups[index].elementName),
             "%s",option_algorithms[index].des);
    snprintf(properties.listModelsForGroups[index].groupName,sizeof(properties.listModelsForGroups[index].groupName),
             "%s",option_algorithms[index].category);
    properties.listModelsForGroups[index].index = index;
  }

  set_up_combobox_with_array_use_groups(properties.GtkInfo.comboboxModel, properties.listModelsForGroups, num_models, properties.TreeToIndex,1);

  ////////////////////////////////////////////////////////////////////////

  expires(LEG1,30,properties.skipmonth,&properties);
  expires(LEG2,30,properties.skipmonth2,&properties);

  properties.GtkInfo.treeview = gtk_tree_view_new();

  setup_tree_view(&properties);
    
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (properties.GtkInfo.scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add( GTK_CONTAINER (properties.GtkInfo.scrolledwindow1), properties.GtkInfo.treeview );

  // Use G_PRIORITY_LOW so computationally intensive models are less likely to freeze up GUI...
  //properties.GtkInfo.gcalculate_options = g_timeout_add(1000 * properties.updatedelayseconds, (GSourceFunc) calculate_options, &properties);
  properties.GtkInfo.gcalculate_options = g_timeout_add_full(G_PRIORITY_LOW, 1000 * properties.updatedelayseconds, (GSourceFunc) calculate_options, &properties, NULL);

  updatePrecision(0,&properties);
  updateTime(0,&properties);

  //gtk_builder_connect_signals(properties.GtkInfo.builder, NULL);

  gtk_widget_show_all(properties.GtkInfo.window);

  gtk_widget_hide(properties.GtkInfo.spinbuttonSteps);
  gtk_widget_hide(properties.GtkInfo.labelSteps);
  gtk_widget_hide(properties.GtkInfo.spinbuttonTime2);
  gtk_widget_hide(properties.GtkInfo.spinbuttonTime3);
  gtk_widget_hide(properties.GtkInfo.labelTime2);
  gtk_widget_hide(properties.GtkInfo.labelTime3);
  gtk_widget_hide(properties.GtkInfo.buttonCalendar2);
  gtk_widget_hide(properties.GtkInfo.buttonCalendar3);
  gtk_widget_hide(properties.GtkInfo.label2);
  gtk_widget_hide(properties.GtkInfo.label3);

  gtk_widget_hide(properties.GtkInfo.labelUseZ);
  gtk_widget_hide(properties.GtkInfo.labelUseB);
  gtk_widget_hide(properties.GtkInfo.labelUseJ);
  gtk_widget_hide(properties.GtkInfo.labelUseP);
  gtk_widget_hide(properties.GtkInfo.labelUseQ);
  gtk_widget_hide(properties.GtkInfo.labelUseR);
  gtk_widget_hide(properties.GtkInfo.labelUseS);
  gtk_widget_hide(properties.GtkInfo.labelUseT);
  gtk_widget_hide(properties.GtkInfo.labelState);
  gtk_widget_hide(properties.GtkInfo.comboboxState);

  gtk_widget_hide(properties.GtkInfo.spinbuttonUseZ);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseB);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseJ);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseP);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseQ);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseR);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseS);
  gtk_widget_hide(properties.GtkInfo.spinbuttonUseT);

  gtk_widget_hide(properties.GtkInfo.labelCycle);
  gtk_widget_hide(properties.GtkInfo.comboboxCycle);
  gtk_widget_hide(properties.GtkInfo.labelDaysToDividend);
  gtk_widget_hide(properties.GtkInfo.labelDaysToDividend2);
  gtk_widget_hide(properties.GtkInfo.spinbuttonDaysToDividend);
  gtk_widget_hide(properties.GtkInfo.spinbuttonDaysToDividend2);
  gtk_widget_hide(properties.GtkInfo.spinbuttonDividend);
  gtk_widget_hide(properties.GtkInfo.labelDividend);
  gtk_widget_hide(properties.GtkInfo.labelExpirations);
  gtk_widget_hide(properties.GtkInfo.buttonProperties);
  gtk_widget_hide(properties.GtkInfo.scaleMonths);
  gtk_widget_hide(properties.GtkInfo.scaleMonths2);
  gtk_widget_hide(properties.GtkInfo.scaleStrikes2);
  gtk_widget_hide(properties.GtkInfo.radiobutton1);
  gtk_widget_hide(properties.GtkInfo.radiobutton2);
  gtk_widget_hide(properties.GtkInfo.radiobutton3);
  gtk_widget_hide(properties.GtkInfo.radiobutton4);
  gtk_widget_hide(properties.GtkInfo.radiobutton5);
  gtk_widget_hide(properties.GtkInfo.labelDisplayFormats);
  gtk_widget_hide(properties.GtkInfo.labelDisplayFormats2);
  gtk_widget_hide(properties.GtkInfo.labelInfo);
  gtk_widget_hide(properties.GtkInfo.labelDistMean);
  gtk_widget_hide(properties.GtkInfo.spinbuttonDistMean);
  gtk_widget_hide(properties.GtkInfo.labelDistVariance);
  gtk_widget_hide(properties.GtkInfo.spinbuttonDistVariance);
  gtk_widget_hide(properties.GtkInfo.labelStrikes2);
  gtk_widget_hide(properties.GtkInfo.spinbuttonCustomStrike);
  gtk_widget_hide(properties.GtkInfo.spinbuttonCustomStrike2);
  gtk_widget_hide(properties.GtkInfo.checkbuttonSpreads);
  gtk_widget_hide(properties.GtkInfo.labelSpread);
  gtk_widget_hide(properties.GtkInfo.buttonDividends);
  gtk_widget_hide(properties.GtkInfo.menu_source_export);
  gtk_widget_hide(properties.GtkInfo.buttonCoupons);
  gtk_widget_hide(properties.GtkInfo.buttonPrincipal);

  on_comboboxModel_changed_show(0, &properties);
  on_comboboxModel_changed_hide(0, &properties);

  checkForSourceCode(&properties);

  g_object_unref(G_OBJECT (properties.GtkInfo.builder));

  gtk_main();

  properties.TreeToIndex.clear();

  if( properties.listModelsForGroups )
  {
    delete [] properties.listModelsForGroups;
    properties.listModelsForGroups = 0;
  }

  exit(EXIT_SUCCESS);

} // int main(int argc, char *argv[])

void window_configure_event( GtkWidget *widget, struct _properties *properties )
{
  g_print("window_configure_event()\n");
}
