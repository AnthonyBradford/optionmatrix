/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_display.cpp of optionmatrix                                    */
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

void file_export(struct _properties *properties, char *dataExport)
{
  g_print("file_export()\n");

  properties->fileExport = false;
  properties->textExport = false;

  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Save File",
                                        GTK_WINDOW(properties->GtkInfo.window),
                                        action,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ("_Save"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;

    filename = gtk_file_chooser_get_filename (chooser);
    g_print("filename = %s\n", filename);

    ofstream optionmatrixFileExport;
    
    optionmatrixFileExport.open (filename);

    if (optionmatrixFileExport.is_open())
    {
      optionmatrixFileExport << dataExport;
      optionmatrixFileExport.close();
 
    } else {
      g_print("Error could not open file: %s\n", filename);
    }

    g_free (filename);
  }

  gtk_widget_destroy (dialog);
 
}

void text_export(struct _properties *properties, char *dataExport)
{
  g_print("text_export()\n");

  properties->textExport = false;

  GtkWidget *window, *scrolled_win, *textview;
  GtkTextBuffer *buffer;

  time_t mytime;
  struct tm *my_tm;
    
  time(&mytime);
  my_tm=localtime(&mytime);

  char tstring[400] = { 0 };
  char windowTitle[1024] = { 0 };
  strftime(tstring,sizeof(tstring),"%a %b %d %Y %H:%M:%S",my_tm);
  snprintf(windowTitle,sizeof(windowTitle),"%s Export %s @ %s", PACKAGE_NAME, option_algorithms[properties->modeltype].des, tstring);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), windowTitle);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 1050, 300);

  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("images/2.png"));

  textview = gtk_text_view_new ();
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
  
  gtk_text_buffer_set_text (buffer, dataExport, -1);
  
  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  
  gtk_container_add (GTK_CONTAINER (window), scrolled_win);
  gtk_widget_show_all (window);

} // void text_export(struct _properties *properties, char *dataExport)

void setup_tree_view(struct _properties *properties)
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  char strike[200] = { 0 };
  char call[200] = { 0 };
  char put[200] = { 0 };

  // delete previous column names if any...
  GtkTreeViewColumn *col;
  while((col = gtk_tree_view_get_column(GTK_TREE_VIEW(properties->GtkInfo.treeview),0)) != NULL)
  {
    gtk_tree_view_remove_column(GTK_TREE_VIEW(properties->GtkInfo.treeview),col);
  }

  if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
  {
    //g_print("tree Future detected\n");

    if(properties->decimalorcalendar == CALENDAR )
    {
      //g_print("tree CALENDAR future detect\n");

      if( properties->spreads == 0 )
      {
        properties->GtkInfo.liststore1 = gtk_list_store_new (5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );
      } else if( properties->spreads == 1 )
      {
        properties->GtkInfo.liststore1 = gtk_list_store_new (12, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );
      }

      gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
      g_object_unref (properties->GtkInfo.liststore1);
  
      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                           ("Expiration", renderer, "text", X1 , NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                          ("Price", renderer, "text", X2, NULL);
                          //(option_algorithms[properties->modeltype].price, renderer, "text", X2, NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                           ("Days to Expr", renderer, "text", X3, NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
        //                 ("Decimal Time", renderer, "text", X4, NULL);
                           ("Years to Expr", renderer, "text", X4, NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                           ("Ticker", renderer, "text", X5, NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      if( properties->spreads == 1 )
      {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Expiration", renderer, "text", X6 , NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Price", renderer, "text", X7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Days to Expr", renderer, "text", X8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Years to Expr", renderer, "text", X9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Ticker", renderer, "text", X10, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Spread", renderer, "text", X11, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes
                           ("Spread Ticker", renderer, "text", X12, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
      }

      return;
    }

    if(properties->decimalorcalendar == DECIMALS )
    {
      //g_print("DECIMALS future detect\n");

      properties->GtkInfo.liststore1 = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING );

      gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
      g_object_unref (properties->GtkInfo.liststore1);
  
      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                           ("Description", renderer, "text", X1 , NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

      renderer = gtk_cell_renderer_text_new();
      column = gtk_tree_view_column_new_with_attributes
                           ("Value", renderer, "text", X2, NULL);
      gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
      return;
    }
  }

  if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
  {
    g_print("Bonds detected\n");

    properties->GtkInfo.liststore1 = gtk_list_store_new (8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

    gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
    g_object_unref (properties->GtkInfo.liststore1);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", X1 , NULL);

    ///////////////////////////////////////////////////////////////////////////////////////////

    g_object_set (GTK_TREE_VIEW (properties->GtkInfo.treeview), "has-tooltip", TRUE, NULL); // Works
    
    //g_signal_connect (column, "query-tooltip",
    //                G_CALLBACK (query_tooltip_tree_view_cb), NULL);
    //g_signal_connect (gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view)),
    //                "changed", G_CALLBACK (selection_changed_cb), tree_view);

    if(gtk_tree_view_column_get_widget(column))
    {
      g_print("gtk_tree_view_column_get_widget(column) WORKS!!!!!!!!!!!!!!!!!!!!!!!!");
      gtk_widget_set_tooltip_text(GTK_WIDGET(gtk_tree_view_column_get_widget(column)), "This is a test"); // Fails
      gtk_widget_set_tooltip_text(gtk_tree_view_column_get_widget(column), "This is a test"); // Fails
      gtk_widget_set_tooltip_markup(GTK_WIDGET(gtk_tree_view_column_get_widget(column)), "This is a test"); // Fails
      gtk_widget_set_tooltip_markup(gtk_tree_view_column_get_widget(column), "This is a test"); // Fails
    }

    if(gtk_tree_view_get_column (GTK_TREE_VIEW (properties->GtkInfo.treeview), 0))
    {
       g_print("gtk_tree_view_get_column (GTK_TREE_VIEW (properties->GtkInfo.treeview), 0) WORKS!!!!!!!!!!!!!!!!!!!!!!!!");
    }
   

    //gtk_tree_view_column_set_clickable (column, TRUE);       // works
    //g_object_set (gtk_tree_view_column_get_button (column), "tooltip-text", "Header", NULL);    

    ///////////////////////////////////////////////////////////////////////////////////////////

    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Value", renderer, "text", X2 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", X3 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Time", renderer, "text", X4 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    return;
  }

  if( option_algorithms[properties->modeltype].assetClass == TERMSTRUCTURE_CLASS )  {
    g_print("Termstructure detected\n");

    properties->GtkInfo.liststore1 = gtk_list_store_new (8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

    gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
    g_object_unref (properties->GtkInfo.liststore1);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", X1 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Value", renderer, "text", X2 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", X3 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Time", renderer, "text", X4 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    return;

  }

  if( properties->decimalorcalendar == DECIMALS )
  {
    properties->GtkInfo.liststore1 = gtk_list_store_new (14, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

    gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
    g_object_unref (properties->GtkInfo.liststore1);
  
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (option_algorithms[properties->modeltype].price, renderer, "text", X1 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(call,sizeof(call),"%s",option_algorithms[properties->modeltype].call);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (call, renderer, "text", X3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(put,sizeof(put),"%s",option_algorithms[properties->modeltype].put);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (put, renderer, "text", X4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Delta", renderer, "text", X5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Delta", renderer, "text", X6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Gamma", renderer, "text", X7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Vega", renderer, "text", X8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Theta", renderer, "text", X9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Theta", renderer, "text", X10, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Rho", renderer, "text", X11, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Rho", renderer, "text", X12, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Elast", renderer, "text", X13, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Elast", renderer, "text", X14, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

  } 
  else if(properties->decimalorcalendar == CALENDAR && properties->format == CALENDAR_OPTIONS6 )
  {
    properties->GtkInfo.liststore1 = gtk_list_store_new (8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model (GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1));
    g_object_unref (properties->GtkInfo.liststore1);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (option_algorithms[properties->modeltype].price, renderer, "text", X1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
  
    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    char textDate[500] = { 0 };

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].call,mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].call,mon[*(properties->expiration_month+1)],*(properties->days_to_expiration+1),(double)*(properties->expiration_year+1) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].call,mon[*(properties->expiration_month+2)],*(properties->days_to_expiration+2),(double)*(properties->expiration_year+2) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].put,mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].put,mon[*(properties->expiration_month+1)],*(properties->days_to_expiration+1),(double)*(properties->expiration_year+1) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s %s%2d %04.0f",option_algorithms[properties->modeltype].put,mon[*(properties->expiration_month+2)],*(properties->days_to_expiration+2),(double)*(properties->expiration_year+2) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

  } else if( properties->decimalorcalendar == CALENDAR && properties->format == CALENDAR_OPTIONS5 )
  {
    properties->GtkInfo.liststore1 = gtk_list_store_new( 10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

    gtk_tree_view_set_model( GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1) );
    g_object_unref( properties->GtkInfo.liststore1 );

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (option_algorithms[properties->modeltype].price, renderer, "text", X1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
  
    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    char textDate[400] = { 0 };

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*properties->expiration_month],*properties->days_to_expiration,(double)*properties->expiration_year + 2000);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+1)],*(properties->days_to_expiration+1),(double)*(properties->expiration_year+1) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+2)],*(properties->days_to_expiration+2),(double)*(properties->expiration_year+2) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+3)],*(properties->days_to_expiration+3),(double)*(properties->expiration_year+3) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+4)],*(properties->days_to_expiration+4),(double)*(properties->expiration_year+4) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+5)],*(properties->days_to_expiration+5),(double)*(properties->expiration_year+5) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+6)],*(properties->days_to_expiration+6),(double)*(properties->expiration_year+6) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(textDate,sizeof(textDate),"%s%2d %04.0f",mon[*(properties->expiration_month+7)],*(properties->days_to_expiration+7),(double)*(properties->expiration_year+7) + 2000 );
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (textDate, renderer, "text", X10, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

  } else if( properties->decimalorcalendar == CALENDAR && properties->spreads == 0 && ( properties->format == CALENDAR_OPTIONS4 || properties->format == CALENDAR_OPTIONS3 || properties->format == CALENDAR_CUSTOM ))
  {
    properties->GtkInfo.liststore1 = gtk_list_store_new( 17, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING , G_TYPE_STRING , G_TYPE_STRING , G_TYPE_STRING , G_TYPE_STRING );
    
    gtk_tree_view_set_model( GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1) );
    g_object_unref(properties->GtkInfo.liststore1 );

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (option_algorithms[properties->modeltype].price, renderer, "text", X1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Expr Date", renderer, "text", X2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
  
    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(call,sizeof(call),"%s",option_algorithms[properties->modeltype].call);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (call, renderer, "text", X4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    if(option_algorithms[properties->modeltype].supportPuts)
      snprintf(put,sizeof(put),"%s",option_algorithms[properties->modeltype].put);
    else
      put[0] = 0;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (put, renderer, "text", X5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Days to Expr", renderer, "text", X6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Years to Expr", renderer, "text", X7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Delta", renderer, "text", X8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Delta", renderer, "text", X9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Gamma", renderer, "text", X10, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Vega", renderer, "text", X11, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Theta", renderer, "text", X12, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Theta", renderer, "text", X13, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Call Rho", renderer, "text", X14, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Put Rho", renderer, "text", X15, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Legacy C", renderer, "text", X16, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Legacy P", renderer, "text", X17, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

  } else if( properties->decimalorcalendar == CALENDAR && properties->spreads == 1 && ( properties->format == CALENDAR_OPTIONS4 || properties->format == CALENDAR_OPTIONS3 || properties->format == CALENDAR_CUSTOM ))
  {
    g_print("Spreads for Options\n");

    properties->GtkInfo.liststore1 = gtk_list_store_new( 13, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

    gtk_tree_view_set_model( GTK_TREE_VIEW (properties->GtkInfo.treeview), GTK_TREE_MODEL (properties->GtkInfo.liststore1) );
    g_object_unref(properties->GtkInfo.liststore1 );

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (option_algorithms[properties->modeltype].price, renderer, "text", X1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Expr Date", renderer, "text", X2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(call,sizeof(call),"%s",option_algorithms[properties->modeltype].call);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (call, renderer, "text", X4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    if(option_algorithms[properties->modeltype].supportPuts)
      snprintf(put,sizeof(put),"%s",option_algorithms[properties->modeltype].put);
    else
      put[0] = 0;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (put, renderer, "text", X5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Expr Date", renderer, "text", X6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);
  
    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      snprintf(strike,sizeof(strike),"%s",option_algorithms[properties->modeltype].strike);
    } else
    {
      strike[0] = 0;
    }
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (strike, renderer, "text", X7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    snprintf(call,sizeof(call),"%s",option_algorithms[properties->modeltype].call);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (call, renderer, "text", X8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    if(option_algorithms[properties->modeltype].supportPuts)
      snprintf(put,sizeof(put),"%s",option_algorithms[properties->modeltype].put);
    else
      put[0] = 0;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           (put, renderer, "text", X9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Spread C-C", renderer, "text", X10, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Spread P-P", renderer, "text", X11, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Spread C-P", renderer, "text", X12, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes
                           ("Spread P-C", renderer, "text", X13, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW (properties->GtkInfo.treeview), column);

  }

} // void setup_tree_view(struct _properties *properties)
