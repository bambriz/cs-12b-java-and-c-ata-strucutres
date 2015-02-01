/* Bryan Ambriz
bambriz
unix.ucsc.edu
code courtesy of Wesley Mackey


Name of program----- cmatch

description: cmatch
searches the named input files for lines containing the string
.By default the matching lines are printed.
If more than one file is specified, lines
of output are preceded by the filename.




*/
#define _GNU_SOURCE
#include <errno.h> 
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;
const char *strbool (bool value) {
   return value ? "true" : "false";
}
//most of the code is from Mackey's charbyline
void cmatch (FILE *input, char *filename, char *search, options *opts) {
   char buffer[1024];
 
  for (int linenr = 1;; ++linenr) {
    char *buf = fgets (buffer, sizeof buffer, input);
    if (buf == NULL) break;
   
    if (strstr(buf, search) ||
        (opts->ignore_case && strcasestr(buf, search))){
     
      if (opts->filenames_only){
        printf("%s:", filename);
      }
      if (!opts->filenames_only){
       
        if (opts->number_lines){
          printf ("%d:%s", linenr, buf);
        } else {
          printf("%s", buf);
        }
      } else {
       
        if (strcmp(filename, STDIN_NAME) != 0) {
          printf("%s\n", filename);
          break;
        }
      }
    }
  }
}
//char *program_name = NULL;
//int exit_status = EXIT_SUCCESS;


//from the getopt file provided from Wesley Mackey
void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
            break;
      }
   }
}



//most code from charbyline and getopt
int main (int argc, char **argv) {
 // int boredom = 13;
 // int number =0;
  options opts;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);
   char *pattern; // will be the string we try to find in file
   
   // Im still a bit confused about the next part but I know it works
   if (argc == 1) {
      exit_status = EXIT_FAILURE;
	  fflush(NULL);
	  fprintf (stderr, "an error occured"); // prints an error to stderr
	  fflush(NULL);
      //tada
   }else if (argc ==2){
      if (argv[1][0] == '-' && strlen(argv[1]) != 1){
	        exit_status = EXIT_FAILURE;
	  fflush(NULL);
	  fprintf (stderr, "an error occured"); // prints an error to stderr
	  fflush(NULL);
	  
	  } else {
	       pattern = argv[1];
		   cmatch (stdin, STDIN_NAME, pattern, &opts);
	  
	    }
       
   }
   else if (argc == 3) {
     // this will check for the options from the pdf iln
	 if (argv[1][0] == '-' && strlen(argv[1]) != 1){
	   pattern = argv[2];
	    char *filename = argv[3];
		  FILE *input = fopen (filename, "r"); // learned this one in class monday
	   cmatch (input, filename, pattern, &opts);
	 } else {
	      pattern = argv[1];
		  char *filename = argv[2];
		  FILE *input = fopen (filename, "r"); // learned this one in class monday
		  cmatch (input, filename, pattern, &opts);
	 
	   }
   
   }else {
     int argerin = 2;
	 pattern = argv[1];
	 //opts.more_files = true;
	 
	 if (argv[1][0] == '-' && strlen(argv[1]) != 1){
	      pattern = argv[2];
		  argerin = 3;
		 // opts.more_files = (argc == 4)? false : true;
		  
	 
	 }
	 
	 for (; argerin < argc; ++argerin) {
	       char *filename = argv[argerin];
		   if (strcmp (filename, STDIN_NAME)){
		        cmatch (stdin, STDIN_NAME, pattern, &opts);
		   }else {
		     FILE *input = fopen (filename, "r"); // again from class
			 
			 if(input != NULL) {
			    cmatch (stdin, STDIN_NAME, pattern, &opts);
				fclose (input);
			 }else {
			    exit_status = EXIT_FAILURE;
                fflush (NULL);
                fprintf (stderr, "%s: %s: %s\n", program_name,
                filename, strerror (errno));
                fflush (NULL);
			 
			 
			   }
	 
	 
	 
	 }
   

  }
  
  }
     return exit_status;
  
}