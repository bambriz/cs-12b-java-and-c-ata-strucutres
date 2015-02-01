// $Id: uninit.c,v 1.1 2013-11-07 02:47:22-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int foo;
   printf ("%d\n", foo);
   int *pointer;
   printf ("%d\n", *pointer);
}
