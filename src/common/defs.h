/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: defs.h of optionmatrix                                             */
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

#include "config.h"

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#include <map>
#include <string>
#include <vector>

#include "environment.h"

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

#ifndef QUANTLIB
# undef HAVE_QL_QUANTLIB_HPP
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

  bool filterNegativePrices;

}; // struct _data {

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
    bool fileExport;

    struct lconv * lc;

    char source_directory_prefix[PATH_MAX*2];
    char data_dir[PATH_MAX*2];

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

}; // struct _properties {

struct integratable_distributions {

  double (*constantvalue) (const double);
  double (*integrationpart) (const double,const double, const double);
  const char des[256];

};

// list of numerical integration methods
struct numerical_integration_method {

  double (*method) (const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3);

  const char           des[256];
  mutable int          resolution;
  const bool           allowOnlyEven;
  const int            UpperLimit;

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
       BARRIERBINOMINAL,           // by metaoptions BarrierBinominal.c 52
       CONVERTIBLEBOND,            // by metaoptions ConvertibleBond.c 53
       CRRBINOMINAL,               // by metaoptions CRRBinominal.c 54

       // Missing Transpose() function...
       //IMPLIEDTRINOMINALTREE,      // ImpliedTrinominalTree.c  - computes volatility

       THREEDIMENSIONALBINOMINAL,  // ThreeDimensionalBinominal.c 55
       TRINOMINALTREE,             // TrinominalTree.c 56
       LOOKBARRIER,                // by metaoptions 57
       PARTIALTIMEBARRIER,         // has multiple text states, some call abort()? 58
       ROLLGESKEWHALEY,            // by metaoptions 59
       EXTREMESPREADOPTION,        // by metaoptions 60
       EXTREMESPREADOPTION2,       // by metaoptions 61
       PARTIALFIXEDLB,             // by metaoptions 62
       PARTIALFLOATLB,             // by metaoptions 63
       PARTIALFLOATLB2,            // by metaoptions 64
       EXTENDIBLEWRITER,           // by metaoptions 65
       CALLSONOPTIONS,             // by metaoptions OptionsOnOptions.c 66
       PUTSONOPTIONS,              // by metaoptions OptionsOnOptions.c 67
       LEVYASIAN,                  // by metaoptions 68
       GEOMETRICAVERAGERATEOPTION, // by metaoptions 69
       FORWARDSTARTOPTION,         // by metaoptions 70
       SWAPOPTION,                 // by metaoptions 71
       TURNBULLWAKEMANASIAN,       // by metaoptions 72

       // Crashes with positive dividend. Dividend disabled
       EXCHANGEEXCHANGEOPTION,     // by metaoptions 73
       SIMPLECHOOSER,              // by metaoptions 74
       COMPLEXCHOOSER,             // by metaoptions uses 3 bleeding time vars 75

#endif

#ifdef FINRECIPES

       BLACKSCHOLES3,          // option_price_call_black_scholes() 76
       PERPETUAL,              // option_price_american_perpetual_call() 77
       FUTOPTEURBLACK,         // futures_option_price_call_european_black() 78
       FUTOPTAMBINOMIAL,       // futures_option_price_call_american_binomial() 79

       // prototyped in fin_recipes.h but not defined in the library
       //AMERBJERKSUNDSTENSLAND, // option_price_american_call_approximated_bjerksund_stensland()

       AMERBINOMIAL,           // option_price_call_american_binomial() signature 1 without dividend 80
       AMERBINOMIALDIV,        // option_price_call_american_binomial() signature 2 with dividend 81
       AMERICANTRINOMIAL,      // option_price_call_american_trinomial() 82
       AMERBAW,                // option_price_american_call_approximated_baw() 83
       AMERPUTAPPROXJOHNSON,   // option_price_american_put_approximated_johnson() 84

#ifdef HAVE_LIBGSL

       AMERPUTAPPROXGESKEJOHNSON, // option_price_american_put_approximated_geske_johnson() 85
       HESTON,                    // heston_call_option_price() 86

#endif

       BONDZEROBLACK,          // bond_option_price_call_zero_black_scholes() 87
       BONDAMERBINOMIAL,       // bond_option_price_call_american_binomial() 88
       BOND_ZERO_AM_RENDLEMAN_BARTTER, // bond_option_price_call_zero_american_rendleman_bartter() 89
       BSPAYOUT,               // option_price_european_call_payout() 90
       EUROBIONMIAL,           // option_price_call_european_binomial() 91
       ASIANGEOMETRICAVG,      // option_price_asian_geometric_average_price_call() 92
       EUROLOOKBACK,           // option_price_european_lookback_call() 93
       EUROLOOKBACK2,          // option_price_european_lookback_call() 94
       MERTONJUMPDIFF,         // option_price_call_merton_jump_diffusion() 95
       CURRAMBINOMIAL,         // currency_option_price_call_american_binomial() 96
       CURREURO,               // currency_option_price_call_european() 97
       ROLLGESKEWHALEY2,       // option_price_american_call_one_dividend() 98
       EUROBINOMIAL1P,         // option_price_call_european_binomial_single_period() 99
       EUROBINOMIALMP,         // option_price_call_european_binomial_multi_period_given_ud() 100
       AMBINOMIAL,             // option_price_generic_binomial() 101
       EUROSIM,                // option_price_call_european_simulated() 102
       SIMEUROGENERIC,         // derivative_price_simulate_european_option_generic() 103
       SIMEUROGENERICCV,       // derivative_price_simulate_european_option_generic_with_control_variate() 104
       SIMEUROGENERICAV,       // derivative_price_simulate_european_option_generic_with_antithetic_variate() 105
       SIMPRICEPATH,           // derivative_price_simulate_european_option_generic() 106
       SIMPRICEPATHCONTROLVARIATE,  // derivative_price_simulate_european_option_generic_with_control_variate() 107
       DISTLOGRAND,            // simulate_lognormal_random_variable() 108
       AMFINITEDIFFEXP,        // option_price_call_american_finite_diff_explicit() 109
       EUROFINITEDIFFEXP,      // option_price_call_european_finite_diff_explicit() 110

#ifdef HAVE_NEWMAT_NEWMAT_H

       AMFINDIFFIMP,           // findiff_imp_am_call_newmat.cc findiff_imp_am_put_newmat.cc 111
       EURFINDDIFFIMP,         // findiff_imp_eur_call_newmat.cc findiff_imp_eur_put_newmat.cc 112

#endif

#ifdef HAVE_ITPP_ITBASE_H

       AMFINDIFFIMPPUT,        // option_price_put_american_finite_diff_implicit_itpp() 113

#endif

       // puts prototyped in fin_recipes.h but not defined in the library
       IMPLIEDNEWTON,          // option_price_implied_volatility_call_black_scholes_newton() 114

       // puts prototyped in fin_recipes.h but not defined in the library
       IMPLIEDBISECTIONS,      //option_price_implied_volatility_call_black_scholes_bisections() 115

       BONDZEROVASICEK,        // bond_option_price_call_zero_vasicek() 116
       EURODIVIDENDS,          // option_price_european_call_dividends() 117

       AMDISDIVSBINOMIAL,      // option_price_call_american_discrete_dividends_binomial() 118
       AMPROPORTDIVSBINOMIAL,  // option_price_call_american_proportional_dividends_binomial() 119
       BERMUDANBINOMIAL,       // option_price_call_bermudan_binomial() 120
       BSCOUPONBOND,           // bond_option_price_call_coupon_bond_black_scholes() 121
       WARRANT_NO_DIV,         // warrant_price_adjusted_black_scholes() 122
       WARRANT_DIV,            // warrant_price_adjusted_black_scholes() 123
       EURBOND_HO_LEE,         // 124

       TERMFLAT,                // term_structure_class_flat.cc 125
       TERMCIR,                 // termstru_discfact_cir.cc 126
       TERMVASICEK,             // termstru_discfact_vasicek.cc 127
       TERMNELSONSIEGEL,        // termstru_yield_nelson_siegel.cc 128
       TERMSVENSSON,            // termstru_yield_svensson.cc 129
       TERMCUBICSPLINE,         // termstru_discfact_cubic_spline.cc 130
       TERMINTERPOLATED,        // termstru_yield_interpolated.cc 131

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


       FUTURES,                // futures_price() 132

#endif

#ifdef ABRADFORD

       FUTURES2,               // 133
       BACHELIER,              // 134
       BACHELIERMODIFIED,      // 135
       SPRENKLE,               // 136
       BONESS,                 // 137
       SAMUELSON,              // 138

#endif

#ifdef FINRECIPES

       BONDS,                  // 139
       BONDSTERM,              // 140
       BONDSPRINCIPAL,         // 141
       IRR,                    // 142

#endif

#ifdef HAVE_QL_QUANTLIB_HPP

       QUANTLIB_BLACKSCHOLES_EUROPEAN,                 // 143
       QUANTLIB_HESTON_SEMI_ANALYTIC_EUR,              // 144
       QUANTLIB_BARONE_ADESI_WHALEY_AM,                // 145
       QUANTLIB_BJERKSUND_STENSLAND_AM,                // 146
       QUANTLIB_FINITE_DIFFERENCES_EUROPEAN,           // 147
       QUANTLIB_FINITE_DIFFERENCES_AMERICAN,           // 148
       QUANTLIB_MC_CRUDE_EUR,                          // 149
       QUANTLIB_QMC_SOBOL_EUR,                         // 150
       QUANTLIB_MC_LONGSTAFF_SCHWARTZ_AM,              // 151
       QUANTLIB_BINOMIAL_JARROW_RUDD_EUR_AM,           // 152
       QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_EUR_AM,   // 153
       QUANTLIB_ADDITIVE_EQUIPROBABILITIES_EUR_AM,     // 154
       QUANTLIB_BINOMIAL_TRIGEORGIS_EUR_AM,            // 155
       QUANTLIB_BINOMIAL_TIAN_EUR_AM,                  // 156
       QUANTLIB_BINOMIAL_LEISEN_REIMER_EUR_AM,         // 157
       QUANTLIB_BINOMIAL_JOSHI_EUR_AM,                 // 158
       QUANTLIB_BATES_SEMI_ANALYTIC_EUROPEAN,          // 159
       QUANTLIB_INTEGRAL_EUROPEAN,                     // 160
       QUANTLIB_FINITE_DIFFERENCES_BERMUDAN,           // 161
       QUANTLIB_BINOMIAL_JARROW_RUDD_BERMUDAN,         // 162
       QUANTLIB_BINOMIAL_COX_ROSS_RUBINSTEIN_BERMUDAN, // 163
       QUANTLIB_ADDITIVE_EQUIPROBABILITIES_BERMUDAN,   // 164
       QUANTLIB_BINOMIAL_TRIGEORGIS_BERMUDAN,          // 165
       QUANTLIB_BINOMIAL_TIAN_BERMUDAN,                // 166
       QUANTLIB_BINOMIAL_LEISEN_REIMER_BERMUDAN,       // 167
       QUANTLIB_BINOMIAL_JOSHI_BERMUDAN,               // 168
       QUANTLIB_DISCRETE_AVERAGE_ASIAN,                // 169
       QUANTLIB_CONTINUOUS_AVERAGING_ASIAN,            // 170
       QUANTLIB_CONTINUOUS_LEVY_ASIAN,                 // 171

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

struct _int_to_name          { const char string[256]; };
struct _int_to_name_nonconst { char string[256]; };
struct _int_to_function { double (*fun) (const double&, const double&); };

struct option_algorithm {

  int modeltype;
  char des[256];
  char source[PATH_MAX*2];
  char curses_des[240]; // 240 = 3 lines of text

  // source path should have a separator ';' to include multiple files in 1 reference...
  // there are instances where more than 2 source files need to be displayed...
  char sourceCode[PATH_MAX*2];
  char sourceCode2[PATH_MAX*2];
  char category[256];

  bool supportRealTime;
  mutable bool filterNegativePrices;

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
  bool produceCallElasticity;
  bool producePutElasticity;
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
  char supportTime1des[256];
  /* 
     supportTime2
        0 - t2 not used
        1 - t2 used, model supports decimal/date entry dating and not calendar dating
        2 - t2 used, model supports decimal/date entry and calendar dating...
  */
  int supportTime2;
  char supportTime2des[256];

  int supportTime3;
  char supportTime3des[256];

  char price[256];
  char dividend[256];
  char call[256];
  char put[256];
  char strike[256];
  char volatility[256];

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseZ;
  bool bZallow0Negative;
  char UseZdes[256];
  double Zdefault;
  double Zmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseB;
  bool bBallow0Negative;
  char UseBdes[256];
  double Bdefault;
  double Bmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseJ;
  bool bJallow0Negative;
  char UseJdes[256];
  double Jdefault;
  double Jmax;

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseP;
  bool bPallow0Negative;
  char UsePdes[256];
  double Pdefault;
  double Pmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseQ;
  bool bQallow0Negative;
  char UseQdes[256];
  double Qdefault;
  double Qmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseR;
  bool bRallow0Negative;
  char UseRdes[256];
  double Rdefault;
  double Rmax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseS;
  bool bSallow0Negative;
  char UseSdes[256];
  double Sdefault;
  double Smax;  

  /*
    0 = not used
    1 = used as double
    2 = used as int
  */
  int iUseT;
  bool bTallow0Negative;
  char UseTdes[256];
  double Tdefault;
  double Tmax;  

  /* bUsePound '#' is for option states */
  int bUsePound;
  bool bPoundallow0Negative;
  char UsePounddes[256];
  int Pounddefault;
  int Poundmax;

  bool bUseStateNames;
  mutable const struct _int_to_name *StateNames;

};

struct _strike_control {

  const double xcontrol;
  const double incrementor;
  const int strikes5or1;
  const double retdiscard;
  const char des[256];
  const int precision;
  const double sliderScale;

};

struct term_structure {
  int modeltype;
};

struct elementList
{
  char elementName[256];
};

struct elementListWithGroup
{
  char groupName[256];
  char elementName[256];
  int index;
};

const struct _int_to_name QuantLibnamelistamericanoreuropean[] = { { "American" }, { "European" } };
