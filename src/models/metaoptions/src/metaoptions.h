/*
    libmetaoptions - A collection of option-related functions. 
    Copyright (C) 2000-2006 B. Augestad, bjorn.augestad@gmail.com 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef METAOPTIONS_H
#define METAOPTIONS_H

#include <assert.h>

#ifdef NDEBUG
#define assert_equal(a, b) (1)
#else

/* At least temporarily */
#include <stdio.h>
#include <stdlib.h>

#define assert_equal(a, b)\
{\
	double x = fabs(a - b);\
	double maxdiff = 0.0001;\
	if(x > maxdiff) {\
		fprintf(stderr, "%s():%s(%d): assert_equal failed for values %.10g and %.10g\n",\
		__func__, __FILE__, __LINE__, a, b);\
		abort();\
	}\
}
#endif

/*
 * Local macros used to verify/sanity check the parameters
 * we receive from Excel. We don't want to call our functions
 * under all circumstances, so this is error checking with excel specific
 * reporting.
 */
#define VOLATILITY_MIN 0.0000001
#define VOLATILITY_MAX 100.99999

/* 
 * There are approx. 253 trading days per year. We allow for less time than one 
 * day to avoid rounding errors. Less than an hour is meaningless.
 * Max time is 20 (trading) years. Remember that t==1.0 == one trading year
 */
#define TIME_MIN (1.0/(253.0 * 24.0)) 
#define TIME_MAX (20.0)

/* 
 * Some sanity checks for interest rate. We cannot have negative rates
 * as that screws up the entire economic system. Not so sure about max values
 * because from time to time one gets insane rates. We set some kind of max anyway
 */
#define INTEREST_RATE_MIN 0.0 /* Zero is OK and happens from time to time, e.g. Japan */
#define INTEREST_RATE_MAX 1000.0 /* 100000% yearly is quite a lot */

/*
 * Strike and price min/max are equal. Nothing is free, so PRICE_MIN > 0.0
 * There's no theoretical upper bound for price, but we want to avoid infinity
 * and set a max price anyway.
 */
#define PRICE_MIN 0.000001
#define PRICE_MAX 1000000000000.0

#define STRIKE_MIN PRICE_MIN
#define STRIKE_MAX PRICE_MAX

/* 
 * Cost of carry is defined here.
 * I guess we could apply rules like COC <= INTEREST_RATE as noone would
 * ever buy something with a cost of carry > risk free rate. 
 * What about negative costs? Happens when underlying pays a yield greater
 * than risk free rate. 
 */
#define COST_OF_CARRY_MIN	-INTEREST_RATE_MAX
#define COST_OF_CARRY_MAX	INTEREST_RATE_MAX

/**
 * Some constants we use a lot.
 * The M_E and friends from math.h is not a part of the ANSI C standard,
 * so we add them here instead.
 * e, pi and sqrt(2*pi);
 * A common calculation is (1/sqrt2pi) *e, which equals e/sqr2pi.
 *
 * Use the gcc flag -Wshadow to locate scoping problems
 */
//static const double e = 2.7182818284590452354;
static const double pi = 3.14159265358979323846;	
static const double sqrt2pi = 2.50662827463100024161;
static const double e_div_sqrt2pi = 1.08443755141922748564;
static const double one_div_sqrt2pi = 0.39894228040143270286;

#if 0
static inline double pow2    (double n) { return n * n; }
static inline double normdist(double x) { return one_div_sqrt2pi * exp(-((x * x)/ 2.0)); }
#else
#define pow2(n) ((n) * (n))
#define normdist(x) ( one_div_sqrt2pi * exp(-(((x) * (x))/ 2.0)))
#endif



/*
 * Error checking macros, used to aid users of the library.
 * We define our own is_sane() macro which tests a double as much as possible.
 * Some platforms and standards have *very* poor support for this, namely C89.
 * This is the main reason we use our own function.
 */
#if 1
#define is_sane(a) ((a) == (a)) /* if not, it is NaN on many systems. */
#else
/* Windows version */
#include <float.h>
#define is_sane(a) (!_isnan((a)) && _finite((a)))
#endif

#if 0
/* More silly C89 shit, no fmin/fmax macros */
#define fmax(x, y) ((x) > (y) ? (x) : (y))
#define fmin(x, y) ((x) < (y) ? (x) : (y))
#endif


#define assert_valid_price(S)			assert(is_sane(S) && (S) >= PRICE_MIN && (S) <= PRICE_MAX)
#define assert_valid_strike(X)			assert(is_sane(X) && (X) >= STRIKE_MIN && (X) <= STRIKE_MAX)
#define assert_valid_time(T)			assert(is_sane(T) && (T) >= TIME_MIN && (T) <= TIME_MAX)
#define assert_valid_interest_rate(r)	assert(is_sane(r) && (r) >= INTEREST_RATE_MIN && (r) <= INTEREST_RATE_MAX)
#define assert_valid_cost_of_carry(b)	assert(is_sane(b) && (b) >= COST_OF_CARRY_MIN && (b) <= COST_OF_CARRY_MAX)
#define assert_valid_volatility(v)		assert(is_sane(v) && (v) >= VOLATILITY_MIN && v <= VOLATILITY_MAX)

/*
 * Parameter rules, naming conventions:
 * X - Strike
 * S - Stock price right now
 * T - Time to expiry as fraction of year. 6 months == 0.5, 9 months == 0.75
 * r - Risk free interest rate. 10% == 0.10
 * b - Cost of Carry. 10% == 0.10
 * v - Volatility, 30% == 0.30
 */

/* Cumulative normal distribution */
double cnd(double x);

/* Cumulative bivariate normal distribution */
double cbnd(double a, double b, double Rho);

extern double blackscholes(int fCall, double S, double X, double T, double r, double v);

/* gbs == generalized black & scholes */
extern double gbs(int fCall, double S, double X, double T, double r, double b, double v);
extern double gbs_put(double S, double X, double T, double r, double b, double v);
extern double gbs_call(double S, double X, double T, double r, double b, double v);

extern double delta(int fCall, double S, double X, double T, double r, double b, double v);
extern double delta_put(double S, double X, double T, double r,  double b, double v);
extern double delta_call(double S, double X, double T, double r,  double b, double v);

extern double Gamma(double S, double X, double T, double r, double b, double v);

extern double carry(int fCall, double S, double X, double T, double r, double b, double v);
extern double carry_put(double S, double X, double T, double r, double b, double v); 
extern double carry_call(double S, double X, double T, double r, double b, double v);

extern double theta(int fCall, double S, double X, double T, double r, double b, double v);
extern double theta_put(double S, double X, double T, double r, double b, double v); 
extern double theta_call(double S, double X, double T, double r, double b, double v);

extern double rho(int fCall, double S, double X, double T, double r, double b, double v);
extern double rho_put(double S, double X, double T, double r, double b, double v);
extern double rho_call(double S, double X, double T, double r, double b, double v);

extern double black76(int fCall, double F, double X, double T, double r, double v);
extern double black76_put(double F, double X, double T, double r, double v); 
extern double black76_call(double F, double X, double T, double r, double v); 

extern double blackscholes_put(double S, double X, double T, double r, double v); 
extern double blackscholes_call(double S, double X, double T, double r, double v); 

extern double french(int fCall, double S, double X, double T, double t1, double r, double b, double v);
extern double french_put(double S, double X, double T, double t1, double r, double b, double v);
extern double french_call(double S, double X, double T, double t1, double r, double b, double v);

extern double vega(double S, double X, double T, double r, double b, double v);

/* American Calls on stocks with known dividends, Roll-Geske-Whaley */
    /*t1 time to dividend payout */
    /*T2 time to option expiration */
double RollGeskeWhaley(
	double S,
	double X,
	double t1,
	double T2,
	double r,
	double d,
	double v);

/* The Barone-Adesi and Whaley (1987) American approximation */
double BAWAmericanApprox(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v);

/* The Bjerksund and Stensland (1993) American approximation */
double BSAmericanApprox(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v);

/* Partial-time fixed strike lookback options */
double PartialFixedLB(
	int fCall,
	double S,
	double X,
	double t1,
	double T2,
	double r,
	double b,
	double v);

double EuropeanExchangeOption(
	double S1,
	double S2,
	double Q1,
	double Q2,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho);

double AmericanExchangeOption(
	int fCall,
	double S1,
	double S2,
	double Q1,
	double Q2,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho);

extern double AssetOrNothing_put(double S, double X, double T, double r, double b, double v);
extern double AssetOrNothing_call(double S, double X, double T, double r, double b, double v);
extern double AssetOrNothing(int fCall, double S, double X, double T, double r, double b, double v);

double BSAmericanCallApprox(
	double S,
	double X,
	double T,
	double r,
	double b,
	double v);

double CashOrNothing(
	int fCall,
	double S,
	double X,
	double K,
	double T,
	double r,
	double b,
	double v);

double ComplexChooser(
	double S,
	double Xc,
	double Xp,
	double T,
	double Tc, 
	double Tp,
	double r,
	double b,
	double v);

double EquityLinkedFXO(
	int fCall,
	double E,
	double S,
	double X,
	double T,
	double r,
	double rf,
	double q,
	double vS,
	double vE,
	double Rho);

extern double Executive_call(double S, double X, double T, double r, double b, double v, double lambda);
extern double Executive_put(double S, double X, double T, double r, double b, double v, double lambda);
extern double Executive(int fCall, double S, double X, double T, double r, double b, double v, double lambda);

double ExchangeExchangeOption(
	int TypeFlag,
	double S1,
	double S2,
	double q,
	double t1,
	double T2,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho);

double ExtendibleWriter(
	int fCall,
	double S,
	double X1,
	double X2,
	double t1,
	double T2,
	double r,
	double b,
	double v);



/*
 * We have four different types of extreme spread options, the regular put/call
 * as well as extreme or "reverse extreme". We use some defined constants for this.
 * Use one of them as typeflag.
 */
#define ESO_CALL			1
#define ESO_PUT				2
#define ESO_REVERSE_CALL	3
#define ESO_REVERSE_PUT		4
double ExtremeSpreadOption(
	int TypeFlag,
	double S,
	double SMin,
	double SMax,
	double t1,
	double T,
	double r,
	double b,
	double v); 

double FixedStrikeLookback(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double X,
	double T,
	double r,
	double b,
	double v);

double FloatingStrikeLookback(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double T,
	double r,
	double b,
	double v);


double ForEquOptInDomCur(
	int fCall,
	double E,
	double S,
	double X,
	double T,
	double r,
	double q,
	double vS,
	double vE,
	double Rho);

double ForwardStartOption(
	int fCall,
	double S,
	double alpha,
	double t1,
	double T,
	double r,
	double b,
	double v);

double GapOption(
	int fCall,
	double S,
	double X1,
	double X2,
	double T,
	double r,
	double b,
	double v);

double GeometricAverageRateOption(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double r,
	double b,
	double v);

double JumpDiffusion(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double v,
	double lambda,
	double gamma_val);

double LevyAsian(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double r,
	double b,
	double v);

double MiltersenSchwartz(
	int fCall,
	double Pt,
	double FT,
	double X,
	double t1,
	double T2,
	double vS,
	double vE,
	double vf,
	double rhoSe,
	double rhoSf,
	double rhoef,
	double Kappae,
	double Kappaf);

double OptionsOnTheMaxMin(
	const char* TypeFlag,
	double S1,
	double S2,
	double X,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho);

/* We can have a couple of combinations for OoO, 
 * and use an integer to define the combos. No enums since
 * that makes it harder to call the function from other languages.
 */
#define OOO_PUT_ON_CALL		1
#define OOO_CALL_ON_CALL	2
#define OOO_PUT_ON_PUT 		3
#define OOO_CALL_ON_PUT		4
double OptionsOnOptions(
	int typeflag,
	double S,
	double X1,
	double X2,
	double t1,
	double T2,
	double r,
	double b,
	double v);

double PartialFloatLB(
	int fCall,
	double S,
	double SMin,
	double SMax,
	double t1,
	double T2,
	double r,
	double b,
	double v,
	double lambda);


/*************** BARRIER FORMULAS START ******************/
double BinaryBarrier(
	int TypeFlag,
	double S,
	double X,
	double H,
	double K,
	double T,
	double r,
	double b,
	double v,
	int eta,
	int phi);

/* We have 4 types of DoubleBarrier options, defined here */
#define DB_PUT_IN		1
#define DB_PUT_OUT		2
#define DB_CALL_IN		3
#define DB_CALL_OUT		4
double DoubleBarrier(
	int TypeFlag,
	double S,
	double X,
	double L,
	double U,
	double T,
	double r,
	double b,
	double v,
	double delta1,
	double delta2);


double DiscreteAdjustedBarrier(double S, double H, double v, double dt);
/*
 * Option types for StandardBarrier(), LookBarrier(),
 * PartialTimeTwoAssetBarrier() and SoftBarrier() .
 * LookBarrier() accepts 
 * 		SB_CALL_UP_OUT, 
 * 		SB_PUT_DOWN_OUT, 
 * 		SB_CALL_UP_IN and 
 * 		SB_PUT_DOWN_IN
 * BarrierBinominal() uses: 
 * 		SB_CALL_UP_OUT, 
 * 		SB_CALL_DOWN_OUT, 
 * 		SB_PUT_UP_OUT, 
 * 		SB_PUT_DOWN_OUT
 */
#define SB_CALL_DOWN_IN		1
#define SB_CALL_DOWN_OUT	2
#define SB_CALL_UP_IN		3
#define SB_CALL_UP_OUT		4
#define SB_PUT_DOWN_IN		5
#define SB_PUT_DOWN_OUT		6
#define SB_PUT_UP_IN		7
#define SB_PUT_UP_OUT		8
double StandardBarrier(
	int typeflag,
	double S,
	double X,
	double H,
	double K,
	double T,
	double r,
	double b,
	double v);

double SoftBarrier(
	int typeflag,
	double S,
	double X,
	double L,
	double U,
	double T,
	double r,
	double b,
	double v); 

double PartialTimeTwoAssetBarrier(
	int typeflag,
	double S1,
	double S2,
	double X,
	double H,
	double t1,
	double T2,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho);

double LookBarrier(
	int type,
	double S,
	double X,
	double H,
	double t1,
	double T2,
	double r,
	double b,
	double v);

extern double BarrierBinomial(
	int EuropeanOption,
	int type,
	double S,
	double X,
	double H,
	double T,
	double r,
	double b,
	double v,
	int n);



/*
 * Partial time barrier accepts the following option types:
 * NOTE: See the TODO file ASAP, as in Before you do anything else.
 */
#define PTB_CALL_UP_OUT_A		1
#define PTB_CALL_DOWN_OUT_A		2
#define PTB_CALL_DOWN_OUT_B1	3
#define PTB_CALL_DOWN_OUT_B2	4
#define PTB_CALL_UP_OUT_B2		5
#define PTB_CALL_OUT_B1			6
#define PTB_PUT_DOWN_OUT_A		7
#define PTB_PUT_UP_OUT_A		8
#define PTB_PUT_OUT_B1			9
#define PTB_PUT_DOWN_OUT_B2		10

double PartialTimeBarrier(
	const char* TypeFlag,
	double S,
	double X,
	double H,
	double t1,
	double T2,
	double r,
	double b,
	double v);

double TwoAssetBarrier(
	int type,
	double S1,
	double S2,
	double X,
	double H,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho); 

/*************** BARRIER FORMULAS END  ******************/

double Quanto(
	int fCall,
	double Ep,
	double S,
	double X,
	double T,
	double r,
	double rf,
	double q,
	double vS,
	double vE,
	double Rho); 

double SimpleChooser(
	double S,
	double X,
	double t1,
	double T2,
	double r,
	double b,
	double v); 

double SpreadApproximation(
	int fCall,
	double f1,
	double f2,
	double X,
	double T,
	double r,
	double v1,
	double v2,
	double Rho); 

double SuperShare(
	double S,
	double XL,
	double XH,
	double T,
	double r,
	double b,
	double v); 

double TakeoverFXoption(
	double v,
	double b,
	double E,
	double X,
	double T,
	double r,
	double rf,
	double vV,
	double vE,
	double Rho); 

double TimeSwitchOption(
	int fCall,
	double S,
	double X,
	double a,
	double T,
	int m ,
	double dt,
	double r,
	double b,
	double v); 

double TurnbullWakemanAsian(
	int fCall,
	double S,
	double SA,
	double X,
	double T,
	double T2,
	double tau,
	double r,
	double b,
	double v); 

double TwoAssetCashOrNothing(
	int TypeFlag,
	double S1,
	double S2,
	double X1,
	double X2,
	double K,
	double T,
	double r, 
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho); 

extern double TwoAssetCorrelation(
	int fCall,
	double S1,
	double S2,
	double X1,
	double X2,
	double T,
	double b1,
	double b2,
	double r,
	double v1,
	double v2,
	double Rho);

extern double merton73(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double q,
	double v); 

extern double GarmanKohlhagen(
	int fCall,
	double S,
	double X,
	double T,
	double r,	/* Risk free rate for the currency */
	double rf,	/* Risk free rate for the foreign currency */
	double v); 

/* Find the Implied Volatility for a european stock option */
extern int NewtonRaphson(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double cm,
	double *piv);

extern int NewtonRaphson_put(
	double S,
	double X,
	double T,
	double r,
	double cm,
	double *piv);

extern int NewtonRaphson_call(
	double S,
	double X,
	double T,
	double r,
	double cm,
	double *piv);

/* Black-76 European swap option */
extern double Swapoption(
	int fCall,
	double t1,
	double m,
	double F,
	double X,
	double T,
	double r,
	double v);

extern double VasicekBondPrice(
	double t1,
	double T,
	double r,
	double Theta,
	double Kappa,
	double v);

double VasicekBondOption(
	int fCall,
	double F,
	double X,
	double tau,
	double T,
	double r,
	double Theta,
	double kappa,
	double v);

/* 
 * Bisection algorithm for finding IV 
 * using BAWAmericanApprox() to compute value.
 */
extern double BAWbisection(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double price);

extern double BSbisection(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double price);

extern int bisection(
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double price,
	double *piv);

/* Cox-Ross-Rubinstein binomial tree */
extern double CRRBinomial(
	int EuropeanOption,
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v,
	int n);

/* Convertible bonds in binomial trees.
 * T2: Time to maturity 
 * t1: Time to to first conversion date, only used when the option is American 
 * k   Issuer's credit spread above risk-free return(similar Treasuries). 
 * q   Stock dividend yield 
 * v:  Stock volatility 
 * n:  Number of time-steps in the tree 
 * F   Bond face value 
 */

extern double ConvertibleBond(
	int EuropeanOption,
	double S,
	double X,
	double T2,
	double t1,
	double r,
	double k,
	double q,
	double v,
	double F,
	double Coupon,
	int n);

extern double TrinomialTree(
	int EuropeanOption,
	int fCall,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v,
	double n);

/*
 * The TypeFlag can have 7 different values, from 1..7.
 * The TDB_ prefix is short for ThreeDimensionalBinominal_
 * As usual, we don't use an enum to support more (calling) languages.
 */
#define TDB_SPREAD_OPTION 				1
#define TDB_OPTION_ON_THE_MAX			2 /* between two assets */
#define TDB_OPTION_ON_THE_MIN			3 /* between two assets */
#define TDB_DUAL_STRIKE_OPTION			4
#define TDB_REVERSE_DUAL_STRIKE_OPTION	5
#define TDB_PORTFOLIO_OPTION			6
#define TDB_EXCHANGE_OPTION				7

#define TDB_OPTIONTYPE_MIN				1
#define TDB_OPTIONTYPE_MAX				7

extern double ThreeDimensionalBinomial(
	int type,
	int EuropeanOption,
	int fCall,
	double S1,
	double S2,
	double Q1,
	double Q2,
	double X1,
	double X2,
	double T,
	double r,
	double b1,
	double b2,
	double v1,
	double v2,
	double Rho,
	int n);

extern double ImpliedTrinomialTree(
	const char* ReturnFlag,
	int STEPn,
	int STATEi,
	double S,
	double X,
	double T,
	double r,
	double b,
	double v,
	double Skew,
	int nSteps);

#endif


