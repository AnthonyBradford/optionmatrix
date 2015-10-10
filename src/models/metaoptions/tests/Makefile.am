#AUTOMAKE_OPTIONS = subdir-objects
FM = -ffast-math

TESTS = check_options\
	CashOrNothing_check\
	bisection_check\
	NewtonRaphson_check\
	RollGeskeWhaley_check\
	cnd_check\
	cbnd_check\
	ExtremeSpreadOption_check\
	PartialFloatLB_check \
	PartialFixedLB_check \
	FloatingStrikeLookback_check\
	StandardBarrier_check\
	DoubleBarrier_check\
	LevyAsian_check\
	SoftBarrier_check\
	BinaryBarrier_check\
	JumpDiffusion_check\
	EuropeanExchangeOption_check\
	AmericanExchangeOption_check\
	ExchangeExchangeOption_check\
	gbs_check\
	quanto_check\
	gtheta_check\
	gdelta_check\
	ggamma_check\
	gvega_check\
	gcarry_check\
	grho_check\
	blackscholes_check\
	black76_check\
	ExtendibleWriter_check\
	MiltersenSchwartz_check\
	FixedStrikeLookback_check\
	Executive_check\
	SuperShare_check\
	TwoAssetBarrier_check\
	AssetOrNothing_check\
	ComplexChooser_check\
	GapOption_check\
	SimpleChooser_check\
	Swapoption_check\
	BSAmericanApprox_check\
	SpreadApproximation_check\
	EquityLinkedFXO_check\
	ForwardStartOption_check\
	OptionsOnOptions_check\
	BAWbisection_check\
	ForEquOptInDomCur_check\
	GeometricAverageRateOption_check\
	DiscreteAdjustedBarrier_check\
	PartialTimeBarrier_check\
	OptionsOnTheMaxMin_check\
	TakeoverFXoption_check\
	TwoAssetCashOrNothing_check\
	TwoAssetCorrelation_check\
	GarmanKohlhagen_check\
	merton73_check

# These checks are omitted until further investigation...
#	TurnbullWakemanAsian_check\
#	BAWAmericanApprox_check\
#	gfrench_check\
#	TimeSwitchOption_check\
#	BSbisection_check\
#	LookBarrier_check\
#	VasicekBondPrice_check\
#	VasicekBondOption_check\
#	PartialTimeTwoAssetBarrier_check

check_PROGRAMS= $(TESTS)

noinst_PROGRAMS = check_options ExtremeSpreadOption_check PartialFloatLB_check PartialFixedLB_check FixedStrikeLookback_check FloatingStrikeLookback_check BAWAmericanApprox_check StandardBarrier_check PartialTimeTwoAssetBarrier_check cbnd_check cnd_check LookBarrier_check DoubleBarrier_check SoftBarrier_check LevyAsian_check BinaryBarrier_check JumpDiffusion_check AmericanExchangeOption_check EuropeanExchangeOption_check MiltersenSchwartz_check ExchangeExchangeOption_check SuperShare_check NewtonRaphson_check bisection_check CashOrNothing_check TwoAssetBarrier_check TurnbullWakemanAsian_check AssetOrNothing_check ComplexChooser_check TimeSwitchOption_check GapOption_check SimpleChooser_check Swapoption_check BSAmericanApprox_check SpreadApproximation_check EquityLinkedFXO_check ForwardStartOption_check OptionsOnOptions_check OptionsOnOptions_check OptionsOnOptions_check GeometricAverageRateOption_check BAWbisection_check BSbisection_check grho_check ForEquOptInDomCur_check DiscreteAdjustedBarrier_check PartialTimeBarrier_check merton73_check OptionsOnTheMaxMin_check TakeoverFXoption_check TwoAssetCorrelation_check TwoAssetCashOrNothing_check VasicekBondPrice_check VasicekBondOption_check gbs_check gtheta_check gdelta_check gcarry_check black76_check blackscholes_check ggamma_check gfrench_check gvega_check quanto_check RollGeskeWhaley_check ExtendibleWriter_check Executive_check GarmanKohlhagen_check

check_options_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb
check_options_LDADD=-L. -lm
check_options_SOURCES=../src/check_options.c 

ExtremeSpreadOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEXTREMESPREADOPTION_CHECK
ExtremeSpreadOption_check_LDADD=-lm
ExtremeSpreadOption_check_SOURCES=../src/ExtremeSpreadOption.c ../src/cnd.c

PartialFloatLB_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DPARTIALFLOATLB_CHECK
PartialFloatLB_check_LDADD=-lm
PartialFloatLB_check_SOURCES=../src/PartialFloatLB.c ../src/cbnd.c ../src/cnd.c

PartialFixedLB_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DPARTIALFIXEDLB_CHECK
PartialFixedLB_check_LDADD=-lm
PartialFixedLB_check_SOURCES=../src/PartialFixedLB.c ../src/cbnd.c ../src/cnd.c

FixedStrikeLookback_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DFIXEDSTRIKELOOKBACK_CHECK
FixedStrikeLookback_check_LDADD=-lm
FixedStrikeLookback_check_SOURCES=../src/FixedStrikeLookback.c ../src/cnd.c

FloatingStrikeLookback_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DFLOATINGSTRIKELOOKBACK_CHECK
FloatingStrikeLookback_check_LDADD=-lm
FloatingStrikeLookback_check_SOURCES=../src/FloatingStrikeLookback.c ../src/cnd.c

BAWAmericanApprox_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBAWAMERICANAPPROX_CHECK
BAWAmericanApprox_check_LDADD=-lm
BAWAmericanApprox_check_SOURCES=../src/BAWAmericanApprox.c ../src/gbs.c ../src/cnd.c ../src/black76.c

StandardBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSTANDARDBARRIER_CHECK
StandardBarrier_check_LDADD=-lm
StandardBarrier_check_SOURCES=../src/StandardBarrier.c ../src/cnd.c 

PartialTimeTwoAssetBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DPARTIALTIMETWOASSETBARRIER_CHECK
PartialTimeTwoAssetBarrier_check_LDADD=-lm
PartialTimeTwoAssetBarrier_check_SOURCES=../src/PartialTimeTwoAssetBarrier.c ../src/cbnd.c ../src/cnd.c ../src/gbs.c

cbnd_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DCBND_CHECK
cbnd_check_LDADD=-lm
cbnd_check_SOURCES=../src/cbnd.c ../src/cnd.c 

cnd_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DCND_CHECK
cnd_check_LDADD=-lm
cnd_check_SOURCES=../src/cnd.c 

LookBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DLOOKBARRIER_CHECK
LookBarrier_check_LDADD=-lm
LookBarrier_check_SOURCES=../src/LookBarrier.c ../src/cnd.c ../src/cbnd.c ../src/PartialFixedLB.c

DoubleBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DDOUBLEBARRIER_CHECK
DoubleBarrier_check_LDADD=-lm
DoubleBarrier_check_SOURCES=../src/DoubleBarrier.c ../src/gbs.c ../src/cnd.c 

SoftBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSOFTBARRIER_CHECK
SoftBarrier_check_LDADD=-lm
SoftBarrier_check_SOURCES=../src/SoftBarrier.c ../src/gbs.c ../src/cnd.c 

LevyAsian_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DLEVYASIAN_CHECK
LevyAsian_check_LDADD=-lm
LevyAsian_check_SOURCES=../src/LevyAsian.c ../src/cnd.c

BinaryBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBINARYBARRIER_CHECK
BinaryBarrier_check_LDADD=-lm
BinaryBarrier_check_SOURCES=../src/BinaryBarrier.c ../src/cnd.c

JumpDiffusion_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DJUMPDIFFUSION_CHECK
JumpDiffusion_check_LDADD=-lm
JumpDiffusion_check_SOURCES=../src/JumpDiffusion.c ../src/gbs.c ../src/cnd.c


AmericanExchangeOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DAMERICANEXCHANGEOPTION_CHECK
AmericanExchangeOption_check_LDADD=-lm
AmericanExchangeOption_check_SOURCES=../src/AmericanExchangeOption.c ../src/BSAmericanApprox.c ../src/gbs.c ../src/cnd.c

EuropeanExchangeOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEUROPEANEXCHANGEOPTION_CHECK
EuropeanExchangeOption_check_LDADD=-lm
EuropeanExchangeOption_check_SOURCES=../src/EuropeanExchangeOption.c ../src/cnd.c

MiltersenSchwartz_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DMILTERSENSCHWARTZ_CHECK
MiltersenSchwartz_check_LDADD=-lm
# Slight typo in filename
MiltersenSchwartz_check_SOURCES=../src/MiltersenSwartz.c ../src/cnd.c

ExchangeExchangeOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEXCHANGEEXCHANGEOPTION_CHECK
ExchangeExchangeOption_check_LDADD=-lm
ExchangeExchangeOption_check_SOURCES=../src/ExchangeExchangeOption.c ../src/cnd.c ../src/cbnd.c

SuperShare_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSUPERSHARE_CHECK
SuperShare_check_LDADD=-lm
SuperShare_check_SOURCES=../src/SuperShare.c ../src/cnd.c

NewtonRaphson_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DNEWTONRAPHSON_CHECK
NewtonRaphson_check_LDADD=-lm
NewtonRaphson_check_SOURCES=../src/NewtonRaphson.c ../src/gbs.c ../src/gvega.c ../src/blackscholes.c ../src/cnd.c

bisection_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBISECTION_CHECK
bisection_check_LDADD=-lm
bisection_check_SOURCES=../src/bisection.c ../src/gbs.c ../src/cnd.c

CashOrNothing_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DCASHORNOTHING_CHECK
CashOrNothing_check_LDADD=-lm
CashOrNothing_check_SOURCES=../src/CashOrNothing.c ../src/cnd.c

TwoAssetBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTWOASSETBARRIER_CHECK
TwoAssetBarrier_check_LDADD=-lm
TwoAssetBarrier_check_SOURCES=../src/TwoAssetBarrier.c ../src/gbs.c ../src/cbnd.c ../src/cnd.c

TurnbullWakemanAsian_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTURNBULLWAKEMANASIAN_CHECK
TurnbullWakemanAsian_check_LDADD=-lm
TurnbullWakemanAsian_check_SOURCES=../src/TurnbullWakemanAsian.c ../src/gbs.c ../src/cnd.c

AssetOrNothing_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DASSETORNOTHING_CHECK
AssetOrNothing_check_LDADD=-lm
AssetOrNothing_check_SOURCES=../src/AssetOrNothing.c ../src/cnd.c

ComplexChooser_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DCOMPLEXCHOOSER_CHECK
ComplexChooser_check_LDADD=-lm
ComplexChooser_check_SOURCES=../src/ComplexChooser.c ../src/cnd.c ../src/cbnd.c ../src/gbs.c ../src/gdelta.c

TimeSwitchOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTIMESWITCHOPTION_CHECK
TimeSwitchOption_check_LDADD=-lm
TimeSwitchOption_check_SOURCES=../src/TimeSwitchOption.c ../src/cnd.c

GapOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGAPOPTION_CHECK
GapOption_check_LDADD=-lm
GapOption_check_SOURCES=../src/GapOption.c ../src/cnd.c

SimpleChooser_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSIMPLECHOOSER_CHECK
SimpleChooser_check_LDADD=-lm
SimpleChooser_check_SOURCES=../src/SimpleChooser.c ../src/cnd.c

Swapoption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSWAPOPTION_CHECK
Swapoption_check_LDADD=-lm
Swapoption_check_SOURCES=../src/Swapoption.c ../src/cnd.c

BSAmericanApprox_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBSAMERICANAPPROX_CHECK
BSAmericanApprox_check_LDADD=-lm
BSAmericanApprox_check_SOURCES=../src/BSAmericanApprox.c ../src/cnd.c ../src/gbs.c

SpreadApproximation_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DSPREADAPPROXIMATION_CHECK
SpreadApproximation_check_LDADD=-lm
SpreadApproximation_check_SOURCES=../src/SpreadApproximation.c ../src/cnd.c ../src/gbs.c

EquityLinkedFXO_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEQUITYLINKEDFXO_CHECK
EquityLinkedFXO_check_LDADD=-lm
EquityLinkedFXO_check_SOURCES=../src/EquityLinkedFXO.c ../src/cnd.c

ForwardStartOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DFORWARDSTARTOPTION_CHECK
ForwardStartOption_check_LDADD=-lm
ForwardStartOption_check_SOURCES=../src/ForwardStartOption.c ../src/gbs.c ../src/cnd.c

OptionsOnOptions_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DOPTIONSONOPTIONS_CHECK
OptionsOnOptions_check_LDADD=-lm
OptionsOnOptions_check_SOURCES=../src/OptionsOnOptions.c ../src/gbs.c ../src/gdelta.c ../src/cbnd.c ../src/cnd.c

GeometricAverageRateOption_check_CFLAGS=-Wshadow -ffast-math -O0 -std=c99 -W -Wall -pedantic -ggdb -DGEOMETRICAVERAGERATEOPTION_CHECK
GeometricAverageRateOption_check_LDADD=-lm
GeometricAverageRateOption_check_SOURCES=../src/GeometricAverageRateOption.c ../src/gbs.c ../src/cnd.c

BAWbisection_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBAWBISECTION_CHECK
BAWbisection_check_LDADD=-lm
BAWbisection_check_SOURCES=../src/BAWbisection.c ../src/BAWAmericanApprox.c ../src/gbs.c ../src/cnd.c

BSbisection_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBSBISECTION_CHECK
BSbisection_check_LDADD=-lm
BSbisection_check_SOURCES=../src/BSbisection.c ../src/BSAmericanApprox.c ../src/gbs.c ../src/cnd.c

grho_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGRHO_CHECK
grho_check_LDADD=-lm
grho_check_SOURCES=../src/grho.c ../src/cnd.c ../src/gbs.c

ForEquOptInDomCur_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DFOREQUOPTINDOMCUR_CHECK
ForEquOptInDomCur_check_LDADD=-lm
ForEquOptInDomCur_check_SOURCES=../src/ForEquOptInDomCur.c ../src/cnd.c

DiscreteAdjustedBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DDISCRETEADJUSTEDBARRIER_CHECK
DiscreteAdjustedBarrier_check_LDADD=-lm
DiscreteAdjustedBarrier_check_SOURCES=../src/DiscreteAdjustedBarrier.c 

PartialTimeBarrier_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DPARTIALTIMEBARRIER_CHECK
PartialTimeBarrier_check_LDADD=-lm
PartialTimeBarrier_check_SOURCES=../src/PartialTimeBarrier.c ../src/cbnd.c ../src/cnd.c

merton73_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DMERTON73_CHECK
merton73_check_LDADD=-lm
merton73_check_SOURCES=../src/merton73.c ../src/cnd.c

OptionsOnTheMaxMin_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DOPTIONSONTHEMAXMIN_CHECK
OptionsOnTheMaxMin_check_LDADD=-lm
OptionsOnTheMaxMin_check_SOURCES=../src/OptionsOnTheMaxMin.c ../src/EuropeanExchangeOption.c ../src/cbnd.c ../src/cnd.c

TakeoverFXoption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTAKEOVERFXOPTION_CHECK
TakeoverFXoption_check_LDADD=-lm
TakeoverFXoption_check_SOURCES=../src/TakeoverFXoption.c ../src/cbnd.c ../src/cnd.c

TwoAssetCorrelation_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTWOASSETCORRELATION_CHECK
TwoAssetCorrelation_check_LDADD=-lm
TwoAssetCorrelation_check_SOURCES=../src/TwoAssetCorrelation.c ../src/cbnd.c ../src/cnd.c

TwoAssetCashOrNothing_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DTWOASSETCASHORNOTHING_CHECK
TwoAssetCashOrNothing_check_LDADD=-lm
TwoAssetCashOrNothing_check_SOURCES=../src/TwoAssetCashOrNothing.c ../src/cbnd.c ../src/cnd.c

VasicekBondPrice_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DVASICEKBONDPRICE_CHECK
VasicekBondPrice_check_LDADD=-lm
VasicekBondPrice_check_SOURCES=../src/VasicekBondPrice.c ../src/cnd.c

VasicekBondOption_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DVASICEKBONDOPTION_CHECK
VasicekBondOption_check_LDADD=-lm
VasicekBondOption_check_SOURCES=../src/VasicekBondOption.c ../src/VasicekBondPrice.c ../src/cnd.c

gbs_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGBS_CHECK
gbs_check_LDADD=-lm
gbs_check_SOURCES=../src/gbs.c ../src/cnd.c

gtheta_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGTHETA_CHECK
gtheta_check_LDADD=-lm
gtheta_check_SOURCES=../src/gtheta.c ../src/cnd.c

gdelta_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGDELTA_CHECK
gdelta_check_LDADD=-lm
gdelta_check_SOURCES=../src/gdelta.c ../src/cnd.c

gcarry_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGCARRY_CHECK
gcarry_check_LDADD=-lm
gcarry_check_SOURCES=../src/gcarry.c ../src/cnd.c

black76_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBLACK76_CHECK
black76_check_LDADD=-lm
black76_check_SOURCES=../src/black76.c ../src/cnd.c

blackscholes_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DBLACKSCHOLES_CHECK
blackscholes_check_LDADD=-lm
blackscholes_check_SOURCES=../src/blackscholes.c ../src/cnd.c

ggamma_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGGAMMA_CHECK
ggamma_check_LDADD=-lm
ggamma_check_SOURCES=../src/ggamma.c 

gfrench_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGFRENCH_CHECK
gfrench_check_LDADD=-lm
gfrench_check_SOURCES=../src/gfrench.c ../src/cnd.c

gvega_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGVEGA_CHECK
gvega_check_LDADD=-lm
gvega_check_SOURCES=../src/gvega.c 

quanto_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DQUANTO_CHECK
quanto_check_LDADD=-lm
quanto_check_SOURCES=../src/Quanto.c ../src/cnd.c

RollGeskeWhaley_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DROLLGESKEWHALEY_CHECK
RollGeskeWhaley_check_LDADD=-lm
RollGeskeWhaley_check_SOURCES=../src/RollGeskeWhaley.c ../src/blackscholes.c ../src/cbnd.c ../src/cnd.c

ExtendibleWriter_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEXTENDIBLEWRITER_CHECK
ExtendibleWriter_check_LDADD=-lm
ExtendibleWriter_check_SOURCES=../src/ExtendibleWriter.c ../src/gbs.c ../src/cbnd.c ../src/cnd.c

Executive_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DEXECUTIVE_CHECK
Executive_check_LDADD=-lm
Executive_check_SOURCES=../src/Executive.c ../src/gbs.c ../src/cnd.c

GarmanKohlhagen_check_CFLAGS=-Wshadow $(FM) -O0 -std=c99 -W -Wall -pedantic -ggdb -DGARMANKOHLHAGEN_CHECK
GarmanKohlhagen_check_LDADD=-lm
GarmanKohlhagen_check_SOURCES=../src/GarmanKohlhagen.c ../src/cnd.c
