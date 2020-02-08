/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: extern.h of optionmatrix                                           */
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

#undef PACKAGE_VERSION
#undef VERSION

#include "config.h"

extern int months[];
extern const char *const mon[];
extern const char *const optionscycle[];
extern const char *const weekdays[];
extern const char *const future_codes[];
extern const char *const option_calls[];
extern const char *const option_puts[];
extern const char *const order[];

extern struct _properties properties;
extern struct _properties future_properties;

/* distributions */
extern double normal_dist_integrate(const double, const double, const double);
extern double inverse_normal_dist_integrate(const double, const double, const double);

extern double normal_dist_constant(const double standarddeviation);
extern double inverse_normal_dist_constant(const double standarddeviation);

extern const int sizeofterm_structure_list;
extern const int sizeofdistribution_list;
extern const int sizeofintegration_method;
extern const int sizeofstrike_control;

/* cumlative norm calculation methods */
extern double rombergs_method(const double, const double, int, double (*fun) (double,double,double), const double, const double);
extern double simpsons_rule(const double, const double, int, double (*fun) (double,double,double), const double, const double);
extern double trapezoid_rule(const double, const double, int, double (*fun) (double,double,double), const double parm2, const double parm3 );
extern double unit_normal_poly_approx6(const double z);
extern double unit_normal_poly_approx4(const double z);
extern double unit_normal_rat_7(const double z);
extern double unit_normal_rat_4(const double z);
extern double unit_normal_hart(const double z);

// This is needed so fin_recipes N() is not used but rather
// cnd() in cumulative_norm.c is used
extern double N(const double& z);
// This is needed so metaoptions libraries dont use their cnd()
// but rather the cnd() from cumulative_norm.c
extern "C"
{
  double cnd(double d1);
}

extern double cnd(const double d1);
extern double unit(const double z);
extern double normd(const double z);

/* time/date functions */
extern int day_changed();
extern int validate_date(const int day, const int month, int year);
extern int validate_time(const int hours, const int minutes, const int seconds);
extern int date_to_days_away(const int day, int month, int year);
extern char *decimal_date_to_real_date(double);
extern void decimal_date_to_real_dates(double decimaltime, int *year, int *month, int *day, int *hour, int *minute, int *seconds);
extern int decimal_date_to_int_month(const double);
extern int decimal_date_to_int_year(const double);
extern double adjust_to_current_time_and_expr(int *tte, unsigned int expiration_time, const double day_offset);
extern double adjust_to_current_time(double t, const double day_offset);
extern double adjust_to_current_time_forward(double t, const double day_offset);
extern void calendar(const struct _properties *properties);
extern int expires(const int, const int, const int, struct _properties *properties);

/* program properties */
extern int props(struct _properties *properties, struct _properties *future_properties);
extern void props_defaults_options(struct _properties *properties, const int clearcalendar);
extern void props_defaults_futures(struct _properties *properties, const int clearcalendar);
extern void simple_help(const struct _properties *properties);
extern void quit(int);
extern void calendar_date_message(void);
extern void decimal_date_message(void);
extern void one_time_banner_message(void);

extern const struct integratable_distributions distribution_list[];
extern const struct numerical_integration_method integration_method[];
extern const char *const license;
extern const char *const license2;
extern void choose_options(void);
extern void welcome_screen(void);

extern struct _data option_call(struct _data *data);
extern struct _data option_put(struct _data *data);
extern struct _data option_call_delta(struct _data *data);
extern struct _data option_put_delta(struct _data *data);
extern struct _data option_gamma(struct _data *dat);
extern struct _data option_vega(struct _data *dat);
extern struct _data option_call_theta(struct _data *dat);
extern struct _data option_put_theta(struct _data *dat);
extern struct _data option_call_rho(struct _data *dat);
extern struct _data option_put_rho(struct _data *dat);
extern struct _data future(struct _data *dat);
extern struct _data termstructure(struct _data *dat);
extern struct _data bonddispatch(struct _properties *properties);

extern const int sizeofoption_algorithms;
extern const struct option_algorithm option_algorithms[];
extern const struct _strike_control strike_control[];

/* tickers.c */
extern char strike_price_codes(const double strike);

extern int get_user_inputs(struct _properties *properties, struct _properties *future_properties);
extern int nonblockscan(int *control);
extern int select_model(struct _properties *properties);

extern void matrix(struct _properties *properties, struct _properties *future_properties);
extern void parameter_display(struct _properties *properties, struct _properties *future_properties);

extern int sanity_check(struct _properties *properties, char *statusMessage, const size_t n);

extern const int transextremeoptioncall[];
extern const struct _int_to_name namelistoptionsontheminmax2[];
extern const struct _int_to_name namelistTwoAssetBarrier[];
extern const int transextremeoptionput[];
extern const struct _int_to_name namelistpartialtimebarrier[];
extern const struct _int_to_name namelistimpliedtrinominaltree[];
extern const struct term_structure term_structure_list[];
extern const struct _int_to_name QuantLibnamelistamericanoreuropean[];

extern const struct _int_to_function funlistcall[];
extern const struct _int_to_function funlistput[];

extern const struct _int_to_name namefunlist[];
extern const struct _int_to_name namefunlist2[];

extern const struct _int_to_name nametestlist[];
extern const struct _int_to_name nametestlist2[];

extern int init_demo(struct _properties *properties);
extern int init_futures_demo(struct _properties *properties, struct _properties *future_properties);
extern int futures_demo(struct _properties *properties, struct _properties *future_properties, const int bPerpetual);
extern int options_demo(struct _properties *properties, const int bPerpetual);

extern int myusleep(const int useconds);
extern int SetToFuture(struct _properties *properties);
extern int SetToOption(struct _properties *properties);
extern int DoWeHaveFutures(const struct _properties *properties);
extern int DoWeHaveOptions(const struct _properties *properties);

extern void curses_process(struct _properties *properties, struct _properties *future_properties);

extern void logger(const char *name, const int num_args, ...);
extern void programExit(void);
extern void programInits(struct _properties *properties);

extern void process_arguments(const int argc, const char **argv, bool *debug);
extern void program_usage(const char *isGtkVersion);
extern void program_list_models(void);
extern void program_version(void);
extern void program_source(void);
extern void program_check_pricing_models(const bool quietMode, const bool debug);
extern void program_check_pricing_time(const int modelnumber, const int iterations);

extern bool process_arguments_checks(const int argc, const char **argv, bool *debug);
extern void program_version_checks();
extern void program_usage_checks();
