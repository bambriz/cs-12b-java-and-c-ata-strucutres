//Bryan Ambriz Bambriz
// $Id: bitreecalc.java,v 1.1 2013-10-16 12:58:29-07 - - $
import java.lang.*;
import java.util.*;
class bitreecalc {


   public static void main (String[] args) {
        String line = "";
        char o_var = 'o';
        String d_Num = "";
        double Numero;
        char l_var = 'b';
        Scanner scan = new Scanner(System.in);
        boolean  var_true = false; // will be used later for the scanning
        boolean test = true; // for a while loop that will continue the program until an error happens
        boolean first = true; // to scan for the first time
        while(test){ 
             if(line == "e") System.exit(1);// no longer nessacery
             if(first){ //take outside of while loop do not need the boolean logic
                   System.out.println("Please enter something foo bar");
                   line = scan.next();
                   first = false;
             }
             for(int i = 0; i<line.length(); i++){
                   //check if there is white space then find if the first non white space is a letter
                   if(line.charAt(i)!= ' '){
                        //check which letter it is
                        if(var_true){
                             //check which operator is chosen
                             o_var = line.charAt(i);
                             switch(o_var){
                                 case ':':
                                      for(int j= i+1; j<line.length()-1;j++){
                                            d_Num= d_Num.concat(line.substring(j));
                                      }
                                      Numero = Double.parseDouble(d_Num);
                                      if(Double.isNaN(Numero)){
                                          System.out.println("A is not a double");
                                          System.exit(1);
                                      } else{
                                                 System.out.println("Great Succes numero: "+Numero);
                                                 System.exit(1);
                                        } 
                                 default : 
                                        System.out.println("Not a valid operation");
                                        System.exit(1);


                             }
                             System.out.println("Code does reach var_true " +"var_true: "+var_true+" l_var: "+l_var+" O_var:  "+o_var+ " line: "+line );
                             System.exit(1);
                        } else{ 
                             if(line.charAt(i)== 'a'){
                                     var_true = true;
                                     l_var= line.charAt(i);
                              } else{ System.out.println("That is not a letter A"); 
                                      System.exit(1);
                                 } 
                         }
                    }
              }
        }  
 
    
   }

}

