/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: defs.h of optionmatrix                                             */
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

#include "config.h"

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include <map>
#include <string>
#include <vector>

/* models to use. comment out to exclude */
#define ABRADFORD
#define SPINSKY
#define METAOPTIONS
#define FINRECIPES
#define QUANTLIB
#define DUMMYTESTMODELS     // For testing

#ifndef HAVE_LIBPTHREAD
# error Sorry, missing pthread library which is needed by this code
#endif

#ifdef HAVE_PTHREAD_H
# include <pthread.h>
#else
# error Sorry, this code requires <pthread.h>
#endif

#ifdef HAVE_LOCALE_H
# include <locale.h>
#else
# error Sorry, this code requires <locale.h>
#endif

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#else
# error Sorry, this code requires <stdlib.h>
#endif

#ifndef HAVE_LIBM
# error Sorry, this code requires the 'm' library (-lm)
#endif

#ifdef HAVE_MATH_H
# include <math.h>
#else
# error Sorry, this code requires <math.h>
#endif

#ifdef HAVE_FLOAT_H
# include <float.h>
#else
# error Sorry, this code requires <float.h>
#endif

#ifdef HAVE_STDDEF_H
# include <stddef.h>
#else
# error Sorry, this code requires <stddef.h>
#endif

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#else
# error Sorry, this code requires <unistd.h>
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif

#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#if defined(HAVE_GSL_GSL_ERRNO_H) && defined(HAVE_LIBGSL)
# include <gsl/gsl_errno.h>
#endif

#ifndef HAVE_MEMSET
# error Sorry, missing memset which is needed by this code
#endif

#ifndef HAVE_MODF
# error Sorry, missing modf which is needed by this code
#endif

#ifndef HAVE_POW
# error Sorry, missing pow which is needed by this code
#endif

#ifndef HAVE_SQRT
# error Sorry, missing sqrt which is needed by this code
#endif

#ifndef HAVE_LOCALECONV
# error Sorry, missing localeconv which is needed by this code
#endif

#if defined(HAVE_LIBGTK_3) || defined(HAVE_LIBGTK_X11_2_0)
# include "../gtk/gtk_include.h"
#endif

using namespace std;

enum { OPTION_CLASS = 0, FUTURES_CLASS, BOND_CLASS, TERMSTRUCTURE_CLASS };

// date securities via decimal/date entry dating or date to calendar engine ( e.g. 3rd friday + 1 )..
enum { DECIMALS, CALENDAR };

enum { LEG1, LEG2 };

// screen style formats
enum { 
       // begin screens for options
       DECIMAL_GREEKS = 0, DECIMAL_OPTIONS, 
       CALENDAR_OPTIONS1,  CALENDAR_OPTIONS2,
       CALENDAR_OPTIONS3,  CALENDAR_OPTIONS4,
       CALENDAR_OPTIONS5,  CALENDAR_OPTIONS6,
       CALENDAR_CUSTOM,
       OPTIONS_FORMAT_END,

       // begin screens for futures
       DECIMAL_FUTURE, CALENDAR_FUTURE,
       FUTURES_FORMAT_END,

       // next are properties, keep separate from formats
       // by FUTURES_FORMAT_END 

       DEMO_OPTIONS, DEMO_FUTURES, 
       OPTIONS_CALENDAR, FUTURES_CALENDAR,
       PROPERTIES,

       // always keep QUIT as last enum
       QUIT,

     };

enum { NORMAL_DISTRIBUTION = 0 };

enum { POLYNOMIAL_APPROX6, POLYNOMIAL_APPROX4, RATIONAL_APPROX7, RATIONAL_APPROX4, HART,
       ROMBERGS_METHOD, SIMPSONS_RULE, TRAPEZOID_RULE, ERF };

struct _data {

  // input data
  int modeltype;
  int term_model;

  double price;
  double strike;
  double rate;
  double volatility;
  double t[3];
  double dividend;

  pthread_mutex_t mutexCashflow;

  vector<double> amounts;
  vector<double> times;
  vector<double> times_adjusted;

  vector<double> coupon;
  vector<double> coupon_times;
  vector<double> coupon_times_adjusted;

  vector<double> principal;
  vector<double> principal_times;
  vector<double> principal_times_adjusted;

  vector<double> *generic_amounts;
  vector<double> *generic_times;
  vector<double> *generic_times_adjusted;

#ifdef FINRECIPES
  class term_structure_class *term;
#endif

  double UseZ;
  double UseB;
  double UseJ;
  double UseP;
  double UseQ;
  double UseR;
  double UseS;
  double UseT;
  int UsePound;  // '#'

  int steps;

  // computed data

  double te;  // time elapsed in decimal since user input to minus from t
  double te2; // time elapsed in decimal since user input to minus from t2
  double te3; // time elapsed in decimal since user input to minus from t3
  double te4;

  double call;
  double put;

  double future;

  double calldelta;
  double putdelta;

  double gamma;
  double vega;

  double calltheta;
  double puttheta;

  double callrho;
  double putrho;

  double callElasticity;
  double putElasticity;

  // Term Stuctures
  double discount_t1;
  double discount_t2;
  double spot_t1;
  double spot_t2;
  double forward;

  // Bonds
  double bond_price;
  double pv_discrete;
  double pv_continous;
  double irr;
  double irr_discrete;
  bool   uirr;
  double YTMDiscrete;
  double YTMContinous;
  double durationContinous;
  double durationDiscrete;

  double durationMacaulayDiscrete;
  double durationModifiedDiscrete;

  double convexityContinous;
  double convexityDiscrete;

  bool debug;
  bool isnan;

};

typedef std::map<std::string, int> treeToIndex;

struct _properties {
   
    struct _data data;

    int decimalorcalendar;

    int modeltype;
    int occurence_day;
    int occurence_in_month;
    int occurence_plus_offset;
    int expiration_hour,expiration_minute,expiration_second;
    unsigned int expiration_time;
    double adjusttime;
  
    // Leg 1 or single option or future
    int *time_to_expiration,*days_to_expiration,*expiration_month,*expiration_year,*start_time_to_expiration,*start_days_to_expiration,*start_expiration_month,*start_expiration_year;

    // Leg 2
    int *time_to_expiration2,*days_to_expiration2,*expiration_month2,*expiration_year2,*start_time_to_expiration2,*start_days_to_expiration2,*start_expiration_month2,*start_expiration_year2;

    // All Months 0, Jan cycle 1, Feb cycle 2, Mar cycle 3
    int optionscycle;
    int skipmonth;   // Leg 1
    int skipmonth2;  // Leg 2
    int day_offset_counter;
    double day_offset;

    time_t starttime;
    time_t starttime2;
    time_t starttime3;
    time_t starttime4;

    time_t updatetime;

    int calendarSelected;

    bool realTimeBleeding;
    int updatedelayseconds;
    bool highlightInTheMoney;
    bool spreads;
    bool filterNegativePrices;

    int precision;
    int strikestoogle;
    double customstrike;
    double strike_offset;
    double strike_offset2;
    double discard;
    bool verticalSpread;

    struct _int_to_name_nonconst *termstructure_name_list; 

    int format;

    int distribution_type;
    double distribution_mean;
    double distribution_variance;
    int integration_type;

    bool textExport;
    struct lconv * lc;

    char source_directory_prefix[1024];
    char data_dir[1024];

    // curses specific
    int start;
    int mode;               // incrementor/decrementor 1 = small, 2 = medium, 3 = large
    int demotype;

    // GTK+ specific
#if defined(HAVE_LIBGTK_3) || defined(HAVE_LIBGTK_X11_2_0)
    struct gtkinfo GtkInfo;
#endif

    // GTK+ specific
    struct elementListWithGroup *listModelsForGroups;
    treeToIndex TreeToIndex;

};

struct integratable_distributions {

  double (*constantvalue) (double);
  double (*integrationpart) (double,double,double);
  char   des[30];

};

// list of numerical integration methods
struct numerical_integration_method {

  double (*method) (const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3);

  char           des[30];
  mutable int    resolution;
  bool           allowOnlyEven;
  int            UpperLimit;

};

/* list of all financial models */
enum { 

#ifdef ABRADFORD

       BLACKSCHOLES,           // by Anthony Bradford 1
       MERTON73,               // by Anthony Bradford 2
       BLACK76,                // by Anthony Bradford 3

#endif

#ifdef SPINSKY

       AMERICAN_CRR,           // by Seth Pinsky 4
       AMERICAN_EQUIPROB,      // by Seth Pinsky 5
       EURO_CRR,               // by Seth Pinsky 6
       EURO_EQUIPROB,          // by Seth Pinsky 7

#endif

#ifdef METAOPTIONS
  
       BLACKSCHOLES2,              // by metaoptions 8
       GBS,                        // by metaoptions 9
       MERTON73B,                  // by metaoptions 10
       GFRENCH,                    // by metaoptions 11
       GCARRY,                     // by metaoptions 12
       BAWAMERICAN,                // by metaoptions 13
       BSAMERICAN,                 // by metaoptions 14
       BLACK76B,                   // by metaoptions 15
       ASSETORNOTHING,             // by metaoptions 16
       EXECUTIVE,                  // by metaoptions 17
       GARMANKOHLHAGEN,            // by metaoptions 18
       CASHORNOTHING,              // by metaoptions 19
       GAPOPTION,                  // by metaoptions 20
       SUPERSHARE,                 // by metaoptions 21
       SUPERSHARE2,                // by metaoptions 22
       VASICEKBONDPRICE,           // by metaoptions 23
       VASICEKBONDOPTION,          // by metaoptions 24
       TIMESWITCHOPTION,           // by metaoptions 25
       FOREQUOPTINDOMCUR,          // by metaoptions 26
       QUANTO,                     // by metaoptions 27
       EQUITYLINKEDFXO,            // by metaoptions 28
       SPREADAPPROXIMATION,        // by metaoptions 29
       JUMPDIFFUSION,              // by metaoptions 30
       BISECTION,                  // by metaoptions - computes volatility 31
       NEWTONRAPHSON,              // by metaoptions - computes volatility 32
       BAWBISECTION,               // by metaoptions - computes volatility 33
       BSBISECTION,                // by metaoptions - computes volatility 34
       AMERICANEXCHANGEOPTION,     // by metaoptions 35
       EUROPEANEXCHANGEOPTION,     // by metaoptions 36
       MILTERSENSWARTZ,            // by metaoptions 37
       PARTIALTIMETWOASSETBARRIER, // by metaoptions 38
       TAKEOVERFXOPTION,           // by metaoptions 39
       TWOASSETBARRIER,            // by metaoptions 40
       TWOASSETCASHORNOTHING,      // by metaoptions 41
       TWOASSETCORRELATION,        // by metaoptions 42
       FLOATINGSTRIKELOOKBACK,     // by metaoptions 43
       FLOATINGSTRIKELOOKBACK2,    // by metaoptions 44
       FIXEDSTRIKELOOKBACK,        // by metaoptions 45
       OPTIONSONTHEMAXMIN,         // by metaoptions 46
       STANDARDBARRIER,            // by metaoptions 47
       DOUBLEBARRIER,              // by metaoptions 48
       SOFTBARRIER,                // by metaoptions 49
       BINARYBARRIER,              // by metaoptions has 28 int states 50
       DISCRETEADJUSTEDBARRIER,    // by metaoptions 51

       // Crashes - Segmentation fault
       //BARRIERBINOMINAL,           // BarrierBinominal.c

       CONVERTIBLEBOND,            // ConvertibleBond.c 52
       CRRBINOMINAL,               // CRRBinominal.c 53

       // Missing Transpose() function...
       //IMPLIEDTRINOMINALTREE,      // ImpliedTrinominalTree.c  - computes volatility

       THREEDIMENSIONALBINOMINAL,  // ThreeDimensionalBinominal.c 54
       TRINOMINALTREE,             // TrinominalTree.c 55
       LOOKBARRIER,                // by metaoptions 56
       PARTIALTIMEBARRIER,         // has multiple text states, some call abort()? 57
       ROLLGESKEWHALEY,            // by metaoptions 58
       EXTREMESPREADOPTION,        // by metaoptions 59
       EXTREMESPREADOPTION2,       // by metaoptions 60
       PARTIALFIXEDLB,             // by metaoptions 61
       PARTIALFLOATLB,             // by metaoptions 62
       PARTIALFLOATLB2,            // by metaoptions 63
       EXTENDIBLEWRITER,           // by metaoptions 64
       CALLSONOPTIONS,             // by metaoptions OptionsOnOptions.c 65
       PUTSONOPTIONS,              // by metaoptions OptionsOnOptions.c 66
       LEVYASIAN,                  // by metaoptions 67
       GEOMETRICAVERAGERATEOPTION, // by metaoptions 68
       FORWARDSTARTOPTION,         // by metaoptions 69
       SWAPOPTION,                 // by metaoptions 70
       TURNBULLWAKEMANASIAN,       // by metaoptions 71

       // Crashes with positive dividend. Dividend disabled
       EXCHANGEEXCHANGEOPTION,     // by metaoptions 72
       SIMPLECHOOSER,              // by metaoptions 73
       COMPLEXCHOOSER,             // by metaoptions uses 3 bleeding time vars 74

#endif

#ifdef FINRECIPES

       BLACKSCHOLES3,          // option_price_call_black_scholes() 75
       PERPETUAL,              // option_price_american_perpetual_call() 76
       FUTOPTEURBLACK,         // futures_option_price_call_european_black() 77
       FUTOPTAMBINOMIAL,       // futures_option_price_call_american_binomial() 78

       // prototyped in fin_recipes.h but not defined in the library
       //AMERBJERKSUNDSTENSLAND, // option_price_american_call_approximated_bjerksund_stensland()

       AMERBINOMIAL,           // option_price_call_american_binomial() signature 1 without dividend 79
       AMERBINOMIALDIV,        // option_price_call_american_binomial() signature 2 with dividend 80
       AMERICANTRINOMIAL,      // option_price_call_american_trinomial() 81
       AMERBAW,                // option_price_american_call_approximated_baw() 82
       AMERPUTAPPROXJOHNSON,   // option_price_american_put_approximated_johnson() 83

#ifdef HAVE_LIBGSL

       AMERPUTAPPROXGESKEJOHNSON, // option_price_american_put_approximated_geske_johnson() 84
       HESTON,                    // heston_call_option_price() 85

#endif

       BONDZEROBLACK,          // bond_option_price_call_zero_black_scholes() 86
       BONDAMERBINOMIAL,       // bond_option_price_call_american_binomial() 87
       BOND_ZERO_AM_RENDLEMAN_BARTTER, // bond_option_price_call_zero_american_rendleman_bartter() 88
       BSPAYOUT,               // option_price_european_call_payout() 89
       EUROBIONMIAL,           // option_price_call_european_binomial() 90
       ASIANGEOMETRICAVG,      // option_price_asian_geometric_average_price_call() 91
       EUROLOOKBACK,           // option_price_european_lookback_call() 92
       EUROLOOKBACK2,          // option_price_european_lookback_call() 93
       MERTONJUMPDIFF,         // option_price_call_merton_jump_diffusion() 94
       CURRAMBINOMIAL,         // currency_option_price_call_american_binomial() 95
       CURREURO,               // currency_option_price_call_european() 96
       ROLLGESKEWHALEY2,       // option_price_american_call_one_dividend() 97
       EUROBINOMIAL1P,         // option_price_call_european_binomial_single_period() 98
       EUROBINOMIALMP,         // option_price_call_european_binomial_multi_period_given_ud() 99
       AMBINOMIAL,             // option_price_generic_binomial() 100
       EUROSIM,                // option_price_call_european_simulated() 101
       SIMEUROGENERIC,         // derivative_price_simulate_european_option_generic() 102
       SIMEUROGENERICCV,       // derivative_price_simulate_european_option_generic_with_control_variate() 103
       SIMEUROGENERICAV,       // derivative_price_simulate_european_option_generic_with_antithetic_variate() 104
       SIMPRICEPATH,           // derivative_price_simulate_european_option_generic() 105
       SIMPRICEPATHCONTROLVARIATE,  // derivative_price_simulate_european_option_generic_with_control_variate() 106
       DISTLOGRAND,            // simulate_lognormal_random_variable() 107
       AMFINITEDIFFEXP,        // option_price_call_american_finite_diff_explicit() 108
       EUROFINITEDIFFEXP,      // option_price_call_european_finite_diff_explicit() 109

#ifdef HAVE_NEWMAT_NEWMAT_H

       AMFINDIFFIMP,           // findiff_imp_am_call_newmat.cc findiff_imp_am_put_newmat.cc 110
       EURFINDDIFFIMP,         // findiff_imp_eur_call_newmat.cc findiff_imp_eur_put_newmat.cc 111

#endif

#ifdef HAVE_ITPP_ITBASE_H

       AMFINDIFFIMPPUT,        // option_price_put_american_finite_diff_implicit_itpp() 112

#endif

       // puts prototyped in fin_recipes.h but not defined in the library
       IMPLIEDNEWTON,          // option_price_implied_volatility_call_black_scholes_newton() 113

       // puts prototyped in fin_recipes.h but not defined in the library
       IMPLIEDBISECTIONS,      //option_price_implied_volatility_call_black_scholes_bisections() 114

       BONDZEROVASICEK,        // bond_option_price_call_zero_vasicek() 115
       EURODIVIDENDS,          // option_price_european_call_dividends() 116

       // Throws std::bad_alloc and freezes...
       //AMDISDIVSBINOMIAL,      // option_price_call_american_discrete_dividends_binomial()

       AMPROPORTDIVSBINOMIAL,  // option_price_call_american_proportional_dividends_binomial() 117
       BERMUDANBINOMIAL,       // option_price_call_bermudan_binomial() 118
       BSCOUPONBOND,           // bond_option_price_call_coupon_bond_black_scholes() 119
       WARRANT_NO_DIV,         // warrant_price_adjusted_black_scholes() 120
       WARRANT_DIV,            // warrant_price_adjusted_black_scholes() 121

       // Segmentation fault, To implement un-comment EURBOND_HO_LEE reference in defaults.c
       //EURBOND_HO_LEE,

       TERMFLAT,                // term_structure_class_flat.cc 122
       TERMCIR,                 // termstru_discfact_cir.cc 123
       TERMVASICEK,             // termstru_discfact_vasicek.cc 124
       TERMNELSONSIEGEL,        // termstru_yield_nelson_siegel.cc 125
       TERMSVENSSON,            // termstru_yield_svensson.cc 126
       TERMCUBICSPLINE,         // termstru_discfact_cubic_spline.cc 127
       TERMINTERPOLATED,        // termstru_yield_interpolated.cc 128

       // prototyped in fin_recipes_extra.h but not defined in the library
       //TERMDISESTCIR,          // term_structure_discount_factor_estimated_cir()

       // prototyped in fin_recipes_extra.h but not defined in the library
       //TERMYIELDBLISS          // term_structure_yield_bliss()

       /*
         Not implemented...

         termstru_transforms.cc
         
         simulate_european_options_generic_routine_price_sequence.cc:
                            vector<double>prices = 
                            simulate_lognormally_distributed_sequence(
                                    S,r,sigma,time,no_steps);

         vector< vector<double> > interest_rate_trees_gbm_build(
                            const double& r0,
                            const double& u,
                            const double& d,
                            const int& n);

         double interest_rate_trees_gbm_value_of_cashflows(
                            const vector<double>& cflow,
                            const vector< vector<double> >& r_tree,
                            const double& q);

         double interest_rate_trees_gbm_value_of_callable_bond(
                            const vector<double>& cflows,
                            const vector< vector<double> >& r_tree,
                            const double& q,
                            const int& first_call_time,
                            const double& call_price);

         vector< vector<term_structure_class_ho_lee> > 
                            term_structure_ho_lee_build_term_structure_tree(
                            term_structure_class* initial,
                            const int& no_steps,
                            const double& delta,
                            const double& pi);
        */


       FUTURES,                // futures_price() 129

#endif

#ifdef ABRADFORD

       FUTURES2,               // 130
       BACHELIER,              // 131
       BACHELIERMODIFIED,      // 132
       SPRENKLE,               // 133
       BONESS,                 // 134
       SAMUELSON,              // 135

#endif

#ifdef FINRECIPES

       BONDS,                  // 136
       BONDSTERM,              // 137
       BONDSPRINCIPAL,         // 138
       IRR,                    // 139

#endif

#ifdef HAVE_QL_QUANTLIB_HPP

       QUANTLIB_BLACKSCHOLES_EUROPEAN,                 // 140
       QUANTLIB_HESTON_SEMI_ANALYTIC_EUR,              // 141
       QUANTLIB_BARONE_ADESI_WHALEY_AM,                // 142
       QUANTLIB_BJERKSUND_STENSLAND_AM,                // 143
       QUANTLIB_FINITE_DIFFERENCES_EUROPEAN,           // 144
       QUANTLIB_FINITE_DIFFERENCES_AMERICAN,           // 145
       QUANTLIB_MC_CRUDE_EUR,                          // 146
       QUANTLIB_QMC_SOBOL_EUR,                         // 147
       QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM,              // 148
       QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM,           // 149
       QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM,   // 150
       QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM,     // 151
       QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM,            // 152
       QUANTLIB_BINOMIAL_TIAN_EUR_AM,                  // 153
       QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM,         // 154
       QUANTLIB_BINOMIAL_JOSHI_EUR_AM,                 // 155
       QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN,          // 156
       QUANTLIB_INTEGRAL_EUROPEAN,                     // 157
       QUANTLIB_FINITE_DIFFERENCES_BERMUDAN,           // 158
       QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN,         // 159
       QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN, // 160
       QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN,   // 161
       QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN,          // 162
       QUANTLIB_BINOMIAL_TIAN_BERMUDAN,                // 163
       QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN,       // 164
       QUANTLIB_BINOMIAL_JOSHI_BERMUDAN,               // 165

#endif

#ifdef DUMMYTESTMODELS

       TESTOPTION1,
       TESTOPTION2,
       TESTOPTION3,
       TESTOPTION4,
       TESTOPTION5,
       TESTOPTIONONEDIVIDEND1,
       TESTOPTIONONEDIVIDEND2,
       TESTFUTURES1,
       TESTFUTURES2,

#endif

};

/* _FUTURES is used for internal calendar control. Don't remove */
enum { _FUTURES = -1 };

struct _int_to_name          { const char string[30]; };
struct _int_to_name_nonconst { char string[30]; };
struct _int_to_function { double (*fun) (const double&, const double&); };

struct option_algorithm {

  int modeltype;
  char des[40];
  char source[80];
  char curses_des[240]; // 240 = 3 lines of text

  // source path should have a separator ';' to include multiple files in 1 reference...
  // there are instances where more than 2 source files need to be displayed...
  char sourceCode[200];
  char sourceCode2[200];
  char category[200];

  bool supportRealTime;

  int ReservedNotUsed1;
  bool supportCND;
  bool supportSteps;
  mutable int steps;
  int assetClass;
  bool perpetual;

  bool supportPrice;
  bool supportRate;
  bool supportVolatility;
  bool supportStrikes;
  bool ReservedNotUsed2;
  bool supportCalls;
  bool supportPuts;
  bool produceCallDelta; 
  bool producePutDelta; 
  bool produceGamma;
  bool produceVega;
  bool produceCallTheta;
  bool producePutTheta;
  bool produceCallRho;
  bool producePutRho;
  bool failsOnMeanVarianceChanges;

  /*
    supportDividend:
        0 - no dividend support
        1 - dividend supported
        2 - force initial default value of dividend
        3 - vector<double>& times, vector<double>& amounts
        4 - vector<double>& potential_exercise_times
        5 - vector<double>& coupon_times, vector<double>& coupon_amounts
        6 - vector<double>& coupon_times, vector<double>& coupon_amounts, 
            vector<double>& principal_times, vector<double>& principal_amounts
  */
  int supportDividend;
  double defaultDividend;
  char supportTime1des[50];
  /* 
     supportTime2
        0 - t2 not used
        1 - t2 used, model supports decimal/date entry dating and not calendar dating
        2 - t2 used, model supports decimal/date entry and calendar dating...
  */
  int supportTime2;
  char supportTime2des[50];

  int supportTime3;
  char supportTime3des[50];

  char price[50];
  char dividend[50];
  char call[50];
  char put[50];
  char strike[50];
  char volatility[50];

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseZ;
  bool bZallow0Negative;
  char UseZdes[50];
  double Zdefault;
  double Zmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseB;
  bool bBallow0Negative;
  char UseBdes[50];
  double Bdefault;
  double Bmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseJ;
  bool bJallow0Negative;
  char UseJdes[50];
  double Jdefault;
  double Jmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseP;
  bool bPallow0Negative;
  char UsePdes[50];
  double Pdefault;
  double Pmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseQ;
  bool bQallow0Negative;
  char UseQdes[50];
  double Qdefault;
  double Qmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseR;
  bool bRallow0Negative;
  char UseRdes[50];
  double Rdefault;
  double Rmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseS;
  bool bSallow0Negative;
  char UseSdes[50];
  double Sdefault;
  double Smax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseT;
  bool bTallow0Negative;
  char UseTdes[50];
  double Tdefault;
  double Tmax;  

  /* bUsePound '#' is for option states */
  int bUsePound;
  bool bPoundallow0Negative;
  char UsePounddes[50];
  int Pounddefault;
  int Poundmax;

  bool bUseStateNames;
  mutable const struct _int_to_name *StateNames;

};

struct _strike_control {

  double xcontrol;
  double incrementor;
  int strikes5or1;
  double retdiscard;
  char des[5];
  int precision;
  double sliderScale;

};

struct term_structure {
  int modeltype;
};

struct elementList
{
  char elementName[200];
};

struct elementListWithGroup
{
  char groupName[200];
  char elementName[200];
  int index;
};

const struct _int_to_name QuantLibnamelistamericanoreuropean[] = { { "American" }, { "European" } };
