/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: checks.cpp of optionmatrix                                         */
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
#include "main.h"
#include "license.h"

#ifdef HAVE_GETOPT_H
 #include <getopt.h>
#endif

int main(int argc, char **argv)
{
    setlocale(LC_ALL,"");
    programInits(&properties);
    props_defaults_options(&properties,1);
    bool quietMode = false;

#ifdef HAVE_GETOPT_H

    quietMode = process_arguments_checks(argc, (const char **) argv, &properties.data.debug);

#endif

    program_source();
    program_check_pricing_models(quietMode, properties.data.debug);

    exit(EXIT_SUCCESS);

} // int main(int argc, char **argv)

#ifdef HAVE_GETOPT_H

bool process_arguments_checks(const int argc, const char **argv, bool *debug)
{
    int c;
    int exit_program = false;
    int exit_status = EXIT_FAILURE;

    *debug = false;

    const static struct option long_options[] = {
        { "quiet",   no_argument,       NULL, 'q' },
        { "debug",   no_argument,       NULL, 'd' },
        { "version", no_argument,       NULL, 'v' },
        { "help",    no_argument,       NULL, 'h' },
        { NULL,      no_argument,       NULL,  0  }
    };

    int option_index = 0;
    while ((c = getopt_long(argc, (char **) argv, "qdvh", long_options, &option_index)) != -1)
    {
        int this_option_optind = optind ? optind : 1;

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

         case 'q':

            return true;

         case 'd':

            *debug = true;

            break;

         case 'v':

            program_version_checks();
            exit(EXIT_SUCCESS);

            break;

         case 'h':

            program_usage_checks();
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

    } // while ((c = getopt_long(argc, (char **) argv, "qdvh", long_options, &option_index)) != -1)
 
    if( optind < argc )
    {
        printf("\n%s: non-option argv-elements not understood: ", PACKAGE);

        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");

        exit_program = true;
        exit_status = EXIT_FAILURE;

    } // if( optind < argc )

    if( exit_program )
      exit(exit_status);
    
    return false;

} // bool process_arguments_checks(const int argc, const char **argv, bool *debug)

void program_version_checks()
{

  printf("checks for %s %s\n\n%s\n", PACKAGE, PACKAGE_VERSION, license2);

} // void program_version_checks()

void program_usage_checks()
{

  printf("Usage: checks [OPTION] ...\n");

  printf("Confirm optionmatrix access to models source code.\nIterate through and compute all optionmatrix models with various strikes and\ninputs for testing.  Report total number of tests run.");

  printf("\n\n");
  printf("  -q, --quiet           do not display output during option computations\n");
  printf("  -d, --debug           create %s.log debug file in home directory\n", PACKAGE);
  printf("  -h, --help            display this help and exit\n");
  printf("  -v, --version         output version information\n");

  printf("\nReport %s bugs to %s\n", PACKAGE, PACKAGE_BUGREPORT);

} // void program_usage_checks()

#endif
