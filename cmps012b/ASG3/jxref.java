// $Id: jxref.java,v 1.1 2014-05-12 23:05:01-07 - - $
 
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jxref {
   static boolean fcase = false; 
   static boolean dcase = false;
   static final String STDIN_NAME = "-";
   static String FN = "";
   
   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value)  {
         
           //code 
         
          out.printf ("%s", key);
          for (int linenr: value) out.printf (" %d", linenr);
          out.printf ("%n");
         

        
        
        
      }
   }

   static void xref_file (String filename, Scanner scan) {
      treemap <String, queue <Integer>> map =
            new treemap <String, queue <Integer>> ();
      for (int linenr = 1; scan.hasNextLine (); ++linenr) {
         for (String word: scan.nextLine().split ("\\W+")) {
            if (word.matches ("^\\d*$")) continue;
            if(fcase == true) word.toLowerCase();
            
            queue<Integer> queues = map.get(word);
            if (queues == null){
                queue<Integer> newQueue = new queue<Integer>();
                newQueue.insert(linenr);
                map.put(word, newQueue);
            }
            if (queues != null){
                queues.insert(linenr);
            }
         }
      }
      if(dcase == false){
      visitor <String, queue <Integer>> print_fn = new printer ();
      map.do_visit (print_fn);
      }else{
      map.debug_dump();
      }
   }

   public static void main (String[] args) {
   int argj = 0;
      if (args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in));
      }else{
      
         if (args[0].startsWith("-")){
             if (args[0].equals("-d")){
             dcase = true;
             }
             if (args[0].equals("-f")){
             fcase = true;
             }
             if (args[0].equals("-fd") || args[0].equals("-df")){
             dcase = true;
             fcase = true;
             }
             argj++;
         }
         if (args[0].equals("-")){
         xref_file (STDIN_NAME, new Scanner (in));
         }else{
         for (; argj < args.length; ++argj) {
            String filename = args[argj];
            FN = filename;
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in));
            }else{
               try {
                  Scanner scan = new Scanner (new File (filename));
                   
                  xref_file (filename, scan);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            }
         }
      }
      }
      auxlib.exit ();
   }

}

