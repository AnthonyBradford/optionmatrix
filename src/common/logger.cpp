/* optionmatrix:                                                            */
/*                                                                          */
/* Options & Futures Matrix Modeler                                         */
/* View and Control Theoretical Option Chains                               */
/*                                                                          */
/* File: logger.cpp of optionmatrix                                         */
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
#include <stdarg.h>

void logger(const char *name, const int num_args, ...)
{
  va_list ap;
  double dval;

  static FILE *fp = 0;
  static char logFile[PATH_MAX];
  char *homeDirectory;

  static int oneTime = 0;

  if( oneTime++ == 0 )
  {
    homeDirectory = getenv("HOME");

    if( homeDirectory != NULL )
       snprintf(logFile,sizeof(logFile),"%s/%s.log", homeDirectory, PACKAGE);
     else
       snprintf(logFile,sizeof(logFile),"%s.log", PACKAGE);
  }

  if( !fp && strcmp(name,"") )
  {
    fp = fopen(logFile,"w");

  } else if( fp && !strcmp(name,"") )
  {
    fprintf(fp,"logger closing debug file\n");
    fclose(fp);
    return;

  } else if( !fp && !strcmp(name,"") )
  {
    return;
  }

  //fprintf(fp,"num_args = %d\n",num_args);
  fprintf(fp,"%s\n", name);

  va_start(ap, num_args); /* make ap point to 1st unnamed arg */

  int index;
  for (index = 0; index < num_args; index++)
  {
    dval = (double) va_arg(ap, double);
    fprintf(fp,"%d = %.*f\n", index+1, 15, dval);
  }
  va_end(ap);

  fflush(fp);

} // void logger(const char *name, const int num_args, ...)
