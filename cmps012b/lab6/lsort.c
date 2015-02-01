// Bryan Ambriz
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
    char* value;
    node_reference link;
};

int freedom(node_reference head) {
   while (head != NULL) {
      node_reference oldfuck = head;
      head = head->link;
      free(oldfuck->value);
      free(oldfuck);
      
   }
   return EXIT_SUCCESS;
}

int printAll(node_reference head, struct options *opts) {
   if (opts->debug == true) {
      for (node_reference current = head; current != NULL; current = current->link) {
         printf ("%p -> struct node {value= %s, link= %p}\n",
         (void*) current, current->value, (void*) current->link);
      }
      return EXIT_SUCCESS;
   } else {
      for (node_reference current = head; current != NULL; current = current->link) {
         printf("%s\n", current->value);
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
   char buffer[82];
   int linenumbr;
   for (linenumbr = 1; ; ++linenumbr) {
      char *hasline = fgets (buffer, sizeof buffer, stdin);
      if (hasline == NULL) break;

      char *nullCpos = strchr (buffer, '\n');
      if (nullCpos != NULL) {
         *nullCpos = '\0';
      }else {
         exit_status = EXIT_FAILURE;
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  programName, linenumbr, buffer);
      }
         node_reference new = malloc (sizeof(struct node));
         assert(new!=NULL);
        // sprintf(output,"%f", num);
         new->value = strdup(buffer);
         node_reference previous = NULL;
         node_reference current = head;
         while (current != NULL) {
            int cmp = strcmp(current->value, new->value);
            if (cmp > 0) break;
            previous = current;
            current = current->link;
         }
         new->link = current;
         if (previous == NULL) head = new;
            else previous->link = new;
     /* } else {
         fprintf(stderr, "%s: invalid input\n", programName);
         exit_status = EXIT_FAILURE;
         return exit_status;
      }*/
      
   }
   printAll(head, &opts);
   freedom(head);
   return exit_status;
}

