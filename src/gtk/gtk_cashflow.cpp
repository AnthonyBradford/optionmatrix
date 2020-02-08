/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_cashflow.cpp of optionmatrix                                   */
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
#include <vector>

#include "gtk_main.h"

void InitPaint(struct _properties *properties)
{
  g_print("InitPaint()\n");

  GtkTreeIter iter;
  char amountText[400] = { 0 };
  char decimalTimeText[400] = { 0 };
  char actualTimeText[400] = { 0 };

  pthread_mutex_lock(&properties->data.mutexCashflow);

  std::vector<double>::iterator it;
  std::vector<double>::iterator it2;

  g_print("InitPaint(): data.generic_amounts->size() = %lu\n", properties->data.generic_amounts->size());
  g_print("InitPaint(): data.generic_times_adjusted->size() = %lu\n", properties->data.generic_times_adjusted->size());

  if( properties->data.generic_amounts->size() != properties->data.generic_times_adjusted->size() )
  {
    g_print("InitPaint(): Error: Size mismatch between amounts and times\n");
  }

  for( it  = properties->data.generic_amounts->begin(),
       it2 = properties->data.generic_times_adjusted->begin();
       it != properties->data.generic_amounts->end();  
       ++it, it2++)
  {
    snprintf(amountText,sizeof(amountText),"%.*f", properties->precision,*it);
    snprintf(decimalTimeText,sizeof(decimalTimeText),"%.15f", *it2);
    snprintf(actualTimeText,sizeof(actualTimeText),"%s", decimal_date_to_real_date(*it2) );

    if( option_algorithms[properties->modeltype].supportDividend == 3 ||
        option_algorithms[properties->modeltype].supportDividend == 5 ||
        option_algorithms[properties->modeltype].supportDividend == 6 )
    {
      gtk_tree_store_append(properties->GtkInfo.store, &iter, NULL);
      gtk_tree_store_set(properties->GtkInfo.store, &iter, X1, amountText, X2, decimalTimeText, X3, actualTimeText, -1);

    } else if ( option_algorithms[properties->modeltype].supportDividend == 4 )
    {
      gtk_tree_store_append(properties->GtkInfo.store, &iter, NULL);
      gtk_tree_store_set(properties->GtkInfo.store, &iter, X1, decimalTimeText, X2, actualTimeText, -1);

    } else
    {
      g_print("on_buttonDividends_clicked(): dividend format not understood\n");
    }

  }

  pthread_mutex_unlock(&properties->data.mutexCashflow);

  gtk_tree_view_set_model(GTK_TREE_VIEW (properties->GtkInfo.treeview2), GTK_TREE_MODEL (properties->GtkInfo.store));
  gtk_tree_view_expand_all(GTK_TREE_VIEW (properties->GtkInfo.treeview2));

  return;

} // void InitPaint(struct _properties *properties)

gboolean ListTimer(struct _properties *properties)
{
  g_print("ListTimer():\n");

  GtkTreeIter iter;
  char amountText[400] = { 0 };
  char decimalTimeText[400] = { 0 };
  char actualTimeText[400] = { 0 };

  GtkTreeModel *model;
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(properties->GtkInfo.treeview2));

  if( gtk_tree_model_get_iter_from_string(model,&iter,"0") )
  {
    //g_print("***********************************************************************************\n");

    pthread_mutex_lock(&properties->data.mutexCashflow);

    std::vector<double>::iterator it;
    std::vector<double>::iterator it2;

    if( properties->data.generic_amounts->size() != properties->data.generic_times_adjusted->size() )
    {
      g_print("ListTimer(): Error: Size mismatch between amounts and times\n");
    }

    for( it  = properties->data.generic_amounts->begin(),
         it2 = properties->data.generic_times_adjusted->begin();
         it != properties->data.generic_amounts->end();  
         ++it, it2++)
    {
      snprintf(amountText,sizeof(amountText),"%.*f", properties->precision,*it);
      snprintf(decimalTimeText,sizeof(decimalTimeText),"%.15f", *it2);
      snprintf(actualTimeText,sizeof(actualTimeText),"%s", decimal_date_to_real_date(*it2) );

      if( option_algorithms[properties->modeltype].supportDividend == 3 ||
          option_algorithms[properties->modeltype].supportDividend == 5 ||
          option_algorithms[properties->modeltype].supportDividend == 6  )
      {
        gtk_tree_store_set(properties->GtkInfo.store, &iter, X1, amountText, X2, decimalTimeText, X3, actualTimeText, -1);

      } else if ( option_algorithms[properties->modeltype].supportDividend == 4 )
      {
        gtk_tree_store_set(properties->GtkInfo.store, &iter, X1, decimalTimeText, X2, actualTimeText, -1);

      } else
      {
        g_print("on_buttonDividends_clicked(): dividend format not understood\n");
      }

      gtk_tree_model_iter_next(model, &iter);

    } // for(...)

    pthread_mutex_unlock(&properties->data.mutexCashflow);

    gtk_tree_view_set_model(GTK_TREE_VIEW (properties->GtkInfo.treeview2), GTK_TREE_MODEL (properties->GtkInfo.store));
    gtk_tree_view_expand_all(GTK_TREE_VIEW (properties->GtkInfo.treeview2));

  } else
  {
    g_print("No tree model iter\n");
  }

  return GTK_IS_DIALOG(properties->GtkInfo.dialog);

} // gboolean ListTimer(struct _properties *properties)

void AddToVector(struct _properties *properties)
{
  g_print("AddToVector()\n");

  GtkTreeModel *model;
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(properties->GtkInfo.treeview2));

  pthread_mutex_lock(&properties->data.mutexCashflow);

  properties->data.generic_amounts->erase( properties->data.generic_amounts->begin(), properties->data.generic_amounts->end() );
  properties->data.generic_times->erase( properties->data.generic_times->begin(), properties->data.generic_times->end() );
  properties->data.generic_times_adjusted->erase( properties->data.generic_times_adjusted->begin(), properties->data.generic_times_adjusted->end() );

  GtkTreeIter iter;

  if( gtk_tree_model_get_iter_from_string(model, &iter, "0") )
  {
    gchar *timeText;
    gchar *amountsText;
    
    double amount;
    double decimalTime;

    do
    {
      if( option_algorithms[properties->modeltype].supportDividend == 3 ||
          option_algorithms[properties->modeltype].supportDividend == 5 ||
          option_algorithms[properties->modeltype].supportDividend == 6 )
      {
        gtk_tree_model_get(model, &iter, X1, &amountsText, -1);
        gtk_tree_model_get(model, &iter, X2, &timeText, -1);

        if( sscanf(amountsText,"%lf", &amount) != 1 )
          g_print("AddToVector(): Error(1): sscanf does not equal 1 for amountText\n");

        if( sscanf(timeText,"%lf", &decimalTime) != 1 )
          g_print("AddToVector(): Error(2): sscanf does not equal 1 for timeText\n");

        g_print("amount = %lf, decimalTime = %lf\n", amount, decimalTime);

        properties->data.generic_amounts->push_back(amount);
        properties->data.generic_times->push_back(decimalTime);
        properties->data.generic_times_adjusted->push_back(decimalTime);

        time(&properties->starttime4);

        g_free(amountsText);
        g_free(timeText);

      } else if( option_algorithms[properties->modeltype].supportDividend == 4 )
      {
        gtk_tree_model_get(model, &iter, X1, &timeText, -1);

        if( sscanf(timeText,"%lf", &decimalTime) != 1 )
          g_print("AddToVector(): Error(3): sscanf does not equal 1 for timeText\n");

        g_print("AddToVector(): decimalTime = %lf\n", decimalTime);

        properties->data.generic_amounts->push_back(amount);
        properties->data.generic_times->push_back(decimalTime);
        properties->data.generic_times_adjusted->push_back(decimalTime);

        time(&properties->starttime4);

        g_free(timeText);

      } else
      {
        g_print("AddToVector(): dividend format not understood\n");
      }

    }  while(gtk_tree_model_iter_next (model, &iter));

  } // if( gtk_tree_model_get_iter_from_string(model, &iter, "0") )

  pthread_mutex_unlock(&properties->data.mutexCashflow);

} // void AddToVector(struct _properties *properties)

void on_buttonDividends_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_buttonDividends_clicked()\n");

  properties->data.generic_amounts = &properties->data.amounts;
  properties->data.generic_times = &properties->data.times;
  properties->data.generic_times_adjusted = &properties->data.times_adjusted;

  generic_process_button(properties);

} // void on_buttonDividends_clicked( GtkWidget *widget, struct _properties *properties )

void on_buttonCoupons_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_buttonCoupons_clicked()\n");

  properties->data.generic_amounts = &properties->data.coupon;
  properties->data.generic_times = &properties->data.coupon_times;
  properties->data.generic_times_adjusted = &properties->data.coupon_times_adjusted;

  generic_process_button(properties);

} // void on_buttonCoupons_clicked( GtkWidget *widget, struct _properties *properties )

void on_buttonPrincipal_clicked( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_buttonPrincipal_clicked()\n");

  properties->data.generic_amounts = &properties->data.principal;
  properties->data.generic_times = &properties->data.principal_times;
  properties->data.generic_times_adjusted = &properties->data.principal_times_adjusted;

  generic_process_button(properties);

} // void on_buttonPrincipal_clicked( GtkWidget *widget, struct _properties *properties )

void generic_process_button(struct _properties *properties )
{
  g_print("generic_process_button()\n");

  GtkWidget *scrolled_win, *vbox, *hbox, *add, *remove;
  GtkTreeSelection *selection;
  
  properties->GtkInfo.dialog = gtk_dialog_new();

  gtk_window_set_icon(GTK_WINDOW(properties->GtkInfo.dialog), create_pixbuf("images/2.png"));
  gtk_window_set_title(GTK_WINDOW (properties->GtkInfo.dialog), option_algorithms[properties->modeltype].dividend);
  gtk_container_set_border_width(GTK_CONTAINER (properties->GtkInfo.dialog), 10);

  // width, height
  gtk_widget_set_size_request(properties->GtkInfo.dialog, 420, 300);
  
  properties->GtkInfo.treeview2 = gtk_tree_view_new();  

  if( option_algorithms[properties->modeltype].supportDividend == 3 ||
      option_algorithms[properties->modeltype].supportDividend == 5 ||
      option_algorithms[properties->modeltype].supportDividend == 6 )
  {
    setup_tree_view3(properties->GtkInfo.treeview2);
    properties->GtkInfo.store = gtk_tree_store_new(X4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  }
  else if( option_algorithms[properties->modeltype].supportDividend == 4 )
  {
    setup_tree_view4(properties->GtkInfo.treeview2);
    properties->GtkInfo.store = gtk_tree_store_new(X3, G_TYPE_STRING, G_TYPE_STRING);
  }
  
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW (properties->GtkInfo.treeview2));
  gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
  
  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_win),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  add = gtk_button_new_from_stock(GTK_STOCK_ADD);
  remove = gtk_button_new_from_stock(GTK_STOCK_REMOVE);
#endif
#ifdef HAVE_LIBGTK_3
  add = gtk_button_new_with_label("Add");
  remove = gtk_button_new_with_label("Remove");
#endif
  
  if( option_algorithms[properties->modeltype].supportDividend == 3 ||
      option_algorithms[properties->modeltype].supportDividend == 5 ||
      option_algorithms[properties->modeltype].supportDividend == 6 )
  {
    g_signal_connect(G_OBJECT (add), "clicked", G_CALLBACK (add_cashflow3), properties);
  }
  else if( option_algorithms[properties->modeltype].supportDividend == 4 )
  {
    g_signal_connect(G_OBJECT (add), "clicked", G_CALLBACK (add_cashflow4), properties);
  }

  g_signal_connect(G_OBJECT (remove), "clicked", G_CALLBACK (remove_cashflows), properties);

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  hbox = gtk_hbox_new(FALSE, 5);
#endif
#ifdef HAVE_LIBGTK_3
  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
#endif

  gtk_box_pack_start(GTK_BOX (hbox), add, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX (hbox), remove, FALSE, TRUE, 0);

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  vbox = gtk_vbox_new(FALSE, 5);
#endif
#ifdef HAVE_LIBGTK_3
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
#endif

  gtk_box_pack_start(GTK_BOX (vbox), scrolled_win, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER (scrolled_win), properties->GtkInfo.treeview2);
  gtk_box_pack_start(GTK_BOX( gtk_dialog_get_content_area(GTK_DIALOG (properties->GtkInfo.dialog))), vbox, TRUE, TRUE, 0);
  gtk_widget_show_all(properties->GtkInfo.dialog);

  InitPaint(properties);

  if( properties->realTimeBleeding )
    properties->GtkInfo.gListTimer = g_timeout_add(1000, (GSourceFunc) ListTimer, (gpointer) properties);

  gtk_dialog_run(GTK_DIALOG (properties->GtkInfo.dialog));

  AddToVector(properties);

  gtk_widget_destroy (properties->GtkInfo.dialog);  

  gtk_tree_store_clear(properties->GtkInfo.store);
  g_object_unref(properties->GtkInfo.store);

  g_print("generic_process_button(): Fell through\n");

  if( properties->realTimeBleeding )
    g_source_remove(properties->GtkInfo.gListTimer);

} // void generic_process_button(struct _properties *properties )

void add_cashflow3(GtkButton *add, struct _properties *properties)
{
  g_print("add_cashflow3()\n");

  GtkWidget *dialog;
  GtkWidget *table, *spin, *spin2;
  GtkWidget *content_area;

  GtkTreeIter iter;
  GtkTreeModel *model;
  double t;
  int ret;

  gchar *timeText;

  double amount;
  double decimalTime;

  char amountText[400] = { 0 };
  char decimalTimeText[400] = { 0 };
  char actualTimeText[400] = { 0 };
  
#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  dialog = gtk_dialog_new_with_buttons("Add", NULL,
                                       GTK_DIALOG_MODAL,
                                       GTK_STOCK_ADD, GTK_RESPONSE_OK,
                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                       NULL);
#endif

#ifdef HAVE_LIBGTK_3
  dialog = gtk_dialog_new_with_buttons("Add", NULL,
                                       GTK_DIALOG_MODAL,
                                       "Add",
                                       GTK_RESPONSE_OK,
                                       "Cancel",
                                       GTK_RESPONSE_CANCEL,
                                       NULL);
#endif

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  gtk_window_set_icon(GTK_WINDOW(dialog), create_pixbuf("images/2.png"));

  spin = gtk_spin_button_new_with_range(-1000, 1000, 1);
  spin2 = gtk_spin_button_new_with_range(0, 200, 1);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0);

  gtk_spin_button_set_digits( GTK_SPIN_BUTTON(spin), 4 );
  gtk_spin_button_set_digits( GTK_SPIN_BUTTON(spin2), 4 );
  
#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  table = gtk_table_new(4, 2, FALSE);
  gtk_table_set_row_spacings( GTK_TABLE (table), 5 );
  gtk_table_set_col_spacings( GTK_TABLE (table), 5 );
  gtk_container_set_border_width( GTK_CONTAINER (table), 5 );

  gtk_table_attach( GTK_TABLE (table), gtk_label_new ("Amount:"), 0, 1, 0, 1, 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0 );

  gtk_table_attach( GTK_TABLE (table), spin, 1, 2, 0, 1,
                   (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0 );

  gtk_table_attach( GTK_TABLE (table), gtk_label_new ("Time:"), 0, 1, 2, 3, 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0 );

  gtk_table_attach( GTK_TABLE (table), spin2, 1, 2, 2, 3, 
                   (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0 );
#endif
#ifdef HAVE_LIBGTK_3
 
  table = gtk_grid_new();
  gtk_grid_set_row_spacing( GTK_GRID (table), 5 );
  gtk_grid_set_column_spacing( GTK_GRID (table), 5 );

  gtk_grid_attach( GTK_GRID (table), gtk_label_new ("Amount:"), 1, 0, 2, 1 );
  // spin for amount
  gtk_grid_attach( GTK_GRID (table), spin, 5, 0, 2, 1 );

  gtk_grid_attach( GTK_GRID (table), gtk_label_new ("Time:"), 1, 1, 2, 1 );
  // spin2 for time
  gtk_grid_attach( GTK_GRID (table), spin2, 5, 1, 2, 1 );

#endif

  gtk_container_add(GTK_CONTAINER (content_area), table);  
  gtk_widget_show_all(dialog);

  if( gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_OK )
  {
    amount = gtk_spin_button_get_value( GTK_SPIN_BUTTON (spin) );
    //g_print("amount = %f\n", amount);

    t = gtk_spin_button_get_value(GTK_SPIN_BUTTON (spin2));
    //g_print("t = %f\n", t);
    
    model = gtk_tree_view_get_model((GtkTreeView *)properties->GtkInfo.treeview2);
    ret = gtk_tree_model_get_iter_from_string(model, &iter, "0");
    //g_print("ret = %d\n", ret);

    gboolean found = 0;
    int counter = 0;

    if( ret )
    do
    {
      gtk_tree_model_get(model, &iter, X2, &timeText, -1);
      
      if( sscanf(timeText,"%lf", &decimalTime) != 1 )
        g_print("add_cashflow3(): Error: sscanf does not equal 1\n");

      //g_print("double t = %f\n", decimalTime);

      if( t > decimalTime )
      {
        counter++;
      }
      
      g_free(timeText);

    } while( gtk_tree_model_iter_next (model, &iter) );

    //g_print("counter = %d\n", counter);
    
    int counter2 = 0;

    ret = gtk_tree_model_get_iter_from_string(model, &iter, "0");
    //g_print("ret = %d\n", ret);
    
    if( ret )
    do
    {
      gtk_tree_model_get(model, &iter, X2, &timeText, -1);
      
      if( sscanf(timeText,"%lf", &decimalTime) != 1 )
        g_print("add_cashflow3(): Error: sscanf does not equal 1\n");

      //g_print("double t = %f\n", decimalTime);

      if( t > decimalTime )
      {
        //g_print("%d - %d\t\t%f > %f\n", counter2, counter, t, decimalTime);
        counter2++;
        
        if ( counter2 >= counter )
        {
          found = 1;
          g_free(timeText);
          //g_print("Insert here\n");
          break;
        }
      }
      
      g_free(timeText);

    } while(gtk_tree_model_iter_next (model, &iter));

    snprintf(amountText,sizeof(amountText),"%f", amount);
    snprintf(decimalTimeText,sizeof(decimalTimeText),"%.15f", t);
    snprintf(actualTimeText,sizeof(actualTimeText),"%s", decimal_date_to_real_date(t) );
  
    //g_print("found     = %d\t", found);
    //g_print("counter   = %d\t", counter);
    //g_print("counter2  = %d\n", counter2);
  
    if( !found && !counter )
    {
      //g_print("set first one\n");
      gtk_tree_store_prepend(GTK_TREE_STORE(model), &iter, NULL);
    } else
    {
      gtk_tree_store_insert_after(GTK_TREE_STORE(model), &iter, NULL, &iter);
    }
  
    gtk_tree_store_set( GTK_TREE_STORE(model), &iter, X1, amountText, X2, decimalTimeText, X3, actualTimeText, -1 );

  }

  gtk_widget_destroy(dialog);

  if( properties->realTimeBleeding )
    AddToVector(properties);

} // void add_cashflow3(GtkButton *add, struct _properties *properties)

void add_cashflow4(GtkButton *add, struct _properties *properties)
{
  g_print("add_cashflow4()\n");

  GtkWidget *dialog, *table, *spin2;
  GtkWidget *content_area;

  GtkTreeIter iter;
  GtkTreeModel *model;
  double t;
  int ret;

  gchar *timeText;

  double decimalTime;

  char decimalTimeText[400] = { 0 };
  char actualTimeText[400] = { 0 };

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  dialog = gtk_dialog_new_with_buttons("Add", NULL,
                                       GTK_DIALOG_MODAL,
                                       GTK_STOCK_ADD, GTK_RESPONSE_OK,
                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                       NULL);
#endif

#ifdef HAVE_LIBGTK_3
  dialog = gtk_dialog_new_with_buttons("Add", NULL,
                                       GTK_DIALOG_MODAL,
                                       "Add",
                                       GTK_RESPONSE_OK,
                                       "Cancel",
                                       GTK_RESPONSE_CANCEL,
                                       NULL);
#endif

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  spin2 = gtk_spin_button_new_with_range(0, 200, 1);
  gtk_spin_button_set_digits( GTK_SPIN_BUTTON (spin2), 4 );

#ifdef HAVE_LIBGTK_X11_2_0
  // DEPRECATED
  table = gtk_table_new(4, 2, FALSE);
  gtk_table_set_row_spacings( GTK_TABLE (table), 5 );
  gtk_table_set_col_spacings( GTK_TABLE (table), 5 );
  gtk_container_set_border_width( GTK_CONTAINER (table), 5 );

  gtk_table_attach(GTK_TABLE (table), gtk_label_new ("Time:"), 0, 1, 2, 3, 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0);

  gtk_table_attach(GTK_TABLE (table), spin2, 1, 2, 2, 3, 
                   (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 
                   (GtkAttachOptions) (GTK_SHRINK | GTK_FILL), 
                   0, 0);
#endif

#ifdef HAVE_LIBGTK_3

  table = gtk_grid_new();
  gtk_grid_set_row_spacing( GTK_GRID (table), 5 );
  gtk_grid_set_column_spacing( GTK_GRID (table), 5 );
  gtk_grid_attach( GTK_GRID (table), gtk_label_new ("Time:"), 1, 0, 2, 1 );
  // spin2 for time
  gtk_grid_attach( GTK_GRID (table), spin2, 5, 0, 2, 1 );

#endif

  gtk_container_add (GTK_CONTAINER (content_area), table);  
  gtk_widget_show_all(dialog);

  if( gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_OK )
  {
    t = gtk_spin_button_get_value( GTK_SPIN_BUTTON (spin2) );
    //g_print("t = %f\n", t);
    
    model = gtk_tree_view_get_model((GtkTreeView *)properties->GtkInfo.treeview2);
    ret = gtk_tree_model_get_iter_from_string(model, &iter, "0");
    //g_print("ret = %d\n", ret);

    gboolean found = 0;
    int counter = 0;

    if( ret )
    do
    {
      gtk_tree_model_get(model, &iter, X1, &timeText, -1);
      
      if( sscanf(timeText,"%lf", &decimalTime) != 1 )
        g_print("add_cashflow4(): error: sscanf does not equal 1\n");

      //g_print("double t = %f\n", decimalTime);

      if( t > decimalTime )
      {
        counter++;
      }
      
      g_free(timeText);

    } while(gtk_tree_model_iter_next (model, &iter));

    //g_print("counter = %d\n", counter);
    
    int counter2 = 0;

    ret = gtk_tree_model_get_iter_from_string(model, &iter, "0");
    //g_print("ret = %d\n", ret);
    
    if( ret )
    do
    {
      gtk_tree_model_get(model, &iter, X1, &timeText, -1);
      
      if( sscanf(timeText,"%lf", &decimalTime) != 1 )
        g_print("add_cashflow4(): Error: sscanf does not equal 1\n");

      //g_print("double t = %f\n", decimalTime);

      if( t > decimalTime )
      {
        //g_print("%d - %d\t\t%f > %f\n", counter2, counter, t, decimalTime);
        counter2++;
        
        if ( counter2 >= counter )
        {
          found = 1;
          g_free(timeText);
          //g_print("Insert here\n");
          break;
        }
      }
      
      g_free(timeText);

    } while(gtk_tree_model_iter_next (model, &iter));

    snprintf(decimalTimeText,sizeof(decimalTimeText),"%.15f", t);
    snprintf(actualTimeText,sizeof(actualTimeText),"%s", decimal_date_to_real_date(t) );
  
    //g_print("found     = %d\t", found);
    //g_print("counter   = %d\t", counter);
    //g_print("counter2  = %d\n", counter2);
  
    if( !found && !counter )
    {
      //g_print("set first one\n");
      gtk_tree_store_prepend(GTK_TREE_STORE(model), &iter, NULL);
    } else
    {
      gtk_tree_store_insert_after(GTK_TREE_STORE(model), &iter, NULL, &iter);
    }
  
    gtk_tree_store_set(GTK_TREE_STORE(model), &iter, X1, decimalTimeText, X2, actualTimeText, -1);
  }

  gtk_widget_destroy(dialog);

  if( properties->realTimeBleeding )
    AddToVector(properties);

} // void add_cashflow4(GtkButton *add, struct _properties *properties)

void remove_row(GtkTreeRowReference *ref, struct _properties *properties)
{
  g_print("remove_row()\n");

  GtkTreeIter iter;
  GtkTreePath *path;
  
  path = gtk_tree_row_reference_get_path(ref);
  gtk_tree_model_get_iter(properties->GtkInfo.model, &iter, path);

  gtk_tree_store_remove(GTK_TREE_STORE (properties->GtkInfo.model), &iter);    

} // void remove_row(GtkTreeRowReference *ref, struct _properties *properties)

void remove_cashflows(GtkButton *remove, struct _properties *properties)
{
  g_print("remove_cashflows()\n");

  g_source_remove(properties->GtkInfo.gListTimer);

  GtkTreeSelection *selection;
  GtkTreeRowReference *ref;
  GList *rows, *ptr, *references = NULL;
  
  selection = gtk_tree_view_get_selection((GtkTreeView *)properties->GtkInfo.treeview2);
  properties->GtkInfo.model = gtk_tree_view_get_model((GtkTreeView *)properties->GtkInfo.treeview2);
  rows = gtk_tree_selection_get_selected_rows(selection, &properties->GtkInfo.model);

  //g_print("remove_cashflows(): rows = %lf\n", rows);

  ptr = rows;
  while ( ptr != NULL )
  {
    ref = gtk_tree_row_reference_new(properties->GtkInfo.model, (GtkTreePath*) ptr->data);
    references = g_list_prepend(references, gtk_tree_row_reference_copy (ref));
    gtk_tree_row_reference_free(ref);
    ptr = ptr->next;
  }
  
  g_list_foreach(references, (GFunc) remove_row, properties);
  g_list_foreach(references, (GFunc) gtk_tree_row_reference_free, NULL);
  g_list_foreach(rows, (GFunc) gtk_tree_path_free, NULL);
  g_list_free(references);
  g_list_free(rows);

  if( properties->realTimeBleeding )
  {
    AddToVector(properties);
    properties->GtkInfo.gListTimer = g_timeout_add(1000, (GSourceFunc) ListTimer, (gpointer) properties);
  }

} // void remove_cashflows(GtkButton *remove, struct _properties *properties)

void setup_tree_view3(GtkWidget *treeview)
{
  g_print("setup_tree_view3()\n");

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes
                         ("Amount", renderer, "text", X1, NULL);
  gtk_tree_view_append_column( GTK_TREE_VIEW (treeview), column );
  
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes
       ("Decimal Time", renderer, "text", X2, NULL);
  gtk_tree_view_append_column( GTK_TREE_VIEW (treeview), column );
  
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes
                         ("Actual Date", renderer, "text", X3, NULL);
  gtk_tree_view_append_column( GTK_TREE_VIEW (treeview), column );

} // void setup_tree_view3(GtkWidget *treeview)

void setup_tree_view4(GtkWidget *treeview)
{
  g_print("setup_tree_view4()\n");

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes
       ("Decimal Time", renderer, "text", X1, NULL);
  gtk_tree_view_append_column( GTK_TREE_VIEW (treeview), column );
  
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes
                         ("Actual Date", renderer, "text", X2, NULL);
  gtk_tree_view_append_column( GTK_TREE_VIEW (treeview), column );

} // void setup_tree_view4(GtkWidget *treeview)
