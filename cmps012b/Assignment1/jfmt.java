// $Id: jfmt.java,v 1.1 2013-10-15 02:21:49-07 - - $
//
// Starter code for the jfmt utility.  This program is similar
// to the example code jcat.java, which iterates over all of its
// input files, except that this program shows how to use
// String.split to extract non-whitespace sequences of characters
// from each line.
//


/*

   This is a comment
   it has no purpose
   
    ||||     ||||
   ||  ||   ||  ||
     |||     |||
	 |||     |||
	     |||
          |	 
	 ||      ||
	  ||    ||
	   ||||||






*/
import java.io.*;
 import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;
   
   
   //This part will make sure only 65 characters are printed
    static void Printa_Paragrafo (list<String>words){
	
	     int numerCharos = 1;
		 
		 for( String word: words){
		     
			 if(numerCharos == 1){
			     
				 out.printf(word);
			 
			 } else {
			         numerCharos += 1+ word.length();
					 if(numerCharos >= 65){
						 out.printf("/n" + word);
						 numerCharos = word.length();
			   
			   } else {
			         
				   out.printf(""+word);
			   
			     }
		 
		 }
	     words.clear();
	}

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }


   // Formats a single file.
   static void format (Scanner infile) {
      // Read each line from the opened file, one after the other.
      // Stop the loop at end of file.
      for (int linenr = 1; infile.hasNextLine(); ++linenr) {
         String line = infile.nextLine();
         out.printf ("line %3d: [%s]%n", linenr, line);

         // Create a LinkedList of Strings.
         List<String> words = new LinkedList<String>();

         // Split the line into words around white space and iterate
         // over the words.
         for (String word: line.split ("\\s+")) {

            // Skip an empty word if such is found.
            if (word.length() == 0) continue;
            out.printf ("...[%s]%n", word);
            // Append the word to the end of the linked list.
            words.add (word);

         }
         out.printf ("list:");

         // Use iterator syntax to print out all of the words.
         for (String word: words) out.printf (" %s", word);
		 Printa_Paragrafo (words);
         out.printf ("%n");
      }
   }


   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // There are no filenames given on the command line.
         out.printf ("FILE: -%n");
         format (new Scanner (in));
      }else {
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (filename.equals ("-")) {
               // Treat a filename of "-" to mean System.in.
               out.printf ("FILE: -%n");
               format (new Scanner (in));
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                  out.printf ("FILE: %s%n", filename);
                  format (infile);
                  infile.close();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage());
               }
            }
         }
      }
      exit (exit_status);
   }

}
