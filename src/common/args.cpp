/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: args.cpp of optionmatrix                                           */
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

#include "defs.h"
#include "extern.h"

#include <list>

#ifdef HAVE_GETOPT_H
 #include <getopt.h>
#endif

#ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
#endif

#ifdef HAVE_SYS_TIME_H
 #include <sys/time.h>
#endif

#if defined(HAVE_GETOPT_H) && defined(HAVE_GETTIMEOFDAY)

void process_arguments(const int argc, const char **argv, bool *debug)
{
    int c;
    int exit_program = false;
    int exit_status = EXIT_FAILURE;

    *debug = false;

    const static struct option long_options[] = {
        { "version",    no_argument,       NULL, 'v' },
        { "help",       no_argument,       NULL, 'h' },
        { "list",       no_argument,       NULL, 'l' },
        { "source",     no_argument,       NULL, 's' },
        { "price",      no_argument,       NULL, 'p' },
        { "quiet",      no_argument,       NULL, 'q' },
        { "debug",      no_argument,       NULL, 'd' },
        { "Directory",  required_argument, NULL, 'D' },
        { "datadir",    required_argument, NULL, 'x' },
        { "model",      required_argument, NULL, 'm' },
        { "iterate",    required_argument, NULL, 'i' },
        { NULL,         no_argument,       NULL,  0  }
    };

    // default number of options to iterate for testing and timing...
    int iopt = 200000;

    int option_index = 0;
    while ((c = getopt_long(argc, (char **) argv, "vhlsqdpD:x:m:i:", long_options, &option_index)) != -1)
    {
        switch (c) {

        case 0:

            //printf ("option %s", long_options[option_index].name);

            if (optarg)
            {
                printf (" with arg %s not understood", optarg);

                exit_program = true;
                exit_status = EXIT_FAILURE;
            }

            break;

         case 'v':

            program_version();
            exit(EXIT_SUCCESS);

            break;

         case 'h':

            program_usage(strstr(argv[0],"console"));
            exit(EXIT_SUCCESS);

            break;

         case 'l':

            program_list_models();

            exit_program = true;
            exit_status = EXIT_SUCCESS;

            break;

         case 's':

            program_source();

            exit_program = true;
            exit_status = EXIT_SUCCESS;

            break;

         case 'd':

            *debug = true;

            break;

         case 'D':

            //printf("optarg = %s\n", optarg);
            snprintf(properties.source_directory_prefix,sizeof(properties.source_directory_prefix),"%s", optarg);

            break;

         case 'x':

            //printf("optarg = %s\n", optarg);
            snprintf(properties.data_dir,sizeof(properties.data_dir),"%s", optarg);

            break;

         case 'p':

            program_check_pricing_models(false,*debug);
            exit(EXIT_SUCCESS);

            break;

         case 'q':

            program_check_pricing_models(true,*debug);
            exit(EXIT_SUCCESS);

            break;

         case 'i':

            //printf("option i with value '%d'\n", atoi(optarg));
            iopt = atoi(optarg);

            break;

         case 'm':

            //printf("option t with value '%d'\n", atoi(optarg));
            program_check_pricing_time( atoi(optarg), iopt );
            exit(EXIT_SUCCESS);

            break;

        case '?':

            exit_program = true;
            exit_status = EXIT_FAILURE;

            break;

        default:

            printf("%s: ?? getopt returned character code 0%o ??\n", PACKAGE, c);

            exit_program = true;
            exit_status = EXIT_FAILURE;

            break;

        } // switch (c) {

    } // while ((c = getopt_long(argc, (char **) argv, "vhlsqdpD:x:m:i:", long_options, &option_index)) != -1)
 
    if( optind < argc )
    {
        printf("\n%s: non-option argv-elements not understood: ", PACKAGE);

        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");

        exit_program = true;
        exit_status = EXIT_FAILURE;

    } // if( optind < argc )

    if( *debug == true )
    {
      char logText[PATH_MAX*3];

      snprintf(logText,sizeof(logText),"%s %s", PACKAGE_NAME, PACKAGE_VERSION);
      logger(logText, 0);

      snprintf(logText,sizeof(logText),"Compiler version: %s" , __VERSION__);
      logger(logText, 0);

#if defined(ENVIRONMENT32)
      snprintf(logText,sizeof(logText),"32-bit");
      logger(logText, 0);
#elif defined(ENVIRONMENT64)
      snprintf(logText,sizeof(logText),"64-bit");
      logger(logText, 0);
#else
      snprintf(logText,sizeof(logText),"Bit size unknown");
      logger(logText, 0);
#endif

      snprintf(logText,sizeof(logText),"properties.source_directory_prefix = %s\n", properties.source_directory_prefix);
      logger(logText, 0);

    } // if( *debug == true )

    if( exit_program )
     exit(exit_status);
    
    return;

} // void process_arguments(const int argc, const char **argv, bool *debug, char *source_directory_prefix)

#endif

void program_version()
{

  printf("%s %s\n\n%s\n", PACKAGE, PACKAGE_VERSION, license2);

} // void program_version()

void program_usage(const char *isConsoleVersion)
{

  if( isConsoleVersion ) {
    printf("Usage: %s_console [OPTION] ...\nCurses ", PACKAGE);
  } else
  {
    printf("Usage: %s [OPTION] ...\n", PACKAGE);
    
#ifdef HAVE_LIBGTK_3
    printf("GTK+ 3 ");
#endif

#ifdef HAVE_LIBGTK_X11_2_0
    printf("GTK+ 2 ");
#endif
 
  }

  printf("Financial Derivatives Calculator featuring models from ");

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)  

  printf("QuantLib, ");

#endif

#ifdef METAOPTIONS

  printf("Bjorn Augestad, ");

#endif

#ifdef ABRADFORD

  printf("Anthony Bradford, ");

#endif

#ifdef FINRECIPES

  printf("Bernt Arne Oedegaard, ");

#endif

#ifdef SPINSKY

  printf("and Seth Pinsky.  ");

#endif

  printf("Program with no arguments will launch the %s Application.  ", ( isConsoleVersion ? "Curses" : "Gtk+") );

  if( isConsoleVersion ) {
    printf("See optionmatrix for the GTK+ Version.  ");
  } else
  {
    printf("See optionmatrix_console for the Curses Version.  ");
  }

  printf("Command line arguments can be used to list and test model execution time on the shell level.  ");

#if defined(HAVE_QL_QUANTLIB_HPP) | defined(HAVE_LIBGSL) | defined(HAVE_NEWMAT_NEWMAT_H) | defined(HAVE_ITPP_ITBASE_H) | defined(METAOPTIONS) | defined(FINRECIPES)
  printf("Compiled with the following libraries: ");
#endif

#if defined(HAVE_QL_QUANTLIB_HPP) && defined(QUANTLIB)
  printf("QuantLib, ");
#endif

#ifdef METAOPTIONS
  printf("MetaOptions, ");
#endif

#ifdef FINRECIPES
  printf("Financial Numerical Recipes in C++, ");
#endif

#ifdef HAVE_LIBGSL
  printf("GSL, ");
#endif
  
#ifdef HAVE_NEWMAT_NEWMAT_H
  printf("Newmat, ");
#endif

#ifdef HAVE_ITPP_ITBASE_H
  printf("IT++");
#endif

  printf(".");
    
  printf("\n\n");
  printf("  -h, --help              display this help and exit\n");
  printf("  -v, --version           output version information\n\n");
  printf("  -l, --list              list models\n");
  printf("  -s, --source            print model source code which cannot be accessed\n");
  printf("  -d, --debug             create %s.log debug file in home directory\n", PACKAGE);
  printf("  -p, --price             test all pricing models\n");
  printf("  -q, --quiet             test all pricing models in quiet mode\n");
  printf("  -m, --model NUMBER      time test model number\n");
  printf("  -i, --iterate NUMBER    time test model number at specified iterations\n");

  if( !isConsoleVersion )
    printf("  -D, --Directory STRING  set model source code directory\n");

  if( !isConsoleVersion )
    printf("  -x, --datadir STRING    set datadir directory\n");

  printf("\nReport %s bugs to %s\n", PACKAGE, PACKAGE_BUGREPORT);

} // void program_usage(const char *isConsoleVersion)

void program_list_models()
{
  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));

  for( index = 0; index < numberofmodels; index++ )
  {
    printf("%d %s\n", index,option_algorithms[index].des);
  }

} // void program_list_models()

void program_source()
{
  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  char source_levelup[PATH_MAX*2];
  char source_levelup2[PATH_MAX*2];
  char source_src[PATH_MAX*2];
  char source_src2[PATH_MAX*2];

  for( index = 0; index < numberofmodels; index++ )
  {
    snprintf(source_levelup,sizeof(source_levelup),"../%s",option_algorithms[index].sourceCode);
    snprintf(source_levelup2,sizeof(source_levelup2),"../%s",option_algorithms[index].sourceCode2);

    snprintf(source_src,sizeof(source_levelup),"src/%s-%s/src/%s", PACKAGE_TARNAME,VERSION,option_algorithms[index].sourceCode);
    snprintf(source_src2,sizeof(source_levelup2),"src/%s-%s/src/%s", PACKAGE_TARNAME,VERSION,option_algorithms[index].sourceCode2);

    if( strcmp( option_algorithms[index].sourceCode,"") != 0 )
    {
      if( access( source_levelup, F_OK ) == 0 || access( source_src, F_OK ) == 0 )
      {
        //printf("%s source code found: %s\n", option_algorithms[index].des,option_algorithms[index].sourceCode);
      } else
      {
        printf("%s source code cannot be accessed: %s\n", option_algorithms[index].des,option_algorithms[index].sourceCode);
      }
 
    } // if( strcmp( option_algorithms[index].sourceCode,"") != 0 )

    if( strcmp( option_algorithms[index].sourceCode2,"") != 0 )
    {
      if( access( source_levelup2, F_OK ) == 0 || access( source_src2, F_OK ) == 0 )
      {
        //printf("%s source code found: %s\n", option_algorithms[index].des,option_algorithms[index].sourceCode2);
      } else
      {
        printf("%s source code cannot be accessed: %s\n", option_algorithms[index].des,option_algorithms[index].sourceCode2);
      }

    } // if( strcmp( option_algorithms[index].sourceCode2,"") != 0 )

  } // for( index = 0; index < numberofmodels; index++ )
  
} // void program_source()

void program_check_pricing_models(const bool quietMode, const bool debug)
{
  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  char statusMessage[80 * 4] = { 0 };
  double strike;
  double t;
  double totalNumberOfTests = 0;

  struct _data dat;
  memset( &dat, 0, sizeof(dat) );

  dat.price = 100;
  dat.rate = 0.03;
  dat.volatility = 0.25;
  dat.dividend = .02;
  dat.steps = 25;
  dat.term_model = 1;
  dat.UsePound = 1;
  dat.te  = 0;
  dat.te2 = 0;
  dat.te3 = 0;
  dat.te4 = 0;
  dat.debug = debug;
  dat.filterNegativePrices = false;

  int indexModelsWithPricingIssues = 0;

  const int modelsWithPricingIssues[] = {
    
#ifdef METAOPTIONS
    LOOKBARRIER,            // Aborted (core dumped)
    PARTIALTIMEBARRIER,     // Aborted (core dumped)
    PARTIALFIXEDLB,         // Aborted (core dumped)
    PARTIALFLOATLB,         // Aborted (core dumped)
    PARTIALFLOATLB2,        // Aborted (core dumped)
    EXTENDIBLEWRITER,       // Aborted (core dumped)
    CALLSONOPTIONS,         // Aborted (core dumped)
    PUTSONOPTIONS,          // Aborted (core dumped)
    EXCHANGEEXCHANGEOPTION, // Aborted (core dumped)
    COMPLEXCHOOSER,         // Aborted (core dumped)
#endif // METAOPTIONS

#ifdef FINRECIPES
    AMDISDIVSBINOMIAL,      // throws Exception caught: std::bad_alloc
#endif // FINRECIPES

#ifdef HAVE_QL_QUANTLIB_HPP

#endif // HAVE_QL_QUANTLIB_HPP

  };

  const int numberOfPricingIssues =  sizeof(modelsWithPricingIssues)/sizeof(modelsWithPricingIssues[0]);
  bool continueToSkip = false;

  // vector inputs, only a few mondels using this...
  dat.times.push_back(0.25);
  dat.amounts.push_back(option_algorithms[index].defaultDividend); 

  dat.times.push_back(0.75);
  dat.amounts.push_back(option_algorithms[index].defaultDividend); 
      
  dat.times.push_back(1.25);
  dat.amounts.push_back(option_algorithms[index].defaultDividend); 

  dat.times.push_back(1.75);
  dat.amounts.push_back(option_algorithms[index].defaultDividend); 

  //printf("size = %d\n", sizeof(modelsWithPricingIssues)/sizeof(modelsWithPricingIssues[0]));

  clock_t c0, c1;
  struct timeval start, end;

  c0 = clock();
  gettimeofday(&start, NULL);

  time_t model_start_time;
  time_t model_time_elasped;

  bool modelHasNegativePricing;
  std::list<std::string> modelsWithNegativePricing;

  for( index = 0; index < numberofmodels; index++ )
  {
    time(&model_start_time);
    continueToSkip = false;
    modelHasNegativePricing = false;

    if( option_algorithms[index].assetClass == BOND_CLASS )
    {
      if ( !quietMode )
        printf("Bond class check not implemented for %s\n", option_algorithms[index].des);
      continue;

    } else if( option_algorithms[index].assetClass == TERMSTRUCTURE_CLASS )
    {
      if ( !quietMode )
        printf("Term Structure class check not implemented for %s\n", option_algorithms[index].des);
      continue;
    }

    for( indexModelsWithPricingIssues = 0; indexModelsWithPricingIssues < numberOfPricingIssues; indexModelsWithPricingIssues++ )
    {
      if( option_algorithms[index].modeltype == modelsWithPricingIssues[indexModelsWithPricingIssues] )
      {
        continueToSkip = true;
        break;
      }
    }

    if(continueToSkip)
      continue;

    dat.modeltype = index;

    if ( !quietMode )
    {
      printf("Model: %d ", index);
      printf("%s ", option_algorithms[index].des);
    }

    dat.UseZ = option_algorithms[index].Zdefault;
    dat.UseB = option_algorithms[index].Bdefault;
    dat.UseJ = option_algorithms[index].Jdefault;
    dat.UseP = option_algorithms[index].Pdefault;
    dat.UseQ = option_algorithms[index].Qdefault;
    dat.UseR = option_algorithms[index].Rdefault;
    dat.UseS = option_algorithms[index].Sdefault;
    dat.UseT = option_algorithms[index].Tdefault;
    dat.UsePound = option_algorithms[index].Pounddefault;

    for( t = 0.2; t < 3; t += 0.10 )
    {
      dat.t[0] = t;
      dat.t[1] = t * 2;
      dat.t[2] = t * 3;

      bool model_timed_out = false;

      for( strike = 5; strike < 150; strike += 5 )
      {
         time(&model_time_elasped);
         if( difftime(model_time_elasped,model_start_time) > 4 )
         {
           if( !quietMode )
             printf("%s - not spending >4 seconds on any option model testing.\n", option_algorithms[index].des);
           model_timed_out = true;
           break;
         }

         statusMessage[0] = 0;
         sanity_check(&properties, &statusMessage[0],sizeof(statusMessage));

         if( option_algorithms[index].assetClass == OPTION_CLASS )
         {
           dat.strike = strike;

           struct _data optiondata;

           if( option_algorithms[index].supportCalls )
           {
             optiondata = option_call(&dat);
             totalNumberOfTests++;

             if( !quietMode )
               printf("%f ",optiondata.call);

             // sometimes the picing is almost zero but negative -0.000000
             if( optiondata.call < -1 )   
               modelHasNegativePricing = true;
           }

           if( option_algorithms[index].supportPuts )
           {
             optiondata = option_put(&dat);
             totalNumberOfTests++;

             if ( !quietMode )
               printf("%f ",optiondata.put);

             // sometimes the picing is almost zero but negative -0.000000
             if( optiondata.put < -1 )   
               modelHasNegativePricing = true;
            }

         } else if( option_algorithms[index].assetClass == FUTURES_CLASS )
         {
           struct _data futuredata;
           futuredata = future(&dat);
           totalNumberOfTests++;

           if ( !quietMode )
             printf("%f ", futuredata.price);

           // break futures have no strikes to iterate...
           break;

         } else
         {
           // should not reach...
           if ( !quietMode )
             printf("program_check_pricing_models(): asset class not understood: %d\n", option_algorithms[index].assetClass);

           break;
         }

      } // for( strike = 5; strike < 150; strike += 5 )

      if( model_timed_out == true )
        break;
      
    } // for( t = 0.2; t < 3; t += 0.10 )

    if( modelHasNegativePricing )
      modelsWithNegativePricing.push_back(option_algorithms[index].des);

  } // for( index = 0; index < numberofmodels; index++ )

  gettimeofday(&end, NULL);
  c1 = clock();

  dat.amounts.erase( dat.amounts.begin(), dat.amounts.end() );
  dat.times.erase( dat.times.begin(), dat.times.end() );

  if ( !quietMode )
  {
    printf("\n****Tests skipped the following models due to open issues:\n");

    for( indexModelsWithPricingIssues = 0; indexModelsWithPricingIssues < numberOfPricingIssues; indexModelsWithPricingIssues++ )
    {
      printf("%s\n",option_algorithms[modelsWithPricingIssues[indexModelsWithPricingIssues]].des);
    }

    std::list<std::string>::iterator it;
    printf("****Models with negative pricing:\n");
    
    for ( it=modelsWithNegativePricing.begin(); it!=modelsWithNegativePricing.end(); ++it )
      printf("%s\n", std::string(*it).c_str() );

  } // if ( !quietMode )

  printf("****Total number of tests run: %.0f\n", totalNumberOfTests);
  printf("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000)
          - (start.tv_sec + (double) start.tv_usec / 1000000)));
  printf("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);

#if defined(ENVIRONMENT32)
    printf("32-bit build\n");
#elif defined(ENVIRONMENT64)
    printf("64-bit build\n");
#endif

#ifndef ABRADFORD
  printf("ABRADFORD models not defined in source code.\n");
#endif

#ifndef SPINSKY
  printf("SPINSKY models not defined in source code.\n");
#endif

#ifndef METAOPTIONS
  printf("METAOPTIONS models not defined in source code.\n");
#endif

#ifndef FINRECIPES
  printf("FINRECIPES models not defined in source code.\n");
#endif

#ifndef HAVE_LIBGSL
  printf("HAVE_LIBGSL models not defined in source code.\n");
#endif

#ifndef HAVE_ITPP_ITBASE_H
  printf("HAVE_ITPP_ITBASE_H models not defined in source code.\n");
#endif

#ifndef HAVE_NEWMAT_NEWMAT_H
  printf("HAVE_NEWMAT_NEWMAT_H models not defined in source code.\n");
#endif

#if !defined(HAVE_QL_QUANTLIB_HPP) || !defined(QUANTLIB)
  printf("HAVE_QL_QUANTLIB_HPP models not defined in source code.\n");
#endif

} // void program_check_pricing_models(const bool quietMode, const bool debug)

void program_check_pricing_time(const int modelnumber, const int iterations)
{
  if( iterations < 0 )
  {
    fprintf(stderr,"Error: Iterations must be a postive number.\n");
    return;
  }

  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));

  if( modelnumber < 0 || modelnumber >= numberofmodels )
  {
    fprintf(stderr,"Error: Model range: 0 to %d\n", numberofmodels-1);
    return;
  }

  if( option_algorithms[modelnumber].assetClass == BOND_CLASS )
  {
    fprintf(stderr,"Bond time check not implemented for %s\n", option_algorithms[modelnumber].des);
    return;

  } else if( option_algorithms[modelnumber].assetClass == TERMSTRUCTURE_CLASS )
  {
    fprintf(stderr,"Term Structure time check not implemented for %s\n", option_algorithms[modelnumber].des);
    return;
  }

  clock_t c0, c1;
  struct timeval start, end;

  char statusMessage[80 * 4] = { 0 };

  struct _data dat;
  memset( &dat, 0, sizeof(dat) );

  dat.modeltype = modelnumber;
  dat.price = 100;
  dat.strike = 100;
  dat.rate = 0.03;
  dat.volatility = 0.25;
  dat.dividend = .02;
  dat.t[0] = 1;
  dat.t[1] = 2;
  dat.t[2] = 3;
  dat.steps = 50;
  dat.term_model = 1;
  dat.UsePound = 1;
  dat.te  = 0;
  dat.te2 = 0;
  dat.te3 = 0;
  dat.te4 = 0;
  dat.debug = false;

  printf("Model #: %d ", option_algorithms[modelnumber].modeltype);
  printf("%s\n\n", option_algorithms[modelnumber].des);

  int index = 0;

  // vector inputs, only a few mondels using this...
  dat.times.push_back(0.25);
  dat.amounts.push_back(option_algorithms[modelnumber].defaultDividend); 

  dat.times.push_back(0.75);
  dat.amounts.push_back(option_algorithms[modelnumber].defaultDividend); 
      
  dat.times.push_back(1.25);
  dat.amounts.push_back(option_algorithms[modelnumber].defaultDividend); 

  dat.times.push_back(1.75);
  dat.amounts.push_back(option_algorithms[modelnumber].defaultDividend); 

  dat.UseZ = option_algorithms[modelnumber].Zdefault;
  dat.UseB = option_algorithms[modelnumber].Bdefault;
  dat.UseJ = option_algorithms[modelnumber].Jdefault;
  dat.UseP = option_algorithms[modelnumber].Pdefault;
  dat.UseQ = option_algorithms[modelnumber].Qdefault;
  dat.UseR = option_algorithms[modelnumber].Rdefault;
  dat.UseS = option_algorithms[modelnumber].Sdefault;
  dat.UseT = option_algorithms[modelnumber].Tdefault;
  dat.UsePound = option_algorithms[modelnumber].Pounddefault;
  dat.filterNegativePrices = false;

  sanity_check(&properties, &statusMessage[0],sizeof(statusMessage));

  if( option_algorithms[modelnumber].assetClass == OPTION_CLASS )
  {
    if( option_algorithms[modelnumber].supportCalls )
    {
      struct _data optiondata;

      c0 = clock();
      gettimeofday(&start, NULL);

      for(index = 0; index < iterations; index++)
        optiondata = option_call(&dat);

      gettimeofday(&end, NULL);
      c1 = clock();

      printf("%d Calls calculated @\n", iterations);
      printf("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000)
                  - (start.tv_sec + (double) start.tv_usec / 1000000)));
      printf("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);

    } // if( option_algorithms[modelnumber].supportCalls )

    if( option_algorithms[modelnumber].supportPuts )
    {
      struct _data optiondata;

      c0 = clock();
      gettimeofday(&start, NULL);

      for(index = 0; index < iterations; index++)
        optiondata = option_put(&dat);

      gettimeofday(&end, NULL);
      c1 = clock();

      printf("\n%d Puts calculated @\n", iterations);
      printf("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000)
                  - (start.tv_sec + (double) start.tv_usec / 1000000)));
      printf("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);

    } // if( option_algorithms[modelnumber].supportPuts )

  } else if( option_algorithms[modelnumber].assetClass == FUTURES_CLASS )
  {
    struct _data futuredata;

    c0 = clock();
    gettimeofday(&start, NULL);

    for(index = 0; index < iterations; index++)
      futuredata = future(&dat);

    gettimeofday(&end, NULL);
    c1 = clock();

    printf("%d Futures calculated @\n", iterations);
    printf("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000)
                - (start.tv_sec + (double) start.tv_usec / 1000000)));
    printf("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);

  } else
  {
    // should not reach...
    fprintf(stderr,"program_check_pricing_time(): Error: Asset class not understood: %d\n", option_algorithms[modelnumber].assetClass);
  }

  dat.amounts.erase( dat.amounts.begin(), dat.amounts.end() );
  dat.times.erase( dat.times.begin(), dat.times.end() );

} // void program_check_pricing_time(const int modelnumber, const int iterations)
