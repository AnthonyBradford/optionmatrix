/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: gtk_extern.h of optionmatrix                                       */
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

extern GdkPixbuf *create_pixbuf(const gchar * filename);
extern void show_title(const struct _properties *properties);

extern void setup_tree_view(struct _properties *properties);
extern gboolean calculate_options(struct _properties *properties);
extern void process_greeks(struct _properties *properties, struct _data *dat, char *textCallDelta, char *textPutDelta, char *textGamma, char *textVega, char *textCallTheta, char *textPutTheta, char *textCallRho, char *textPutRho, char *textCallElasticity, char *textPutElasticity);
void text_export(struct _properties *properties, char *);
void file_export(struct _properties *properties, char *);

void spreadName(struct _properties *properties);

extern void on_calendar1_day_selected(GtkWidget *widget, struct _properties *properties);
extern int on_dialogCalendar_delete_event(GtkWidget *widget, GdkEvent *event, const struct _properties *properties);
extern void on_buttonCalendar_clicked(GtkWidget *widget, struct _properties *properties);
extern void on_buttonCalendar2_clicked(GtkWidget *widget, struct _properties *properties);
extern void on_buttonCalendar3_clicked(GtkWidget *widget, struct _properties *properties);

extern void on_menu_quit_activate(GtkWidget *widget, const struct _properties *properties);
extern void on_menu_about_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_website_activate(GtkWidget *widget, const struct _properties *properties);
extern void on_menu_feedback_activate(GtkWidget *widget, const struct _properties *properties);
extern void on_menu_debug_log_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_text_export_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_file_export_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_source_export_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_ListCategory_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_ListAuthor_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_List_activate(GtkWidget *widget, struct _properties *properties);
extern void on_menu_settings_activate(GtkWidget *widget, struct _properties *properties);

extern void checkForSourceCode(struct _properties *properties);
extern void display_source(const char *, const struct _properties *properties);

extern void set_up_combobox_with_array(GtkWidget *combo, const struct elementList *array, const size_t number);
extern void set_up_combobox_with_array2(GtkWidget *combo, const struct elementList *array, const size_t number);
void set_up_combobox_with_array_use_groups(GtkWidget *combo, struct elementListWithGroup *array, const size_t number,std::map<std::string, int>& treeToIndex, const int sort);
extern void on_comboboxWeekday_changed(GtkComboBox *combo, const struct _properties *properties);
extern void on_comboboxOccurance_changed(GtkComboBox *combo, const struct _properties *properties);
extern void on_comboboxStrikes_changed(GtkComboBox *combo, struct _properties *properties);
extern void on_comboboxModel_changed(GtkComboBox *combo, struct _properties *properties);
extern void on_comboboxModel_changed_hide(int modeltype, struct _properties *properties);
extern void on_comboboxModel_changed_show(int modeltype, struct _properties *properties);
extern void on_comboboxState_changed(GtkComboBox *combo, struct _properties *properties);
extern void on_comboboxCycle_changed(GtkComboBox *combo, struct _properties *properties);
extern void on_comboboxCND_changed(GtkComboBox *combo, struct _properties *properties);

extern void calc_strike_scale(struct _properties *properties);

extern void updateStepping(struct _properties *properties);
extern void updateVolatility(int modeltype, const struct _properties *properties);
extern void updateTime(int modeltype, struct _properties *properties);
void updatePrecision(int modeltype, struct _properties *properties);

void calc_strike_scale(struct _properties *properties);
void on_scaleStrikes_value_changed(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties);
void on_scaleMonths_value_changed(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties);
void on_scaleStrikes_value_changed2(GtkScaleButton *scaleButton, gdouble value, struct _properties *properties);
void on_scaleMonths_value_changed2(GtkScaleButton *scaleButton,  gdouble value, struct _properties *properties);

void on_spinbuttonDayOffset_value_changed(GtkSpinButton *spinButton, const struct _properties *properties);
void on_spinbuttonSleepDelay_value_changed(GtkSpinButton *spinButton, struct _properties *properties);
void on_spinbuttonUseZ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseB_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseJ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseP_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseQ_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseR_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseS_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonUseT_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonPrice_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
int on_spinbuttonTime_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
int on_spinbuttonTime_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
int on_spinbuttonTime2_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
int on_spinbuttonTime2_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
int on_spinbuttonTime3_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
int on_spinbuttonTime3_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToExpr_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToExpr_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToDividend_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToDividend_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToDividend2_focus_out_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonDaysToDividend2_focus_in_event(GtkSpinButton *spinbutton, GdkEventFocus *event, struct _properties *properties);
void on_spinbuttonTime_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonTime2_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonTime3_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDaysToExpr_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDaysToDividend_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDaysToDividend2_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonRate_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonStandardDeviation_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDividend_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonSteps_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonPrecision_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDistMean_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);
void on_spinbuttonDistVariance_value_changed(GtkSpinButton *spinbutton, struct _properties *properties);

void on_radiobutton1_pressed(GtkWidget *widget, struct _properties *properties);
void on_radiobutton2_pressed(GtkWidget *widget, struct _properties *properties);
void on_radiobutton3_pressed(GtkWidget *widget, struct _properties *properties);
void on_radiobutton4_pressed(GtkWidget *widget, struct _properties *properties);
void on_radiobutton5_pressed( GtkWidget *widget, struct _properties *properties);
void set_scale_button(struct _properties *properties );

void on_checkbuttonDateEngine_toggled(GtkButton *button, struct _properties *properties);
void on_checkbuttonRealTime_toggled(GtkButton *button, struct _properties *properties);
void on_checkbuttonSpreads_toggled(GtkButton *button, struct _properties *properties);
void on_checkbuttonFilterNegativePrice_toggled(GtkButton *button, struct _properties *properties);

void show_label_expirations(const struct _properties *properties);

void on_dialogProperties_ok(GtkWidget *widget, struct _properties *properties);
void on_dialogProperties_cancel(GtkWidget *widget, const struct _properties *properties);
void on_buttonProperties_clicked(GtkWidget *widget, const struct _properties *properties);
int on_dialogProperties_delete_event(GtkWidget *widget, const struct _properties *properties);

void on_dialogSettings_ok(GtkWidget *widget, gpointer *data);
void on_dialogSettings_cancel(GtkWidget *widget, const struct _properties *properties);
void on_buttonSettings_clicked(GtkWidget *widget, const struct _properties *properties);
int on_dialogSettings_delete_event(GtkWidget *widget, const struct _properties *properties);

void on_buttonDividends_clicked(GtkWidget *widget, struct _properties *properties);
void on_buttonCoupons_clicked( GtkWidget *widget, struct _properties *properties );
void on_buttonPrincipal_clicked( GtkWidget *widget, struct _properties *properties );

void window_configure_event( GtkWidget *widget, struct _properties *properties );

extern void setup_tree_view3(GtkWidget*);
extern void setup_tree_view4(GtkWidget*);
void generic_process_button(struct _properties *properties );

extern void add_cashflow3(GtkButton*, struct _properties *properties);
extern void add_cashflow4(GtkButton*, struct _properties *properties);
extern void remove_cashflows(GtkButton*, struct _properties *properties);
extern void remove_row(GtkTreeRowReference *ref, struct _properties *properties);

extern const char *const gtkBuilderString;
