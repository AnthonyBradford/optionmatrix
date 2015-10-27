/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: args.cpp of optionmatrix                                           */
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

#include "defs.h"
#include "extern.h"

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

void process_arguments(int argc, char **argv, bool *debug, char *source_directory_prefix)
{
    int c;
    int exit_program = false;
    int exit_status = EXIT_FAILURE;

    *debug = false;

    static struct option long_options[] = {
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
    while ((c = getopt_long(argc, argv, "vhlsqdpD:x:m:i:", long_options, &option_index)) != -1)
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
	    sprintf(properties.source_directory_prefix,"%s", optarg);

            break;

	 case 'x':

	    //printf("optarg = %s\n", optarg);
	    sprintf(properties.data_dir,"%s", optarg);

            break;

         case 'p':

            program_check_pricing_models(false);
            exit(EXIT_SUCCESS);

            break;

         case 'q':

            program_check_pricing_models(true);
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

        }
    }
 
    if( optind < argc )
    {
        printf("\n%s: non-option argv-elements not understood: ", PACKAGE);

        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");

        exit_program = true;
        exit_status = EXIT_FAILURE;
    }

    if(*debug == true)
    {
      char logText[512];

      sprintf(logText,"%s %s", PACKAGE_NAME, PACKAGE_VERSION);
      logger(logText, 0);

      sprintf(logText,"Compiler version: %s" , __VERSION__);
      logger(logText, 0);

      sprintf(logText,"properties.source_directory_prefix = %s\n", properties.source_directory_prefix);
      logger(logText, 0);
    }

    if( exit_program )
     exit(exit_status);
    
    return;
}

#endif

void program_version()
{

  printf("%s %s\n\n%s\n", PACKAGE, PACKAGE_VERSION, license2);

}

void program_usage(char *isConsoleVersion)
{

  if( isConsoleVersion )
    printf("Usage: %s_console [OPTION] ...\n", PACKAGE);
  else
    printf("Usage: %s [OPTION] ...\n", PACKAGE);

  printf("Financial Derivatives Calculator featuring models from ");

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

  if( isConsoleVersion )
    printf("See optionmatrix for the GTK+ Version.  ");
  else
    printf("See optionmatrix_console for the Curses Version.  ");

  printf("Command line arguments can be used to list and test model execution time on the shell level.  ");

#if defined(HAVE_LIBGSL) | defined(HAVE_NEWMAT_NEWMAT_H) | defined(HAVE_ITPP_ITBASE_H) | defined(METAOPTIONS) | defined(FINRECIPES)
  printf("Compiled with the following libraries: ");
#endif

#ifdef METAOPTIONS
  printf("MetaOptions");
#endif

#ifdef FINRECIPES
  printf(", Financial Numerical Recipes in C++");
#endif

#ifdef HAVE_LIBGSL
  printf(", GSL");
#endif
  
#ifdef HAVE_NEWMAT_NEWMAT_H
  printf(", Newmat");
#endif

#ifdef HAVE_ITPP_ITBASE_H
  printf(", IT++");
#endif

  printf(".");
    
  printf("\n\n");
  printf("  -h, --help              display this help and exit\n");
  printf("  -v, --version           output version information\n\n");
  printf("  -l, --list              list models\n");
  printf("  -s, --source            print model source code which cannot be accessed\n");
  printf("  -d, --debug             create %s.log debug file\n", PACKAGE);
  printf("  -p, --price             test all pricing models\n");
  printf("  -q, --quiet             test all pricing models in quiet mode\n");
  printf("  -m, --model NUMBER      time test model number\n");
  printf("  -i, --iterate NUMBER    time test model number at specified iterations\n");

  if( !isConsoleVersion )
    printf("  -D, --Directory STRING  set model source code directory\n");

  if( !isConsoleVersion )
    printf("  -x, --datadir STRING    set datadir directory\n");

  printf("\nReport %s bugs to %s\n", PACKAGE, PACKAGE_BUGREPORT);

}

void program_list_models()
{

  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  
  for( index = 0; index < numberofmodels; index++ )
  {
    printf("%d ",option_algorithms[index].modeltype);
    printf("%s\n",option_algorithms[index].des);
  }

}

void program_source()
{

  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  char source_levelup[1024];
  char source_levelup2[1024];
  
  for( index = 0; index < numberofmodels; index++ )
  {
    sprintf(source_levelup,"../%s",option_algorithms[index].sourceCode);
    sprintf(source_levelup2,"../%s",option_algorithms[index].sourceCode2);
    //printf("%s %s\n",source_levelup,source_levelup);

    if( strcmp( option_algorithms[index].sourceCode,"") != 0 )
    {
      if( access( source_levelup, F_OK ) != 0 )
      {
        printf("Source code cannot be accessed: %s\n",option_algorithms[index].sourceCode);
      } else if( strcmp( option_algorithms[index].sourceCode2,"") != 0 )
      {
	if( access( source_levelup2, F_OK ) != 0 )
         {
           printf("Source code cannot be accessed: %s\n",option_algorithms[index].sourceCode2);
         }
      }
    }
  }

}

void program_check_pricing_models(bool quietMode)
{
  int index;
  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));
  char statusMessage[80 * 3] = { 0 };
  double strike;
  double t;
  double totalNumberOfTests = 0;

  struct _data dat;

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
  // turn debug log off
  dat.debug = false;

  int indexModelsWithPricingIssues = 0;

  // EURODIVIDENDS has a mutex lock problem on Fedora 32 bit but not Ubuntu...
  const int modelsWithPricingIssues[] = { 
    LOOKBARRIER,
    PARTIALTIMEBARRIER,
    PARTIALFIXEDLB,
    PARTIALFLOATLB,
    PARTIALFLOATLB2,
    EXTENDIBLEWRITER,
    CALLSONOPTIONS,
    PUTSONOPTIONS,
    EXCHANGEEXCHANGEOPTION,
    COMPLEXCHOOSER,
    EURODIVIDENDS,
    AMPROPORTDIVSBINOMIAL,
    BERMUDIANBINOMIAL,
    BSCOUPONBOND
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

  for( index = 0; index < numberofmodels; index++ )
  {
    continueToSkip = false;

    if( option_algorithms[index].assetClass == BOND_CLASS )
    {
      if ( !quietMode )
	printf("Bond class check not implemented\n");
      continue;

    } else if( option_algorithms[index].assetClass == TERMSTRUCTURE_CLASS )
    {
      if ( !quietMode )
	printf("Term Structure class check not implemented\n");
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
      printf("%d ",option_algorithms[index].modeltype);
      printf("%s ",option_algorithms[index].des);
      //fflush(NULL);
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

      for( strike = 5; strike < 150; strike += 5 )
      {
         sanity_check(&properties, &statusMessage[0]);

         if( option_algorithms[index].assetClass == OPTION_CLASS )
         {
           dat.strike = strike;

           struct _data optiondata;

           if( option_algorithms[index].supportCalls )
           {
             optiondata = option_call(&dat);
             totalNumberOfTests++;

	     if ( !quietMode )
	       printf("%f ",optiondata.call);

           }

           if( option_algorithms[index].supportPuts )
           {
             optiondata = option_put(&dat);
             totalNumberOfTests++;

	     if ( !quietMode )
	       printf("%f ",optiondata.put);

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
      }
    }
  }

  gettimeofday(&end, NULL);
  c1 = clock();

  dat.amounts.erase( dat.amounts.begin(), dat.amounts.end() );
  dat.times.erase( dat.times.begin(), dat.times.end() );

  if ( !quietMode )
  {
    printf("Tests skipped the following models due to open issues:\n");

    for( indexModelsWithPricingIssues = 0; indexModelsWithPricingIssues < numberOfPricingIssues; indexModelsWithPricingIssues++ )
    {
      printf("%s\n",option_algorithms[modelsWithPricingIssues[indexModelsWithPricingIssues]].des);
    }
  }

  printf("Total number of tests run: %.0f\n", totalNumberOfTests);
  printf("Time %fs\n", ( (double) (end.tv_sec + (double) end.tv_usec / 1000000)
	 - (start.tv_sec + (double) start.tv_usec / 1000000)));
  printf("CPU time: %fs\n", (float) (c1 - c0) / CLOCKS_PER_SEC);

}

void program_check_pricing_time(int modelnumber, int iterations)
{
  if( iterations < 0 )
  {
    printf("Error: Iterations must be a postive number.\n");
    return;
  }

  const int numberofmodels = (signed)(sizeofoption_algorithms/sizeof(struct option_algorithm));

  if( modelnumber < 0 || modelnumber >= numberofmodels )
  {
    printf("Error: Model range: 0 to %d\n", numberofmodels-1);
    return;
  }

  if( option_algorithms[modelnumber].assetClass == BOND_CLASS )
  {
    printf("Bond time check not implemented\n");
    return;

  } else if( option_algorithms[modelnumber].assetClass == TERMSTRUCTURE_CLASS )
  {
      printf("Term Structure time check not implemented\n");
      return;
  }

  clock_t c0, c1;
  struct timeval start, end;

  char statusMessage[80 * 3] = { 0 };

  struct _data dat;

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

  sanity_check(&properties, &statusMessage[0]);

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

    }

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
    }

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
    printf("program_check_pricing_time(): Error: Asset class not understood: %d\n", option_algorithms[modelnumber].assetClass);
  }

  dat.amounts.erase( dat.amounts.begin(), dat.amounts.end() );
  dat.times.erase( dat.times.begin(), dat.times.end() );

}
