/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_combobox.cpp of optionmatrix                                   */
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

#include <map>
#include <algorithm>
#include <string>
#include <gtk/gtk.h>

#include "gtk_main.h"

typedef int (*compfn)(const void*, const void*);

static int cmpstringp(struct elementListWithGroup *pp1, struct elementListWithGroup *pp2)
{
  int ret = strcmp(pp1->groupName,pp2->groupName);

  // if same groupName sort by elementName
  if( ret == 0 )
    return strcmp(pp1->elementName,pp2->elementName);

  return ret;

} // static int cmpstringp(struct elementListWithGroup *pp1, struct elementListWithGroup *pp2)

char *recurse(char *parse, GtkTreeStore *store, GtkTreeIter *iter, char *text, char *text2)
{
  GtkTreeIter child;
  GtkTreeIter past2;
  static char pathString[1000];

  int ret = 0;
  char first[1000] = { 0 };

  GtkTreePath *path = 0;
  pathString[0] = 0;

  ret = sscanf(parse,"%[^;]", &first[0]);

  if( ret == 1  )
  {
    //g_print("recurse first = %s\n", first);
    //g_print("gtk_tree_model_iter_n_children() = %d\n", gtk_tree_model_iter_n_children(GTK_TREE_MODEL(store),iter));

    GtkTreeIter it;
    bool found = false;
    int index = 0;
    for(index = 0; index < gtk_tree_model_iter_n_children(GTK_TREE_MODEL(store),iter); index++)
    {
      gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(store),&it,iter,index);
      gtk_tree_model_get(GTK_TREE_MODEL(store), &it, 0, &text, -1);
      //g_print("text = %s\n", text);

      if( strcmp(text,first) == 0 )
      {
        //g_print("Match for %s\n", text);
        found = true;
        break;
      }

    } // for(index = 0; index < gtk_tree_model_iter_n_children(GTK_TREE_MODEL(store),iter); index++)

    if( found == false )
    {
      //g_print("found false\n");

      gtk_tree_store_append(store, &child, iter);
      gtk_tree_store_set(store, &child, 0, first, -1);

      if( strlen(parse) > strnlen(first,sizeof(first)) )
      {
        recurse(parse+strnlen(first,sizeof(first))+1,store,&child,text,text2);
      }
      else
      {
        g_print("text2 = %s\n", text2);

        gtk_tree_store_append(store, &past2, &child);
        gtk_tree_store_set(store, &past2, 0, text2, -1);

        path = gtk_tree_model_get_path(GTK_TREE_MODEL(store),&past2);

        if( path )
        {
          //g_print("gtk_tree_path_to_string() = %s\n",gtk_tree_path_to_string(gtk_tree_model_get_path(GTK_TREE_MODEL(store),&past2)));
          gchar * pathToString = gtk_tree_path_to_string(path);
          strncpy(pathString,pathToString,sizeof(pathString));
          g_free(pathToString);
          gtk_tree_path_free(path);
          path = 0;

        } else
        {
          g_print("Path failed for %s\n", text2);
        }

      }
    } // if( found == false )
    else if( found == true )
    {
      //g_print("found true\n");

      if( strlen(parse) > strnlen(first,sizeof(first)) )
      {
        recurse(parse+strnlen(first,sizeof(first))+1,store,&it,text,text2);
      }
      else
      {
        g_print("text2 = %s\n", text2);

        gtk_tree_store_append(store, &past2, &it);
        gtk_tree_store_set(store, &past2, 0, text2, -1);
      }
    }

  } // if( ret == 1  )

  if( !pathString[0] )
  {

    path = gtk_tree_model_get_path(GTK_TREE_MODEL(store),&past2);

    if( path )
    {
      //g_print("gtk_tree_path_to_string() = %s\n",gtk_tree_path_to_string(gtk_tree_model_get_path(GTK_TREE_MODEL(store),&past2)));
      gchar * pathToString = gtk_tree_path_to_string(path);
      strncpy(pathString,pathToString,sizeof(pathString));
      g_free(pathToString);
      gtk_tree_path_free(path);

    } else
    {
      g_print("Path failed for %s\n", text2);
    }

  } // if( !pathString[0] )

  return &pathString[0];

} // char *recurse(char *parse, GtkTreeStore *store, GtkTreeIter *iter, char *text, char *text2)

static void is_model_sensitive(GtkCellLayout *cell_layout, GtkCellRenderer *cell, GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
  gboolean sensitive;

  sensitive = !gtk_tree_model_iter_has_child (tree_model, iter);

  g_object_set(cell, "sensitive", sensitive, NULL);

} // static void is_model_sensitive()

void set_up_combobox_with_array_use_groups(GtkWidget *combo, struct elementListWithGroup *array, const size_t number, treeToIndex& TreeToIndex, const int sort)
{
  g_print("set_up_combobox_with_array_use_groups()\n");

  static GtkTreeStore *store;
  static GtkTreeStore *destroy_store;
  static GtkCellRenderer *renderer;
  char text[1000] = { 0 };

  if( store )
  {
    destroy_store = (GtkTreeStore *) store;
  }

  store = gtk_tree_store_new(1, G_TYPE_STRING);

  TreeToIndex.erase( TreeToIndex.begin(), TreeToIndex.end() );

  //g_print("number = %d, sizeof = %d\n", number, sizeof(elementListWithGroup));

  qsort(array, number, sizeof(elementListWithGroup), (compfn)cmpstringp);

  char *t;
  char first[1000] = { 0 };
  char temp[1000] = { 0 };
  char *p;
  char dummy;

  guint i;
  for (i = 0; i < number; i++)
  {
    sscanf(array[i].groupName,"%[^;]",first);

    if( sort )
    {
      if( sscanf(first,"%c", &dummy) )
      {
        //g_print("groupName = %s\n", array[i].groupName);
        p = &(array[i].groupName[0]);
        p += strnlen(first,sizeof(first))+1;
        strncpy(temp,&p[0],sizeof(temp));
        strncpy(array[i].groupName,temp,sizeof(array[i].groupName));

        //g_print("array[i].groupName = %s\n",array[i].groupName);

      } else
      {
        g_print("set_up_combobox_with_array_use_groups() ERROR: Format needs sort order\n");
      }

    } // if( sort )

    //g_print("groupName = %s\n", array[i].groupName);
    t = recurse(array[i].groupName, store, 0, text, array[i].elementName);

    if( t )
    {
      //g_print("t = %s for %s\n", t, array[i].elementName);
      TreeToIndex[t] = array[i].index;
    } else
    {
      g_print("ERROR: No path for %s\n", array[i].elementName);
    }

  } // for (i = 0; i < number; i++)

  //g_print("TreeToIndex.size() = %d\n", TreeToIndex.size());

  // Causes warning:
  // Gtk-CRITICAL **: gtk_tree_view_append_column: assertion `GTK_IS_TREE_VIEW (tree_view)' failed
  gtk_combo_box_set_model( GTK_COMBO_BOX(combo), GTK_TREE_MODEL(store) );

  renderer = gtk_cell_renderer_text_new();

  gtk_cell_layout_clear(GTK_CELL_LAYOUT(combo));
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);

  gtk_cell_layout_set_cell_data_func(GTK_CELL_LAYOUT (combo),
                                        renderer,
                                        is_model_sensitive,
                                        NULL, NULL);

  GtkTreeIter iter;
  GtkTreePath *path;
  path = gtk_tree_path_new_from_indices(0, 0, -1);
  gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, path);
  gtk_combo_box_set_active_iter(GTK_COMBO_BOX (combo), &iter);
  gtk_tree_path_free(path);

  if( destroy_store )
  {
    g_print("Executing: gtk_tree_store_clear(destroy_store)\n");
    gtk_tree_store_clear(GTK_TREE_STORE(destroy_store));
    g_object_unref( G_OBJECT(destroy_store) );
    destroy_store = 0;
  }

} // void set_up_combobox_with_array_use_groups()

void set_up_combobox_with_array(GtkWidget *combo, const struct elementList *array, const size_t number)
{
  static GtkListStore *store;
  static GtkListStore *destroy_store;
  static GtkCellRenderer *renderer;
  char text[1000] = { 0 };

  if( store )
  {
    destroy_store = (GtkListStore *) store;
  }

  store = gtk_list_store_new(1, G_TYPE_STRING);

  GtkTreeIter iter;
  guint i;
  for (i = 0; i < number; i++)
  {
    gtk_list_store_append(store, &iter);
    snprintf(text,sizeof(text),"%s",array[i].elementName);
    gtk_list_store_set (store, &iter, 0, text, -1);
  }

  // Causes warning:
  // Gtk-CRITICAL **: gtk_tree_view_append_column: assertion `GTK_IS_TREE_VIEW (tree_view)' failed
  gtk_combo_box_set_model( GTK_COMBO_BOX(combo), GTK_TREE_MODEL(store) );
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

  renderer = gtk_cell_renderer_text_new();

  gtk_cell_layout_clear(GTK_CELL_LAYOUT (combo));
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer, "text", 0, NULL);

  if( destroy_store )
  {
    g_print("Executing: gtk_list_store_clear(destroy)\n");
    gtk_list_store_clear( GTK_LIST_STORE(destroy_store) );
    g_object_unref( G_OBJECT(destroy_store) );
    destroy_store = 0;
  }

} // void set_up_combobox_with_array(GtkWidget *combo, const struct elementList *array, const size_t number)

void set_up_combobox_with_array2(GtkWidget *combo, const struct elementList *array, const size_t number)
{
  static GtkListStore *store;
  static GtkCellRenderer *renderer;
  char text[1000] = { 0 };

  store = gtk_list_store_new(1, G_TYPE_STRING);

  GtkTreeIter iter;
  guint i;
  for (i = 0; i < number; i++)
  {
    gtk_list_store_append(store, &iter);
    snprintf(text,sizeof(text),"%s",array[i].elementName);
    gtk_list_store_set (store, &iter, 0, text, -1);
  }

  // Causes warning:
  // Gtk-CRITICAL **: gtk_tree_view_append_column: assertion `GTK_IS_TREE_VIEW (tree_view)' failed
  gtk_combo_box_set_model( GTK_COMBO_BOX(combo), GTK_TREE_MODEL(store) );
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

  renderer = gtk_cell_renderer_text_new();

  gtk_cell_layout_clear(GTK_CELL_LAYOUT (combo));
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer, "text", 0, NULL);

  g_object_unref( G_OBJECT(store) );

} // void set_up_combobox_with_array2(GtkWidget *combo, const struct elementList *array, const size_t number)

void on_comboboxWeekday_changed(GtkComboBox *combo, const struct _properties *properties)
{
  g_print("on_comboboxWeekday_changed()\n");
  
  int value = gtk_combo_box_get_active(combo);
  if( properties->occurence_day != value )
  {
    //g_print("gtk_combo_box_get_active(combo) = %d\n",value);

    const char *const weekDays[]= { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    struct elementList listOccurance[4];
    int index;
    for( index = 0; index < 4; index++ )
    {
      snprintf(listOccurance[index].elementName,sizeof(listOccurance[index].elementName),"%d%s %s", index+1, order[index], weekDays[value] );
      //g_print("%s\n",listOccurance[index].elementName);
    }
    set_up_combobox_with_array2(properties->GtkInfo.comboboxOccurance, listOccurance, sizeof(listOccurance) / sizeof(listOccurance[0]));
  }

} // void on_comboboxWeekday_changed(GtkComboBox *combo, const struct _properties *properties)

void on_comboboxOccurance_changed(GtkComboBox *combo, const struct _properties *properties)
{
  g_print("on_comboboxOccurance_changed()\n");
  
  int value = gtk_combo_box_get_active(combo);
  //g_print("occurence change to %d\n",value);

  if( value >= 3 )
  {
    //g_print("resetting dayoffset to 0\n");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDayOffset),0);
    gtk_widget_hide(properties->GtkInfo.labelDayOffset);
    gtk_widget_hide(properties->GtkInfo.spinbuttonDayOffset);
  } else
  {
    gtk_widget_show(properties->GtkInfo.labelDayOffset);
    gtk_widget_show(properties->GtkInfo.spinbuttonDayOffset);
  }
  //g_print("comboboxOCC PropButton properties->occurence_plus_offset = %d\n",properties->occurence_plus_offset);
  //g_print("comboboxOcc PropButton properties->occurence_day = %d\n",properties->occurence_day);
  //g_print("comboboxOcc PropButton properties->occurence_in_month-1 = %d\n",properties->occurence_in_month-1);

} // void on_comboboxOccurance_changed(GtkComboBox *combo, const struct _properties *properties)

void on_comboboxStrikes_changed(GtkComboBox *combo, struct _properties *properties)
{
  g_print("on_comboboxStrikes_changed()\n");
  properties->strikestoogle = gtk_combo_box_get_active(combo);

  properties->strike_offset = (int) properties->strike_offset;
  properties->strike_offset2 = (int) properties->strike_offset2;

  calc_strike_scale(properties);

  // custom strikes...
  if( strike_control[properties->strikestoogle].incrementor == 0 )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"Strike");
    gtk_widget_show(properties->GtkInfo.labelStrikes2);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes);

    if( properties->spreads == 1 &&
      ( properties->format != CALENDAR_OPTIONS5 && properties->format != CALENDAR_OPTIONS6 ) )
    {
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"StrikeLeg1");
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
      gtk_widget_show(properties->GtkInfo.labelStrikes2);

      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike);
      gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
      gtk_widget_show(properties->GtkInfo.spinbuttonCustomStrike2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes2);
     }

  }
  else
  {
    gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes2),"StrikeLeg2");
    gtk_widget_hide(properties->GtkInfo.labelStrikes2);
    gtk_widget_show(properties->GtkInfo.scaleStrikes);
  }

} // void on_comboboxStrikes_changed(GtkComboBox *combo, struct _properties *properties)

void on_comboboxModel_changed_show(int modeltype, struct _properties *properties)
{
  g_print("on_comboboxModel_changed_show()\n");

  char t1Des[1000] = { 0 };
  snprintf(t1Des,sizeof(t1Des),"Time to %s", option_algorithms[modeltype].supportTime1des);
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.label1), t1Des);
  snprintf(t1Des,sizeof(t1Des),"Days to %s", option_algorithms[modeltype].supportTime1des);
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDaysToExpr), t1Des);

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStrikes),"Strikes");

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDividend), option_algorithms[modeltype].dividend);
  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelPrice), option_algorithms[properties->modeltype].price);

  if( option_algorithms[modeltype].supportTime2 && !option_algorithms[modeltype].perpetual )
  {
    char des[1000] = { 0 };
    snprintf(des,sizeof(des),"Time to %s",option_algorithms[modeltype].supportTime2des);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.label2),des);
    gtk_widget_show(properties->GtkInfo.label2);

    snprintf(des,sizeof(des),"Days to %s",option_algorithms[modeltype].supportTime2des);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDaysToDividend),des);
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend);

    //g_print("label2 show 2\n");
  } else
  {
    //gtk_widget_hide(properties->GtkInfo.label2);
    //g_print("label2 hide\n");
  }

  if( option_algorithms[modeltype].supportStrikes )
  {
    gtk_widget_show(properties->GtkInfo.labelStrikes);
  }

  if( option_algorithms[modeltype].supportCND )
  {
    g_print("supportCND\n");

    if( integration_method[properties->integration_type].method )
    {
      properties->integration_type = 0;
      gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxCND), 0);
    }

    gtk_widget_show(properties->GtkInfo.labelCND);
    gtk_widget_show(properties->GtkInfo.comboboxCND);

  }

  if( option_algorithms[properties->modeltype].supportTime3 )
  {
    char des[1000] = { 0 };
    snprintf(des,sizeof(des),"Time to %s",option_algorithms[properties->modeltype].supportTime3des);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.label3),des);
    gtk_widget_show(properties->GtkInfo.label3);

    snprintf(des,sizeof(des),"Days to %s",option_algorithms[properties->modeltype].supportTime3des);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelDaysToDividend2),des);
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend2);

    //g_print("label3 show 2\n");
  }

  if( option_algorithms[modeltype].supportPrice )
  {
    gtk_widget_show(properties->GtkInfo.labelPrice);
    gtk_widget_show(properties->GtkInfo.spinbuttonPrice);
  }

  if( option_algorithms[modeltype].supportRate )
  {
    gtk_widget_show(properties->GtkInfo.labelRate);
    gtk_widget_show(properties->GtkInfo.spinbuttonRate);
  }

  if( option_algorithms[modeltype].supportDividend == 2 )
  {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDividend),option_algorithms[modeltype].defaultDividend);
  }

  if( option_algorithms[modeltype].supportDividend == 1 || option_algorithms[modeltype].supportDividend == 2 )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonDividend);
    gtk_widget_show(properties->GtkInfo.labelDividend);
  } else
  {
    gtk_spin_button_set_value( GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDividend), 0.0 );
    gtk_widget_hide(properties->GtkInfo.spinbuttonDividend);
    gtk_widget_hide(properties->GtkInfo.labelDividend);
  }

  if( option_algorithms[modeltype].supportDividend == 3 || option_algorithms[modeltype].supportDividend == 4 )
  {
    gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.buttonDividends),option_algorithms[modeltype].dividend);
    gtk_widget_show(properties->GtkInfo.buttonDividends);

  } else
  {
    gtk_widget_hide(properties->GtkInfo.buttonDividends);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  if( option_algorithms[modeltype].iUseZ )
  {
    //g_print("UseZ\n");
    //g_print("%f\n",option_algorithms[modeltype].Zdefault);
    //g_print("%d\n",((option_algorithms[modeltype].bZallow0Negative == 1) ? -100 : 1));

    //g_print("%f\n",((option_algorithms[modeltype].Zmax == 0) ? 1000 : option_algorithms[modeltype].Zmax));
    //g_print("%f\n",((option_algorithms[modeltype].iUseZ == 2) ? 1 : .01));
    //g_print("%f\n",((option_algorithms[modeltype].iUseZ == 2) ? 2 : .1));
    //(option_algorithms[modeltype].iUseZ == 1 ? 1 : (double) 0.0001)
    properties->GtkInfo.spin_z = GTK_ADJUSTMENT (gtk_adjustment_new(option_algorithms[modeltype].Zdefault, 
                            ((option_algorithms[modeltype].bZallow0Negative == 1) ? -100 : .0001),
                            //((option_algorithms[modeltype].bZallow0Negative == 1) ? -100 : (option_algorithms[modeltype].iUseZ == 1 ? 1 : (double) 0.0001)),
                            ((option_algorithms[modeltype].Zmax == 0) ? 99999 : option_algorithms[modeltype].Zmax),
                            ((option_algorithms[modeltype].iUseZ == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseZ == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseZ),properties->GtkInfo.spin_z);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseZ),option_algorithms[modeltype].Zdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseZ);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseZ),option_algorithms[modeltype].UseZdes);
    gtk_widget_show(properties->GtkInfo.labelUseZ);
    properties->data.UseZ = option_algorithms[modeltype].Zdefault;

    if( option_algorithms[modeltype].iUseZ == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseZ), NULL, 1, 0);
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  if( option_algorithms[modeltype].iUseB )
  {
    //g_print("UseB\n");
    //g_print("option_algorithms[modeltype].Bdefault = %f\n",option_algorithms[modeltype].Bdefault);
    //g_print("((option_algorithms[modeltype].bBallow0Negative == 1) ? -100 : .0001) = %f\n",((option_algorithms[modeltype].bBallow0Negative == 1) ? -100 : .0001));
    //g_print("((option_algorithms[modeltype].Bmax == 0) ? 1000 : option_algorithms[modeltype].Bmax) = %f\n",((option_algorithms[modeltype].Bmax == 0) ? 1000 : option_algorithms[modeltype].Bmax));

    //(option_algorithms[modeltype].iUseB == 1 ? 1 : (double) 0.0001)
    properties->GtkInfo.spin_b = GTK_ADJUSTMENT (gtk_adjustment_new(option_algorithms[modeltype].Bdefault, 
                            ((option_algorithms[modeltype].bBallow0Negative == 1) ? -100 : .0001),
                            //(option_algorithms[modeltype].iUseB == 1 ? 1 : (double) 0.0001),
                            ((option_algorithms[modeltype].Bmax == 0) ? 99999 : option_algorithms[modeltype].Bmax),
                            ((option_algorithms[modeltype].iUseB == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseB == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseB),properties->GtkInfo.spin_b);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseB),option_algorithms[modeltype].Bdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseB);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseB),option_algorithms[modeltype].UseBdes);
    gtk_widget_show(properties->GtkInfo.labelUseB);
    properties->data.UseB = option_algorithms[modeltype].Bdefault;

    if( option_algorithms[modeltype].iUseB == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseB), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  if( option_algorithms[modeltype].iUseJ )
  {
    //g_print("UseJ\n");
    //g_print("%f\n",option_algorithms[modeltype].Jdefault);

    properties->GtkInfo.spin_j = GTK_ADJUSTMENT (gtk_adjustment_new(option_algorithms[modeltype].Jdefault, 
                            ((option_algorithms[modeltype].bJallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Jmax == 0) ? 99999 : option_algorithms[modeltype].Jmax),
                            ((option_algorithms[modeltype].iUseJ == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseJ == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseJ),properties->GtkInfo.spin_j);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseJ),option_algorithms[modeltype].Jdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseJ);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseJ),option_algorithms[modeltype].UseJdes);
    gtk_widget_show(properties->GtkInfo.labelUseJ);
    properties->data.UseJ = option_algorithms[modeltype].Jdefault;

    if( option_algorithms[modeltype].iUseJ == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseJ), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  
  if( option_algorithms[modeltype].iUseP )
  {
    //g_print("UseP\n");
    //g_print("%f\n",option_algorithms[modeltype].Pdefault);

    properties->GtkInfo.spin_p = GTK_ADJUSTMENT (gtk_adjustment_new( option_algorithms[modeltype].Pdefault, 
                            ((option_algorithms[modeltype].bPallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Pmax == 0) ? 99999 : option_algorithms[modeltype].Pmax),
                            ((option_algorithms[modeltype].iUseP == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseP == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseP),properties->GtkInfo.spin_p);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseP),option_algorithms[modeltype].Pdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseP);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseP),option_algorithms[modeltype].UsePdes);
    gtk_widget_show(properties->GtkInfo.labelUseP);
    properties->data.UseP = option_algorithms[modeltype].Pdefault;

    if( option_algorithms[modeltype].iUseP == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseP), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  
  if( option_algorithms[modeltype].iUseQ )
  {
    //g_print("UseQ\n");
    //g_print("%f\n",option_algorithms[modeltype].Qdefault);

    properties->GtkInfo.spin_q = GTK_ADJUSTMENT (gtk_adjustment_new( option_algorithms[modeltype].Qdefault, 
                            ((option_algorithms[modeltype].bQallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Qmax == 0) ? 99999 : option_algorithms[modeltype].Qmax),
                            ((option_algorithms[modeltype].iUseQ == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseQ == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseQ),properties->GtkInfo.spin_q);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseQ),option_algorithms[modeltype].Qdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseQ);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseQ),option_algorithms[modeltype].UseQdes);
    gtk_widget_show(properties->GtkInfo.labelUseQ);
    properties->data.UseQ = option_algorithms[modeltype].Qdefault;

    if( option_algorithms[modeltype].iUseQ == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseQ), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  
  if( option_algorithms[modeltype].iUseR )
  {
    //g_print("UseR\n");
    //g_print("%f\n",option_algorithms[modeltype].Rdefault);

    properties->GtkInfo.spin_r = GTK_ADJUSTMENT (gtk_adjustment_new( option_algorithms[modeltype].Rdefault, 
                            ((option_algorithms[modeltype].bRallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Rmax == 0) ? 99999 : option_algorithms[modeltype].Rmax),
                            ((option_algorithms[modeltype].iUseR == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseR == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseR),properties->GtkInfo.spin_r);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseR),option_algorithms[modeltype].Rdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseR);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseR),option_algorithms[modeltype].UseRdes);
    gtk_widget_show(properties->GtkInfo.labelUseR);
    properties->data.UseR = option_algorithms[modeltype].Rdefault;

    if( option_algorithms[modeltype].iUseR == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseR), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  if( option_algorithms[modeltype].iUseS )
  {
    //g_print("UseS\n");
    //g_print("%f\n",option_algorithms[modeltype].Sdefault);

    properties->GtkInfo.spin_s = GTK_ADJUSTMENT (gtk_adjustment_new( option_algorithms[modeltype].Sdefault, 
                            ((option_algorithms[modeltype].bSallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Pmax == 0) ? 99999 : option_algorithms[modeltype].Smax),
                            ((option_algorithms[modeltype].iUseS == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseS == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseS),properties->GtkInfo.spin_s);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseS),option_algorithms[modeltype].Sdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseS);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseS),option_algorithms[modeltype].UseSdes);
    gtk_widget_show(properties->GtkInfo.labelUseS);
    properties->data.UseS = option_algorithms[modeltype].Sdefault;

    if( option_algorithms[modeltype].iUseS == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseS), NULL, 1, 0);
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  if( option_algorithms[modeltype].iUseT )
  {
    //g_print("UseT\n");
    //g_print("%f\n",option_algorithms[modeltype].Tdefault);

    properties->GtkInfo.spin_t = GTK_ADJUSTMENT (gtk_adjustment_new( option_algorithms[modeltype].Tdefault, 
                            ((option_algorithms[modeltype].bTallow0Negative == 1) ? -100 : .0001),
                            ((option_algorithms[modeltype].Tmax == 0) ? 99999 : option_algorithms[modeltype].Tmax),
                            ((option_algorithms[modeltype].iUseT == 2) ? 1 : .01), 
                            ((option_algorithms[modeltype].iUseT == 2) ? 2 : .1),
                            0));

    gtk_spin_button_set_adjustment(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseT),properties->GtkInfo.spin_t);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseT),option_algorithms[modeltype].Tdefault);
    gtk_widget_show(properties->GtkInfo.spinbuttonUseT);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelUseT),option_algorithms[modeltype].UseTdes);
    gtk_widget_show(properties->GtkInfo.labelUseT);
    properties->data.UseT = option_algorithms[modeltype].Tdefault;
    
    if( option_algorithms[modeltype].iUseT == 2 )
    {
      g_print("Should be set to (int)\n");
      gtk_spin_button_configure(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonUseT), NULL, 1, 0);
    }
  }

  if( option_algorithms[modeltype].supportTime2 &&
      option_algorithms[modeltype].perpetual == 0 )
  {
    gtk_widget_show(properties->GtkInfo.spinbuttonTime2);
    gtk_widget_show(properties->GtkInfo.spinbuttonDaysToDividend);
    gtk_widget_show(properties->GtkInfo.labelTime2);
    gtk_widget_show(properties->GtkInfo.buttonCalendar2);
    gtk_widget_show(properties->GtkInfo.labelDaysToDividend);
    //g_print("show spinbuttonTime2, labelTime2\n");
  }

  if( option_algorithms[properties->modeltype].assetClass == BOND_CLASS )
  {
    gtk_widget_show(properties->GtkInfo.checkbuttonRealTime);
  }

  if( option_algorithms[modeltype].supportRealTime )
  {
    gtk_widget_show(properties->GtkInfo.checkbuttonRealTime);
  }

} // void on_comboboxModel_changed_show(int modeltype, struct _properties *properties)

void on_comboboxModel_changed_hide(int modeltype, struct _properties *properties)
{
  g_print("on_comboboxModel_changed_hide()\n");

  properties->strikestoogle = 0;
  gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxStrikes), 0);

  gtk_widget_hide(properties->GtkInfo.label2);
  gtk_widget_hide(properties->GtkInfo.labelInfo);
  gtk_widget_hide(properties->GtkInfo.labelStrikes2);
  gtk_widget_hide(properties->GtkInfo.scaleStrikes2);
  gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike);
  gtk_widget_hide(properties->GtkInfo.spinbuttonCustomStrike2);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseZ);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseB);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseJ);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseP);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseQ);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseR);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseS);
  gtk_widget_hide(properties->GtkInfo.spinbuttonUseT);
  gtk_widget_hide(properties->GtkInfo.labelUseZ);
  gtk_widget_hide(properties->GtkInfo.labelUseB);
  gtk_widget_hide(properties->GtkInfo.labelUseJ);
  gtk_widget_hide(properties->GtkInfo.labelUseP);
  gtk_widget_hide(properties->GtkInfo.labelUseQ);
  gtk_widget_hide(properties->GtkInfo.labelUseR);
  gtk_widget_hide(properties->GtkInfo.labelUseS);
  gtk_widget_hide(properties->GtkInfo.labelUseT);

  if( option_algorithms[properties->modeltype].supportDividend != 5 &&
      option_algorithms[properties->modeltype].supportDividend != 6 )
  {
    gtk_widget_hide(properties->GtkInfo.buttonCoupons);
  }

  if( option_algorithms[properties->modeltype].supportDividend != 6 )
  {
     gtk_widget_hide(properties->GtkInfo.buttonPrincipal);
  }

  if( !option_algorithms[modeltype].supportPrice )
  {
    gtk_widget_hide(properties->GtkInfo.labelPrice);
    gtk_widget_hide(properties->GtkInfo.spinbuttonPrice);
  }

  if( !option_algorithms[properties->modeltype].supportTime3 )
  {
    gtk_widget_hide(properties->GtkInfo.label3);
    //g_print("label3 hide\n");
  }

  if( !option_algorithms[modeltype].supportCND )
  {
    g_print("!supportCND\n");

    gtk_widget_hide(properties->GtkInfo.labelCND);
    gtk_widget_hide(properties->GtkInfo.comboboxCND);
  }

  // model does not support calendar dating engine...
  if( option_algorithms[modeltype].supportTime2 == 1 )
  {
    //g_print("Model does not support calendar dating engine\n");
    properties->format = DECIMAL_GREEKS;
    properties->decimalorcalendar = DECIMALS;
    setup_tree_view(properties);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonDateEngine),0);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);
    gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);
  }

  if( option_algorithms[modeltype].perpetual )
  {
    //g_print("perpetual setting to DECIMAL_GREEK and DECIMALS\n");
    properties->format = DECIMAL_GREEKS;
    properties->decimalorcalendar = DECIMALS;
    gtk_widget_hide(properties->GtkInfo.labelCND);
    gtk_widget_hide(properties->GtkInfo.comboboxCND);

    gtk_widget_hide(properties->GtkInfo.radiobutton1);
    gtk_widget_hide(properties->GtkInfo.radiobutton2);
    gtk_widget_hide(properties->GtkInfo.radiobutton3);
    gtk_widget_hide(properties->GtkInfo.radiobutton4);
    gtk_widget_hide(properties->GtkInfo.radiobutton5);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats);
    gtk_widget_hide(properties->GtkInfo.labelDisplayFormats2);

    setup_tree_view(properties);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonDateEngine),0);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);
    gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);

  } // if( option_algorithms[modeltype].perpetual )

  if( !option_algorithms[modeltype].supportRate )
  {
    gtk_widget_hide(properties->GtkInfo.labelRate);
    gtk_widget_hide(properties->GtkInfo.spinbuttonRate);
  }

  if( properties->decimalorcalendar == CALENDAR )
  {
    gtk_widget_hide(properties->GtkInfo.checkbuttonRealTime);
    gtk_widget_hide(properties->GtkInfo.buttonCalendar);
  }

  if( !option_algorithms[properties->modeltype].bUsePound )
  {
    gtk_widget_hide(properties->GtkInfo.labelState);
    gtk_widget_hide(properties->GtkInfo.comboboxState);
  }

  if( !option_algorithms[modeltype].supportRealTime )
  {
    gtk_widget_hide(properties->GtkInfo.checkbuttonRealTime);
    g_print("Leaving realtime. Model probably doesn't support timing to hour, minute, second\n");
    properties->realTimeBleeding = 0;
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonRealTime),false);

    properties->data.t[0] = properties->data.t[0] - properties->data.te;
    properties->data.t[1] = properties->data.t[1] - properties->data.te2;
    properties->data.t[2] = properties->data.t[2] - properties->data.te3;

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

  } // if( !option_algorithms[modeltype].supportRealTime )

} // void on_comboboxModel_changed_hide(int modeltype, struct _properties *properties)

void on_comboboxModel_changed(GtkComboBox *combo, struct _properties *properties)
{
  g_print("on_comboboxModel_changed()\n");

  GtkTreeIter iter;
  GtkTreeModel *mstore;

  if( !gtk_combo_box_get_active_iter (GTK_COMBO_BOX (combo), &iter) )
  {
    g_print("on_comboboxModel_changed(): GTK_COMBO_BOX (combo) not valid (1)\n");
    return;
  }

  mstore = gtk_combo_box_get_model( GTK_COMBO_BOX(combo) );

  if( !mstore )
  {
    g_print("on_comboboxModel_changed(): GTK_COMBO_BOX (combo) not valid (2)\n");
    return;
  }

  char *key = (char *) gtk_tree_model_get_string_from_iter(GTK_TREE_MODEL(mstore), &iter);

  treeToIndex::iterator it = properties->TreeToIndex.begin();

  it = properties->TreeToIndex.find(key);
  if ( it != properties->TreeToIndex.end() ) 
  {
    g_print("Found value based on key %s is: %d\n", key, it->second);
    properties->modeltype = it->second;
  }
  else
  {
    g_print("Key \"%s\" is not in my_map. Using gtk_combo_box_get_active()\n", key);
    properties->modeltype = gtk_combo_box_get_active(combo);
  }
  g_free(key);

  g_print("properties->modeltype = %d\n", properties->modeltype);

  gtk_combo_box_set_active(GTK_COMBO_BOX(properties->GtkInfo.comboboxCycle), 0);

  checkForSourceCode(properties);

  updateStepping(properties);
  updateTime(properties->modeltype,properties);
  updateVolatility(properties->modeltype,properties);
  updatePrecision(properties->modeltype,properties);

  on_comboboxModel_changed_hide(properties->modeltype,properties);

  gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelStandardDeviation),option_algorithms[properties->modeltype].volatility);

  on_comboboxModel_changed_show(properties->modeltype,properties);

  if( option_algorithms[properties->modeltype].supportDividend == 5 )
  {
    gtk_widget_show(properties->GtkInfo.buttonCoupons);
  }

  if( option_algorithms[properties->modeltype].supportDividend == 6 )
  {
    gtk_widget_show(properties->GtkInfo.buttonCoupons);
    gtk_widget_show(properties->GtkInfo.buttonPrincipal);
  }

  pthread_mutex_lock(&properties->data.mutexCashflow);

  properties->data.amounts.erase( properties->data.amounts.begin(), properties->data.amounts.end() );
  properties->data.times.erase( properties->data.times.begin(), properties->data.times.end() );

  properties->data.times.push_back(0.25);
  properties->data.amounts.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.times.push_back(0.75);
  properties->data.amounts.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.times.push_back(1.25);
  properties->data.amounts.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.times.push_back(1.75);
  properties->data.amounts.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  //

  properties->data.coupon.erase( properties->data.coupon.begin(), properties->data.coupon.end() );
  properties->data.coupon_times.erase( properties->data.coupon_times.begin(), properties->data.coupon_times.end() );

  // should not use steps variable for this...Should be variable AddBondToLastCoupon...
  if( option_algorithms[properties->modeltype].steps == 0 )
  {
    properties->data.coupon_times.push_back(0.25);
    // defaultDividend variable being used as the coupon...
    properties->data.coupon.push_back(option_algorithms[properties->modeltype].defaultDividend); 

    properties->data.coupon_times.push_back(0.75);
    properties->data.coupon.push_back(option_algorithms[properties->modeltype].defaultDividend); 

    properties->data.coupon_times.push_back(1.25);
    properties->data.coupon.push_back(option_algorithms[properties->modeltype].defaultDividend); 

    properties->data.coupon_times.push_back(1.75);
    properties->data.coupon.push_back(option_algorithms[properties->modeltype].defaultDividend); 

    properties->data.coupon_times.push_back(2.25);
    // push back full bond value + the coupon...Bond is complete on this payment...
    properties->data.coupon.push_back(100 + option_algorithms[properties->modeltype].defaultDividend); 
  
  }
  else if( option_algorithms[properties->modeltype].steps == 1 )
  {
    properties->data.coupon_times.push_back(0.25);
    properties->data.coupon.push_back(1.25); 

    properties->data.coupon_times.push_back(0.75);
    properties->data.coupon.push_back(1.25); 

    properties->data.coupon_times.push_back(1.25);
    properties->data.coupon.push_back(1.25); 

    properties->data.coupon_times.push_back(1.75);
    properties->data.coupon.push_back(1.25); 

    properties->data.coupon_times.push_back(2.25);
    // push back last coupon...Bond is complete on this payment..
    properties->data.coupon.push_back(1.25); 

  } else if( option_algorithms[properties->modeltype].steps == 2 )
  {
    properties->data.coupon_times.push_back(1);
    properties->data.coupon.push_back(-100); 

    properties->data.coupon_times.push_back(2);
    properties->data.coupon.push_back(10); 

    properties->data.coupon_times.push_back(3);
    properties->data.coupon.push_back(110); 
  }

  //

  properties->data.principal.erase( properties->data.principal.begin(), properties->data.principal.end() );
  properties->data.principal_times.erase( properties->data.principal_times.begin(), properties->data.principal_times.end() );

  properties->data.principal_times.push_back(0.25);
  // defaultDividend variable being used as the principal payment...
  properties->data.principal.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.principal_times.push_back(0.50);
  properties->data.principal.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.principal_times.push_back(0.75);
  properties->data.principal.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.principal_times.push_back(1.00);
  properties->data.principal.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  properties->data.principal_times.push_back(1.25);
  properties->data.principal.push_back(option_algorithms[properties->modeltype].defaultDividend); 

  pthread_mutex_unlock(&properties->data.mutexCashflow);

  if( option_algorithms[properties->modeltype].bUsePound )
  {
    gtk_widget_show(properties->GtkInfo.labelState);
    gtk_label_set_text(GTK_LABEL(properties->GtkInfo.labelState),option_algorithms[properties->modeltype].UsePounddes);

    struct elementList listStates[option_algorithms[properties->modeltype].Poundmax];
    int num_states = option_algorithms[properties->modeltype].Poundmax;
    //g_print("num_states = %d\n",num_states);

    int index;
    for(index = 0; index < num_states; index++)
    {
      if( option_algorithms[properties->modeltype].bUseStateNames )
      {
        snprintf(listStates[index].elementName,sizeof(listStates[index].elementName),
                 "%d - %s",index+1,(char *) &(option_algorithms[properties->modeltype].StateNames[index]));
        //g_print("%d - %s\n",index+1,(char *) &(option_algorithms[properties->modeltype].StateNames[index]));
      } else
      {
        snprintf(listStates[index].elementName,sizeof(listStates[index].elementName),"%d",index+1);
      }
    }
    set_up_combobox_with_array2(properties->GtkInfo.comboboxState, listStates, num_states);
    gtk_widget_show(properties->GtkInfo.comboboxState);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////

  if( option_algorithms[properties->modeltype].assetClass == FUTURES_CLASS )
  {
    if( properties->decimalorcalendar == DECIMALS )
    {
      properties->format = DECIMAL_FUTURE;
    } else
    {
      properties->format = CALENDAR_FUTURE;

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);
      gtk_widget_show(properties->GtkInfo.checkbuttonSpreads);
    }

    gtk_widget_hide(properties->GtkInfo.labelStrikes);
    gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    gtk_widget_hide(properties->GtkInfo.scaleStrikes2);
    gtk_widget_hide(properties->GtkInfo.labelCND);
    gtk_widget_hide(properties->GtkInfo.comboboxCND);

  } else
  {
    if( properties->decimalorcalendar == DECIMALS )
    {
      properties->format = DECIMAL_GREEKS;
    } else
    {
      properties->format = DECIMAL_GREEKS;
      properties->decimalorcalendar = DECIMALS;
      properties->GtkInfo.checkbuttonDateEngineIgnore = true;
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonDateEngine),false);

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonSpreads),0);
      gtk_widget_hide(properties->GtkInfo.checkbuttonSpreads);
      gtk_widget_hide(properties->GtkInfo.scaleMonths2);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes2);

      updateTime(properties->modeltype,properties);
    }

    if( option_algorithms[properties->modeltype].supportStrikes )
    {
      gtk_widget_show(properties->GtkInfo.labelStrikes);
      gtk_widget_show(properties->GtkInfo.comboboxStrikes);

      gtk_button_set_label(GTK_BUTTON(properties->GtkInfo.scaleStrikes),"Strike Adjuster");
      gtk_widget_show(properties->GtkInfo.scaleStrikes);

    } else
    {
      gtk_widget_hide(properties->GtkInfo.labelStrikes);
      gtk_widget_hide(properties->GtkInfo.comboboxStrikes);
      gtk_widget_hide(properties->GtkInfo.scaleStrikes);
    }
  }

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(properties->GtkInfo.checkbuttonFilterNegativePrice),option_algorithms[properties->modeltype].filterNegativePrices);

  setup_tree_view(properties);
  show_title(properties);

} // void on_comboboxModel_changed(GtkComboBox *combo, struct _properties *properties)

void on_comboboxState_changed(GtkComboBox *combo, struct _properties *properties)
{
  //g_print("on_comboboxState_changed()\n");
  properties->data.UsePound = gtk_combo_box_get_active(combo) + 1;
  //g_print("State = %d\n",properties->data.UsePound);

} // void on_comboboxState_changed(GtkComboBox *combo, struct _properties *properties)

void on_comboboxCycle_changed(GtkComboBox *combo, struct _properties *properties)
{
  g_print("on_comboboxCycle_changed()\n");
  properties->optionscycle = gtk_combo_box_get_active(combo);

  expires(LEG1,30,properties->skipmonth,properties);
  expires(LEG2,30,properties->skipmonth2,properties);

  setup_tree_view(properties);

} // void on_comboboxCycle_changed(GtkComboBox *combo, struct _properties *properties)

void on_comboboxCND_changed(GtkComboBox *combo, struct _properties *properties)
{
  if( !option_algorithms[properties->modeltype].supportCND )
  {
    g_print("Option model does not support CND\n");
    return;
  }

  g_print("on_comboboxCND_changed() to ");
   
  properties->integration_type = gtk_combo_box_get_active(combo);

  g_print("%d %s\n", properties->integration_type,integration_method[properties->integration_type].des);

  properties->distribution_mean = 0.0;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistMean),0.0);

  properties->distribution_variance = 1.0;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonDistVariance),1.0);

  updateStepping(properties);

} // void on_comboboxCND_changed(GtkComboBox *combo, struct _properties *properties)
