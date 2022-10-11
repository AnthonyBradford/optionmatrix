/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: glade.h of optionmatrix                                            */
/*                                                                          */
/* Copyright (c) Anthony Bradford. 2012.                                    */
/* anthony_bradford@yahoo.com                                               */
/*                                                                          */
/* optionmatrix may be freely redistributed.                                */
/* See file COPYING included with this distribution for license information */

/* 
   optionmatrix program is free software; you can redistribute it and/or modify
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

// Import gtk_glade_xml.glade file after word gtkBuilderString = "
// replace all control-J with \\Control-J 
// replace after the first " all " with \\"  (leave gtkBuilderString = " alone )
// change final ending \ to ";

const char *const gtkBuilderString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<interface>\
  <requires lib=\"gtk+\" version=\"2.16\"/>\
  <!-- interface-naming-policy project-wide -->\
  <object class=\"GtkDialog\" id=\"dialogCalendar\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"type_hint\">normal</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkVBox\" id=\"dialog-vbox2\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkHButtonBox\" id=\"dialog-action_area2\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkCalendar\" id=\"calendar1\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <property name=\"year\">2010</property>\
            <property name=\"month\">10</property>\
            <property name=\"day\">29</property>\
            <signal name=\"day-selected\" handler=\"on_calendar1_day_selected\" swapped=\"no\"/>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkLabel\" id=\"labelCalendar\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
  <object class=\"GtkDialog\" id=\"dialogProperties\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"modal\">True</property>\
    <property name=\"window_position\">center-on-parent</property>\
    <property name=\"default_width\">300</property>\
    <property name=\"type_hint\">normal</property>\
    <property name=\"gravity\">center</property>\
    <signal name=\"delete-event\" handler=\"on_dialogProperties_delete_event\" swapped=\"no\"/>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkVBox\" id=\"dialog-vbox1\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkHButtonBox\" id=\"dialog-action_area1\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkHBox\" id=\"hbox19\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelWeekday\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Expiration weekday</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkComboBox\" id=\"comboboxWeekday\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">False</property>\
                <property name=\"pack_type\">end</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkHBox\" id=\"hbox20\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelOccurance\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Occurance</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkComboBox\" id=\"comboboxOccurance\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">False</property>\
                <property name=\"pack_type\">end</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkHBox\" id=\"hbox21\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDayOffset\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Day offset</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkSpinButton\" id=\"spinbuttonDayOffset\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"invisible_char\">●</property>\
                <property name=\"primary_icon_activatable\">False</property>\
                <property name=\"secondary_icon_activatable\">False</property>\
                <property name=\"primary_icon_sensitive\">True</property>\
                <property name=\"secondary_icon_sensitive\">True</property>\
                <signal name=\"value-changed\" handler=\"on_spinbuttonDayOffset_value_changed\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">False</property>\
                <property name=\"pack_type\">end</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">3</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkHBox\" id=\"hbox22\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelExpirationTime\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Expiration Time</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkEntry\" id=\"entryExpirationTime\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"max_length\">8</property>\
                <property name=\"invisible_char\">●</property>\
                <property name=\"width_chars\">8</property>\
                <property name=\"primary_icon_activatable\">False</property>\
                <property name=\"secondary_icon_activatable\">False</property>\
                <property name=\"primary_icon_sensitive\">True</property>\
                <property name=\"secondary_icon_sensitive\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">False</property>\
                <property name=\"pack_type\">end</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">4</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkLabel\" id=\"labelTimeError\">\
            <property name=\"can_focus\">False</property>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">5</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
  <object class=\"GtkDialog\" id=\"dialogSettings\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"type_hint\">normal</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkVBox\" id=\"dialog-vbox3\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkHButtonBox\" id=\"dialog-action_area3\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkVBox\" id=\"vbox1\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"checkbuttonFilterNegativePrice\">\
                <property name=\"label\" translatable=\"yes\">Filter negative put/call prices</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"active\">True</property>\
                <property name=\"draw_indicator\">True</property>\
                <signal name=\"toggled\" handler=\"on_checkbuttonFilterNegativePrice_toggled\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox14\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"labelSleepDelay\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Sleep delay</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonSleepDelay\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonSleepDelay_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
  <object class=\"GtkListStore\" id=\"liststore1\"/>\
  <object class=\"GtkRadioMenuItem\" id=\"radiomenuitem1\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"draw_as_radio\">True</property>\
  </object>\
  <object class=\"GtkWindow\" id=\"window1\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"title\" translatable=\"yes\">OptionMatrix</property>\
    <property name=\"gravity\">center</property>\
    <child>\
      <object class=\"GtkVPaned\" id=\"vpaned1\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">True</property>\
        <child>\
          <object class=\"GtkTable\" id=\"tableTop\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"n_rows\">15</property>\
            <property name=\"n_columns\">8</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelRate\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Interest Rate</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"checkbuttonDateEngine\">\
                <property name=\"label\" translatable=\"yes\">Use Date Engine</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"draw_indicator\">True</property>\
                <signal name=\"toggled\" handler=\"on_checkbuttonDateEngine_toggled\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"top_attach\">10</property>\
                <property name=\"bottom_attach\">11</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDaysToExpr\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Days to Expiration</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelTime1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Time to Expiration</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseZ\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseB\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseP\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">6</property>\
                <property name=\"right_attach\">7</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseJ\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelExpirations\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Expirations set to 3rd Friday+1 @ 11:59:00</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">10</property>\
                <property name=\"bottom_attach\">11</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelSteps\">\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Steps</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelPrecision\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Precision</property>\
                <property name=\"use_underline\">True</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">6</property>\
                <property name=\"right_attach\">7</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelModel\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Model</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkMenuBar\" id=\"menubar1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkMenuItem\" id=\"menuitem1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">_File</property>\
                    <property name=\"use_underline\">True</property>\
                    <child type=\"submenu\">\
                      <object class=\"GtkMenu\" id=\"menu1\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_text_export\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Text Export</property>\
                            <property name=\"use_underline\">True</property>\
                            <signal name=\"activate\" handler=\"on_menu_text_export_activate\" swapped=\"no\"/>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_file_export\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">File Export</property>\
                            <property name=\"use_underline\">True</property>\
                            <signal name=\"activate\" handler=\"on_menu_file_export_activate\" swapped=\"no\"/>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_source_export\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Source View</property>\
                            <property name=\"use_underline\">True</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkCheckMenuItem\" id=\"menu_debug_log\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Debug Log</property>\
                            <property name=\"use_underline\">True</property>\
                            <signal name=\"activate\" handler=\"on_menu_debug_log_activate\" swapped=\"no\"/>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkSeparatorMenuItem\" id=\"menuitem2\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkImageMenuItem\" id=\"menu_quit\">\
                            <property name=\"label\">gtk-quit</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"use_underline\">True</property>\
                            <property name=\"use_stock\">True</property>\
                            <signal name=\"activate\" handler=\"on_menu_quit_activate\" swapped=\"no\"/>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child>\
                  <object class=\"GtkMenuItem\" id=\"menuitem3\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">_Models</property>\
                    <property name=\"use_underline\">True</property>\
                    <child type=\"submenu\">\
                      <object class=\"GtkMenu\" id=\"menu2\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkRadioMenuItem\" id=\"menu_ListCategory\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">List by Category</property>\
                            <property name=\"use_underline\">True</property>\
                            <property name=\"active\">True</property>\
                            <property name=\"group\">radiomenuitem1</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkRadioMenuItem\" id=\"menu_ListAuthor\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">List by Author</property>\
                            <property name=\"use_underline\">True</property>\
                            <property name=\"draw_as_radio\">True</property>\
                            <property name=\"group\">radiomenuitem1</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkRadioMenuItem\" id=\"menu_List\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">List</property>\
                            <property name=\"use_underline\">True</property>\
                            <property name=\"draw_as_radio\">True</property>\
                            <property name=\"group\">radiomenuitem1</property>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child>\
                  <object class=\"GtkMenuItem\" id=\"menuitem5\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">_Prefs</property>\
                    <property name=\"use_underline\">True</property>\
                    <child type=\"submenu\">\
                      <object class=\"GtkMenu\" id=\"menu4\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_settings\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Settings</property>\
                            <property name=\"use_underline\">True</property>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child>\
                  <object class=\"GtkMenuItem\" id=\"menuitem4\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">_Help</property>\
                    <property name=\"use_underline\">True</property>\
                    <child type=\"submenu\">\
                      <object class=\"GtkMenu\" id=\"menu3\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_website\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Website</property>\
                            <property name=\"use_underline\">True</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkMenuItem\" id=\"menu_feedback\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Send Feedback</property>\
                            <property name=\"use_underline\">True</property>\
                          </object>\
                        </child>\
                        <child>\
                          <object class=\"GtkImageMenuItem\" id=\"menu_about\">\
                            <property name=\"label\">gtk-about</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"use_underline\">True</property>\
                            <property name=\"use_stock\">True</property>\
                            <signal name=\"activate\" handler=\"on_menu_about_activate\" swapped=\"no\"/>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"right_attach\">8</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox2\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">13</property>\
                <property name=\"bottom_attach\">14</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox3\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkComboBox\" id=\"comboboxModel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox4\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonPrice\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <property name=\"climb_rate\">0.10000000000000001</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonPrice_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox5\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseZ\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseZ_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox6\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonTime\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in years</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"focus\" handler=\"on_spinbuttonTime_focus\" swapped=\"no\"/>\
                    <signal name=\"proximity-in-event\" handler=\"on_spinbuttonTime_proximity_in_event\" swapped=\"no\"/>\
                    <signal name=\"focus-out-event\" handler=\"on_spinbuttonTime_focus_out_event\" swapped=\"no\"/>\
                    <signal name=\"input\" handler=\"on_spinbuttonTime_input\" swapped=\"no\"/>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonTime_value_changed\" swapped=\"no\"/>\
                    <signal name=\"focus-in-event\" handler=\"on_spinbuttonTime_focus_in_event\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox7\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkComboBox\" id=\"comboboxStrikes\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonCustomStrike\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <property name=\"climb_rate\">0.10000000000000001</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonCustomStrike_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelCND\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">CND</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
                <property name=\"x_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox9\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDaysToExpr\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in days</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonDaysToExpr_value_changed\" swapped=\"no\"/>\
                    <signal name=\"focus-in-event\" handler=\"on_spinbuttonDaysToExpr_focus_in_event\" swapped=\"no\"/>\
                    <signal name=\"focus-out-event\" handler=\"on_spinbuttonDaysToExpr_focus_out_event\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox10\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseB\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseB_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox11\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonRate\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonRate_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox12\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkComboBox\" id=\"comboboxCND\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <signal name=\"changed\" handler=\"on_comboboxCND_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox13\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDistMean\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox15\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonSteps\">\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"editable\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <property name=\"climb_rate\">1</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonSteps_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox16\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonStandardDeviation\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonStandardDeviation_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox17\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseJ\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseJ_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox18\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkButton\" id=\"buttonProperties\">\
                    <property name=\"label\" translatable=\"yes\">Date Engine Properties</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">True</property>\
                    <signal name=\"clicked\" handler=\"on_buttonProperties_clicked\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">10</property>\
                <property name=\"bottom_attach\">11</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelInfo\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Info</property>\
              </object>\
              <packing>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">14</property>\
                <property name=\"bottom_attach\">15</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"buttonCalendar\">\
                <property name=\"label\" translatable=\"yes\">Calendar</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <signal name=\"clicked\" handler=\"on_buttonCalendar_clicked\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">7</property>\
                <property name=\"bottom_attach\">8</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelState\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">State</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox23\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkComboBox\" id=\"comboboxState\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <signal name=\"changed\" handler=\"on_comboboxState_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDistMean\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Distribution Mean</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDistVariance\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Distribution Variance</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox24\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDistVariance\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">2</property>\
                <property name=\"bottom_attach\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox25\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonPrecision\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"max_length\">2</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <property name=\"numeric\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonPrecision_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">7</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">1</property>\
                <property name=\"bottom_attach\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox26\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDividend\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonDividend_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkButton\" id=\"buttonDividends\">\
                    <property name=\"label\" translatable=\"yes\">Dividends</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">7</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox27\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseP\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseP_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">7</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">5</property>\
                <property name=\"bottom_attach\">6</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseQ\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseR\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseS\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelUseT\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">6</property>\
                <property name=\"right_attach\">7</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox28\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseT\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseT_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">7</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox29\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseS\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseS_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox30\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseR\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseR_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox31\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonUseQ\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonUseQ_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">6</property>\
                <property name=\"bottom_attach\">7</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkRadioButton\" id=\"radiobutton1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"active\">True</property>\
                    <property name=\"draw_indicator\">True</property>\
                    <signal name=\"pressed\" handler=\"on_radiobutton1_pressed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkRadioButton\" id=\"radiobutton2\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"draw_indicator\">True</property>\
                    <property name=\"group\">radiobutton1</property>\
                    <signal name=\"pressed\" handler=\"on_radiobutton2_pressed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkRadioButton\" id=\"radiobutton3\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"draw_indicator\">True</property>\
                    <property name=\"group\">radiobutton1</property>\
                    <signal name=\"pressed\" handler=\"on_radiobutton3_pressed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkRadioButton\" id=\"radiobutton4\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"draw_indicator\">True</property>\
                    <property name=\"group\">radiobutton1</property>\
                    <signal name=\"pressed\" handler=\"on_radiobutton4_pressed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">3</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkRadioButton\" id=\"radiobutton5\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"draw_indicator\">True</property>\
                    <property name=\"group\">radiobutton1</property>\
                    <signal name=\"pressed\" handler=\"on_radiobutton5_pressed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">4</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">11</property>\
                <property name=\"bottom_attach\">12</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDisplayFormats2\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">11</property>\
                <property name=\"bottom_attach\">12</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDisplayFormats\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Display Formats</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">11</property>\
                <property name=\"bottom_attach\">12</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelPrice\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Price</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelStandardDeviation\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Standard Deviation</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDividend\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Dividend</property>\
                <property name=\"use_underline\">True</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">6</property>\
                <property name=\"right_attach\">7</property>\
                <property name=\"top_attach\">4</property>\
                <property name=\"bottom_attach\">5</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"checkbuttonSpreads\">\
                <property name=\"label\" translatable=\"yes\">Spreads</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"draw_indicator\">True</property>\
                <signal name=\"toggled\" handler=\"on_checkbuttonSpreads_toggled\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"top_attach\">11</property>\
                <property name=\"bottom_attach\">12</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"checkbuttonRealTime\">\
                <property name=\"label\" translatable=\"yes\">RealTime</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"draw_indicator\">True</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDisplayTime\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">6</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelSpread\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">11</property>\
                <property name=\"bottom_attach\">12</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelStrikes\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Strikes</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelCycle\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Cycle</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">10</property>\
                <property name=\"bottom_attach\">11</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkScaleButton\" id=\"scaleMonths\">\
                <property name=\"label\" translatable=\"yes\">Month Adjuster</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"relief\">none</property>\
                <property name=\"focus_on_click\">False</property>\
                <property name=\"orientation\">vertical</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkScaleButton\" id=\"scaleMonths2\">\
                <property name=\"label\" translatable=\"yes\">Month Adj Leg2</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"relief\">none</property>\
                <property name=\"focus_on_click\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <signal name=\"value-changed\" handler=\"on_scaleMonths2_value_changed\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">13</property>\
                <property name=\"bottom_attach\">14</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkScaleButton\" id=\"scaleStrikes2\">\
                <property name=\"label\" translatable=\"yes\">Strike Adj Leg2</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"relief\">none</property>\
                <property name=\"focus_on_click\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <signal name=\"value-changed\" handler=\"on_scaleStrikes2_value_changed\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">13</property>\
                <property name=\"bottom_attach\">14</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox32\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonCustomStrike2\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <property name=\"climb_rate\">0.10000000000000001</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkScaleButton\" id=\"scaleStrikes\">\
                    <property name=\"label\" translatable=\"yes\">Strike Adjuster</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">True</property>\
                    <property name=\"relief\">none</property>\
                    <property name=\"focus_on_click\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <signal name=\"value-changed\" handler=\"on_scaleStrikes_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelStrikes2\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">StrikeLeg2</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">12</property>\
                <property name=\"bottom_attach\">13</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox33\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkComboBox\" id=\"comboboxCycle\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"active\">0</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">10</property>\
                <property name=\"bottom_attach\">11</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label3\">\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Time to Dividend</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox34\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonTime3\">\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in years</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonTime3_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDaysToDividend2\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Days to Dividend</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox35\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDaysToDividend2\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in days</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonDaysToDividend2_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelTime3\">\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label2\">\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Time to Dividend</property>\
              </object>\
              <packing>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox36\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonTime2\">\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in years</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonTime2_value_changed\" swapped=\"no\"/>\
                    <signal name=\"focus-in-event\" handler=\"on_spinbuttonTime2_focus_in_event\" swapped=\"no\"/>\
                    <signal name=\"focus-out-event\" handler=\"on_spinbuttonTime2_focus_out_event\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">1</property>\
                <property name=\"right_attach\">2</property>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelDaysToDividend\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Days to Dividend</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">2</property>\
                <property name=\"right_attach\">3</property>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox37\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkSpinButton\" id=\"spinbuttonDaysToDividend\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Time in days</property>\
                    <property name=\"invisible_char\">●</property>\
                    <property name=\"primary_icon_activatable\">False</property>\
                    <property name=\"secondary_icon_activatable\">False</property>\
                    <property name=\"primary_icon_sensitive\">True</property>\
                    <property name=\"secondary_icon_sensitive\">True</property>\
                    <signal name=\"value-changed\" handler=\"on_spinbuttonDaysToDividend_value_changed\" swapped=\"no\"/>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">3</property>\
                <property name=\"right_attach\">4</property>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"buttonCalendar3\">\
                <property name=\"label\" translatable=\"yes\">Calendar</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">8</property>\
                <property name=\"bottom_attach\">9</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"buttonCalendar2\">\
                <property name=\"label\" translatable=\"yes\">Calendar</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <signal name=\"clicked\" handler=\"on_buttonCalendar2_clicked\" swapped=\"no\"/>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"labelTime2\">\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">4</property>\
                <property name=\"right_attach\">5</property>\
                <property name=\"top_attach\">9</property>\
                <property name=\"bottom_attach\">10</property>\
                <property name=\"x_options\"/>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"buttonCoupons\">\
                <property name=\"label\" translatable=\"yes\">Coupons</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"left_attach\">5</property>\
                <property name=\"right_attach\">6</property>\
                <property name=\"top_attach\">3</property>\
                <property name=\"bottom_attach\">4</property>\
                <property name=\"x_options\">GTK_FILL</property>\
                <property name=\"y_options\"/>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkHBox\" id=\"hbox8\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <object class=\"GtkButton\" id=\"buttonPrincipal\">\
                    <property name=\"label\" translatable=\"yes\">Principal</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"left_attach\">7</property>\
                <property name=\"right_attach\">8</property>\
                <property name=\"top_attach\">3</property>\
                <property name=\"bottom_attach\">4</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"resize\">False</property>\
            <property name=\"shrink\">False</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow1\">\
            <property name=\"width_request\">575</property>\
            <property name=\"height_request\">320</property>\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <property name=\"hscrollbar_policy\">automatic</property>\
            <property name=\"vscrollbar_policy\">automatic</property>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"resize\">True</property>\
            <property name=\"shrink\">True</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
</interface>";
