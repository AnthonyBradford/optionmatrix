/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_menu.cpp of optionmatrix                                       */
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

void on_menu_quit_activate(GtkWidget *widget, const struct _properties *properties)
{
  g_print ("on_menu_quit_activate():\n");
  gtk_main_quit();
}

void on_menu_website_activate(GtkWidget *widget, const struct _properties *properties)
{
  g_print("on_menu_website_activate():\n");

#ifdef WIN32
  
  g_print("WIN32\n");
  char openURL[1024];
  snprintf(openURL,sizeof(openURL),"explorer %s", PACKAGE_URL);
  system(openURL);
  
#elif __APPLE__
  
  g_print("__APPLE__ %s\n", PACKAGE_URL);
  char openURL[1024];
  snprintf(openURL,sizeof(openURL),"open %s", PACKAGE_URL);
  system(openURL);

#elif __CYGWIN__
  
  g_print("__CYGWIN__\n");
  char openURL[1024];
  snprintf(openURL,sizeof(openURL),"explorer %s", PACKAGE_URL);
  system(openURL);
  
#else
  
  GError *error = NULL;

#ifdef HAVE_LIBGTK_3
  g_print("HAVE_LIBGTK_3\n");
  gtk_show_uri_on_window(NULL,PACKAGE_URL, GDK_CURRENT_TIME, &error);
#else
  g_print("!HAVE_LIBGTK_3\n");
  gtk_show_uri(NULL,PACKAGE_URL, GDK_CURRENT_TIME, &error);
#endif
  
  if (error != NULL)
  {
    if (error->domain == GDK_PIXBUF_ERROR)
      g_print ("GdkPixbufError: %s\n", error->message);
    else if (error->domain == G_FILE_ERROR)
      g_print ("GFileError: %s\n", error->message);
    else
      g_print ("An error \"%s\" in the unexpected domain:%d has occurred!\n", error->message, error->domain);

    g_error_free (error);
  }

#endif

} // void on_menu_website_activate(GtkWidget *widget, const struct _properties *properties)

void on_menu_feedback_activate(GtkWidget *widget, const struct _properties *properties)
{
  g_print("on_menu_feedback_activate():\n");
  char packageBugreport[1024];

#ifdef WIN32
  
  g_print("WIN32\n");
  snprintf(packageBugreport,sizeof(packageBugreport),"explorer mailto:%s",PACKAGE_BUGREPORT);
  system(packageBugreport);
  
#elif __APPLE__
  
  g_print("__APPLE__ %s\n", PACKAGE_URL);
  snprintf(packageBugreport,sizeof(packageBugreport),"open mailto:%s",PACKAGE_BUGREPORT);
  system(packageBugreport);
  
#elif __CYGWIN__
  
  g_print("__CYGWIN__\n");
  snprintf(packageBugreport,sizeof(packageBugreport),"explorer mailto:%s",PACKAGE_BUGREPORT);
  system(packageBugreport);

#else
  
  GError *error = NULL;

  snprintf(packageBugreport,sizeof(packageBugreport),"mailto:%s",PACKAGE_BUGREPORT);

#ifdef HAVE_LIBGTK_3
  g_print("HAVE_LIBGTK_3\n");
  gtk_show_uri_on_window(NULL,packageBugreport, GDK_CURRENT_TIME, &error);
#else
  g_print("!HAVE_LIBGTK_3\n");  
  gtk_show_uri(NULL,packageBugreport, GDK_CURRENT_TIME, &error);
#endif

  if (error != NULL)
  {
    if (error->domain == GDK_PIXBUF_ERROR)
      g_print ("GdkPixbufError: %s\n", error->message);
    else if (error->domain == G_FILE_ERROR)
      g_print ("GFileError: %s\n", error->message);
    else
      g_print ("An error \"%s\" in the unexpected domain:%d has occurred!\n", error->message, error->domain);

    g_error_free (error);
  }

#endif

} // void on_menu_feedback_activate(GtkWidget *widget, const struct _properties *properties)

static gboolean pngTimer(struct _properties *properties)
{
  g_print("pngTimer():\n");

  // Take random images from ./images or DATADIR/PACKAGE/images
  // If no images can be found gtk_icon.h is used to set
  // gtk_window_set_default_icon() in gtk_main.cpp
  // DATADIR can be overridden from the command line with the -x directory option

  int index = 0;
  char imageName[PATH_MAX*4] = { 0 };
  char dataDIRlocation[PATH_MAX*3] = { 0 };
  bool dataDIR = false;

  for( index = 0; index < 30; index++ )
  {
    snprintf(imageName,sizeof(imageName),"images/%d.png", index + 1);
    g_print("1 Checking for name: ./%s\n", imageName);

    if( access( imageName, F_OK ) == -1 )
    {
      break;
    }
  }

#ifdef DATADIR
  if( index == 0 )
  {
    g_print("DATADIR  = %s\n", DATADIR );
    g_print("data_dir = %s\n", properties->data_dir);

    for( index = 0; index < 30; index++ )
    {
      snprintf(imageName,sizeof(imageName),
               "%s/%s/images/%d.png",  (properties->data_dir[0] ? properties->data_dir : DATADIR), PACKAGE, index + 1);
      g_print("2 Checking for name: %s\n", imageName);

      if( access( imageName, F_OK ) == -1 )
      {
        dataDIR = true;
        break;
      }
    }
  }

  if(dataDIR)
  {
    snprintf(dataDIRlocation, sizeof(dataDIRlocation),
             "%s/%s/images", (properties->data_dir[0] ? properties->data_dir : DATADIR), PACKAGE);
  }
#endif

  GdkPixbuf *logo;
  GError *error = NULL;

  if( index )
  {
    if( index == 1 )
    {
      snprintf(imageName,sizeof(imageName),"%s/1.png", dataDIR ? dataDIRlocation : "images" );
      logo = gdk_pixbuf_new_from_file(imageName, &error);
    } else
    {
      snprintf(imageName,sizeof(imageName),
               "%s/%d.png", dataDIR ? dataDIRlocation : "images", 1 + (int)(index * (rand() / (RAND_MAX + 1.0))));
      g_print("imageName = %s\n",imageName);
      logo = gdk_pixbuf_new_from_file (imageName, &error);
    }

    /* Set the application logo or handle the error. */
    if (error == NULL)
    {
      gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), logo);

      g_object_unref(logo);

    } else
    {
        if (error->domain == GDK_PIXBUF_ERROR)
          g_print("GdkPixbufError: %s\n", error->message);
        else if (error->domain == G_FILE_ERROR)
          g_print("GFileError: %s\n", error->message);
        else
          g_print("An error in the unexpected domain:%d has occurred!\n", error->domain);

        g_error_free (error);
    }
  } else
  {
    g_print("No images available\n");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), NULL);
  }

  return GTK_IS_ABOUT_DIALOG(properties->GtkInfo.dialogAbout);

} // static gboolean pngTimer(struct _properties *properties)

void on_menu_about_activate( GtkWidget *widget, struct _properties *properties )
{
  g_print("on_menu_about_activate():\n");

  const gchar *authors[] = {
    "Anthony Bradford",
    PACKAGE_BUGREPORT,
    PACKAGE_URL,
    "\nwith models from:",

#ifdef METAOPTIONS
    "Bjorn Augestad, Meta Systems AS (Metaoptions-0.0.4)",
#endif

#ifdef ABRADFORD
    "Anthony Bradford",
#endif

#ifdef FINRECIPES
    "Bernt Arne Oedegaard (Financial Numerical Recipes in C++)",
#endif

#ifdef SPINSKY
    "Seth Pinsky",
#endif

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)
    "QuantLib",
#endif

    NULL
  };

  const gchar *documenters[] = {
    "Anthony Bradford",
    PACKAGE_BUGREPORT,
    PACKAGE_URL,
    NULL
  };

  properties->GtkInfo.dialogAbout = gtk_about_dialog_new();

  GdkPixbuf *logo;
  GError *error = NULL;
  char imageName[PATH_MAX*3];

  // This works for Windows
  if( access("images/6.png", F_OK ) == 0 )
  {
    snprintf(imageName,sizeof(imageName),"images/6.png");
    logo = gdk_pixbuf_new_from_file(imageName, &error);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), logo);
    g_object_unref(logo);
  }

#ifdef DATADIR
  g_print("DATADIR  = %s\n", DATADIR );
  g_print("data_dir = %s\n", properties->data_dir);

  snprintf(imageName,sizeof(imageName),"%s/%s/images/6.png",  (properties->data_dir[0] ? properties->data_dir : DATADIR), PACKAGE);
  g_print("3 Checking for name: %s\n", imageName);

  if( access( imageName, F_OK ) == 0 )
  {
    logo = gdk_pixbuf_new_from_file(imageName, &error);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), logo);
    g_object_unref(logo);
  }

#endif  

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), PACKAGE_NAME);

  char version[1024];

#if defined(ENVIRONMENT32)
  snprintf(version, sizeof(version), "%s 32-bit", PACKAGE_VERSION);
#elif defined(ENVIRONMENT64)
  snprintf(version, sizeof(version), "%s 64-bit", PACKAGE_VERSION);
#else
  snprintf(version, sizeof(version), "%s", PACKAGE_VERSION);
#endif

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), version);

  char aboutDialog[PATH_MAX];
  snprintf(aboutDialog,sizeof(aboutDialog),"The Ultimate Options Calculator\n%s", PACKAGE_BUGREPORT);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), 
                                 aboutDialog);

  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), 
                                  "(C) 2012 Anthony Bradford");

  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), license);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), 
                                       PACKAGE_URL);
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG (properties->GtkInfo.dialogAbout), 
                                      PACKAGE_URL);

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(properties->GtkInfo.dialogAbout), authors);
  gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(properties->GtkInfo.dialogAbout), documenters);
  snprintf(aboutDialog,sizeof(aboutDialog),"Anthony Bradford\n<%s>\n%s          ", PACKAGE_BUGREPORT, PACKAGE_URL);
  gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(properties->GtkInfo.dialogAbout), aboutDialog);

  // Next line places 1 images in the about dialog
  //pngTimer(properties);

  guint ret = 0;
  // Next line rotates the images in the about dialog, images are not the same size so the dialog jumps around
  ret = g_timeout_add(4000, (GSourceFunc) pngTimer, (gpointer) properties);

  gtk_dialog_run(GTK_DIALOG(properties->GtkInfo.dialogAbout));

  if( ret )
    g_source_remove(ret);

  gtk_widget_destroy(properties->GtkInfo.dialogAbout);

} // void on_menu_about_activate( GtkWidget *widget, struct _properties *properties )

void on_menu_debug_log_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_debug_log_activate()\n");

  if( properties->data.debug == true )
    properties->data.debug = false;
  else
    properties->data.debug = true;

} // void on_menu_debug_log_activate(GtkWidget *widget, struct _properties *properties)

void on_menu_text_export_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_text_export_activate()\n");

  properties->textExport = true;
}

void on_menu_file_export_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_file_export_activate()\n");

  properties->textExport = true;
  properties->fileExport = true;
}

void on_menu_source_export_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_source_export_activate()\n");

  if( strcmp(option_algorithms[properties->modeltype].sourceCode,"") != 0 )
  {
    g_print("option_algorithms[properties->modeltype].sourceCode = %s\n", option_algorithms[properties->modeltype].sourceCode );
    display_source(option_algorithms[properties->modeltype].sourceCode, properties);
  }

  if( strcmp(option_algorithms[properties->modeltype].sourceCode2,"") != 0 )
  {
    g_print("sourceCode2 exists sourceCode2 = %s\n", option_algorithms[properties->modeltype].sourceCode2 );
    display_source(option_algorithms[properties->modeltype].sourceCode2, properties);
  }

} // void on_menu_source_export_activate(GtkWidget *widget, struct _properties *properties)

// display_source() fails on displaying src/models/metaoptions/src/bisection.c source file
// (under Linux but not Windows) due to some Norwegian in the comments of the source
void display_source(const char *name, const struct _properties *properties)
{
  g_print("properties.source_directory_prefix = %s\n", properties->source_directory_prefix);

  GtkWidget *window, *scrolled_win, *textview;
  GtkTextBuffer *buffer;

  char windowTitle[PATH_MAX*2] = { 0 };
  snprintf(windowTitle,sizeof(windowTitle),"%s Source Export %s", PACKAGE_NAME, name);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), windowTitle);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 700, 600);

  if( access("images/2.png", F_OK ) == 0 )
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("images/2.png"));
  
  textview = gtk_text_view_new();

  FILE *file = NULL;
  char *bufferSource;
  unsigned long fileLen;

  char name2[PATH_MAX*3]  = { 0 };
  char name3[PATH_MAX*3]  = { 0 };
  char name4[PATH_MAX*3]  = { 0 };

  snprintf(name2,sizeof(name2),"src/%s-%s/src/%s", PACKAGE_TARNAME,VERSION,name);
  snprintf(name3,sizeof(name3),"../../src/%s", name);
  snprintf(name4,sizeof(name4),"%s/src/%s", properties->source_directory_prefix,name);

  if( access( name, F_OK ) == 0 )
  {
    file = fopen(name, "rb");

  } else if( access( name2, F_OK ) == 0 )
  {
    file = fopen(name2, "rb");

  } else if( access( name3, F_OK ) == 0 )
  {
    file = fopen(name3, "rb");

  } else if( access( name4, F_OK ) == 0 )
  {
    file = fopen(name4, "rb");
  }

  if( !file )
  {
    g_print("display_source(): Unable to open source file %s or %s or %s or %s", name, name2, name3, name4);
    return;
  }

  fseek(file, 0, SEEK_END);
  fileLen = ftell(file);
  fseek(file, 0, SEEK_SET);

  bufferSource = (char *) malloc(fileLen+1);

  if( !bufferSource )
  {
    g_print("display_source(): Memory error\n");
    fclose(file);
    return;
  }

  if(!fread(bufferSource, fileLen, 1, file))
  {
    g_print("display_source(): fread() returning 0\n");
  }

  fclose(file);

  bufferSource[fileLen] = 0;
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
  
  gtk_text_buffer_set_text (buffer, g_locale_to_utf8 (bufferSource, -1,0,0,0), -1);
  
  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  
  gtk_container_add(GTK_CONTAINER (window), scrolled_win);
  gtk_widget_show_all(window);

  free(bufferSource);

} // void display_source(const char *name, const struct _properties *properties)

void checkForSourceCode(struct _properties *properties)
{
  char sourceLocation2[PATH_MAX*3]  = { 0 };
  char sourceLocation3[PATH_MAX*3]  = { 0 };
  char sourceLocation4[PATH_MAX*3]  = { 0 };

  snprintf(sourceLocation2,sizeof(sourceLocation2),"src/%s-%s/src/%s",PACKAGE_TARNAME,VERSION,option_algorithms[properties->modeltype].sourceCode);
  g_print("sourceLocation2 = %s\n",sourceLocation2);

  snprintf(sourceLocation3,sizeof(sourceLocation3),"../../src/%s", option_algorithms[properties->modeltype].sourceCode);
  g_print("sourceLocation3 = %s\n",sourceLocation3);

  snprintf(sourceLocation4,sizeof(sourceLocation4),"%s/src/%s", properties->source_directory_prefix,option_algorithms[properties->modeltype].sourceCode);
  g_print("sourceLocation4 = %s\n",sourceLocation4);

  if( strcmp( option_algorithms[properties->modeltype].sourceCode,"") != 0 )
  {
    if( access( option_algorithms[properties->modeltype].sourceCode, F_OK ) == 0 )
    {
      g_print("sourceCode is %s\n",option_algorithms[properties->modeltype].sourceCode);
      gtk_widget_show(properties->GtkInfo.menu_source_export);

    } else if( access( sourceLocation2, F_OK ) == 0  )
    {
      g_print("sourceCode is %s\n",sourceLocation2);
      gtk_widget_show(properties->GtkInfo.menu_source_export);

    } else if( access( sourceLocation3, F_OK ) == 0  )
    {
      g_print("sourceCode is %s\n",sourceLocation3);
      gtk_widget_show(properties->GtkInfo.menu_source_export);

    } else if( access( sourceLocation4, F_OK ) == 0  )
    {
      g_print("sourceCode is %s\n",sourceLocation4);
      gtk_widget_show(properties->GtkInfo.menu_source_export);

    } else
    {
      g_print("Cannot access sourceCode %s or\n%s\n",option_algorithms[properties->modeltype].sourceCode,sourceLocation2);
      gtk_widget_hide(properties->GtkInfo.menu_source_export);
    }

  } else
  {
    g_print("sourceCode not defined\n");
    gtk_widget_hide(properties->GtkInfo.menu_source_export);
  }

} // void checkForSourceCode(struct _properties *properties)

void on_menu_ListCategory_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_ListCategory_activate():\n");

  const int num_models = (signed) (sizeofoption_algorithms/sizeof(struct option_algorithm));

  struct elementListWithGroup *listModelsForGroups = new elementListWithGroup[num_models];

  int index = 0;
  for(index = 0; index < num_models; index++)
  {
    snprintf(listModelsForGroups[index].elementName,sizeof(listModelsForGroups[index].elementName),
             "%s",option_algorithms[index].des);
    snprintf(listModelsForGroups[index].groupName,sizeof(listModelsForGroups[index].groupName),
             "%s",option_algorithms[index].category);
    listModelsForGroups[index].index = index;
  }

  set_up_combobox_with_array_use_groups(properties->GtkInfo.comboboxModel, listModelsForGroups, num_models, properties->TreeToIndex,1);

  if( listModelsForGroups )
  {
    delete [] listModelsForGroups;
    listModelsForGroups = 0;
  }

} // void on_menu_ListCategory_activate(GtkWidget *widget, struct _properties *properties)

void on_menu_ListAuthor_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_ListAuthor_activate():\n");

  const int num_models = (signed) (sizeofoption_algorithms/sizeof(struct option_algorithm));

  struct elementListWithGroup *listModelsForGroups = new elementListWithGroup[num_models];

  int index = 0;
  for(index = 0; index < num_models; index++)
  {
    snprintf(listModelsForGroups[index].elementName,sizeof(listModelsForGroups[index].elementName),
             "%s",option_algorithms[index].des);
    snprintf(listModelsForGroups[index].groupName,sizeof(listModelsForGroups[index].groupName),
             "%s",option_algorithms[index].source);
    listModelsForGroups[index].index = index;
  }

  set_up_combobox_with_array_use_groups(properties->GtkInfo.comboboxModel, listModelsForGroups, num_models, properties->TreeToIndex,0);

  if( listModelsForGroups )
  {
    delete [] listModelsForGroups;
    listModelsForGroups = 0;
  }

} // void on_menu_ListAuthor_activate(GtkWidget *widget, struct _properties *properties)

void on_menu_List_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_List_activate():\n");

  const int num_models = (signed) (sizeofoption_algorithms/sizeof(struct option_algorithm));
  struct elementList listModels[num_models];

  int index = 0;
  for(index = 0; index < num_models; index++)
  {
    snprintf(listModels[index].elementName,sizeof(listModels[index].elementName),
             "%d - %s", index + 1, option_algorithms[index].des);
  }

  set_up_combobox_with_array(properties->GtkInfo.comboboxModel, listModels, num_models);

} // void on_menu_List_activate(GtkWidget *widget, struct _properties *properties)

void on_menu_settings_activate(GtkWidget *widget, struct _properties *properties)
{
  g_print("on_menu_settings_activate():\n");

  gtk_widget_show_all(properties->GtkInfo.dialogSettings);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(properties->GtkInfo.spinbuttonSleepDelay),properties->updatedelayseconds);

} // void on_menu_settings_activate(GtkWidget *widget, struct _properties *properties)
