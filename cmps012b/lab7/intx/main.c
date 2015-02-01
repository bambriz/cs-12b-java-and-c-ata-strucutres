// $Id: main.c,v 1.10 2013-03-13 13:36:20-07 - - $

//
// Silly main program which just creates an intx box, puts a
// number in it, gets it back out, and deletes the box.
// Run with bcheck to verify no memory leaks.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "intx.h"

char *execname = NULL;

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc'
   execname = basename (argv[0]);

   // Declare the box and initialize it.
   intx *box = new_intx();
   printf ("box = %p\n", box);

   // Perform a couple of operations on it.
   put_intx (box, 1024);
   printf ("box value is %d\n", get_intx (box));

   // Free up the box and set the handle to NULL to avoid a dangle.
   free_intx (box);
   box = NULL;

   return EXIT_SUCCESS;
}

