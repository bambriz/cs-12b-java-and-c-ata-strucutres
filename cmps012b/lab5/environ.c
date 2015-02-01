//Bryan Ambriz bambriz

#include <stdio.h>

extern char **environ;

int main (int argc, char **argv){
   for (int z = 0; environ[z] != NULL; z++){
      
       printf("%s\n", environ[z]);

   }

}
