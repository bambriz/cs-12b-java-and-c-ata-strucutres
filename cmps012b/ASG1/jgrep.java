// $Id: jgrep.java,v 1.2 2014-04-02 21:30:12-07 - - $

//
// This program is a stub showing how to create a pattern from a
// regular expression.  It does not handle options or files, and
// has some other bugs which you must discover and fix.
//


//Bryan Ambriz
//bambriz

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;

class jgrep {
    static Pattern tits;

   static void scanfile (Scanner input, String filename,
                         Pattern pattern, options opts) {
      int nLines = 1;
      while (input.hasNextLine()) {
         String line = input.nextLine();
         boolean matches = pattern.matcher (line).find();
         if (matches && !opts.reverse_match) {
             messages.exit_status = messages.EXIT_SUCCESS;
            if(opts.filename_only){
               
                out.printf(filename + "\n");
                return;
              }
               if(opts.number_lines)
                   out.printf ("%d ",nLines);
               out.printf ("%s:%s%n", filename, line);
               nLines += 1;
         }else if( !matches && opts.reverse_match){
                     if(opts.number_lines)
                        out.printf ("%d ",nLines);
               out.printf ("%s:%s%n", filename, line);
               nLines += 1;
}
      }
   }

   public static void main (String[] args) {
      options opts = new options (args);
      try {
         if(opts.insensitive){
              tits = Pattern.compile (opts.regex,
                                     Pattern.CASE_INSENSITIVE);
       } else{
          tits = Pattern.compile (opts.regex);
          }
         if (opts.filenames == null) {
            scanfile (new Scanner (in), "<stdin>", tits, opts);
         }else {
            for (int argi = 0; argi < opts.filenames.length; ++argi) {
               try {
                  String filename = opts.filenames[argi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename, tits, opts);
                  input.close();
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }
      }catch (PatternSyntaxException error) {
         messages.die (error.getMessage());
      }
      exit (messages.exit_status);
   }

}

