/**********************CONSTANT-DEFINITIONS*******************/
#define ONE 1
#define UNITY 1.0
#define TWO 2.0
#define ITWO 2
#define HALF 0.5
#define ERROR 1

/***********************ARGUMENT MACROS***********************/
#define BMAX(x,y) ((x)>(y)) ? (x) : (y)
#define SQR(x) ((x)*(x))

/**********************ENUMERATION CONSTANTS******************/
typedef enum {
    CRR,            /*use Cox-Ross-Rubinstein formula for probabilities*/
    EQUIPROB,       /*use equiprobability formula*/
} formulas;

typedef enum {
    EUROCALL,       /*European call*/
    EUROPUT,        /*European put*/
    AMERCALL,       /*American call*/
    AMERPUT,        /*American put*/
} prop;

/**************************DATA TYPES**************************/
/*Set precision for floating-point calcuations*/
typedef float Float;

/*Node: data to be stored at each node in the binary tree*/
typedef struct{
    Float spot;     /*hypothetical spot price*/
    Float prob;     /*computed probability*/
    Float option;   /*computed option value*/
} Node;

/*TreeConst: parameters needed for building binomial tree*/
typedef struct{
    Float up;       /*multiplicative upward movement*/
    Float down;     /*multiplicatiive downward movement*/
    Float prob;     /*probability of upward movement*/
} TreeConst;

/*Ivar: structure containing five floating-point vars for option
 pricing*/
typedef struct{
    Float S;        /*spot price*/
    Float X;        /*strike price*/
    Float T;        /*time to expiration*/
    Float sigma;    /*volatility*/
    Float mu;       /*risk-free interest rate*/
} Ivar;
/***************************************************************/

extern float option_price(
    Ivar vars,      /*five floating vars defined in Ivar type*/
    long steps,     /*number of steps in the binomial tree*/
    int type,       /*call / put  -- American/European*/
    int method      /*Cox-Ross-Rubinstein or Equiprobability*/ );
