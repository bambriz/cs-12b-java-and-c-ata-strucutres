// $Id: options.java,v 1.2 2014-04-02 21:30:12-07 - - $
//Bryan Ambriz
//bambriz
import static java.lang.System.*;

class options {
   boolean insensitive = false;
   boolean filename_only= false;
   boolean number_lines= false ;
   boolean reverse_match = false;
   String regex;
   String[] filenames;

   options (String[] args) {
      if (args.length == 0) { 
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
         exit (messages.EXIT_FAILURE);
      }
     String a = messages.program_name;
     String b =" [-ilnv] regex [filename...]";
      regex = args[0];
      String key = args[1];
      filenames = new String[args.length - 1];
      for (int argi = 2; argi < args.length; ++argi) {
         
         if(regex.charAt(0)=='-'){
               filenames[argi - 2] = args[argi];
               for(int i = 0; i<regex.length()-1; i++){
               switch(regex.charAt(i)){
                     case '-':;
                     break;
                     case 'i': insensitive = true;
                    break;
                     case 'l': filename_only= true;
                     break;
                     case 'n': number_lines = true;
                     break;
                     case 'v': reverse_match = true;
                     break;
                     default :
                          err.printf("Usage: "+a+b+"%n");
                          messages.die(); 
               }
              }
           
         } 
           filenames[argi - 2] = args[argi-1]; 
      }
   }
}

