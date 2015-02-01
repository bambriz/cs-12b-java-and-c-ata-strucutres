// Bryan ambriz
//bambriz

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

char *programName = NULL;         
int exit_status = EXIT_SUCCESS;

struct options {
   bool debug;
};

typedef struct node *node_reference;
struct node {
    double value;
    node_reference link;
};

int freedom(node_reference head) {
   while (head != NULL) {
      node_reference oldfuck = head;
      head = head->link;
     // free(oldfuck->value);
      free(oldfuck);
   }
   return EXIT_SUCCESS;
}

int printAll(node_reference head, struct options *opts) {
   if (opts->debug == true) {
      for (node_reference current = head; current != NULL; current = current->link) {
         printf ("%p -> struct node {value= %.15g, link= %p}\n",
         (void*) current, current->value, (void*) current->link);
      }
      return EXIT_SUCCESS;
   } else {
      for (node_reference current = head; current != NULL; current = current->link) {
         printf("%24.15g\n", current->value);
      }
      return EXIT_SUCCESS;
   }
}

void scan_options (int argc, char **argv, struct options *opts) {
   opts->debug = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->debug = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     programName, optopt);
            fflush (NULL);
            exit_status = EXIT_FAILURE;
       }
   }
}

int main (int argc, char **argv) {
   programName = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (exit_status == EXIT_FAILURE) return exit_status;
   node_reference head = NULL;
   while (1) {
      double num;
      int rc = scanf("%lg", &num);
      if (rc == EOF) {
         printAll(head, &opts);
         break;
      } if (rc !=0 ) {
         node_reference new = malloc (sizeof(struct node));
         assert(new!=NULL);
         new->value = num;
         node_reference previous = NULL;
         node_reference current = head;
         while (current != NULL) {
            if (current->value > new->value) break;
            previous = current;
            current = current->link;
         }
         new->link = current;
         if (previous == NULL) head = new;
            else previous->link = new;
      } else {
         fprintf(stderr, "%s: invalid input\n", programName);
         exit_status = EXIT_FAILURE;
         return exit_status;
      }
   }
   freedom(head);
   return exit_status;
}
