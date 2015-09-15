/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-5
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char **argv) {

#include "globalinit.c"
  int localsize =  10+10*( (float) rand()/(float)RAND_MAX - .5),
    root = ntids-1;

  int *localsizes=NULL;
  // create local data
  localdata = (int*) malloc( localsize*sizeof(int) );
  for (i=0; i<localsize; i++)
    localdata[i] = mytid+1;
  // we assume that each process has a value "localsize"
  // the root process collectes these values

  if (mytid==root)
    localsizes = (int*) malloc( (ntids+1)*sizeof(int) );

  // everyone contributes their info
  MPI_Gather(&localsize,1,MPI_INT,
             localsizes,1,MPI_INT,root,comm);
  if (mytid==root) {
    printf("Local sizes: ");
    for (i=0; i<ntids; i++)
      printf("%d, ",localsizes[i]);
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}
