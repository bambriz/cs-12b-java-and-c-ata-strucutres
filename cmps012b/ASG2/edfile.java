// $Id: edfile.java,v 1.8 2014-04-27 21:41:08-07 - - $

import java.util.Scanner;
import static java.lang.System.*;
import static java.lang.Integer.*;
import java.io.*;

class edfile{
 
public static int lines_read = 0;
public static int lw = 0;
    public static void w (String file_namething, dllist lines){
         try{
               //creating the file
               FileWriter FW = new FileWriter( file_namething);
              // BufferedWritter outputW = new BufferedWriter(FW);
      PrintWriter outputW = new PrintWriter(new BufferedWriter(FW));
               
               lw = 0; //lines written
               if(!lines.isempty()){
                   lines.setposition(dllist.position.LAST);
                   int last = lines.getposition();
                   lines.setposition(dllist.position.FIRST);
                   
                   for(int argi = 0; argi <= last; ++argi){
                       ++lw; // increase liens written
                       outputW.write(lines.getitem()+'\n');
                       lines.setposition(dllist.position.FOLLOWING);
                   }
               }
               
               out.printf("%d lines were written to %s%n",
                              lw,file_namething);
                //clsoe the file
                outputW.close();
                lines = null;
         }catch (Exception e){
                     lw = 0; // reset it all
                     auxlib.warn(e.getMessage());
                }
    }
    public static void i (dllist lines, String file_namething){
        lines.insert(file_namething, dllist.position.PREVIOUS);
        printCurrent(lines.getposition(),lines.getitem());
    }
    public static void d (dllist lines){
        lines.delete();
    }
    public static void a (dllist lines, String file_namething){
        lines.insert(file_namething, dllist.position.FOLLOWING);
        printCurrent(lines.getposition(),lines.getitem());
    }
    public static void greater (dllist lines){
        lines.setposition(dllist.position.FOLLOWING);
        printCurrent(lines.getposition(),lines.getitem());
    }
    public static void less  (dllist lines){
        lines.setposition(dllist.position.FIRST);
        printCurrent(lines.getposition(), lines.getitem());
        
    }
    public static void zero (dllist lines){
        lines.setposition(dllist.position.FIRST);
        printCurrent(lines.getposition(), lines.getitem());
    }
    public static void period( dllist lines){
        printCurrent(lines.getposition(), lines.getitem());
    }
    public static void asterisk( dllist lines){
       lines.print_the_lines();
       lines.setposition(dllist.position.LAST);
    }
    public static void dollar( dllist lines){
       lines.setposition(dllist.position.LAST);
       printCurrent(lines.getposition(),lines.getitem());
    }
    public static void printCurrent(int pos, String item){
      out.printf("%6d %s%n", pos, item);
   } 
    public static boolean nada(dllist lines){ //checks for empty
      if (lines.isempty()){
         out.printf("no lines in file%n");
         lines = null;
         return true;
      }
      lines = null;
      return false;
   }
 
    public static void r ( String filename, dllist lines){ //reads files
          try{
         // Open File
         FileInputStream fs = new FileInputStream( filename );
         // Get the object of DataInputStream
         DataInputStream inside = new DataInputStream(fs);
         BufferedReader buffr = new BufferedReader
                                  (new InputStreamReader(inside));
         String curr_line;
         lines_read = 0;

         //Read in File line by line
         while ((curr_line = buffr.readLine()) != null) {
            ++lines_read;
            lines.insert(curr_line, dllist.position.FOLLOWING);
         }
         inside.close();
         lines = null;
         out.println(lines_read);
      }catch (Exception e){
         lines_read = 0;
         auxlib.warn(e.getMessage());
      }
   }
     
   public static void main (String[] args) {
      boolean want_echo = false;
      dllist lines = new dllist ();
     // auxlib.STUB ("Check for -e option");
      //boolean e = false;
      
      //Read in cmd line options and arguments
      int linesread = 0;
      for(int argi = 0; argi < args.length; ++argi) {
         if(args[argi].equals("-e")){
            want_echo = true;
            continue;
         }
         
         r(args[argi],lines);
         linesread += lines_read;
      }

      if (linesread != 0)
         out.printf("%d lines read %n", linesread);
     // auxlib.STUB ("Load file from args filename, if any.");
      Scanner stdin = new Scanner (in);
      for (;;) {
         out.printf ("%s: ", auxlib.program_name());
         if (! stdin.hasNextLine()) break;
         String inputline = stdin.nextLine();
        // inputline.trim();
         if (want_echo) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         char command = inputline.charAt(0);
         String file_namething = inputline.substring(1);
         switch (command) {
            case '#': break;
            case '$': 
                      if(nada(lines)) continue;
                      dollar(lines); break;
            case '*': 
                      asterisk(lines);break;
            case '.': 
                       if(nada(lines)) continue;
                       period(lines); break;
            case '0': 
                      if(nada(lines)) continue;
                      zero(lines);break;                      
            case '<': 
                     if(nada(lines)) continue;
                     less(lines);break;                     
            case '>': 
                     if(nada(lines)) continue;
                     greater(lines); break;
            case 'a': 
                     a(lines, file_namething);break;
            case 'd': 
                     d(lines);break;
            case 'i': 
                     i(lines, file_namething); break;
            case 'r': 
                     r(file_namething, lines);
                     out.printf("%d lines were read frm %s%n",
                                 lines_read, file_namething);
                      break;
                     
            case 'w': 
                     w(file_namething, lines); break;
            default : 
                     auxlib.warn("not a valid command: "
                                     , inputline); break;
         }
      }
        
             stdin.close();
             exit(auxlib.exit_status);
         
   }

}

