/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_main.cpp of optionmatrix                                    */
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

#include <signal.h>

#include <time.h>
#include "../common/defs.h"
#include "../common/extern.h"
#include "main.h"
#include "curses_include.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL,"");

    /* what to do if we get a control-c */
    signal(SIGINT,quit);

    programInits(&properties);

    props_defaults_options(&properties,1);
    props_defaults_futures(&future_properties,1);

#if defined(HAVE_GETOPT_H) && defined(HAVE_GETTIMEOFDAY)

    process_arguments(argc, (const char **) argv, &properties.data.debug);

#endif

    initscr();
    keypad(stdscr,TRUE);

    // if mousemask() not called Windows MSYS2 seems to change
    // from nodelay(stdscr,TRUE); to nodelay(stdscr,FALSE);
    // on any mouse click
    mousemask(ALL_MOUSE_EVENTS, NULL);

    welcome_screen();

    for(;;)
    {
        /* get initial user inputs */
        if( get_user_inputs(&properties,&future_properties) == -1 )
          continue;

        curses_process(&properties,&future_properties);

    } /* for(;;) */

} // int main(int argc, char **argv)
