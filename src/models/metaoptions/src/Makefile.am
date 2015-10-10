AUTOMAKE_OPTIONS = subdir-objects
FM=-ffast-math

AM_CFLAGS=-Winline -Wshadow $(FM) -O3 -DNDEBUG -pthread -std=c99

noinst_LIBRARIES=libmetaoptions.a 

noinst_HEADERS = metaoptions.h

libmetaoptions_a_CFLAGS=$(FM) -O3 -std=c99 \
	-Werror -Wshadow -W -Wall -pedantic -DNDEBUG -Wmissing-prototypes

libmetaoptions_a_SOURCES = \
	AmericanExchangeOption.c\
	AssetOrNothing.c\
	BAWAmericanApprox.c\
	BAWbisection.c\
	BinaryBarrier.c\
	bisection.c\
	black76.c\
	blackscholes.c\
	BSAmericanApprox.c\
	BSbisection.c\
	CashOrNothing.c\
	cbnd.c\
	cnd.c\
	ComplexChooser.c\
	DiscreteAdjustedBarrier.c\
	DoubleBarrier.c\
	EquityLinkedFXO.c\
	EuropeanExchangeOption.c\
	Executive.c\
	ExtendibleWriter.c\
	ExtremeSpreadOption.c\
	FixedStrikeLookback.c\
	FloatingStrikeLookback.c\
	ForEquOptInDomCur.c\
	ForwardStartOption.c\
	GapOption.c\
	gbs.c\
	gcarry.c\
	gdelta.c\
	GeometricAverageRateOption.c\
	gfrench.c\
	ggamma.c\
	grho.c\
	gtheta.c\
	gvega.c\
	JumpDiffusion.c\
	LevyAsian.c\
	LookBarrier.c\
	GarmanKohlhagen.c\
	merton73.c\
	MiltersenSwartz.c\
	NewtonRaphson.c\
	OptionsOnOptions.c\
	OptionsOnTheMaxMin.c\
	PartialFixedLB.c\
	PartialFloatLB.c\
	PartialTimeBarrier.c\
	PartialTimeTwoAssetBarrier.c\
	Quanto.c\
	RollGeskeWhaley.c\
	SimpleChooser.c\
	SoftBarrier.c\
	SpreadApproximation.c\
	StandardBarrier.c\
	SuperShare.c\
	Swapoption.c\
	TakeoverFXoption.c\
	TimeSwitchOption.c\
	TurnbullWakemanAsian.c\
	TwoAssetBarrier.c\
	TwoAssetCashOrNothing.c\
	TwoAssetCorrelation.c\
	ExchangeExchangeOption.c\
	VasicekBondOption.c\
	VasicekBondPrice.c\
	BarrierBinominal.c\
	ConvertibleBond.c\
	CRRBinominal.c\
	ThreeDimensionalBinominal.c\
	TrinominalTree.c
