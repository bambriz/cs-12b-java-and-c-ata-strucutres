//Bryan Ambriz bambriz
/* this is line sort

   this utility reads in lines from stdin into an array, sorts them, then prints them.
   
     (i) Allocate an array of 1000 pointers to character strings, read in each character string from stdin
	 and strup each line into the array. Plug the newline
	 at the the end of each line with a '\0', but dont error out if there is no newline.
	 
	use char buffer[1000] as an input buffer. The program at the end of file, or when the array is full.
	
	(ii) it then calls inssort to sort the strings using a suitable comparison function. the lines are sorted into increasing lexicographic order.
	(iii) the lines are then printed, one per line of output.
	
	*/
	
	
	#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <math.h>
#include <string.h>
#include "inssort.h"

#define MAX_LINE_LEN 4096
#define BUFFER_SIZE 1000
char *progname = NULL;

int strstrcmp (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}

int main(int argc, char **argv) {
   progname = basename (argv[0]);
   int count = 0;
   char line[MAX_LINE_LEN]; 
   char **buffer; 
   buffer = (char**)malloc(sizeof(char*) * BUFFER_SIZE); 
   count = 0; 
   while(fgets(line,MAX_LINE_LEN,stdin)) {
        if (feof(stdin)){ 
           
            break;
        }
        buffer[count] = strdup(line);
        count++;
        if (count == BUFFER_SIZE) {
            
            break;
        }
   }
   int i = argc;
   i++; 
 
   inssort(buffer, count, sizeof(buffer[0]), strstrcmp);
   for (int i = 0; i < count ; i++) {
      printf("%s", buffer[i]);
   }
   for(count=0;count<BUFFER_SIZE;count++) {
     free(buffer[count]);
   }
   free(buffer);
}