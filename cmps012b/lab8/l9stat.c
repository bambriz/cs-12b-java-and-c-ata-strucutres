//Bryan E. Ambriz
//bambriz


#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>



char *p_Name = NULL;
int exit_status = EXIT_SUCCESS; // used for the exit status of this program


void l9stat(char *name_of_file)
{
    double d180 = 180*24*3600;
    struct stat buffer;
	int program_status = lstat(name_of_file, &buffer);
	if (program_status != 0) 
	{
	   printf("stat hs failed");
	   fflush (NULL);
	   fprintf (stderr, "%s: %s: %s", p_Name, name_of_file, strerror (errno));
	   fflush (NULL);
	   exit_status = EXIT_FAILURE;
	   } else
	      {
		       printf("stat has succeeded ");
			   int el_size = (int)buffer.st_size; // will set el_size to equal the number value of bytes of the file
			   int la_moda = (int)buffer.st_mode; // will set la_moda to equal the mode of file which i think its the Read Write thingy im not sure but its suppose to give a number value ???
			   printf("%06o\t%d ", la_moda, el_size); // translated into C from the pearl program provided by mackey (printf "%06o %9d %s %s%s\n")
			   struct tm *tm = localtime(&buffer.st_mtime);
			   time_t realtime;
			   time(&realtime);
			   double otherT = difftime(buffer.st_mtime, realtime); // most of this stuff I have to be honest I just asked upperclass man and looked for apis and stuff online.
			   char *formatter = NULL;
			   if (otherT < 0) otherT = -otherT;
			   if (otherT > d180)
			   {
			   
			       formatter = "%b %d %y";
				   
				 } else 
				    {
					    formatter = "%b %d %X";
						
				    }
					
			    char timebuffer[1024];
				strftime(timebuffer, sizeof(timebuffer), formatter, tm);
				printf("%s %s", timebuffer, name_of_file);
				
				char *lkName = NULL;
				lkName = malloc(buffer.st_size+1);
				assert(lkName != NULL);
				int lkFlagger = readlink(name_of_file, lkName, buffer.st_size+1);
				
				
				
				if (lkFlagger != -1)
				{
				
				   lkName[buffer.st_size] = '\0';
				   printf(" --> %s", lkName);
				 }
				 
				 printf("\n");
				 
				 }
				 
			}
			
			int main(int argc, char **argv) 
			{
			
			   exit_status = EXIT_SUCCESS;
			   p_Name = basename (argv[0]);
			   
			   switch(argc){
			       case 1:
				        l9stat(".");
						
				    default:
					     for (int buki = 1; buki < argc; buki++){
						 
						     char *name_of_file = argv[buki];
							 l9stat(name_of_file);
							 
							 }
							 
				 }
				 
				 
			}