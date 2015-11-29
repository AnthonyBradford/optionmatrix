/* Pricing for American and European options using binomial trees */
/* binomial.c originally named amereuro.c, main() removed         */
/* Copyright (c) Seth Pinsky. 2008                                */
/* 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "binomial.h"

/************************FUNCTION PROTOTYPES********************/
Float option_price(Ivar,long,int,int);
TreeConst GetConst(Ivar,int,long);
Float Max(Float,Float);
/***************************************************************/

/*calculate up, down, and probability based on method used*/
TreeConst GetConst(Ivar option_data, int method, long steps){
    TreeConst constants;
    Float mu, sigma, dt;


    /******DATA FOR DETERMINATION OF UP, DOWN, AND PROB******/
    mu = option_data.mu;
    sigma = option_data.sigma;
    dt = option_data.T / (steps - ONE);
    /********************************************************/
    

    /******COX-ROSS-RUBINSTEIN FORMULAE**********************/
    if(CRR == method){
        constants.up =   exp(sigma * sqrt(dt));
        constants.down = UNITY / constants.up;
        constants.prob = (exp(mu*dt) - constants.down) / 
            (constants.up - constants.down);
    }
    /********************************************************/


    /*****EQUIPROBABIITY FORMULAE****************************/
    else if(EQUIPROB == method){
        constants.prob = HALF;
        /*expressions from Hull book*/
        constants.up=exp((mu - SQR(sigma)/TWO)*dt + sigma * sqrt(dt)); 
        constants.down=exp((mu - SQR(sigma)/TWO)*dt - sigma * sqrt(dt));
    }
    /********************************************************/


    /**********FAULTY VALUE FOR METHOD***********************/
    else{
        fprintf(stderr, "ERROR: invalid method specified\n");
        exit(ERROR);
    }
    /*********************************************************/

    return constants;
}

/*return option price*/
Float option_price(
    Ivar vars,      /*five floating vars defined in Ivar type*/
    long steps,     /*number of steps in the binomial tree*/
    int type,       /*call / put  -- American/European*/
    int method      /*Cox-Ross-Rubinstein or Equiprobability*/
) {

    Node *tree;
    TreeConst constants;    /*constants for CRR or EQUIPROB*/
    Float up, down;         /*constants for CRR or EQUIPROB*/
    Float up_prob;          /*constants for CRR or EQUIPROB*/
    Float down_prob;        /*constants for CRR or EQUIPROB*/
    long StepPtr;           /*dummy: step pointer*/
    long SpotPtr;           /*dummy: price pointer*/ 
    Float discount;         /*discount factor for one time step*/
    Float price;            /*value to be returned*/
    Float dt;               /*time step*/

    /******CALCULATE DISCOUNT FACTOR FOR ONE TIME STEP********/
    dt = vars.T / (steps - ONE);
    discount = exp(-vars.mu * dt);

    /***CALCULATE APPROPRIATE CONSTANTS FOR SPECIFIED METHOD**/
    constants = GetConst(vars, method, steps);
    up = constants.up;
    down = constants.down;
    up_prob = constants.prob;
    down_prob = UNITY - up_prob;

    /******ALLOCATE SPACE FOR ONE STEP IN BINOMIAL TREE*******/
    tree = (Node*)malloc((steps + ONE)*sizeof(Node));
    if(NULL == tree){
        fprintf(stderr, "ERROR: failure of malloc()\n");
        exit(ERROR);
    }

    /*********FIRST INITIALIZE ZEROTH NODE*******************/
    tree[0].spot = vars.S;
    tree[0].prob = UNITY;

    /*********FILL TREE WITH SPOT PRICES**********************/
    for(StepPtr = ONE; StepPtr < steps; StepPtr++){
        tree[StepPtr].spot = tree[StepPtr - ONE].spot * up;
        for(SpotPtr = 0; SpotPtr < StepPtr; SpotPtr++){
            tree[SpotPtr].spot *= down; 
        }
    }

    /********FILL TREE WITH PROBABILITIES**********************/
    for(StepPtr = ONE; StepPtr < steps; StepPtr++){

        /*calculate prob for highest spot price*/
        tree[StepPtr].prob =
            tree[StepPtr - ONE].prob * up_prob;

        /*calculate prob for spot price in between*/
        for(SpotPtr = StepPtr - ONE; SpotPtr > 0; SpotPtr--){
            tree[SpotPtr].prob = 
                tree[SpotPtr].prob * down_prob
                +
                tree[SpotPtr - ONE].prob * up_prob
            ;
        }

        /*calculate prob for lowest spot price*/
        tree[0].prob *= down_prob;
    }

    /******CALCULATE OPTION VALUES ON EXPIRATION DATE**********/
    if((EUROCALL == type)||(AMERCALL == type)){
        for(SpotPtr = 0; SpotPtr < steps; SpotPtr++){
            tree[SpotPtr].option =  
                BMAX(0.0, tree[SpotPtr].spot - vars.X);
        }
    }
    else if((EUROPUT == type)||(AMERPUT == type)){
        for(SpotPtr = 0; SpotPtr < steps; SpotPtr++){
            tree[SpotPtr].option =
                BMAX(0.0, vars.X - tree[SpotPtr].spot);
        }
    }
    else{
        fprintf(stderr, "ERROR: invalid option type\n");
        exit(ERROR);
    }

    /*WALK BACKWARDS THROUGH BINOMIAL TREE FROM EXPIRATION TO ORIGIN*/
    price=0.0;
    for(StepPtr = steps - ITWO; StepPtr >=0; StepPtr--){
        for(SpotPtr = 0; SpotPtr <= StepPtr; SpotPtr++){
            Float early = 0.0;      /*value if exercised early*/

            /*calculate weighted average*/
            tree[SpotPtr].option = 
                down_prob * tree[SpotPtr].option 
                +
                up_prob * tree[SpotPtr + ONE].option
            ;

            /*calculate spot price*/
            tree[SpotPtr].spot =
                tree[SpotPtr+ONE].spot / up;

            /*apply discount factor*/
            tree[SpotPtr].option *= discount;

            /*determine if early exercise is desirable*/
            if(AMERCALL == type){
                early = BMAX(0.0, tree[SpotPtr].spot - vars.X);
            }
            else if(AMERPUT == type){
                early = BMAX(0.0, vars.X - tree[SpotPtr].spot);
            }
            
            tree[SpotPtr].option = BMAX(
                tree[SpotPtr].option,
                early
            );


        }
    }

    /*price is...*/
    price =  tree[0].option;

    /*return the binomial tree to the memory pool and return the result*/
    free(tree);
    
    return price;
}
