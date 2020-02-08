/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: cumulative_norm.cpp of optionmatrix                                */
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

#include "defs.h"
#include "extern.h"

// This is needed so fin_recipes N() is not used but rather
// cnd() in cumulative_norm.c is used
double N(const double& z)
{
   return cnd(z);
} // double N(const double& z)

double cnd(const double d1)
{
    double dd1;

    if( integration_method[properties.integration_type].method  ||
        properties.distribution_type     != NORMAL_DISTRIBUTION ||
        properties.distribution_mean     != 0                   ||
        properties.distribution_variance != 1
      )
    {
        /*
         * if the distribution mean or variance isn't
         * normal we have to use romberg's, simpson's rule or trapeziod.
         */
        if( properties.distribution_mean     != 0   || 
            properties.distribution_variance != 1   ||
            properties.distribution_type != NORMAL_DISTRIBUTION )
        {
          if( integration_method[properties.integration_type].method == 0 )
          {
            properties.integration_type = ROMBERGS_METHOD;
            //properties.integration_type = SIMPSONS_RULE;
          }
        }

        dd1 = unit(d1);
        dd1 += (double).5;

    } else
    {
      switch(properties.integration_type)
      {
        case POLYNOMIAL_APPROX6:

          dd1 = unit_normal_poly_approx6(d1);

          break;

        case POLYNOMIAL_APPROX4:

          dd1 = unit_normal_poly_approx4(d1);

          break;

        case RATIONAL_APPROX7:

          dd1 = unit_normal_rat_7(d1);

          break;

        case RATIONAL_APPROX4:

          dd1 = unit_normal_poly_approx4(d1);

          break;

        case HART:

          dd1 = unit_normal_hart(d1);

          break;

        case ERF:

          // Square Root of 2 = 1.414213562
          dd1 = 0.5 + erf(d1/1.414213562) / 2.00;

          break;

        default:

          fprintf(stderr,"Integration type: %d not found\n", properties.integration_type);

          break;
      }
    }

    return dd1;

} // double cnd(const double d1)

/*
 * get area under the curve. calculate from mean to z-score. area under curve
 * calculated with numerical integration...
 */
double unit(const double z)
{
  return (*(distribution_list[properties.distribution_type].constantvalue))(properties.distribution_variance)*
             (*(integration_method[properties.integration_type].method))(0,(double)z,integration_method[properties.integration_type].resolution,(*distribution_list[properties.distribution_type].integrationpart),properties.distribution_mean,properties.distribution_variance);
    
}

 /*
  * Calculate the cumulative normal distribution function using
  * polynomial approximation
  * See M. Abramowitz and I. Stegun, Handbook of Mathematical Functions
  * (New York: Dover Publications, 1972
  */
double unit_normal_poly_approx6(const double z)
{
    const double y =   0.2316419;
    const double a1 =  0.319381530;
    const double a2 = -0.356563782;
    const double a3 =  1.781477937;
    const double a4 = -1.821255978;
    const double a5 =  1.330274429;
    
    if( z < 0 )
    {

      return ( (double) 1 - unit_normal_poly_approx6(-z) );
        
    } else if( z >= 0)
    {
        return (double)
               (
                (double) 1 - 
                (
                    (
                        (
                            (double)1 / (double)
                            sqrt( (double)2 * (double)M_PI)
                            
                             ) * exp((-z*z/(double)2))
                        
                    ) *
                    (
                           (a1 * (double)1/((double)((double)1+y*z))) +
                        (a2 * pow( ((double)1/(double)((double)1+y*z)),2) ) +
                        (a3 * pow( ((double)1/(double)((double)1+y*z)),3) ) +
                        (a4 * pow( ((double)1/(double)((double)1+y*z)),4) ) +
                        (a5 * pow( ((double)1/(double)((double)1+y*z)),5) )
                    )
                )
               );
    }

    /* should not reach */
    return 0;

} // double unit_normal_poly_approx6(const double z)

 /*
  * Calculate the cumulative normal distribution function using
  * polynomial approximation
  * See M. Abramowitz and I. Stegun, Handbook of Mathematical Functions
  * (New York: Dover Publications, 1972
  */
double unit_normal_poly_approx4(const double z)
{
    const double y  =  0.33267;
    const double a1 =  0.4361836;
    const double a2 = -0.1201676;
    const double a3 =  0.9372980;
    
    if( z < 0 )
    {
      return ( (double) 1 - unit_normal_poly_approx4(-z) );
        
    } else if( z >= 0 )
    {
        return (double)
               (
                (double) 1 - 
                (
                    (
                        (
                            (double)1 / (double)
                            sqrt( (double)2 * (double)M_PI)
                            
                             ) * exp((-z*z/(double)2))
                        
                    ) *
                    (
                           (a1 * (double)1/((double)((double)1+y*z))) +
                        (a2 * pow( ((double)1/(double)((double)1+y*z)),2) ) +
                        (a3 * pow( ((double)1/(double)((double)1+y*z)),3) )
                    )
                )
               );
    }

    /* should not reach */
    return 0;

} // double unit_normal_poly_approx4(const double z)

double trapezoid_rule(const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3 )
{
    int x;
    double cum = 0,h = 0;

    /* make n even */
    if( n%2 != 0 )
    {
        n++;
    }

    h = (double)(b-a) / n;

    cum = ((*fun) (a,parm2,parm3));

    for( x = 0; x < n-2; x++ )
    {
        cum = cum + (2*((*fun) (a+h,parm2,parm3)));
        h = h + (double)(b-a) / n;
    }

    cum = cum + ((*fun) (a+h,parm2,parm3));
    cum = cum * (b-a)/(2*n);  
    
    return cum;

} // double trapezoid_rule()

/*
 * Approximate integration by breaking into partitions of parabolas and
 * adding up the area of them. Variable n is the number of partitions to
 * use. (*fun) (double, double, double) is a pointer to a function which
 * will be integrated. Integrate from a to b.
 */
double simpsons_rule(const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3 )
{
    /* simpsons_rule named after Englishman Thomas Simpson (1710-1761) */

    /*
     * argument n must be even or simpsons_rule will barf
     * function to simpsons_rule takes 3 arguments
     */
    int x;
    double cum = 0, h = 0;

    /* make n even */
    if( n%2 != 0 )
    {
        n++;
    }

    h = (double)(b-a)/n;
    cum = ((*fun) (a,parm2,parm3));

    for( x = 0; x < ((n/2)-1); x++ )
    {
        cum = cum + (4*((*fun) (a+h,parm2,parm3)));
        h = h + (double )(b-a)/n;
        cum = cum + (2*((*fun) (a+h,parm2,parm3)));
        h = h+ (double)(b-a)/n;
    }
    cum = cum + (4*((*fun) (a+h,parm2,parm3)));
    cum = cum + ((*fun) (b,parm2,parm3));
    cum = cum * (b-a)/(3*n);

    return cum;

} // double simpsons_rule()

/*
 * The following Romberg's Method is based upon
 * http://code.google.com/p/romberg-integration
 */
double rombergs_method(const double a, const double b, int n, double (*fun) (double,double,double),const double parm2, const double parm3 )
{
        long double h0,h;
        long double I[2][n];
        long double temp_sum;
        unsigned int i,j,j_1;
        unsigned long exp_2 = 1;
        unsigned long exp_4 = 1;
        unsigned long exp_4_1;

        h0=b-a;
        h=h0;
        I[0][0]=h*(((*fun) (a,parm2,parm3))+((*fun) (b,parm2,parm3)))/2.0;

        for( i = 1; i < (unsigned) n; i++ )
        {
                temp_sum = 0.0;
                exp_2 <<= 1;
                h = h0 / ((long double)exp_2);
                for( j = 1; j < exp_2; j += 2 )
                {
                        temp_sum += ((*fun) (a+ j*h,parm2,parm3));
                }
                        
                I[0][i] = I[0][i-1] * 0.5 + temp_sum * h;
        }        
        for( j = 1; j < (unsigned) n; j++ )
        {
                exp_4 <<= 2;
                exp_4_1 = exp_4-1;
                j_1 = j - 1;
        
                for( i = 0; i < n-j; i++ )
                {
                    I[j%2][i] = (exp_4*I[j_1%2][i+1]-I[j_1%2][i])/(exp_4_1);
                }
        }

        return I[j%2][i];

} // double rombergs_method()

double unit_normal_rat_7(const double z)
{
    const double a1 = 0.0498673470;
    const double a2 = 0.0211410061;
    const double a3 = 0.0032776263;
    const double a4 = 0.0000380036;
    const double a5 = 0.0000488906;
    const double a6 = 0.0000053830;
    
    if( z < 0 )
    {

      return ( (double) 1 - unit_normal_rat_7(-z) );
        
    } else if( z >= 0 )
    {
        return (double)
               (
                (double) 1 -
                (
                   (double)0.5 *

                   pow(
                   (   
                        (double)1 + 
                           (a1 * z)  +
                        a2 * pow(z,2) +
                        a3 * pow(z,3) +
                        a4 * pow(z,4) +
                        a5 * pow(z,5) +
                        a6 * pow(z,6)
                   ),-16)
                )
               );
     }

    /* should not reach */
    return 0;

} // double unit_normal_rat_7(const double z)

double unit_normal_rat_4(const double z)
{
    const double a1 = 0.196854;
    const double a2 = 0.115194;
    const double a3 = 0.000344;
    const double a4 = 0.019527;
    
    if( z < 0 )
    {
      return ( (double) 1 - unit_normal_rat_4(-z) );
        
    } else if( z >= 0 )
    {
        return (double)
               (
                (double) 1 -
                (
                   (double)0.5 *

                   pow(
                   (
                        (double)1 + 
                           (a1 * z)  +
                        a2 * pow(z,2) +
                        a3 * pow(z,3) +
                        a4 * pow(z,4)

                   ),-4)
                )
               );
     }

    /* should not reach */
    return 0;

} // double unit_normal_rat_4(const double z)

double unit_normal_hart(const double x)
{
  const double a1 = 0.0352624965998911;
  const double a2 = 0.700383064443688;
  const double a3 = 6.37396220353165;
  const double a4 = 33.912866078383;
  const double a5 = 112.079291497871;
  const double a6 = 221.213596169931;
  const double a7 = 220.206867912376;

  const double b1 = 0.0883883476483184;
  const double b2 = 1.75566716318264;
  const double b3 = 16.064177579207;
  const double b4 = 86.7807322029461;
  const double b5 = 296.564248779674;
  const double b6 = 637.333633378831;
  const double b7 = 793.826512519948;
  const double b8 = 440.413735824752;

  double z;

  if( x < 0 )
  {
    z = fabs(x);
  } else
  {
    z = x;
  }

  double a = ((((((a1*z+a2)*z+a3)*z+a4)*z+a5)*z+a6)*z+a7);
  double b = (((((((b1*z+b2)*z+b3)*z+b4)*z+b5)*z+b6)*z+b7)*z+b8);
  double result;

  if( z < 7.07106781186547 )
  {
    result = 1.0 - exp(-z*z/2.0) * (a/b);

  } else if( z > 37 )
  {
    result = 1;

  } else if( z >= 7.07106781186547 )
  {
    double c = (z+1.0/(z+2.0/(z+3.0/(z+4.0/z+0.65))));

    result = 1.0 - exp(-z*z/2.0) * (1.0/(2.506628274631*c));
  }

  if( x < 0 )
  {
    return 1.0 - result;

  } else
  {
    return result;
  }

  /* should not reach */
  return 0;

} // double unit_normal_hart(const double x)

double normd(const double z)
{
  return ( ( 1.0 / sqrt( 2 * M_PI ) ) * exp ( - ( z * z ) / 2 ) );

} // double normd(const double z)
