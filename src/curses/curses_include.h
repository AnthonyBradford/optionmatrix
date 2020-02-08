/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: curses_include.h of optionmatrix                                   */
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

#ifdef HAVE_CURSES_H
# include <curses.h>

#elif HAVE_NCURSES_NCURSES_H
# include <ncurses/ncurses.h>

#elif HAVE_NCURSES_H
# include <ncurses.h>

#elif HAVE_NCURSES_CURSES_H
# include <ncurses/curses.h>

#elif HAVE_PDCURSES_CURSES_H
# include <pdcurses/pdcurses.h>

#elif HAVE_PDCURSES_H
# include <pdcurses.h>

#else
// You might still be able to build the GTK+ version of the program...
# error Sorry, this code requires curses.h for the programs curses version

#endif
