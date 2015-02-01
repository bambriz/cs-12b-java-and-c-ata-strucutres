//Bryan E. Ambriz
//Bambriz
/* This program is numsort, 
This utility reads in double numbers from stdin ,sorts them, then prints them.
(i) Write
A program which will create an array
double array[1000]and use scanf
to read numbers into this array.
(ii) It stops reading when the first of the following happens: end of file any
invalid input not recognized by scanf or the array is full.
(iii) The numbers are then passed to the function
inssort along with a suitable
comparison function. The numbers are sorted in increasing order.
(iv) The numbers are then printed one per line using the format
"%20.15g\n"
.

*/



#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <math.h>
#include "inssort.h"

#define ARRAY_SIZE 1000
char *progname = NULL;

int doublecmp (const void *this, const void *that) {
   double *thisdoub = (double*) this;
   double *thatdoub = (double*) that;
   return *thisdoub < *thatdoub ? -1 : *thisdoub > *thatdoub ? +1 : 0;
}

int main(int agrc, char **argv) {
   progname = basename (argv[0]);
   double array[ARRAY_SIZE];
   int count = 0;
   for (; ;count++) {
      if (count == ARRAY_SIZE) {
       
         break;
      } 
      double num;
      int rc = scanf("%lg",&num);
      if (rc == EOF) {
        
         break;
      } 
      if (rc != 0) {
         array[count] = num;
      } 
      else {
       
	   
	   
	   
	   
	   
         return EXIT_FAILURE;
      }
   }
   int i = agrc; 
   i++;

   inssort(array, count, sizeof (double), doublecmp);
   for (int i = 0; i < count; i++) {
      printf("%20.15g\n",array[i]);
   }
}